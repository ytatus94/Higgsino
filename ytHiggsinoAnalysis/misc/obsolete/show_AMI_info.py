#!/usr/bin/python
'''
### obsolete ###
Use AMI to list the crossSection_mean and GenFiltEff_mean
'''
import os

dataset = [
    "mc15_13TeV.394301.MGPy8EG_A14N23LO_NUHM2_m12_300_weak_C1C1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394302.MGPy8EG_A14N23LO_NUHM2_m12_300_weak_N2C1m_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394303.MGPy8EG_A14N23LO_NUHM2_m12_300_weak_N2C1p_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394304.MGPy8EG_A14N23LO_NUHM2_m12_300_weak_N2N1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394305.MGPy8EG_A14N23LO_NUHM2_m12_350_weak_C1C1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394306.MGPy8EG_A14N23LO_NUHM2_m12_350_weak_N2C1m_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394307.MGPy8EG_A14N23LO_NUHM2_m12_350_weak_N2C1p_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394308.MGPy8EG_A14N23LO_NUHM2_m12_350_weak_N2N1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394309.MGPy8EG_A14N23LO_NUHM2_m12_400_weak_C1C1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394310.MGPy8EG_A14N23LO_NUHM2_m12_400_weak_N2C1m_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394311.MGPy8EG_A14N23LO_NUHM2_m12_400_weak_N2C1p_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394312.MGPy8EG_A14N23LO_NUHM2_m12_400_weak_N2N1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394313.MGPy8EG_A14N23LO_NUHM2_m12_500_weak_C1C1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394313.MGPy8EG_A14N23LO_NUHM2_m12_500_weak_C1C1_2LMET50_MadSpin.evgen.EVNT.e6241",
    "mc15_13TeV.394314.MGPy8EG_A14N23LO_NUHM2_m12_500_weak_N2C1m_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394315.MGPy8EG_A14N23LO_NUHM2_m12_500_weak_N2C1p_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394316.MGPy8EG_A14N23LO_NUHM2_m12_500_weak_N2N1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394317.MGPy8EG_A14N23LO_NUHM2_m12_600_weak_C1C1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394317.MGPy8EG_A14N23LO_NUHM2_m12_600_weak_C1C1_2LMET50_MadSpin.evgen.EVNT.e6241",
    "mc15_13TeV.394318.MGPy8EG_A14N23LO_NUHM2_m12_600_weak_N2C1m_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394319.MGPy8EG_A14N23LO_NUHM2_m12_600_weak_N2C1p_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394320.MGPy8EG_A14N23LO_NUHM2_m12_600_weak_N2N1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394321.MGPy8EG_A14N23LO_NUHM2_m12_700_weak_C1C1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394322.MGPy8EG_A14N23LO_NUHM2_m12_700_weak_N2C1m_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394323.MGPy8EG_A14N23LO_NUHM2_m12_700_weak_N2C1p_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394324.MGPy8EG_A14N23LO_NUHM2_m12_700_weak_N2N1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394325.MGPy8EG_A14N23LO_NUHM2_m12_800_weak_C1C1_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394326.MGPy8EG_A14N23LO_NUHM2_m12_800_weak_N2C1m_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394327.MGPy8EG_A14N23LO_NUHM2_m12_800_weak_N2C1p_2LMET50_MadSpin.evgen.EVNT.e6233",
    "mc15_13TeV.394328.MGPy8EG_A14N23LO_NUHM2_m12_800_weak_N2N1_2LMET50_MadSpin.evgen.EVNT.e6233"
    ]

for sample in dataset:
    m12 = sample[sample.index("m12_") + len("m12_") : sample.index("_weak_")]
    decay_channel = sample[sample.index("_weak_") + len("_weak_") : sample.index("_2LMET50")]
    name = m12 + "_" + decay_channel

print "crossSection_mean:"
for sample in dataset:
    command_Xsec = "ami show dataset info " + sample + " | grep crossSection_mean"
    print command_Xsec
    os.system(command_Xsec)

print "GenFiltEff_mean:"
for sample in dataset:
    command_eff = "ami show dataset info " + sample + " | grep GenFiltEff_mean"
    print command_eff
    os.system(command_eff)
