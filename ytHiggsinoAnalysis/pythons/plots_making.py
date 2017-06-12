#!/usr/bin/python
import ROOT
from ROOT import kBlack,kWhite,kGray,kRed,kPink,kMagenta,kViolet,kBlue,kAzure,kCyan,kTeal,kGreen,kSpring,kYellow,kOrange,kDashed
import AtlasStyle

def main():
    version = 1.6
    f_NUHM2 = "optimization_MC_MGPy8EG_A14N23LO_NUHM2_m12_600_weak_SusySkimHiggsino_v%s_SUSY16_tree_NoSys.root/hist-SusySkimHiggsino_v%s_SUSY16_Signal_tree.root" % version, version
    f_Higgsino = "optimization_MC_MGPy8EG_A14N23LO_SM_Higgsino_160_150_2LMET50_MadSpin_SusySkimHiggsino_v%s_SUSY16_tree_NoSys.root/hist-SusySkimHiggsino_v%s_SUSY16_Signal_tree.root" % version, version

    vars = ["h_NJets", "h_NJet30", "h_NJet25",
            "h_jets_pT", "h_jet1_pT", "h_jet2_pT", "h_jet3_pT", #"h_jet4_pT",
            "h_Nbjets", #"h_bJets_pT",
            "h_NLepts_baseline", "h_lepts_pT_baseline", "h_lept1_pT_baseline", "h_lept2_pT_baseline", "h_lept3_pT_baseline", "h_lept4_pT_baseline",
            "h_NLepts_signal", "h_lepts_pT_signal", "h_lept1_pT_signal", "h_lept2_pT_signal", "h_lept3_pT_signal", "h_lept4_pT_signal",
            "h_met", "h_HT", "h_METOverHT", "h_METOverHTLep12", #"h_mT2",
            "h_mll"]

    for var in vars:
        print var
        compare_two_curves(f_NUHM2, f_Higgsino, var, True)

#----------------------------#

def compare_two_curves(file1, file2, var, normalize):
    canvas = ROOT.TCanvas("c","", 800,600)
    if var not in ["h_NJets", "h_NJet30", "h_NJet25", "h_Nbjets", "h_NLepts_baseline", "h_NLepts_signal"]:
        ROOT.gPad.SetLogy()

    f1 = ROOT.TFile(file1)
    var_in_f1 = f1.Get(var)
    integral1 = var_in_f1.Integral()
    if normalize is True:
        var_in_f1.Scale(1/integral1)

    f2 = ROOT.TFile(file2)
    var_in_f2 = f2.Get(var)
    integral2 = var_in_f2.Integral()
    if normalize is True:
        var_in_f2.Scale(1/integral2)

    y_maximum = max( var_in_f1.GetMaximum(), var_in_f2.GetMaximum() )
    
    var_in_f1.SetStats(0)
    var_in_f1.SetLineColor(kBlue)
    if normalize is True:
        var_in_f1.SetYTitle("Normalized event counts")
    else:
        var_in_f1.SetYTitle("Event counts")
    var_in_f1.SetMaximum(y_maximum * 1.2)
    if var is "h_mll":
        var_in_f1.GetXaxis().SetRangeUser(0, 300)
    var_in_f1.Draw("hist")

    var_in_f2.SetLineColor(kRed)
    var_in_f2.Draw("hist,same")

    legend = ROOT.TLegend(0.6, 0.7, 0.9, 0.8)
    legend.AddEntry(var_in_f1, "NUHM2_m12_600", "l")
    legend.AddEntry(var_in_f2, "Higgsino_160_150", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.03);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    AtlasStyle.ATLASLabel(0.15, 0.85, "ATLAS internal", kBlack)
    if normalize is not True:
        AtlasStyle.myText(0.3, 0.85, kBlack, "36.1fb^{-1}")
    #AtlasStyle.myText(0.6, 0.4, kBlack, "#sqrt{s}=13TeV")

    output = var + ".pdf"
    canvas.SaveAs(output)

#----------------------------#

if __name__ == '__main__':
    main()
