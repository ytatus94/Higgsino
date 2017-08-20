#!/usr/bin/python
import ROOT
import AtlasStyle
import math

def main():
    path_higgsino = "/Users/ytshen/Desktop/20170817/"
    n2_n1 = "190_150"
    f_higgsino_N2N1 = "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root"
    f_higgsino_C1C1 = "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root"
    f_higgsino_N2C1p = "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root"
    f_higgsino_N2C1m = "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root"

    n2 = int( n2_n1[:n2_n1.find("_")] )
    n1 = int( n2_n1[n2_n1.find("_")+1:] )
    higgsino_dm = n2 - n1

    path_nuhm2 = "/Users/ytshen/Desktop/20170817/"
    m12 = 600
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

    h_higgsino = get_histogram(file1, file2, file3, file4)
    h_higgsino.SetLineColor(ROOT.kBlack)

    h_nuhm2 = get_histogram(file5, file6, file7, file8)
    h_nuhm2.SetLineColor(ROOT.kBlue)

    # Use a Gaussian to fit the core and an exponential function to fit the tail
    # Firstly, fit core and tail separately to get the parameters,
    # then use the parameters as initial parameters for combined fit.

    # Fitting histogram (with predefined function):
    fit_higgsino_core = ROOT.TF1("fit_higgsino_core", "gaus", 0, higgsino_dm)
    fit_higgsino_core.SetLineColor(ROOT.kRed-8)
    fit_higgsino_core.SetLineWidth(3)
    # fit_higgsino_core = ROOT.TF1("fit_higgsino_core", funcMllDistr, 0, higgsino_dm, 3) # need to provide number of parameters as the last argument
    # fit_higgsino_core.SetParameters(1, n1, -1.*n2) # n1 and n2 should be opposite sign
    # fit_higgsino_core.FixParameter(1, n1)
    # fit_higgsino_core.FixParameter(2, -1.*n2)
    h_higgsino.Fit(fit_higgsino_core, "R0")
    h_higgsino.Fit(fit_higgsino_core, "R0")
    h_higgsino.Fit(fit_higgsino_core, "R0+")
    higgsino_core_parameters = fit_higgsino_core.GetParameters()

    fit_higgsino_tail = ROOT.TF1("fit_higgsino_tail", "expo", higgsino_dm, h_higgsino.GetXaxis().GetXmax())
    fit_higgsino_tail.SetLineColor(ROOT.kRed-8)
    fit_higgsino_tail.SetLineWidth(3)
    h_higgsino.Fit(fit_higgsino_tail, "R0")
    h_higgsino.Fit(fit_higgsino_tail, "R0")
    h_higgsino.Fit(fit_higgsino_tail, "R0+")
    higgsino_tail_parameters = fit_higgsino_tail.GetParameters()

    # print "Fit higgsino total:"
    fit_higgsino_total = ROOT.TF1("fit_higgsino_total", "gaus(0)+expo(3)", h_higgsino.GetXaxis().GetXmin(), h_higgsino.GetXaxis().GetXmax())
    fit_higgsino_total.SetLineColor(ROOT.kRed-8)
    fit_higgsino_total.SetLineWidth(3)
    fit_higgsino_total.SetParameters(higgsino_core_parameters[0],
                                     higgsino_core_parameters[1],
                                     higgsino_core_parameters[2],
                                     higgsino_tail_parameters[0], 
                                     higgsino_tail_parameters[1])
    h_higgsino.Fit(fit_higgsino_total, "R0")
    h_higgsino.Fit(fit_higgsino_total, "R0")
    h_higgsino.Fit(fit_higgsino_total, "R+")

    # Fitting histogram (with predefined function):
    fit_nuhm2_core = ROOT.TF1("fit_nuhm2_core", "gaus", 0, nuhm2_dm)
    fit_nuhm2_core.SetLineColor(ROOT.kGreen-7)
    fit_nuhm2_core.SetLineWidth(3)
    h_nuhm2.Fit(fit_nuhm2_core, "R0")
    h_nuhm2.Fit(fit_nuhm2_core, "R0")
    h_nuhm2.Fit(fit_nuhm2_core, "R0+")
    nuhm2_core_parameters = fit_nuhm2_core.GetParameters()

    fit_nuhm2_tail = ROOT.TF1("fit_nuhm2_tail", "expo", nuhm2_dm, h_nuhm2.GetXaxis().GetXmax())
    fit_nuhm2_tail.SetLineColor(ROOT.kGreen-7)
    fit_nuhm2_tail.SetLineWidth(3)
    h_nuhm2.Fit(fit_nuhm2_tail, "R0")
    h_nuhm2.Fit(fit_nuhm2_tail, "R0")
    h_nuhm2.Fit(fit_nuhm2_tail, "R0+")
    nuhm2_tail_parameters = fit_nuhm2_tail.GetParameters()

    # print "Fit NUHM2 total"
    fit_nuhm2_total = ROOT.TF1("fit_nuhm2_total", "gaus(0)+expo(3)", h_nuhm2.GetXaxis().GetXmin(), h_nuhm2.GetXaxis().GetXmax())
    fit_nuhm2_total.SetLineColor(ROOT.kGreen-7)
    fit_nuhm2_total.SetLineWidth(3)
    fit_nuhm2_total.SetParameters(nuhm2_core_parameters[0],
                                  nuhm2_core_parameters[1],
                                  nuhm2_core_parameters[2],
                                  nuhm2_tail_parameters[0], 
                                  nuhm2_tail_parameters[1])
    h_nuhm2.Fit(fit_nuhm2_total, "R0")
    h_nuhm2.Fit(fit_nuhm2_total, "R0")
    h_nuhm2.Fit(fit_nuhm2_total, "R+")

    # Make plot
    canvas = ROOT.TCanvas("c","", 800,600)
    canvas.SetLeftMargin(0.12)
    # ROOT.gStyle.SetOptFit(1111) # show fitting results in stats box
    logY = True

    if logY:
        ROOT.gPad.SetLogy()

    h_higgsino.SetStats(0) # no stats box
    h_nuhm2.SetStats(0) # no stats box

    max_value = max(h_higgsino.GetMaximum(), h_nuhm2.GetMaximum()) * 10
    h_higgsino.SetMinimum(0.0001)
    h_higgsino.SetMaximum(max_value)
    h_higgsino.Draw()
    h_nuhm2.Draw("same")

    legend = ROOT.TLegend(0.5, 0.7, 0.9, 0.8)
    legend.AddEntry(h_higgsino, "Higgsino" + n2_n1, "l")
    legend.AddEntry(h_nuhm2, "NUHM2 m12=" + str(m12), "l")
    # legend.AddEntry(fit_higgsino_total, "fitting Higgsino", "l")
    # legend.AddEntry(fit_nuhm2_total, "fitting NUHM2", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.02);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    AtlasStyle.ATLASLabel(0.15, 0.85, "internal", ROOT.kBlack)

    output = "fit_" + var + "_" + str(m12) + ".pdf"
    canvas.SaveAs(output)

