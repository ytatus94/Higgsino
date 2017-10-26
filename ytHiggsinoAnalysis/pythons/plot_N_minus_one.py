#!/usr/bin/python
import ROOT
import array, math
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

def main():
    plot_N_minus_one_distribution_in_SR(600, 'METOverHTLep', True, False)
    # plot_N_minus_one_distribution_in_SR(600, 'Rll', False, True)
    # plot_N_minus_one_distribution_in_SR(600, 'mt_lep1', False, True)

#----------------------------#

def get_correct_weight(genWeight, eventWeight, leptonWeight, jvtWeight, pileupWeight, bTagWeight, FFWeight):
    Lumi = 36.09756
    return Lumi * 1000 * genWeight * eventWeight * leptonWeight * jvtWeight * pileupWeight * bTagWeight * FFWeight

#----------------------------#

def get_N_minus_one_histogram(file, tree_name, varexp, lep_EEOS, lep_MMOS):
    '''
    Loop the tree entries to get the variable values with SR cuts applied and then dump into histogram
    return the histogram.
    '''
    xtitle = ""
    ytitle = ""
    nbins, xmin, xmax = 0, 0., 0.

    h_name = "h_" + tree_name
    hist = None

    if varexp == "METOverHTLep":
        xtitle = "E^{miss}_{T}/H^{leptons}_{T}"
        ytitle = "Events / bin"
        nbins = 19
        METOverHTLep_binning = [0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15., 17., 20., 25., 30]
        METOverHTLep_binning_array = array.array("d", METOverHTLep_binning)
        hist = ROOT.TH1F(h_name, "", nbins, METOverHTLep_binning_array)
    elif varexp == "Rll":
        xtitle = "#Delta R(#font[12]{l}#font[12]{l})"
        ytitle = "Events / 0.20"
        nbins, xmin, xmax = 25, 0., 5.
        hist = ROOT.TH1F(h_name, "", nbins, xmin, xmax)
    elif varexp == "mt_lep1":
        xtitle = "m_{T}(#font[12]{l}_{1}) [GeV]"
        ytitle = "Events / 10 GeV"
        nbins, xmin, xmax = 20, 0., 200.
        hist = ROOT.TH1F(h_name, "", nbins, xmin, xmax)

    hist.GetXaxis().SetTitle(xtitle)
    hist.GetYaxis().SetTitle(ytitle)

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

        # Apply cuts
        if len(jetPt) >= 1:
            if ( # common_cuts
                 trigMatch_metTrig == 1 and
                (FS != 206 and FS != 207) and
                (nLep_signal == 2 and nLep_base == 2) and
                (mll < 3 or mll > 3.2) and
                (lep1Author != 16 and lep2Author != 16) and
                ( (lep1TruthMatched and lep2TruthMatched) or (DatasetNumber >= 407311 and DatasetNumber <= 407315) ) and
                met_Et > 200 and jetPt[0] > 100 and minDPhiAllJetsMet > 0.4 and mll > 1 and mll < 60 and lep1Pt > 5 and Rll > 0.05 and
                # common_SR
                nBJet20_MV2c10 == 0 and DPhiJ1Met > 2.0 and (MTauTau > 160 or MTauTau < 0)# and
                # select_hg
                # METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0 and mt_lep1 < 70 #and
                # Rll < 2.0 and mt_lep1 < 70
                # (lep1Charge != lep2Charge) and lep1Flavor == 1 and lep2Flavor == 1 # lep_EEOS
                # (lep1Charge != lep2Charge) and lep1Flavor == 2 and lep2Flavor == 2 # lep_MMOS
                ):

                # calculate weight for the event pass select_hg
                genWeight = event.genWeight
                eventWeight = event.eventWeight
                leptonWeight = event.leptonWeight
                jvtWeight = event.jvtWeight
                pileupWeight = event.pileupWeight
                bTagWeight = event.bTagWeight
                FFWeight = event.FFWeight
                correct_weight = get_correct_weight(genWeight, eventWeight, leptonWeight, jvtWeight, pileupWeight, bTagWeight, FFWeight)

                value = 0
                if varexp is "METOverHTLep":
                    if Rll < 2.0 and mt_lep1 < 70:
                        value = event.METOverHTLep
                elif varexp is "Rll":
                    if METOverHTLep > max(5., 15. - 2.*mll) and mt_lep1 < 70:
                        value = event.Rll
                elif varexp is "mt_lep1":
                    if METOverHTLep > max(5., 15. - 2.*mll) and Rll < 2.0:
                        value = mt_lep1

                if lep_EEOS is True:
                    if (lep1Charge != lep2Charge) and lep1Flavor == 1 and lep2Flavor == 1:
                        if "data" in tree_name:
                            hist.Fill(value)
                        else:
                            hist.Fill(value, correct_weight)
                if lep_MMOS is True:
                    if (lep1Charge != lep2Charge) and lep1Flavor == 2 and lep2Flavor == 2:
                        if eventWeight > -10: # in Zttjets, eventNumber=5637 has eventWeight=-57.46849, we have to ignore this strange point
                            if "data" in tree_name:
                                hist.Fill(value)
                            else:
                                hist.Fill(value, correct_weight)

    return hist

