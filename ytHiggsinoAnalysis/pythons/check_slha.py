#!/usr/bin/python
import os, filecmp

path1 = "/Users/ytshen/Documents/Working/OU/HEP/Abe/WeakSHLA/"
path2 = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/ytHiggsinoAnalysis/misc/NUHM2/share/DSID394xxx/"

for slha in sorted( os.listdir(path1) ):
    if slha.startswith("susy.") and slha.endswith(".slha"):
        m12 = slha[slha.find("m12_") + len("m12_"): slha.find(".slha")]
        print m12
        for slha_new in sorted( os.listdir(path2) ):
            if m12 in slha_new and slha_new.startswith("susy.") and slha.endswith(".slha"):
               print "Compare: " + slha + " and " + slha_new, filecmp.cmp(path1 + slha, path2 + slha_new)
