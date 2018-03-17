#!/usr/bin/python
'''
Make the N-1 distributions for NUHM2
TMVA BDT
'''
import ROOT
import array, math
import AtlasStyle

path = "/raid07/users/walker/yuting/A4X/run/output_v41_Evaluate_BDTG/"
files = {
    # 'dataFile':
    'sigFile300': 'MGPy8EG_A14N23LO_NUHM2_m12_300_weak_2LMET50_MadSpin_NoSys/output.root',
    'sigFile350': 'MGPy8EG_A14N23LO_NUHM2_m12_350_weak_2LMET50_MadSpin_NoSys/output.root',
    'sigFile400': 'MGPy8EG_A14N23LO_NUHM2_m12_400_weak_2LMET50_MadSpin_NoSys/output.root',
    'sigFile500': 'MGPy8EG_A14N23LO_NUHM2_m12_500_weak_2LMET50_MadSpin_NoSys/output.root',
    'sigFile600': 'MGPy8EG_A14N23LO_NUHM2_m12_600_weak_2LMET50_MadSpin_NoSys/output.root',
    'sigFile700': 'MGPy8EG_A14N23LO_NUHM2_m12_700_weak_2LMET50_MadSpin_NoSys/output.root',
    'sigFile800': 'MGPy8EG_A14N23LO_NUHM2_m12_800_weak_2LMET50_MadSpin_NoSys/output.root',
    'bkgFile':    'bkg/output.root',
    'dibosonFile':'diboson_NoSys/output.root',
    'fakesFile':  'fakes_NoSys/output.root',
    'otherFile':  'other_NoSys/output.root',
    'topFile':    'top_NoSys/output.root',
    'ZttjetsFile':'Zttjets_NoSys/output.root'
}

#-----------------------------------------------#
# copy from HistFitter/analysis/higgsino/HiggsinoConfig.py

#======================================================
#
#                     Regions
#
#======================================================

# Dictionary of cuts for Tree -> hist

# cuts common to signal region 
met_trig  = 'trigMatch_metTrig'
stau_veto = '&& FS != 206 && FS != 207' # only relevant for slepton signal samples

# SF = same flavour (ee, mm), DF = different flavour (em, me), AF = all flavour (ee, mm, em, me)
# SS = same sign, OS = opposite sign
nLep2     = '&& nLep_signal == 2 && nLep_base == 2'
lep_OS    = '&& (lep1Charge != lep2Charge)'
lep_SS    = '&& (lep1Charge == lep2Charge)'
lep_SFOS  = lep_OS + '&& (lep1Flavor == lep2Flavor)'
lep_SFSS  = lep_SS + '&& (lep1Flavor == lep2Flavor)'
lep_DFOS  = lep_OS + '&& (lep1Flavor != lep2Flavor)'
lep_AFOS  = lep_OS

# EE = two electrons, MM = two muons
lep_EEOS  = lep_OS + '&& lep1Flavor == 1 && lep2Flavor == 1'
lep_MMOS  = lep_OS + '&& lep1Flavor == 2 && lep2Flavor == 2'

# EE
lep_EEME_SS = lep_SS + '&& ( (lep1Flavor == 1 && lep2Flavor == 1) || (lep1Flavor == 2 && lep2Flavor == 1) )'
lep_MMEM_SS = lep_SS + '&& ( (lep1Flavor == 2 && lep2Flavor == 2) || (lep1Flavor == 1 && lep2Flavor == 2) )'
lep_AFSS    = lep_SS 

# Jpsi veto
jpsi_veto = '&& (mll < 3 || mll > 3.2)'

# lepton author = 16 veto (ambiguous electrons from conversions)
lep_author16_veto = '&& (lep1Author != 16 && lep2Author != 16)'

# lepton truth matching
# bug in MCTruthClassifer means VVV samples not treated correctly (407311 to 407315)
lep_truth_matching = '&& ( (lep1TruthMatched && lep2TruthMatched) || (DatasetNumber >= 407311 && DatasetNumber <= 407315) )'

# Construct global cuts applied to all regions
common_cuts = met_trig + stau_veto + nLep2 + jpsi_veto + lep_author16_veto + lep_truth_matching + '&& met_Et > 200 && jetPt[0] > 100 && minDPhiAllJetsMet > 0.4 && mll > 1 && mll < 60 && lep1Pt > 5 && Rll > 0.05'
common_cuts_minDPhiAllJetsMet = met_trig + stau_veto + nLep2 + jpsi_veto + lep_author16_veto + lep_truth_matching + '&& met_Et > 200 && jetPt[0] > 100 && mll > 1 && mll < 60 && lep1Pt > 5 && Rll > 0.05'

