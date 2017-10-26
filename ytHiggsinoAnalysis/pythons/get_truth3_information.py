#!/usr/bin/python
import os, subprocess

def main():
    print "Weighted events"
    get_truth3_weighted_events()
    print "\n"

    # run on lxplus only
    print "Efficiency"
    get_ami_efficiency()
    print "\n"

    print "cross-section"
    get_slha_Xsec()
    print "\n"

    print "Branching ratio"
    get_susyhit_br()
    print "\n"

#----------------------------#

def get_truth3_weighted_events():
    path = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170926b/"
    m12 = [300, 350, 400, 500, 600, 700, 800]
    decays = ["N2N1", "C1C1", "N2C1p", "N2C1m"]
    print "{0:<5} & {1:<9} & {2:<9} & {3:<9} & {4:<9}".format("m12", "N2N1", "C1C1", "N2C1p", "N2C1m")
    for i in m12:
        # print i,
        weighted_events = []
        for j in decays:
            filename = "NUHM2_m12_" + str(i) + "_" + j + ".txt"
            with open(path + filename) as fopen:
                lines = fopen.readlines()
                for line in lines:
                    list = line.split(",")
                    if list[0] == "EwkNUHM22016__All":
                        weighted_events.append( float(list[2]) )
        print "{0:<5} & {1:<9.2f} & {2:<9.2f} & {3:<9.2f} & {4:<9.2f}".format(i, weighted_events[0], weighted_events[1], weighted_events[2], weighted_events[3])
    
#----------------------------#

def get_ami_efficiency():
    print "{0:<5} & {1:<9} & {2:<9} & {3:<9} & {4:<9}".format("m12", "N2N1", "C1C1", "N2C1p", "N2C1m")
    for m12 in 300, 350, 400, 500, 600, 700, 800:
        filter_eff = []
        for decay in "N2N1", "C1C1", "N2C1p", "N2C1m":
            filename = ""
            dsid = 0
            e_tag = "e6233" # default
            if m12 == 300:
                if decay == "C1C1":
                    dsid = 394301
                elif decay == "N2C1m":
                    dsid = 394302
                elif decay == "N2C1p":
                    dsid = 394303
                elif decay == "N2N1":
                    dsid = 394304
            elif m12 == 350:
                if decay == "C1C1":
                    dsid = 394305
                elif decay == "N2C1m":
                    dsid = 394306
                elif decay == "N2C1p":
                    dsid = 394307
                elif decay == "N2N1":
                    dsid = 394308
            elif m12 == 400:
                if decay == "C1C1":
                    dsid = 394309
                elif decay == "N2C1m":
                    dsid = 394310
                elif decay == "N2C1p":
                    dsid = 394311
                elif decay == "N2N1":
                    dsid = 394312
            elif m12 == 500:
                if decay == "C1C1":
                    dsid = 394313
                    e_tag = "e6241"
                elif decay == "N2C1m":
                    dsid = 394314
                elif decay == "N2C1p":
                    dsid = 394315
                elif decay == "N2N1":
                    dsid = 394316
            elif m12 == 600:
                if decay == "C1C1":
                    dsid = 394317
                    e_tag = "e6241"
                elif decay == "N2C1m":
                    dsid = 394318
                elif decay == "N2C1p":
                    dsid = 394319
                elif decay == "N2N1":
                    dsid = 394320
            elif m12 == 700:
                if decay == "C1C1":
                    dsid = 394321
                elif decay == "N2C1m":
                    dsid = 394322
                elif decay == "N2C1p":
                    dsid = 394323
                elif decay == "N2N1":
                    dsid = 394324
            elif m12 == 800:
                if decay == "C1C1":
                    dsid = 394325
                elif decay == "N2C1m":
                    dsid = 394326
                elif decay == "N2C1p":
                    dsid = 394327
                elif decay == "N2N1":
                    dsid = 394328
            filename = "mc15_13TeV." + str(dsid) + ".MGPy8EG_A14N23LO_NUHM2_m12_" + str(m12) + "_weak_" + decay + "_2LMET50_MadSpin.evgen.EVNT." + e_tag
            command_eff = "ami show dataset info " + filename + " | grep GenFiltEff_mean"
            proc = subprocess.Popen([command_eff], stdout=subprocess.PIPE, shell=True)
            out = proc.stdout.read()
            eff = float( out.split(":")[1] )
            filter_eff.append(eff)
        print "{0:<5} & {1:<9.6f} & {2:<9.6f} & {3:<9.6f} & {4:<9.6f}".format(m12, filter_eff[0], filter_eff[1], filter_eff[2], filter_eff[3])

#----------------------------#

