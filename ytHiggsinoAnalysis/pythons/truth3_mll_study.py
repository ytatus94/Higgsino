#!/usr/bin/python

import ROOT
import AtlasStyle

def main():
    # mll_components()
    # mll_C1_test()
    # mll_no_Hadronic_Tau()
    # mll_shape()
    # compare_pythia_madgraph_madspin()
    compare_n2_decay()

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
    f_Higgsino_N2N1 = "../../../SimpleAnalysis/Results/20170628/user.yushen.SM_N2N1_170_150_2LMET50.root"
    f_Higgsino_N2C1p = "../../../SimpleAnalysis/Results/20170628/user.yushen.SM_N2C1p_170_150_2LMET50.root"
    f_Higgsino_N2C1m = "../../../SimpleAnalysis/Results/20170628/user.yushen.SM_N2C1m_170_150_2LMET50.root"
    f_NUHM2_100k_CC_filtered = "../../../SimpleAnalysis/Results/20170628/user.chris.100k.CC.filtered.TestJob.root"
    f_NUHM2_10k_n2_decay_no_jet = "../../../SimpleAnalysis/Results/20170628/user.chris.10k.n2.decay.no.jet.TestJob.root"
    f_NUHM2_10k_n2_decay_with_jet = "../../../SimpleAnalysis/Results/20170628/user.chris.10k.n2.decay.with.jet.TestJob.root"

    file1 = f_Higgsino_N2N1
    file2 = f_Higgsino_N2C1p
    file3 = f_Higgsino_N2C1m
    file4 = f_NUHM2_100k_CC_filtered
    file5 = f_NUHM2_10k_n2_decay_no_jet
    file6 = f_NUHM2_10k_n2_decay_with_jet

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

    f6 = ROOT.TFile(file6)
    t6 = f6.Get("EwkHiggsino2016__ntuple")
    h6 = ROOT.TH1F("h6_" + var, var, nbins, xmin, xmax)
    t6.Project("h6_" + var, var, cut)
    integral6 = h6.Integral()
    # print integral6
    if normalize is True:
        h6.Scale(1/integral6)
    h6.SetDirectory(ROOT.gROOT)

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

    h6.SetLineColor(ROOT.kGreen)
    h6.Draw("hist,same")

    legend = ROOT.TLegend(0.4, 0.6, 0.9, 0.8)
    legend.AddEntry(h1, "Higgsino_N2N1_170_150", "f")
    legend.AddEntry(h2, "Higgsino_N2C1p_170_150", "f")
    legend.AddEntry(h3, "Higgsino_N2C1m_170_150", "f")
    legend.AddEntry(h4, "NUHM2_m12_600 (100k, C+C(+j), filtered)", "l")
    legend.AddEntry(h5, "NUHM2_m12_600 (10k, n2>l+l-n1, no jet, filtered)", "l")
    legend.AddEntry(h6, "NUHM2_m12_600 (10k, n2>l+l-n1, with jet, filtered)", "l")
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

