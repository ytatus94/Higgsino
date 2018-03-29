#!/usr/bin/python
'''
plot ee and mumu invariant mass for instrumental met background
'''
import ROOT
import array, math
import AtlasStyle

#------------------------------------------------#

def main():
    plot_invariant_mass(lep_EEOS = True)
    plot_invariant_mass(lep_MMOS = True)

#------------------------------------------------#

def create_histogram(tree_name, varexp, xtitle = 'xtitle', ytitle = 'ytitle', nbins = 0, xmin = 0, xmax = 0, binning_array = None):
    '''
    create empty histogram
    '''
    # xtitle = ""
    # ytitle = ""
    # nbins, xmin, xmax = 0, 0., 0.

    h_name = "h_" + tree_name
    hist = None

    if binning_array is None:
        hist = ROOT.TH1F(h_name, "", nbins, xmin, xmax)
    else:
        hist = ROOT.TH1F(h_name, "", nbins, binning_array)

    hist.GetXaxis().SetTitle(xtitle)
    hist.GetYaxis().SetTitle(ytitle)

    return hist

#------------------------------------------------#

def get_histogram(file, tree_name, varexp, lep_EEOS = False, lep_MMOS = False):
    hist = create_histogram(tree_name, varexp, 'm_{#font[12]{l}#font[12]{l}} [GeV]', 'Events / 0.05 GeV', 6000, 0.2, 300.0)

    fopen = ROOT.TFile(file)
    tree = fopen.Get(tree_name)

    for event in tree:
        trigMatch_metTrig = event.trigMatch_metTrig
        DPhiJ1Met = event.DPhiJ1Met
        # nLep_signal = event.nLep_signal
        nLep_base = event.nLep_base
        lep1Charge = event.lep1Charge
        lep2Charge = event.lep2Charge
        lep1Flavor = event.lep1Flavor
        lep2Flavor = event.lep2Flavor
        mll = event.mll

        if trigMatch_metTrig == 1 and DPhiJ1Met < 1.5 and nLep_base == 2 and lep1Charge != lep2Charge:
            if lep_EEOS and lep1Flavor == 1 and lep2Flavor == 1:
                hist.Fill(mll)
            elif lep_MMOS and lep1Flavor == 2 and lep2Flavor == 2:
                hist.Fill(mll)

    return hist

#------------------------------------------------#

def plot_invariant_mass(lep_EEOS = False, lep_MMOS = False):
    path = '/raid05/atlas/data/Higgsino/SusySkimHiggsino_v1.1_SUSY16_Bkgs_tree/'
    data15 = 'data15_SusySkimHiggsino_v1.1_SUSY16_tree.root'
    data16 = 'data16_SusySkimHiggsino_v1.1_SUSY16_tree.root'

    h_data15 = get_histogram(path + data15, "data15", 'mll', lep_EEOS, lep_MMOS)
    h_data15.SetLineColor(ROOT.kAzure)

    h_data16A = get_histogram(path + data16, "data16A", 'mll', lep_EEOS, lep_MMOS)
    h_data16A.SetLineColor(ROOT.kAzure)
    h_data16B = get_histogram(path + data16, "data16B", 'mll', lep_EEOS, lep_MMOS)
    h_data16B.SetLineColor(ROOT.kAzure)
    h_data16C = get_histogram(path + data16, "data16C", 'mll', lep_EEOS, lep_MMOS)
    h_data16C.SetLineColor(ROOT.kAzure)
    h_data16D = get_histogram(path + data16, "data16D", 'mll', lep_EEOS, lep_MMOS)
    h_data16D.SetLineColor(ROOT.kAzure)
    h_data16E = get_histogram(path + data16, "data16E", 'mll', lep_EEOS, lep_MMOS)
    h_data16E.SetLineColor(ROOT.kAzure)
    h_data16F = get_histogram(path + data16, "data16F", 'mll', lep_EEOS, lep_MMOS)
    h_data16F.SetLineColor(ROOT.kAzure)
    h_data16G = get_histogram(path + data16, "data16G", 'mll', lep_EEOS, lep_MMOS)
    h_data16G.SetLineColor(ROOT.kAzure)
    h_data16I = get_histogram(path + data16, "data16I", 'mll', lep_EEOS, lep_MMOS)
    h_data16I.SetLineColor(ROOT.kAzure)
    h_data16K = get_histogram(path + data16, "data16K", 'mll', lep_EEOS, lep_MMOS)
    h_data16K.SetLineColor(ROOT.kAzure)
    h_data16L = get_histogram(path + data16, "data16L", 'mll', lep_EEOS, lep_MMOS)
    h_data16L.SetLineColor(ROOT.kAzure)

    h_data = h_data15.Clone()
    h_data.Add(h_data16A)
    h_data.Add(h_data16B)
    h_data.Add(h_data16C)
    h_data.Add(h_data16D)
    h_data.Add(h_data16E)
    h_data.Add(h_data16F)
    h_data.Add(h_data16G)
    h_data.Add(h_data16I)
    h_data.Add(h_data16K)
    h_data.Add(h_data16L)

    entries = h_data.Integral()

    # Making plot
    c1 = ROOT.TCanvas("c1", "", 800, 800)
    ROOT.gStyle.SetOptStat(0)
    ROOT.gPad.SetBottomMargin(0.15)
    ROOT.gPad.SetRightMargin(0.05)
    ROOT.gPad.SetLeftMargin(0.15)
    ROOT.gPad.SetLogx()

    ymax = 0.
    if lep_EEOS:
        ymax = 250.
    elif lep_MMOS:
        ymax = 2000.
    h_data.SetMinimum(0.)
    h_data.SetMaximum(ymax)
    h_data.GetXaxis().SetTitleOffset(1.5)
    h_data.GetYaxis().SetTitleOffset(1.8)
    h_data.Draw()

    AtlasStyle.myText(0.2, 0.83, "#sqrt{s} = 13 TeV, 36.1 fb^{-1}", ROOT.kBlack, 0.04)
    AtlasStyle.myText(0.2, 0.78, "SusySkimHiggsino v1.1, Data (" + str(int(entries)) + " Events)", ROOT.kBlack, 0.03)
    AtlasStyle.myText(0.2, 0.73, "Pass E^{miss}_{T} triggers, #Delta#phi(#font[62]{p}^{j1}_{T}, #font[62]{p}^{miss}_{T}) < 1.5 Control Region", ROOT.kBlack, 0.03)
    if lep_EEOS:
        AtlasStyle.myText(0.2, 0.68, "Baseline e^{#pm}e^{#mp}", ROOT.kBlack, 0.03)
    elif lep_MMOS:
        AtlasStyle.myText(0.2, 0.68, "Baseline #mu^{#pm}#mu^{#mp}", ROOT.kBlack, 0.03)

    output = 'invariant_mass_'
    if lep_EEOS:
        output += 'lep_EEOS.pdf'
    elif lep_MMOS:
        output += 'lep_MMOS.pdf'

    c1.SaveAs(output)

#------------------------------------------------#

if __name__ == '__main__':
    main()
