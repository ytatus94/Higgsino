#!/usr/bin/python

import os, ROOT

path = "/afs/cern.ch/work/y/yushen/private/Higgsino/Cutflow/Results/"

def main():
    for directory in sorted(os.listdir(path)):
        # if directory.startswith("optimization_MC_MGPy8EG_A14N23LO_NUHM2_m12_"):
        if directory.startswith("optimization_"):
            for file in sorted(os.listdir(path + directory)):
                if file.startswith("hist-SusySkimHiggsino_v1.6_SUSY16_") and file.endswith("root"):
                    # print directory + "/" + file
                    name = get_sample_name(directory)
                    yields, weighted_yields = get_yields(path + directory + "/" + file)
                    print name, yields, weighted_yields



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



def get_yields(file):
    fopen = ROOT.TFile(file)
    h_yields = fopen.Get("h_yields")
    h_weighted_yields = fopen.Get("h_weighted_yields")
    if "Signal_tree" in file:
        # We use h_yields->Fill(2) so it is bin3
        yields = h_yields.GetBinContent(3)
        weighted_yields = h_weighted_yields.GetBinContent(3)
    elif "Bkgs_tree" in file:
        # We use h_yields->Fill(3) so it is bin4
        yields = h_yields.GetBinContent(4)
        weighted_yields = h_weighted_yields.GetBinContent(4)
    return yields, weighted_yields



if __name__ == "__main__":
    main()