def compare_pythia_madgraph_madspin():
    f_Higgsino_N2C1p = "../../../SimpleAnalysis/Results/20170628/user.yushen.SM_N2C1p_170_150_2LMET50.root"
    f_Higgsino_N2C1m = "../../../SimpleAnalysis/Results/20170628/user.yushen.SM_N2C1m_170_150_2LMET50.root"
    f_NUHM2_100k_CC_filtered = "../../../SimpleAnalysis/Results/20170628/user.chris.100k.CC.filtered.TestJob.root"
    f_NUHM2_10k_n2_decay_no_jet = "../../../SimpleAnalysis/Results/20170628/user.chris.10k.n2.decay.no.jet.TestJob.root"
    f_MadSpin_N2C1p = "../../../SimpleAnalysis/Results/20170629/user.Judita.10k.N2C1p.TestJob.root"
    f_MadSpin_N2C1m = "../../../SimpleAnalysis/Results/20170629/user.Judita.10k.N2C1m.TestJob.root"

    file1 = f_Higgsino_N2C1p
    file2 = f_Higgsino_N2C1m
    file3 = f_NUHM2_100k_CC_filtered
    file4 = f_NUHM2_10k_n2_decay_no_jet
    file5 = f_MadSpin_N2C1p
    file6 = f_MadSpin_N2C1m

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
    # integral1 = h1.Integral()
    # print integral1
    # if normalize is True:
    #     h1.Scale(1/integral1)
    h1.SetDirectory(ROOT.gROOT)

    f2 = ROOT.TFile(file2)
    t2 = f2.Get("EwkHiggsino2016__ntuple")
    h2 = ROOT.TH1F("h2_" + var, var, nbins, xmin, xmax)
    t2.Project("h2_" + var, var, cut)
    # integral2 = h2.Integral()
    # print integral2
    # if normalize is True:
    #     h2.Scale(1/integral2)
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
    # integral5 = h5.Integral()
    # print integral5
    # if normalize is True:
    #     h5.Scale(1/integral5)
    h5.SetDirectory(ROOT.gROOT)

    f6 = ROOT.TFile(file6)
    t6 = f6.Get("EwkHiggsino2016__ntuple")
    h6 = ROOT.TH1F("h6_" + var, var, nbins, xmin, xmax)
    t6.Project("h6_" + var, var, cut)
    # integral6 = h6.Integral()
    # print integral6
    # if normalize is True:
    #     h6.Scale(1/integral6)
    h6.SetDirectory(ROOT.gROOT)

    ROOT.gROOT.cd()

    h12 = h1.Clone()
    h12.Add(h2)
    integral12 = h12.Integral()
    h12.Scale(1/integral12)

    h56 = h5.Clone()
    h56.Add(h6)
    integral56 = h56.Integral()
    h56.Scale(1/integral56)

    y_maximum = max( h12.GetMaximum(), h56.GetMaximum() )

    h12.SetStats(0)
    h12.SetTitle(var)
    h12.SetXTitle(var + " [GeV]")
    h12.SetYTitle("Normalized event counts")
    h12.SetMaximum(y_maximum * 20)
    h12.SetMinimum(0.0003)
    h12.GetYaxis().SetTitleOffset(1.5)
    h12.SetLineColor(ROOT.kOrange)
    h12.SetFillColor(ROOT.kOrange)
    h12.SetFillStyle(1001) # Solid
    h12.Draw()

    h3.SetLineColor(ROOT.kBlue)
    h3.SetFillColor(ROOT.kBlue)
    h3.SetFillStyle(0)
    h3.Draw("hist,same")

    h4.SetLineColor(ROOT.kRed)
    h4.SetFillColor(ROOT.kRed)
    h4.SetFillStyle(0)
    h4.Draw("hist,same")

    h56.SetLineColor(ROOT.kGreen)
    h56.SetFillColor(ROOT.kGreen)
    h56.SetFillStyle(0)
    h56.Draw("hist,same")

    legend = ROOT.TLegend(0.5, 0.6, 0.9, 0.8)
    legend.AddEntry(h12, "Higgsino_N2C1p/m_170_150", "f")
    legend.AddEntry(h3, "NUHM2_m12_600 (Pythia)", "l")
    legend.AddEntry(h4, "NUHM2_m12_600 (N2C1p/m, MadGraph)", "l")
    legend.AddEntry(h56, "NUHM2_m12_600 (N2C1p/m, MadSpin)", "l")
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

