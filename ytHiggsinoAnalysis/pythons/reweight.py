#!/usr/bin python
import ROOT
import AtlasStyle
import math

def main():
    path = "/Users/ytshen/Desktop/"
    f_higgsino_140_100 = "MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root"
    f_higgsino_160_100 = "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root"
    f_higgsino_170_150 = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root"

    fopen = ROOT.TFile(path + f_higgsino_170_150)

    name = fopen.GetName()
    n2_n1 = name[name.find("Higgsino") + len("Higgsino") + 1: name.find("_2LMET50")]
    n2 = n2_n1.split("_")[0]
    n1 = n2_n1.split("_")[1]
    dm_higgsino = int(n2) - int(n1)

    m12 = 600
    dm_nuhm2 = 0
    if m12 == 300:
        dm_nuhm2 = 55
    elif m12 == 350:
        dm_nuhm2 = 46
    elif m12 == 400:
        dm_nuhm2 = 38
    elif m12 == 500:
        dm_nuhm2 = 28
    elif m12 == 600:
        dm_nuhm2 = 22
    elif m12 == 700:
        dm_nuhm2 = 18
    elif m12 == 800:
        dm_nuhm2 = 15

    tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 + "_2LMET50_MadSpin_NoSys"
    tree = fopen.Get(tree_name)

    h_mll = ROOT.TH1F("h_mll", "mll", 50, 0, 50)
    h_reweighted_mll_1 = ROOT.TH1F("h_reweighted_mll_1", "mll", 50, 0, 50)
    h_reweighted_mll_2 = ROOT.TH1F("h_reweighted_mll_2", "mll", 50, 0, 50)

    for event in tree:
        mll = event.truthMll
        if mll > 0:
            reweighted_mll_1 = reweight_method_1(mll, float(dm_nuhm2) / float(dm_higgsino))
            h_mll.Fill(mll)
            h_reweighted_mll_1.Fill(reweighted_mll_1)
            h_reweighted_mll_2.Fill(mll, float(dm_nuhm2) / float(dm_higgsino))

    canvas = ROOT.TCanvas("canvas", "mll", 800, 600)
    ROOT.gPad.SetLogy()
    h_mll.SetLineColor(ROOT.kBlue)
    h_mll.Draw()
    h_reweighted_mll_1.Draw("hist,same")
    h_reweighted_mll_1.SetLineStyle(2)
    h_reweighted_mll_1.SetLineColor(ROOT.kRed)
    h_reweighted_mll_2.Draw("hist,same")
    h_reweighted_mll_2.SetLineColor(ROOT.kGreen)
    canvas.SaveAs("reweight_mll.pdf")

#----------------------------#

def reweight_method_1(mll, ratio):
    '''
    Reweight Higgsino mll to NUHM2 using
    m_{\ell\ell}(NUHM2) = m_{\ell\ell}(Higgsino) * (dM_{NUHM2}/dM_{Higgsino})
    '''
    return mll * ratio

#----------------------------#

if __name__ == '__main__':
    main()
