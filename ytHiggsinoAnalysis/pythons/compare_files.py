#!/usr/bin/python
import os, filecmp

def main():
	check_slha()
	check_results()

#----------------------------#

def check_slha():
    '''
    Compare the SLHA files in two different folders.
    '''
    path1 = "/Users/ytshen/Documents/Working/OU/HEP/Abe/WeakSLHA/"
    path2 = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/ytHiggsinoAnalysis/misc/NUHM2/share/DSID394xxx/"

    for slha in sorted( os.listdir(path1) ):
        if slha.startswith("susy.") and slha.endswith(".slha"):
            m12 = slha[slha.find("m12_") + len("m12_"): slha.find(".slha")]
            # print m12
            for slha_new in sorted( os.listdir(path2) ):
                if m12 in slha_new and slha_new.startswith("susy.") and slha.endswith(".slha"):
                   # print "Compare: " + slha + " and " + slha_new, filecmp.cmp(path1 + slha, path2 + slha_new)
                    bool = filecmp.cmp(path1 + slha, path2 + slha_new)
                    if bool is False:
                        print "In " + m12 + ", compare: " + slha + " and " + slha_new + " are different."


#----------------------------#

def check_results():
    path1 = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/Results/20170817/"
    path2 = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/20170817/"

    for file in sorted( os.listdir(path1) ):
        bool = filecmp.cmp(path1 + file, path2 + file)
        # print bool
        if bool is False:
            print file + " in " + path1 + " and " + path2 + " are different."

#----------------------------#

if __name__ == '__main__':
    main()