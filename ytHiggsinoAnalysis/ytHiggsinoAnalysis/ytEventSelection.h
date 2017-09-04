#ifndef ytEventSelection_ytEventSelection_H
#define ytEventSelection_ytEventSelection_H

#include <EventLoop/Algorithm.h>

#include <TROOT.h>
#include <TChain.h>
// #include <TFile.h>
// #include <TString.h>
// #include <TCanvas.h>
// #include <TLegend.h>
#include <TH1.h>

#include "ytHiggsinoAnalysis/yt_regions.h"
#include "ytHiggsinoAnalysis/yt_cutflows.h"

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <typeinfo>
#include <algorithm>
using namespace std;

class ytEventSelection : public EL::Algorithm
{
    // put your configuration variables here as public variables.
    // that way they can be set directly from CINT and python.
public:
    // float cutValue;

    yt_regions *m_region; //!
    yt_cutflows *m_cutflows; //!

    bool isMC;
    bool isCutflow;
    bool isOptimization;
    string analysis_type;
    string sample_type;
    string sample;
    float luminosity;

    // double weighted_event_counts[6]; //!

    // variables that don't get filled at submission time should be
    // protected from being send from the submission node to the worker
    // node (done by the //!)
public:
    // Tree *myTree; //!
    // TH1 *myHist; //!
    //
    // Tree and branches copy from TSelector
    //
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain

