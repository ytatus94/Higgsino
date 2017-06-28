#!/bin/bash
# Higgsino N2=160 N1=150 (dm = 10)
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.09999250._000001.pool.root ../test_truth_study/DAOD_TRUTH3.09999250._000002.pool.root -o user.yushen.SM_N2N1_160_150_2LMET50
# Higgsino N2=170 N1=150 (dm = 20)
 simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.09999255._000001.pool.root ../test_truth_study/DAOD_TRUTH3.09999255._000002.pool.root -o user.yushen.SM_N2N1_170_150_2LMET50
# Higgsino N2=170 C1=150
 simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.09998720._000001.pool.root ../test_truth_study/DAOD_TRUTH3.09998720._000002.pool.root -o user.yushen.SM_N2C1p_170_150_2LMET50
 simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.09998992._000001.pool.root ../test_truth_study/DAOD_TRUTH3.09998992._000002.pool.root -o user.yushen.SM_N2C1m_170_150_2LMET50
# Higgsino N2=155 C1=150
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.09998712._000001.pool.root ../test_truth_study/DAOD_TRUTH3.09998712._000002.pool.root -o user.yushen.SM_N2C1p_155_150_2LMET50
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.09998979._000001.pool.root ../test_truth_study/DAOD_TRUTH3.09998979._000002.pool.root -o user.yushen.SM_N2C1m_155_150_2LMET50

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
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.CC.unfiltered.TestJob.pool.root -o user.chris.100k.CC.unfiltered.TestJob
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.CC.filtered.TestJob.pool.root -o user.chris.100k.CC.filtered.TestJob

# C+C, C+C+j 10k w/ filter no C1
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.10k.CC.no.x1.filtered.TestJob.pool.root -o user.chris.10k.CC.no.x1.filtered.TestJob

# C+C, C+C+j, C1 put in the half way of N1 and N2
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.C1.middle.TestJob.pool.root -o user.chris.C1.middle.TestJob

# C+C, C+C+j, 10k no Hadronic Tau
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.10k.no.HadTau.TestJob.pool.root -o user.chris.10k.no.HadTau.TestJob

# C+C, C+C+j, 10k no Hadronic Tau
# simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.10k.simplified.no.HadTau.TestJob.pool.root -o user.chris.10k.simplified.no.HadTau.TestJob

# p p > n2 x1+ (j), n2 > l+ l- n1
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.n2.decay.pool.root -o user.chris.10k.n2.decay.TestJob
# p p  > n2 x1+/-, n2 > l+ l- n1
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.10k.n2.decay.no.jet.pool.root -o user.chris.10k.n2.decay.no.jet.TestJob
# p p  > n2 x1+/- j, n2 > l+ l- n1
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.10k.n2.decay.with.jet.pool.root -o user.chris.10k.n2.decay.with.jet.TestJob

