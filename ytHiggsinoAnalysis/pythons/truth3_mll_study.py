#!/usr/bin/python

import ROOT
import AtlasStyle

def main():
    # mll_components()
    # mll_C1_test()
    # mll_no_Hadronic_Tau()
    mll_shape()

#----------------------------#

def mll_components():
    ''' show the mll components '''
    f1 = ROOT.TFile("/afs/cern.ch/work/y/yushen/private/Higgsino/SimpleAnalysis/Results/20170619/user.chris.100k.CC.filtered.TestJob.root")
    t1 = f1.Get("EwkHiggsino2016__ntuple")

    h1 = ROOT.TH1F("h1", "mll", 100, 0, 50)
    h2 = ROOT.TH1F("h2", "mll is2LChannel", 100, 0, 50)
    h3 = ROOT.TH1F("h3", "mll !is2LChannel", 100, 0, 50)
    h4 = ROOT.TH1F("h4", "mll isSameSign", 100, 0, 50)
    h5 = ROOT.TH1F("h5", "mll !isSameSign", 100, 0, 50)
    h6 = ROOT.TH1F("h6", "mll is2LChannel&&isSameSign", 100, 0, 50)
    h7 = ROOT.TH1F("h7", "mll is2LChannel&&!isSameSign", 100, 0, 50)
    h8 = ROOT.TH1F("h8", "mll !is2LChannel&&isSameSign", 100, 0, 50)
    h9 = ROOT.TH1F("h9", "mll !is2LChannel&&!isSameSign", 100, 0, 50)
    
    t1.Project("h1", "mll", "mll>0")
    t1.Project("h2", "mll", "mll>0&&is2LChannel")
    t1.Project("h3", "mll", "mll>0&&!is2LChannel")
    t1.Project("h4", "mll", "mll>0&&isSameSign")
    t1.Project("h5", "mll", "mll>0&&!isSameSign")
    t1.Project("h6", "mll", "mll>0&&is2LChannel&&isSameSign")
    t1.Project("h7", "mll", "mll>0&&is2LChannel&&!isSameSign")
    t1.Project("h8", "mll", "mll>0&&!is2LChannel&&isSameSign")
    t1.Project("h9", "mll", "mll>0&&!is2LChannel&&!isSameSign")

    h1.SetLineColor(ROOT.kBlack)
    h2.SetLineColor(ROOT.kRed)
    h3.SetLineColor(ROOT.kGreen)
    h3.SetFillColor(ROOT.kGreen)
    h3.SetFillStyle(1001) # solid
    h4.SetLineColor(ROOT.kBlue)
    h4.SetFillColor(ROOT.kBlue)
    h4.SetFillStyle(0) # hollow
    h5.SetLineColor(ROOT.kYellow)
    h6.SetLineColor(ROOT.kMagenta)
    h6.SetFillColor(ROOT.kMagenta)
    h6.SetFillStyle(1001) # solid
    h7.SetLineColor(ROOT.kCyan)
    h8.SetLineColor(ROOT.kOrange)
    h8.SetFillColor(ROOT.kYellow)
    h8.SetFillStyle(1001) # solid
    h9.SetLineColor(ROOT.kAzure)
    h9.SetFillColor(ROOT.kAzure)
    h9.SetFillStyle(0)

    c1 = ROOT.TCanvas("c1", "c1", 800, 800)
    ROOT.gPad.SetLogy()

    h1.GetXaxis().SetRangeUser(0, 50)
    h1.SetStats(0) # no stats box
    h1.SetXTitle("M_{ll} [GeV]")
    h1.Draw()
    h2.Draw("same")
    h3.Draw("same")
    h4.Draw("same")
    h5.Draw("same")
    h6.Draw("same")
    h7.Draw("same")
    h8.Draw("same")
    h9.Draw("same")

    legend = ROOT.TLegend(0.5, 0.6, 0.9, 0.8)
    legend.AddEntry(h1, "All", "l")
    legend.AddEntry(h2, "is2L", "l")
    legend.AddEntry(h3, "!is2L", "l")
    legend.AddEntry(h4, "isSS", "l")
    legend.AddEntry(h5, "!is2L", "l")
    legend.AddEntry(h6, "is2L && isSS", "l")
    legend.AddEntry(h7, "is2L && !isSS", "l")
    legend.AddEntry(h8, "!is2L && isSS", "l")
    legend.AddEntry(h9, "!is2L && !isSS", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.02);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    AtlasStyle.ATLASLabel(0.15, 0.85, "internal", ROOT.kBlack)

    c1.SaveAs("mll_components.pdf")

