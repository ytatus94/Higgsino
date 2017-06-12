#!/usr/bin/python

import os, ROOT, array
from ROOT import kFALSE

def main():
    nsig, nbkg = read_number_of_events_in_signal_region()
    zn = []
    zn.append(calculate_Zn(nsig[0], nbkg)) # m12=300
    zn.append(calculate_Zn(nsig[1], nbkg)) # m12=350
    zn.append(calculate_Zn(nsig[2], nbkg)) # m12=400
    zn.append(calculate_Zn(nsig[3], nbkg)) # m12=500
    zn.append(calculate_Zn(nsig[4], nbkg)) # m12=600
    zn.append(calculate_Zn(nsig[5], nbkg)) # m12=700
    zn.append(calculate_Zn(nsig[6], nbkg)) # m12=800
    # print zn

    make_significance_plot(zn)
    # make_significance_plot([20.0, 20.0, 15.66, 6.98, 2.48, 0.01, 0.01])

#----------------------------#

def read_number_of_events_in_signal_region():
    NUHM2_yields = []
    bkg_yields = 0
    with open("yields.txt") as fopen:
        lines = fopen.readlines()
        for line in lines: # line is a string
            list = line.split() # split string into list
            # NUHM2 signal
            if "NUHM2_m12_300" in line:
                NUHM2_yields.append( float(list[2]) )
            elif "NUHM2_m12_350" in line:
                NUHM2_yields.append( float(list[2]) )
            elif "NUHM2_m12_400" in line:
                NUHM2_yields.append( float(list[2]) )
            elif "NUHM2_m12_500" in line:
                NUHM2_yields.append( float(list[2]) )
            elif "NUHM2_m12_600" in line:
                NUHM2_yields.append( float(list[2]) )
            elif "NUHM2_m12_700" in line:
                NUHM2_yields.append( float(list[2]) )
            elif "NUHM2_m12_800" in line:
                NUHM2_yields.append( float(list[2]) )
            # bkg
            elif "Wgamma" in line:
                bkg_yields += float(list[2])
            elif "Wjets" in line:
                bkg_yields += float(list[2])
            elif "Zgamma" in line:
                bkg_yields += float(list[2])
            elif "Zjets" in line:
                bkg_yields += float(list[2])
            elif "Zttgamma" in line:
                bkg_yields += float(list[2])
            elif "Zttjets" in line:
                bkg_yields += float(list[2])
            # elif "alt_DY_PowPy" in line:
            #     bkg_yields += float(list[2])
            # elif "alt_ttbar_nonallhad" in line:
            #     bkg_yields += float(list[2])
            elif "diboson0L" in line:
                bkg_yields += float(list[2])
            elif "diboson1L" in line:
                bkg_yields += float(list[2])
            elif "diboson2L" in line:
                bkg_yields += float(list[2])
            elif "diboson3L" in line:
                bkg_yields += float(list[2])
            elif "diboson4L" in line:
                bkg_yields += float(list[2])
            elif "higgs" in line:
                bkg_yields += float(list[2])
            elif "singletop" in line:
                bkg_yields += float(list[2])
            elif "tZ" in line:
                bkg_yields += float(list[2])
            elif "topOther" in line:
                bkg_yields += float(list[2])
            elif "triboson" in line:
                bkg_yields += float(list[2])
            elif "ttV" in line:
                bkg_yields += float(list[2])
            elif "ttbar" in line:
                bkg_yields += float(list[2])
    # print NUHM2_yields
    # print bkg_yields
    return NUHM2_yields, bkg_yields

#----------------------------#

def calculate_Zn(nsig, nbkg):
    uncert = 0.3
    Zn = ROOT.RooStats.NumberCountingUtils.BinomialExpZ(nsig, nbkg, uncert)
    return Zn

#----------------------------#

def make_significance_plot(zn):
    # Create a TH2F histogram and fill it.
    hFinalSig = ROOT.TH2F("hFinalSig", "Significance", 80, 200, 1000, 8, -1, 3)
    xbin = []
    for i in [300, 350, 400, 500, 600, 700, 800]: # NUHM2 mass points
        xbin.append( hFinalSig.GetXaxis().FindBin(i) )
    ybin = hFinalSig.GetYaxis().FindBin(0.2)
    # print xbin
    # print ybin
    for j in range(0, len(zn)):
        # print j, xbin[j], ybin, zn[j]
        hFinalSig.SetBinContent(xbin[j], ybin, zn[j])
    hFinalSig.SetXTitle("m_{1/2} [GeV]")
    hFinalSig.GetXaxis().SetTitleOffset(1.5)
    hFinalSig.SetStats(kFALSE)

    c1 = ROOT.TCanvas("c1", "significance", 800, 800)
    ROOT.gPad.SetBottomMargin(0.13)
    hFinalSig.Draw("text,colz")

    # Translate from Ximo's script
    # --- Begin extracting and drawing contours
    # Convert TH2F to TGraph2D
    g = ROOT.TGraph2D()
    ret = TH2toTGraph2D(hFinalSig, g)
    if ret == 0:
        print "no points left, exiting"
        exit()

    Ghisto = g.GetHistogram()
    # Contours for 1.64sigma (~exclusion) and 3sigma
    level = array.array('d', [1.64, 3])
    Ghisto.SetContour(2, level)
    Ghisto.Draw("cont1,list ,same")
    # --- END extracting and drawing contours
    c1.SaveAs("sig.pdf")

#----------------------------#

def TH2toTGraph2D(h_TH2F, g_TGraph2D):
    firstxbin = 1
    lastxbin = h_TH2F.GetXaxis().GetNbins()
    firstybin = 1
    lastybin = h_TH2F.GetYaxis().GetNbins()
    npoints = 0
    # print lastxbin, lastybin
    for j in range(firstybin, lastybin + 1):
        for i in range(firstxbin, lastxbin + 1):
            if h_TH2F.GetBinContent(i,j) > 0:
                print npoints, i, j, h_TH2F.GetBinContent(i,j)
                g_TGraph2D.SetPoint(npoints,
                                    h_TH2F.GetXaxis().GetBinCenter(i),
                                    h_TH2F.GetYaxis().GetBinCenter(j),
                                    h_TH2F.GetBinContent(i,j))
                # For NUHM2 we need other points in order to make a line
                # Because to define a line we need at least two points.
                g_TGraph2D.SetPoint(npoints+1,
                                    h_TH2F.GetXaxis().GetBinCenter(i),
                                    h_TH2F.GetYaxis().GetBinCenter(j)+10,
                                    h_TH2F.GetBinContent(i,j))
                g_TGraph2D.SetPoint(npoints+2,
                                    h_TH2F.GetXaxis().GetBinCenter(i),
                                    h_TH2F.GetYaxis().GetBinCenter(j)-10,
                                    h_TH2F.GetBinContent(i,j))
                # npoints += 1
                npoints += 3
                print npoints

    return npoints

#----------------------------#

if __name__ == "__main__":
    main()
