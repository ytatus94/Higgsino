#!/usr/bin/python
'''
List branching ratio in SLHA or SusyHit files.
'''
import os

path_slha = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/ytHiggsinoAnalysis/misc/NUHM2/share/DSID394xxx/"
path_susyhit = "/Users/ytshen/Documents/Working/OU/HEP/MikeHance/"

def main():
    # sum_BR()
    list_branching_ratio("slha")
    list_branching_ratio("susyhit")

    # for m12 in 300, 350, 400, 500, 600, 700, 800:
    #     for decay in "N2N1", "C1C1", "N2C1p", "N2C1m":
    #         file_name = "NUHM2_m12_" + str(m12) + "_weak_" + decay + ".slha"
            # print file_name

#----------------------------#

def list_branching_ratio(input_file):
    if input_file is "slha":
        for file in sorted( os.listdir(path_slha) ):
            if file.startswith("susy") and file.endswith(".slha"): # for .slha
                print file
                # .slha
                if "N2" in file:
                    print "BR(N2->llN1)=", get_branching_ratio(input_file, path_slha + file, "N2")
                if "C1p" in file or "C1m" in file:
                    print "BR(C1+/- ->ffN1)=", get_branching_ratio(input_file, path_slha + file, "C1ffN1")
                if "C1C1" in file:
                    print "BR(C1->lvlN1)=", get_branching_ratio(input_file, path_slha + file, "C1lvlN1")
    elif input_file is "susyhit":
        for file in sorted( os.listdir(path_susyhit) ):
            if file.startswith("susyhit_slha.") and file.endswith(".out"): # for .out
                print file
                # susyhit_slha.*.out
                print "BR(N2->llN1)=", get_branching_ratio(input_file, path_susyhit + file, "N2")
                print "BR(C1+/- ->ffN1)=", get_branching_ratio(input_file, path_susyhit + file, "C1ffN1")
                print "BR(C1->lvlN1)=", get_branching_ratio(input_file, path_susyhit + file, "C1lvlN1")

#----------------------------#

def get_slha_file(m12, decay):
    for file in sorted( os.listdir(path_slha) ):
        if file.startswith("susy") and file.endswith(".slha"):
            if str(m12) in file and decay in file:
                print file

#----------------------------#

def get_branching_ratio(input_file, file, decay):
    decay_string = ""
    if decay is "N2":
        if input_file is "slha":
            decay_string = "# Z2SS  decays" # for .slha
        elif input_file is "susyhit":
            decay_string = "# neutralino2 decays" # for .out
    elif decay is "C1ffN1" or decay is "C1lvlN1":
        if input_file is "slha":
            decay_string = "# W1SS+ decays" # for .slha
        elif input_file is "susyhit":
            decay_string = "# chargino1+ decays" # for .out

    with open(file) as fopen:
        lines = fopen.readlines()
        read_buffer = False
        total = 0
        for line in lines:
            if input_file is "slha":
                if decay_string in line:
                    read_buffer = True
                elif "#         PDG         Width" in line: # for .slha
                    read_buffer = False

                if read_buffer:
                    if (decay is "N2" and ("# Z2SS   -->  Z1SS   E-     E+" in line or
                                           "# Z2SS   -->  Z1SS   MU-    MU+" in line or
                                           "# Z2SS   -->  Z1SS   TAU-   TAU+" in line ) ): # for .slha
                        BR = line.split()
                        total += float( BR[0] )
                    elif (decay is "C1ffN1" and ("# W1SS+  -->  Z1SS   UP     DB" in line or
                                                 "# W1SS+  -->  Z1SS   CH     SB" in line ) ): # for .slha
                        BR = line.split()
                        total += float( BR[0] )
                    elif (decay is "C1lvlN1" and ("# W1SS+  -->  Z1SS   E+     NUE" in line or
                                                  "# W1SS+  -->  Z1SS   MU+    NUM" in line or
                                                  "# W1SS+  -->  Z1SS   TAU+   NUT" in line) ): # for .slha
                        BR = line.split()
                        total += float( BR[0] )
            elif input_file is "susyhit":
                if decay_string in line:
                    read_buffer = True
                elif "#         PDG            Width" in line: # for .out
                    read_buffer = False

                if read_buffer:
                    if (decay is "N2" and ("# BR(~chi_20 -> ~chi_10 e+      e-)" in line or
                                           "# BR(~chi_20 -> ~chi_10 mu+     mu-)" in line or
                                           "# BR(~chi_20 -> ~chi_10 tau+    tau-)" in line ) ): # for .out
                        BR = line.split()
                        total += float( BR[0] )
                    elif (decay is "C1ffN1" and ("# BR(~chi_1+ -> ~chi_10 u    db)" in line or
                                                 "# BR(~chi_1+ -> ~chi_10 c    sb)" in line ) ): # for .out
                        BR = line.split()
                        total += float( BR[0] )
                    elif (decay is "C1lvlN1" and ("# BR(~chi_1+ -> ~chi_10 e+   nu_e)" in line or
                                                  "# BR(~chi_1+ -> ~chi_10 mu+  nu_mu)" in line or
                                                  "# BR(~chi_1+ -> ~chi_10 tau+ nu_tau)" in line) ): # for .out
                        BR = line.split()
                        total += float( BR[0] )
        return total

#----------------------------#

def sum_BR():
    # file_to_open = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/test_mg5/run_02a/susy.370621.NUHM2_m12_600.slha"
    file_to_open = "/Users/ytshen/Documents/Working/OU/HEP/Abe/WeakSLHA/susy.370621.NUHM2_m12_600.slha"
    with open(file_to_open) as fopen:
        lines = fopen.readlines()
        N2_decay_block = False
        block_on_str = "DECAY   1000023  4.02875366E-06   # Z2SS  decays"
        block_off_str = "DECAY   1000025  2.02629805E-01   # Z3SS  decays"
        total = 0
        for line in lines:
            if block_on_str in line:
                N2_decay_block = True
            if block_off_str in line:
                N2_decay_block = False
            if N2_decay_block is True:
                if "DECAY" not in line and "BR" not in line and "PDG" not in line:
                    list = line.split()
                    # print float(list[0])
                    total += float(list[0])

        print total

#----------------------------#

if __name__ == '__main__':
    main()
