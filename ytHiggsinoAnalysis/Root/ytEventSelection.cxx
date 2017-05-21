#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <ytHiggsinoAnalysis/ytEventSelection.h>

// this is needed to distribute the algorithm to the workers
ClassImp(ytEventSelection)



ytEventSelection :: ytEventSelection ()
{
    // Here you put any code for the base initialization of variables,
    // e.g. initialize all pointers to 0.  Note that you should only put
    // the most basic initialization here, since this method will be
    // called on both the submission and the worker node.  Most of your
    // initialization code will go into histInitialize() and
    // initialize().
}



EL::StatusCode ytEventSelection :: setupJob (EL::Job& job)
{
    // Here you put code that sets up the job on the submission object
    // so that it is ready to work with your algorithm, e.g. you can
    // request the D3PDReader service or add output files.  Any code you
    // put here could instead also go into the submission script.  The
    // sole advantage of putting it here is that it gets automatically
    // activated/deactivated when you add/remove the algorithm from your
    // job, which may or may not be of value to you.
    return EL::StatusCode::SUCCESS;
}



EL::StatusCode ytEventSelection :: histInitialize ()
{
    // Here you do everything that needs to be done at the very
    // beginning on each worker node, e.g. create histograms and output
    // trees.  This method gets called before any input files are
    // connected.

    return EL::StatusCode::SUCCESS;
}



EL::StatusCode ytEventSelection :: fileExecute ()
{
    // Here you do everything that needs to be done exactly once for every
    // single file, e.g. collect a list of all lumi-blocks processed
    return EL::StatusCode::SUCCESS;
}



