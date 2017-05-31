#!/usr/bin/python

import os, ROOT

path = "/afs/cern.ch/work/y/yushen/private/Higgsino/Cutflow/Results/"

for directory in sorted(os.listdir(path)):
    for file in sorted(os.listdir(path + directory)):
        if file.startswith("hist-SusySkimHiggsino_v1.4_SUSY16_") and file.endswith("root"):
            print directory + "/" + file
            fopen = ROOT.TFile(path + directory + "/" + file)
            h_yields = fopen.Get("h_yields")
            h_weighted_yields = fopen.Get("h_weighted_yields")
            if "Signal_tree" in file:
                print h_yields.GetBinContent(2)
                print h_weighted_yields.GetBinContent(2)
            elif "Bkgs_tree" in file:
                print h_yields.GetBinContent(3)
                print h_weighted_yields.GetBinContent(3)
