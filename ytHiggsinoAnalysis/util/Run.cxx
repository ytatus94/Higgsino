// Usage:
// Run optimization analysis_type=abc sample_type=def sample=ghi [PROOF/Condor/Grid]
// abc = 2L0J_DirSlep/2L0J/2L2J_Conv_High/2L2J_Conv_Med/2L2J_Conv_Low/
// def = data/signals/backgrounds
// ghi = Vgamma/ttbar/higgs/VV/VVV

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

    bool isOptimization = false;

    string analysis_type;
    string sample_type;
    string sample;

    bool use_Condor = false;
    bool use_Grid = false;
    bool use_PROOF = false;

    for (int i = 1; i < argc; i++) {
        //const char *key = argv[i];
        const char* key = strtok(argv[i], "=");
        const char* val = strtok(0, " ");

        if (strcmp(key, "optimization") == 0)
            isOptimization = true;
        if (strcmp(key, "analysis_type") == 0)
            analysis_type = val;
        if (strcmp(key, "sample_type") == 0)
            sample_type = val;
        if (strcmp(key, "sample") == 0)
            sample = val;
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

    // Print out input arguments
    if (isOptimization) {
        printf("Running SR optimization for analysis_type=%s, sample_type=%s, and sample=%s\n", analysis_type.c_str(), sample_type.c_str(), sample.c_str());
        submitDir = "optimization_" + analysis_type;
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
    const char* inputFilePath = "../Data/Sarah"; // no slash (/) at the end
    if (sample_type == "signals")
        SH::ScanDir().filePattern("CentralSignals.root").scan(sh, inputFilePath);
    else if (sample_type == "backgrounds")
        SH::ScanDir().filePattern("CentralBackgrounds.root").scan(sh, inputFilePath);
    else if (sample_type == "data")
        SH::ScanDir().filePattern("CentralData.root").scan(sh, inputFilePath);

    // Set the name of the input TTree.
    cout << "Load TTree: " << sample << "_CENTRAL tree ..." << endl;
    if (sample_type == "Data")
        sh.setMetaString("nc_tree", "Data_CENTRAL");
    else if (sample_type == "signals")
        cout << "Sorry, not support sample_type = signals yet" << endl;
    else if (sample_type == "backgrounds") {
        if (sample == "Vgamma")
            sh.setMetaString("nc_tree", "Vgamma_CENTRAL");
        else if (sample == "ttbar")
            sh.setMetaString("nc_tree", "ttbar_CENTRAL");
        else if (sample == "higgs")
            sh.setMetaString("nc_tree", "higgs_CENTRAL");
        else if (sample == "VV")
            sh.setMetaString("nc_tree", "VV_CENTRAL");
        else if (sample == "VVV")
            sh.setMetaString("nc_tree", "VVV_CENTRAL");
    }

    // Print what we found:
    sh.print(); // list all the root files in the dataset
    // cout << "sh.size()=" << sh.size() << endl; // number of dataset

    // Create an EventLoop job:
    EL::Job job;
    job.sampleHandler( sh );
    job.options()->setDouble (EL::Job::optMaxEvents, 50);

    // Add our analysis to the job:
    ytEventSelection *alg = new ytEventSelection();
    alg->set_isOptimization(isOptimization);
    alg->set_analysis_type(analysis_type);

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
