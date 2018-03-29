#!/usr/bin/python
'''
plot 2D METOverHT vs mll plot
'''
import ROOT
import AtlasStyle

path = "/afs/cern.ch/work/j/jeliu/public/HiggsinoFitterTrees/v1_9/"
files = {
    'sigFile':    'AllSignals_SusySkimHiggsino_v1.9b_SUSY16_tree_AllSys.root',
    'dataFile':   'data_SusySkimHiggsino_v1.9_hadded_tree.root',
    'dibosonFile':'diboson_SusySkimHiggsino_v1.9_hadded_tree.root',
    'fakesFile':  'fakes2Lb_DijetFFs_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root',
    'otherFile':  'other_SusySkimHiggsino_v1.9_hadded_tree.root',
    'topFile':    'top_SusySkimHiggsino_v1.9_hadded_tree.root',
    'ZttjetsFile':'Zttjets_SusySkimHiggsino_v1.9_hadded_tree.root'
}

#------------------------------------------------#

def get_correct_weight(genWeight, eventWeight, leptonWeight, jvtWeight, pileupWeight, bTagWeight, FFWeight):
    Lumi = 80.0
    return Lumi * 1000 * genWeight * eventWeight * leptonWeight * jvtWeight * pileupWeight * bTagWeight * FFWeight

#------------------------------------------------#

def get_histogram(file, tree_name, histogram_name):
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
        lep2Pt = event.lep2Pt
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

        # Apply all SR cuts except METOverHT and mll cuts
        if len(jetPt) >= 1:
            if ( # common_cuts
                trigMatch_metTrig == 1 and
                (FS != 206 and FS != 207) and
                (nLep_signal == 2 and nLep_base == 2) and
                # (mll < 3 or mll > 3.2) and
                (lep1Author != 16 and lep2Author != 16) and
                ( (lep1TruthMatched and lep2TruthMatched) or (DatasetNumber >= 407311 and DatasetNumber <= 407315) ) and
                ( (lep1Charge != lep2Charge) and (lep1Flavor == lep2Flavor) ) and
                met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                # common_SR
                nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0) and
                # select_hg
                # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 #and
                Rll < 2.0 and mt_lep1 < 70
                ):

                lep2_pt_requirement = 0.
                if lep1Flavor == 1: # electron
                    lep2_pt_requirement = 4.5
                elif lep2Flavor == 2: #muon
                    lep2_pt_requirement = 4

                if lep2Pt > lep2_pt_requirement:
                    correct_weight = get_correct_weight(genWeight, eventWeight, leptonWeight, jvtWeight, pileupWeight, bTagWeight, FFWeight)

                    x_value = event.mll
                    y_value = event.METOverHTLep

                    histogram_name.Fill(x_value, y_value, correct_weight)

    return histogram_name

#------------------------------------------------#