EL::StatusCode ytEventSelection :: changeInput (bool firstFile)
{
    // Here you do everything you need to do when we change input files,
    // e.g. resetting branch addresses on trees.  If you are using
    // D3PDReader or a similar service this method is not needed.

    // Set object pointer
    jetPt = 0;
    jetEta = 0;
    jetPhi = 0;
    jetM = 0;

    // Set branch addresses and branch pointers
    fChain = wk()->tree();
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("trigWeight_metTrig", &trigWeight_metTrig, &b_trigWeight_metTrig);
    fChain->SetBranchAddress("trigMatch_metTrig", &trigMatch_metTrig, &b_trigMatch_metTrig);
    fChain->SetBranchAddress("trigWeight_singleMuonTrig", &trigWeight_singleMuonTrig, &b_trigWeight_singleMuonTrig);
    fChain->SetBranchAddress("trigMatch_singleMuonTrig", &trigMatch_singleMuonTrig, &b_trigMatch_singleMuonTrig);
    fChain->SetBranchAddress("trigWeight_singleElectronTrig", &trigWeight_singleElectronTrig, &b_trigWeight_singleElectronTrig);
    fChain->SetBranchAddress("trigMatch_singleElectronTrig", &trigMatch_singleElectronTrig, &b_trigMatch_singleElectronTrig);
    fChain->SetBranchAddress("HLT_2mu4_j85_xe50_mht_emul", &HLT_2mu4_j85_xe50_mht_emul, &b_HLT_2mu4_j85_xe50_mht_emul);
    fChain->SetBranchAddress("HLT_mu4_j125_xe90_mht_emul", &HLT_mu4_j125_xe90_mht_emul, &b_HLT_mu4_j125_xe90_mht_emul);
    fChain->SetBranchAddress("mu", &mu, &b_mu);
    fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
    fChain->SetBranchAddress("nLep_base", &nLep_base, &b_nLep_base);
    fChain->SetBranchAddress("nLep_signal", &nLep_signal, &b_nLep_signal);
    fChain->SetBranchAddress("lep1Flavor", &lep1Flavor, &b_lep1Flavor);
    fChain->SetBranchAddress("lep1Charge", &lep1Charge, &b_lep1Charge);
    fChain->SetBranchAddress("lep1Pt", &lep1Pt, &b_lep1Pt);
    fChain->SetBranchAddress("lep1Eta", &lep1Eta, &b_lep1Eta);
    fChain->SetBranchAddress("lep1Phi", &lep1Phi, &b_lep1Phi);
    fChain->SetBranchAddress("lep1M", &lep1M, &b_lep1M);
    fChain->SetBranchAddress("lep1D0", &lep1D0, &b_lep1D0);
    fChain->SetBranchAddress("lep1D0Sig", &lep1D0Sig, &b_lep1D0Sig);
    fChain->SetBranchAddress("lep1Z0", &lep1Z0, &b_lep1Z0);
    fChain->SetBranchAddress("lep1Z0SinTheta", &lep1Z0SinTheta, &b_lep1Z0SinTheta);
    fChain->SetBranchAddress("lep1Topoetcone20", &lep1Topoetcone20, &b_lep1Topoetcone20);
    fChain->SetBranchAddress("lep1Ptvarcone20", &lep1Ptvarcone20, &b_lep1Ptvarcone20);
    fChain->SetBranchAddress("lep1Ptvarcone30", &lep1Ptvarcone30, &b_lep1Ptvarcone30);
    fChain->SetBranchAddress("lep1CorrTopoetcone20", &lep1CorrTopoetcone20, &b_lep1CorrTopoetcone20);
    fChain->SetBranchAddress("lep1CorrPtvarcone20", &lep1CorrPtvarcone20, &b_lep1CorrPtvarcone20);
    fChain->SetBranchAddress("lep1CorrPtvarcone30", &lep1CorrPtvarcone30, &b_lep1CorrPtvarcone30);
    fChain->SetBranchAddress("lep1PassOR", &lep1PassOR, &b_lep1PassOR);
    fChain->SetBranchAddress("lep1Type", &lep1Type, &b_lep1Type);
    fChain->SetBranchAddress("lep1Origin", &lep1Origin, &b_lep1Origin);
    fChain->SetBranchAddress("lep1NPix", &lep1NPix, &b_lep1NPix);
    fChain->SetBranchAddress("lep1PassBL", &lep1PassBL, &b_lep1PassBL);
    fChain->SetBranchAddress("lep1VeryLoose", &lep1VeryLoose, &b_lep1VeryLoose);
    fChain->SetBranchAddress("lep1Loose", &lep1Loose, &b_lep1Loose);
    fChain->SetBranchAddress("lep1Medium", &lep1Medium, &b_lep1Medium);
    fChain->SetBranchAddress("lep1Tight", &lep1Tight, &b_lep1Tight);
    fChain->SetBranchAddress("lep1IsoLoose", &lep1IsoLoose, &b_lep1IsoLoose);
    fChain->SetBranchAddress("lep1IsoTight", &lep1IsoTight, &b_lep1IsoTight);
    fChain->SetBranchAddress("lep1IsoGradient", &lep1IsoGradient, &b_lep1IsoGradient);
    fChain->SetBranchAddress("lep1IsoGradientLoose", &lep1IsoGradientLoose, &b_lep1IsoGradientLoose);
    fChain->SetBranchAddress("lep1IsoLooseTrackOnly", &lep1IsoLooseTrackOnly, &b_lep1IsoLooseTrackOnly);
    fChain->SetBranchAddress("lep1IsoFixedCutLoose", &lep1IsoFixedCutLoose, &b_lep1IsoFixedCutLoose);
    fChain->SetBranchAddress("lep1IsoFixedCutTight", &lep1IsoFixedCutTight, &b_lep1IsoFixedCutTight);
    fChain->SetBranchAddress("lep1IsoFixedCutTightTrackOnly", &lep1IsoFixedCutTightTrackOnly, &b_lep1IsoFixedCutTightTrackOnly);
    fChain->SetBranchAddress("lep1IsoCorrLoose", &lep1IsoCorrLoose, &b_lep1IsoCorrLoose);
    fChain->SetBranchAddress("lep1IsoCorrTight", &lep1IsoCorrTight, &b_lep1IsoCorrTight);
    fChain->SetBranchAddress("lep1IsoCorrGradient", &lep1IsoCorrGradient, &b_lep1IsoCorrGradient);
    fChain->SetBranchAddress("lep1IsoCorrGradientLoose", &lep1IsoCorrGradientLoose, &b_lep1IsoCorrGradientLoose);
    fChain->SetBranchAddress("lep1IsoCorrLooseTrackOnly", &lep1IsoCorrLooseTrackOnly, &b_lep1IsoCorrLooseTrackOnly);
    fChain->SetBranchAddress("lep1IsoCorrFixedCutLoose", &lep1IsoCorrFixedCutLoose, &b_lep1IsoCorrFixedCutLoose);
    fChain->SetBranchAddress("lep1IsoCorrFixedCutTight", &lep1IsoCorrFixedCutTight, &b_lep1IsoCorrFixedCutTight);
    fChain->SetBranchAddress("lep1IsoCorrFixedCutTightTrackOnly", &lep1IsoCorrFixedCutTightTrackOnly, &b_lep1IsoCorrFixedCutTightTrackOnly);
    fChain->SetBranchAddress("lep1Signal", &lep1Signal, &b_lep1Signal);
    fChain->SetBranchAddress("lep1MatchesTrigger", &lep1MatchesTrigger, &b_lep1MatchesTrigger);
    fChain->SetBranchAddress("lep1TruthCharge", &lep1TruthCharge, &b_lep1TruthCharge);
    fChain->SetBranchAddress("lep1TruthPt", &lep1TruthPt, &b_lep1TruthPt);
    fChain->SetBranchAddress("lep1TruthEta", &lep1TruthEta, &b_lep1TruthEta);
    fChain->SetBranchAddress("lep1TruthPhi", &lep1TruthPhi, &b_lep1TruthPhi);
    fChain->SetBranchAddress("lep1TruthM", &lep1TruthM, &b_lep1TruthM);
    fChain->SetBranchAddress("lep2Flavor", &lep2Flavor, &b_lep2Flavor);
    fChain->SetBranchAddress("lep2Charge", &lep2Charge, &b_lep2Charge);
    fChain->SetBranchAddress("lep2Pt", &lep2Pt, &b_lep2Pt);
    fChain->SetBranchAddress("lep2Eta", &lep2Eta, &b_lep2Eta);
    fChain->SetBranchAddress("lep2Phi", &lep2Phi, &b_lep2Phi);
    fChain->SetBranchAddress("lep2M", &lep2M, &b_lep2M);
    fChain->SetBranchAddress("lep2D0", &lep2D0, &b_lep2D0);
    fChain->SetBranchAddress("lep2D0Sig", &lep2D0Sig, &b_lep2D0Sig);
    fChain->SetBranchAddress("lep2Z0", &lep2Z0, &b_lep2Z0);
    fChain->SetBranchAddress("lep2Z0SinTheta", &lep2Z0SinTheta, &b_lep2Z0SinTheta);
    fChain->SetBranchAddress("lep2Topoetcone20", &lep2Topoetcone20, &b_lep2Topoetcone20);
    fChain->SetBranchAddress("lep2Ptvarcone20", &lep2Ptvarcone20, &b_lep2Ptvarcone20);
    fChain->SetBranchAddress("lep2Ptvarcone30", &lep2Ptvarcone30, &b_lep2Ptvarcone30);
    fChain->SetBranchAddress("lep2CorrTopoetcone20", &lep2CorrTopoetcone20, &b_lep2CorrTopoetcone20);
    fChain->SetBranchAddress("lep2CorrPtvarcone20", &lep2CorrPtvarcone20, &b_lep2CorrPtvarcone20);
    fChain->SetBranchAddress("lep2CorrPtvarcone30", &lep2CorrPtvarcone30, &b_lep2CorrPtvarcone30);
    fChain->SetBranchAddress("lep2PassOR", &lep2PassOR, &b_lep2PassOR);
    fChain->SetBranchAddress("lep2Type", &lep2Type, &b_lep2Type);
    fChain->SetBranchAddress("lep2Origin", &lep2Origin, &b_lep2Origin);
    fChain->SetBranchAddress("lep2NPix", &lep2NPix, &b_lep2NPix);
    fChain->SetBranchAddress("lep2PassBL", &lep2PassBL, &b_lep2PassBL);
    fChain->SetBranchAddress("lep2VeryLoose", &lep2VeryLoose, &b_lep2VeryLoose);
    fChain->SetBranchAddress("lep2Loose", &lep2Loose, &b_lep2Loose);
    fChain->SetBranchAddress("lep2Medium", &lep2Medium, &b_lep2Medium);
    fChain->SetBranchAddress("lep2Tight", &lep2Tight, &b_lep2Tight);
    fChain->SetBranchAddress("lep2IsoLoose", &lep2IsoLoose, &b_lep2IsoLoose);
    fChain->SetBranchAddress("lep2IsoTight", &lep2IsoTight, &b_lep2IsoTight);
    fChain->SetBranchAddress("lep2IsoGradient", &lep2IsoGradient, &b_lep2IsoGradient);
    fChain->SetBranchAddress("lep2IsoGradientLoose", &lep2IsoGradientLoose, &b_lep2IsoGradientLoose);
    fChain->SetBranchAddress("lep2IsoLooseTrackOnly", &lep2IsoLooseTrackOnly, &b_lep2IsoLooseTrackOnly);
    fChain->SetBranchAddress("lep2IsoFixedCutLoose", &lep2IsoFixedCutLoose, &b_lep2IsoFixedCutLoose);
    fChain->SetBranchAddress("lep2IsoFixedCutTight", &lep2IsoFixedCutTight, &b_lep2IsoFixedCutTight);
    fChain->SetBranchAddress("lep2IsoFixedCutTightTrackOnly", &lep2IsoFixedCutTightTrackOnly, &b_lep2IsoFixedCutTightTrackOnly);
    fChain->SetBranchAddress("lep2IsoCorrLoose", &lep2IsoCorrLoose, &b_lep2IsoCorrLoose);
    fChain->SetBranchAddress("lep2IsoCorrTight", &lep2IsoCorrTight, &b_lep2IsoCorrTight);
    fChain->SetBranchAddress("lep2IsoCorrGradient", &lep2IsoCorrGradient, &b_lep2IsoCorrGradient);
    fChain->SetBranchAddress("lep2IsoCorrGradientLoose", &lep2IsoCorrGradientLoose, &b_lep2IsoCorrGradientLoose);
    fChain->SetBranchAddress("lep2IsoCorrLooseTrackOnly", &lep2IsoCorrLooseTrackOnly, &b_lep2IsoCorrLooseTrackOnly);
    fChain->SetBranchAddress("lep2IsoCorrFixedCutLoose", &lep2IsoCorrFixedCutLoose, &b_lep2IsoCorrFixedCutLoose);
    fChain->SetBranchAddress("lep2IsoCorrFixedCutTight", &lep2IsoCorrFixedCutTight, &b_lep2IsoCorrFixedCutTight);
    fChain->SetBranchAddress("lep2IsoCorrFixedCutTightTrackOnly", &lep2IsoCorrFixedCutTightTrackOnly, &b_lep2IsoCorrFixedCutTightTrackOnly);
    fChain->SetBranchAddress("lep2Signal", &lep2Signal, &b_lep2Signal);
    fChain->SetBranchAddress("lep2MatchesTrigger", &lep2MatchesTrigger, &b_lep2MatchesTrigger);
    fChain->SetBranchAddress("lep2TruthCharge", &lep2TruthCharge, &b_lep2TruthCharge);
    fChain->SetBranchAddress("lep2TruthPt", &lep2TruthPt, &b_lep2TruthPt);
    fChain->SetBranchAddress("lep2TruthEta", &lep2TruthEta, &b_lep2TruthEta);
    fChain->SetBranchAddress("lep2TruthPhi", &lep2TruthPhi, &b_lep2TruthPhi);
    fChain->SetBranchAddress("lep2TruthM", &lep2TruthM, &b_lep2TruthM);
    fChain->SetBranchAddress("lep3Flavor", &lep3Flavor, &b_lep3Flavor);
    fChain->SetBranchAddress("lep3Charge", &lep3Charge, &b_lep3Charge);
    fChain->SetBranchAddress("lep3Pt", &lep3Pt, &b_lep3Pt);
    fChain->SetBranchAddress("lep3Eta", &lep3Eta, &b_lep3Eta);
    fChain->SetBranchAddress("lep3Phi", &lep3Phi, &b_lep3Phi);
    fChain->SetBranchAddress("lep3M", &lep3M, &b_lep3M);
    fChain->SetBranchAddress("lep3D0", &lep3D0, &b_lep3D0);
    fChain->SetBranchAddress("lep3D0Sig", &lep3D0Sig, &b_lep3D0Sig);
    fChain->SetBranchAddress("lep3Z0", &lep3Z0, &b_lep3Z0);
    fChain->SetBranchAddress("lep3Z0SinTheta", &lep3Z0SinTheta, &b_lep3Z0SinTheta);
    fChain->SetBranchAddress("lep3Topoetcone20", &lep3Topoetcone20, &b_lep3Topoetcone20);
    fChain->SetBranchAddress("lep3Ptvarcone20", &lep3Ptvarcone20, &b_lep3Ptvarcone20);
    fChain->SetBranchAddress("lep3Ptvarcone30", &lep3Ptvarcone30, &b_lep3Ptvarcone30);
    fChain->SetBranchAddress("lep3CorrTopoetcone20", &lep3CorrTopoetcone20, &b_lep3CorrTopoetcone20);
    fChain->SetBranchAddress("lep3CorrPtvarcone20", &lep3CorrPtvarcone20, &b_lep3CorrPtvarcone20);
    fChain->SetBranchAddress("lep3CorrPtvarcone30", &lep3CorrPtvarcone30, &b_lep3CorrPtvarcone30);
    fChain->SetBranchAddress("lep3PassOR", &lep3PassOR, &b_lep3PassOR);
    fChain->SetBranchAddress("lep3Type", &lep3Type, &b_lep3Type);
    fChain->SetBranchAddress("lep3Origin", &lep3Origin, &b_lep3Origin);
    fChain->SetBranchAddress("lep3NPix", &lep3NPix, &b_lep3NPix);
    fChain->SetBranchAddress("lep3PassBL", &lep3PassBL, &b_lep3PassBL);
    fChain->SetBranchAddress("lep3VeryLoose", &lep3VeryLoose, &b_lep3VeryLoose);
    fChain->SetBranchAddress("lep3Loose", &lep3Loose, &b_lep3Loose);
    fChain->SetBranchAddress("lep3Medium", &lep3Medium, &b_lep3Medium);
    fChain->SetBranchAddress("lep3Tight", &lep3Tight, &b_lep3Tight);
    fChain->SetBranchAddress("lep3IsoLoose", &lep3IsoLoose, &b_lep3IsoLoose);
    fChain->SetBranchAddress("lep3IsoTight", &lep3IsoTight, &b_lep3IsoTight);
    fChain->SetBranchAddress("lep3IsoGradient", &lep3IsoGradient, &b_lep3IsoGradient);
    fChain->SetBranchAddress("lep3IsoGradientLoose", &lep3IsoGradientLoose, &b_lep3IsoGradientLoose);
    fChain->SetBranchAddress("lep3IsoLooseTrackOnly", &lep3IsoLooseTrackOnly, &b_lep3IsoLooseTrackOnly);
    fChain->SetBranchAddress("lep3IsoFixedCutLoose", &lep3IsoFixedCutLoose, &b_lep3IsoFixedCutLoose);
    fChain->SetBranchAddress("lep3IsoFixedCutTight", &lep3IsoFixedCutTight, &b_lep3IsoFixedCutTight);
    fChain->SetBranchAddress("lep3IsoFixedCutTightTrackOnly", &lep3IsoFixedCutTightTrackOnly, &b_lep3IsoFixedCutTightTrackOnly);
    fChain->SetBranchAddress("lep3IsoCorrLoose", &lep3IsoCorrLoose, &b_lep3IsoCorrLoose);
    fChain->SetBranchAddress("lep3IsoCorrTight", &lep3IsoCorrTight, &b_lep3IsoCorrTight);
    fChain->SetBranchAddress("lep3IsoCorrGradient", &lep3IsoCorrGradient, &b_lep3IsoCorrGradient);
    fChain->SetBranchAddress("lep3IsoCorrGradientLoose", &lep3IsoCorrGradientLoose, &b_lep3IsoCorrGradientLoose);
    fChain->SetBranchAddress("lep3IsoCorrLooseTrackOnly", &lep3IsoCorrLooseTrackOnly, &b_lep3IsoCorrLooseTrackOnly);
    fChain->SetBranchAddress("lep3IsoCorrFixedCutLoose", &lep3IsoCorrFixedCutLoose, &b_lep3IsoCorrFixedCutLoose);
    fChain->SetBranchAddress("lep3IsoCorrFixedCutTight", &lep3IsoCorrFixedCutTight, &b_lep3IsoCorrFixedCutTight);
    fChain->SetBranchAddress("lep3IsoCorrFixedCutTightTrackOnly", &lep3IsoCorrFixedCutTightTrackOnly, &b_lep3IsoCorrFixedCutTightTrackOnly);
    fChain->SetBranchAddress("lep3Signal", &lep3Signal, &b_lep3Signal);
    fChain->SetBranchAddress("lep3MatchesTrigger", &lep3MatchesTrigger, &b_lep3MatchesTrigger);
    fChain->SetBranchAddress("lep3TruthCharge", &lep3TruthCharge, &b_lep3TruthCharge);
    fChain->SetBranchAddress("lep3TruthPt", &lep3TruthPt, &b_lep3TruthPt);
    fChain->SetBranchAddress("lep3TruthEta", &lep3TruthEta, &b_lep3TruthEta);
    fChain->SetBranchAddress("lep3TruthPhi", &lep3TruthPhi, &b_lep3TruthPhi);
    fChain->SetBranchAddress("lep3TruthM", &lep3TruthM, &b_lep3TruthM);
    fChain->SetBranchAddress("lep4Flavor", &lep4Flavor, &b_lep4Flavor);
    fChain->SetBranchAddress("lep4Charge", &lep4Charge, &b_lep4Charge);
    fChain->SetBranchAddress("lep4Pt", &lep4Pt, &b_lep4Pt);
    fChain->SetBranchAddress("lep4Eta", &lep4Eta, &b_lep4Eta);
    fChain->SetBranchAddress("lep4Phi", &lep4Phi, &b_lep4Phi);
    fChain->SetBranchAddress("lep4M", &lep4M, &b_lep4M);
    fChain->SetBranchAddress("lep4D0", &lep4D0, &b_lep4D0);
    fChain->SetBranchAddress("lep4D0Sig", &lep4D0Sig, &b_lep4D0Sig);
    fChain->SetBranchAddress("lep4Z0", &lep4Z0, &b_lep4Z0);
    fChain->SetBranchAddress("lep4Z0SinTheta", &lep4Z0SinTheta, &b_lep4Z0SinTheta);
    fChain->SetBranchAddress("lep4Topoetcone20", &lep4Topoetcone20, &b_lep4Topoetcone20);
    fChain->SetBranchAddress("lep4Ptvarcone20", &lep4Ptvarcone20, &b_lep4Ptvarcone20);
    fChain->SetBranchAddress("lep4Ptvarcone30", &lep4Ptvarcone30, &b_lep4Ptvarcone30);
    fChain->SetBranchAddress("lep4CorrTopoetcone20", &lep4CorrTopoetcone20, &b_lep4CorrTopoetcone20);
    fChain->SetBranchAddress("lep4CorrPtvarcone20", &lep4CorrPtvarcone20, &b_lep4CorrPtvarcone20);
    fChain->SetBranchAddress("lep4CorrPtvarcone30", &lep4CorrPtvarcone30, &b_lep4CorrPtvarcone30);
    fChain->SetBranchAddress("lep4PassOR", &lep4PassOR, &b_lep4PassOR);
    fChain->SetBranchAddress("lep4Type", &lep4Type, &b_lep4Type);
    fChain->SetBranchAddress("lep4Origin", &lep4Origin, &b_lep4Origin);
    fChain->SetBranchAddress("lep4NPix", &lep4NPix, &b_lep4NPix);
    fChain->SetBranchAddress("lep4PassBL", &lep4PassBL, &b_lep4PassBL);
    fChain->SetBranchAddress("lep4VeryLoose", &lep4VeryLoose, &b_lep4VeryLoose);
    fChain->SetBranchAddress("lep4Loose", &lep4Loose, &b_lep4Loose);
    fChain->SetBranchAddress("lep4Medium", &lep4Medium, &b_lep4Medium);
    fChain->SetBranchAddress("lep4Tight", &lep4Tight, &b_lep4Tight);
    fChain->SetBranchAddress("lep4IsoLoose", &lep4IsoLoose, &b_lep4IsoLoose);
    fChain->SetBranchAddress("lep4IsoTight", &lep4IsoTight, &b_lep4IsoTight);
    fChain->SetBranchAddress("lep4IsoGradient", &lep4IsoGradient, &b_lep4IsoGradient);
    fChain->SetBranchAddress("lep4IsoGradientLoose", &lep4IsoGradientLoose, &b_lep4IsoGradientLoose);
    fChain->SetBranchAddress("lep4IsoLooseTrackOnly", &lep4IsoLooseTrackOnly, &b_lep4IsoLooseTrackOnly);
    fChain->SetBranchAddress("lep4IsoFixedCutLoose", &lep4IsoFixedCutLoose, &b_lep4IsoFixedCutLoose);
    fChain->SetBranchAddress("lep4IsoFixedCutTight", &lep4IsoFixedCutTight, &b_lep4IsoFixedCutTight);
    fChain->SetBranchAddress("lep4IsoFixedCutTightTrackOnly", &lep4IsoFixedCutTightTrackOnly, &b_lep4IsoFixedCutTightTrackOnly);
    fChain->SetBranchAddress("lep4IsoCorrLoose", &lep4IsoCorrLoose, &b_lep4IsoCorrLoose);
    fChain->SetBranchAddress("lep4IsoCorrTight", &lep4IsoCorrTight, &b_lep4IsoCorrTight);
    fChain->SetBranchAddress("lep4IsoCorrGradient", &lep4IsoCorrGradient, &b_lep4IsoCorrGradient);
    fChain->SetBranchAddress("lep4IsoCorrGradientLoose", &lep4IsoCorrGradientLoose, &b_lep4IsoCorrGradientLoose);
    fChain->SetBranchAddress("lep4IsoCorrLooseTrackOnly", &lep4IsoCorrLooseTrackOnly, &b_lep4IsoCorrLooseTrackOnly);
    fChain->SetBranchAddress("lep4IsoCorrFixedCutLoose", &lep4IsoCorrFixedCutLoose, &b_lep4IsoCorrFixedCutLoose);
    fChain->SetBranchAddress("lep4IsoCorrFixedCutTight", &lep4IsoCorrFixedCutTight, &b_lep4IsoCorrFixedCutTight);
    fChain->SetBranchAddress("lep4IsoCorrFixedCutTightTrackOnly", &lep4IsoCorrFixedCutTightTrackOnly, &b_lep4IsoCorrFixedCutTightTrackOnly);
    fChain->SetBranchAddress("lep4Signal", &lep4Signal, &b_lep4Signal);
    fChain->SetBranchAddress("lep4MatchesTrigger", &lep4MatchesTrigger, &b_lep4MatchesTrigger);
    fChain->SetBranchAddress("lep4TruthCharge", &lep4TruthCharge, &b_lep4TruthCharge);
    fChain->SetBranchAddress("lep4TruthPt", &lep4TruthPt, &b_lep4TruthPt);
    fChain->SetBranchAddress("lep4TruthEta", &lep4TruthEta, &b_lep4TruthEta);
    fChain->SetBranchAddress("lep4TruthPhi", &lep4TruthPhi, &b_lep4TruthPhi);
    fChain->SetBranchAddress("lep4TruthM", &lep4TruthM, &b_lep4TruthM);
    fChain->SetBranchAddress("nJet30", &nJet30, &b_nJet30);
    fChain->SetBranchAddress("nJet25", &nJet25, &b_nJet25);
    fChain->SetBranchAddress("nTotalJet", &nTotalJet, &b_nTotalJet);
    fChain->SetBranchAddress("nBJet30_MV2c10", &nBJet30_MV2c10, &b_nBJet30_MV2c10);
    fChain->SetBranchAddress("nBJet30_MV2c10_FixedCutBEff_60", &nBJet30_MV2c10_FixedCutBEff_60, &b_nBJet30_MV2c10_FixedCutBEff_60);
    fChain->SetBranchAddress("nBJet30_MV2c10_FixedCutBEff_70", &nBJet30_MV2c10_FixedCutBEff_70, &b_nBJet30_MV2c10_FixedCutBEff_70);
    fChain->SetBranchAddress("nBJet30_MV2c10_FixedCutBEff_77", &nBJet30_MV2c10_FixedCutBEff_77, &b_nBJet30_MV2c10_FixedCutBEff_77);
    fChain->SetBranchAddress("nBJet30_MV2c10_FixedCutBEff_85", &nBJet30_MV2c10_FixedCutBEff_85, &b_nBJet30_MV2c10_FixedCutBEff_85);
    fChain->SetBranchAddress("DecayModeTTbar", &DecayModeTTbar, &b_DecayModeTTbar);
    fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
    fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
    fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
    fChain->SetBranchAddress("jetM", &jetM, &b_jetM);
    fChain->SetBranchAddress("met_Et", &met_Et, &b_met_Et);
    fChain->SetBranchAddress("met_Phi", &met_Phi, &b_met_Phi);
    fChain->SetBranchAddress("TST_Et", &TST_Et, &b_TST_Et);
    fChain->SetBranchAddress("TST_Phi", &TST_Phi, &b_TST_Phi);
    fChain->SetBranchAddress("deltaPhi_MET_TST_Phi", &deltaPhi_MET_TST_Phi, &b_deltaPhi_MET_TST_Phi);
    fChain->SetBranchAddress("mt", &mt, &b_mt);
    fChain->SetBranchAddress("meffInc30", &meffInc30, &b_meffInc30);
    fChain->SetBranchAddress("Ht30", &Ht30, &b_Ht30);
    fChain->SetBranchAddress("hadronicWMass", &hadronicWMass, &b_hadronicWMass);
    fChain->SetBranchAddress("hadronicWPt", &hadronicWPt, &b_hadronicWPt);
    fChain->SetBranchAddress("LepAplanarity", &LepAplanarity, &b_LepAplanarity);
    fChain->SetBranchAddress("JetAplanarity", &JetAplanarity, &b_JetAplanarity);
    fChain->SetBranchAddress("amt2", &amt2, &b_amt2);
    fChain->SetBranchAddress("amt2b", &amt2b, &b_amt2b);
    fChain->SetBranchAddress("amt2bWeight", &amt2bWeight, &b_amt2bWeight);
    fChain->SetBranchAddress("mt2tau", &mt2tau, &b_mt2tau);
    fChain->SetBranchAddress("mt2lj", &mt2lj, &b_mt2lj);
    fChain->SetBranchAddress("mbb", &mbb, &b_mbb);
    fChain->SetBranchAddress("mt_lep1", &mt_lep1, &b_mt_lep1);
    fChain->SetBranchAddress("mt_lep2", &mt_lep2, &b_mt_lep2);
    fChain->SetBranchAddress("mt_lep3", &mt_lep3, &b_mt_lep3);
    fChain->SetBranchAddress("mt_lep4", &mt_lep4, &b_mt_lep4);
    fChain->SetBranchAddress("METOverHT", &METOverHT, &b_METOverHT);
    fChain->SetBranchAddress("METOverJ1pT", &METOverJ1pT, &b_METOverJ1pT);
    fChain->SetBranchAddress("DPhiJ1Met", &DPhiJ1Met, &b_DPhiJ1Met);
    fChain->SetBranchAddress("METOverHTLep12", &METOverHTLep12, &b_METOverHTLep12);
    fChain->SetBranchAddress("mll", &mll, &b_mll);
    fChain->SetBranchAddress("Rll", &Rll, &b_Rll);
    fChain->SetBranchAddress("MSqTauTau_1", &MSqTauTau_1, &b_MSqTauTau_1);
    fChain->SetBranchAddress("MSqTauTau_2", &MSqTauTau_2, &b_MSqTauTau_2);
    fChain->SetBranchAddress("MTauTau", &MTauTau, &b_MTauTau);
    fChain->SetBranchAddress("RjlOverEl", &RjlOverEl, &b_RjlOverEl);
    fChain->SetBranchAddress("LepCosThetaLab", &LepCosThetaLab, &b_LepCosThetaLab);
    fChain->SetBranchAddress("LepCosThetaCoM", &LepCosThetaCoM, &b_LepCosThetaCoM);
    fChain->SetBranchAddress("mt2leplsp_0", &mt2leplsp_0, &b_mt2leplsp_0);
    fChain->SetBranchAddress("mt2leplsp_25", &mt2leplsp_25, &b_mt2leplsp_25);
    fChain->SetBranchAddress("mt2leplsp_50", &mt2leplsp_50, &b_mt2leplsp_50);
    fChain->SetBranchAddress("mt2leplsp_75", &mt2leplsp_75, &b_mt2leplsp_75);
    fChain->SetBranchAddress("mt2leplsp_90", &mt2leplsp_90, &b_mt2leplsp_90);
    fChain->SetBranchAddress("mt2leplsp_95", &mt2leplsp_95, &b_mt2leplsp_95);
    fChain->SetBranchAddress("mt2leplsp_100", &mt2leplsp_100, &b_mt2leplsp_100);
    fChain->SetBranchAddress("mt2leplsp_105", &mt2leplsp_105, &b_mt2leplsp_105);
    fChain->SetBranchAddress("mt2leplsp_110", &mt2leplsp_110, &b_mt2leplsp_110);
    fChain->SetBranchAddress("mt2leplsp_115", &mt2leplsp_115, &b_mt2leplsp_115);
    fChain->SetBranchAddress("mt2leplsp_120", &mt2leplsp_120, &b_mt2leplsp_120);
    fChain->SetBranchAddress("mt2leplsp_150", &mt2leplsp_150, &b_mt2leplsp_150);
    fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
    fChain->SetBranchAddress("leptonWeight", &leptonWeight, &b_leptonWeight);
    fChain->SetBranchAddress("eventWeight", &eventWeight, &b_eventWeight);
    fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
    fChain->SetBranchAddress("bTagWeight", &bTagWeight, &b_bTagWeight);
    fChain->SetBranchAddress("jvtWeight", &jvtWeight, &b_jvtWeight);
    fChain->SetBranchAddress("genWeightUp", &genWeightUp, &b_genWeightUp);
    fChain->SetBranchAddress("genWeightDown", &genWeightDown, &b_genWeightDown);
    fChain->SetBranchAddress("SherpaVjetsNjetsWeight", &SherpaVjetsNjetsWeight, &b_SherpaVjetsNjetsWeight);
    fChain->SetBranchAddress("HLT_mu4", &HLT_mu4, &b_HLT_mu4);
    fChain->SetBranchAddress("HLT_2mu4", &HLT_2mu4, &b_HLT_2mu4);
    fChain->SetBranchAddress("HLT_2mu10", &HLT_2mu10, &b_HLT_2mu10);
    fChain->SetBranchAddress("HLT_2mu4_j85_xe50_mht", &HLT_2mu4_j85_xe50_mht, &b_HLT_2mu4_j85_xe50_mht);
    fChain->SetBranchAddress("HLT_mu4_j125_xe90_mht", &HLT_mu4_j125_xe90_mht, &b_HLT_mu4_j125_xe90_mht);
    fChain->SetBranchAddress("HLT_xe70", &HLT_xe70, &b_HLT_xe70);
    fChain->SetBranchAddress("HLT_xe70_mht", &HLT_xe70_mht, &b_HLT_xe70_mht);
    fChain->SetBranchAddress("HLT_xe70_mht_wEFMu", &HLT_xe70_mht_wEFMu, &b_HLT_xe70_mht_wEFMu);
    fChain->SetBranchAddress("HLT_xe70_tc_lcw", &HLT_xe70_tc_lcw, &b_HLT_xe70_tc_lcw);
    fChain->SetBranchAddress("HLT_xe70_tc_lcw_wEFMu", &HLT_xe70_tc_lcw_wEFMu, &b_HLT_xe70_tc_lcw_wEFMu);
    fChain->SetBranchAddress("HLT_xe80_tc_lcw_L1XE50", &HLT_xe80_tc_lcw_L1XE50, &b_HLT_xe80_tc_lcw_L1XE50);
    fChain->SetBranchAddress("HLT_xe90_tc_lcw_L1XE50", &HLT_xe90_tc_lcw_L1XE50, &b_HLT_xe90_tc_lcw_L1XE50);
    fChain->SetBranchAddress("HLT_xe90_mht_L1XE50", &HLT_xe90_mht_L1XE50, &b_HLT_xe90_mht_L1XE50);
    fChain->SetBranchAddress("HLT_xe90_tc_lcw_wEFMu_L1XE50", &HLT_xe90_tc_lcw_wEFMu_L1XE50, &b_HLT_xe90_tc_lcw_wEFMu_L1XE50);
    fChain->SetBranchAddress("HLT_xe90_mht_wEFMu_L1XE50", &HLT_xe90_mht_wEFMu_L1XE50, &b_HLT_xe90_mht_wEFMu_L1XE50);
    fChain->SetBranchAddress("HLT_xe100_L1XE50", &HLT_xe100_L1XE50, &b_HLT_xe100_L1XE50);
    fChain->SetBranchAddress("HLT_xe100_wEFMu_L1XE50", &HLT_xe100_wEFMu_L1XE50, &b_HLT_xe100_wEFMu_L1XE50);
    fChain->SetBranchAddress("HLT_xe100_tc_lcw_L1XE50", &HLT_xe100_tc_lcw_L1XE50, &b_HLT_xe100_tc_lcw_L1XE50);
    fChain->SetBranchAddress("HLT_xe100_mht_L1XE50", &HLT_xe100_mht_L1XE50, &b_HLT_xe100_mht_L1XE50);
    fChain->SetBranchAddress("HLT_xe100_tc_lcw_wEFMu_L1XE50", &HLT_xe100_tc_lcw_wEFMu_L1XE50, &b_HLT_xe100_tc_lcw_wEFMu_L1XE50);
    fChain->SetBranchAddress("HLT_xe100_mht_wEFMu_L1XE50", &HLT_xe100_mht_wEFMu_L1XE50, &b_HLT_xe100_mht_wEFMu_L1XE50);
    fChain->SetBranchAddress("HLT_xe110_L1XE50", &HLT_xe110_L1XE50, &b_HLT_xe110_L1XE50);
    fChain->SetBranchAddress("HLT_xe110_tc_em_L1XE50", &HLT_xe110_tc_em_L1XE50, &b_HLT_xe110_tc_em_L1XE50);
    fChain->SetBranchAddress("HLT_xe110_wEFMu_L1XE50", &HLT_xe110_wEFMu_L1XE50, &b_HLT_xe110_wEFMu_L1XE50);
    fChain->SetBranchAddress("HLT_xe110_tc_em_wEFMu_L1XE50", &HLT_xe110_tc_em_wEFMu_L1XE50, &b_HLT_xe110_tc_em_wEFMu_L1XE50);
    fChain->SetBranchAddress("HLT_xe110_mht_L1XE50", &HLT_xe110_mht_L1XE50, &b_HLT_xe110_mht_L1XE50);
    fChain->SetBranchAddress("HLT_xe90_mht_L1XE40", &HLT_xe90_mht_L1XE40, &b_HLT_xe90_mht_L1XE40);
    fChain->SetBranchAddress("HLT_xe50_mht_L1XE20", &HLT_xe50_mht_L1XE20, &b_HLT_xe50_mht_L1XE20);
    fChain->SetBranchAddress("HLT_j85_L1J40", &HLT_j85_L1J40, &b_HLT_j85_L1J40);
    fChain->SetBranchAddress("HLT_j125_L1J50", &HLT_j125_L1J50, &b_HLT_j125_L1J50);
    fChain->SetBranchAddress("HLT_e26_lhtight_nod0_ivarloose", &HLT_e26_lhtight_nod0_ivarloose, &b_HLT_e26_lhtight_nod0_ivarloose);
    fChain->SetBranchAddress("HLT_e60_lhmedium_nod0", &HLT_e60_lhmedium_nod0, &b_HLT_e60_lhmedium_nod0);
    fChain->SetBranchAddress("HLT_e60_medium", &HLT_e60_medium, &b_HLT_e60_medium);
    fChain->SetBranchAddress("HLT_e140_lhloose_nod0", &HLT_e140_lhloose_nod0, &b_HLT_e140_lhloose_nod0);
    fChain->SetBranchAddress("HLT_mu26_ivarmedium", &HLT_mu26_ivarmedium, &b_HLT_mu26_ivarmedium);
    fChain->SetBranchAddress("ttbarNNLOWeight", &ttbarNNLOWeight, &b_ttbarNNLOWeight);
    fChain->SetBranchAddress("ttbarNNLOWeightUp", &ttbarNNLOWeightUp, &b_ttbarNNLOWeightUp);
    fChain->SetBranchAddress("ttbarNNLOWeightDown", &ttbarNNLOWeightDown, &b_ttbarNNLOWeightDown);
    fChain->SetBranchAddress("truthTopPt", &truthTopPt, &b_truthTopPt);
    fChain->SetBranchAddress("truthAntiTopPt", &truthAntiTopPt, &b_truthAntiTopPt);
    fChain->SetBranchAddress("truthTtbarPt", &truthTtbarPt, &b_truthTtbarPt);
    fChain->SetBranchAddress("truthTtbarM", &truthTtbarM, &b_truthTtbarM);
    fChain->SetBranchAddress("x1", &x1, &b_x1);
    fChain->SetBranchAddress("x2", &x2, &b_x2);
    fChain->SetBranchAddress("pdf1", &pdf1, &b_pdf1);
    fChain->SetBranchAddress("pdf2", &pdf2, &b_pdf2);
    fChain->SetBranchAddress("scalePDF", &scalePDF, &b_scalePDF);
    fChain->SetBranchAddress("id1", &id1, &b_id1);
    fChain->SetBranchAddress("id2", &id2, &b_id2);
    fChain->SetBranchAddress("PRWHash", &PRWHash, &b_PRWHash);
    fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
    fChain->SetBranchAddress("xsec", &xsec, &b_xsec);
    fChain->SetBranchAddress("TrueHt", &TrueHt, &b_TrueHt);
    fChain->SetBranchAddress("DatasetNumber", &DatasetNumber, &b_DatasetNumber);
    fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
    fChain->SetBranchAddress("RandomRunNumber", &RandomRunNumber, &b_RandomRunNumber);
    fChain->SetBranchAddress("FS", &FS, &b_FS);

    return EL::StatusCode::SUCCESS;
}