#----------------------------#

def get_histogram(f_N2N1, f_C1C1, f_N2C1p, f_N2C1m):
    '''
    Get the combined histogram
    '''
    file1 = f_N2N1
    file2 = f_C1C1
    file3 = f_N2C1p
    file4 = f_N2C1m

    var = "mll"
    nbins, xmin, xmax = 200, 0, 200
    cut = ""

    f1 = ROOT.TFile(file1)
    t1 = f1.Get("EwkNUHM22016__ntuple")
    h1 = ROOT.TH1F("h1_" + var, var, nbins, xmin, xmax)
    t1.Project("h1_" + var, var, cut)
    integral1 = h1.Integral()
    h1.Scale(1/integral1)
    h1.SetDirectory(ROOT.gROOT)

    f2 = ROOT.TFile(file2)
    t2 = f2.Get("EwkNUHM22016__ntuple")
    h2 = ROOT.TH1F("h2_" + var, var, nbins, xmin, xmax)
    t2.Project("h2_" + var, var, cut)
    integral2 = h2.Integral()
    h2.Scale(1/integral2)
    h2.SetDirectory(ROOT.gROOT)

    f3 = ROOT.TFile(file3)
    t3 = f3.Get("EwkNUHM22016__ntuple")
    h3 = ROOT.TH1F("h3_" + var, var, nbins, xmin, xmax)
    t3.Project("h3_" + var, var, cut)
    integral3 = h3.Integral()
    h3.Scale(1/integral3)
    h3.SetDirectory(ROOT.gROOT)

    f4 = ROOT.TFile(file4)
    t4 = f4.Get("EwkNUHM22016__ntuple")
    h4 = ROOT.TH1F("h4_" + var, var, nbins, xmin, xmax)
    t4.Project("h4_" + var, var, cut)
    integral4 = h4.Integral()
    h4.Scale(1/integral4)
    h4.SetDirectory(ROOT.gROOT)

    ROOT.gROOT.cd()

    h1.Scale(integral1 / (integral1+integral2+integral3+integral4) )
    h2.Scale(integral2 / (integral1+integral2+integral3+integral4) )
    h3.Scale(integral3 / (integral1+integral2+integral3+integral4) )
    h4.Scale(integral4 / (integral1+integral2+integral3+integral4) )

    h_Combined = h1.Clone()
    h_Combined.Add(h2)
    h_Combined.Add(h3)
    h_Combined.Add(h4)

    h_Combined.SetLineColor(ROOT.kBlack)
    h_Combined.SetFillColor(ROOT.kBlack)
    h_Combined.SetFillStyle(0) # hollow
    h_Combined.SetXTitle(var + " [GeV]")
    h_Combined.SetYTitle("Normalized event counts")

    return h_Combined

#----------------------------#

def funcMllDistr(x, par):
    '''
    taken from https://arxiv.org/abs/0704.2515
    equation 4, page 9
    NB there is a typo in the formula (just in writing it in the the paper, not in the work)
    the correct formula is in this code
    '''
    m1 = float(par[1])
    m2 = float(par[2])
    mu = m2 - m1
    m = float(x[0])
    M = m1 + m2
    m_Z = 91.
    norm = float(par[0]) * m

    radice = math.sqrt( pow(m, 4) - pow(m, 2) * ( pow(mu, 2) + pow(M, 2) ) + pow(mu * M, 2) )
    normalizzazione = pow(  pow(m, 2) - pow(m_Z, 2), 2)
    var = (norm * radice) / normalizzazione
    var = var * (-2 * pow(m, 4) + pow(m, 2) * (2 * pow(M, 2) - pow(mu, 2)) + pow((mu * M), 2) )

    if float(x[0]) > math.fabs(m2) - math.fabs(m1):
        var = 1

    return var

#----------------------------#

if __name__ == '__main__':
    main()
