#!/usr/bin/python
import ROOT
import array

Lumi = 36.1

max_events = 5000.
multiplier_2L3 = 100.
multiplier_MET50 = 20.

# The order is [N2N1, C1C1, N2C1p, N2C1m]

# Branching ratio
# from SLHA file
# BR_N2_to_llN1 = 0.107
# BR_C1_to_ffN1 = 0.666
# BR_C1_to_lvlN1 = 0.333
BR_N2_to_llN1_300 = [0.0378120923, 1.0, 0.0378120923, 0.0378120923]
BR_N2_to_llN1_350 = [0.1013306826, 1.0, 0.1013306826, 0.1013306826]
BR_N2_to_llN1_400 = [0.1028803438, 1.0, 0.1028803438, 0.1028803438]
BR_N2_to_llN1_500 = [0.1051690615, 1.0, 0.1051690615, 0.1051690615]
BR_N2_to_llN1_600 = [0.1069829426, 1.0, 0.1069829426, 0.1069829426]
BR_N2_to_llN1_700 = [0.1084250846, 1.0, 0.1084250846, 0.1084250846]
BR_N2_to_llN1_800 = [0.1094692499, 1.0, 0.1094692499, 0.1094692499]
BR_N2_to_llN1 = [BR_N2_to_llN1_300, BR_N2_to_llN1_350, BR_N2_to_llN1_400, BR_N2_to_llN1_500, BR_N2_to_llN1_600, BR_N2_to_llN1_700, BR_N2_to_llN1_800]

BR_C1_to_ffN1_300 = [1.0, 1.0, 0.666666806, 0.666666806]
BR_C1_to_ffN1_350 = [1.0, 1.0, 0.666664720, 0.666664720]
BR_C1_to_ffN1_400 = [1.0, 1.0, 0.666664064, 0.666664064]
BR_C1_to_ffN1_500 = [1.0, 1.0, 0.666664064, 0.666664064]
BR_C1_to_ffN1_600 = [1.0, 1.0, 0.666664362, 0.666664362]
BR_C1_to_ffN1_700 = [1.0, 1.0, 0.666664540, 0.666664540]
BR_C1_to_ffN1_800 = [1.0, 1.0, 0.666664660, 0.666664660]
BR_C1_to_ffN1 = [BR_C1_to_ffN1_300, BR_C1_to_ffN1_350, BR_C1_to_ffN1_400, BR_C1_to_ffN1_500, BR_C1_to_ffN1_600, BR_C1_to_ffN1_700, BR_C1_to_ffN1_800]

BR_C1_to_lvlN1_300 = [1.0, 0.333333194, 1.0, 1.0]
BR_C1_to_lvlN1_350 = [1.0, 0.333336010, 1.0, 1.0]
BR_C1_to_lvlN1_400 = [1.0, 0.333336010, 1.0, 1.0]
BR_C1_to_lvlN1_500 = [1.0, 0.333335965, 1.0, 1.0]
BR_C1_to_lvlN1_600 = [1.0, 0.333335683, 1.0, 1.0]
BR_C1_to_lvlN1_700 = [1.0, 0.333335459, 1.0, 1.0]
BR_C1_to_lvlN1_800 = [1.0, 0.333335274, 1.0, 1.0]
BR_C1_to_lvlN1 = [BR_C1_to_lvlN1_300, BR_C1_to_lvlN1_350, BR_C1_to_lvlN1_400, BR_C1_to_lvlN1_500, BR_C1_to_lvlN1_600, BR_C1_to_lvlN1_700, BR_C1_to_lvlN1_800]

# Unweighted filter efficiency
# eff_300 = [0.409333, 0.152448, 0.253807, 0.265449]
# eff_350 = [0.233383, 0.137159, 0.260173, 0.261520]
# eff_400 = [0.214160, 0.129604, 0.228425, 0.233951]
# eff_500 = [0.183824, 0.115923, 0.191344, 0.194447]
# eff_600 = [0.163084, 0.106943, 0.170091, 0.174929]
# eff_700 = [0.147171, 0.097254, 0.161943, 0.164026]
# eff_800 = [0.135208, 0.094652, 0.149589, 0.154617]