#----------------------------#

def mll_C1_test():
    path = "/afs/cern.ch/work/y/yushen/private/Higgsino/SimpleAnalysis/Results/"
    f_original = path + "20170619/user.chris.100k.CC.filtered.TestJob.root"
    f_C1_at_middle = path + "20170620/user.chris.C1.middle.TestJob.root"
    f_no_C1 = path + "20170619/user.chris.10k.CC.no.x1.filtered.TestJob.root"

    f1 = ROOT.TFile(f_original)
    f2 = ROOT.TFile(f_C1_at_middle)
    f3 = ROOT.TFile(f_no_C1)

    t1 = f1.Get("EwkHiggsino2016__ntuple")
    h1 = ROOT.TH1F("h1", "mll", 100, 0, 50)
    t1.Project("h1", "mll", "mll>0")
    h1.SetDirectory(ROOT.gROOT)

    t2 = f2.Get("EwkHiggsino2016__ntuple")
    h2 = ROOT.TH1F("h2", "mll", 100, 0, 50)
    t2.Project("h2", "mll", "mll>0")
    h2.SetDirectory(ROOT.gROOT)

    t3 = f3.Get("EwkHiggsino2016__ntuple")
    h3 = ROOT.TH1F("h3", "mll", 100, 0, 50)
    t3.Project("h3", "mll", "mll>0")
    h3.SetDirectory(ROOT.gROOT)

    h1.Scale(1/h1.Integral())
    h2.Scale(1/h2.Integral())
    h3.Scale(1/h3.Integral())

    h1.SetLineColor(ROOT.kBlack)
    h2.SetLineColor(ROOT.kRed)
    h3.SetLineColor(ROOT.kBlue)

    c1 = ROOT.TCanvas("c1", "c1", 800, 800)
    ROOT.gPad.SetLogy()

    h1.SetStats(0) # no stats box
    h1.SetXTitle("M_{ll} [GeV]")
    h1.SetMaximum(h1.GetMaximum() * 20)
    h1.Draw()
    h2.Draw("same")
    h3.Draw("same")

    legend = ROOT.TLegend(0.5, 0.6, 0.9, 0.8)
    legend.AddEntry(h1, "NUHM2, 100k, Original", "l")
    legend.AddEntry(h2, "NUHM2, 10k, C1 at middle", "l")
    legend.AddEntry(h3, "NUHM2, 10k, No C1", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.02);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    AtlasStyle.ATLASLabel(0.15, 0.85, "internal", ROOT.kBlack)

    c1.SaveAs("mll_C1_test.pdf")

#----------------------------#

