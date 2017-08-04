#!/bin/bash

# execute this before running the script
# asetup 20.1.8.3,AtlasDerivation,gcc48,here

# for i in 20 21 22 23
# do
#    inputFile="user.yushen.TestJob_weak_600_run_"$i".pool.root"
#    outputFile="yushen.run_"$i".pool.root"
#    Reco_tf.py --inputEVNTFile $inputFile --outputDAODFile $outputFile --reductionConf TRUTH3
# done

# for m12 in 300 350 400 500 600 700 800
# do
#    for decay in N2N1 C1C1 N2C1p N2C1m
#    do
#        inputFile="user.yushen.run_${m12}_${decay}_.pool.root"
#        outputFile="yushen.run_${m12}_${decay}.pool.root"
#        # ls $inputFile
#        # echo $outputFile
#        Reco_tf.py --inputEVNTFile $inputFile --outputDAODFile $outputFile --reductionConf TRUTH3
#    done
# done

for dir in mc15_13TeV.393510.MGPy8EG_A14N23LO_SM_N2N1_160_100_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393559.MGPy8EG_A14N23LO_SM_C1C1_160_100_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393412.MGPy8EG_A14N23LO_SM_N2C1p_160_100_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393461.MGPy8EG_A14N23LO_SM_N2C1m_160_100_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393509.MGPy8EG_A14N23LO_SM_N2N1_140_100_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393558.MGPy8EG_A14N23LO_SM_C1C1_140_100_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393411.MGPy8EG_A14N23LO_SM_N2C1p_140_100_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393460.MGPy8EG_A14N23LO_SM_N2C1m_140_100_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393515.MGPy8EG_A14N23LO_SM_N2N1_170_150_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393564.MGPy8EG_A14N23LO_SM_C1C1_170_150_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393417.MGPy8EG_A14N23LO_SM_N2C1p_170_150_2LMET50_MadSpin.evgen.EVNT.e5512 \
           mc15_13TeV.393466.MGPy8EG_A14N23LO_SM_N2C1m_170_150_2LMET50_MadSpin.evgen.EVNT.e5512
do
    for inputFile in $(ls $dir)
    do
        outputFile=$(echo $inputFile | gawk 'BEGIN {FS=".";OFS="."}; { print $2, $3, $4, $5}')
        # echo $inputFile
        # echo $outputFile
        Reco_tf.py --inputEVNTFile ${dir}/${inputFile} --outputDAODFile $outputFile --reductionConf TRUTH3
    done
done