# signal like selection without lepton flavour/multiplicity requirement
common_SR = common_cuts + '&& nBJet20_MV2c10 == 0 && DPhiJ1Met > 2.0 && (MTauTau > 160 || MTauTau < 0)'
select_hg = common_SR   + '&& METOverHTLep > max(5, 15 - 2*mll) && Rll < 2.0 && mt_lep1 < 70' 
select_sl = common_SR   + ' && METOverHTLep > max(3, 15 - 2*( mt2leplsp_100 -100) )' 

# common SR cuts with one of the variables removed
common_SR_nBJet20_MV2c10 = common_cuts + '&& DPhiJ1Met > 2.0 && (MTauTau > 160 || MTauTau < 0)'
common_SR_DPhiJ1Met      = common_cuts + '&& nBJet20_MV2c10 == 0 && (MTauTau > 160 || MTauTau < 0)'
common_SR_MTauTau        = common_cuts + '&& nBJet20_MV2c10 == 0 && DPhiJ1Met > 2.0'
common_SR_minDPhiAllJetsMet = common_cuts_minDPhiAllJetsMet + '&& nBJet20_MV2c10 == 0 && DPhiJ1Met > 2.0 && (MTauTau > 160 || MTauTau < 0)'

#-----------------------------------------------#

def main():
    # plot_N_minus_one_distribution_in_SR(600, 'tmva_BDTG', True, True)

    varexp_list = ['tmva_BDTG',
                   'met_Et', 'nJet30', 'nBJet20_MV2c10', 'DPhiJ1Met', 'minDPhiAllJetsMet', 'lep1Pt', 'lep2Pt',
                   'mt_lep1', 'MTauTau', 'mll', 'Rll', 'METOverHTLep']

    m12_list = [600, 700, 800]

    for m12 in m12_list:
        for varexp in varexp_list:
            lep_EEOS = True
            lep_MMOS = True
            plot_N_minus_one_distribution_in_SR(m12, varexp, lep_EEOS, lep_MMOS)

#-----------------------------------------------#

def get_correct_weight(genWeight, eventWeight, leptonWeight, jvtWeight, pileupWeight, bTagWeight, FFWeight):
    Lumi = 80.0
    return Lumi * 1000 * genWeight * eventWeight * leptonWeight * jvtWeight * pileupWeight * bTagWeight * FFWeight

#-----------------------------------------------#