def compare_n2_decay():
    f_Higgsino_N2C1p = "../../../SimpleAnalysis/Results/20170628/user.yushen.SM_N2C1p_170_150_2LMET50.root"
    f_Higgsino_N2C1m = "../../../SimpleAnalysis/Results/20170628/user.yushen.SM_N2C1m_170_150_2LMET50.root"
    f_run_12p = "../../../SimpleAnalysis/Results/20170708/user.yushen.run_12p.TestJob.root"
    f_run_12m = "../../../SimpleAnalysis/Results/20170708/user.yushen.run_12m.TestJob.root"
    f_run_13p = "../../../SimpleAnalysis/Results/20170708/user.yushen.run_13p.TestJob.root"
    f_run_13m = "../../../SimpleAnalysis/Results/20170708/user.yushen.run_13m.TestJob.root"
    f_run_14p = "../../../SimpleAnalysis/Results/20170708/user.yushen.run_14p.TestJob.root"
    f_run_14m = "../../../SimpleAnalysis/Results/20170708/user.yushen.run_14m.TestJob.root"
    f_run_15p = "../../../SimpleAnalysis/Results/20170708/user.yushen.run_15p.TestJob.root"
    f_run_15m = "../../../SimpleAnalysis/Results/20170708/user.yushen.run_15m.TestJob.root"

    file1 = f_Higgsino_N2C1p
    file2 = f_Higgsino_N2C1m
    file3 = f_run_12p
    file4 = f_run_12m
    file5 = f_run_13p
    file6 = f_run_13m
    file7 = f_run_14p
    file8 = f_run_14m
    file9 = f_run_15p
    file10 = f_run_15m

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
    h1.SetDirectory(ROOT.gROOT)

    f2 = ROOT.TFile(file2)
    t2 = f2.Get("EwkHiggsino2016__ntuple")
    h2 = ROOT.TH1F("h2_" + var, var, nbins, xmin, xmax)
    t2.Project("h2_" + var, var, cut)
    h2.SetDirectory(ROOT.gROOT)

    f3 = ROOT.TFile(file3)
    t3 = f3.Get("EwkHiggsino2016__ntuple")
    h3 = ROOT.TH1F("h3_" + var, var, nbins, xmin, xmax)
    t3.Project("h3_" + var, var, cut+"&&met>50")
    # print "h3.Integral()=", h3.Integral()
    h3.SetDirectory(ROOT.gROOT)

    f4 = ROOT.TFile(file4)
    t4 = f4.Get("EwkHiggsino2016__ntuple")
    h4 = ROOT.TH1F("h4_" + var, var, nbins, xmin, xmax)
    t4.Project("h4_" + var, var, cut+"&&met>50")
    # print "h4.Integral()=", h4.Integral()
    h4.SetDirectory(ROOT.gROOT)

    f5 = ROOT.TFile(file5)
    t5 = f5.Get("EwkHiggsino2016__ntuple")
    h5 = ROOT.TH1F("h5_" + var, var, nbins, xmin, xmax)
    t5.Project("h5_" + var, var, cut+"&&met>50")
    # print "h5.Integral()=", h5.Integral()
    h5.SetDirectory(ROOT.gROOT)

    f6 = ROOT.TFile(file6)
    t6 = f6.Get("EwkHiggsino2016__ntuple")
    h6 = ROOT.TH1F("h6_" + var, var, nbins, xmin, xmax)
    t6.Project("h6_" + var, var, cut+"&&met>50")
    # print "h6.Integral()=", h6.Integral()
    h6.SetDirectory(ROOT.gROOT)

    f7 = ROOT.TFile(file7)
    t7 = f7.Get("EwkHiggsino2016__ntuple")
    h7 = ROOT.TH1F("h7_" + var, var, nbins, xmin, xmax)
    t7.Project("h7_" + var, var, cut+"&&met>50")
    # print "h7.Integral()=", h7.Integral()
    h7.SetDirectory(ROOT.gROOT)

    f8 = ROOT.TFile(file8)
    t8 = f8.Get("EwkHiggsino2016__ntuple")
    h8 = ROOT.TH1F("h8_" + var, var, nbins, xmin, xmax)
    t8.Project("h8_" + var, var, cut+"&&met>50")
    # print "h8.Integral()=", h8.Integral()
    h8.SetDirectory(ROOT.gROOT)

    f9 = ROOT.TFile(file9)
    t9 = f9.Get("EwkHiggsino2016__ntuple")
    h9 = ROOT.TH1F("h9_" + var, var, nbins, xmin, xmax)
    t9.Project("h9_" + var, var, cut+"&&met>50")
    # print "h9.Integral()=", h9.Integral()
    h9.SetDirectory(ROOT.gROOT)

    f10 = ROOT.TFile(file10)
    t10 = f10.Get("EwkHiggsino2016__ntuple")
    h10 = ROOT.TH1F("h10_" + var, var, nbins, xmin, xmax)
    t10.Project("h10_" + var, var, cut+"&&met>50")
    # print "h10.Integral()=", h10.Integral()
    h10.SetDirectory(ROOT.gROOT)

    # Filter efficiency
    eff_run_12p = 0.605510
    eff_run_12m = 0.619579
    eff_run_13p = 0.0009555
    eff_run_13m = 0.010037
    eff_run_14p = 0.029174
    eff_run_14m = 0.028922
    eff_run_15p = 0.117129
    eff_run_15m = 0.123213

    h3.Scale(eff_run_12p)
    h4.Scale(eff_run_12m)
    h5.Scale(eff_run_13p)
    h6.Scale(eff_run_13m)
    h7.Scale(eff_run_14p)
    h8.Scale(eff_run_14m)
    h9.Scale(eff_run_15p)
    h10.Scale(eff_run_15m)

    ROOT.gROOT.cd()

    # Higgsino
    h12 = h1.Clone()
    h12.Add(h2)
    integral12 = h12.Integral()
    # print "h12.Integral()=", h12.Integral()
    h12.Scale(1/integral12)

    # run_12
    h34 = h3.Clone()
    h34.Add(h4)
    integral34 = h34.Integral()
    # print "integral34=", integral34
    # h34.Scale(1/integral34)

    # run_13
    h56 = h5.Clone()
    h56.Add(h6)
    integral56 = h56.Integral()
    # print "integral56=", integral56
    # h56.Scale(1/integral56)

    # run_14
    h78 = h7.Clone()
    h78.Add(h8)
    integral78 = h78.Integral()
    # print "integral78=", integral78
    # h78.Scale(1/integral78)

    # run_15
    h910 = h9.Clone()
    h910.Add(h10)
    integral910 = h910.Integral()
    # print "integral910=", integral910
    # h910.Scale(1/integral910)

    br_run_12 = 1.07E-01
    br_run_13 = 2.19E-01
    br_run_14 = 6.65E-01
    br_run_15 = 4.47E-03

    # Above calculation is based on the assumption that BR=100% for that specific n2 decay
    # The integral value is the number of events when the BR=100%
    # But we have to consider the real situation that BR is not equal to 100%, i.e. scale to BR
    # For example, if N=5 when BR=100%, then N=1 when BR=20%
    h34.Scale(br_run_12)
    h56.Scale(br_run_13)
    h78.Scale(br_run_14)
    h910.Scale(br_run_15)

    integral34_new = h34.Integral()
    integral56_new = h56.Integral()
    integral78_new = h78.Integral()
    integral910_new = h910.Integral()

    print "integral34_new=", integral34_new
    print "integral56_new=", integral56_new
    print "integral78_new=", integral78_new
    print "integral910_new=", integral910_new

    integral_total = integral34_new + integral56_new + integral78_new + integral910_new
    print "integral_total=", integral_total

    # print "integral34_new / integral_total=", integral34_new / integral_total
    # print "integral56_new / integral_total=", integral56_new / integral_total
    # print "integral78_new / integral_total=", integral78_new / integral_total
    # print "integral910_new / integral_total=", integral910_new / integral_total

    # Then we normalize the total n2 decays to one.
    # h34.Scale(1/integral34_new)
    # h56.Scale(1/integral56_new)
    # h78.Scale(1/integral78_new)
    # h910.Scale(1/integral910_new)
    h34.Scale(1/integral_total)
    h56.Scale(1/integral_total)
    h78.Scale(1/integral_total)
    h910.Scale(1/integral_total)
    # Each decay should be normalized based on their proportion
    print "h34.Integral()=", h34.Integral() * 100
    print "h56.Integral()=", h56.Integral() * 100
    print "h78.Integral()=", h78.Integral() * 100
    print "h910.Integral()=", h910.Integral() * 100

    y_maximum = max( h12.GetMaximum(), h34.GetMaximum() )

    h12.SetStats(0)
    h12.SetTitle(var)
    h12.SetXTitle(var + " [GeV]")
    h12.SetYTitle("Normalized event counts")
    h12.SetMaximum(y_maximum * 20)
    h12.SetMinimum(0.00001)
    h12.GetYaxis().SetTitleOffset(1.5)
    h12.SetLineColor(ROOT.kOrange)
    h12.SetFillColor(ROOT.kOrange)
    h12.SetFillStyle(1001) # Solid
    h12.Draw()

    # h34.Scale(br_run_12)
    h34.SetLineColor(ROOT.kBlue)
    h34.SetFillColor(ROOT.kBlue)
    h34.SetFillStyle(0)
    # h34.Draw("hist,same")

    # h56.Scale(br_run_13)
    h56.SetLineColor(ROOT.kGreen)
    h56.SetFillColor(ROOT.kGreen)
    h56.SetFillStyle(0)
    # h56.Draw("hist,same")

    # h78.Scale(br_run_14)
    h78.SetLineColor(ROOT.kMagenta)
    h78.SetFillColor(ROOT.kMagenta)
    h78.SetFillStyle(0)
    # h78.Draw("hist,same")

    # h910.Scale(br_run_15)
    h910.SetLineColor(ROOT.kCyan)
    h910.SetFillColor(ROOT.kCyan)
    h910.SetFillStyle(0)
    # h910.Draw("hist,same")

    hs = ROOT.THStack()
    hs.Add(h56)
    hs.Add(h78)
    hs.Add(h910)
    hs.Add(h34)

    # By default the background of the histograms is erased before drawing the
    # histograms. The option "noclear" avoid this behaviour. This is useful
    # when drawing a THStack on top of an other plot. If the patterns used to
    # draw the histograms in the stack are transparents, then the plot behind
    # will be visible.
    hs.Draw("hist,same,noclear")

    legend = ROOT.TLegend(0.5, 0.6, 0.9, 0.8)
    legend.AddEntry(h12, "Higgsino_N2C1p/m_170_150", "f")
    legend.AddEntry(h34, "NUHM2_m12_600 (n2 > l+ l- n1)", "l")
    legend.AddEntry(h56, "NUHM2_m12_600 (n2 > #nu #bar{#nu} n1)", "l")
    legend.AddEntry(h78, "NUHM2_m12_600 (n2 > q #bar{q} n1)", "l")
    legend.AddEntry(h910, "NUHM2_m12_600 (n2 > f f c1)", "l")
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
