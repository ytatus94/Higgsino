#!/usr/bin/python

import ROOT
# import numpy as np
import os
import array

path = "/Users/ytshen/Documents/Working/OU/HEP/Abe/"
strong_Xsec = "NUHM2_Strong_SUSYTools.txt"
weak_Xsec = "NUHM2_Weak_SUSYTools.txt"
strong_slha = "StrongSLHA/"
weak_slha = "WeakSHLA/"

def main():
    Xsec_list = read_cross_section(path + weak_Xsec)
    Xsec_plots_all_FS(Xsec_list)
    Xsec_plots_weak(Xsec_list) # only works for weak
    particles_dict = read_slha(path + weak_slha)
    mass_spectra(particles_dict, ("z1ss", "z2ss", "z3ss", "z4ss", "w1ss", "w2ss"))
    mass_difference_spectra(particles_dict, ("z1ss", "z2ss", "z3ss", "z4ss", "w1ss", "w2ss"))

#----------------------------#

# Xsec_list = []

def read_cross_section(filename):
    Xsec_list = []
    with open(filename) as fopen:
        lines = fopen.readlines()
        for line in lines:
            dict = {}
            if "SAMPLE     FS   CROSSECTION[pb]     K-FACTOR     FILTEREFF   REL.UNCERT" not in line:
                dict['sample'], dict['fs'], dict['Xsec'], dict['kFactor'], dict['filterEff'], dict['relUncert'] = line.split()
                index_of_m12 = dict['sample'].find('m12_')
                index_of_slha = dict['sample'].find(".slha", index_of_m12)
                dict['m12'] = dict['sample'][index_of_m12 + len('m12_') : index_of_slha]
                Xsec_list.append(dict)
    return Xsec_list

#----------------------------#

def Xsec_plots_all_FS(Xsec_list):
    # Get the final states (FS) for the dictionary
    list_FS = []
    for d in Xsec_list:
        # if d['fs'] != 'FS':
            if int(d['fs']) not in list_FS:
                list_FS.append( int(d['fs']) )

    # Extract m12 and Xsec and put into a list
    list_FS_m12_Xsec = []
    for fs in list_FS:
        dict = {}
        list_m12 = []
        list_Xsec = []
        for d in Xsec_list:
            # if d['fs'] != 'FS' and int(d['fs']) == fs:
            if int(d['fs']) == fs:
                #print d['fs'], d['sample'], d['m12'], d['Xsec']
                list_m12.append( int(d['m12']) )
                list_Xsec.append( float(d['Xsec']) )
        dict['m12'] = list_m12
        dict['Xsec'] = list_Xsec
        list_FS_m12_Xsec.append(dict)
    #print list_FS_m12_Xsec
    number_of_FS = len(list_FS_m12_Xsec)

    # Convert list to array, and put in TGragh
    list_TGraph = []
    for i in range(0, number_of_FS):
        # x = np.asarray( list_FS_m12_Xsec[1]['m12'] )
        # y = np.asarray( list_FS_m12_Xsec[1]['Xsec'] )
        x = array.array("d", list_FS_m12_Xsec[i]['m12'])
        y = array.array("d", list_FS_m12_Xsec[i]['Xsec'])
        g = ROOT.TGraph(len(x), x, y)
        g.SetLineColor(i + 1)
        list_TGraph.append( g.Clone() )
        del g
    # print len(list_TGraph)

    # Create a TCanvas
    Xsec_canvas = ROOT.TCanvas("c1", "", 800, 800)
    Xsec_canvas.SetLeftMargin(0.12)
    Xsec_canvas.SetBottomMargin(0.13)
    Xsec_canvas.SetLogy()

    mg = ROOT.TMultiGraph()
    # mg.SetTitle("Cross-section")

    for g in list_TGraph:
        # print list_TGraph.index(g)
        g.SetLineColor(list_TGraph.index(g) + 1)
        mg.Add(g)

    mg.Draw("Al")
    mg.GetXaxis().SetTitle("m_{1/2} [GeV]")
    mg.GetXaxis().SetTitleOffset(1.5)
    mg.GetYaxis().SetTitle("cross-section [pb]")
    mg.GetYaxis().SetTitleOffset(1.5)

    Xsec_canvas.SaveAs("Xsec.pdf")

#----------------------------#