# Weighted filter efficiency
# from log.generate
eff_300 = [0.414405, 0.164017, 0.265627, 0.277531]
eff_350 = [0.248245, 0.148728, 0.273310, 0.275627]
eff_400 = [0.231079, 0.141000, 0.244031, 0.249081]
eff_500 = [0.198565, 0.125613, 0.206531, 0.207577]
eff_600 = [0.177126, 0.115093, 0.182043, 0.188051]
eff_700 = [0.160043, 0.103832, 0.174270, 0.176030]
eff_800 = [0.146843, 0.101354, 0.161460, 0.165694]
eff = [eff_300, eff_350, eff_400, eff_500, eff_600, eff_700, eff_800]

# Weighted_events
# from log.generate
events_300 = [6496.438761, 7001.824881, 7045.985973, 7069.025200]
events_350 = [6981.815608, 7081.169635, 7100.283196, 7127.214925]
events_400 = [7110.087579, 7118.357039, 7194.425192, 7210.782080]
events_500 = [7091.717201, 7096.000634, 7291.280653, 7240.862591]
events_600 = [7149.202958, 7081.053773, 7201.247888, 7306.759687]
events_700 = [7140.607424, 7011.838356, 7254.922130, 7300.162934]
events_800 = [7142.989645, 7028.658871, 7249.957357, 7274.957122]
events = [events_300, events_350, events_400, events_500, events_600, events_700, events_800]

# Cross-section
# from Xsec file
Xsec_300 = [0.0009775530, 1.1640104660, 0.4768609298, 0.2784795051]
Xsec_350 = [0.5835187445, 0.9548695995, 0.6833463531, 0.3983657446]
Xsec_400 = [0.6255603991, 0.8415837349, 0.6845201512, 0.3976839861]
Xsec_500 = [0.6603094819, 0.7280789222, 0.6819165298, 0.3955900373]
Xsec_600 = [0.6656504736, 0.6745140438, 0.6791453722, 0.3930396433]
Xsec_700 = [0.6643270342, 0.6438838471, 0.6766070496, 0.3913281838]
Xsec_800 = [0.6598118363, 0.6240319555, 0.6748686972, 0.3906074836]
Xsec = [Xsec_300, Xsec_350, Xsec_400, Xsec_500, Xsec_600, Xsec_700, Xsec_800]

# Number of events in SR: cut and count
N_SR_300 = [117, 123, 146, 129]
N_SR_350 = [197, 137, 129, 139]
N_SR_400 = [221, 135, 197, 172]
N_SR_500 = [266, 171, 234, 200]
N_SR_600 = [281, 160, 249, 246]
N_SR_700 = [303, 185, 234, 229]
N_SR_800 = [298, 180, 275, 233]
N_SR = [N_SR_300, N_SR_350, N_SR_400, N_SR_500, N_SR_600, N_SR_700, N_SR_800]

#----------------------------#

def main():
    for m12 in range(0, len(Xsec)):
        # decay = len(Xsec[m12]) # should be 4 because there are 4 decays
        # acc = [acceptance(N_pass_truth, max_events) for N_pass_truth in N_SR[m12]]
        acc = []
        for N_pass_truth, max_events in zip(N_SR[m12], events[m12]):
            acc.append( acceptance(N_pass_truth, max_events) )

        n_events = []
        for decay in range(0, len(Xsec[m12])):
            # BR = 0
            # if decay is 0: # N2N1
            #     BR = BR_N2_to_llN1
            # elif decay is 1: # C1C1
            #     BR = BR_C1_to_lvlN1 * BR_C1_to_lvlN1
            # else: # N2C1p and N2C1m
            #     BR = BR_N2_to_llN1 * BR_C1_to_ffN1
            BR = BR_N2_to_llN1[m12][decay] * BR_C1_to_ffN1[m12][decay] * BR_C1_to_lvlN1[m12][decay] * BR_C1_to_lvlN1[m12][decay]
            n_events.append( Nevents(36.1, acc[decay], eff[m12][decay], Xsec[m12][decay], BR) )

        if m12 is 0:
            print "m12=300:"
            print "acceptance:", acc
            print "N_events:", n_events
            print "total=", sum(n_events)
        elif m12 is 1:
            print "m12=350:"
            print "acceptance:", acc
            print "N_events:", n_events
            print "total=", sum(n_events)
        elif m12 is 2:
            print "m12=400:"
            print "acceptance:", acc
            print "N_events:", n_events
            print "total=", sum(n_events)
        elif m12 is 3:
            print "m12=500:"
            print "acceptance:", acc
            print "N_events:", n_events
            print "total=", sum(n_events)
        elif m12 is 4:
            print "m12=600:"
            print "acceptance:", acc
            print "N_events:", n_events
            print "total=", sum(n_events)
        elif m12 is 5:
            print "m12=700:"
            print "acceptance:", acc
            print "N_events:", n_events
            print "total=", sum(n_events)
        elif m12 is 6:
            print "m12=800:"
            print "acceptance:", acc
            print "N_events:", n_events
            print "total=", sum(n_events)

    # print transpose(Xsec)
    make_plot( transpose(Xsec) )