def create_histogram(tree_name, varexp):
    '''
    create empty histogram
    '''
    xtitle = ""
    ytitle = ""
    nbins, xmin, xmax = 0, 0., 0.

    if varexp == 'tmva_BDTG':
        xtitle = "BDT"
        ytitle = "Events / 0.01"
        nbins, xmin, xmax = 20, -1., 1.
    elif varexp == "met_Et":
        xtitle = "E^{miss}_{T} [GeV]"
        ytitle = "Events / 20 GeV"
        nbins, xmin, xmax = 50, 0., 1000.
    elif varexp == "nJet30":
        xtitle = "N^{pT>30GeV}_{jets}"
        ytitle = "Events / 1"
        nbins, xmin, xmax = 10, 0., 10.
    elif varexp == "nBJet20_MV2c10":
        xtitle = "N^{pT>20GeV}_{b-jet}, 85% WP"
        ytitle = "Events / 1"
        nbins, xmin, xmax = 7, 0., 7.
    elif varexp == "DPhiJ1Met":
        xtitle = "|#Delta#phi(#font[62]{p}^{j1}_{T}, #font[62]{p}^{miss}_{T})|"
        ytitle = "Events / 0.20"
        nbins, xmin, xmax = 20, 0., 4.
    elif varexp == "minDPhiAllJetsMet":
        xtitle = "min[|#Delta#phi(#font[62]{p}^{All jets}_{T}, #font[62]{p}^{miss}_{T})|]"
        ytitle = "Events / 0.20"
        nbins, xmin, xmax = 20, 0., 4.
    elif varexp == "lep1Pt":
        xtitle = "p_{T}(#font[12]{l}_{1}) [GeV]"
        ytitle = "Events / 5 GeV"
        nbins, xmin, xmax = 40, 0., 200.
    elif varexp == "lep2Pt":
        xtitle = "p_{T}(#font[12]{l}_{2}) [GeV]"
        ytitle = "Events / 2 GeV"
        nbins, xmin, xmax = 50, 0., 100.
    elif varexp == "mt_lep1":
        xtitle = "m_{T}(#font[12]{l}_{1}) [GeV]"
        ytitle = "Events / 10 GeV"
        nbins, xmin, xmax = 20, 0., 200.
    # elif varexp == "mt_lep1+mt_lep2":
    #     xtitle = "m_{T}(#font[12]{l}_{1})+m_{T}(#font[12]{l}_{2}) [GeV]"
    #     ytitle = "Events / 10 GeV"
    #     nbins, xmin, xmax = 30, 0., 300.
    elif varexp == "MTauTau":
        xtitle = "m(#tau#tau) [GeV]"
        ytitle = "Events / 50 GeV"
        nbins, xmin, xmax = 20, -500., 500.
    elif varexp == "mll":
        xtitle = "m(#font[12]{l}#font[12]{l}) [GeV]"
        ytitle = "Events / bin"
        nbins = 11
    elif varexp == "Rll":
        xtitle = "#Delta R(#font[12]{l}#font[12]{l})"
        ytitle = "Events / 0.20"
        nbins, xmin, xmax = 25, 0., 5.
    elif varexp == "METOverHTLep":
        xtitle = "E^{miss}_{T}/H^{leptons}_{T}"
        ytitle = "Events / bin"
        nbins = 19

    mll_binning = [0., 1., 3., 5., 10., 15., 20., 25., 30., 40., 50., 60]
    METOverHTLep_binning = [0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15., 17., 20., 25., 30]

    h_name = "h_" + tree_name
    hist = None

    if varexp != "mll" and varexp != "METOverHTLep":
        hist = ROOT.TH1F(h_name, "", nbins, xmin, xmax)
    elif varexp == "mll":
        mll_binning_array = array.array("d", mll_binning)
        hist = ROOT.TH1F(h_name, "", nbins, mll_binning_array)
    elif varexp == "METOverHTLep":
        METOverHTLep_binning_array = array.array("d", METOverHTLep_binning)
        hist = ROOT.TH1F(h_name, "", nbins, METOverHTLep_binning_array)

    hist.GetXaxis().SetTitle(xtitle)
    hist.GetYaxis().SetTitle(ytitle)

    return hist

#-----------------------------------------------#

