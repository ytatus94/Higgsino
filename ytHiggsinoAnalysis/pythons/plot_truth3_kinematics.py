#!/usr/bin/python
'''
Compare the truth distributions between NUHM2 m12=600 and Higgsino_170_150.
The results are used in the internal note.
We use Higgsino_170_150 because the dM=20 and close to dM(NUHM2 m12=600)~22
'''
import ROOT
import AtlasStyle

# path = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170926b/"
path = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/SimpleAnalysis/Results/20170926b/"
NUHM2 = ["NUHM2_m12_600_N2N1.root",
         "NUHM2_m12_600_C1C1.root",
         "NUHM2_m12_600_N2C1p.root",
         "NUHM2_m12_600_N2C1m.root"]
Higgsino = ["Higgsino_170_150_N2N1.root",
            "Higgsino_170_150_C1C1.root",
            "Higgsino_170_150_N2C1p.root",
            "Higgsino_170_150_N2C1m.root"]

def main():
    variables = get_variable_list()
    for var in variables:
        h_NUHM2_N2N1 = loop_tree(path + NUHM2[0], var)
        h_NUHM2_C1C1 = loop_tree(path + NUHM2[1], var)
        h_NUHM2_N2C1p = loop_tree(path + NUHM2[2], var)
        h_NUHM2_N2C1m = loop_tree(path + NUHM2[3], var)

        h_Higgsino_N2N1 = loop_tree(path + Higgsino[0], var)
        h_Higgsino_C1C1 = loop_tree(path + Higgsino[1], var)
        h_Higgsino_N2C1p = loop_tree(path + Higgsino[2], var)
        h_Higgsino_N2C1m = loop_tree(path + Higgsino[3], var)

        # Use all events (not events pass SR requirements)
        plot_making(var, True,
                    h_Higgsino_N2N1, h_Higgsino_C1C1, h_Higgsino_N2C1p, h_Higgsino_N2C1m,
                    h_NUHM2_N2N1, h_NUHM2_C1C1, h_NUHM2_N2C1p, h_NUHM2_N2C1m)

#----------------------------#

