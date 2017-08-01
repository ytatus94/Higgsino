#!/usr/bin/python

import os, ROOT

path = "/UserDisk2/yushen/Higgsino/"
dirs = ["SusySkimHiggsino_v1.8_SUSY16_Signal_tree", "SusySkimHiggsino_v1.8_SUSY16_Bkgs_tree"]

for dir in dirs:
    for rootfile in sorted( os.listdir(path + dir) ):
        if rootfile.endswith("_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root"):
            print rootfile
            fo = ROOT.TFile(path + dir + "/" + rootfile)
            # fo.ls()
            print fo.GetListOfKeys().At(0).GetName()
