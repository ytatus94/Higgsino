#!/usr/bin/python

import ROOT
# from ROOT import kBlack,kWhite,kGray,kRed,kPink,kMagenta,kViolet,kBlue,kAzure,kCyan,kTeal,kGreen,kSpring,kYellow,kOrange,kDashed


def ATLASLabel(x, y, text, color):
    l = ROOT.TLatex()
    l.SetNDC()
    l.SetTextFont(72)
    l.SetTextColor(color)

    delx = 0.115*696*ROOT.gPad.GetWh()/(472*ROOT.gPad.GetWw())
    # delx = 0.085*696*ROOT.gPad.GetWh()/(472*ROOT.gPad.GetWw())

    l.DrawLatex(x, y, "ATLAS")
    if text:
        p = ROOT.TLatex()
        p.SetNDC()
        p.SetTextFont(42)
        p.SetTextColor(color)
        p.DrawLatex(x+delx, y, text)


#def ATLASLabelOld(x, y, Preliminary, color):
#    l = ROOT.TLatex()
#    l.SetNDC()
#    l.SetTextFont(72)
#    l.SetTextColor(color)
#    l.DrawLatex(x, y, "ATLAS")
#    if Preliminary is True:
#        p = ROOT.TLatex()
#        p.SetNDC()
#        p.SetTextFont(42)
#        p.SetTextColor(color)
#        p.DrawLatex(x+0.115, y, "Preliminary")


def ATLASVersion(version, x, y, color):
    if version:
        versionString = "Version %s", version
        l = ROOT.TLatex()
        l.SetTextAlign(22)
        l.SetTexSize(0.04)
        l.SetNDC()
        l.SetTextFont(72)
        l.SetTextColor(color)
        l.DrawLatex(x, y, versionString)


def myText(x, y, text, color, tsize):
    # tsize = 0.05
    l = ROOT.TLatex()
    # l.SetTextAlign(12)
    l.SetTextSize(tsize)
    l.SetTextFont(42)
    l.SetNDC()
    l.SetTextColor(color)
    l.DrawLatex(x, y, text)


def myBoxText(x, y, boxsize, text, mcolor):
    tsize = 0.06
    l = ROOT.TLatex()
    l.SetTextAlign(12)
    l.SetNDC()
    l.DrawLatex(x, y, text)

    y1 = y - 0.25*tsize
    y2 = y + 0.25*tsize
    x2 = x - 0.3*tsize
    x1 = x2 - boxsize

    print "x1= %f, x2= %f, y1= %f, y2= %f \n", x1, x2, y1, y2

    mbox = ROOT.TPav(x1, y1, x2, y2, 0, "NDC")

    mbox.SetFillColor(mcolor)
    mbox.SetFillStyle(1001)
    mbox.Draw()

    mline = ROOT.TLine()
    mline.SetLineWidth(4)
    mline.SetLineColor(1)
    mline.SetLineStyle(1)
    y_new = (y1 + y2)/2.
    mline.DrawLineNDC(x1, y_new, x2, y_new)


def myMarkerText(x, y, text, color, mstyle, msize):
    tsize = 0.06
    marker = ROOT.TMarker(x - (0.4*tsize), y, 8)
    marker.SetMarkerColor(color)
    marker.SetNDC()
    marker.SetMarkerStyle(mstyle)
    marker.SetMarkerSize(msize)
    marker.Draw()

    l = ROOT.TLatex
    l.SetTextAlign(12)
    l.SetNDC()
    l.DrawLatex(x, y, text)
