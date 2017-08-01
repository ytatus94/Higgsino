#!/usr/bin/python
import ROOT
from ROOT import kBlack,kWhite,kGray,kRed,kPink,kMagenta,kViolet,kBlue,kAzure,kCyan,kTeal,kGreen,kSpring,kYellow,kOrange,kDashed
import AtlasStyle
import read_Xsec

# Global variables
xsec_higgsino_N2N1 = read_Xsec.get_XS_Higgsino(read_Xsec.get_line_Higgsino("N2N1_170_150"))
xsec_higgsino_C1C1 = read_Xsec.get_XS_Higgsino(read_Xsec.get_line_Higgsino("C1C1_170_150"))
xsec_higgsino_N2C1p = read_Xsec.get_XS_Higgsino(read_Xsec.get_line_Higgsino("N2C1p_170_150"))
xsec_higgsino_N2C1m = read_Xsec.get_XS_Higgsino(read_Xsec.get_line_Higgsino("N2C1m_170_150"))

# BF_higgsino_N2N1 = get_BF_Higgsino(get_line_Higgsino("N2N1_170_150"))
# BF_higgsino_C1C1 = get_BF_Higgsino(get_line_Higgsino("C1C1_170_150"))
# BF_higgsino_N2C1p = get_BF_Higgsino(get_line_Higgsino("N2C1p_170_150"))
# BF_higgsino_N2C1m = get_BF_Higgsino(get_line_Higgsino("N2C1m_170_150"))
BF_n2_lln1 = 0.9
BF_c1_ffn1 = 9.42923324e-02

eff_higgsino_N2N1 = read_Xsec.get_FilterEff_Higgsino(read_Xsec.get_line_Higgsino("N2N1_170_150"))
eff_higgsino_C1C1 = read_Xsec.get_FilterEff_Higgsino(read_Xsec.get_line_Higgsino("C1C1_170_150"))
eff_higgsino_N2C1p = read_Xsec.get_FilterEff_Higgsino(read_Xsec.get_line_Higgsino("N2C1p_170_150"))
eff_higgsino_N2C1m = read_Xsec.get_FilterEff_Higgsino(read_Xsec.get_line_Higgsino("N2C1m_170_150"))

events_higgsino_N2N1 = 10000
events_higgsino_C1C1 = 10000
events_higgsino_N2C1p = 10000
events_higgsino_N2C1m = 10000

xsec_nuhm2_N2N1 = read_Xsec.get_XS_NUHM2(370621, 112)
xsec_nuhm2_C1C1 = read_Xsec.get_XS_NUHM2(370621, 157)
xsec_nuhm2_N2C1p = read_Xsec.get_XS_NUHM2(370621, 125)
xsec_nuhm2_N2C1m = read_Xsec.get_XS_NUHM2(370621, 127)

# BF_nuhm2_N2N1 =
# BF_nuhm2_C1C1 =
# BF_nuhm2_N2C1p =
# BF_nuhm2_N2C1m =
BF_n2_lln1 = 3.67224030E-02 + 3.67224030E-02 + 3.35381366E-02
BF_c1_ffn1 = 1.

# read from log.generate
eff_nuhm2_N2N1 = 0.165175
eff_nuhm2_C1C1 = 0.107170
eff_nuhm2_N2C1p = 0.175818
eff_nuhm2_N2C1m = 0.175864

events_nuhm2_N2N1 = 10000
events_nuhm2_C1C1 = 10000
events_nuhm2_N2C1p = 10000
events_nuhm2_N2C1m = 10000

