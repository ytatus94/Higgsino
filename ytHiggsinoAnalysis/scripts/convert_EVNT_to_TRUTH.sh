#!/bin/bash

# execute this before running the script
# asetup 20.1.8.3,AtlasDerivation,gcc48,here

for i in 20 21 22 23
do
    inputFile="user.yushen.TestJob_weak_600_run_"$i".pool.root"
    outputFile="yushen.run_"$i".pool.root"
    Reco_tf.py --inputEVNTFile $inputFile --outputDAODFile $outputFile --reductionConf TRUTH3
done