def get_slha_Xsec():
    print "{0:<5} & {1:<12} & {2:<12} & {3:<12} & {4:<12}".format("m12", "N2N1", "C1C1", "N2C1p", "N2C1m")
    for dsid in 370617, 370618, 370619, 370620, 370621, 370622, 370623: # 300, 350, 400, 500, 600, 700, 800
        m12 = 0
        if dsid == 370617:
            m12 = 300
        elif dsid == 370618:
            m12 = 350
        elif dsid == 370619:
            m12 = 400
        elif dsid == 370620:
            m12 = 500
        elif dsid == 370621:
            m12 = 600
        elif dsid == 370622:
            m12 = 700
        elif dsid == 370623:
            m12 = 800

        cross_section = []
        for fs in 112, 157, 125, 127: # 112: N2N1, 125: N2C1p, 127: N2C1m, 157: C1C1
            cross_section.append( get_XS_NUHM2(dsid, fs) )
        print "{0:<5} & {1:<12.10f} & {2:<12.10f} & {3:<12.10f} & {4:<12.10f}".format(m12, cross_section[0], cross_section[1], cross_section[2], cross_section[3])

#----------------------------#

# copy from read_Xsec.py
def get_XS_NUHM2(dsid, fs):
    NUHM2_Xsec_file = "../misc/NUHM2_Weak_SUSYTools.txt"
    with open(NUHM2_Xsec_file) as fopen:
        lines = fopen.readlines()
        for line in lines:
            list = line.split()
            if list[0] != "SAMPLE":
                if str(dsid) in list[0] and float(list[1]) == fs:
                    return float(list[2])

#----------------------------#

def get_susyhit_br():
    path_susyhit = "/Users/ytshen/Documents/Working/OU/HEP/MikeHance/"
    print "{0:<5} & {1:<12} & {2:<16} & {3:<12}".format("m12", "BR(N2->llN1)", "BR(C1+/- ->ffN1)", "BR(C1->lvlN1)")
    for file in sorted( os.listdir(path_susyhit) ):
        if file.startswith("susyhit_slha.") and file.endswith(".out"):
            m12 = 0
            if "370617" in file:
                m12 = 300
            elif "370618" in file:
                m12 = 350
            elif "370619" in file:
                m12 = 400
            elif "370620" in file:
                m12 = 500
            elif "370621" in file:
                m12 = 600
            elif "370622" in file:
                m12 = 700
            elif "370623" in file:
                m12 = 800
            
            branching_ratio = []
            for decay in "N2", "C1ffN1", "C1lvlN1":
                branching_ratio.append( get_branching_ratio(path_susyhit + file, decay) )

            print "{0:<5} & {1:<12.10f} & {2:<16.2f} & {3:<12.10f}".format(m12, branching_ratio[0], branching_ratio[1], branching_ratio[2])

#----------------------------#

# copy from BR_calculation.py and modify it
def get_branching_ratio(file, decay):
    decay_string = ""
    if decay is "N2":
        decay_string = "# neutralino2 decays"
    elif decay is "C1ffN1" or decay is "C1lvlN1":
        decay_string = "# chargino1+ decays"

    with open(file) as fopen:
        lines = fopen.readlines()
        read_buffer = False
        total = 0
        for line in lines:
            if decay_string in line:
                read_buffer = True
            elif "#         PDG            Width" in line:
                read_buffer = False

            if read_buffer:
                if (decay is "N2" and ("# BR(~chi_20 -> ~chi_10 e+      e-)" in line or
                                       "# BR(~chi_20 -> ~chi_10 mu+     mu-)" in line or
                                       "# BR(~chi_20 -> ~chi_10 tau+    tau-)" in line ) ):
                    BR = line.split()
                    total += float( BR[0] )
                elif (decay is "C1ffN1" and ("# BR(~chi_1+ -> ~chi_10 u    db)" in line or
                                             "# BR(~chi_1+ -> ~chi_10 c    sb)" in line or
                                             "# BR(~chi_1+ -> ~chi_10 e+   nu_e)" in line or
                                              "# BR(~chi_1+ -> ~chi_10 mu+  nu_mu)" in line or
                                              "# BR(~chi_1+ -> ~chi_10 tau+ nu_tau)" in line) ):
                    BR = line.split()
                    total += float( BR[0] )
                elif (decay is "C1lvlN1" and ("# BR(~chi_1+ -> ~chi_10 e+   nu_e)" in line or
                                              "# BR(~chi_1+ -> ~chi_10 mu+  nu_mu)" in line or
                                              "# BR(~chi_1+ -> ~chi_10 tau+ nu_tau)" in line) ):
                    BR = line.split()
                    total += float( BR[0] )
        return total

#----------------------------#

if __name__ == "__main__":
    main()
