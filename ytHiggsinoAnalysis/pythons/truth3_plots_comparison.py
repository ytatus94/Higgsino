#!/usr/bin/python
import ROOT
from ROOT import kBlack,kWhite,kGray,kRed,kPink,kMagenta,kViolet,kBlue,kAzure,kCyan,kTeal,kGreen,kSpring,kYellow,kOrange,kDashed
import AtlasStyle

def main():
    # f_Higgsino = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.yushen.SM_N2N1_160_150_2LMET50.no.MET.cut.root"
    f_Higgsino_N2N1 = "../../../SimpleAnalysis/Results/20170622/user.yushen.SM_N2N1_170_150_2LMET50.root"
    # f_Higgsino_N2C1p = "../../../SimpleAnalysis/Results/20170617/user.yushen.SM_N2C1p_155_150_2LMET50.root"
    # f_Higgsino_N2C1m = "../../../SimpleAnalysis/Results/20170617/user.yushen.SM_N2C1m_155_150_2LMET50.root"
    f_Higgsino_N2C1p = "../../../SimpleAnalysis/Results/20170622/user.yushen.SM_N2C1p_170_150_2LMET50.root"
    f_Higgsino_N2C1m = "../../../SimpleAnalysis/Results/20170622/user.yushen.SM_N2C1m_170_150_2LMET50.root"
    # f_NUHM2_judita = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.judita.TestJob.root"
    # f_NUHM2_10k_unfiltered = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.pskubic.10k.TestJob.root"
    # f_NUHM2_100k_unfiltered = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.chris.100k.unfiltered.TestJob.root"
    # f_NUHM2_100k_filtered = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.chris.100k.filtered.TestJob.root"
    # f_NUHM2_100k_CC_unfiltered = "../../../SimpleAnalysis/Results/20170617/user.chris.100k.CC.unfiltered.TestJob.root"
    f_NUHM2_100k_CC_filtered = "../../../SimpleAnalysis/Results/20170622/user.chris.100k.CC.filtered.TestJob.root"
    #f_NUHM2_10k_no_x1_filtered = "../../../SimpleAnalysis/Results/20170622/user.chris.10k.CC.no.x1.filtered.TestJob.root"
    f_NUHM2_10k_n2_decay_no_jet = "../../../SimpleAnalysis/Results/20170628/user.chris.10k.n2.decay.no.jet.TestJob.root"

    # kinematic_vars = ["pt", "eta", "phi", "charge", "id"]
    kinematic_vars = ["pt", "eta", "phi"]
    electron_vars = ["Electrons_" + x for x in kinematic_vars]
    muon_vars = ["Muons_" + x for x in kinematic_vars]
    lepton_vars = ["Leptons_" + x for x in kinematic_vars]
    jet_vars = ["Jets_" + x for x in kinematic_vars]
    Bjet_vars = ["Bjets_" + x for x in kinematic_vars]

    # print electron_vars
    # print muon_vars
    # print lepton_vars
    # print jet_vars
    # print Bjet_vars

    baseline_vars = []
    for i in electron_vars, muon_vars, lepton_vars, jet_vars:
        for j in i:
            baseline_vars.append("baseline" + j)

    signal_vars = []
    for i in electron_vars, muon_vars, lepton_vars, jet_vars, Bjet_vars:
        for j in i:
            signal_vars.append("signal" + j)

    # print baseline_vars
    # print signal_vars

    # var = ["eventWeight", "Event", "gen_met", "gen_ht", "met", "channel_number", "mc_weight",
    variables = ["met", "mc_weight",
                 "nBaselineLeptons", "nSignalLeptons", "nElectrons", "nMuons", "nJets", "nJet30", "nJet25", "nBjets",
                 # "is2LChannel", "isSameSign", "channel", "dphiMin1", "mT", "mT2", "meffIncl", "HTIncl", "HT30", "HTLep12",
                 "dphiMin1", "mT", "mT2", "meffIncl", "HTIncl", "HT30", "HTLep12",
                 "METOverHT", "METOverHTLep12", "mll", "pTll", "Rll", "MTauTau"]

    for var in baseline_vars:
        # print var
        # compare_two_curves(f_NUHM2, f_Higgsino, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_judita, f_NUHM2_10k_unfiltered, f_NUHM2_100k_unfiltered, f_NUHM2_100k_filtered, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_100k_CC_unfiltered, f_NUHM2_100k_CC_filtered, var, True)
        # compare_two_curves(f_Higgsino_N2N1, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_no_x1_filtered, var, True)
        compare_stack_curves(f_Higgsino_N2N1, f_Higgsino_N2C1p, f_Higgsino_N2C1m, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_n2_decay_no_jet, var, True)

    for var in signal_vars:
        # print var
        # compare_two_curves(f_NUHM2, f_Higgsino, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_judita, f_NUHM2_10k_unfiltered, f_NUHM2_100k_unfiltered, f_NUHM2_100k_filtered, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_100k_CC_unfiltered, f_NUHM2_100k_CC_filtered, var, True)
        # compare_two_curves(f_Higgsino_N2N1, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_no_x1_filtered, var, True)
        compare_stack_curves(f_Higgsino_N2N1, f_Higgsino_N2C1p, f_Higgsino_N2C1m, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_n2_decay_no_jet, var, True)

    for var in variables:
        # print var
        # compare_two_curves(f_NUHM2, f_Higgsino, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_judita, f_NUHM2_10k_unfiltered, f_NUHM2_100k_unfiltered, f_NUHM2_100k_filtered, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_100k_CC_unfiltered, f_NUHM2_100k_CC_filtered, var, True)
        # compare_two_curves(f_Higgsino_N2N1, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_no_x1_filtered, var, True)
        compare_stack_curves(f_Higgsino_N2N1, f_Higgsino_N2C1p, f_Higgsino_N2C1m, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_n2_decay_no_jet, var, True)

