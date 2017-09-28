#!/usr/bin/python
'''
List the tree name in the common ntuples.
'''
import os, ROOT

# path = "/UserDisk2/yushen/Higgsino/"
path = "../../../MC/"
dirs = ["SusySkimHiggsino_v1.9_SUSY16_Signal_tree", "SusySkimHiggsino_v1.9_SUSY16_Bkgs_tree", "SusySkimHiggsino_v1.9b_SUSY16_Signal_NUHM2_tree"]

for dir in dirs:
    for rootfile in sorted( os.listdir(path + dir) ):
        if rootfile.endswith("_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root") or rootfile.endswith("_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root"):
            print rootfile
            fo = ROOT.TFile(path + dir + "/" + rootfile)
            # fo.ls()
            print fo.GetListOfKeys().At(0).GetName()