    // Declaration of leaf types
    Double_t        trigWeight_metTrig; //!
    Bool_t          trigMatch_metTrig; //!
    Double_t        trigWeight_singleMuonTrig; //!
    Bool_t          trigMatch_singleMuonTrig; //!
    Double_t        trigWeight_singleElectronTrig; //!
    Bool_t          trigMatch_singleElectronTrig; //!
    Bool_t          HLT_2mu4_j85_xe50_mht_emul; //!
    Bool_t          HLT_mu4_j125_xe90_mht_emul; //!
    Float_t         mu; //!
    Int_t           nVtx; //!
    Int_t           nLep_base; //!
    Int_t           nLep_signal; //!
    Int_t           lep1Flavor; //!
    Int_t           lep1Charge; //!
    Int_t           lep1Author; //!
    Float_t         lep1Pt; //!
    Float_t         lep1Eta; //!
    Float_t         lep1Phi; //!
    Float_t         lep1M; //!
    Float_t         lep1D0; //!
    Float_t         lep1D0Sig; //!
    Float_t         lep1Z0; //!
    Float_t         lep1Z0SinTheta; //!
    Float_t         lep1Topoetcone20; //!
    Float_t         lep1Ptvarcone20; //!
    Float_t         lep1Ptvarcone30; //!
    Float_t         lep1CorrTopoetcone20; //!
    Float_t         lep1CorrPtvarcone20; //!
    Float_t         lep1CorrPtvarcone30; //!
    Bool_t          lep1PassOR; //!
    Int_t           lep1Type; //!
    Int_t           lep1Origin; //!
    Int_t           lep1EgMotherType; //!
    Int_t           lep1EgMotherOrigin; //!
    Int_t           lep1NPix; //!
    Bool_t          lep1PassBL; //!
    Bool_t          lep1VeryLoose; //!
    Bool_t          lep1Loose; //!
    Bool_t          lep1Medium; //!
    Bool_t          lep1Tight; //!
    Bool_t          lep1IsoLoose; //!
    Bool_t          lep1IsoTight; //!
    Bool_t          lep1IsoGradient; //!
    Bool_t          lep1IsoGradientLoose; //!
    Bool_t          lep1IsoLooseTrackOnly; //!
    Bool_t          lep1IsoFixedCutLoose; //!
    Bool_t          lep1IsoFixedCutTight; //!
    Bool_t          lep1IsoFixedCutTightTrackOnly; //!
    Bool_t          lep1IsoCorrLoose; //!
    Bool_t          lep1IsoCorrTight; //!
    Bool_t          lep1IsoCorrGradient; //!
    Bool_t          lep1IsoCorrGradientLoose; //!
    Bool_t          lep1IsoCorrLooseTrackOnly; //!
    Bool_t          lep1IsoCorrFixedCutLoose; //!
    Bool_t          lep1IsoCorrFixedCutTight; //!
    Bool_t          lep1IsoCorrFixedCutTightTrackOnly; //!
    Bool_t          lep1Signal; //!
    Bool_t          lep1TruthMatched; //!
    Int_t           lep1TruthCharge; //!
    Float_t         lep1TruthPt; //!
    Float_t         lep1TruthEta; //!
    Float_t         lep1TruthPhi; //!
    Float_t         lep1TruthM; //!
    Int_t           lep2Flavor; //!
    Int_t           lep2Charge; //!
    Int_t           lep2Author; //!
    Float_t         lep2Pt; //!
    Float_t         lep2Eta; //!
    Float_t         lep2Phi; //!
    Float_t         lep2M; //!
    Float_t         lep2D0; //!
    Float_t         lep2D0Sig; //!
    Float_t         lep2Z0; //!
    Float_t         lep2Z0SinTheta; //!
    Float_t         lep2Topoetcone20; //!
    Float_t         lep2Ptvarcone20; //!
    Float_t         lep2Ptvarcone30; //!
    Float_t         lep2CorrTopoetcone20; //!
    Float_t         lep2CorrPtvarcone20; //!
    Float_t         lep2CorrPtvarcone30; //!
    Bool_t          lep2PassOR; //!
    Int_t           lep2Type; //!
    Int_t           lep2Origin; //!
    Int_t           lep2EgMotherType; //!
    Int_t           lep2EgMotherOrigin; //!
    Int_t           lep2NPix; //!
    Bool_t          lep2PassBL; //!
    Bool_t          lep2VeryLoose; //!
    Bool_t          lep2Loose; //!
    Bool_t          lep2Medium; //!
    Bool_t          lep2Tight; //!
    Bool_t          lep2IsoLoose; //!
    Bool_t          lep2IsoTight; //!
    Bool_t          lep2IsoGradient; //!
    Bool_t          lep2IsoGradientLoose; //!
    Bool_t          lep2IsoLooseTrackOnly; //!
    Bool_t          lep2IsoFixedCutLoose; //!
    Bool_t          lep2IsoFixedCutTight; //!
    Bool_t          lep2IsoFixedCutTightTrackOnly; //!
    Bool_t          lep2IsoCorrLoose; //!
    Bool_t          lep2IsoCorrTight; //!
    Bool_t          lep2IsoCorrGradient; //!
    Bool_t          lep2IsoCorrGradientLoose; //!
    Bool_t          lep2IsoCorrLooseTrackOnly; //!
    Bool_t          lep2IsoCorrFixedCutLoose; //!
    Bool_t          lep2IsoCorrFixedCutTight; //!
    Bool_t          lep2IsoCorrFixedCutTightTrackOnly; //!
    Bool_t          lep2Signal; //!
    Bool_t          lep2TruthMatched; //!
    Int_t           lep2TruthCharge; //!
    Float_t         lep2TruthPt; //!
    Float_t         lep2TruthEta; //!
    Float_t         lep2TruthPhi; //!
    Float_t         lep2TruthM; //!
    Int_t           lep3Flavor; //!
    Int_t           lep3Charge; //!
    Int_t           lep3Author; //!
    Float_t         lep3Pt; //!
    Float_t         lep3Eta; //!
    Float_t         lep3Phi; //!
    Float_t         lep3M; //!
    Float_t         lep3D0; //!
    Float_t         lep3D0Sig; //!
    Float_t         lep3Z0; //!
    Float_t         lep3Z0SinTheta; //!
    Float_t         lep3Topoetcone20; //!
    Float_t         lep3Ptvarcone20; //!
    Float_t         lep3Ptvarcone30; //!
    Float_t         lep3CorrTopoetcone20; //!
    Float_t         lep3CorrPtvarcone20; //!
    Float_t         lep3CorrPtvarcone30; //!
    Bool_t          lep3PassOR; //!
    Int_t           lep3Type; //!
    Int_t           lep3Origin; //!
    Int_t           lep3EgMotherType; //!
    Int_t           lep3EgMotherOrigin; //!
    Int_t           lep3NPix; //!
    Bool_t          lep3PassBL; //!
    Bool_t          lep3VeryLoose; //!
    Bool_t          lep3Loose; //!
    Bool_t          lep3Medium; //!
    Bool_t          lep3Tight; //!
    Bool_t          lep3IsoLoose; //!
    Bool_t          lep3IsoTight; //!
    Bool_t          lep3IsoGradient; //!
    Bool_t          lep3IsoGradientLoose; //!
    Bool_t          lep3IsoLooseTrackOnly; //!
    Bool_t          lep3IsoFixedCutLoose; //!
    Bool_t          lep3IsoFixedCutTight; //!
    Bool_t          lep3IsoFixedCutTightTrackOnly; //!
    Bool_t          lep3IsoCorrLoose; //!
    Bool_t          lep3IsoCorrTight; //!
    Bool_t          lep3IsoCorrGradient; //!
    Bool_t          lep3IsoCorrGradientLoose; //!
    Bool_t          lep3IsoCorrLooseTrackOnly; //!
    Bool_t          lep3IsoCorrFixedCutLoose; //!
    Bool_t          lep3IsoCorrFixedCutTight; //!
    Bool_t          lep3IsoCorrFixedCutTightTrackOnly; //!
    Bool_t          lep3Signal; //!
    Bool_t          lep3TruthMatched; //!
    Int_t           lep3TruthCharge; //!
    Float_t         lep3TruthPt; //!
    Float_t         lep3TruthEta; //!
    Float_t         lep3TruthPhi; //!
    Float_t         lep3TruthM; //!
    Int_t           lep4Flavor; //!
    Int_t           lep4Charge; //!
    Int_t           lep4Author; //!
    Float_t         lep4Pt; //!
    Float_t         lep4Eta; //!
    Float_t         lep4Phi; //!
    Float_t         lep4M; //!
    Float_t         lep4D0; //!
    Float_t         lep4D0Sig; //!
    Float_t         lep4Z0; //!
    Float_t         lep4Z0SinTheta; //!
    Float_t         lep4Topoetcone20; //!
    Float_t         lep4Ptvarcone20; //!
    Float_t         lep4Ptvarcone30; //!
    Float_t         lep4CorrTopoetcone20; //!
    Float_t         lep4CorrPtvarcone20; //!
    Float_t         lep4CorrPtvarcone30; //!
    Bool_t          lep4PassOR; //!
    Int_t           lep4Type; //!
    Int_t           lep4Origin; //!
    Int_t           lep4EgMotherType; //!
    Int_t           lep4EgMotherOrigin; //!
    Int_t           lep4NPix; //!
    Bool_t          lep4PassBL; //!
    Bool_t          lep4VeryLoose; //!
    Bool_t          lep4Loose; //!
    Bool_t          lep4Medium; //!
    Bool_t          lep4Tight; //!
    Bool_t          lep4IsoLoose; //!
    Bool_t          lep4IsoTight; //!
    Bool_t          lep4IsoGradient; //!
    Bool_t          lep4IsoGradientLoose; //!
    Bool_t          lep4IsoLooseTrackOnly; //!
    Bool_t          lep4IsoFixedCutLoose; //!
    Bool_t          lep4IsoFixedCutTight; //!
    Bool_t          lep4IsoFixedCutTightTrackOnly; //!
    Bool_t          lep4IsoCorrLoose; //!
    Bool_t          lep4IsoCorrTight; //!
    Bool_t          lep4IsoCorrGradient; //!
    Bool_t          lep4IsoCorrGradientLoose; //!
    Bool_t          lep4IsoCorrLooseTrackOnly; //!
    Bool_t          lep4IsoCorrFixedCutLoose; //!
    Bool_t          lep4IsoCorrFixedCutTight; //!
    Bool_t          lep4IsoCorrFixedCutTightTrackOnly; //!
    Bool_t          lep4Signal; //!
    Bool_t          lep4TruthMatched; //!
    Int_t           lep4TruthCharge; //!
    Float_t         lep4TruthPt; //!
    Float_t         lep4TruthEta; //!
    Float_t         lep4TruthPhi; //!
    Float_t         lep4TruthM; //!
    Int_t           nJet30; //!
    Int_t           nJet25; //!
    Int_t           nJet20; //!
    Int_t           nTotalJet; //!
    Int_t           nTotalJet20; //!
    Int_t           nBJet30_MV2c10; //!
    Int_t           nBJet20_MV2c10; //!
    Int_t           nBJet30_MV2c10_FixedCutBEff_60; //!
    Int_t           nBJet30_MV2c10_FixedCutBEff_70; //!
    Int_t           nBJet30_MV2c10_FixedCutBEff_77; //!
    Int_t           nBJet30_MV2c10_FixedCutBEff_85; //!
    Int_t           nBJet20_MV2c10_FixedCutBEff_60; //!
    Int_t           nBJet20_MV2c10_FixedCutBEff_70; //!
    Int_t           nBJet20_MV2c10_FixedCutBEff_77; //!
    Int_t           nBJet20_MV2c10_FixedCutBEff_85; //!
    Int_t           DecayModeTTbar; //!
    vector<float>   *jetPt; //!
    vector<float>   *jetEta; //!
    vector<float>   *jetPhi; //!
    vector<float>   *jetM; //!
    vector<float>   *jetTileEnergy; //!
    Float_t         vectorSumJetsPt; //!
    Float_t         vectorSumJetsEta; //!
    Float_t         vectorSumJetsPhi; //!
    Float_t         vectorSumJetsM; //!
    Float_t         dPhiVectorSumJetsMET; //!
    Float_t         met_Et; //!
    Float_t         met_Phi; //!
    Float_t         TST_Et; //!
    Float_t         TST_Phi; //!
    Float_t         met_track_Et; //!
    Float_t         met_track_Phi; //!
    Float_t         deltaPhi_MET_TST_Phi; //!
    Float_t         mt; //!
    Float_t         meffInc30; //!
    Float_t         Ht30; //!
    Float_t         hadronicWMass; //!
    Float_t         hadronicWPt; //!
    Float_t         LepAplanarity; //!
    Float_t         JetAplanarity; //!
    Float_t         amt2; //!
    Float_t         amt2b; //!
    Float_t         amt2bWeight; //!
    Float_t         mt2tau; //!
    Float_t         mt2lj; //!
    Float_t         mbb; //!
    Float_t         mt_lep1; //!
    Float_t         mt_lep2; //!
    Float_t         mt_lep3; //!
    Float_t         mt_lep4; //!
    Float_t         mt_lep1_metTrack; //!
    Float_t         mt_lep2_metTrack; //!
    Float_t         mt_lep3_metTrack; //!
    Float_t         mt_lep4_metTrack; //!
    Float_t         METOverHT; //!
    Float_t         METOverJ1pT; //!
    Float_t         METTrackOverHT; //!
    Float_t         METTrackOverJ1pT; //!
    Float_t         DPhiJ1Met; //!
    Float_t         DPhiJ2Met; //!
    Float_t         DPhiJ3Met; //!
    Float_t         DPhiJ4Met; //!
    Float_t         minDPhi4JetsMet; //!
    Float_t         minDPhiAllJetsMet; //!
    Float_t         DPhiJ1MetTrack; //!
    Float_t         DPhiJ2MetTrack; //!
    Float_t         DPhiJ3MetTrack; //!
    Float_t         DPhiJ4MetTrack; //!
    Float_t         minDPhi4JetsMetTrack; //!
    Float_t         minDPhiAllJetsMetTrack; //!
    Float_t         METOverHTLep; //!
    Float_t         METTrackOverHTLep; //!
    Float_t         mll; //!
    Float_t         Rll; //!
    Float_t         Ptll; //!
    Float_t         dPhiPllMet; //!
    Float_t         dPhiPllMetTrack; //!
    Float_t         METRel; //!
    Float_t         METTrackRel; //!
    Float_t         dPhiNearMet; //!
    Float_t         dPhiNearMetTrack; //!
    Float_t         dPhiMetAndMetTrack; //!
    Float_t         MSqTauTau_1; //!
    Float_t         MSqTauTau_2; //!
    Float_t         MTauTau; //!
    Float_t         MSqTauTau_1_metTrack; //!
    Float_t         MSqTauTau_2_metTrack; //!
    Float_t         MTauTau_metTrack; //!
    Float_t         RjlOverEl; //!
    Float_t         LepCosThetaLab; //!
    Float_t         LepCosThetaCoM; //!
    Float_t         mt2leplsp_0; //!
    Float_t         mt2leplsp_25; //!
    Float_t         mt2leplsp_50; //!
    Float_t         mt2leplsp_75; //!
    Float_t         mt2leplsp_90; //!
    Float_t         mt2leplsp_95; //!
    Float_t         mt2leplsp_100; //!
    Float_t         mt2leplsp_105; //!
    Float_t         mt2leplsp_110; //!
    Float_t         mt2leplsp_115; //!
    Float_t         mt2leplsp_120; //!
    Float_t         mt2leplsp_150; //!
    Float_t         mt2leplsp_175; //!
    Float_t         mt2leplsp_200; //!
    Float_t         mt2leplsp_250; //!
    Float_t         mt2leplsp_300; //!
    Float_t         mt2leplsp_0_metTrack; //!
    Float_t         mt2leplsp_25_metTrack; //!
    Float_t         mt2leplsp_50_metTrack; //!
    Float_t         mt2leplsp_75_metTrack; //!
    Float_t         mt2leplsp_90_metTrack; //!
    Float_t         mt2leplsp_95_metTrack; //!
    Float_t         mt2leplsp_100_metTrack; //!
    Float_t         mt2leplsp_105_metTrack; //!
    Float_t         mt2leplsp_110_metTrack; //!
    Float_t         mt2leplsp_115_metTrack; //!
    Float_t         mt2leplsp_120_metTrack; //!
    Float_t         mt2leplsp_150_metTrack; //!
    Float_t         mt2leplsp_175_metTrack; //!
    Float_t         mt2leplsp_200_metTrack; //!
    Float_t         mt2leplsp_250_metTrack; //!
    Float_t         mt2leplsp_300_metTrack; //!
    Double_t        pileupWeight; //!
    Double_t        leptonWeight; //!
    Double_t        eventWeight; //!
    Double_t        genWeight; //!
    Double_t        bTagWeight; //!
    Double_t        jvtWeight; //!
    Double_t        genWeightUp; //!
    Double_t        genWeightDown; //!
    vector<float>   *LHE3Weights; //!
    Double_t        FFWeight; //!
    Int_t           nLep_antiID; //!
    Bool_t          lep1AntiID; //!
    Bool_t          lep2AntiID; //!
    Bool_t          lep3AntiID; //!
    Bool_t          lep4AntiID; //!
    Int_t           nLep_signalActual; //!
    Bool_t          lep1SignalActual; //!
    Bool_t          lep2SignalActual; //!
    Bool_t          lep3SignalActual; //!
    Bool_t          lep4SignalActual; //!
    Bool_t          HLT_mu4; //!
    Bool_t          HLT_2mu4; //!
    Bool_t          HLT_2mu10; //!
    Bool_t          HLT_2mu4_j85_xe50_mht; //!
    Bool_t          HLT_mu4_j125_xe90_mht; //!
    Bool_t          HLT_xe70; //!
    Bool_t          HLT_xe70_mht; //!
    Bool_t          HLT_xe70_mht_wEFMu; //!
    Bool_t          HLT_xe70_tc_lcw; //!
    Bool_t          HLT_xe70_tc_lcw_wEFMu; //!
    Bool_t          HLT_xe80_tc_lcw_L1XE50; //!
    Bool_t          HLT_xe90_tc_lcw_L1XE50; //!
    Bool_t          HLT_xe90_mht_L1XE50; //!
    Bool_t          HLT_xe90_tc_lcw_wEFMu_L1XE50; //!
    Bool_t          HLT_xe90_mht_wEFMu_L1XE50; //!
    Bool_t          HLT_xe100_L1XE50; //!
    Bool_t          HLT_xe100_wEFMu_L1XE50; //!
    Bool_t          HLT_xe100_tc_lcw_L1XE50; //!
    Bool_t          HLT_xe100_mht_L1XE50; //!
    Bool_t          HLT_xe100_tc_lcw_wEFMu_L1XE50; //!
    Bool_t          HLT_xe100_mht_wEFMu_L1XE50; //!
    Bool_t          HLT_xe110_L1XE50; //!
    Bool_t          HLT_xe110_tc_em_L1XE50; //!
    Bool_t          HLT_xe110_wEFMu_L1XE50; //!
    Bool_t          HLT_xe110_tc_em_wEFMu_L1XE50; //!
    Bool_t          HLT_xe110_mht_L1XE50; //!
    Bool_t          HLT_xe90_mht_L1XE40; //!
    Bool_t          HLT_xe50_mht_L1XE20; //!
    Bool_t          HLT_j85_L1J40; //!
    Bool_t          HLT_j125_L1J50; //!
    Bool_t          HLT_e26_lhtight_nod0_ivarloose; //!
    Bool_t          HLT_e60_lhmedium_nod0; //!
    Bool_t          HLT_e60_medium; //!
    Bool_t          HLT_e140_lhloose_nod0; //!
    Bool_t          HLT_mu26_ivarmedium; //!
    Double_t        ttbarNNLOWeight; //!
    Double_t        ttbarNNLOWeightUp; //!
    Double_t        ttbarNNLOWeightDown; //!
    Float_t         truthTopPt; //!
    Float_t         truthAntiTopPt; //!
    Float_t         truthTtbarPt; //!
    Float_t         truthTtbarM; //!
    Float_t         x1; //!
    Float_t         x2; //!
    Float_t         pdf1; //!
    Float_t         pdf2; //!
    Float_t         scalePDF; //!
    Int_t           id1; //!
    Int_t           id2; //!
    ULong64_t       PRWHash; //!
    ULong64_t       EventNumber; //!
    Float_t         xsec; //!
    Float_t         TrueHt; //!
    Int_t           DatasetNumber; //!
    Int_t           RunNumber; //!
    Int_t           RandomRunNumber; //!
    Int_t           FS; //!

