// Usage:
// Run cutflow analysis_type=abc sample_type=def sample=ghi [PROOF/Condor/Grid]
// Run optimization analysis_type=abc sample_type=def sample=ghi [PROOF/Condor/Grid]
// abc = MC/Data
// def = data/signals/backgrounds
// ghi = MGPy8EG_A14N23LO_NUHM2_m12_300_weak_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
//       MGPy8EG_A14N23LO_NUHM2_m12_350_weak_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
//       MGPy8EG_A14N23LO_NUHM2_m12_300_weak_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
//       MGPy8EG_A14N23LO_NUHM2_m12_400_weak_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
//       MGPy8EG_A14N23LO_NUHM2_m12_500_weak_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
//       MGPy8EG_A14N23LO_NUHM2_m12_600_weak_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
//       MGPy8EG_A14N23LO_NUHM2_m12_700_weak_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
//       MGPy8EG_A14N23LO_NUHM2_m12_800_weak_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
//       or the background sample root files
//       or the data sample root files (data_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root)

#include "SampleHandler/SampleHandler.h"
//#include "SampleHandler/Sample.h"
#include "SampleHandler/ScanDir.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/DiskListLocal.h"

#include "EventLoop/Job.h"
#include "EventLoop/DirectDriver.h"
#include "EventLoop/ProofDriver.h"
#include "EventLoop/CondorDriver.h"
#include "EventLoopGrid/PrunDriver.h"

#include <TSystem.h>
#include <TH1.h>

#include "ytHiggsinoAnalysis/ytEventSelection.h"

#include <iostream>
#include <string>
using namespace std;

