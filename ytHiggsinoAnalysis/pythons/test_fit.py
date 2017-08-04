#!/usr/bin/python
import ROOT
import AtlasStyle

def main():
    path_higgsino = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/SimpleAnalysis/Results/20170802/"
    n2_n1 = "160_100"
    f_higgsino_N2N1 = "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root"
    f_higgsino_C1C1 = "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root"
    f_higgsino_N2C1p = "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root"
    f_higgsino_N2C1m = "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root"

    higgsino_dm = int( n2_n1[:n2_n1.find("_")] ) - int( n2_n1[n2_n1.find("_")+1:] )

    path_nuhm2 = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/SimpleAnalysis/Results/20170730/"
    m12 = 300
    f_nuhm2_N2N1 = "user.yushen.run_" + str(m12) + "_N2N1.TestJob.root"
    f_nuhm2_C1C1 = "user.yushen.run_" + str(m12) + "_C1C1.TestJob.root"
    f_nuhm2_N2C1p = "user.yushen.run_" + str(m12) + "_N2C1p.TestJob.root"
    f_nuhm2_N2C1m = "user.yushen.run_" + str(m12) + "_N2C1m.TestJob.root"

    nuhm2_dm = 0
    if m12 == 300:
        nuhm2_dm = 55
    elif m12 == 350:
        nuhm2_dm = 46
    elif m12 == 400:
        nuhm2_dm = 38
    elif m12 == 500:
        nuhm2_dm = 28
    elif m12 == 600:
        nuhm2_dm = 22
    elif m12 == 700:
        nuhm2_dm = 18
    elif m12 == 800:
        nuhm2_dm = 15

    file1 = path_higgsino + f_higgsino_N2N1
    file2 = path_higgsino + f_higgsino_C1C1
    file3 = path_higgsino + f_higgsino_N2C1p
    file4 = path_higgsino + f_higgsino_N2C1m
    file5 = path_nuhm2 + f_nuhm2_N2N1
    file6 = path_nuhm2 + f_nuhm2_C1C1
    file7 = path_nuhm2 + f_nuhm2_N2C1p
    file8 = path_nuhm2 + f_nuhm2_N2C1m

    var = "mll"
    nbins, xmin, xmax = 200, 0, 100
    if m12 == 300 or m12 == 350 or m12 == 400:
        nbins, xmin, xmax = 400, 0, 200
    cut = ""

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

    h1.Scale(integral1 / (integral1+integral2+integral3+integral4) )
    h2.Scale(integral2 / (integral1+integral2+integral3+integral4) )
    h3.Scale(integral3 / (integral1+integral2+integral3+integral4) )
    h4.Scale(integral4 / (integral1+integral2+integral3+integral4) )

    h5.Scale(integral5 / (integral5+integral6+integral7+integral8) )
    h6.Scale(integral6 / (integral5+integral6+integral7+integral8) )
    h7.Scale(integral7 / (integral5+integral6+integral7+integral8) )
    h8.Scale(integral8 / (integral5+integral6+integral7+integral8) )

    h_higgsino = h1.Clone()
    h_higgsino.Add(h2)
    h_higgsino.Add(h3)
    h_higgsino.Add(h4)

    h_higgsino.SetLineColor(ROOT.kBlack)
    h_higgsino.SetFillColor(ROOT.kBlack)
    h_higgsino.SetFillStyle(0) # hollow
    h_higgsino.SetXTitle(var + " [GeV]")
    h_higgsino.SetYTitle("Normalized event counts")

    # Fitting histogram (with predefined function):
    fit_higgsino_core = ROOT.TF1("fit_higgsino_core", "gaus", 0, higgsino_dm)
    fit_higgsino_core.SetLineColor(ROOT.kRed-8)
    fit_higgsino_core.SetLineWidth(3)
    h_higgsino.Fit(fit_higgsino_core, "0")
    h_higgsino.Fit(fit_higgsino_core, "0")
    h_higgsino.Fit(fit_higgsino_core, "R+")
    higgsino_core_parameters = fit_higgsino_core.GetParameters()

    fit_higgsino_tail = ROOT.TF1("fit_higgsino_tail", "expo", higgsino_dm, h_higgsino.GetXaxis().GetXmax())
    fit_higgsino_tail.SetLineColor(ROOT.kRed-8)
    fit_higgsino_tail.SetLineWidth(3)
    h_higgsino.Fit(fit_higgsino_tail, "0")
    h_higgsino.Fit(fit_higgsino_tail, "0")
    h_higgsino.Fit(fit_higgsino_tail, "R+")
    higgsino_tail_parameters = fit_higgsino_tail.GetParameters()

    print "Fit higgsino total:"
    fit_higgsino_total = ROOT.TF1("fit_higgsino_total", "gaus(0)+expo(3)", h_higgsino.GetXaxis().GetXmin(), h_higgsino.GetXaxis().GetXmax())
    fit_higgsino_total.SetLineColor(ROOT.kRed-8)
    fit_higgsino_total.SetLineWidth(3)
    fit_higgsino_total.SetParameters(higgsino_core_parameters[0],
                                     higgsino_core_parameters[1],
                                     higgsino_core_parameters[2],
                                     higgsino_tail_parameters[0], 
                                     higgsino_tail_parameters[1])
    h_higgsino.Fit(fit_higgsino_total, "0")
    h_higgsino.Fit(fit_higgsino_total, "0")
    h_higgsino.Fit(fit_higgsino_total, "R+")

    h_nuhm2 = h5.Clone()
    h_nuhm2.Add(h6)
    h_nuhm2.Add(h7)
    h_nuhm2.Add(h8)

    h_nuhm2.SetLineColor(ROOT.kBlue)
    h_nuhm2.SetFillColor(ROOT.kBlue)
    h_nuhm2.SetFillStyle(0) # hollow
    h_nuhm2.SetXTitle(var + " [GeV]")
    h_nuhm2.SetYTitle("Normalized event counts")

    # Fitting histogram (with predefined function):
    fit_nuhm2_core = ROOT.TF1("fit_nuhm2_core", "gaus", 0, nuhm2_dm)
    fit_nuhm2_core.SetLineColor(ROOT.kGreen-7)
    fit_nuhm2_core.SetLineWidth(3)
    h_nuhm2.Fit(fit_nuhm2_core, "0")
    h_nuhm2.Fit(fit_nuhm2_core, "0")
    h_nuhm2.Fit(fit_nuhm2_core, "R+")
    nuhm2_core_parameters = fit_nuhm2_core.GetParameters()

    fit_nuhm2_tail = ROOT.TF1("fit_nuhm2_tail", "expo", nuhm2_dm, h_nuhm2.GetXaxis().GetXmax())
    fit_nuhm2_tail.SetLineColor(ROOT.kGreen-7)
    fit_nuhm2_tail.SetLineWidth(3)
    h_nuhm2.Fit(fit_nuhm2_tail, "0")
    h_nuhm2.Fit(fit_nuhm2_tail, "0")
    h_nuhm2.Fit(fit_nuhm2_tail, "R+")
    nuhm2_tail_parameters = fit_nuhm2_tail.GetParameters()

    print "Fit NUHM2 total"
    fit_nuhm2_total = ROOT.TF1("fit_nuhm2_total", "gaus(0)+expo(3)", h_nuhm2.GetXaxis().GetXmin(), h_nuhm2.GetXaxis().GetXmax())
    fit_nuhm2_total.SetLineColor(ROOT.kGreen-7)
    fit_nuhm2_total.SetLineWidth(3)
    fit_nuhm2_total.SetParameters(nuhm2_core_parameters[0],
                                  nuhm2_core_parameters[1],
                                  nuhm2_core_parameters[2],
                                  nuhm2_tail_parameters[0], 
                                  nuhm2_tail_parameters[1])
    h_nuhm2.Fit(fit_nuhm2_total, "0")
    h_nuhm2.Fit(fit_nuhm2_total, "0")
    h_nuhm2.Fit(fit_nuhm2_total, "R+")

    canvas = ROOT.TCanvas("c","", 800,600)
    canvas.SetLeftMargin(0.12)
    # ROOT.gStyle.SetOptFit(1111) # show fitting results in stats box
    logY = True

    if logY:
        ROOT.gPad.SetLogy()

    h_higgsino.SetStats(0) # no stats box
    h_nuhm2.SetStats(0) # no stats box
    h_higgsino.Draw()
    h_nuhm2.Draw("same")

    legend = ROOT.TLegend(0.5, 0.7, 0.9, 0.8)
    legend.AddEntry(h_higgsino, "Higgsino" + n2_n1, "l")
    legend.AddEntry(h_nuhm2, "NUHM2 m12=" + str(m12), "l")
    legend.AddEntry(fit_higgsino_total, "fitting Higgsino", "l")
    legend.AddEntry(fit_nuhm2_total, "fitting NUHM2", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.02);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    AtlasStyle.ATLASLabel(0.15, 0.85, "internal", ROOT.kBlack)

    output = "fit_" + var + "_" + str(m12) + ".pdf"
    canvas.SaveAs(output)

# def peak_distribution():

# def tail_distribution():

#----------------------------#

if __name__ == '__main__':
    main()
