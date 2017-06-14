#!/usr/bin/python

import ROOT
# import numpy as np
import array

path = "/Users/ytshen/Documents/Working/OU/HEP/Abe/"
strong_Xsec = "NUHM2_Strong_SUSYTools.txt"
weak_Xsec = "NUHM2_Weak_SUSYTools.txt"

def main():
    read_cross_section(path + weak_Xsec)
    Xsec_plot()

#----------------------------#

Xsec_list = []

def read_cross_section(filename):
    with open(filename) as fopen:
        lines = fopen.readlines()
        for line in lines:
            dict = {}
            dict['sample'], dict['fs'], dict['Xsec'], dict['kFactor'], dict['filterEff'], dict['relUncert'] = line.split()
            index_of_m12 = dict['sample'].find('m12_')
            index_of_slha = dict['sample'].find(".slha", index_of_m12)
            dict['m12'] = dict['sample'][index_of_m12 + len('m12_') : index_of_slha]
            Xsec_list.append(dict)

#----------------------------#

def Xsec_plot():
    # Get the final states (FS) for the dictionary
    list_FS = []
    for d in Xsec_list:
        if d['fs'] != 'FS':
            if int(d['fs']) not in list_FS:
                list_FS.append( int(d['fs']) )

    # Extract m12 and Xsec and put into a list
    list_FS_m12_Xsec = []
    for fs in list_FS:
        dict = {}
        list_m12 = []
        list_Xsec = []
        for d in Xsec_list:
            if d['fs'] != 'FS' and int(d['fs']) == fs:
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
    mg.SetTitle("NUHM2 Cross-section")

    for g in list_TGraph:
        # print list_TGraph.index(g)
        g.SetLineColor(list_TGraph.index(g) + 1)
        mg.Add(g)

    mg.Draw("AC")
    mg.GetXaxis().SetTitle("m_{1/2} [GeV]")
    mg.GetXaxis().SetTitleOffset(1.5)
    mg.GetYaxis().SetTitle("cross-section [pb]")
    mg.GetYaxis().SetTitleOffset(1.5)

    Xsec_canvas.SaveAs("Xsec.pdf")

#----------------------------#

if __name__ == "__main__":
    main()