def Xsec_plots_weak(Xsec_list, combined = True, individual = False):
    ''' make compressed+compressed, compressed+accessible, and accessible+accessible cross-section plots '''

    list_CC_FS = [111, 112, 115, 117, 122, 125, 127, 157]
    list_CA_FS = [113, 114, 116, 118, 123, 124, 126, 128, 135, 137, 145, 147, 158, 167]
    list_AA_FS = [133, 134, 136, 138, 144, 146, 148, 168]

    Xsec_CC = sum_of_Xsec(Xsec_list, list_CC_FS) # Get compressed+compressed cross-section
    Xsec_CA = sum_of_Xsec(Xsec_list, list_CA_FS) # Get compressed+accessible cross-section
    Xsec_AA = sum_of_Xsec(Xsec_list, list_AA_FS) # Get accessible+accessible cross-section

    Xsec_N1N1 = sum_of_Xsec(Xsec_list, [111]) # N1N1
    Xsec_N1N2 = sum_of_Xsec(Xsec_list, [112]) # N1N2, N2N1
    Xsec_N1C1 = sum_of_Xsec(Xsec_list, [115, 117]) # N1C1, C1N1
    Xsec_N2N2 = sum_of_Xsec(Xsec_list, [122]) # N2N2
    Xsec_N2C1 = sum_of_Xsec(Xsec_list, [125, 127]) # N2C1, C1N2
    Xsec_C1C1 = sum_of_Xsec(Xsec_list, [157])

    # Convert list to array, and put in TGragh
    x = array.array("d", [300, 350, 400, 500, 600, 700, 800])
    y_CC = array.array("d", Xsec_CC)
    y_CA = array.array("d", Xsec_CA)
    y_AA = array.array("d", Xsec_AA)

    g_CC = ROOT.TGraph(len(x), x, y_CC)
    g_CA = ROOT.TGraph(len(x), x, y_CA)
    g_AA = ROOT.TGraph(len(x), x, y_AA)

    g_CC.SetLineWidth(2)
    g_CC.SetLineColor(ROOT.kBlack)
    g_CA.SetLineWidth(2)
    g_CA.SetLineColor(ROOT.kRed)
    g_AA.SetLineWidth(2)
    g_AA.SetLineColor(ROOT.kBlue)

    if individual:
        y_N1N1 = array.array("d", Xsec_N1N1)
        y_N1N2 = array.array("d", Xsec_N1N2)
        y_N1C1 = array.array("d", Xsec_N1C1)
        y_N2N2 = array.array("d", Xsec_N2N2)
        y_N2C1 = array.array("d", Xsec_N2C1)
        y_C1C1 = array.array("d", Xsec_C1C1)

        g_N1N1 = ROOT.TGraph(len(x), x, y_N1N1)
        g_N1N2 = ROOT.TGraph(len(x), x, y_N1N2)
        g_N1C1 = ROOT.TGraph(len(x), x, y_N1C1)
        g_N2N2 = ROOT.TGraph(len(x), x, y_N2N2)
        g_N2C1 = ROOT.TGraph(len(x), x, y_N2C1)
        g_C1C1 = ROOT.TGraph(len(x), x, y_C1C1)

        g_N1N1.SetLineStyle(2)
        g_N1N1.SetLineColor(1)
        g_N1N2.SetLineStyle(2)
        g_N1N2.SetLineColor(2)
        g_N1C1.SetLineStyle(2)
        g_N1C1.SetLineColor(3)
        g_N2N2.SetLineStyle(2)
        g_N2N2.SetLineColor(4)
        g_N2C1.SetLineStyle(2)
        g_N2C1.SetLineColor(5)
        g_C1C1.SetLineStyle(2)
        g_C1C1.SetLineColor(6)

    mg = ROOT.TMultiGraph()
    # mg.SetTitle("Cross-section")
    if combined:
        mg.Add(g_CC)
        mg.Add(g_CA)
        mg.Add(g_AA)
    if individual:
        mg.Add(g_N1N1)
        mg.Add(g_N1N2)
        mg.Add(g_N1C1)
        mg.Add(g_N2N2)
        mg.Add(g_N2C1)
        mg.Add(g_C1C1)

    # Create a TCanvas
    Xsec_canvas = ROOT.TCanvas("c1", "", 800, 800)
    Xsec_canvas.SetLeftMargin(0.12)
    Xsec_canvas.SetBottomMargin(0.13)
    Xsec_canvas.SetLogy()

    if combined:
        mg.Draw("AC")
    if individual:
        mg.Draw("Al")
    mg.GetXaxis().SetTitle("m_{1/2} [GeV]")
    mg.GetXaxis().SetTitleOffset(1.5)
    mg.GetYaxis().SetTitle("NUHM2 cross-section [pb]")
    mg.GetYaxis().SetTitleOffset(1.5)

    y_min = 0.6
    y_max = 0.8

    if individual and combined:
        y_min = 0.7
        y_max = 0.3
    elif not combined:
        y_min = 0.45
        y_max = 0.75

    legend = ROOT.TLegend(0.5, y_min, 0.8, y_max)
    if combined:
        legend.AddEntry(g_CC, "Compressed + Compressed", "l")
        legend.AddEntry(g_CA, "Compressed + Accessible", "l")
        legend.AddEntry(g_AA, "Accessible + Accessible", "l")
    if individual:
        legend.AddEntry(g_N1N1, "#tilde{#chi}^{0}_{1}#tilde{#chi}^{0}_{1}", "l")
        legend.AddEntry(g_N1N2, "#tilde{#chi}^{0}_{1}#tilde{#chi}^{0}_{2}", "l")
        legend.AddEntry(g_N1C1, "#tilde{#chi}^{0}_{1}#tilde{#chi}^{#pm}_{1}", "l")
        legend.AddEntry(g_N2N2, "#tilde{#chi}^{0}_{2}#tilde{#chi}^{0}_{2}", "l")
        legend.AddEntry(g_N2C1, "#tilde{#chi}^{0}_{2}#tilde{#chi}^{#pm}_{1}", "l")
        legend.AddEntry(g_C1C1, "#tilde{#chi}^{#pm}_{1}#tilde{#chi}^{#pm}_{1}", "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.03);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    Xsec_canvas.SaveAs("Xsec_weak.pdf")

#----------------------------#

def sum_of_Xsec(Xsec_list, FS_list):
    Xsec_sum = [0., 0., 0., 0., 0., 0., 0.]
    for d in Xsec_list:
        if int(d['fs']) in FS_list:
            if int(d['m12']) == 300:
                Xsec_sum[0] += float(d['Xsec'])
            elif int(d['m12']) == 350:
                Xsec_sum[1] += float(d['Xsec'])
            elif int(d['m12']) == 400:
                Xsec_sum[2] += float(d['Xsec'])
            elif int(d['m12']) == 500:
                Xsec_sum[3] += float(d['Xsec'])
            elif int(d['m12']) == 600:
                Xsec_sum[4] += float(d['Xsec'])
            elif int(d['m12']) == 700:
                Xsec_sum[5] += float(d['Xsec'])
            elif int(d['m12']) == 800:
                Xsec_sum[6] += float(d['Xsec'])
    return Xsec_sum

#----------------------------#

def read_slha(dirname):
    ''' read the mass values from the SLHA file '''

    particles = ["top", "W^+", "h^0", "H^0", "A^0", "H^+", "dnl", "upl", "stl", "chl",
                 "b1", "t1", "el-", "nuel", "mul-", "numl", "tau1", "nutl", "glss", "z1ss",
                 "z2ss", "w1ss", "z3ss", "z4ss", "w2ss", "gvss", "dnr", "upr", "str", "chr",
                 "b2", "t2", "er-", "mur-", "tau2"]

    particles_dict = {}
    for particle in particles:
        particles_dict[particle] = []

    for slha in sorted(os.listdir(dirname)):
        with open(dirname + slha) as fopen:
            lines = fopen.readlines()
            read_particle_mass = False
            for line in lines:
                if "Block MASS   # Scalar and gaugino mass spectrum" in line:
                    read_particle_mass = True
                if "Block ALPHA   # Effective Higgs mixing parameter" in line:
                    read_particle_mass = False
                if read_particle_mass:
                    for particle in particles:
                        if particle in line and "#" in line:
                            temp = line.split()
                            mass = abs( float(temp[1]) )
                            particles_dict[particle].append(mass)
    return particles_dict

#----------------------------#

def mass_spectra(particles_dict, particles_tuple):
    ''' make mass spectra for partiles listed in particles_tuple '''

    # Convert list to array, and put in TGragh
    list_TGraph = []
    # for key in particles_dict.keys():
    for key in particles_tuple:
        x = array.array("d", [300, 350, 400, 500, 600, 700, 800])
        y = array.array("d", particles_dict[key] )
        g = ROOT.TGraph(len(x), x, y)
        list_TGraph.append( g.Clone() )
        del g
    # print len(list_TGraph)

    # Create a TCanvas
    canvas = ROOT.TCanvas("c1", "", 800, 800)
    canvas.SetLeftMargin(0.12)
    canvas.SetBottomMargin(0.13)
    # canvas.SetLogy()

    mg = ROOT.TMultiGraph()
    # mg.SetTitle("SUSY particle masses")

    for g in list_TGraph:
        # print list_TGraph.index(g)
        g.SetLineColor(list_TGraph.index(g) + 1)
        mg.Add(g)

    mg.Draw("AC")
    mg.GetXaxis().SetTitle("m_{1/2} [GeV]")
    mg.GetXaxis().SetTitleOffset(1.5)
    mg.GetYaxis().SetTitle("mass [GeV]")
    mg.GetYaxis().SetTitleOffset(1.5)

    legend = ROOT.TLegend(0.2, 0.5, 0.3, 0.8)
    # Need to modify this part manually
    for key in particles_tuple:
        if "z1ss" in key:
            text = "#tilde{#chi}^{0}_{1}"
        elif "z2ss" in key:
            text = "#tilde{#chi}^{0}_{2}"
        elif "z3ss" in key:
            text = "#tilde{#chi}^{0}_{3}"
        elif "z4ss" in key:
            text = "#tilde{#chi}^{0}_{4}"
        elif "w1ss" in key:
            text = "#tilde{#chi}^{#pm}_{1}"
        elif "w2ss" in key:
            text = "#tilde{#chi}^{#pm}_{2}"
        index = particles_tuple.index(key)
        legend.AddEntry(list_TGraph[index], text, "l")
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.03);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    # canvas.BuildLegend()
    canvas.SaveAs("mass_spectra.pdf")