def get_N_minus_one_histogram(file, tree_name, varexp, lep_EEOS, lep_MMOS):
    '''
    Loop the tree entries to get the variable values with SR cuts applied and then dump into histogram
    return the histogram.
    '''
    hist = create_histogram(tree_name, varexp)

    fopen = ROOT.TFile(file)
    tree = fopen.Get(tree_name)
    for event in tree:
        trigMatch_metTrig = event.trigMatch_metTrig
        FS = event.FS
        nLep_signal = event.nLep_signal
        nLep_base = event.nLep_base
        mll = event.mll
        lep1Author = event.lep1Author
        lep2Author = event.lep2Author
        lep1TruthMatched = event.lep1TruthMatched
        lep2TruthMatched = event.lep2TruthMatched
        DatasetNumber = event.DatasetNumber
        met_Et = event.met_Et
        jetPt = event.jetPt
        minDPhiAllJetsMet = event.minDPhiAllJetsMet
        lep1Pt = event.lep1Pt
        Rll = event.Rll
        nBJet20_MV2c10 = event.nBJet20_MV2c10
        DPhiJ1Met = event.DPhiJ1Met
        MTauTau = event.MTauTau
        METOverHTLep = event.METOverHTLep
        mt_lep1 = event.mt_lep1

        lep1Charge = event.lep1Charge
        lep2Charge = event.lep2Charge
        lep1Flavor = event.lep1Flavor
        lep2Flavor = event.lep2Flavor

        genWeight = event.genWeight
        eventWeight = event.eventWeight
        leptonWeight = event.leptonWeight
        jvtWeight = event.jvtWeight
        pileupWeight = event.pileupWeight
        bTagWeight = event.bTagWeight
        FFWeight = event.FFWeight

        tmva_BDTG = event.tmva_BDTG

        # Apply cuts
        # if len(jetPt) >= 1:
        if ( # common_cuts
             trigMatch_metTrig == 1 and
            (FS != 206 and FS != 207) and
            (nLep_signal == 2 and nLep_base == 2) and
            # (mll < 3 or mll > 3.2) and
            (lep1Author != 16 and lep2Author != 16) and
            ( (lep1TruthMatched and lep2TruthMatched) or (DatasetNumber >= 407311 and DatasetNumber <= 407315) )
            # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
            # common_SR
            # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0)# and
            # select_hg
            # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 #and
            ):

            correct_weight = get_correct_weight(genWeight, eventWeight, leptonWeight, jvtWeight, pileupWeight, bTagWeight, FFWeight)

            value = -9999.

            if varexp == 'tmva_BDTG':
                value = event.tmva_BDTG
            elif varexp == "met_Et":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.met_Et
            elif varexp == "nJet30":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.nJet30
            elif varexp == "nBJet20_MV2c10":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                    # DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.nBJet20_MV2c10
            elif varexp == "DPhiJ1Met":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.DPhiJ1Met
            elif varexp == "minDPhiAllJetsMet":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.minDPhiAllJetsMet
            elif varexp == "lep1Pt":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.lep1Pt
            elif varexp == "lep2Pt":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.lep2Pt
            elif varexp == "mt_lep1":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 # select_hg
                    ):
                    value = mt_lep1
            # elif varexp == "mt_lep1+mt_lep2":
            #     if ((mll < 3 or mll > 3.2) and
            #         met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
            #         nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) # common_SR
            #         METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
            #         ):
            #         value = event.mt_lep1 + event.mt_lep2
            elif varexp == "MTauTau":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.MTauTau
            elif varexp == "mll":
                if (tmva_BDTG > 0.74
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and lep1Pt > 5 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.mll
            elif varexp == "Rll":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # METOverHTLep > max(5., 15. - 2.*mll) and mt_lep1 < 70 # select_hg
                    ):
                    value = event.Rll
            elif varexp == "METOverHTLep":
                if (tmva_BDTG > 0.74
                    # (mll < 3 or mll > 3.2) and
                    # met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                    # nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and # common_SR
                    # Rll < 2.0 and mt_lep1 < 70 # select_hg
                    ):
                    value = event.METOverHTLep


            if lep_EEOS is True and lep_MMOS is False:
                if (lep1Charge != lep2Charge) and lep1Flavor == 1 and lep2Flavor == 1:
                    if "data" in tree_name:
                        hist.Fill(value)
                    else:
                        hist.Fill(value, correct_weight)
            if lep_MMOS is True and lep_EEOS is False:
                if (lep1Charge != lep2Charge) and lep1Flavor == 2 and lep2Flavor == 2:
                    if "data" in tree_name:
                        hist.Fill(value)
                    else:
                        hist.Fill(value, correct_weight)
            if lep_EEOS is True and lep_MMOS is True:
                if (lep1Charge != lep2Charge) and ((lep1Flavor == 1 and lep2Flavor == 1) or (lep1Flavor == 2 and lep2Flavor == 2)):
                    if "data" in tree_name:
                        hist.Fill(value)
                    else:
                        hist.Fill(value, correct_weight)

    return hist

#-----------------------------------------------#