def loop_tree(filename, var):
    hist = create_histogram(var)

    fopen = ROOT.TFile(filename)
    tree = fopen.Get("EwkNUHM22016__ntuple")
    for event in tree:
        weight = event.eventWeight
        if var == "baselineElectrons_pt":
            baselineElectrons_pt = event.baselineElectrons_pt
            for item in range(0, len(baselineElectrons_pt)):
                hist.Fill(baselineElectrons_pt[item], weight)
        elif var == "baselineElectrons_eta":
            baselineElectrons_eta = event.baselineElectrons_eta
            for item in range(0, len(baselineElectrons_eta)):
                hist.Fill(baselineElectrons_eta[item], weight)
        elif var == "baselineElectrons_phi":
            baselineElectrons_phi = event.baselineElectrons_phi
            for item in range(0, len(baselineElectrons_phi)):
                hist.Fill(baselineElectrons_phi[item], weight)
        elif var == "baselineMuons_pt":
            baselineMuons_pt = event.baselineMuons_pt
            for item in range(0, len(baselineMuons_pt)):
                hist.Fill(baselineMuons_pt[item], weight)
        elif var == "baselineMuons_eta":
            baselineMuons_eta = event.baselineMuons_eta
            for item in range(0, len(baselineMuons_eta)):
                hist.Fill(baselineMuons_eta[item], weight)
        elif var == "baselineMuons_phi":
            baselineMuons_phi = event.baselineMuons_phi
            for item in range(0, len(baselineMuons_phi)):
                hist.Fill(baselineMuons_phi[item], weight)
        elif var == "baselineLeptons_pt":
            baselineLeptons_pt = event.baselineLeptons_pt
            for item in range(0, len(baselineLeptons_pt)):
                hist.Fill(baselineLeptons_pt[item], weight)
        elif var == "baselineLeptons_eta":
            baselineLeptons_eta = event.baselineLeptons_eta
            for item in range(0, len(baselineLeptons_eta)):
                hist.Fill(baselineLeptons_eta[item], weight)
        elif var == "baselineLeptons_phi":
            baselineLeptons_phi = event.baselineLeptons_phi
            for item in range(0, len(baselineLeptons_phi)):
                hist.Fill(baselineLeptons_phi[item], weight)
        elif var == "baselineJets_pt":
            baselineJets_pt = event.baselineJets_pt
            for item in range(0, len(baselineJets_pt)):
                hist.Fill(baselineJets_pt[item], weight)
        elif var == "baselineJets_eta":
            baselineJets_eta = event.baselineJets_eta
            for item in range(0, len(baselineJets_eta)):
                hist.Fill(baselineJets_eta[item], weight)
        elif var == "baselineJets_phi":
            baselineJets_phi = event.baselineJets_phi
            for item in range(0, len(baselineJets_phi)):
                hist.Fill(baselineJets_phi[item], weight)
        elif var == "signalElectrons_pt":
            signalElectrons_pt = event.signalElectrons_pt
            for item in range(0, len(signalElectrons_pt)):
                hist.Fill(signalElectrons_pt[item], weight)
        elif var == "signalElectrons_eta":
            signalElectrons_eta = event.signalElectrons_eta
            for item in range(0, len(signalElectrons_eta)):
                hist.Fill(signalElectrons_eta[item], weight)
        elif var == "signalElectrons_phi":
            signalElectrons_phi = event.signalElectrons_phi
            for item in range(0, len(signalElectrons_phi)):
                hist.Fill(signalElectrons_phi[item], weight)
        elif var == "signalMuons_pt":
            signalMuons_pt = event.signalMuons_pt
            for item in range(0, len(signalMuons_pt)):
                hist.Fill(signalMuons_pt[item], weight)
        elif var == "signalMuons_eta":
            signalMuons_eta = event.signalMuons_eta
            for item in range(0, len(signalMuons_eta)):
                hist.Fill(signalMuons_eta[item], weight)
        elif var == "signalMuons_phi":
            signalMuons_phi = event.signalMuons_phi
            for item in range(0, len(signalMuons_phi)):
                hist.Fill(signalMuons_phi[item], weight)
        elif var == "signalLeptons_pt":
            signalLeptons_pt = event.signalLeptons_pt
            for item in range(0, len(signalLeptons_pt)):
                hist.Fill(signalLeptons_pt[item], weight)
        elif var == "signalLeptons_eta":
            signalLeptons_eta = event.signalLeptons_eta
            for item in range(0, len(signalLeptons_eta)):
                hist.Fill(signalLeptons_eta[item], weight)
        elif var == "signalLeptons_phi":
            signalLeptons_phi = event.signalLeptons_phi
            for item in range(0, len(signalLeptons_phi)):
                hist.Fill(signalLeptons_phi[item], weight)
        elif var == "signalJets_pt":
            signalJets_pt = event.signalJets_pt
            for item in range(0, len(signalJets_pt)):
                hist.Fill(signalJets_pt[item], weight)
        elif var == "signalJets_eta":
            signalJets_eta = event.signalJets_eta
            for item in range(0, len(signalJets_eta)):
                hist.Fill(signalJets_eta[item], weight)
        elif var == "signalJets_phi":
            signalJets_phi = event.signalJets_phi
            for item in range(0, len(signalJets_phi)):
                hist.Fill(signalJets_phi[item], weight)
        elif var == "signalBjets_pt":
            signalBjets_pt = event.signalBjets_pt
            for item in range(0, len(signalBjets_pt)):
                hist.Fill(signalBjets_pt[item], weight)
        elif var == "signalBjets_eta":
            signalBjets_eta = event.signalBjets_eta
            for item in range(0, len(signalBjets_eta)):
                hist.Fill(signalBjets_eta[item], weight)
        elif var == "signalBjets_phi":
            signalBjets_phi = event.signalBjets_phi
            for item in range(0, len(signalBjets_phi)):
                hist.Fill(signalBjets_phi[item], weight)
        elif var == "met":
            met = event.met
            hist.Fill(met, weight)
        elif var == "mc_weight":
            mc_weight = event.mc_weight
            hist.Fill(mc_weight, weight)
        elif var == "nBaselineLeptons":
            nBaselineLeptons = event.nBaselineLeptons
            hist.Fill(nBaselineLeptons, weight)
        elif var == "nSignalLeptons":
            nSignalLeptons = event.nSignalLeptons
            hist.Fill(nSignalLeptons, weight)
        elif var == "nElectrons":
            nElectrons = event.nElectrons
            hist.Fill(nElectrons, weight)
        elif var == "nMuons":
            nMuons = event.nMuons
            hist.Fill(nMuons, weight)
        elif var == "nJets":
            nJets = event.nJets
            hist.Fill(nJets, weight)
        elif var == "nJet30":
            nJet30 = event.nJet30
            hist.Fill(nJet30, weight)
        elif var == "nJet25":
            nJet25 = event.nJet25
            hist.Fill(nJet25, weight)
        elif var == "nBjets":
            nBjets = event.nBjets
            hist.Fill(nBjets, weight)
        elif var == "dphiMin1":
            dphiMin1 = event.dphiMin1
            hist.Fill(dphiMin1, weight)
        elif var == "mT":
            mT = event.mT
            hist.Fill(mT, weight)
        elif var == "mT2":
            mT2 = event.mT2
            if mT2 > 0:
                hist.Fill(mT2, weight)
        elif var == "meffIncl":
            meffIncl = event.meffIncl
            hist.Fill(meffIncl, weight)
        elif var == "HTIncl":
            HTIncl = event.HTIncl
            if HTIncl > 0:
                hist.Fill(HTIncl, weight)
        elif var == "HT30":
            HT30 = event.HT30
            if HT30 > 0:
                hist.Fill(HT30, weight)
        elif var == "HTLep12":
            HTLep12 = event.HTLep12
            hist.Fill(HTLep12, weight)
        elif var == "METOverHT":
            METOverHT = event.METOverHT
            hist.Fill(METOverHT, weight)
        elif var == "METOverHTLep12":
            METOverHTLep12 = event.METOverHTLep12
            hist.Fill(METOverHTLep12, weight)
        elif var == "mll":
            mll = event.mll
            hist.Fill(mll, weight)
        elif var == "pTll":
            pTll = event.pTll
            hist.Fill(pTll, weight)
        elif var == "Rll":
            Rll = event.Rll
            hist.Fill(Rll, weight)
        elif var == "MTauTau":
            MTauTau = event.MTauTau
            hist.Fill(MTauTau, weight)

    return hist

