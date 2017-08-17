#!/usr/bin/python
import ROOT
import AtlasStyle
import math

def main():
    # Higgsino common ntuple v1.8b
    path = "/Users/ytshen/Desktop/"
    f_140_100 = "MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root"
    f_160_100 = "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root"
    f_170_150 = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root"
    f_190_150 = "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root"

    fit_plot(path + f_140_100, "140_100")
    fit_plot(path + f_160_100, "160_100")
    fit_plot(path + f_170_150, "170_150")
    fit_plot(path + f_190_150, "190_150")

#----------------------------#

def fit_plot(file, n2_n1):
    f = ROOT.TFile(file)
    t = f.Get("MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 +"_2LMET50_MadSpin_NoSys")
    h = ROOT.TH1F("h_" + n2_n1, "truthMll", 100, 0, 100)
    t.Project("h_" + n2_n1, "truthMll", "truthMll>0")

    n2 = float( (n2_n1.split("_"))[0] )
    n1 = float( (n2_n1.split("_"))[1] )
    dm = n2 - n1
    print n2, n1, dm

    fit_func = ROOT.TF1("fit_func", funcMllDistr, 0, dm, 3)
    fit_func.SetParameters(1., n1, -1. * n2)
    area_fit_func = fit_func.Integral(0., dm)
    fit_func.SetParameter(0, 1. / area_fit_func) # normalize fit_func
    fit_func.FixParameter(1, n1)
    fit_func.FixParameter(2, -1. * n2)
    fit_func.SetLineColor(ROOT.kRed)
    fit_func.SetLineStyle(2)

    canvas = ROOT.TCanvas("c","", 800,600)
    canvas.SetLeftMargin(0.12)
    logY = True

    if logY:
        ROOT.gPad.SetLogy()
    ROOT.gStyle.SetOptFit(1111)

    h.SetXTitle("m_{ll} [GeV]")
    h.SetYTitle("Events / 1GeV")
    h.GetYaxis().SetTitleOffset(1.2)
    h.SetLineColor(ROOT.kBlue)
    h.Draw("hist")

    h.Fit(fit_func, "R0")
    h.Fit(fit_func, "R0")
    h.Fit(fit_func, "R+")

    fit_func.Draw("same")

    AtlasStyle.ATLASLabel(0.15, 0.85, "internal", ROOT.kBlack)

    legend = ROOT.TLegend(0.5, 0.4, 0.9, 0.5)
    legend.AddEntry(h, "Higgsino_" + n2_n1, "l")
    # legend.AddEntry(fit_func, "Theoretical Higgsino_" + n2_n1 + "(fix N2 and N1)", "l")
    legend.AddEntry(fit_func, "Theoretical Higgsino_" + n2_n1, "l")
    legend.SetBorderSize(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.03)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    legend.Draw()

    output = "fit_Higgsino_common_ntuple_v1.8b_" + n2_n1 + ".pdf"
    canvas.SaveAs(output)

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
    var = 0;
    delta = abs(m2) - abs(m1);

    if m < delta:
        radice = math.sqrt( pow(m, 4) - pow(m, 2) * ( pow(mu, 2) + pow(M, 2) ) + pow(mu * M, 2) )
        normalizzazione = pow(  pow(m, 2) - pow(m_Z, 2), 2)
        var = (norm * radice) / normalizzazione
        var = var * (-2 * pow(m, 4) + pow(m, 2) * (2 * pow(M, 2) - pow(mu, 2)) + pow((mu * M), 2) )

    # if x[0] > math.fabs(m2) - math.fabs(m1):
    #     var = 1

    return var

#----------------------------#

if __name__ == '__main__':
    main()