def plot_N_minus_one_distribution_in_SR(m12, varexp, lep_EEOS, lep_MMOS):
    file = None
    if m12 == 300:
        file = path + files['sigFile300']
    elif m12 == 350:
        file = path + files['sigFile350']
    elif m12 == 400:
        file = path + files['sigFile400']
    elif m12 == 500:
        file = path + files['sigFile500']
    elif m12 == 600:
        file = path + files['sigFile600']
    elif m12 == 700:
        file = path + files['sigFile700']
    elif m12 == 800:
        file = path + files['sigFile800']

    # signal
    h_nuhm2 = get_N_minus_one_histogram(file, "higgsino", varexp, lep_EEOS, lep_MMOS)
    h_nuhm2.SetLineColor(ROOT.kRed)
    h_nuhm2.SetLineWidth(2)
    # h_nuhm2.SetFillColor(ROOT.kRed)
    integral_nuhm2 = h_nuhm2.Integral()

    # data
    # h_data = get_N_minus_one_histogram(path + files['dataFile'], "data", varexp, lep_EEOS, lep_MMOS)
    # bkg
    h_diboson = get_N_minus_one_histogram(path + files['dibosonFile'], "higgsino", varexp, lep_EEOS, lep_MMOS)
    h_fakes   = get_N_minus_one_histogram(path + files['fakesFile'],   "higgsino",   varexp, lep_EEOS, lep_MMOS)
    h_other   = get_N_minus_one_histogram(path + files['otherFile'],   "higgsino",   varexp, lep_EEOS, lep_MMOS)
    h_top     = get_N_minus_one_histogram(path + files['topFile'],     "higgsino",     varexp, lep_EEOS, lep_MMOS)
    h_Zttjets = get_N_minus_one_histogram(path + files['ZttjetsFile'], "higgsino", varexp, lep_EEOS, lep_MMOS)

    # h_data.SetLineColor(ROOT.kBlack)
    # h_data.SetMarkerColor(ROOT.kBlack)
    # h_data.SetMarkerStyle(ROOT.kFullCircle)
    # h_data.SetMarkerSize(1.5)
    # integral_data = h_data.Integral()

    h_diboson.SetLineColor(ROOT.kOrange+1)
    h_diboson.SetFillColor(ROOT.kOrange+1)
    h_diboson.SetFillStyle(1001)
    integral_diboson = h_diboson.Integral()

    h_fakes.SetLineColor(18)
    h_fakes.SetFillColor(18)
    h_fakes.SetFillStyle(1001)
    integral_fakes = h_fakes.Integral()

    h_other.SetLineColor(ROOT.kYellow-9)
    h_other.SetFillColor(ROOT.kYellow-9)
    h_other.SetFillStyle(1001)
    integral_other = h_other.Integral()

    h_top.SetLineColor(ROOT.kAzure+7)
    h_top.SetFillColor(ROOT.kAzure+7)
    h_top.SetFillStyle(1001)
    integral_top = h_top.Integral()

    h_Zttjets.SetLineColor(ROOT.kGreen+2)
    h_Zttjets.SetFillColor(ROOT.kGreen+2)
    h_Zttjets.SetFillStyle(1001)
    integral_Zttjets = h_Zttjets.Integral()

    hstack = ROOT.THStack()
    hstack.Add(h_other)
    hstack.Add(h_diboson)
    hstack.Add(h_Zttjets)
    hstack.Add(h_top)
    hstack.Add(h_fakes)

    h_SM = h_diboson.Clone()
    h_SM.Reset()
    h_SM.Add(h_diboson)
    h_SM.Add(h_fakes)
    h_SM.Add(h_other)
    h_SM.Add(h_top)
    h_SM.Add(h_Zttjets)
    h_SM.SetLineColor(ROOT.kGray+3)
    h_SM.SetFillColor(ROOT.kGray+3)
    h_SM.SetFillStyle(0)
    integral_SM = h_SM.Integral()

    h_SM_err = h_SM.Clone()
    h_SM_err.SetLineColor(ROOT.kGray+3)
    h_SM_err.SetFillColor(ROOT.kGray+3)
    h_SM_err.SetMarkerColor(ROOT.kGray+3)
    h_SM_err.SetFillStyle(3004)

    # Set error of SM to stat + 20% syst
    for i in range(0, h_SM.GetXaxis().GetNbins()+1):
        stat = h_SM.GetBinError(i)
        syst = h_SM.GetBinContent(i)
        error = math.sqrt(stat * stat + (syst * 0.2) * (syst * 0.2))
        h_SM.SetBinError(i, error)

    # Making plot
    c1 = ROOT.TCanvas("c1", "", 800, 800)
    ROOT.gStyle.SetOptStat(0)
    # gStyle->SetOptFit(1111)

    ROOT.gPad.SetBottomMargin(0.1)
    ROOT.gPad.SetRightMargin(0.05)
    ROOT.gPad.SetLeftMargin(0.16)
    if varexp == 'tmva_BDTG':
        ROOT.gPad.SetLogy()
    # ROOT.gPad.SetGridy() # grid lines

    # Upper plot will be in pad1
    # pad1 = ROOT.TPad("pad1", "pad1", 0, 0.35, 1, 1.0)
    # pad1.SetBottomMargin(0.05)
    # pad1.SetRightMargin(0.05)
    # pad1.SetLeftMargin(0.16)
    # # pad1->SetGridy() # grid lines
    # pad1.Draw()

    # # lower plot will be in pad
    # pad2 = ROOT.TPad("pad2", "pad2", 0, 0.05, 1, 0.35)
    # pad2.SetTopMargin(0.05)
    # pad2.SetBottomMargin(0.3)
    # pad2.SetRightMargin(0.05)
    # pad2.SetLeftMargin(0.16)
    # # pad2.SetGridy() # grid lines
    # pad2.Draw()

    #
    # pad1: top pad
    #
    # pad1.cd() # pad1 becomes the current pad
    # pad1.SetFrameLineWidth(2)

    hstack.Draw("hist") # need to draw first, otherwise cannot GetHistogram()
    hstack.GetHistogram().SetStats(0)
    # hstack.SetMinimum(0.)
    if varexp == 'tmva_BDTG':
        hstack.SetMaximum(h_SM.GetMaximum() * 10)
    else:
        hstack.SetMaximum(h_SM.GetMaximum() * 2.6)
    # hstack.GetHistogram().SetXTitle("") # suppress Xtitle
    hstack.GetHistogram().SetXTitle(h_nuhm2.GetXaxis().GetTitle())
    hstack.GetXaxis().SetTitleOffset(1.2)
    if varexp == "met_Et":
        hstack.GetXaxis().SetRangeUser(0, 600)
    elif varexp == "lep1Pt" or varexp == "lep2Pt":
        hstack.GetXaxis().SetRangeUser(0, 60)
    # hstack.GetXaxis().SetLabelSize(0)
    # hstack.GetHistogram().SetYTitle(h_data.GetYaxis().GetTitle())
    hstack.GetHistogram().SetYTitle(h_nuhm2.GetYaxis().GetTitle())
    hstack.GetYaxis().SetLabelSize(0.04)
    hstack.GetYaxis().SetLabelOffset(0.015)
    hstack.GetYaxis().SetTitleSize(0.05)
    hstack.GetYaxis().SetTitleOffset(1.3)
    hstack.Draw("hist") # re-draw to make the changes working

    hstack.Draw("hist")
    h_SM.Draw("hist,same")
    h_SM_err.Draw("E2,same")
    # h_data.Draw("E,same")
    if varexp == 'tmva_BDTG':
        h_nuhm2.Scale(10.) # multiply by 10 on the Nsig because Nsig is to small
    h_nuhm2.Draw("hist,same")

    x1, x2, dx = 0., 0., 0.
    if varexp == 'tmva_BDTG':
        x1 = 0.74
        dx = h_SM.GetXaxis().GetXmax() * 0.1
    # elif varexp == "met_Et":
    #     x1 = 200.
    #     dx = h_SM.GetXaxis().GetXmax() * 0.1
    # elif varexp == "nBJet20_MV2c10":
    #     x1 = 1.
    #     dx = -1 * h_SM.GetXaxis().GetXmax() * 0.1
    # elif varexp == "DPhiJ1Met":
    #     x1 = 2.
    #     dx = h_SM.GetXaxis().GetXmax() * 0.1
    # elif varexp == "minDPhiAllJetsMet":
    #     x1 = 0.5
    #     dx = h_SM.GetXaxis().GetXmax() * 0.1
    # elif varexp == "mt_lep1":
    #     x1 = 70.
    #     dx = -1 * h_SM.GetXaxis().GetXmax() * 0.1
    # elif varexp == "MTauTau":
    #     x1 = 0.
    #     dx = -1 * h_SM.GetXaxis().GetXmax() * 0.1
    #     x2 = 160.
    # elif varexp == "Rll":
    #     x1 = 2.
    #     dx = -1 * h_SM.GetXaxis().GetXmax() * 0.1
    # elif varexp == "METOverHTLep":
    #     x1 = 5.
    #     dx = h_SM.GetXaxis().GetXmax() * 0.1

        v_line_y = h_SM.GetMaximum() * 0.2
        v_line1 = ROOT.TLine(x1, 0., x1, v_line_y)
        v_line1.SetLineWidth(3)
        v_line1.SetLineColor(ROOT.kBlack)
        v_line1.Draw()

        v_arrow1 = ROOT.TArrow(x1, v_line_y, x1+dx, v_line_y, 0.03, "|>")
        v_arrow1.SetLineColor(ROOT.kBlack)
        v_arrow1.SetLineWidth(3)
        v_arrow1.SetFillColor(ROOT.kBlack)
        v_arrow1.SetFillStyle(1001)
        v_arrow1.Draw()

    # if (varexp != 'nJet30' and
    #     varexp != 'lep1Pt' and
    #     varexp != 'lep2Pt' and
    #     varexp != 'mll'
    #     ):
    #     if varexp == 'tmva_BDTG':
    #         v_line_y = h_SM.GetMaximum() * 0.2
    #     else:
    #         v_line_y = h_SM.GetMaximum() * 1.3
    #     v_line1 = ROOT.TLine(x1, 0., x1, v_line_y)
    #     v_line1.SetLineWidth(3)
    #     v_line1.SetLineColor(ROOT.kBlack)
    #     v_line1.Draw()

    #     v_arrow1 = ROOT.TArrow(x1, v_line_y, x1+dx, v_line_y, 0.03, "|>")
    #     v_arrow1.SetLineColor(ROOT.kBlack)
    #     v_arrow1.SetLineWidth(3)
    #     v_arrow1.SetFillColor(ROOT.kBlack)
    #     v_arrow1.SetFillStyle(1001)
    #     v_arrow1.Draw()

    # v_line2, v_arror2 = None, None
    # if varexp == "MTauTau":
    #     v_line2 = ROOT.TLine(x2, 0., x2, v_line_y)
    #     v_line2.SetLineWidth(3)
    #     v_line2.SetLineColor(ROOT.kBlack)
    #     v_line2.Draw()

    #     v_arrow2 = ROOT.TArrow(x2, v_line_y, x2-dx, v_line_y, 0.03, "|>")
    #     v_arrow2.SetLineColor(ROOT.kBlack)
    #     v_arrow2.SetLineWidth(3)
    #     v_arrow2.SetFillColor(ROOT.kBlack)
    #     v_arrow2.SetFillStyle(1001)
    #     v_arrow2.Draw()

    AtlasStyle.ATLASLabel(0.2, 0.83, "Internal", ROOT.kBlack)
    AtlasStyle.myText(0.2, 0.78, "13 TeV, 80 fb^{-1}", ROOT.kBlack, 0.04)
    # if lep_EEOS is True and lep_MMOS is False:
    #     AtlasStyle.myText(0.2, 0.75, "SRee-iMLLg ee", ROOT.kBlack, 0.02)
    # if lep_MMOS is True and lep_EEOS is False:
    #     AtlasStyle.myText(0.2, 0.75, "SRmm-iMLLg #mu#mu", ROOT.kBlack, 0.02)
    # if lep_EEOS is True and lep_MMOS is True:
    #     AtlasStyle.myText(0.2, 0.75, "SRee-iMLLg ee + SRmm-iMLLg #mu#mu", ROOT.kBlack, 0.02)
    # AtlasStyle.myText(0.2, 0.72, "SusySkimHiggsino v1.9b", ROOT.kGray, 0.02)
    if varexp == 'tmva_BDTG':
        AtlasStyle.myText(0.2, 0.72, "NUHM2 curve is multiplied by 10", ROOT.kGray, 0.02)

    legend_nuhm2   = "NUHM2 m12={0} ({1:.2f})".format(m12, integral_nuhm2)
    # legend_data    = "Data ({0:.1f} Events)".format(integral_data)
    legend_SM      = "SM stat #oplus 20% syst ({0:.1f})".format(integral_SM)
    legend_fakes   = "Fake leptons ({0:.1f}%)".format(integral_fakes / integral_SM * 100)
    legend_top     = 't#bar{t}& Single top ' + "({0:.1f}%)".format(integral_top / integral_SM * 100)
    legend_Zttjets = "Z(#rightarrow#tau#tau)+jets ({0:.1f}%)".format(integral_Zttjets / integral_SM * 100)
    legend_diboson = "Diboson ({0:.1f}%)".format(integral_diboson / integral_SM * 100)
    legend_other   = "Others ({0:.1f}%)".format(integral_other / integral_SM * 100)

    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.87)
    legend.AddEntry(h_nuhm2, legend_nuhm2, "l")
    # legend.AddEntry(h_data, legend_data, "pl")
    legend.AddEntry(h_SM_err, legend_SM, "fl")
    legend.AddEntry(h_fakes, legend_fakes, "f")
    legend.AddEntry(h_top, legend_top, "f")
    legend.AddEntry(h_Zttjets, legend_Zttjets, "f")
    legend.AddEntry(h_diboson, legend_diboson, "f")
    legend.AddEntry(h_other, legend_other, "f")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.02);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    #
    # pad2: bottom pad
    #
    # pad2.cd() # pad2 becomes the current pad

    # pad2_X_min = h_data.GetXaxis().GetXmin()
    # pad2_X_max = h_data.GetXaxis().GetXmax()
    # pad2_Y_min = 0.
    # pad2_Y_max = 2.
    # pad2_X_title = h_data.GetXaxis().GetTitle()
    # pad2_Y_title = "Data / SM"

    # frame = pad2.DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max)
    # frame.GetXaxis().SetNdivisions(510)
    # frame.GetYaxis().SetNdivisions(405)
    # frame.SetLineWidth(1)
    # frame.SetXTitle(pad2_X_title)
    # frame.GetXaxis().SetTitleSize(25)
    # frame.GetXaxis().SetTitleFont(47)
    # frame.GetXaxis().SetTitleOffset(4.0)
    # frame.GetXaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
    # frame.GetXaxis().SetLabelSize(20)
    # frame.GetXaxis().SetLabelOffset(0.05)
    # frame.SetYTitle(pad2_Y_title)
    # frame.GetYaxis().SetTitleSize(25)
    # frame.GetYaxis().SetTitleFont(43)
    # frame.GetYaxis().SetTitleOffset(2.0)
    # frame.GetYaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
    # frame.GetYaxis().SetLabelSize(20)
    # frame.GetYaxis().SetLabelOffset(0.015)
    # frame.Draw()

    # line = ROOT.TLine(pad2_X_min, 1., pad2_X_max, 1.)
    # line.SetLineColor(ROOT.kBlack)
    # line.SetLineStyle(1)
    # line.SetLineWidth(1)
    # line.Draw("same")

    # h_data_over_SM = h_data.Clone()
    # h_data_over_SM.Divide(h_SM)
    # h_data_over_SM.SetLineColor(ROOT.kBlack)
    # h_data_over_SM.SetMarkerColor(ROOT.kBlack)
    # h_data_over_SM.SetMarkerStyle(ROOT.kFullCircle)
    # h_data_over_SM.SetMarkerSize(1.5)

    # bin_center = []
    # for i in range(0, h_data_over_SM.GetXaxis().GetNbins()+1):
    #     # remove the 0 bin content points by setting the central value to -99
    #     if h_data_over_SM.GetBinContent(i) == 0:
    #         h_data_over_SM.SetBinContent(i, -99.)
    #     if h_data_over_SM.GetBinContent(i) > 2:
    #         bin_center.append(h_data_over_SM.GetBinCenter(i))

    # h_data_over_SM.Draw("E0,same")
    # # Use E optoin, then no 0 bin content points are drawn but no error bars for those point > 2
    # # Use E0 option, the 0 bin content points are drawn and so do error bars

    # # Add a small arrow for those bins with central value > 2
    # arrow_list = []
    # for x in bin_center:
    #     arrow = ROOT.TArrow(x, 1.7, x, 1.95, 0.01, "|>")
    #     # arrow.SetArrowSize(0.02)
    #     arrow.SetLineColor(ROOT.kOrange+1)
    #     arrow.SetLineWidth(3)
    #     arrow.SetFillColor(ROOT.kOrange+1)
    #     arrow.SetFillStyle(1001)
    #     # If draw arrow at here, then only the last arrow is drawn.
    #     # So put arrow object into a list and draw them later.
    #     if x < pad2_X_max:
    #         arrow_list.append(arrow)
    # for arrow in arrow_list:
    #     arrow.Draw()

    # h_SM_over_SM = h_SM.Clone()
    # h_SM_over_SM.Divide(h_SM)
    # h_SM_over_SM.SetLineColor(ROOT.kGray+3)
    # h_SM_over_SM.SetFillColor(ROOT.kGray+3)
    # h_SM_over_SM.SetMarkerColor(ROOT.kGray+3)
    # h_SM_over_SM.SetFillStyle(3004)
    # h_SM_over_SM.Draw("E2,same")

    output = "NUHM2_m12_" + str(m12) + "_and_Bkg_" + varexp

    if lep_EEOS is True and lep_MMOS is False:
        output += "_EEOS"
    if lep_MMOS is True and lep_EEOS is False:
        output += "_MMOS"
    if lep_EEOS is True and lep_MMOS is True:
        output += "_SFOS"
    # output += "_N_minus_one_distribution_in_SR.pdf"
    output += "_N_minus_one_distribution_in_SR_times_10_on_Nsig.pdf"

    c1.SaveAs(output)

#----------------------------#

if __name__ == '__main__':
    main()
