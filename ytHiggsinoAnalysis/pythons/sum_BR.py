#!/usr/bin/python

def main():
  sum_BR()

#----------------------------#

def sum_BR():
    # file_to_open = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/test_mg5/run_02a/susy.370621.NUHM2_m12_600.slha"
    file_to_open = "/Users/ytshen/Documents/Working/OU/HEP/Abe/WeakSHLA/susy.370621.NUHM2_m12_600.slha"
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