EL::StatusCode ytEventSelection :: initialize ()
{
    // Here you do everything that you need to do after the first input
    // file has been connected and before the first event is processed,
    // e.g. create additional histograms based on which variables are
    // available in the input files.  You can also create all of your
    // histograms and trees in here, but be aware that this method
    // doesn't get called if no events are processed.  So any objects
    // you create here won't be available in the output if you have no
    // input events.
    return EL::StatusCode::SUCCESS;
}



EL::StatusCode ytEventSelection :: execute ()
{
    // Here you do everything that needs to be done on every single
    // events, e.g. read input variables, apply cuts, and fill
    // histograms and trees.  This is where most of your actual analysis
    // code will go.

    wk()->tree()->GetEntry(wk()->treeEntry());



    return EL::StatusCode::SUCCESS;
}



EL::StatusCode ytEventSelection :: postExecute ()
{
    // Here you do everything that needs to be done after the main event
    // processing.  This is typically very rare, particularly in user
    // code.  It is mainly used in implementing the NTupleSvc.
    return EL::StatusCode::SUCCESS;
}



EL::StatusCode ytEventSelection :: finalize ()
{
    // This method is the mirror image of initialize(), meaning it gets
    // called after the last event has been processed on the worker node
    // and allows you to finish up any objects you created in
    // initialize() before they are written to disk.  This is actually
    // fairly rare, since this happens separately for each worker node.
    // Most of the time you want to do your post-processing on the
    // submission node after all your histogram outputs have been
    // merged.  This is different from histFinalize() in that it only
    // gets called on worker nodes that processed input events.
    return EL::StatusCode::SUCCESS;
}



EL::StatusCode ytEventSelection :: histFinalize ()
{
    // This method is the mirror image of histInitialize(), meaning it
    // gets called after the last event has been processed on the worker
    // node and allows you to finish up any objects you created in
    // histInitialize() before they are written to disk.  This is
    // actually fairly rare, since this happens separately for each
    // worker node.  Most of the time you want to do your
    // post-processing on the submission node after all your histogram
    // outputs have been merged.  This is different from finalize() in
    // that it gets called on all worker nodes regardless of whether
    // they processed input events.
    return EL::StatusCode::SUCCESS;
}