def main():
    # METOverHT function
    func1 = ROOT.TF1("func1", "TMath::Max(5., 15.-2.*x)", 0, 30)
    func1.SetLineColor(ROOT.kRed)

    # 2-D histograms for NUHM2
    hist_m12_350 = ROOT.TH2F("hist_m12_350", "", 300, 0., 30., 500, 0., 50)
    hist_m12_400 = ROOT.TH2F("hist_m12_400", "", 300, 0., 30., 500, 0., 50)
    hist_m12_500 = ROOT.TH2F("hist_m12_500", "", 300, 0., 30., 500, 0., 50)
    hist_m12_600 = ROOT.TH2F("hist_m12_600", "", 300, 0., 30., 500, 0., 50)
    hist_m12_700 = ROOT.TH2F("hist_m12_700", "", 300, 0., 30., 500, 0., 50)
    hist_m12_800 = ROOT.TH2F("hist_m12_800", "", 300, 0., 30., 500, 0., 50)

    get_histogram(path + files['sigFile'], "MGPy8EG_A14N23LO_NUHM2_m12_350_weak_NoSys", hist_m12_350)
    get_histogram(path + files['sigFile'], "MGPy8EG_A14N23LO_NUHM2_m12_400_weak_NoSys", hist_m12_400)
    get_histogram(path + files['sigFile'], "MGPy8EG_A14N23LO_NUHM2_m12_500_weak_NoSys", hist_m12_500)
    get_histogram(path + files['sigFile'], "MGPy8EG_A14N23LO_NUHM2_m12_600_weak_NoSys", hist_m12_600)
    get_histogram(path + files['sigFile'], "MGPy8EG_A14N23LO_NUHM2_m12_700_weak_NoSys", hist_m12_700)
    get_histogram(path + files['sigFile'], "MGPy8EG_A14N23LO_NUHM2_m12_800_weak_NoSys", hist_m12_800)

    hist_m12_350.SetMarkerStyle(ROOT.kFullCircle)
    hist_m12_400.SetMarkerStyle(ROOT.kFullCircle)
    hist_m12_500.SetMarkerStyle(ROOT.kFullCircle)
    hist_m12_600.SetMarkerStyle(ROOT.kFullCircle)
    hist_m12_700.SetMarkerStyle(ROOT.kFullCircle)
    hist_m12_800.SetMarkerStyle(ROOT.kFullCircle)

    hist_m12_350.SetMarkerColor(ROOT.kAzure)
    hist_m12_400.SetMarkerColor(ROOT.kMagenta)
    hist_m12_500.SetMarkerColor(ROOT.kRed)
    hist_m12_600.SetMarkerColor(ROOT.kYellow)
    hist_m12_700.SetMarkerColor(ROOT.kGreen)
    hist_m12_800.SetMarkerColor(ROOT.kCyan)

    hist_m12_350.SetMarkerSize(1.0)
    hist_m12_400.SetMarkerSize(1.0)
    hist_m12_500.SetMarkerSize(1.0)
    hist_m12_600.SetMarkerSize(1.0)
    hist_m12_700.SetMarkerSize(1.0)
    hist_m12_800.SetMarkerSize(1.0)

    # 2-D histograms for backgrounds
    hist_total_bkg = ROOT.TH2F("hist_total_bkg", "", 6, 0., 30., 10, 0., 50.)
    hist_diboson   = ROOT.TH2F("hist_diboson",   "", 6, 0., 30., 10, 0., 50.)
    hist_fakes     = ROOT.TH2F("hist_fakes",     "", 6, 0., 30., 10, 0., 50.)
    hist_other     = ROOT.TH2F("hist_other",     "", 6, 0., 30., 10, 0., 50.)
    hist_top       = ROOT.TH2F("hist_top",       "", 6, 0., 30., 10, 0., 50.)
    hist_Zttjets   = ROOT.TH2F("hist_Zttjets",   "", 6, 0., 30., 10, 0., 50.)

    get_histogram(path + files['dibosonFile'], "diboson_NoSys", hist_diboson)
    get_histogram(path + files['fakesFile'],   "fakes_NoSys",   hist_fakes)
    get_histogram(path + files['otherFile'],   "other_NoSys",   hist_other)
    get_histogram(path + files['topFile'],     "top_NoSys",     hist_top)
    get_histogram(path + files['ZttjetsFile'], "Zttjets_NoSys", hist_Zttjets)

    hist_total_bkg.Add(hist_diboson)
    hist_total_bkg.Add(hist_fakes)
    hist_total_bkg.Add(hist_other)
    hist_total_bkg.Add(hist_top)
    hist_total_bkg.Add(hist_Zttjets)

    # Making plot
    c1 = ROOT.TCanvas("c1", "", 800, 800)
    ROOT.gStyle.SetOptStat(0)
    ROOT.gPad.SetBottomMargin(0.15)
    ROOT.gPad.SetRightMargin(0.05)
    ROOT.gPad.SetLeftMargin(0.15)
    
    hist_total_bkg.SetLineColor(ROOT.kBlack)
    hist_total_bkg.SetFillColor(ROOT.kWhite)
    hist_total_bkg.SetFillStyle(0) #hollow
    hist_total_bkg.GetXaxis().SetTitle("m_{#font[12]{l}#font[12]{l}} [GeV]")
    hist_total_bkg.GetXaxis().SetTitleOffset(1.3)
    hist_total_bkg.GetXaxis().SetTitleSize(0.05)
    hist_total_bkg.GetYaxis().SetTitle("E_{T}^{miss}/H_{T}^{lep}")
    hist_total_bkg.GetYaxis().SetTitleOffset(1.3)
    hist_total_bkg.GetYaxis().SetTitleSize(0.05)
    hist_total_bkg.Draw("box")
    
    hist_m12_350.Draw("same")
    hist_m12_400.Draw("same")
    hist_m12_500.Draw("same")
    hist_m12_600.Draw("same")
    hist_m12_700.Draw("same")
    hist_m12_800.Draw("same")

    func1.Draw("same")

    # AtlasStyle.ATLASLabel(0.2, 0.83, "Internal", ROOT.kBlack)
    # AtlasStyle.myText(0.2, 0.78, "13 TeV, 36.1 fb^{-1}", ROOT.kBlack, 0.04)
    AtlasStyle.myText(0.2, 0.83, "13 TeV, 36.1 fb^{-1}", ROOT.kBlack, 0.04)

    legend_total_bkg = "Total Background"
    legend_m12_350   = "NUHM2 m_{1/2}=350 GeV #Delta m(#tilde{#chi}^{0}_{2}, #tilde{#chi}^{0}_{1})=46.06 GeV"
    legend_m12_400   = "NUHM2 m_{1/2}=400 GeV #Delta m(#tilde{#chi}^{0}_{2}, #tilde{#chi}^{0}_{1})=38.17 GeV"
    legend_m12_500   = "NUHM2 m_{1/2}=500 GeV #Delta m(#tilde{#chi}^{0}_{2}, #tilde{#chi}^{0}_{1})=28.02 GeV"
    legend_m12_600   = "NUHM2 m_{1/2}=600 GeV #Delta m(#tilde{#chi}^{0}_{2}, #tilde{#chi}^{0}_{1})=22.05 GeV"
    legend_m12_700   = "NUHM2 m_{1/2}=700 GeV #Delta m(#tilde{#chi}^{0}_{2}, #tilde{#chi}^{0}_{1})=18.19 GeV"
    legend_m12_800   = "NUHM2 m_{1/2}=800 GeV #Delta m(#tilde{#chi}^{0}_{2}, #tilde{#chi}^{0}_{1})=15.49 GeV"

    legend = ROOT.TLegend(0.54, 0.6, 0.94, 0.87)
    legend.AddEntry(hist_total_bkg, legend_total_bkg, "f")
    legend.AddEntry(hist_m12_350, legend_m12_350, "p")
    legend.AddEntry(hist_m12_400, legend_m12_400, "p")
    legend.AddEntry(hist_m12_500, legend_m12_500, "p")
    legend.AddEntry(hist_m12_600, legend_m12_600, "p")
    legend.AddEntry(hist_m12_700, legend_m12_700, "p")
    legend.AddEntry(hist_m12_800, legend_m12_800, "p")
    # legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.015);
    # legend.SetFillColor(0);
    # legend.SetFillStyle(0);
    legend.Draw()

    # output = "METOverHT_vs_mll.pdf"
    output2 = "METOverHT_vs_mll.png"

    # c1.SaveAs(output)
    c1.SaveAs(output2)

#------------------------------------------------#

if __name__ == '__main__':
    main()
