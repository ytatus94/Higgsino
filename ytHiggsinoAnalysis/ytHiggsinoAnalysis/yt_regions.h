#ifndef YT_REGIONS_H
#define YT_REGIONS_H

#include <TROOT.h>

#include <iostream>
#include <algorithm>
using namespace std;

// Global constant
const float GeV = 1000.;

class yt_regions
{
public:
    yt_regions();
    virtual ~yt_regions();

    // user defined methods
    // Define different regions to select events

    bool pass_MET(float MET);
    bool pass_NJets(int NJets);
    bool pass_leading_jet_pT(float pT);
    bool pass_NBjets(float NBjets);
    bool pass_deltaPhi_MET_leading_jet(float dPhiJ1MET);
    bool pass_Mtautau(float MTauTau);
    bool pass_MET_over_HT(float MET_over_HT, float mll);

/*
    // Used for EWK 2/3L study
    bool pass_baseTwoLepCuts(float lept1Pt, float lept2Pt, bool isEMU, bool isEE, bool isMUMU, float Mll, float lept1q, float lept2q);
    bool pass_sameFlavorLep(bool isEMU, bool isEE, bool isMUMU);
    bool pass_ZVeto(float Mll);
    bool pass_JetVeto(int nCentralBJets20, int nCentralLightJets60);

    // SR definitions for Direct-Slepton
    bool pass_SR2LLoose(float MT2, float Mll);
    bool pass_SR2LTight(float MT2, float Mll);
    // binned SR for Different-Flavour (DF)
    bool pass_SR2LbinA(float MT2, float Mll);
    bool pass_SR2LbinB(float MT2, float Mll);
    bool pass_SR2LbinC(float MT2, float Mll);
    bool pass_SR2LbinD(float MT2, float Mll);
    // binned SR for Same-Flavour (SF)
    bool pass_SR2Lbin1(float MT2, float Mll);
    bool pass_SR2Lbin2(float MT2, float Mll);
    bool pass_SR2Lbin3(float MT2, float Mll);
    bool pass_SR2Lbin4(float MT2, float Mll);
    bool pass_SR2Lbin5(float MT2, float Mll);
    bool pass_SR2Lbin6(float MT2, float Mll);
    bool pass_SR2Lbin7(float MT2, float Mll);
    bool pass_SR2Lbin8(float MT2, float Mll);
    bool pass_SR2Lbin9(float MT2, float Mll);
    bool pass_SR2Lbin10(float MT2, float Mll);
    bool pass_SR2Lbin11(float MT2, float Mll);
    bool pass_SR2Lbin12(float MT2, float Mll);
    bool pass_SR2Lbin13(float MT2, float Mll);

    // 2L2J
    bool pass_bjet_veto(int nCentralBJets);
    bool pass_at_least_two_jets30(int nCentralLightJets30);
    bool pass_thrid_jet_pT(float pT);
    bool pass_mll(string s, float Mll);
    bool pass_Z_pT(string s, float Z_pT);
    bool pass_W_pT(float W_pT);
    bool pass_Z_eta(float Z_eta);
    bool pass_MET(string s, float MET);
    bool pass_MT2(float MT2);
    bool pass_deltaR_jj(string s, float dR_JJ);
    bool pass_deltaR_ll(float dR_LL);
    bool pass_deltaPhi_MET_Z(float dPhi_MET_Z);
    bool pass_deltaPhi_MET_W(string s, float dPhi_MET_W);
    bool pass_deltaPhi_MET_ISR(float dPhi_MET_ISR);
    bool pass_deltaPhi_MET_J0(float dPhi_MET_J0);
    bool pass_mjj(string s, float MJJ);
    bool pass_MET_over_Z_pT(float MET_over_Z_pT);
    bool pass_MET_over_W_pT(float MET_over_W_pT);
    bool pass_MET_over_ISR(float MET_over_ISR);
*/

    ClassDef(yt_regions, 0); //Set ClassVersionID=0 in case you don't need object I/O.
};

#endif // #define YT_REGIONS_H