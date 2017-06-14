#!/bin/bash
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.09999250._000001.pool.root ../test_truth_study/DAOD_TRUTH3.09999250._000002.pool.root -o user.yushen.SM_N2N1_160_150_2LMET50
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/DAOD_TRUTH3.judita.TestJob.pool.root -o user.judita.TestJob
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.TestJob.pool.root -o user.chris.TestJob
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.TestJob.pool.root -o user.chris.100k.TestJob
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.filtered.TestJob.pool.root -o user.chris.100k.filtered.TestJob
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Chris/DAOD_TRUTH3.chris.100k.unfiltered.TestJob.pool.root -o user.chris.100k.unfiltered.TestJob
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Pat/DAOD_TRUTH3.pskubic.TestJob.pool.root -o user.pskubic.TestJob
simpleAnalysis -n -a EwkHiggsino2016 ../test_truth_study/Pat/DAOD_TRUTH3.pskubic.10k.TestJob.pool.root -o user.pskubic.10k.TestJob
