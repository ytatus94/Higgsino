#!/usr/bin/python

Higgsino_Xsec_file = "../misc/MGPy8EG_A14N23LO_Higgsino_2L.txt"
NUHM2_Xsec_file = "../misc/NUHM2_Weak_SUSYTools.txt"

def main():
    # a = get_line_Higgsino("N2N1_170_150")
    # get_XS_Higgsino(a)
    # get_BF_Higgsino(a)
    # get_FilterEff_Higgsino(a)
    get_XS_NUHM2(370621, 112)

#----------------------------#

#----------------------------#

def get_line_Higgsino(note):
    '''
    return a list which contains
    ['datasetID', 'finalState', 'XS', 'BF', 'Filter Eff', 'relUncertainty', 'Note', 'MG sigma [pb]']
    '''
    with open(Higgsino_Xsec_file) as fopen:
        lines = fopen.readlines()
        for line in lines:
            if line[0] is not "#":
                list = line.split()
                if list[7] == note:
                    return list

#----------------------------#

def get_XS_Higgsino(list):
    return float(list[2])

#----------------------------#

def get_BF_Higgsino(list):
    return float(list[3])

#----------------------------#

def get_FilterEff_Higgsino(list):
    return float(list[4])

#----------------------------#

def get_XS_NUHM2(dsid, fs):
    with open(NUHM2_Xsec_file) as fopen:
        lines = fopen.readlines()
        for line in lines:
            list = line.split()
            if list[0] != "SAMPLE":
                if str(dsid) in list[0] and float(list[1]) == fs:
                    return float(list[2])

#----------------------------#

#----------------------------#

if __name__ == "__main__":
    main()