#----------------------------#

def acceptance(N_pass_truth, N_all):
    return N_pass_truth / N_all

#----------------------------#

def Nevents(Lumi, acceptance, efficiency, Xsec, BR):
    return Lumi * 1000. * acceptance * efficiency * Xsec * BR

#----------------------------#

def transpose(original):
    N2N1 = []
    C1C1 = []
    N2C1p = []
    N2C1m = []

    for item in original:
        N2N1.append( item[0] )
        C1C1.append( item[1] )
        N2C1p.append( item[2] )
        N2C1m.append( item[3] )

    transpose = [N2N1, C1C1, N2C1p, N2C1m]
    return transpose

#----------------------------#

def make_plot(y_values):
    m12 = [300, 350, 400, 500, 600, 700, 800]
    # Convert list to array, and put in TGragh
    list_TGraph = []
    x = array.array("d", m12)
    for y_value in y_values:
        y = array.array("d", y_value)
        g = ROOT.TGraph(len(x), x, y)
        g.SetLineColor( y_values.index(y_value) )
        list_TGraph.append( g.Clone() )
        del g

    # Create a TCanvas
    canvas = ROOT.TCanvas("c1", "", 800, 800)
    canvas.SetLeftMargin(0.12)
    canvas.SetBottomMargin(0.13)
    canvas.SetLogy()

    mg = ROOT.TMultiGraph()
    # mg.SetTitle("Cross-section")

    # for g in list_TGraph:
    #     # print list_TGraph.index(g)
    #     g.SetLineColor(list_TGraph.index(g) + 1)
    #     mg.Add(g)

    g_N2N1 = list_TGraph[0]
    g_C1C1 = list_TGraph[1]
    g_N2C1p = list_TGraph[2]
    g_N2C1m = list_TGraph[3]
    g_N2N1.SetLineColor(1)
    g_C1C1.SetLineColor(2)
    g_N2C1p.SetLineColor(3)
    g_N2C1m.SetLineColor(4)
    mg.Add(g_N2N1)
    mg.Add(g_C1C1)
    mg.Add(g_N2C1p)
    mg.Add(g_N2C1m)

    mg.Draw("Al")
    mg.GetXaxis().SetTitle("m_{1/2} [GeV]")
    mg.GetXaxis().SetTitleOffset(1.5)
    mg.GetYaxis().SetTitle("cross-section [pb]")
    mg.GetYaxis().SetTitleOffset(1.5)

    legend = ROOT.TLegend(0.5, 0.45, 0.8, 0.75)
    legend.AddEntry(g_N2N1, "#tilde{#chi}^{0}_{2}#tilde{#chi}^{0}_{1}", "l")
    legend.AddEntry(g_C1C1, "#tilde{#chi}^{#pm}_{1}#tilde{#chi}^{#pm}_{1}", "l")
    legend.AddEntry(g_N2C1p, "#tilde{#chi}^{0}_{2}#tilde{#chi}^{+}_{1}", "l")
    legend.AddEntry(g_N2C1m, "#tilde{#chi}^{0}_{2}#tilde{#chi}^{-}_{1}", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.03);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    canvas.SaveAs("Xsec.pdf")

#----------------------------#

if __name__ == '__main__':
    main()
