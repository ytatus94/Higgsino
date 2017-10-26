#!/usr/bin/python

import os, ROOT

path = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/cutflow_results/20170927/"

def main():
    for directory in sorted(os.listdir(path)):
        # if directory.startswith("optimization_MC_MGPy8EG_A14N23LO_NUHM2_m12_"):
        if directory.startswith("optimization_"):
            for file in sorted(os.listdir(path + directory)):
                if file.startswith("hist-SusySkimHiggsino_v1.") and file.endswith("root"):
                    # print directory + "/" + file
                    name = get_sample_name(directory)
                    yields, weighted_yields = get_yields(path + directory + "/" + file)
                    print name, "yields=", yields, "weighted_yields=", weighted_yields
                    SRee, SRmm, SRSF, weighted_SRee, weighted_SRmm, weighted_SRSF = get_SRee_SRmm_SRSF(path + directory + "/" + file)
                    print "SRee:", SRee
                    print "SRmm:", SRmm
                    print "SRSF:", SRSF
                    print "weighted_SRee:", weighted_SRee
                    print "weighted_SRmm:", weighted_SRmm
                    print "weighted_SRSF:", weighted_SRSF

#----------------------------#

def get_sample_name(file):
    index1 = file.find("_MC_") + len("_MC_")
    index2 = file.find("_SusySkimHiggsino_")
    name = file[index1 : index2]
    if "NUHM2" in name:
        index3 = name.find("NUHM2_m12")
        index4 = name.find("_weak")
        temp = name[index3 : index4]
        name = temp
    return name

#----------------------------#

def get_yields(file):
    fopen = ROOT.TFile(file)
    h_yields = fopen.Get("h_yields")
    h_weighted_yields = fopen.Get("h_weighted_yields")
    if "Signal_tree" in file or "Signal_NUHM2_tree" in file:
        # We use h_yields->Fill(2) so it is bin3
        yields = h_yields.GetBinContent(3)
        weighted_yields = h_weighted_yields.GetBinContent(3)
    elif "Bkgs_tree" in file:
        # We use h_yields->Fill(3) so it is bin4
        yields = h_yields.GetBinContent(4)
        weighted_yields = h_weighted_yields.GetBinContent(4)
    return yields, weighted_yields

#----------------------------#

def get_SRee_SRmm_SRSF(file):
    fopen = ROOT.TFile(file)
    h_yields_SRee = fopen.Get("h_yields_SRee")
    h_yields_SRmm = fopen.Get("h_yields_SRmm")
    h_yields_SRSF = fopen.Get("h_yields_SRSF")
    h_weighted_yields_SRee = fopen.Get("h_weighted_yields_SRee")
    h_weighted_yields_SRmm = fopen.Get("h_weighted_yields_SRmm")
    h_weighted_yields_SRSF = fopen.Get("h_weighted_yields_SRSF")
    SRee = []
    SRmm = []
    SRSF = []
    weighted_SRee = []
    weighted_SRmm = []
    weighted_SRSF = []
    if "Signal_tree" in file:
        SRee.append(h_yields_SRee.GetBinContent(22)) # h->Fill(21) is bin22
        SRee.append(h_yields_SRee.GetBinContent(23))
        SRee.append(h_yields_SRee.GetBinContent(24))
        SRee.append(h_yields_SRee.GetBinContent(25))
        SRee.append(h_yields_SRee.GetBinContent(26))
        SRee.append(h_yields_SRee.GetBinContent(27))
        SRee.append(h_yields_SRee.GetBinContent(28))
        SRmm.append(h_yields_SRmm.GetBinContent(22)) # h->Fill(21) is bin22
        SRmm.append(h_yields_SRmm.GetBinContent(23))
        SRmm.append(h_yields_SRmm.GetBinContent(24))
        SRmm.append(h_yields_SRmm.GetBinContent(25))
        SRmm.append(h_yields_SRmm.GetBinContent(26))
        SRmm.append(h_yields_SRmm.GetBinContent(27))
        SRmm.append(h_yields_SRmm.GetBinContent(28))
        SRSF.append(h_yields_SRSF.GetBinContent(22)) # h->Fill(21) is bin22
        SRSF.append(h_yields_SRSF.GetBinContent(23))
        SRSF.append(h_yields_SRSF.GetBinContent(24))
        SRSF.append(h_yields_SRSF.GetBinContent(25))
        SRSF.append(h_yields_SRSF.GetBinContent(26))
        SRSF.append(h_yields_SRSF.GetBinContent(27))
        SRSF.append(h_yields_SRSF.GetBinContent(28))

        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(22)) # h->Fill(21) is bin22
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(23))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(24))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(25))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(26))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(27))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(28))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(22)) # h->Fill(21) is bin22
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(23))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(24))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(25))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(26))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(27))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(28))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(22)) # h->Fill(21) is bin22
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(23))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(24))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(25))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(26))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(27))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(28))
    elif "Bkgs_tree" in file:
        SRee.append(h_yields_SRee.GetBinContent(32)) # h->Fill(31) is bin32
        SRee.append(h_yields_SRee.GetBinContent(33))
        SRee.append(h_yields_SRee.GetBinContent(34))
        SRee.append(h_yields_SRee.GetBinContent(35))
        SRee.append(h_yields_SRee.GetBinContent(36))
        SRee.append(h_yields_SRee.GetBinContent(37))
        SRee.append(h_yields_SRee.GetBinContent(38))
        SRmm.append(h_yields_SRmm.GetBinContent(32)) # h->Fill(31) is bin32
        SRmm.append(h_yields_SRmm.GetBinContent(33))
        SRmm.append(h_yields_SRmm.GetBinContent(34))
        SRmm.append(h_yields_SRmm.GetBinContent(35))
        SRmm.append(h_yields_SRmm.GetBinContent(36))
        SRmm.append(h_yields_SRmm.GetBinContent(37))
        SRmm.append(h_yields_SRmm.GetBinContent(38))
        SRSF.append(h_yields_SRSF.GetBinContent(32)) # h->Fill(31) is bin32
        SRSF.append(h_yields_SRSF.GetBinContent(33))
        SRSF.append(h_yields_SRSF.GetBinContent(34))
        SRSF.append(h_yields_SRSF.GetBinContent(35))
        SRSF.append(h_yields_SRSF.GetBinContent(36))
        SRSF.append(h_yields_SRSF.GetBinContent(37))
        SRSF.append(h_yields_SRSF.GetBinContent(38))

        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(32)) # h->Fill(31) is bin32
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(33))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(34))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(35))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(36))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(37))
        weighted_SRee.append(h_weighted_yields_SRee.GetBinContent(38))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(32)) # h->Fill(31) is bin32
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(33))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(34))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(35))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(36))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(37))
        weighted_SRmm.append(h_weighted_yields_SRmm.GetBinContent(38))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(32)) # h->Fill(31) is bin32
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(33))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(34))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(35))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(36))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(37))
        weighted_SRSF.append(h_weighted_yields_SRSF.GetBinContent(38))

    return SRee, SRmm, SRSF, weighted_SRee, weighted_SRmm, weighted_SRSF

#----------------------------#

if __name__ == "__main__":
    main()
