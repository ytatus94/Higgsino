#!/usr/bin/bash
import os

path = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/ytHiggsinoAnalysis/misc/NUHM2/share/DSID394xxx/"

for slha in sorted( os.listdir(path) ):
    if slha.startswith("susy.") and slha.endswith(".slha"):
        m12 = slha[slha.find("m12_") + len("m12_"): slha.find(".slha")]
        with open(path + slha) as fopen:
            read_buff = False
            N1_mass, N2_mass = 0., 0.
            for line in fopen.readlines():
                if "Block MASS   # Scalar and gaugino mass spectrum" in line:
                    read_buff = True
                elif "Block ALPHA   # Effective Higgs mixing parameter" in line:
                    read_buff = False
                if read_buff is True and "#  z1ss" in line:
                    N1_mass = abs( float( (line.split())[1] ) )
                elif read_buff is True and "#  z2ss" in line:
                    N2_mass = abs( float( (line.split())[1] ) )
            print m12, N2_mass, N1_mass, N2_mass - N1_mass