def main():
    # f_Higgsino = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.yushen.SM_N2N1_160_150_2LMET50.no.MET.cut.root"
    # f_Higgsino_N2N1 = "../../../SimpleAnalysis/Results/20170622/user.yushen.SM_N2N1_170_150_2LMET50.root"
    # f_Higgsino_N2C1p = "../../../SimpleAnalysis/Results/20170617/user.yushen.SM_N2C1p_155_150_2LMET50.root"
    # f_Higgsino_N2C1m = "../../../SimpleAnalysis/Results/20170617/user.yushen.SM_N2C1m_155_150_2LMET50.root"
    # f_Higgsino_N2C1p = "../../../SimpleAnalysis/Results/20170622/user.yushen.SM_N2C1p_170_150_2LMET50.root"
    # f_Higgsino_N2C1m = "../../../SimpleAnalysis/Results/20170622/user.yushen.SM_N2C1m_170_150_2LMET50.root"
    # f_NUHM2_judita = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.judita.TestJob.root"
    # f_NUHM2_10k_unfiltered = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.pskubic.10k.TestJob.root"
    # f_NUHM2_100k_unfiltered = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.chris.100k.unfiltered.TestJob.root"
    # f_NUHM2_100k_filtered = "../../../SimpleAnalysis/Results/20170615_MET150Cut/user.chris.100k.filtered.TestJob.root"
    # f_NUHM2_100k_CC_unfiltered = "../../../SimpleAnalysis/Results/20170617/user.chris.100k.CC.unfiltered.TestJob.root"
    # f_NUHM2_100k_CC_filtered = "../../../SimpleAnalysis/Results/20170622/user.chris.100k.CC.filtered.TestJob.root"
    #f_NUHM2_10k_no_x1_filtered = "../../../SimpleAnalysis/Results/20170622/user.chris.10k.CC.no.x1.filtered.TestJob.root"
    # f_NUHM2_10k_n2_decay_no_jet = "../../../SimpleAnalysis/Results/20170628/user.chris.10k.n2.decay.no.jet.TestJob.root"

    # Higgsino simplified model
    f_Higgsino_N2N1 = "../../../SimpleAnalysis/Results/20170716/user.yushen.SM_N2N1_170_150_2LMET50.root"
    f_Higgsino_C1C1 = "../../../SimpleAnalysis/Results/20170716/user.yushen.SM_C1C1_170_150_2LMET50.root"
    f_Higgsino_N2C1p = "../../../SimpleAnalysis/Results/20170716/user.yushen.SM_N2C1p_170_150_2LMET50.root"
    f_Higgsino_N2C1m = "../../../SimpleAnalysis/Results/20170716/user.yushen.SM_N2C1m_170_150_2LMET50.root"
    # NUHM2
    f_NUHM2_N2N1 = "../../../SimpleAnalysis/Results/20170716/user.yushen.run_24.TestJob.root"
    f_NUHM2_C1C1 = "../../../SimpleAnalysis/Results/20170716/user.yushen.run_25.TestJob.root"
    f_NUHM2_N2C1p = "../../../SimpleAnalysis/Results/20170716/user.yushen.run_26.TestJob.root"
    f_NUHM2_N2C1m = "../../../SimpleAnalysis/Results/20170716/user.yushen.run_27.TestJob.root"

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
        # compare_stack_curves(f_Higgsino_N2N1, f_Higgsino_N2C1p, f_Higgsino_N2C1m, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_n2_decay_no_jet, var, True)
        compare_stack_curves(f_Higgsino_N2N1, f_Higgsino_C1C1, f_Higgsino_N2C1p, f_Higgsino_N2C1m,
                             f_NUHM2_N2N1, f_NUHM2_C1C1, f_NUHM2_N2C1p, f_NUHM2_N2C1m,
                             var, True)



    for var in signal_vars:
        # print var
        # compare_two_curves(f_NUHM2, f_Higgsino, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_judita, f_NUHM2_10k_unfiltered, f_NUHM2_100k_unfiltered, f_NUHM2_100k_filtered, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_100k_CC_unfiltered, f_NUHM2_100k_CC_filtered, var, True)
        # compare_two_curves(f_Higgsino_N2N1, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_no_x1_filtered, var, True)
        # compare_stack_curves(f_Higgsino_N2N1, f_Higgsino_N2C1p, f_Higgsino_N2C1m, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_n2_decay_no_jet, var, True)
        compare_stack_curves(f_Higgsino_N2N1, f_Higgsino_C1C1, f_Higgsino_N2C1p, f_Higgsino_N2C1m,
                             f_NUHM2_N2N1, f_NUHM2_C1C1, f_NUHM2_N2C1p, f_NUHM2_N2C1m,
                             var, True)

    for var in variables:
        # print var
        # compare_two_curves(f_NUHM2, f_Higgsino, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_judita, f_NUHM2_10k_unfiltered, f_NUHM2_100k_unfiltered, f_NUHM2_100k_filtered, var, True)
        # compare_two_curves(f_Higgsino, f_NUHM2_100k_CC_unfiltered, f_NUHM2_100k_CC_filtered, var, True)
        # compare_two_curves(f_Higgsino_N2N1, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_no_x1_filtered, var, True)
        # compare_stack_curves(f_Higgsino_N2N1, f_Higgsino_N2C1p, f_Higgsino_N2C1m, f_NUHM2_100k_CC_filtered, f_NUHM2_10k_n2_decay_no_jet, var, True)
        compare_stack_curves(f_Higgsino_N2N1, f_Higgsino_C1C1, f_Higgsino_N2C1p, f_Higgsino_N2C1m,
                             f_NUHM2_N2N1, f_NUHM2_C1C1, f_NUHM2_N2C1p, f_NUHM2_N2C1m,
                             var, True)

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
        nbins, xmin, xmax = 6, 0, 6
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