    // List of branches
    TBranch        *b_trigWeight_metTrig;   //!
    TBranch        *b_trigMatch_metTrig;   //!
    TBranch        *b_trigWeight_singleMuonTrig;   //!
    TBranch        *b_trigMatch_singleMuonTrig;   //!
    TBranch        *b_trigWeight_singleElectronTrig;   //!
    TBranch        *b_trigMatch_singleElectronTrig;   //!
    TBranch        *b_HLT_2mu4_j85_xe50_mht_emul;   //!
    TBranch        *b_HLT_mu4_j125_xe90_mht_emul;   //!
    TBranch        *b_mu;   //!
    TBranch        *b_nVtx;   //!
    TBranch        *b_nLep_base;   //!
    TBranch        *b_nLep_signal;   //!
    TBranch        *b_lep1Flavor;   //!
    TBranch        *b_lep1Charge;   //!
    TBranch        *b_lep1Author;   //!
    TBranch        *b_lep1Pt;   //!
    TBranch        *b_lep1Eta;   //!
    TBranch        *b_lep1Phi;   //!
    TBranch        *b_lep1M;   //!
    TBranch        *b_lep1D0;   //!
    TBranch        *b_lep1D0Sig;   //!
    TBranch        *b_lep1Z0;   //!
    TBranch        *b_lep1Z0SinTheta;   //!
    TBranch        *b_lep1Topoetcone20;   //!
    TBranch        *b_lep1Ptvarcone20;   //!
    TBranch        *b_lep1Ptvarcone30;   //!
    TBranch        *b_lep1CorrTopoetcone20;   //!
    TBranch        *b_lep1CorrPtvarcone20;   //!
    TBranch        *b_lep1CorrPtvarcone30;   //!
    TBranch        *b_lep1PassOR;   //!
    TBranch        *b_lep1Type;   //!
    TBranch        *b_lep1Origin;   //!
    TBranch        *b_lep1EgMotherType;   //!
    TBranch        *b_lep1EgMotherOrigin;   //!
    TBranch        *b_lep1NPix;   //!
    TBranch        *b_lep1PassBL;   //!
    TBranch        *b_lep1VeryLoose;   //!
    TBranch        *b_lep1Loose;   //!
    TBranch        *b_lep1Medium;   //!
    TBranch        *b_lep1Tight;   //!
    TBranch        *b_lep1IsoLoose;   //!
    TBranch        *b_lep1IsoTight;   //!
    TBranch        *b_lep1IsoGradient;   //!
    TBranch        *b_lep1IsoGradientLoose;   //!
    TBranch        *b_lep1IsoLooseTrackOnly;   //!
    TBranch        *b_lep1IsoFixedCutLoose;   //!
    TBranch        *b_lep1IsoFixedCutTight;   //!
    TBranch        *b_lep1IsoFixedCutTightTrackOnly;   //!
    TBranch        *b_lep1IsoCorrLoose;   //!
    TBranch        *b_lep1IsoCorrTight;   //!
    TBranch        *b_lep1IsoCorrGradient;   //!
    TBranch        *b_lep1IsoCorrGradientLoose;   //!
    TBranch        *b_lep1IsoCorrLooseTrackOnly;   //!
    TBranch        *b_lep1IsoCorrFixedCutLoose;   //!
    TBranch        *b_lep1IsoCorrFixedCutTight;   //!
    TBranch        *b_lep1IsoCorrFixedCutTightTrackOnly;   //!
    TBranch        *b_lep1Signal;   //!
    TBranch        *b_lep1TruthMatched;   //!
    TBranch        *b_lep1TruthCharge;   //!
    TBranch        *b_lep1TruthPt;   //!
    TBranch        *b_lep1TruthEta;   //!
    TBranch        *b_lep1TruthPhi;   //!
    TBranch        *b_lep1TruthM;   //!
    TBranch        *b_lep2Flavor;   //!
    TBranch        *b_lep2Charge;   //!
    TBranch        *b_lep2Author;   //!
    TBranch        *b_lep2Pt;   //!
    TBranch        *b_lep2Eta;   //!
    TBranch        *b_lep2Phi;   //!
    TBranch        *b_lep2M;   //!
    TBranch        *b_lep2D0;   //!
    TBranch        *b_lep2D0Sig;   //!
    TBranch        *b_lep2Z0;   //!
    TBranch        *b_lep2Z0SinTheta;   //!
    TBranch        *b_lep2Topoetcone20;   //!
    TBranch        *b_lep2Ptvarcone20;   //!
    TBranch        *b_lep2Ptvarcone30;   //!
    TBranch        *b_lep2CorrTopoetcone20;   //!
    TBranch        *b_lep2CorrPtvarcone20;   //!
    TBranch        *b_lep2CorrPtvarcone30;   //!
    TBranch        *b_lep2PassOR;   //!
    TBranch        *b_lep2Type;   //!
    TBranch        *b_lep2Origin;   //!
    TBranch        *b_lep2EgMotherType;   //!
    TBranch        *b_lep2EgMotherOrigin;   //!
    TBranch        *b_lep2NPix;   //!
    TBranch        *b_lep2PassBL;   //!
    TBranch        *b_lep2VeryLoose;   //!
    TBranch        *b_lep2Loose;   //!
    TBranch        *b_lep2Medium;   //!
    TBranch        *b_lep2Tight;   //!
    TBranch        *b_lep2IsoLoose;   //!
    TBranch        *b_lep2IsoTight;   //!
    TBranch        *b_lep2IsoGradient;   //!
    TBranch        *b_lep2IsoGradientLoose;   //!
    TBranch        *b_lep2IsoLooseTrackOnly;   //!
    TBranch        *b_lep2IsoFixedCutLoose;   //!
    TBranch        *b_lep2IsoFixedCutTight;   //!
    TBranch        *b_lep2IsoFixedCutTightTrackOnly;   //!
    TBranch        *b_lep2IsoCorrLoose;   //!
    TBranch        *b_lep2IsoCorrTight;   //!
    TBranch        *b_lep2IsoCorrGradient;   //!
    TBranch        *b_lep2IsoCorrGradientLoose;   //!
    TBranch        *b_lep2IsoCorrLooseTrackOnly;   //!
    TBranch        *b_lep2IsoCorrFixedCutLoose;   //!
    TBranch        *b_lep2IsoCorrFixedCutTight;   //!
    TBranch        *b_lep2IsoCorrFixedCutTightTrackOnly;   //!
    TBranch        *b_lep2Signal;   //!
    TBranch        *b_lep2TruthMatched;   //!
    TBranch        *b_lep2TruthCharge;   //!
    TBranch        *b_lep2TruthPt;   //!
    TBranch        *b_lep2TruthEta;   //!
    TBranch        *b_lep2TruthPhi;   //!
    TBranch        *b_lep2TruthM;   //!
    TBranch        *b_lep3Flavor;   //!
    TBranch        *b_lep3Charge;   //!
    TBranch        *b_lep3Author;   //!
    TBranch        *b_lep3Pt;   //!
    TBranch        *b_lep3Eta;   //!
    TBranch        *b_lep3Phi;   //!
    TBranch        *b_lep3M;   //!
    TBranch        *b_lep3D0;   //!
    TBranch        *b_lep3D0Sig;   //!
    TBranch        *b_lep3Z0;   //!
    TBranch        *b_lep3Z0SinTheta;   //!
    TBranch        *b_lep3Topoetcone20;   //!
    TBranch        *b_lep3Ptvarcone20;   //!
    TBranch        *b_lep3Ptvarcone30;   //!
    TBranch        *b_lep3CorrTopoetcone20;   //!
    TBranch        *b_lep3CorrPtvarcone20;   //!
    TBranch        *b_lep3CorrPtvarcone30;   //!
    TBranch        *b_lep3PassOR;   //!
    TBranch        *b_lep3Type;   //!
    TBranch        *b_lep3Origin;   //!
    TBranch        *b_lep3EgMotherType;   //!
    TBranch        *b_lep3EgMotherOrigin;   //!
    TBranch        *b_lep3NPix;   //!
    TBranch        *b_lep3PassBL;   //!
    TBranch        *b_lep3VeryLoose;   //!
    TBranch        *b_lep3Loose;   //!
    TBranch        *b_lep3Medium;   //!
    TBranch        *b_lep3Tight;   //!
    TBranch        *b_lep3IsoLoose;   //!
    TBranch        *b_lep3IsoTight;   //!
    TBranch        *b_lep3IsoGradient;   //!
    TBranch        *b_lep3IsoGradientLoose;   //!
    TBranch        *b_lep3IsoLooseTrackOnly;   //!
    TBranch        *b_lep3IsoFixedCutLoose;   //!
    TBranch        *b_lep3IsoFixedCutTight;   //!
    TBranch        *b_lep3IsoFixedCutTightTrackOnly;   //!
    TBranch        *b_lep3IsoCorrLoose;   //!
    TBranch        *b_lep3IsoCorrTight;   //!
    TBranch        *b_lep3IsoCorrGradient;   //!
    TBranch        *b_lep3IsoCorrGradientLoose;   //!
    TBranch        *b_lep3IsoCorrLooseTrackOnly;   //!
    TBranch        *b_lep3IsoCorrFixedCutLoose;   //!
    TBranch        *b_lep3IsoCorrFixedCutTight;   //!
    TBranch        *b_lep3IsoCorrFixedCutTightTrackOnly;   //!
    TBranch        *b_lep3Signal;   //!
    TBranch        *b_lep3TruthMatched;   //!
    TBranch        *b_lep3TruthCharge;   //!
    TBranch        *b_lep3TruthPt;   //!
    TBranch        *b_lep3TruthEta;   //!
    TBranch        *b_lep3TruthPhi;   //!
    TBranch        *b_lep3TruthM;   //!
    TBranch        *b_lep4Flavor;   //!
    TBranch        *b_lep4Charge;   //!
    TBranch        *b_lep4Author;   //!
    TBranch        *b_lep4Pt;   //!
    TBranch        *b_lep4Eta;   //!
    TBranch        *b_lep4Phi;   //!
    TBranch        *b_lep4M;   //!
    TBranch        *b_lep4D0;   //!
    TBranch        *b_lep4D0Sig;   //!
    TBranch        *b_lep4Z0;   //!
    TBranch        *b_lep4Z0SinTheta;   //!
    TBranch        *b_lep4Topoetcone20;   //!
    TBranch        *b_lep4Ptvarcone20;   //!
    TBranch        *b_lep4Ptvarcone30;   //!
    TBranch        *b_lep4CorrTopoetcone20;   //!
    TBranch        *b_lep4CorrPtvarcone20;   //!
    TBranch        *b_lep4CorrPtvarcone30;   //!
    TBranch        *b_lep4PassOR;   //!
    TBranch        *b_lep4Type;   //!
    TBranch        *b_lep4Origin;   //!
    TBranch        *b_lep4EgMotherType;   //!
    TBranch        *b_lep4EgMotherOrigin;   //!
    TBranch        *b_lep4NPix;   //!
    TBranch        *b_lep4PassBL;   //!
    TBranch        *b_lep4VeryLoose;   //!
    TBranch        *b_lep4Loose;   //!
    TBranch        *b_lep4Medium;   //!
    TBranch        *b_lep4Tight;   //!
    TBranch        *b_lep4IsoLoose;   //!
    TBranch        *b_lep4IsoTight;   //!
    TBranch        *b_lep4IsoGradient;   //!
    TBranch        *b_lep4IsoGradientLoose;   //!
    TBranch        *b_lep4IsoLooseTrackOnly;   //!
    TBranch        *b_lep4IsoFixedCutLoose;   //!
    TBranch        *b_lep4IsoFixedCutTight;   //!
    TBranch        *b_lep4IsoFixedCutTightTrackOnly;   //!
    TBranch        *b_lep4IsoCorrLoose;   //!
    TBranch        *b_lep4IsoCorrTight;   //!
    TBranch        *b_lep4IsoCorrGradient;   //!
    TBranch        *b_lep4IsoCorrGradientLoose;   //!
    TBranch        *b_lep4IsoCorrLooseTrackOnly;   //!
    TBranch        *b_lep4IsoCorrFixedCutLoose;   //!
    TBranch        *b_lep4IsoCorrFixedCutTight;   //!
    TBranch        *b_lep4IsoCorrFixedCutTightTrackOnly;   //!
    TBranch        *b_lep4Signal;   //!
    TBranch        *b_lep4TruthMatched;   //!
    TBranch        *b_lep4TruthCharge;   //!
    TBranch        *b_lep4TruthPt;   //!
    TBranch        *b_lep4TruthEta;   //!
    TBranch        *b_lep4TruthPhi;   //!
    TBranch        *b_lep4TruthM;   //!
    TBranch        *b_nJet30;   //!
    TBranch        *b_nJet25;   //!
    TBranch        *b_nJet20;   //!
    TBranch        *b_nTotalJet;   //!
    TBranch        *b_nTotalJet20;   //!
    TBranch        *b_nBJet30_MV2c10;   //!
    TBranch        *b_nBJet20_MV2c10;   //!
    TBranch        *b_nBJet30_MV2c10_FixedCutBEff_60;   //!
    TBranch        *b_nBJet30_MV2c10_FixedCutBEff_70;   //!
    TBranch        *b_nBJet30_MV2c10_FixedCutBEff_77;   //!
    TBranch        *b_nBJet30_MV2c10_FixedCutBEff_85;   //!
    TBranch        *b_nBJet20_MV2c10_FixedCutBEff_60;   //!
    TBranch        *b_nBJet20_MV2c10_FixedCutBEff_70;   //!
    TBranch        *b_nBJet20_MV2c10_FixedCutBEff_77;   //!
    TBranch        *b_nBJet20_MV2c10_FixedCutBEff_85;   //!
    TBranch        *b_DecayModeTTbar;   //!
    TBranch        *b_jetPt;   //!
    TBranch        *b_jetEta;   //!
    TBranch        *b_jetPhi;   //!
    TBranch        *b_jetM;   //!
    TBranch        *b_jetTileEnergy;   //!
    TBranch        *b_vectorSumJetsPt;   //!
    TBranch        *b_vectorSumJetsEta;   //!
    TBranch        *b_vectorSumJetsPhi;   //!
    TBranch        *b_vectorSumJetsM;   //!
    TBranch        *b_dPhiVectorSumJetsMET;   //!
    TBranch        *b_met_Et;   //!
    TBranch        *b_met_Phi;   //!
    TBranch        *b_TST_Et;   //!
    TBranch        *b_TST_Phi;   //!
    TBranch        *b_met_track_Et;   //!
    TBranch        *b_met_track_Phi;   //!
    TBranch        *b_deltaPhi_MET_TST_Phi;   //!
    TBranch        *b_mt;   //!
    TBranch        *b_meffInc30;   //!
    TBranch        *b_Ht30;   //!
    TBranch        *b_hadronicWMass;   //!
    TBranch        *b_hadronicWPt;   //!
    TBranch        *b_LepAplanarity;   //!
    TBranch        *b_JetAplanarity;   //!
    TBranch        *b_amt2;   //!
    TBranch        *b_amt2b;   //!
    TBranch        *b_amt2bWeight;   //!
    TBranch        *b_mt2tau;   //!
    TBranch        *b_mt2lj;   //!
    TBranch        *b_mbb;   //!
    TBranch        *b_mt_lep1;   //!
    TBranch        *b_mt_lep2;   //!
    TBranch        *b_mt_lep3;   //!
    TBranch        *b_mt_lep4;   //!
    TBranch        *b_mt_lep1_metTrack;   //!
    TBranch        *b_mt_lep2_metTrack;   //!
    TBranch        *b_mt_lep3_metTrack;   //!
    TBranch        *b_mt_lep4_metTrack;   //!
    TBranch        *b_METOverHT;   //!
    TBranch        *b_METOverJ1pT;   //!
    TBranch        *b_METTrackOverHT;   //!
    TBranch        *b_METTrackOverJ1pT;   //!
    TBranch        *b_DPhiJ1Met;   //!
    TBranch        *b_DPhiJ2Met;   //!
    TBranch        *b_DPhiJ3Met;   //!
    TBranch        *b_DPhiJ4Met;   //!
    TBranch        *b_minDPhi4JetsMet;   //!
    TBranch        *b_minDPhiAllJetsMet;   //!
    TBranch        *b_DPhiJ1MetTrack;   //!
    TBranch        *b_DPhiJ2MetTrack;   //!
    TBranch        *b_DPhiJ3MetTrack;   //!
    TBranch        *b_DPhiJ4MetTrack;   //!
    TBranch        *b_minDPhi4JetsMetTrack;   //!
    TBranch        *b_minDPhiAllJetsMetTrack;   //!
    TBranch        *b_METOverHTLep;   //!
    TBranch        *b_METTrackOverHTLep;   //!
    TBranch        *b_mll;   //!
    TBranch        *b_Rll;   //!
    TBranch        *b_Ptll;   //!
    TBranch        *b_dPhiPllMet;   //!
    TBranch        *b_dPhiPllMetTrack;   //!
    TBranch        *b_METRel;   //!
    TBranch        *b_METTrackRel;   //!
    TBranch        *b_dPhiNearMet;   //!
    TBranch        *b_dPhiNearMetTrack;   //!
    TBranch        *b_dPhiMetAndMetTrack;   //!
    TBranch        *b_MSqTauTau_1;   //!
    TBranch        *b_MSqTauTau_2;   //!
    TBranch        *b_MTauTau;   //!
    TBranch        *b_MSqTauTau_1_metTrack;   //!
    TBranch        *b_MSqTauTau_2_metTrack;   //!
    TBranch        *b_MTauTau_metTrack;   //!
    TBranch        *b_RjlOverEl;   //!
    TBranch        *b_LepCosThetaLab;   //!
    TBranch        *b_LepCosThetaCoM;   //!
    TBranch        *b_mt2leplsp_0;   //!
    TBranch        *b_mt2leplsp_25;   //!
    TBranch        *b_mt2leplsp_50;   //!
    TBranch        *b_mt2leplsp_75;   //!
    TBranch        *b_mt2leplsp_90;   //!
    TBranch        *b_mt2leplsp_95;   //!
    TBranch        *b_mt2leplsp_100;   //!
    TBranch        *b_mt2leplsp_105;   //!
    TBranch        *b_mt2leplsp_110;   //!
    TBranch        *b_mt2leplsp_115;   //!
    TBranch        *b_mt2leplsp_120;   //!
    TBranch        *b_mt2leplsp_150;   //!
    TBranch        *b_mt2leplsp_175;   //!
    TBranch        *b_mt2leplsp_200;   //!
    TBranch        *b_mt2leplsp_250;   //!
    TBranch        *b_mt2leplsp_300;   //!
    TBranch        *b_mt2leplsp_0_metTrack;   //!
    TBranch        *b_mt2leplsp_25_metTrack;   //!
    TBranch        *b_mt2leplsp_50_metTrack;   //!
    TBranch        *b_mt2leplsp_75_metTrack;   //!
    TBranch        *b_mt2leplsp_90_metTrack;   //!
    TBranch        *b_mt2leplsp_95_metTrack;   //!
    TBranch        *b_mt2leplsp_100_metTrack;   //!
    TBranch        *b_mt2leplsp_105_metTrack;   //!
    TBranch        *b_mt2leplsp_110_metTrack;   //!
    TBranch        *b_mt2leplsp_115_metTrack;   //!
    TBranch        *b_mt2leplsp_120_metTrack;   //!
    TBranch        *b_mt2leplsp_150_metTrack;   //!
    TBranch        *b_mt2leplsp_175_metTrack;   //!
    TBranch        *b_mt2leplsp_200_metTrack;   //!
    TBranch        *b_mt2leplsp_250_metTrack;   //!
    TBranch        *b_mt2leplsp_300_metTrack;   //!
    TBranch        *b_pileupWeight;   //!
    TBranch        *b_leptonWeight;   //!
    TBranch        *b_eventWeight;   //!
    TBranch        *b_genWeight;   //!
    TBranch        *b_bTagWeight;   //!
    TBranch        *b_jvtWeight;   //!
    TBranch        *b_genWeightUp;   //!
    TBranch        *b_genWeightDown;   //!
    TBranch        *b_LHE3Weights;   //!
    TBranch        *b_FFWeight;   //!
    TBranch        *b_nLep_antiID;   //!
    TBranch        *b_lep1AntiID;   //!
    TBranch        *b_lep2AntiID;   //!
    TBranch        *b_lep3AntiID;   //!
    TBranch        *b_lep4AntiID;   //!
    TBranch        *b_nLep_signalActual;   //!
    TBranch        *b_lep1SignalActual;   //!
    TBranch        *b_lep2SignalActual;   //!
    TBranch        *b_lep3SignalActual;   //!
    TBranch        *b_lep4SignalActual;   //!
    TBranch        *b_HLT_mu4;   //!
    TBranch        *b_HLT_2mu4;   //!
    TBranch        *b_HLT_2mu10;   //!
    TBranch        *b_HLT_2mu4_j85_xe50_mht;   //!
    TBranch        *b_HLT_mu4_j125_xe90_mht;   //!
    TBranch        *b_HLT_xe70;   //!
    TBranch        *b_HLT_xe70_mht;   //!
    TBranch        *b_HLT_xe70_mht_wEFMu;   //!
    TBranch        *b_HLT_xe70_tc_lcw;   //!
    TBranch        *b_HLT_xe70_tc_lcw_wEFMu;   //!
    TBranch        *b_HLT_xe80_tc_lcw_L1XE50;   //!
    TBranch        *b_HLT_xe90_tc_lcw_L1XE50;   //!
    TBranch        *b_HLT_xe90_mht_L1XE50;   //!
    TBranch        *b_HLT_xe90_tc_lcw_wEFMu_L1XE50;   //!
    TBranch        *b_HLT_xe90_mht_wEFMu_L1XE50;   //!
    TBranch        *b_HLT_xe100_L1XE50;   //!
    TBranch        *b_HLT_xe100_wEFMu_L1XE50;   //!
    TBranch        *b_HLT_xe100_tc_lcw_L1XE50;   //!
    TBranch        *b_HLT_xe100_mht_L1XE50;   //!
    TBranch        *b_HLT_xe100_tc_lcw_wEFMu_L1XE50;   //!
    TBranch        *b_HLT_xe100_mht_wEFMu_L1XE50;   //!
    TBranch        *b_HLT_xe110_L1XE50;   //!
    TBranch        *b_HLT_xe110_tc_em_L1XE50;   //!
    TBranch        *b_HLT_xe110_wEFMu_L1XE50;   //!
    TBranch        *b_HLT_xe110_tc_em_wEFMu_L1XE50;   //!
    TBranch        *b_HLT_xe110_mht_L1XE50;   //!
    TBranch        *b_HLT_xe90_mht_L1XE40;   //!
    TBranch        *b_HLT_xe50_mht_L1XE20;   //!
    TBranch        *b_HLT_j85_L1J40;   //!
    TBranch        *b_HLT_j125_L1J50;   //!
    TBranch        *b_HLT_e26_lhtight_nod0_ivarloose;   //!
    TBranch        *b_HLT_e60_lhmedium_nod0;   //!
    TBranch        *b_HLT_e60_medium;   //!
    TBranch        *b_HLT_e140_lhloose_nod0;   //!
    TBranch        *b_HLT_mu26_ivarmedium;   //!
    TBranch        *b_ttbarNNLOWeight;   //!
    TBranch        *b_ttbarNNLOWeightUp;   //!
    TBranch        *b_ttbarNNLOWeightDown;   //!
    TBranch        *b_truthTopPt;   //!
    TBranch        *b_truthAntiTopPt;   //!
    TBranch        *b_truthTtbarPt;   //!
    TBranch        *b_truthTtbarM;   //!
    TBranch        *b_x1;   //!
    TBranch        *b_x2;   //!
    TBranch        *b_pdf1;   //!
    TBranch        *b_pdf2;   //!
    TBranch        *b_scalePDF;   //!
    TBranch        *b_id1;   //!
    TBranch        *b_id2;   //!
    TBranch        *b_PRWHash;   //!
    TBranch        *b_EventNumber;   //!
    TBranch        *b_xsec;   //!
    TBranch        *b_TrueHt;   //!
    TBranch        *b_DatasetNumber;   //!
    TBranch        *b_RunNumber;   //!
    TBranch        *b_RandomRunNumber;   //!
    TBranch        *b_FS;   //!