#----------------------------#

# def compare_two_curves(file1, file2, var, normalize):
# def compare_two_curves(file1, file2, file3, file4, file5, var, normalize):
def compare_two_curves(file1, file2, file3, var, normalize):
    canvas = ROOT.TCanvas("c","", 800,600)
    canvas.SetLeftMargin(0.12)
    logY = False
    if var in ["HTIncl", "HT30", "HTLep12", "METOverHTLep12", "mll", "mT", "mT2", "MTauTau", "pTll", "Rll"]:
        logY = True
        ROOT.gPad.SetLogy()

    if "_pt" in var:
        nbins, xmin, xmax = 100, 0, 100
    elif "_eta" in var:
        nbins, xmin, xmax = 60, -3, 3
    elif "_phi" in var:
        nbins, xmin, xmax = 80, -4, 4
    # elif "charge" in var:
    #     nbins, xmin, xmax = 40, -2, 2
    elif "met" in var:
        nbins, xmin, xmax = 100, 0, 500
    elif "mc_weight" in var:
        nbins, xmin, xmax = 50, -0, 5
    elif "Jets_pt" in var or "Bjets_pt" in var:
        nbins, xmin, xmax = 500, 0, 500
    elif "nBaselineLeptons" in var or "nSignalLeptons" in var or "nElectrons" in var or "nMuons" in var:
        nbins, xmin, xmax = 5, 0, 5
    elif "nJets" in var or "nJet30" in var or "nJet25" in var or "nBjets" in var:
        nbins, xmin, xmax = 10, 0, 10
    elif "dphiMin1" in var:
        nbins, xmin, xmax = 50, 0, 5
    elif "mT" in var or "mT2" in var:
        nbins, xmin, xmax = 20, 0, 100
    elif "meffIncl" in var:
        nbins, xmin, xmax = 50, 0, 1000
    elif "HTIncl" in var or "HT30" in var:
        nbins, xmin, xmax = 50, 0, 500
    elif "HTLep12" in var and "METOverHTLep12" not in var:
        nbins, xmin, xmax = 10, 0, 50
    elif "METOverHT" in var and "METOverHTLep12" not in var:
        nbins, xmin, xmax = 50, 0, 5
    elif "METOverHTLep12" in var:
        nbins, xmin, xmax = 5, 0, 50
    elif "mll" in var:
        nbins, xmin, xmax = 100, 0, 50
    elif "pTll" in var:
        nbins, xmin, xmax = 50, 0, 50
    elif "Rll" in var:
        nbins, xmin, xmax = 50, 0, 5
    elif "MTauTau" in var:
        nbins, xmin, xmax = 60, -300, 300

    cut = ""
    if "HT30" in var:
        cut = "HT30>0"
    elif "HTIncl" in var:
        cut = "HTIncl>0"
    elif "HTLep12" in var and "METOverHTLep12" not in var:
        cut = "HTLep12>0"
    elif "METOverHT" in var and "METOverHTLep12" not in var:
        cut = "METOverHT>0"
    elif "meffIncl" in var:
        cut = "meffIncl>0"
    elif "Rll" in var:
        cut = "Rll>0"
    elif "dphiMin1" in var:
        cut = "dphiMin1>0"
    elif "mT" in var and "mT2" not in var:
        cut = "mT>0"
    elif "mT2" in var:
        cut = "mT2>0"
    elif "met" in var:
        cut = "met>0"
    elif "mll" in var:
        cut = "mll>0"
    elif "pTll" in var:
        cut = "pTll>0"

    f1 = ROOT.TFile(file1)
    t1 = f1.Get("EwkHiggsino2016__ntuple")
    h1 = ROOT.TH1F("h1_" + var, var, nbins, xmin, xmax)
    t1.Project("h1_" + var, var, cut)
    integral1 = h1.Integral()
    # print integral1
    if normalize is True:
        h1.Scale(1/integral1)
    h1.SetDirectory(ROOT.gROOT)

    f2 = ROOT.TFile(file2)
    t2 = f2.Get("EwkHiggsino2016__ntuple")
    h2 = ROOT.TH1F("h2_" + var, var, nbins, xmin, xmax)
    t2.Project("h2_" + var, var, cut)
    integral2 = h2.Integral()
    # print integral2
    if normalize is True:
        h2.Scale(1/integral2)
    h2.SetDirectory(ROOT.gROOT)

    f3 = ROOT.TFile(file3)
    t3 = f3.Get("EwkHiggsino2016__ntuple")
    h3 = ROOT.TH1F("h3_" + var, var, nbins, xmin, xmax)
    t3.Project("h3_" + var, var, cut)
    integral3 = h3.Integral()
    # print integral3
    if normalize is True:
        h3.Scale(1/integral3)
    h3.SetDirectory(ROOT.gROOT)

    # f4 = ROOT.TFile(file4)
    # t4 = f4.Get("EwkHiggsino2016__ntuple")
    # h4 = ROOT.TH1F("h4_" + var, var, nbins, xmin, xmax)
    # t4.Project("h4_" + var, var, cut)
    # integral4 = h4.Integral()
    # # print integral4
    # if normalize is True:
    #     h4.Scale(1/integral4)
    # h4.SetDirectory(ROOT.gROOT)

    # f5 = ROOT.TFile(file5)
    # t5 = f5.Get("EwkHiggsino2016__ntuple")
    # h5 = ROOT.TH1F("h5_" + var, var, nbins, xmin, xmax)
    # t5.Project("h5_" + var, var, cut)
    # integral5 = h5.Integral()
    # # print integral5
    # if normalize is True:
    #     h5.Scale(1/integral5)
    # h5.SetDirectory(ROOT.gROOT)

    ROOT.gROOT.cd()

    # y_maximum = max( h1.GetMaximum(), h2.GetMaximum() )
    y_max1 = max( h1.GetMaximum(), h2.GetMaximum() )
    # y_max2 = max( h3.GetMaximum(), h4.GetMaximum() )
    # y_maximum = max( y_max1, y_max2 )
    y_maximum = max( y_max1, h3.GetMaximum() )
    
    h1.SetStats(0)
    h1.SetLineColor(kOrange)
    if normalize is True:
        h1.SetYTitle("Normalized event counts")
    else:
        h1.SetYTitle("Event counts")
    h1.GetYaxis().SetTitleOffset(1.5)
    if logY is True:
        h1.SetMaximum(y_maximum * 100)
    else:
        h1.SetMaximum(y_maximum * 1.2)
    # if var is "h_mll":
    #     var_in_f1.GetXaxis().SetRangeUser(0, 300)
    h1.SetFillColor(kOrange)
    h1.Draw("hist")

    h2.SetLineColor(kBlue)
    h2.Draw("hist,same")

    h3.SetLineColor(kRed)
    h3.Draw("hist,same")

    # h4.SetLineColor(kGreen+2)
    # h4.Draw("hist,same")

    # h5.SetLineColor(kCyan)
    # h5.Draw("hist,same")

    legend = ROOT.TLegend(0.3, 0.6, 0.9, 0.8)
    # legend.AddEntry(h1, "Higgsino_160_150", "l")
    # legend.AddEntry(h2, "NUHM2_m12_600 (1k, A+A, C+A, C+C, unfiltered)", "l")
    # legend.AddEntry(h3, "NUHM2_m12_600 (10k, C+C, unfiltered)", "l")
    # legend.AddEntry(h4, "NUHM2_m12_600 (100k, A+A, C+C, unfiltered)", "l")
    # legend.AddEntry(h5, "NUHM2_m12_600 (100k, A+A, C+C, filtered)", "l")
    legend.AddEntry(h1, "Higgsino_170_150", "l")
    # legend.AddEntry(h2, "NUHM2_m12_600 (100k, C+C(+j), unfiltered)", "l")
    # legend.AddEntry(h3, "NUHM2_m12_600 (100k, C+C(+j), filtered)", "l")
    legend.AddEntry(h2, "NUHM2_m12_600 (100k, C+C(+j), filtered)", "l")
    legend.AddEntry(h3, "NUHM2_m12_600 (10k, C+C(+j), no x1, filtered)", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.03);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    AtlasStyle.ATLASLabel(0.15, 0.85, "internal", kBlack)
    if normalize is not True:
        AtlasStyle.myText(0.3, 0.85, kBlack, "36.1fb^{-1}")
    #AtlasStyle.myText(0.6, 0.4, kBlack, "#sqrt{s}=13TeV")

    output = var + ".pdf"
    canvas.SaveAs(output)

