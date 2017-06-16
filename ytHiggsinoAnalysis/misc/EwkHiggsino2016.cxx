#include "SimpleAnalysis/AnalysisClass.h"
#include <algorithm>

DefineAnalysis(EwkHiggsino2016)

void EwkHiggsino2016::Init()
{
    addRegions({"SR"});
    addRegions({"CR_top", "CR_tau", "CR_VV"});
    addRegions({"VR_SS", "VR_dPhi", "VR_DF_MLL", "VR_DR_MT2"});

    // Book 1/2D histograms
    addHistogram("met_Et", 100, 0, 1000);
    addHistogram("MTauTau", 24, -600, 600);
    addHistogram("mll", 25, 0, 100);
    addHistogram("mT2", 20, 90, 190);
    addHistogram("METOverHTLep12", 40, 0, 40);

}

// // The MT2 variable generalised so the hypothesis invisible mass mn can be non-zero
// // This is copied form Jesse's simple analysis.
// static float calc_massive_MT2(const AnalysisObject &o1, const AnalysisObject &o2, const AnalysisObject &met, float mn) {
//     double patr[3] = {o1.M(),o1.Px(),o1.Py()};
//     double pbtr[3] = {o2.M(),o2.Px(),o2.Py()};
//     double pmisstr[3] = { 0, met.Px(), met.Py()};

//     mt2_bisect::mt2 mt2calculator;
//     mt2calculator.set_momenta(patr, pbtr, pmisstr);
//     mt2calculator.set_mn(mn);
//     return mt2calculator.get_mt2();
// }

// The MTauTau variable
// This is copied from Jesse's simple analysis but it is the same as what I did.
static float calc_MTauTau(const AnalysisObject &o1, const AnalysisObject &o2, const AnalysisObject &met) {
    float determinant = o1.Px() * o2.Py() - o1.Py() * o2.Px();
    float xi_1 = (met.Px() * o2.Py() - o2.Px() * met.Py())/determinant;
    float xi_2 = (met.Py() * o1.Px() - o1.Px() * met.Px())/determinant;

    float MSqTauTau = (1. + xi_1) * (1. + xi_2) * 2 * o1.Dot(o2);

    float MTauTau = 0.;
    if (MSqTauTau >= 0) MTauTau =   sqrt( MSqTauTau );
    if (MSqTauTau < 0)  MTauTau = - sqrt( fabs( MSqTauTau ) );

    return MTauTau;
}