    // Histograms
    TH1F *h_yields; //!
    TH1F *h_weighted_yields; //!

    TH1F *h_yields_SRee; //!
    TH1F *h_yields_SRmm; //!
    TH1F *h_yields_SRSF; //!

    TH1F *h_weighted_yields_SRee; //!
    TH1F *h_weighted_yields_SRmm; //!
    TH1F *h_weighted_yields_SRSF; //!

    // Distributions
    TH1F *h_NJets; //! includes forward jets
    TH1F *h_NJet30; //! signal jets
    TH1F *h_NJet25; //! signal jets

    TH1F *h_jets_pT; //!
    TH1F *h_jet1_pT; //!
    TH1F *h_jet2_pT; //!
    TH1F *h_jet3_pT; //!
    TH1F *h_jet4_pT; //!

    TH1F *h_Nbjets; //!
    TH1F *h_bJets_pT; //!

    TH1F *h_NLepts_baseline; //!
    TH1F *h_lepts_pT_baseline; //!
    TH1F *h_lept1_pT_baseline; //!
    TH1F *h_lept2_pT_baseline; //!
    TH1F *h_lept3_pT_baseline; //!
    TH1F *h_lept4_pT_baseline; //!

    TH1F *h_NLepts_signal; //!
    TH1F *h_lepts_pT_signal; //!
    TH1F *h_lept1_pT_signal; //!
    TH1F *h_lept2_pT_signal; //!
    TH1F *h_lept3_pT_signal; //!
    TH1F *h_lept4_pT_signal; //!

