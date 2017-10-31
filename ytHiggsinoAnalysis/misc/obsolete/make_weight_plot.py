#!/usr/bin/python
'''
### obsolete ###
This is used to compare my reweighted results (using v1.8b ntuples) and the official v1.8e ntuples
'''
import ROOT

def main():
    path = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/"
    # make_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 350)
    # make_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 400)
    # make_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 500)
    # make_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 600)
    # make_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 700)
    # make_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 800)

    # This part is wrong. See nuhm2-20170830
    # compare_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 350)
    # compare_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 400)
    # compare_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 500)
    # compare_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 600)
    # compare_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 700)
    # compare_plot(path + "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 800)

    plot_reweight_mll(path + "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 350)
    plot_reweight_mll(path + "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 400)
    plot_reweight_mll(path + "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 500)
    plot_reweight_mll(path + "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 600)
    plot_reweight_mll(path + "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 700)
    plot_reweight_mll(path + "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root", 800)

#----------------------------#

def make_plot(inputfile, m12):
    '''
    Make the weight plots
    '''
    n2_n1 = inputfile[inputfile.find("SM_Higgsino") + len("SM_Higgsino") + 1: inputfile.find("_2LMET50")]
    f = ROOT.TFile(inputfile)
    t = f.Get("MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 + "_2LMET50_MadSpin_NoSys")
    c = ROOT.TCanvas("c", "", 800, 600)
    # t.Draw("NUHM2weight_" + str(m12) + "m12")
    t.Draw("NUHM2weight_" + str(m12) + "m12", "FS!=157&&NUHM2weight_" + str(m12) + "m12!=0")
    # output = "m12_" + str(m12) + "_weight.pdf"
    output = "m12_" + str(m12) + "_weight_no_C1C1.pdf"
    c.SaveAs(output)

#----------------------------#

def compare_plot(inputfile, m12):
    '''
    Compare the weight plots between my results (using v1.8b) and the official v1.8e ntuples.
    This shows the official v1.8e ntuple is wrong.
    See nuhm2-20170830
    '''
    n2_n1 = inputfile[inputfile.find("SM_Higgsino") + len("SM_Higgsino") + 1: inputfile.find("_2LMET50")]
    f1 = ROOT.TFile(inputfile)
    t1 = f1.Get("MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 + "_2LMET50_MadSpin_NoSys")
    f2 = ROOT.TFile("/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/reweighted_m12_" + str(m12) + ".root")
    t2 = f2.Get("MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 + "_2LMET50_MadSpin_NoSys_reweighted_m12_" + str(m12))
    h1 = ROOT.TH1F("h1", "", 300, 0, 3)
    t1.Project("h1", "NUHM2weight_" + str(m12) + "m12", "FS!=157&&NUHM2weight_" + str(m12) + "m12!=0")
    h2 = ROOT.TH1F("h2", "", 300, 0, 3)
    t2.Project("h2", "NUHM2_weight", "FS!=157&&NUHM2_weight!=0")
    c = ROOT.TCanvas("c", "", 800, 600)
    h1.SetLineColor(ROOT.kRed)
    h1.SetXTitle("NUHM2 weight")
    h2.SetYTitle("Entries")
    h1.Draw()
    h2.SetLineColor(ROOT.kBlue)
    h2.Draw("same")
    legend = ROOT.TLegend(0.2, 0.7, 0.4, 0.8)
    legend.AddEntry(h1, "v1.8e", "l")
    legend.AddEntry(h2, "v1.8b", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.03);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()
    output = "m12_" + str(m12) + "_weight_no_C1C1.pdf"
    c.SaveAs(output)

#----------------------------#

def plot_reweight_mll(inputfile, m12):
    '''
    Make the reweight mll plots
    Overlap my results (v1.8b) and official v1.8e ntuples
    '''
    n2_n1 = inputfile[inputfile.find("SM_Higgsino") + len("SM_Higgsino") + 1: inputfile.find("_2LMET50")]
    f1 = ROOT.TFile(inputfile)
    t1 = f1.Get("MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 + "_2LMET50_MadSpin_NoSys")
    h_truth_Mll = ROOT.TH1F("h_truth_Mll", "truth Mll", 200, 0, 200)
    h_reweighted_Mll = ROOT.TH1F("h_reweighted_Mll", "reweighted Mll", 200, 0, 200)

    truthMll = 0
    NUHM2weight_350m12, NUHM2weight_400m12, NUHM2weight_500m12, NUHM2weight_600m12, NUHM2weight_700m12, NUHM2weight_800m12 = 0, 0, 0, 0, 0, 0
    FS = 0
    t1.SetBranchAddress("truthMll", truthMll)
    t1.SetBranchAddress("NUHM2weight_350m12", NUHM2weight_350m12)
    t1.SetBranchAddress("NUHM2weight_400m12", NUHM2weight_400m12)
    t1.SetBranchAddress("NUHM2weight_500m12", NUHM2weight_500m12)
    t1.SetBranchAddress("NUHM2weight_600m12", NUHM2weight_600m12)
    t1.SetBranchAddress("NUHM2weight_700m12", NUHM2weight_700m12)
    t1.SetBranchAddress("NUHM2weight_800m12", NUHM2weight_800m12)
    # t1.SetBranchAddress("FS", FS)

    for event in t1:
        truthMll = event.truthMll
        NUHM2weight_350m12 = event.NUHM2weight_350m12
        NUHM2weight_400m12 = event.NUHM2weight_400m12
        NUHM2weight_500m12 = event.NUHM2weight_500m12
        NUHM2weight_600m12 = event.NUHM2weight_600m12
        NUHM2weight_700m12 = event.NUHM2weight_700m12
        NUHM2weight_800m12 = event.NUHM2weight_800m12
    # entries = t1.GetEntries()
    # for i in range(0, entries + 1):
    #     t1.GetEntry(i)
        h_truth_Mll.Fill(truthMll)
        if m12 == 350:
            h_reweighted_Mll.Fill(truthMll, NUHM2weight_350m12)
        elif m12 == 400:
            h_reweighted_Mll.Fill(truthMll, NUHM2weight_400m12)
        elif m12 == 500:
            h_reweighted_Mll.Fill(truthMll, NUHM2weight_500m12)
        elif m12 == 600:
            h_reweighted_Mll.Fill(truthMll, NUHM2weight_600m12)
        elif m12 == 700:
            h_reweighted_Mll.Fill(truthMll, NUHM2weight_700m12)
        elif m12 == 800:
            h_reweighted_Mll.Fill(truthMll, NUHM2weight_800m12)
    c = ROOT.TCanvas("c", "", 800, 600)
    c.SetLeftMargin(0.12)
    logY = True
    if logY:
        ROOT.gPad.SetLogy()

    y_max = max(h_truth_Mll.GetMaximum(), h_reweighted_Mll.GetMaximum())
    if logY:
        y_max *= 5

    range_user_xmin = 0
    range_user_xmax = 0
    if m12 == 350:
        range_user_xmax = 100
    else:
        range_user_xmax = 50

    h_truth_Mll.SetTitle("")
    h_truth_Mll.SetXTitle("m_{ll} [GeV]")
    h_truth_Mll.SetYTitle("Events")
    h_truth_Mll.GetXaxis().SetRangeUser(range_user_xmin, range_user_xmax)
    h_truth_Mll.GetYaxis().SetTitleOffset(1.4)
    h_truth_Mll.SetMaximum(y_max)
    h_truth_Mll.SetLineColor(ROOT.kGreen)
    h_truth_Mll.SetStats(0)
    h_truth_Mll.Draw("hist")

    h_reweighted_Mll.SetLineColor(ROOT.kRed)
    h_reweighted_Mll.Draw("hist,same")

    legend = ROOT.TLegend(0.2, 0.75, 0.7, 0.85)
    legend.AddEntry(h_truth_Mll, "v1.8e truth Mll (" + n2_n1 + ")", "l")
    legend.AddEntry(h_reweighted_Mll, "v1.8e reweighted truth Mll (m12=" + str(m12) + ")", "l")
    legend.SetBorderSize(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.03)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    legend.Draw()

    output = "reweight_Higgsino_common_ntuple_v1.8e_to_m12_" + str(m12) + ".pdf"
    c.SaveAs(output)
    c.Close()

#----------------------------#

if __name__ == "__main__":
    main()