# def compare_stack_curves(file1, file2, file3, file4, file5, var, normalize):
def compare_stack_curves(file1, file2, file3, file4, file5, file6, file7, file8, var, normalize):
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
        nbins, xmin, xmax = 6, 0, 6
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
    t4.Project("h4_" + var, var, cut)
    integral4 = h4.Integral()
    h4.Scale(1/integral4)
    h4.SetDirectory(ROOT.gROOT)

    # f4 = ROOT.TFile(file4)
    # t4 = f4.Get("EwkHiggsino2016__ntuple")
    # h4 = ROOT.TH1F("h4_" + var, var, nbins, xmin, xmax)
    # if "HT30" in var or "HTIncl" in var or "mT2" in var:
    #     t4.Project("h4_" + var, var, cut+"&&met>50")
    # else:
    #     t4.Project("h4_" + var, var, "met>50")
    # integral4 = h4.Integral()
    # h4.Scale(1/integral4)
    # h4.SetDirectory(ROOT.gROOT)

    # f5 = ROOT.TFile(file5)
    # t5 = f5.Get("EwkHiggsino2016__ntuple")
    # h5 = ROOT.TH1F("h5_" + var, var, nbins, xmin, xmax)
    # if "HT30" in var or "HTIncl" in var or "mT2" in var:
    #     t5.Project("h5_" + var, var, cut+"&&met>50")
    # else:
    #     t5.Project("h5_" + var, var, "met>50")
    # integral5 = h5.Integral()
    # h5.Scale(1/integral5)
    # h5.SetDirectory(ROOT.gROOT)

    f5 = ROOT.TFile(file5)
    t5 = f5.Get("EwkHiggsino2016__ntuple")
    h5 = ROOT.TH1F("h5_" + var, var, nbins, xmin, xmax)
    t5.Project("h5_" + var, var, cut)
    integral5 = h5.Integral()
    h5.Scale(1/integral5)
    h5.SetDirectory(ROOT.gROOT)

    f6 = ROOT.TFile(file6)
    t6 = f6.Get("EwkHiggsino2016__ntuple")
    h6 = ROOT.TH1F("h6_" + var, var, nbins, xmin, xmax)
    t6.Project("h6_" + var, var, cut)
    integral6 = h6.Integral()
    h6.Scale(1/integral6)
    h6.SetDirectory(ROOT.gROOT)

    f7 = ROOT.TFile(file7)
    t7 = f7.Get("EwkHiggsino2016__ntuple")
    h7 = ROOT.TH1F("h7_" + var, var, nbins, xmin, xmax)
    t7.Project("h7_" + var, var, cut)
    integral7 = h7.Integral()
    h7.Scale(1/integral7)
    h7.SetDirectory(ROOT.gROOT)

    f8 = ROOT.TFile(file8)
    t8 = f8.Get("EwkHiggsino2016__ntuple")
    h8 = ROOT.TH1F("h8_" + var, var, nbins, xmin, xmax)
    t8.Project("h8_" + var, var, cut)
    integral8 = h8.Integral()
    h8.Scale(1/integral8)
    h8.SetDirectory(ROOT.gROOT)

    ROOT.gROOT.cd()

    h1.SetLineColor(kOrange)
    h1.SetFillColor(kOrange)
    h1.SetFillStyle(1001) # Solid
    h2.SetLineColor(kOrange-4)
    h2.SetFillColor(kOrange-4)
    h2.SetFillStyle(1001) # Solid
    h3.SetLineColor(kOrange-6)
    h3.SetFillColor(kOrange-6)
    h3.SetFillStyle(1001) # Solid
    h4.SetLineColor(kOrange-8)
    h4.SetFillColor(kOrange-8)
    h4.SetFillStyle(1001) # Solid

    h5.SetLineColor(kBlue)
    h5.SetFillColor(kBlue)
    h5.SetFillStyle(0)
    h6.SetLineColor(kMagenta)
    h6.SetFillColor(kMagenta)
    h6.SetFillStyle(0)
    h7.SetLineColor(kRed)
    h7.SetFillColor(kRed)
    h7.SetFillStyle(0)
    h8.SetLineColor(kGreen)
    h8.SetFillColor(kGreen)
    h8.SetFillStyle(0)

    hs = ROOT.THStack()

    if normalize:
        h1.Scale(integral1 / (integral1+integral2+integral3+integral4) )
        h2.Scale(integral2 / (integral1+integral2+integral3+integral4) )
        h3.Scale(integral3 / (integral1+integral2+integral3+integral4) )
        h4.Scale(integral4 / (integral1+integral2+integral3+integral4) )
    else:
        h1.Scale(weight(xsec_higgsino_N2N1, 1., eff_higgsino_N2N1, BF_n2_lln1, 36.1*1000., events_higgsino_N2N1))
        h2.Scale(weight(xsec_higgsino_C1C1, 1., eff_higgsino_C1C1, BF_c1_ffn1 * BF_c1_ffn1, 36.1*1000., events_higgsino_C1C1))
        h3.Scale(weight(xsec_higgsino_N2C1p, 1., eff_higgsino_N2C1p, BF_n2_lln1 * BF_c1_ffn1, 36.1*1000., events_higgsino_N2C1p))
        h4.Scale(weight(xsec_higgsino_N2C1m, 1., eff_higgsino_N2C1m, BF_n2_lln1 * BF_c1_ffn1, 36.1*1000., events_higgsino_N2C1m))

    hs.Add(h1)
    hs.Add(h2)
    hs.Add(h3)
    hs.Add(h4)

    hs.Draw("hist")

    hs_nuhm2 = ROOT.THStack()

    if normalize:
        h5.Scale(integral5 / (integral5+integral6+integral7+integral8) )
        h6.Scale(integral6 / (integral5+integral6+integral7+integral8) )
        h7.Scale(integral7 / (integral5+integral6+integral7+integral8) )
        h8.Scale(integral8 / (integral5+integral6+integral7+integral8) )
    else:
        h5.Scale(weight(xsec_nuhm2_N2N1, 1., eff_nuhm2_N2N1, BF_n2_lln1, 36.1*1000., events_nuhm2_N2N1))
        h6.Scale(weight(xsec_nuhm2_C1C1, 1., eff_nuhm2_C1C1, BF_c1_ffn1 * BF_c1_ffn1, 36.1*1000., events_nuhm2_C1C1))
        h7.Scale(weight(xsec_nuhm2_N2C1p, 1., eff_nuhm2_N2C1p, BF_n2_lln1 * BF_c1_ffn1, 36.1*1000., events_nuhm2_N2C1p))
        h8.Scale(weight(xsec_nuhm2_N2C1m, 1., eff_nuhm2_N2C1m, BF_n2_lln1 * BF_c1_ffn1, 36.1*1000., events_nuhm2_N2C1m))

    hs_nuhm2.Add(h5)
    hs_nuhm2.Add(h6)
    hs_nuhm2.Add(h7)
    hs_nuhm2.Add(h8)

    y_higgsino = h1.GetMaximum() + h2.GetMaximum() + h3.GetMaximum() + h4.GetMaximum()
    y_nuhm2 = h5.GetMaximum() + h6.GetMaximum() + h7.GetMaximum() + h8.GetMaximum()
    y_maximum = max( y_higgsino, y_nuhm2 )

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

    hs_nuhm2.Draw("hist,same,noclear")

    # h4.SetLineColor(kBlue)
    # h4.Draw("hist,same")

    # h5.SetLineColor(kRed)
    # h5.Draw("hist,same")

    legend = ROOT.TLegend(0.5, 0.6, 0.9, 0.8)
    # legend.AddEntry(h1, "Higgsino_N2N1_170_150", "f")
    # legend.AddEntry(h2, "Higgsino_N2C1p_155_150", "f")
    # legend.AddEntry(h3, "Higgsino_N2C1m_155_150", "f")
    # legend.AddEntry(h2, "Higgsino_N2C1p_170_150", "f")
    # legend.AddEntry(h3, "Higgsino_N2C1m_170_150", "f")
    # legend.AddEntry(h4, "NUHM2_m12_600 (100k, C+C(+j), filtered)", "l")
    # legend.AddEntry(h5, "NUHM2_m12_600 (10k, n2>l+l-n1, no jet, filtered)", "l")
    legend.AddEntry(h1, "Higgsino_N2N1_170_150", "f")
    legend.AddEntry(h2, "Higgsino_C1C1_170_150", "f")
    legend.AddEntry(h3, "Higgsino_N2C1p_170_150", "f")
    legend.AddEntry(h4, "Higgsino_N2C1m_170_150", "f")
    legend.AddEntry(h5, "NUHM2_N2N1", "l")
    legend.AddEntry(h6, "NUHM2_C1C1", "l")
    legend.AddEntry(h7, "NUHM2_N2C1p", "l")
    legend.AddEntry(h8, "NUHM2_N2C1m", "l")

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

def weight(xsec, kfactor, filterEff, BR, lumi, entries):
    return xsec * kfactor * filterEff * BR * lumi * 1000 / entries

#----------------------------#

if __name__ == '__main__':
    main()