#----------------------------#

def get_variable_list():
    kinematic_vars = ["pt", "eta", "phi"]
    electron_vars = ["Electrons_" + x for x in kinematic_vars]
    muon_vars = ["Muons_" + x for x in kinematic_vars]
    lepton_vars = ["Leptons_" + x for x in kinematic_vars]
    jet_vars = ["Jets_" + x for x in kinematic_vars]
    Bjet_vars = ["Bjets_" + x for x in kinematic_vars]

    baseline_vars = []
    for i in electron_vars, muon_vars, lepton_vars, jet_vars:
        for j in i:
            baseline_vars.append("baseline" + j)

    signal_vars = []
    for i in electron_vars, muon_vars, lepton_vars, jet_vars, Bjet_vars:
        for j in i:
            signal_vars.append("signal" + j)

    variables = baseline_vars + signal_vars + \
                ["met", "mc_weight",
                 "nBaselineLeptons", "nSignalLeptons",
                 "nElectrons", "nMuons",
                 "nJets", "nJet30", "nJet25", "nBjets",
                 "dphiMin1", "mT", "mT2", "meffIncl", "HTIncl", "HT30", "HTLep12",
                 "METOverHT", "METOverHTLep12", "mll", "pTll", "Rll", "MTauTau"]

    return variables

#----------------------------#

def create_histogram(var):
    if "_pt" in var:
        nbins, xmin, xmax = 100, 0, 100
    elif "_eta" in var:
        nbins, xmin, xmax = 60, -3, 3
    elif "_phi" in var:
        nbins, xmin, xmax = 80, -4, 4
    elif "met" in var:
        nbins, xmin, xmax = 100, 0, 500
    elif "mc_weight" in var:
        nbins, xmin, xmax = 50, -0, 5
    elif "Jets_pt" in var or "Bjets_pt" in var:
        nbins, xmin, xmax = 500, 0, 500
    elif "nBaselineLeptons" in var or "nSignalLeptons" in var or "nElectrons" in var or "nMuons" in var:
        nbins, xmin, xmax = 6, 0, 6
    elif "nJets" in var or "nJet30" in var or "nJet25" in var or "nBjets" in var:
        nbins, xmin, xmax = 10, 0, 10
    elif "dphiMin1" in var:
        nbins, xmin, xmax = 50, 0, 5
    elif "mT" in var or "mT2" in var:
        nbins, xmin, xmax = 20, 0, 100
    elif "meffIncl" in var:
        nbins, xmin, xmax = 50, 0, 1000
    elif "HTIncl" in var or "HT30" in var:
        nbins, xmin, xmax = 50, 0, 500
    elif "HTLep12" in var and "METOverHTLep12" not in var:
        nbins, xmin, xmax = 10, 0, 50
    elif "METOverHT" in var and "METOverHTLep12" not in var:
        nbins, xmin, xmax = 50, 0, 5
    elif "METOverHTLep12" in var:
        nbins, xmin, xmax = 5, 0, 50
    elif "mll" in var:
        nbins, xmin, xmax = 100, 0, 50
    elif "pTll" in var:
        nbins, xmin, xmax = 50, 0, 50
    elif "Rll" in var:
        nbins, xmin, xmax = 50, 0, 5
    elif "MTauTau" in var:
        nbins, xmin, xmax = 60, -300, 300

    h1 = ROOT.TH1F("h1_" + var, "", nbins, xmin, xmax)

    return h1

