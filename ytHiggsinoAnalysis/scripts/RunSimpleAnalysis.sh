#!/bin/bash
# Higgsino N2=160 N1=150 (dm = 10)
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.09999250._000001.pool.root ../test_truth_study/DAOD_TRUTH3.09999250._000002.pool.root -o user.yushen.SM_N2N1_160_150_2LMET50
# Higgsino N2=170 N1=150 (dm = 20)
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.09999255._000001.pool.root ../test_truth_study/DAOD_TRUTH3.09999255._000002.pool.root -o user.yushen.SM_N2N1_170_150_2LMET50

# NUHM2 samples 
# A+A, C+A, C+C 1k w/o filter
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.judita.TestJob.pool.root -o user.judita.TestJob

# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.TestJob.pool.root -o user.chris.TestJob
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.TestJob.pool.root -o user.chris.100k.TestJob

# A+A, A+A+j, C+C, C+C+j 100k w/ and w/o filter
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.filtered.TestJob.pool.root -o user.chris.100k.filtered.TestJob
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.unfiltered.TestJob.pool.root -o user.chris.100k.unfiltered.TestJob

# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Pat/DAOD_TRUTH3.pskubic.TestJob.pool.root -o user.pskubic.TestJob
# C+C, C+C+j 10k w/o filter
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Pat/DAOD_TRUTH3.pskubic.10k.TestJob.pool.root -o user.pskubic.10k.TestJob

# C+C, C+C+j 100k w/ and w/o filter
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.CC.unfiltered.TestJob.pool.root -o user.chris.100k.CC.unfiltered.TestJob
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.CC.filtered.TestJob.pool.root -o user.chris.100k.CC.filtered.TestJob