void EwkHiggsino2016::ProcessEvent(AnalysisEvent *event)
{
    float gen_met   = event->getGenMET();
    float gen_ht    = event->getGenHT();

    auto baselineElectrons  = event->getElectrons(4.5, 2.47, EVeryLooseLH|EZ05mm);
    auto baselineMuons      = event->getMuons(4.0, 2.5, MuMedium|MuZ05mm);
    auto baselineJets       = event->getJets(20., 2.8);

    auto   metVec           = event->getMET();
    double met              = metVec.Et();
    int    channel_number   = event->getMCNumber();
    float  mc_weight        = event->getMCWeights()[0];

    // Higgsino samples has MET filter.
    // if (met < 50) return;

    // Loose bad jet veto for central jets -- this is truth, so we don't really need this...
    if (countObjects(baselineJets, 20, 2.8, NOT(LooseBadJet))!=0) return;
    // No bad muon veto implemented
    // No cosmic muon veto implemented

    // Overlap removal
    // auto radiusCalcJet  = [] (const AnalysisObject& , const AnalysisObject& muon) { return std::min(0.4, 0.04 + 10/muon.Pt()); };
    // auto radiusCalcMuon = [] (const AnalysisObject& muon, const AnalysisObject& ) { return std::min(0.4, 0.04 + 10/muon.Pt()); };
    // auto radiusCalcElec = [] (const AnalysisObject& elec, const AnalysisObject& ) { return std::min(0.4, 0.04 + 10/elec.Pt()); };
  
    baselineJets        = overlapRemoval(baselineJets, baselineElectrons, 0.2, NOT(BTag85MV2c20));
    // baselineJets        = overlapRemoval(baselineJets, baselineMuons, 0.4, LessThan3Tracks);
    baselineElectrons   = overlapRemoval(baselineElectrons, baselineJets, 0.4);
    baselineMuons       = overlapRemoval(baselineMuons, baselineJets, 0.4);
    // baseElectrons       = overlapRemoval(baselineElectrons, baselineMuons, 0.01);

    auto signalElectrons = filterObjects(baselineElectrons, 4.5, 2.47, ETightLH|ED0Sigma5|EZ05mm|EIsoGradientLoose);
    auto signalMuons     = filterObjects(baselineMuons, 4, 2.5, MuD0Sigma3|MuZ05mm|MuIsoFixedCutTightTrackOnly|MuNotCosmic);
    auto signalJets      = filterObjects(baselineJets, 20, 2.8);
    auto signalBjets     = filterObjects(signalJets, 20, 2.8, BTag85MV2c20);

    // Lists of objects can be merged by simple addition
    auto baselineLeptons    = baselineElectrons + baselineMuons;
    auto signalLeptons      = signalElectrons + signalMuons;

    sortObjectsByPt( signalElectrons );
    sortObjectsByPt( signalMuons );
    sortObjectsByPt( signalJets );
    sortObjectsByPt( signalBjets );

    sortObjectsByPt( baselineLeptons );
    sortObjectsByPt( signalLeptons );

    // Object counting
    int nBaselineLeptons    = baselineLeptons.size(); // Object lists are essentially std::vectors so .size() works
    int nSignalLeptons      = signalLeptons.size();
    int nElectrons          = signalElectrons.size();
    int nMuons              = signalMuons.size();
    int nJets               = signalJets.size();
    int nJet30              = countObjects(signalJets, 30, 2.8);
    int nJet25              = countObjects(signalJets, 30, 2.8);
    int nBjets              = signalBjets.size();

    // require exactly 2 baseline and 2 signal leptons for the 2L channel.
    // if (nBaselineLeptons != 2) return;
    // if (nSignalLeptons != 2) return;
    bool is2LChannel = false;
    if (nBaselineLeptons == 2 && nSignalLeptons == 2)
        is2LChannel = true;

    bool isSameSign = false;
    if (nSignalLeptons >=2) {
        isSameSign = signalLeptons[0].charge() * signalLeptons[1].charge() == 1 ? true : false;
    }

    // mm is channel 0; ee is channel 1; em is channel 2; me is channel 3
    int channel = -1;
    if (nSignalLeptons == 2 && signalElectrons.size() == 0)
        channel = 0;
    else if (nSignalLeptons == 2 && signalMuons.size() == 0)
        channel = 1;
    else if (nSignalLeptons == 2)
        channel = signalElectrons[0].Pt() > signalMuons[0].Pt() ? 2 : 3;
    else if (nSignalLeptons >= 3) {
        // 3 or more leptons, need to check momenta
        // mmm, mme: 0, eee, eem: 1, eme emm: 2 mee, mem: 3
        if (nElectrons == 0)
            channel = 0;
        else if (nMuons == 0)
            channel = 1;
        else if (nElectrons == 1)
            channel = signalElectrons[0].Pt() > signalMuons[0].Pt() ? 2 : 3;
        else if (nMuons == 1)
            channel = signalMuons[0].Pt() > signalElectrons[0].Pt() ? 3 : 2;
        else if (nElectrons > 1)
            channel = signalElectrons[1].Pt() > signalMuons[0].Pt() ? 1 : 2;
        else if (nMuons > 1)
            channel = signalMuons[1].Pt() > signalElectrons[0].Pt() ? 0 : 3; 
    }

    // Calculate a few kinematic variables - add your favorites to AnalysisClass.cxx
    float dphiMin1          = minDphi(metVec, signalJets, 1); // Smallest Delta Phi between the 1st leading jet and MET
    float mT                = 0;
    float mT2               = 0;
    float meffIncl          = met + sumObjectsPt(signalJets) + sumObjectsPt(signalLeptons); // Meff from MET, jets and leptons
    float HTIncl            = sumObjectsPt(signalJets);
    float HT30              = sumObjectsPt(signalJets, 999, 30);
    float HTLep12           = 0; // sumObjectsPt(baselineLeptons, 2); // up to 2 leptons
    float METOverHT         = met / HT30;
    float METOverHTLep12    = 0; // met / HTLep12;
    float mll               = 0;
    float pTll              = 0;
    float Rll               = -99999;
    // float MTauTau           = -99999;
    float MTauTau           = calc_MTauTau(baselineLeptons[0], baselineLeptons[1], metVec);

    if (nSignalLeptons > 0)
        mT = calcMT(signalLeptons[0], metVec); // MT from leading lepton
    if (nSignalLeptons >= 2) {
        // Leading two leptons
        mT2  = calcMT2(signalLeptons[0],signalLeptons[1],metVec);
    }

    if (nBaselineLeptons >= 2) {
        TLorentzVector dilepton(baselineLeptons[0].Px() + baselineLeptons[1].Px(),
                                baselineLeptons[0].Py() + baselineLeptons[1].Py(),
                                baselineLeptons[0].Pz() + baselineLeptons[1].Pz(),
                                baselineLeptons[0].E()  + baselineLeptons[1].E());
        mll  = dilepton.M();
        pTll = dilepton.Pt();
        Rll = baselineLeptons[0].DeltaR(baselineLeptons[1]);
        HTLep12 = baselineLeptons[0].Pt() + baselineLeptons[1].Pt();
        METOverHTLep12 = met / HTLep12;
    }

    // // Calculate MTauTau
    // // Copy version 2 from https://gitlab.cern.ch/SusySkimAna/SusySkimMaker/blob/master/Root/Observables.cxx#L1326
    // float MSqTauTau = -99999.;
    // if (nBaselineLeptons >= 2) {
    //     // ================================================
    //     // get components of transverse momenta
    //     float pmiss_x = metVec.Px();
    //     float pmiss_y = metVec.Py();

    //     float pL1_E   = baselineLeptons[0].E();
    //     float pL1_x   = baselineLeptons[0].Px();
    //     float pL1_y   = baselineLeptons[0].Py();
    //     float pL1_z   = baselineLeptons[0].Pz();

    //     float pL2_E   = baselineLeptons[1].E();
    //     float pL2_x   = baselineLeptons[1].Px();
    //     float pL2_y   = baselineLeptons[1].Py();
    //     float pL2_z   = baselineLeptons[1].Pz();

    //     // calculate the xi (scale factor of tau daughter neutrinos to observed lepton pT)
    //     // we solved this simultaneous equation by hand here (matrix inversion)
    //     float determinant = pL1_x * pL2_y - pL1_y * pL2_x;
    //     float xi_1 = (pmiss_x * pL2_y - pL2_x * pmiss_y)/determinant;
    //     float xi_2 = (pmiss_y * pL1_x - pL1_y * pmiss_x)/determinant;

    //     // else if ( version == 2 ) {
    //       // xi remains unrestricted for energy and momentum like parts
    //       // TLorentzVector* sigLep2 = dynamic_cast<TLorentzVector*>( baselineLeptons.at(1) );
    //       MSqTauTau = (1. + xi_1) * (1. + xi_2) * 2 * baselineLeptons[0].Dot( baselineLeptons.at(1) );
    //     // }
    // }

    // if (MSqTauTau >= 0) MTauTau = sqrt( MSqTauTau );
    // if (MSqTauTau < 0) MTauTau = -1 * sqrt( fabs(MSqTauTau) );

    // Signal region
    if (met > 200 &&
        nJet30 > 0 && nJet30 < 5 &&
        signalJets[0].Pt() > 100 &&
        // signalJets[1].Pt() > 30 && signalJets[2].Pt() > 30 && signalJets[3].Pt() > 30 && // list on the int note but not on the slide?
        dphiMin1 > 2. &&
        nBjets == 0 &&
        is2LChannel &&
        (channel == 0 || channel == 1) && (!isSameSign) &&
        // signalElectrons[0].Pt() > 5 && signalElectrons[0].Pt() > 4.5 && // list on the int note but not on the slide?
        // signalMuons[0].Pt() > 5 && signalMuons[0].Pt() > 4 && // list on the int note but not on the slide?
        (MTauTau < 0 || MTauTau > 160) &&
        METOverHTLep12 > 5)
        accept("SR");
    // Top CR: SR, except > 0 b-tags
    if (met > 200 &&
        nJet30 > 0 && nJet30 < 5 &&
        signalJets[0].Pt() > 100 &&
        dphiMin1 > 2. &&
        nBjets > 0 && nBjets < 3 &&
        is2LChannel &&
        (channel == 0 || channel == 1 || channel == 2 || channel == 3) && (!isSameSign) &&
        (MTauTau < 0 || MTauTau > 160) &&
        METOverHTLep12 > 5)
        accept("CR_top");
    // Z -> tau tau: SR, except 60 < MTauTau < 120, also require 4 < METOverHTLep12 < 8 (to reduce signal contamination)
    if (met > 200 &&
        nJet30 > 0 && nJet30 < 5 &&
        signalJets[0].Pt() > 100 &&
        dphiMin1 > 2. &&
        nBjets == 0 &&
        is2LChannel &&
        (channel == 0 || channel == 1 || channel == 2 || channel == 3) && (!isSameSign) &&
        (MTauTau > 60 && MTauTau < 120) &&
        METOverHTLep12 > 4 && METOverHTLep12 < 8)
        accept("CR_tau");
    // Diboson CR: SR, except METOverHTLep12 < 5, also require mll < 60 (to avoid on-shell Z)
    if (met > 200 &&
        nJet30 > 0 && nJet30 < 5 &&
        signalJets[0].Pt() > 100 &&
        dphiMin1 > 2. &&
        nBjets == 0 &&
        is2LChannel &&
        (channel == 0 || channel == 1 || channel == 2 || channel == 3) && (!isSameSign) &&
        (MTauTau < 0 || MTauTau > 160) &&
        METOverHTLep12 < 5)
        accept("CR_VV");
    // Fakes VR: SR, except same-sign leptons
    if (met > 200 &&
        nJet30 > 0 && nJet30 < 5 &&
        signalJets[0].Pt() > 100 &&
        dphiMin1 > 2. &&
        nBjets == 0 &&
        is2LChannel &&
        (channel == 0 || channel == 1) && isSameSign &&
        (MTauTau < 0 || MTauTau > 160) &&
        METOverHTLep12 > 5)
        accept("VR_SS");
    // General VR: SR, except different-flavor leptons
    if (met > 200 &&
        nJet30 > 0 && nJet30 < 5 &&
        signalJets[0].Pt() > 100 &&
        dphiMin1 < 2. &&
        nBjets == 0 &&
        is2LChannel &&
        (channel == 0 || channel == 1) && (!isSameSign) &&
        (MTauTau < 0 || MTauTau > 160) &&
        METOverHTLep12 > 5)
        accept("VR_dPhi");
    if (met > 200 &&
        nJet30 > 0 && nJet30 < 5 &&
        signalJets[0].Pt() > 100 &&
        dphiMin1 > 2. &&
        nBjets == 0 &&
        is2LChannel &&
        (channel == 0 || channel == 1) && (!isSameSign) &&
        (MTauTau < 0 || MTauTau > 160) &&
        METOverHTLep12 > std::max(5., 15.-2.*mll) &&
        Rll < 2)
        accept("VR_DF_MLL");
    if (met > 200 &&
        nJet30 > 0 && nJet30 < 5 &&
        signalJets[0].Pt() > 100 &&
        dphiMin1 > 2. &&
        nBjets == 0 &&
        is2LChannel &&
        (channel == 0 || channel == 1) && (!isSameSign) &&
        (MTauTau < 0 || MTauTau > 160) &&
        METOverHTLep12 > std::max(5., 15.-2.*(mT2-100.)) )
        accept("VR_DF_MLL");

    // Dump ntuples
    ntupVar("gen_met", gen_met);
    ntupVar("gen_ht", gen_ht);
    ntupVar("baselineElectrons", baselineElectrons);
    ntupVar("baselineMuons", baselineMuons);
    ntupVar("baselineJets", baselineJets);
    ntupVar("met", met);
    ntupVar("channel_number", channel_number);
    ntupVar("mc_weight", mc_weight);
    ntupVar("signalElectrons", signalElectrons);
    ntupVar("signalMuons", signalMuons);
    ntupVar("signalJets", signalJets);
    ntupVar("signalBjets", signalBjets);
    ntupVar("baselineLeptons", baselineLeptons);
    ntupVar("signalLeptons", signalLeptons);
    ntupVar("nBaselineLeptons", nBaselineLeptons);
    ntupVar("nSignalLeptons", nSignalLeptons);
    ntupVar("nElectrons", nElectrons);
    ntupVar("nMuons", nMuons);
    ntupVar("nJets", nJets);
    ntupVar("nJet30", nJet30);
    ntupVar("nJet25", nJet25);
    ntupVar("nBjets", nBjets);
    ntupVar("is2LChannel", is2LChannel);
    ntupVar("isSameSign", isSameSign);
    ntupVar("channel", channel);
    ntupVar("dphiMin1", dphiMin1);
    ntupVar("mT", mT);
    ntupVar("mT2", mT2);
    ntupVar("meffIncl", meffIncl);
    ntupVar("HTIncl", HTIncl);
    ntupVar("HT30", HT30);
    ntupVar("HTLep12", HTLep12);
    ntupVar("METOverHT", METOverHT);
    ntupVar("METOverHTLep12", METOverHTLep12);
    ntupVar("mll", mll);
    ntupVar("pTll", pTll);
    ntupVar("Rll", Rll);
    ntupVar("MTauTau", MTauTau);

    return;
}