    TH1F *h_met; //!
    TH1F *h_HT; //!
    TH1F *h_METOverHT; //!
    // TH1F *h_METOverHTLep12; //!
    TH1F *h_mT2; //!
    TH1F *h_mll; //!

    // TH1F *h_METOverHT_no_cut; //!
    // TH1F *h_METOverHT_with_cut; //!
    // TH1F *h_METOverHTLep12_no_cut; //!
    // TH1F *h_METOverHTLep12_with_cut; //!

    // this is a standard constructor
    ytEventSelection ();

    // these are the functions inherited from Algorithm
    virtual EL::StatusCode setupJob (EL::Job& job);
    virtual EL::StatusCode fileExecute ();
    virtual EL::StatusCode histInitialize ();
    virtual EL::StatusCode changeInput (bool firstFile);
    virtual EL::StatusCode initialize ();
    virtual EL::StatusCode execute ();
    virtual EL::StatusCode postExecute ();
    virtual EL::StatusCode finalize ();
    virtual EL::StatusCode histFinalize ();

    void set_isMC(bool b) { isMC = b; }
    void set_isCutflow(bool b) { isCutflow = b; }
    void set_isOptimization(bool b) { isOptimization = b; }
    void set_analysis_type(string s) { analysis_type = s; }
    void set_sample_type(string s) { sample_type = s; }
    void set_sample(string s) { sample = s; }
    void set_luminosity(float f) { luminosity = f; }

    void debug_print(bool cut_MET, bool cut_NJets, bool cut_leading_jet_pT, bool cut_NBjets, bool cut_dPhiMETJ1, bool cut_MTauTau, bool cut_METOverHT);

    // this is needed to distribute the algorithm to the workers
    ClassDef(ytEventSelection, 1);
};

#endif
