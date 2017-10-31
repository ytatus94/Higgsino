#!/usr/bin/bash
import os

path = "../misc/NUHM2/share/DSID394xxx/"

def main():
    get_mass_difference()

#----------------------------#

def get_mass_difference():
    '''
    List the mass of N2, N1, C1, and the mass difference N2-N1 and
    the mass difference ratio (N2-N1) / (C1-N1) of NUHM2
    '''
    print "{0:<5} & {1:<10} & {2:<10} & {3:<10} & {4:<10} & {5:<10}".format("m12", "m(N2)", "m(N1)", "m(C1)", "m(N2)-m(N1)", "[m(N2)-m(N1)]/[m(C1)-m(N1)]")
    output_list = []
    for slha in sorted( os.listdir(path) ):
        if slha.startswith("susy.") and slha.endswith(".slha"):
            m12 = slha[slha.find("m12_") + len("m12_"): slha.find("_weak_")]
            decay = slha[slha.find("_weak_") + len("_weak_"): slha.find(".slha")]
            with open(path + slha) as fopen:
                read_buff = False
                N1_mass, N2_mass, C1_mass = 0., 0., 0.
                dict = {'m12':0, 'decay':0, 'm(N2)':0, 'm(N1)':0, 'm(C1)':0, 'dM=m(N2)-m(N1)':0, 'm(C1)-m(N1)':0, '(N2-N1)/(C1-N1)':0}
                for line in fopen.readlines():
                    if "Block MASS   # Scalar and gaugino mass spectrum" in line:
                        read_buff = True
                    elif "Block ALPHA   # Effective Higgs mixing parameter" in line:
                        read_buff = False
                    if read_buff is True and "#  z1ss" in line:
                        N1_mass = abs( float( (line.split())[1] ) )
                    elif read_buff is True and "#  z2ss" in line:
                        N2_mass = abs( float( (line.split())[1] ) )
                    elif read_buff is True and "#  w1ss" in line:
                        C1_mass = abs( float( (line.split())[1] ) )
                # if ratio is False:
                dict['m12'] = m12
                dict['decay'] = decay
                dict['m(N2)'] = N2_mass
                dict['m(N1)'] = N1_mass
                dict['m(C1)'] = C1_mass
                dict['dM=m(N2)-m(N1)'] = N2_mass - N1_mass
                dict['m(C1)-m(N1)'] = C1_mass - N1_mass
                dict['(N2-N1)/(C1-N1)'] = (N2_mass - N1_mass) / (C1_mass - N1_mass)
                output_list.append(dict)

    for item in range(0, len(output_list), 4):
        print "{0:<5} & {1:<10.6f} & {2:<10.6f} & {3:<10.6f} & {4:<10.6f} & {5:<10.6f}".format(output_list[item]['m12'],
                                                                                               output_list[item]['m(N2)'],
                                                                                               output_list[item]['m(N1)'],
                                                                                               output_list[item]['m(C1)'],
                                                                                               output_list[item]['dM=m(N2)-m(N1)'],
                                                                                               output_list[item]['(N2-N1)/(C1-N1)'])

#----------------------------#

if __name__ == '__main__':
    main()