def mll_no_Hadronic_Tau():
    path = "/afs/cern.ch/work/y/yushen/private/Higgsino/SimpleAnalysis/Results/"

    f_Higgsino_N1N2 = path + "20170619/user.yushen.SM_N2N1_170_150_2LMET50.root"
    f_Higgsino_N2C1p = path + "20170619/user.yushen.SM_N2C1p_170_150_2LMET50.root"
    f_Higgsino_N2C1m = path + "20170619/user.yushen.SM_N2C1p_170_150_2LMET50.root"
    f_NUHM2_no_HadTau = path + "20170621/user.chris.10k.no.HadTau.TestJob.root"
    f_NUHM2_no_HadTau_simplified = path + "20170621/user.chris.10k.simplified.no.HadTau.TestJob.root"

    f1 = ROOT.TFile(f_Higgsino_N1N2)
    t1 = f1.Get("EwkHiggsino2016__ntuple")
    h1 = ROOT.TH1F("h1", "mll", 100, 0, 50)
    t1.Project("h1", "mll", "mll>0")
    integral1 = h1.Integral()
    h1.Scale(1/integral1)
    h1.SetDirectory(ROOT.gROOT)

    f2 = ROOT.TFile(f_Higgsino_N2C1p)
    t2 = f2.Get("EwkHiggsino2016__ntuple")
    h2 = ROOT.TH1F("h2", "mll", 100, 0, 50)
    t2.Project("h2", "mll", "mll>0")
    integral2 = h2.Integral()
    h2.Scale(1/integral2)
    h2.SetDirectory(ROOT.gROOT)

    f3 = ROOT.TFile(f_Higgsino_N2C1m)
    t3 = f3.Get("EwkHiggsino2016__ntuple")
    h3 = ROOT.TH1F("h3", "mll", 100, 0, 50)
    t3.Project("h3", "mll", "mll>0")
    integral3 = h3.Integral()
    h3.Scale(1/integral3)
    h3.SetDirectory(ROOT.gROOT)

    f4 = ROOT.TFile(f_NUHM2_no_HadTau)
    t4 = f4.Get("EwkHiggsino2016__ntuple")
    h4 = ROOT.TH1F("h4", "mll", 100, 0, 50)
    t4.Project("h4", "mll", "mll>0")
    integral4 = h4.Integral()
    h4.Scale(1/integral4)
    h4.SetDirectory(ROOT.gROOT)

    f5 = ROOT.TFile(f_NUHM2_no_HadTau_simplified)
    t5 = f5.Get("EwkHiggsino2016__ntuple")
    h5 = ROOT.TH1F("h5", "mll", 100, 0, 50)
    t5.Project("h5", "mll", "mll>0")
    integral5 = h5.Integral()
    h5.Scale(1/integral5)
    h5.SetDirectory(ROOT.gROOT)

    ROOT.gROOT.cd()

    h1.SetLineColor(ROOT.kOrange)
    h1.SetFillColor(ROOT.kOrange)
    h1.SetFillStyle(1001) # Solid
    h2.SetLineColor(ROOT.kOrange-3)
    h2.SetFillColor(ROOT.kOrange-3)
    h2.SetFillStyle(1001) # Solid
    h3.SetLineColor(ROOT.kOrange-6)
    h3.SetFillColor(ROOT.kOrange-6)
    h3.SetFillStyle(1001) # Solid

    hs = ROOT.THStack()

    h1.Scale(integral1 / (integral1+integral2+integral3) )
    h2.Scale(integral2 / (integral1+integral2+integral3) )
    h3.Scale(integral3 / (integral1+integral2+integral3) )

    hs.Add(h1)
    hs.Add(h2)
    hs.Add(h3)

    canvas = ROOT.TCanvas("c","", 800,600)
    canvas.SetLeftMargin(0.12)
    ROOT.gPad.SetLogy()

    hs.Draw("hist")

    y_stack = h1.GetMaximum() + h2.GetMaximum() + h3.GetMaximum()
    y_maximum = max( y_stack, h4.GetMaximum() )

    hs.GetHistogram().SetStats(0)
    hs.SetTitle("M_{ll}")
    hs.GetHistogram().SetXTitle("M_{ll} [GeV]")
    hs.GetHistogram().SetYTitle("Normalized event counts")
    hs.SetMaximum(y_maximum * 2)
    
    hs.Draw() # re-draw to make the y axis range setting working

    h4.SetLineColor(ROOT.kBlue)
    h4.Draw("hist,same")

    h5.SetLineColor(ROOT.kRed)
    h5.Draw("hist,same")
    
    legend = ROOT.TLegend(0.5, 0.6, 0.9, 0.8)
    legend.AddEntry(h1, "Higgsino_N2N1_170_150", "f")
    legend.AddEntry(h2, "Higgsino_N2C1p_170_150", "f")
    legend.AddEntry(h3, "Higgsino_N2C1m_170_150", "f")
    legend.AddEntry(h4, "NUHM2_m12_600 no hadronic Tau", "l")
    legend.AddEntry(h5, "NUHM2_m12_600 no hadronic Tau, simplified", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.02);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    AtlasStyle.ATLASLabel(0.15, 0.85, "internal", ROOT.kBlack)

    canvas.SaveAs("mll_no_Hadronic_Tau.pdf")

#----------------------------#