#----------------------------#

def plot_making(var, normalize, h1, h2, h3, h4, h5, h6, h7, h8):
    canvas = ROOT.TCanvas("c","", 800,600)
    canvas.SetLeftMargin(0.12)
    logY = False
    if var in ["HTIncl", "HT30", "HTLep12", "METOverHTLep12", "mll", "mT", "mT2", "MTauTau", "pTll", "Rll"]:
        logY = True
        ROOT.gPad.SetLogy()

    #h1.SetLineColor(ROOT.kOrange)
    #h1.SetFillColor(ROOT.kOrange)
    h1.SetLineColor(ROOT.kGreen+2)
    h1.SetFillColor(ROOT.kGreen+2)
    h1.SetFillStyle(1001) # Solid
    #h2.SetLineColor(ROOT.kOrange-4)
    #h2.SetFillColor(ROOT.kOrange-4)
    h2.SetLineColor(ROOT.kAzure+7)
    h2.SetFillColor(ROOT.kAzure+7)
    h2.SetFillStyle(1001) # Solid
    #h3.SetLineColor(ROOT.kOrange-6)
    #h3.SetFillColor(ROOT.kOrange-6)
    h3.SetLineColor(ROOT.kYellow-9)
    h3.SetFillColor(ROOT.kYellow-9)
    h3.SetFillStyle(1001) # Solid
    #h4.SetLineColor(ROOT.kOrange-8)
    #h4.SetFillColor(ROOT.kOrange-8)
    h4.SetLineColor(17)
    h4.SetFillColor(17)
    h4.SetFillStyle(1001) # Solid

    if normalize:
        integral1 = h1.Integral()
        integral2 = h2.Integral()
        integral3 = h3.Integral()
        integral4 = h4.Integral()

        h1.Scale(1/integral1)
        h2.Scale(1/integral2)
        h3.Scale(1/integral3)
        h4.Scale(1/integral4)

        h1.Scale(integral1 / (integral1+integral2+integral3+integral4) )
        h2.Scale(integral2 / (integral1+integral2+integral3+integral4) )
        h3.Scale(integral3 / (integral1+integral2+integral3+integral4) )
        h4.Scale(integral4 / (integral1+integral2+integral3+integral4) )

    hs = ROOT.THStack()
    hs.Add(h1)
    hs.Add(h2)
    hs.Add(h3)
    hs.Add(h4)
    hs.Draw("hist")

    h5.SetLineColor(ROOT.kBlue)
    h5.SetFillColor(ROOT.kBlue)
    h5.SetFillStyle(0)
    h6.SetLineColor(ROOT.kMagenta)
    h6.SetFillColor(ROOT.kMagenta)
    h6.SetFillStyle(0)
    h7.SetLineColor(ROOT.kRed)
    h7.SetFillColor(ROOT.kRed)
    h7.SetFillStyle(0)
    h8.SetLineColor(ROOT.kGreen)
    h8.SetFillColor(ROOT.kGreen)
    h8.SetFillStyle(0)

    if normalize:
        integral5 = h5.Integral()
        integral6 = h6.Integral()
        integral7 = h7.Integral()
        integral8 = h8.Integral()

        h5.Scale(1/integral5)
        h6.Scale(1/integral6)
        h7.Scale(1/integral7)
        h8.Scale(1/integral8)

        h5.Scale(integral5 / (integral5+integral6+integral7+integral8) )
        h6.Scale(integral6 / (integral5+integral6+integral7+integral8) )
        h7.Scale(integral7 / (integral5+integral6+integral7+integral8) )
        h8.Scale(integral8 / (integral5+integral6+integral7+integral8) )

    hs_nuhm2 = ROOT.THStack()
    hs_nuhm2.Add(h5)
    hs_nuhm2.Add(h6)
    hs_nuhm2.Add(h7)
    hs_nuhm2.Add(h8)

    y_higgsino = h1.GetMaximum() + h2.GetMaximum() + h3.GetMaximum() + h4.GetMaximum()
    y_nuhm2 = h5.GetMaximum() + h6.GetMaximum() + h7.GetMaximum() + h8.GetMaximum()
    y_maximum = max( y_higgsino, y_nuhm2 )

    hs.GetHistogram().SetStats(0)
    # hs.SetTitle(var)

    # X axis
    if "_pt" in var:
        hs.GetHistogram().SetXTitle("p_{T} [GeV]")
    elif "_eta" in var:
        hs.GetHistogram().SetXTitle("#eta")
    elif "_phi" in var:
        hs.GetHistogram().SetXTitle("#phi")
    elif "met" in var:
        hs.GetHistogram().SetXTitle("E_{T}^{miss} [GeV]")
    elif "mT" in var or "mT2" in var or \
         "meffIncl" in var or \
         "HTIncl" in var or "HT30" in var or ("HTLep12" in var and "METOverHTLep12" not in var) or \
         "mll" in var or "pTll" in var or \
         "MTauTau" in var:
        hs.GetHistogram().SetXTitle(var + " [GeV]")
    elif "dphiMin1" in var:
        hs.GetHistogram().SetXTitle("#Delta#phi(E_{T}^{miss}, j_{1})")
    elif "Rll" in var:
        hs.GetHistogram().SetXTitle("#Delta R_{ll}")
    elif "METOverHT" in var or "METOverHTLep12" in var:
        hs.GetHistogram().SetXTitle(var)
    elif "nBaselineLeptons" in var or "nSignalLeptons" in var:
        hs.GetHistogram().SetXTitle("N_{l}")
    elif "nElectrons" in var:
        hs.GetHistogram().SetXTitle("N_{e}")
    elif "nMuons" in var:
        hs.GetHistogram().SetXTitle("N_{#mu}")
    elif "nJets" in var or "nJet30" in var or "nJet25" in var or "nBjets" in var:
        hs.GetHistogram().SetXTitle("N_{jets}")

    # Y axis
    # Y axis
    if normalize is True:
        hs.GetHistogram().SetYTitle("Normalized event counts")
    else:
        hs.GetHistogram().SetYTitle("Events")
    hs.GetHistogram().GetYaxis().SetTitleOffset(1.5)

    if logY is True:
        hs.SetMaximum(y_maximum * 20)
    else:
        if "_eta" in var or "_phi" in var:
            hs.SetMaximum(y_maximum * 2)
        else:
            hs.SetMaximum(y_maximum * 1.2)

    hs.Draw("hist") # re-draw to make the y axis range setting working

    hs_nuhm2.Draw("hist,same,noclear")

    legend = ROOT.TLegend(0.5, 0.6, 0.9, 0.88)
    legend.AddEntry(h1, "Higgsino #tilde{#chi}^{0}_{2}#tilde{#chi}^{0}_{1} m(#tilde{#chi}^{0}_{2},#tilde{#chi}^{0}_{1})=(170,150) GeV", "f")
    legend.AddEntry(h2, "Higgsino #tilde{#chi}^{#pm}_{1}#tilde{#chi}^{#mp}_{1} m(#tilde{#chi}^{0}_{2},#tilde{#chi}^{0}_{1})=(170,150) GeV", "f")
    legend.AddEntry(h3, "Higgsino #tilde{#chi}^{0}_{2}#tilde{#chi}^{+}_{1} m(#tilde{#chi}^{0}_{2},#tilde{#chi}^{0}_{1})=(170,150) GeV", "f")
    legend.AddEntry(h4, "Higgsino #tilde{#chi}^{0}_{2}#tilde{#chi}^{-}_{1} m(#tilde{#chi}^{0}_{2},#tilde{#chi}^{0}_{1})=(170,150) GeV", "f")
    legend.AddEntry(h5, "NUHM2 m_{1/2}=600 GeV #tilde{#chi}^{0}_{2}#tilde{#chi}^{0}_{1}", "l")
    legend.AddEntry(h6, "NUHM2 m_{1/2}=600 GeV #tilde{#chi}^{#pm}_{1}#tilde{#chi}^{#mp}_{1}", "l")
    legend.AddEntry(h7, "NUHM2 m_{1/2}=600 GeV #tilde{#chi}^{0}_{2}#tilde{#chi}^{+}_{1}", "l")
    legend.AddEntry(h8, "NUHM2 m_{1/2}=600 GeV #tilde{#chi}^{0}_{2}#tilde{#chi}^{-}_{1}", "l")

    legend.SetBorderSize(0);
    legend.SetTextFont(42);
    legend.SetTextSize(0.02);
    legend.SetFillColor(0);
    legend.SetFillStyle(0);
    legend.Draw()

    # AtlasStyle.ATLASLabel(0.15, 0.85, "internal", ROOT.kBlack)

    output = var + ".pdf"
    canvas.SaveAs(output)

#----------------------------#

if __name__ == "__main__":
    main()