#----------------------------#

def mass_difference_spectra(particles_dict, particles_tuple):
    ''' make mass difference spectra for partiles listed in particles_tuple '''

    # Calculate mass difference
    mass_difference = []
    # C1 - N1
    dC1N1 = [C1 - N1 for (C1, N1) in zip(particles_dict["w1ss"], particles_dict["z1ss"])]
    mass_difference.append(dC1N1)
    # N2 - N1
    dN2N1 = [N2 - N1 for (N2, N1) in zip(particles_dict["z2ss"], particles_dict["z1ss"])]
    mass_difference.append(dN2N1)
    # N2 - C1
    dN2C1 = [N2 - C1 for (N2, C1) in zip(particles_dict["z2ss"], particles_dict["w1ss"])]
    mass_difference.append(dN2C1)
    # N3 - N1
    dN3N1 = [N3 - N1 for (N3, N1) in zip(particles_dict["z3ss"], particles_dict["z1ss"])]
    mass_difference.append(dN3N1)
    # N3 - N2
    dN3N2 = [N3 - N2 for (N3, N2) in zip(particles_dict["z3ss"], particles_dict["z2ss"])]
    mass_difference.append(dN3N2)
    # N3 - C1
    dN3C1 = [N3 - C1 for (N3, C1) in zip(particles_dict["z3ss"], particles_dict["w1ss"])]
    mass_difference.append(dN3C1)

    # Convert list to array, and put in TGragh
    list_TGraph = []
    for i in range(0, len(mass_difference) ):
        x = array.array("d", [300, 350, 400, 500, 600, 700, 800])
        y = array.array("d", mass_difference[i])
        g = ROOT.TGraph(len(x), x, y)
        list_TGraph.append( g.Clone() )
        del g
    # print len(list_TGraph)

    # Create a TCanvas
    canvas = ROOT.TCanvas("c1", "", 800, 800)
    canvas.SetLeftMargin(0.12)
    canvas.SetBottomMargin(0.13)
    # canvas.SetLogy()

    mg = ROOT.TMultiGraph()
    # mg.SetTitle("SUSY particle masse differences")

    for g in list_TGraph:
        # print list_TGraph.index(g)
        g.SetLineColor(list_TGraph.index(g) + 1)
        mg.Add(g)

    mg.Draw("AC")
    mg.GetXaxis().SetTitle("m_{1/2} [GeV]")
    mg.GetXaxis().SetTitleOffset(1.5)
    mg.GetYaxis().SetTitle("mass [GeV]")
    mg.GetYaxis().SetTitleOffset(1.5)

    legend = ROOT.TLegend(0.2, 0.5, 0.3, 0.8)
    # Need to modify this part manually
    legend.AddEntry(list_TGraph[0], "#tilde{#chi}^{#pm}_{1} - #tilde{#chi}^{0}_{1}", "l")
    legend.AddEntry(list_TGraph[1], "#tilde{#chi}^{0}_{2} - #tilde{#chi}^{0}_{1}", "l")
    legend.AddEntry(list_TGraph[2], "#tilde{#chi}^{0}_{2} - #tilde{#chi}^{#pm}_{1}", "l")
    legend.AddEntry(list_TGraph[3], "#tilde{#chi}^{0}_{3} - #tilde{#chi}^{0}_{1}", "l")
    legend.AddEntry(list_TGraph[4], "#tilde{#chi}^{0}_{3} - #tilde{#chi}^{0}_{2}", "l")
    legend.AddEntry(list_TGraph[5], "#tilde{#chi}^{0}_{3} - #tilde{#chi}^{#pm}_{1}", "l")
    #
    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.03);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    canvas.SaveAs("mass_difference.pdf")

#----------------------------#

if __name__ == "__main__":
    main()
