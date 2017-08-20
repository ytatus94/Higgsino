#!/usr/bin/python

Higgsino_Xsec_file = "../misc/MGPy8EG_A14N23LO_Higgsino_2L.txt"
NUHM2_Xsec_file = "../misc/NUHM2_Weak_SUSYTools.txt"

def main():
    # a = get_line_Higgsino("N2N1_170_150")
    # print get_XS_Higgsino(a)
    # print get_BF_Higgsino(a)
    # print get_FilterEff_Higgsino(a)
    # print get_XS_NUHM2(370621, 112)
    print "N2N1:"
    cross_section_ratio("N2N1_160_100", 350)
    cross_section_ratio("N2N1_190_150", 400)
    cross_section_ratio("N2N1_190_150", 500)
    cross_section_ratio("N2N1_190_150", 600)
    cross_section_ratio("N2N1_170_150", 700)
    cross_section_ratio("N2N1_170_150", 800)

    print "C1C1:"
    cross_section_ratio("C1C1_160_100", 350)
    cross_section_ratio("C1C1_190_150", 400)
    cross_section_ratio("C1C1_190_150", 500)
    cross_section_ratio("C1C1_190_150", 600)
    cross_section_ratio("C1C1_170_150", 700)
    cross_section_ratio("C1C1_170_150", 800)

    print "N2C1p:"
    cross_section_ratio("N2C1p_160_100", 350)
    cross_section_ratio("N2C1p_190_150", 400)
    cross_section_ratio("N2C1p_190_150", 500)
    cross_section_ratio("N2C1p_190_150", 600)
    cross_section_ratio("N2C1p_170_150", 700)
    cross_section_ratio("N2C1p_170_150", 800)

    print "N2C1m:"
    cross_section_ratio("N2C1m_160_100", 350)
    cross_section_ratio("N2C1m_190_150", 400)
    cross_section_ratio("N2C1m_190_150", 500)
    cross_section_ratio("N2C1m_190_150", 600)
    cross_section_ratio("N2C1m_170_150", 700)
    cross_section_ratio("N2C1m_170_150", 800)

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
                list = line.split() # The 6th element is "#"
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

def cross_section_ratio(note, m12):
    a = get_line_Higgsino(note)
    Xsec_Higgsino = get_XS_Higgsino(a)
    # print Xsec_Higgsino

    # dsid = {m12: dsid}
    dsid = {300: 370617,
            350: 370618,
            400: 370619,
            500: 370620,
            600: 370621,
            700: 370622,
            800: 370623}
    # print dsid[m12]

    # fs = {note: fs}
    fs = {"N2N1": 112, "C1C1": 157, "N2C1p": 125, "N2C1m": 127}
    decay = note.split("_")[0]
    # print decay, fs[decay]

    Xsec_NUHM2 = get_XS_NUHM2(dsid[m12], fs[decay])
    # print Xsec_NUHM2

    print "m12=", m12, ": ", Xsec_NUHM2, "/", Xsec_Higgsino, "=", Xsec_NUHM2 / Xsec_Higgsino

#----------------------------#

if __name__ == "__main__":
    main()