#----------------------------#

def compare_stack_curves(file1, file2, file3, file4, file5, var, normalize):
    canvas = ROOT.TCanvas("c","", 800,600)
    canvas.SetLeftMargin(0.12)
    logY = False
    if var in ["HTIncl", "HT30", "HTLep12", "METOverHTLep12", "mll", "mT", "mT2", "MTauTau", "pTll", "Rll"]:
        logY = True
        ROOT.gPad.SetLogy()

    # Set the histogram ranges
    if "_pt" in var:
        nbins, xmin, xmax = 100, 0, 100
    elif "_eta" in var:
        nbins, xmin, xmax = 60, -3, 3
    elif "_phi" in var:
        nbins, xmin, xmax = 80, -4, 4
    # elif "charge" in var:
    #     nbins, xmin, xmax = 40, -2, 2
    elif "met" in var:
        nbins, xmin, xmax = 100, 0, 500
    elif "mc_weight" in var:
        nbins, xmin, xmax = 50, -0, 5
    elif "Jets_pt" in var or "Bjets_pt" in var:
        nbins, xmin, xmax = 500, 0, 500
    elif "nBaselineLeptons" in var or "nSignalLeptons" in var or "nElectrons" in var or "nMuons" in var:
        nbins, xmin, xmax = 5, 0, 5
    elif "nJets" in var or "nJet30" in var or "nJet25" in var or "nBjets" in var:
        nbins, xmin, xmax = 10, 0, 10
    elif "dphiMin1" in var:
        nbins, xmin, xmax = 50, 0, 5
    elif "mT" in var or "mT2" in var:
        nbins, xmin, xmax = 20, 0, 100
    elif "meffIncl" in var:
        nbins, xmin, xmax = 50, 0, 1000
    elif "HTIncl" in var or "HT30" in var:
        nbins, xmin, xmax = 50, 0, 500
    elif "HTLep12" in var and "METOverHTLep12" not in var:
        nbins, xmin, xmax = 10, 0, 50
    elif "METOverHT" in var and "METOverHTLep12" not in var:
        nbins, xmin, xmax = 50, 0, 5
    elif "METOverHTLep12" in var:
        nbins, xmin, xmax = 5, 0, 50
    elif "mll" in var:
        nbins, xmin, xmax = 100, 0, 50
    elif "pTll" in var:
        nbins, xmin, xmax = 50, 0, 50
    elif "Rll" in var:
        nbins, xmin, xmax = 50, 0, 5
    elif "MTauTau" in var:
        nbins, xmin, xmax = 60, -300, 300

    # Add cuts
    # HT30, HTIncl, and mT2 have == 0
    cut = ""
    if "HT30" in var:
        cut = "HT30>0"
    elif "HTIncl" in var:
        cut = "HTIncl>0"
    # elif "HTLep12" in var and "METOverHTLep12" not in var:
    #     cut = "HTLep12>0"
    # elif "METOverHT" in var and "METOverHTLep12" not in var:
    #     cut = "METOverHT>0"
    # elif "meffIncl" in var:
    #     cut = "meffIncl>0"
    # elif "Rll" in var:
    #     cut = "Rll>0"
    # elif "dphiMin1" in var:
    #     cut = "dphiMin1>0"
    # elif "mT" in var and "mT2" not in var:
    #     cut = "mT>0"
    elif "mT2" in var:
        cut = "mT2>0"
    # elif "met" in var:
    #     cut = "met>0"
    # elif "mll" in var:
    #     cut = "mll>0"
    # elif "pTll" in var:
    #     cut = "pTll>0"
    # elif "MTauTau" in var:
    #     cut = "MTauTau!=0"

    f1 = ROOT.TFile(file1)
    t1 = f1.Get("EwkHiggsino2016__ntuple")
    h1 = ROOT.TH1F("h1_" + var, var, nbins, xmin, xmax)
    t1.Project("h1_" + var, var, cut)
    integral1 = h1.Integral()
    h1.Scale(1/integral1)
    h1.SetDirectory(ROOT.gROOT)

    f2 = ROOT.TFile(file2)
    t2 = f2.Get("EwkHiggsino2016__ntuple")
    h2 = ROOT.TH1F("h2_" + var, var, nbins, xmin, xmax)
    t2.Project("h2_" + var, var, cut)
    integral2 = h2.Integral()
    h2.Scale(1/integral2)
    h2.SetDirectory(ROOT.gROOT)

    f3 = ROOT.TFile(file3)
    t3 = f3.Get("EwkHiggsino2016__ntuple")
    h3 = ROOT.TH1F("h3_" + var, var, nbins, xmin, xmax)
    t3.Project("h3_" + var, var, cut)
    integral3 = h3.Integral()
    h3.Scale(1/integral3)
    h3.SetDirectory(ROOT.gROOT)

    f4 = ROOT.TFile(file4)
    t4 = f4.Get("EwkHiggsino2016__ntuple")
    h4 = ROOT.TH1F("h4_" + var, var, nbins, xmin, xmax)
    if "HT30" in var or "HTIncl" in var or "mT2" in var:
        t4.Project("h4_" + var, var, cut+"&&met>50")
    else:
        t4.Project("h4_" + var, var, "met>50")
    integral4 = h4.Integral()
    h4.Scale(1/integral4)
    h4.SetDirectory(ROOT.gROOT)

    f5 = ROOT.TFile(file5)
    t5 = f5.Get("EwkHiggsino2016__ntuple")
    h5 = ROOT.TH1F("h5_" + var, var, nbins, xmin, xmax)
    if "HT30" in var or "HTIncl" in var or "mT2" in var:
        t5.Project("h5_" + var, var, cut+"&&met>50")
    else:
        t5.Project("h5_" + var, var, "met>50")
    integral5 = h5.Integral()
    h5.Scale(1/integral5)
    h5.SetDirectory(ROOT.gROOT)

    ROOT.gROOT.cd()

    h1.SetLineColor(kOrange)
    h1.SetFillColor(kOrange)
    h1.SetFillStyle(1001) # Solid
    h2.SetLineColor(kOrange-3)
    h2.SetFillColor(kOrange-3)
    h2.SetFillStyle(1001) # Solid
    h3.SetLineColor(kOrange-6)
    h3.SetFillColor(kOrange-6)
    h3.SetFillStyle(1001) # Solid

    hs = ROOT.THStack()

    h1.Scale(integral1 / (integral1+integral2+integral3) )
    h2.Scale(integral2 / (integral1+integral2+integral3) )
    h3.Scale(integral3 / (integral1+integral2+integral3) )

    hs.Add(h1)
    hs.Add(h2)
    hs.Add(h3)

    hs.Draw("hist")

    y_stack = h1.GetMaximum() + h2.GetMaximum() + h3.GetMaximum()
    y_maximum = max( y_stack, h4.GetMaximum() )

    hs.GetHistogram().SetStats(0)
    hs.SetTitle(var)

    # X axis
    if "_pt" in var:
        hs.GetHistogram().SetXTitle("p_{T} [GeV]")
    elif "_eta" in var:
        hs.GetHistogram().SetXTitle("#eta")
    elif "_phi" in var:
        hs.GetHistogram().SetXTitle("#phi")
    elif "met" in var:
        hs.GetHistogram().SetXTitle("E_{T}^{miss} [GeV]")
    elif "mT" in var or "mT2" in var or \
         "meffIncl" in var or \
         "HTIncl" in var or "HT30" in var or ("HTLep12" in var and "METOverHTLep12" not in var) or \
         "mll" in var or "pTll" in var or \
         "MTauTau" in var:
        hs.GetHistogram().SetXTitle(var + " [GeV]")
    elif "dphiMin1" in var:
        hs.GetHistogram().SetXTitle("#Delta#phi(E_{T}^{miss}, j_{1})")
    elif "Rll" in var:
        hs.GetHistogram().SetXTitle("#Delta R_{ll}")
    elif "METOverHT" in var or "METOverHTLep12" in var:
        hs.GetHistogram().SetXTitle(var)
    elif "nBaselineLeptons" in var or "nSignalLeptons" in var:
        hs.GetHistogram().SetXTitle("N_{l}")
    elif "nElectrons" in var:
        hs.GetHistogram().SetXTitle("N_{e}")
    elif "nMuons" in var:
        hs.GetHistogram().SetXTitle("N_{#mu}")
    elif "nJets" in var or "nJet30" in var or "nJet25" in var or "nBjets" in var:
        hs.GetHistogram().SetXTitle("N_{jets}")

    # Y axis
    if normalize is True:
        hs.GetHistogram().SetYTitle("Normalized event counts")
    else:
        hs.GetHistogram().SetYTitle("Event counts")
    hs.GetHistogram().GetYaxis().SetTitleOffset(1.5)
    if logY is True:
        hs.SetMaximum(y_maximum * 20)
    else:
        if "_eta" in var or "_phi" in var:
            hs.SetMaximum(y_maximum * 2)
        else:
            hs.SetMaximum(y_maximum * 1.2)

    hs.Draw() # re-draw to make the y axis range setting working

    h4.SetLineColor(kBlue)
    h4.Draw("hist,same")

    h5.SetLineColor(kRed)
    h5.Draw("hist,same")

    legend = ROOT.TLegend(0.5, 0.6, 0.9, 0.8)
    legend.AddEntry(h1, "Higgsino_N2N1_170_150", "f")
    # legend.AddEntry(h2, "Higgsino_N2C1p_155_150", "f")
    # legend.AddEntry(h3, "Higgsino_N2C1m_155_150", "f")
    legend.AddEntry(h2, "Higgsino_N2C1p_170_150", "f")
    legend.AddEntry(h3, "Higgsino_N2C1m_170_150", "f")
    legend.AddEntry(h4, "NUHM2_m12_600 (100k, C+C(+j), filtered)", "l")
    legend.AddEntry(h5, "NUHM2_m12_600 (10k, n2>l+l-n1, no jet, filtered)", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.02);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    AtlasStyle.ATLASLabel(0.15, 0.85, "internal", kBlack)

    output = var + ".pdf"
    canvas.SaveAs(output)

#----------------------------#

if __name__ == '__main__':
    main()