def mll_shape():
    f_Higgsino_N2N1 = "../../../SimpleAnalysis/Results/20170627/user.yushen.SM_N2N1_170_150_2LMET50.root"
    f_Higgsino_N2C1p = "../../../SimpleAnalysis/Results/20170627/user.yushen.SM_N2C1p_170_150_2LMET50.root"
    f_Higgsino_N2C1m = "../../../SimpleAnalysis/Results/20170627/user.yushen.SM_N2C1m_170_150_2LMET50.root"
    f_NUHM2_100k_CC_filtered = "../../../SimpleAnalysis/Results/20170627/user.chris.100k.CC.filtered.TestJob.root"
    f_NUHM2_10k_n2_decay_filtered = "../../../SimpleAnalysis/Results/20170627/user.chris.10k.n2.decay.TestJob.root"

    file1 = f_Higgsino_N2N1
    file2 = f_Higgsino_N2C1p
    file3 = f_Higgsino_N2C1m
    file4 = f_NUHM2_100k_CC_filtered
    file5 = f_NUHM2_10k_n2_decay_filtered

    canvas = ROOT.TCanvas("c","", 800,600)
    canvas.SetLeftMargin(0.12)
    ROOT.gPad.SetLogy()

    var = "mll"
    nbins, xmin, xmax = 100, 0, 50
    cut = "mll>0"
    normalize = True

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

    f4 = ROOT.TFile(file4)
    t4 = f4.Get("EwkHiggsino2016__ntuple")
    h4 = ROOT.TH1F("h4_" + var, var, nbins, xmin, xmax)
    t4.Project("h4_" + var, var, cut)
    integral4 = h4.Integral()
    # print integral4
    if normalize is True:
        h4.Scale(1/integral4)
    h4.SetDirectory(ROOT.gROOT)

    f5 = ROOT.TFile(file5)
    t5 = f5.Get("EwkHiggsino2016__ntuple")
    h5 = ROOT.TH1F("h5_" + var, var, nbins, xmin, xmax)
    t5.Project("h5_" + var, var, cut)
    integral5 = h5.Integral()
    # print integral5
    if normalize is True:
        h5.Scale(1/integral5)
    h5.SetDirectory(ROOT.gROOT)

    ROOT.gROOT.cd()

    h1.SetLineColor(ROOT.kOrange)
    h1.SetFillColor(ROOT.kOrange)
    h1.SetFillStyle(1001) # Solid
    h2.SetLineColor(ROOT.kOrange-3)
    h2.SetFillColor(ROOT.kOrange-3)
    h2.SetFillStyle(1001) # Solid
    h3.SetLineColor(ROOT.kOrange-6)
    h3.SetFillColor(ROOT.kOrange-6)
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
    hs.GetHistogram().SetXTitle(var + " [GeV]")
    hs.GetHistogram().SetYTitle("Normalized event counts")
    hs.SetMaximum(y_maximum * 20)
    hs.GetHistogram().GetYaxis().SetTitleOffset(1.5)

    hs.Draw() # re-draw to make the y axis range setting working

    h4.SetLineColor(ROOT.kBlue)
    h4.Draw("hist,same")

    h5.SetLineColor(ROOT.kRed)
    h5.Draw("hist,same")

    legend = ROOT.TLegend(0.5, 0.6, 0.9, 0.8)
    legend.AddEntry(h1, "Higgsino_N2N1_170_150", "f")
    legend.AddEntry(h2, "Higgsino_N2C1p_170_150", "f")
    legend.AddEntry(h3, "Higgsino_N2C1m_170_150", "f")
    legend.AddEntry(h4, "NUHM2_m12_600 (100k, C+C(+j), filtered)", "l")
    legend.AddEntry(h5, "NUHM2_m12_600 (10k, n2>l+l-n1, filtered)", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.02);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    AtlasStyle.ATLASLabel(0.15, 0.85, "internal", ROOT.kBlack)

    output = var + ".pdf"
    canvas.SaveAs(output)

#----------------------------#

# def nBaselineLeptons():
#     f_filtered = "/afs/cern.ch/work/y/yushen/private/Higgsino/SimpleAnalysis/user.chris.100k.CC.filtered.TestJob.root"
#     f_unfiltered = "/afs/cern.ch/work/y/yushen/private/Higgsino/SimpleAnalysis/user.chris.100k.CC.unfiltered.TestJob.root"

#     f_filtered.cd()
#     t1 = f_filtered.Get("EwkHiggsino2016__ntuple")
#     h1 = ROOT.TH1F("h1", "filtered", 4, 0, 4)
#     h2 = ROOT.TH1F("h2", "filtered met>50", 4, 0, 4)
#     t1.Project("h1", "nBaselineLeptons")
#     t1.Project("h2", "nBaselineLeptons", "met>50")
#     h1.SetDirectory(ROOT.gROOT)
#     h2.SetDirectory(ROOT.gROOT)

#     f_unfiltered.cd()
#     t2 = f_filtered.Get("EwkHiggsino2016__ntuple")
#     h3 = ROOT.TH1F("h3", "unfiltered", 4, 0, 4)
#     h4 = ROOT.TH1F("h4", "unfiltered met>50", 4, 0, 4)
#     t2.Project("h3", "nBaselineLeptons")
#     t2.Project("h4", "nBaselineLeptons", "met>50")
#     h3.SetDirectory(ROOT.gROOT)
#     h4.SetDirectory(ROOT.gROOT)

#     h1.SetLineColor(kBlue)



#----------------------------#

if __name__ == '__main__':
    main()