int main( int argc, char* argv[] )
{
    // Take the submit directory from the input if provided:
    // std::string submitDir = "submitDir";
    // if( argc > 1 ) submitDir = argv[ 1 ];
    std::string submitDir;

    bool isMC = false;
    bool isCutflow = false;
    bool isOptimization = false;

    string analysis_type;
    string sample_type;
    string sample;
    string m12;

    bool use_Condor = false;
    bool use_Grid = false;
    bool use_PROOF = false;

    for (int i = 1; i < argc; i++) {
        //const char *key = argv[i];
        const char* key = strtok(argv[i], "=");
        const char* val = strtok(0, " ");

        if (strcmp(key, "cutflow") == 0)
            isCutflow = true;
        if (strcmp(key, "optimization") == 0)
            isOptimization = true;
        if (strcmp(key, "analysis_type") == 0)
            analysis_type = val;
        if (strcmp(key, "sample_type") == 0)
            sample_type = val;
        if (strcmp(key, "sample") == 0)
            sample = val;
        if (strcmp(key, "m12") == 0)
            m12 = val;
        //
        //
        // Specify the driver to run.
        if (strcmp(key, "Condor") == 0)
            use_Condor = true;
        else if (strcmp(key, "Grid") == 0)
            use_Grid = true;
        else if (strcmp(key, "PROOF") == 0)
            use_PROOF = true;
    }

    // MC or Data?
    if (analysis_type == "MC")
        isMC = true;

    // Print out input arguments
    if (isCutflow) {
        printf("Running cutflow for analysis_type=%s, sample_type=%s, and sample=%s\n", analysis_type.c_str(), sample_type.c_str(), sample.c_str());
        submitDir = "cutflow_" + analysis_type + "_" + sample;
        // string sample_name = sample;
        // sample_name.erase(sample_name.find(".root"), sample_name.length());
        // submitDir = "cutflow_" + analysis_type + "_" + sample_name;
    }
    if (isOptimization) {
        printf("Running SR optimization for analysis_type=%s, sample_type=%s, and sample=%s\n", analysis_type.c_str(), sample_type.c_str(), sample.c_str());
        submitDir = "optimization_" + analysis_type + "_" + sample;
        // string sample_name = sample;
        // sample_name.erase(sample_name.find(".root"), sample_name.length());
        // submitDir = "optimization_" + analysis_type + "_" + sample_name;
    }
    cout << "submitDir = " << submitDir << endl;

    if (use_Condor) {
        printf("Submit jobs to CondorDriver...\n");
    }
    else if (use_Grid) {
        printf("Submit jobs to PrunDriver...\n");
    }
    else if (use_PROOF) {
        printf("Submit jobs to ProofDriver...\n");
    }
    else {
        printf("Submit jobs to DirectDriver...\n");
    }

    // Construct the samples to run on:
    SH::SampleHandler sh;

    // use SampleHandler to scan all of the subdirectories of a directory for particular MC single file:
    const char* inputFilePath;
    if (analysis_type == "MC") {
        if (sample_type == "signals") {
            inputFilePath = "../MC/SusySkimHiggsino_v1.9_SUSY16_Signal_tree"; // no slash (/) at the end
            SH::ScanDir().filePattern(sample).scan(sh, inputFilePath);
        }
        else if (sample_type == "NUHM2") {
            // inputFilePath = "../MC/SusySkimHiggsino_v1.9b_SUSY16_Signal_NUHM2_tree"; // no slash (/) at the end
            inputFilePath = "/afs/cern.ch/work/j/jeliu/public/HiggsinoFitterTrees/v1_9"; // no slash (/) at the end
            SH::ScanDir().filePattern(sample).scan(sh, inputFilePath);
        }
        else if (sample_type == "backgrounds") {
            inputFilePath = "../MC/SusySkimHiggsino_v1.9_SUSY16_Bkgs_tree"; // no slash (/) at the end
            SH::ScanDir().filePattern(sample).scan(sh, inputFilePath);
        }
    }
    else if (analysis_type == "Data") {
        // The data file put in SusySkimHiggsino_v1.8_SUSY16_Bkgs_tree
        inputFilePath = "../MC/SusySkimHiggsino_v1.9_SUSY16_Bkgs_tree"; // no slash (/) at the end
        SH::ScanDir().filePattern(sample).scan(sh, inputFilePath);
    }

    // Set the name of the input TTree.
    string tree_name;
    if (sample_type == "data") {
        tree_name = "data";
    }
    else if (sample_type == "NUHM2") {
        // if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_300_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_300_weak_2LMET50_MadSpin_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_350_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_350_weak_2LMET50_MadSpin_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_400_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_400_weak_2LMET50_MadSpin_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_500_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_500_weak_2LMET50_MadSpin_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_600_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_600_weak_2LMET50_MadSpin_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_700_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_700_weak_2LMET50_MadSpin_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_800_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_800_weak_2LMET50_MadSpin_NoSys";
        if (m12 == "350")
            tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_350_weak_NoSys";
        else if (m12 == "400")
            tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_400_weak_NoSys";
        else if (m12 == "500")
            tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_500_weak_NoSys";
        else if (m12 == "600")
            tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_600_weak_NoSys";
        else if (m12 == "700")
            tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_700_weak_NoSys";
        else if (m12 == "800")
            tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_800_weak_NoSys";
        submitDir += "_m12_" + m12;
    }
    else if (sample_type == "signals") {
        // NUHM2
        // if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_300_weak_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_300_weak_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_350_weak_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_350_weak_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_400_weak_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_400_weak_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_500_weak_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_500_weak_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_600_weak_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_600_weak_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_700_weak_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_700_weak_NoSys";
        // else if (sample == "MGPy8EG_A14N23LO_NUHM2_m12_800_weak_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
        //     tree_name = "MGPy8EG_A14N23LO_NUHM2_m12_800_weak_NoSys";
        // Higgsino
        if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_82_80_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_82_80_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_83_80_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_83_80_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_85_80_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_85_80_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_90_80_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_90_80_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_100_80_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_100_80_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_102_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_102_100_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_103_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_103_100_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_105_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_105_100_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_110_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_110_100_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_120_80_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_120_80_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_120_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_120_100_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_140_80_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_140_80_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_152_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_152_150_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_153_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_153_150_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_155_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_155_150_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_160_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_160_150_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_180_80_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_180_80_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_200_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_200_100_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_202_200_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_202_200_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_203_200_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_203_200_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_205_200_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_205_200_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_210_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_210_150_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_210_200_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_210_200_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_220_200_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_220_200_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_240_200_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_240_200_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_250_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_250_150_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_252_250_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_252_250_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_253_250_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_253_250_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_255_250_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_255_250_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_260_200_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_260_200_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_260_250_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_260_250_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_270_250_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_270_250_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_290_250_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_290_250_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_300_200_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_300_200_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_302_300_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_302_300_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_303_300_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_303_300_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_305_300_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_305_300_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_310_250_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_310_250_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_310_300_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_310_300_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_320_300_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_320_300_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_340_300_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_340_300_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_350_250_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_350_250_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_360_300_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_360_300_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_400_300_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_400_300_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_402_400_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_402_400_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_403_400_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_403_400_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_405_400_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_405_400_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_410_400_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_410_400_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_420_400_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_420_400_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_440_400_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_440_400_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_460_400_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_460_400_2LMET50_MadSpin_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SM_Higgsino_500_400_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_500_400_2LMET50_MadSpin_NoSys";
        // Slepton
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_70p5_70p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_70p5_70p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_71p0_70p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_71p0_70p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_75p0_70p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_75p0_70p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_80p0_70p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_80p0_70p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_30p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_30p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_40p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_40p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_50p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_50p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_60p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_60p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_65p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_65p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_70p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_90p0_70p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_91p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_91p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_92p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_92p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_93p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_93p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_95p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_95p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_100p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_100p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_101p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_101p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_102p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_102p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_103p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_103p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_105p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_105p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_105p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_105p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_110p0_70p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_110p0_70p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_110p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_110p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_110p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_110p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_115p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_115p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_115p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_115p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_60p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_60p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_70p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_70p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_80p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_80p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_120p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_120p5_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_120p5_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_121p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_121p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_122p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_122p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_123p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_123p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_125p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_125p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_125p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_125p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_130p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_130p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_130p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_130p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_135p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_135p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_140p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_140p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_140p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_140p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_141p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_141p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_142p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_142p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_143p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_143p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_145p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_145p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_145p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_145p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_150p0_90p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_150p0_90p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_150p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_150p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_155p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_155p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_160p0_100p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_160p0_100p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_160p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_160p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_160p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_160p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_161p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_161p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_162p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_162p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_163p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_163p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_165p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_165p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_165p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_165p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_170p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_170p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_175p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_175p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_180p0_120p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_180p0_120p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_180p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_180p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_180p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_180p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_180p5_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_180p5_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_181p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_181p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_182p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_182p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_183p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_183p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_185p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_185p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_185p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_185p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_190p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_190p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_195p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_195p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_200p0_140p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_200p0_140p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_200p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_200p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_200p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_200p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_201p0_200p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_201p0_200p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_202p0_200p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_202p0_200p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_205p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_205p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_205p0_200p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_205p0_200p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_210p0_200p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_210p0_200p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_220p0_160p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_220p0_160p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_220p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_220p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_220p0_200p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_220p0_200p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_240p0_180p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_240p0_180p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_251p0_250p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_251p0_250p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_255p0_250p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_255p0_250p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_260p0_250p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_260p0_250p0_MET50_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_SlepSlep_direct_270p0_250p0_MET50_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_SlepSlep_direct_270p0_250p0_MET50_NoSys";
        // WZ
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_110_100_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_110_100_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_120_100_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_120_100_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_140_100_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_140_100_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_160_100_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_160_100_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_160_150_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_160_150_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_170_150_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_170_150_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_180_100_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_180_100_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_190_150_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_190_150_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_200_100_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_200_100_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_210_150_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_210_150_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_210_200_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_210_200_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_220_200_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_220_200_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_230_150_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_230_150_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_240_200_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_240_200_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_250_150_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_250_150_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_260_200_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_260_200_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_260_250_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_260_250_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_270_250_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_270_250_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_280_200_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_280_200_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_290_250_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_290_250_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_300_200_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_300_200_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_310_250_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_310_250_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_310_300_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_310_300_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_320_300_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_320_300_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_330_250_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_330_250_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_340_300_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_340_300_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_350_250_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_350_250_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_360_300_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_360_300_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_360_350_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_360_350_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_370_350_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_370_350_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_380_300_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_380_300_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_390_350_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_390_350_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_400_300_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_400_300_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_410_350_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_410_350_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_430_350_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_430_350_2L2J_2L3andMET100_NoSys";
        else if (sample == "MGPy8EG_A14N23LO_C1N2_WZ_450_350_2L2J_2L3andMET100_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "MGPy8EG_A14N23LO_C1N2_WZ_450_350_2L2J_2L3andMET100_NoSys";
    }
    else if (sample_type == "backgrounds") {
        if (sample == "AllBkgsButFakes_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "Zjets_NoSys";
        else if (sample == "alt_DY_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_DY_PowPy_NoSys";
        else if (sample == "alt_Wgamma_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_Wgamma_Sherpa222_NoSys";
        else if (sample == "alt_Zgamma_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_Zgamma_Sherpa222_NoSys";
        else if (sample == "alt_Zttgamma_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_Zttgamma_Sherpa222_NoSys";
        else if (sample == "alt_Zvvgamma_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_Zvvgamma_Sherpa222_NoSys";
        else if (sample == "alt_diboson1L_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_diboson1L_PowPy_NoSys";
        else if (sample == "alt_diboson1L_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_diboson1L_Sherpa222_NoSys";
        else if (sample == "alt_diboson2L_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_diboson2L_PowPy_NoSys";
        else if (sample == "alt_diboson2L_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_diboson2L_Sherpa222_NoSys";
        else if (sample == "alt_diboson3L_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_diboson3L_PowPy_NoSys";
        else if (sample == "alt_diboson3L_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_diboson3L_Sherpa222_NoSys";
        else if (sample == "alt_diboson4L_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_diboson4L_PowPy_NoSys";
        else if (sample == "alt_diboson4L_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_diboson4L_Sherpa222_NoSys";
        else if (sample == "alt_triboson_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_triboson_Sherpa222_NoSys";
        else if (sample == "alt_ttbar_MGPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_ttbar_MGPy_NoSys";
        else if (sample == "alt_ttbar_PowPy8_dilep_hdamp258p75_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_ttbar_PowPy8_dilep_hdamp258p75_NoSys";
        else if (sample == "alt_ttbar_PowPy8_nonallhad_hdamp172p5_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_ttbar_PowPy8_nonallhad_hdamp172p5_NoSys";
        else if (sample == "alt_ttbar_PowPy8_nonallhad_hdamp258p75_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_ttbar_PowPy8_nonallhad_hdamp258p75_NoSys";
        else if (sample == "alt_ttbar_Sherpa_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_ttbar_Sherpa_NoSys";
        else if (sample == "alt_ttbar_aMcAtNlo_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_ttbar_aMcAtNlo_NoSys";
        else if (sample == "alt_ttbar_nonallhad_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "alt_ttbar_nonallhad_NoSys";
        else if (sample == "diboson0L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "diboson0L_NoSys";
        else if (sample == "diboson1L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "diboson1L_NoSys";
        else if (sample == "diboson2L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "diboson2L_NoSys";
        else if (sample == "diboson3L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "diboson3L_NoSys";
        else if (sample == "diboson4L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "diboson4L_NoSys";
        else if (sample == "triboson_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "triboson_NoSys";
        else if (sample == "higgs_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "higgs_NoSys";
        else if (sample == "singletop_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "singletop_NoSys";
        else if (sample == "topOther_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "topOther_NoSys";
        else if (sample == "ttbar_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "ttbar_NoSys";
        else if (sample == "Wgamma_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "Wgamma_NoSys";
        else if (sample == "Wjets_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "Wjets_NoSys";
        else if (sample == "Zgamma_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "Zgamma_NoSys";
        else if (sample == "Zjets_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "Zjets_NoSys";
        else if (sample == "Zttgamma_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "Zttgamma_NoSys";
        else if (sample == "Zttjets_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "Zttjets_NoSys";
        // else if (sample == "Zvvgamma_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
        //     tree_name = "Zvvgamma_NoSys";
        else if (sample == "Zvvjets_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root")
            tree_name = "Zvvjets_NoSys";
    }

    sh.setMetaString("nc_tree", tree_name);
    cout << "Load TTree: " << tree_name << endl;

    // Print what we found:
    sh.print(); // list all the root files in the dataset
    // cout << "sh.size()=" << sh.size() << endl; // number of dataset

    // Create an EventLoop job:
    EL::Job job;
    job.sampleHandler( sh );
    // job.options()->setDouble (EL::Job::optMaxEvents, 50);

    // Add our analysis to the job:
    ytEventSelection *alg = new ytEventSelection();
    alg->set_isMC(isMC);
    alg->set_isCutflow(isCutflow);
    alg->set_isOptimization(isOptimization);
    alg->set_analysis_type(analysis_type);
    alg->set_sample_type(sample_type);
    alg->set_sample(sample);
    alg->set_luminosity(36100); // pb^{-1}

    job.algsAdd( alg );

    if (use_Condor) {
        // Run the jobs using the Condor driver:
        EL::CondorDriver driver;
        // some commands for setting up root on the nodes
        driver.shellInit = "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase ; source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh ; eval rcSetup Base,2.5.1";
        driver.submitOnly( job, submitDir );
    }
    else if (use_Grid) {
        // Run the jobs using the Grid driver:
        EL::PrunDriver driver;
        // Specify how to name the grid output datasets
        // Note that %nickname% is populated when you do voms-proxy init, so this does not have to be replaced by hand
        driver.options()->setString("nc_outputSampleName", "user.%nickname%.%in:name[2]%.%in:name[3]%.%in:name[6]%.");
        driver.submitOnly( job, submitDir );
    }
    else if (use_PROOF) {
        EL::ProofDriver driver;
        driver.submit( job, submitDir );
    }
    else {
        // Run the job using the local/direct driver:
        EL::DirectDriver driver;
        driver.submit( job, submitDir );
    }

    return 0;
}