#----------------------------#

def plot_N_minus_one_distribution_in_SR(m12, varexp, lep_EEOS, lep_MMOS):
    # signal
    h_nuhm2 = get_N_minus_one_histogram(path + files['sigFile'], "MGPy8EG_A14N23LO_NUHM2_m12_" + str(m12) +"_weak_NoSys", varexp, lep_EEOS, lep_MMOS)
    h_nuhm2.SetLineColor(ROOT.kRed)
    h_nuhm2.SetFillColor(ROOT.kRed)
    integral_nuhm2 = h_nuhm2.Integral()

    # data
    h_data = get_N_minus_one_histogram(path + files['dataFile'], "data", varexp, lep_EEOS, lep_MMOS)
    # bkg
    h_diboson = get_N_minus_one_histogram(path + files['dibosonFile'], "diboson_NoSys", varexp, lep_EEOS, lep_MMOS)
    h_fakes   = get_N_minus_one_histogram(path + files['fakesFile'],   "fakes_NoSys",   varexp, lep_EEOS, lep_MMOS)
    h_other   = get_N_minus_one_histogram(path + files['otherFile'],   "other_NoSys",   varexp, lep_EEOS, lep_MMOS)
    h_top     = get_N_minus_one_histogram(path + files['topFile'],     "top_NoSys",     varexp, lep_EEOS, lep_MMOS)
    h_Zttjets = get_N_minus_one_histogram(path + files['ZttjetsFile'], "Zttjets_NoSys", varexp, lep_EEOS, lep_MMOS)

    h_data.SetLineColor(ROOT.kBlack)
    h_data.SetMarkerColor(ROOT.kBlack)
    h_data.SetMarkerStyle(ROOT.kFullCircle)
    h_data.SetMarkerSize(1.5)
    integral_data = h_data.Integral()

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

    # Upper plot will be in pad1
    pad1 = ROOT.TPad("pad1", "pad1", 0, 0.35, 1, 1.0)
    pad1.SetBottomMargin(0.05)
    pad1.SetRightMargin(0.05)
    pad1.SetLeftMargin(0.16)
    # pad1->SetGridy() # grid lines
    pad1.Draw()

    # lower plot will be in pad
    pad2 = ROOT.TPad("pad2", "pad2", 0, 0.05, 1, 0.35)
    pad2.SetTopMargin(0.05)
    pad2.SetBottomMargin(0.3)
    pad2.SetRightMargin(0.05)
    pad2.SetLeftMargin(0.16)
    # pad2.SetGridy() # grid lines
    pad2.Draw()

    #
    # pad1: top pad
    #
    pad1.cd() # pad1 becomes the current pad
    # pad1.SetFrameLineWidth(2)

    hstack.Draw("hist") # need to draw first, otherwise cannot GetHistogram()
    hstack.GetHistogram().SetStats(0)
    # hstack.SetMinimum(0.)
    hstack.SetMaximum(h_SM.GetMaximum() * 2.6)
    hstack.GetHistogram().SetXTitle("") # suppress Xtitle
    hstack.GetXaxis().SetLabelSize(0)
    hstack.GetHistogram().SetYTitle(h_data.GetYaxis().GetTitle())
    hstack.GetYaxis().SetLabelSize(0.04)
    hstack.GetYaxis().SetLabelOffset(0.015)
    hstack.GetYaxis().SetTitleSize(0.05)
    hstack.GetYaxis().SetTitleOffset(1.3)
    hstack.Draw("hist") # re-draw to make the changes working
 
    hstack.Draw("hist")
    h_SM.Draw("hist,same")
    h_SM_err.Draw("E2,same")
    h_data.Draw("E,same")
    h_nuhm2.Draw("hist,same")

    AtlasStyle.ATLASLabel(0.2, 0.83, "Internal", ROOT.kBlack)
    AtlasStyle.myText(0.2, 0.78, "13 TeV, 36.1 fb^{-1}", ROOT.kBlack, 0.04)
    if lep_EEOS is True:
        AtlasStyle.myText(0.2, 0.75, "SRee-iMLLg ee", ROOT.kBlack, 0.02)
    if lep_MMOS is True:
        AtlasStyle.myText(0.2, 0.75, "SRmm-iMLLg #mu#mu", ROOT.kBlack, 0.02)
    AtlasStyle.myText(0.2, 0.72, "SusySkimHiggsino v1.9b", ROOT.kGray, 0.02)

    legend_nuhm2   = "NUHM2 m12={0} ({1:.1f})".format(m12, integral_nuhm2)
    legend_data    = "Data ({0:.1f} Events)".format(integral_data)
    legend_SM      = "SM stat #oplus 20% syst ({0:.1f})".format(integral_SM)
    legend_fakes   = "Fake leptons ({0:.1f}%)".format(integral_fakes / integral_SM * 100)
    legend_top     = 't#bar{t}& Single top ' + "({0:.1f}%)".format(integral_top / integral_SM * 100)
    legend_Zttjets = "Z(#rightarrow#tau#tau)+jets ({0:.1f}%)".format(integral_Zttjets / integral_SM * 100)
    legend_diboson = "Diboson ({0:.1f}%)".format(integral_diboson / integral_SM * 100)
    legend_other   = "Others ({0:.1f}%)".format(integral_other / integral_SM * 100)

    legend = ROOT.TLegend(0.6, 0.5, 0.9, 0.87)
    legend.AddEntry(h_nuhm2, legend_nuhm2, "l")
    legend.AddEntry(h_data, legend_data, "pl")
    legend.AddEntry(h_SM_err, legend_SM, "fl")
    legend.AddEntry(h_fakes, legend_fakes, "f")
    legend.AddEntry(h_top, legend_top, "f")
    legend.AddEntry(h_Zttjets, legend_Zttjets, "f")
    legend.AddEntry(h_diboson, legend_diboson, "f")
    legend.AddEntry(h_other, legend_other, "f")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.03);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    #
    # pad2: bottom pad
    #
    pad2.cd() # pad2 becomes the current pad

    pad2_X_min = h_data.GetXaxis().GetXmin()
    pad2_X_max = h_data.GetXaxis().GetXmax()
    pad2_Y_min = 0.
    pad2_Y_max = 2.
    pad2_X_title = h_data.GetXaxis().GetTitle()
    pad2_Y_title = "Data / SM"

    frame = pad2.DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max)
    frame.GetXaxis().SetNdivisions(510)
    frame.GetYaxis().SetNdivisions(405)
    frame.SetLineWidth(1)
    frame.SetXTitle(pad2_X_title)
    frame.GetXaxis().SetTitleSize(25)
    frame.GetXaxis().SetTitleFont(47)
    frame.GetXaxis().SetTitleOffset(4.0)
    frame.GetXaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
    frame.GetXaxis().SetLabelSize(20)
    frame.GetXaxis().SetLabelOffset(0.05)
    frame.SetYTitle(pad2_Y_title)
    frame.GetYaxis().SetTitleSize(25)
    frame.GetYaxis().SetTitleFont(43)
    frame.GetYaxis().SetTitleOffset(2.0)
    frame.GetYaxis().SetLabelFont(43) # Absolute font size in pixel (precision 3)
    frame.GetYaxis().SetLabelSize(20)
    frame.GetYaxis().SetLabelOffset(0.015)
    frame.Draw()

    line = ROOT.TLine(pad2_X_min, 1., pad2_X_max, 1.)
    line.SetLineColor(ROOT.kBlack)
    line.SetLineStyle(1)
    line.SetLineWidth(1)
    line.Draw("same")

    h_data_over_SM = h_data.Clone()
    h_data_over_SM.Divide(h_SM)
    h_data_over_SM.SetLineColor(ROOT.kBlack)
    h_data_over_SM.SetMarkerColor(ROOT.kBlack)
    h_data_over_SM.SetMarkerStyle(ROOT.kFullCircle)
    h_data_over_SM.SetMarkerSize(1.5)

    bin_center = []
    for i in range(0, h_data_over_SM.GetXaxis().GetNbins()+1):
        # remove the 0 bin content points by setting the central value to -99 
        if h_data_over_SM.GetBinContent(i) == 0:
            h_data_over_SM.SetBinContent(i, -99.)
        if h_data_over_SM.GetBinContent(i) > 2:
            bin_center.append(h_data_over_SM.GetBinCenter(i))

    h_data_over_SM.Draw("E0,same")
    # Use E optoin, then no 0 bin content points are drawn but no error bars for those point > 2
    # Use E0 option, the 0 bin content points are drawn and so do error bars

    # Ximo says I have to convert to TGraphErrors and use p0 option
    # g_data_over_SM = ROOT.TGraphErrors(h_data_over_SM)
    # remove the 0 bin content points manually
    # for p in range(0, g_data_over_SM.GetN()):
    #     x, y = ROOT.Double(-9.), ROOT.Double(-9.)
    #     g_data_over_SM.GetPoint(p, x, y)
    #     print p, x, y
    #     if y == 0:
    #         g_data_over_SM.RemovePoint(p)
    # g_data_over_SM.Draw("p0")

    # Add a small arrow for those bins with central value > 2
    arrow_list = []
    for x in bin_center:
        arrow = ROOT.TArrow(x, 1.7, x, 1.95, 0.01, "|>")
        # arrow.SetArrowSize(0.02)
        arrow.SetLineColor(ROOT.kOrange+1)
        arrow.SetLineWidth(3)
        arrow.SetFillColor(ROOT.kOrange+1)
        arrow.SetFillStyle(1001)
        # If draw arrow at here, then only the last arrow is drawn.
        # So put arrow object into a list and draw them later.
        arrow_list.append(arrow)
    for arrow in arrow_list:
        arrow.Draw()

    h_SM_over_SM = h_SM.Clone()
    h_SM_over_SM.Divide(h_SM)
    h_SM_over_SM.SetLineColor(ROOT.kGray+3)
    h_SM_over_SM.SetFillColor(ROOT.kGray+3)
    h_SM_over_SM.SetMarkerColor(ROOT.kGray+3)
    h_SM_over_SM.SetFillStyle(3004)
    h_SM_over_SM.Draw("E2,same")

    output = "NUHM2_m12_" + str(m12) + "_and_Bkg_"
    if varexp == 'mt_lep1+mt_lep2':
        output += "mt_lep1_plus_mt_lep2"
    else:
        output += varexp
    if lep_EEOS is True:
        output += "_EEOS"
    if lep_MMOS is True:
        output += "_MMOS"
    output += "_N_minus_one_distribution_in_SR.pdf"

    c1.SaveAs(output)

#----------------------------#

if __name__ == '__main__':
    main()
