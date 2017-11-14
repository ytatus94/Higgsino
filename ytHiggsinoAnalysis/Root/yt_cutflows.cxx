#define YT_CUTFLOWS_CXX
#include "ytHiggsinoAnalysis/yt_cutflows.h"

ClassImp(yt_cutflows)

const char* cut_name[] = {
    // Non-sequential
    "Cut: All events", // 0
    "Cut: Event cleaning", // 1
    "Cut: GRL", // 2
    "Cut: Global Flags", // 3
    "Cut: Primary vertex", // 4
    "Cut: Bad muon", // 5
    "Cut: Bad jet", // 6
    // Non-sequential
    "Cut: >= 1 baseline electron", // 7
    "Cut: >= 1 signal electron", // 8
    "Cut: >= 1 baseline muon", // 9
    "Cut: >= 1 signal muon", // 10
    "Cut: >= 2 baseline electron", // 11
    "Cut: >= 2 signal electron", // 12
    "Cut: >= 2 baseline muon", // 13
    "Cut: >= 2 signal muon", // 14
    "Cut: >= 2 baseline leptons", // 15
    "Cut: >= 2 signal leptons", // 16
    "Cut: exactly 3 baseline electrons", // 17
    "Cut: exactly 3 signal electrons", // 18
    "Cut: exactly 3 baseline muons", // 19
    "Cut: exactly 3 signal muons", // 20
    "Cut: exactly 3 baseline leptons", // 21
    "Cut: exactly 3 signal leptons", // 22
    "Cut: >= 1 baseline jet", // 23
    "Cut: >= 1 signal jet", // 24
    "Cut: zero b-jet", // 25
    "Cut: pass mu4_j125_xe90_mht", // 26
    "Cut: pass 2mu4_j85_xe50_mht", // 27
    "Cut: pass met110_mht", // 28
    "Cut: Ncuts (dummy)", // 29
    // Sequential
    // "Cut 1: >= 2 baseline leptons", // 30
    // "Cut 2: >= 2 signal leptons", // 31
    // "Cut 3: SFOS", // 32
    // "Cut 4: leading lepton pT < 50 GeV", // 33
    // "Cut 5: >= 1 signal jet", // 34
    // "Cut 6: leading jet pT > 150 GeV", // 35
    // "Cut 7: b-jet veto", // 36
    // "Cut 8: MET > 150 GeV", // 37
    // "Cut 9: Dphi(jet, MET) > 2.5", // 38
    // "Cut 10: mll < 50 GeV", // 39
    // "Cut 11: Rll < 1.5", // 40
    // "Cut 12: mtt < 0", // 41
    // "Cut: seq_Ncuts (dummy)" // 42
    // Cutflow table
    "Cut 1:  met trigger, met > 150 GeV, N(baseline lepton) >=2", // 30
    "Cut 2:  Stau veto", // 31
    "Cut 3:  N(baseline lepton) == 2", // 32
    "Cut 4:  N(signal lepton) == 2", // 33
    "Cut 5:  Same flavor", // 34
    "Cut 6:  Opposite charge", // 35
    "Cut 7:  Lepton truth matching", // 36
    "Cut 8:  Lepton author 16 veto", // 37
    "Cut 9:  met > 200 GeV", // 38
    "Cut 10: B-jet veto", // 39
    "Cut 11: pT(j1) > 100 GeV", // 40
    "Cut 12: Dphi(j1, met) > 2.0", // 41
    "Cut 13: min[Dphi(jet, met)] > 0.4", // 42
    "Cut 14: veto mtautau [0, 160]", // 43
    "Cut 15: pT(lep1) > 5 GeV", // 44
    "Cut 16: mll > 1 GeV", // 45
    "Cut 17: veto 3 < mll < 3.2", // 46
    "Cut 18: mll < 60 GeV", // 47
    "Cut 19: dRll > 0.05", // 48
    "Cut 20: METOverHTLep > max(5, 15-2*mll)", // 49
    "Cut 21: dRll < 2.0", // 50
    "Cut 22: mT(lep1) < 70 GeV", // 51
    "Cut: seq_Ncuts (dummy)" // 52
};

yt_cutflows::yt_cutflows()
{
    // events_pass_cutflows = vector<double>(seq_Ncuts, 0); // initialize Ncuts elements to zero.
    // weighted_events_pass_cutflows = vector<double>(seq_Ncuts, 0); // initialize Ncuts elements to zero.
    events_pass_cutflows = vector<double>(table_Ncuts, 0); // initialize Ncuts elements to zero.
    weighted_events_pass_cutflows = vector<double>(table_Ncuts, 0); // initialize Ncuts elements to zero.
}

yt_cutflows::~yt_cutflows()
{

}

void yt_cutflows::update(int cut, bool passed, float weight)
{
    if (passed) {
        events_pass_cutflows[cut] += 1;
        weighted_events_pass_cutflows[cut] += weight;
    }
}

void yt_cutflows::print()
{
    cout << "********** Cutflow **********" << endl;
    // for (int cuts = 0; cuts < seq_Ncuts; cuts++) {
    for (int cuts = 0; cuts < table_Ncuts; cuts++) {
        cout << setw(40) << left << cut_name[cuts] << " = "
             << setw(10) << events_pass_cutflows[cuts] << " / "
             << setw(10) << weighted_events_pass_cutflows[cuts] << "(weighted)" << endl;
    }
    cout << "******************************" << endl;
}

// user defined cutflow methods
// event cleaning (sequential)
bool yt_cutflows::pass_all_events()
{
    return true;
}

bool yt_cutflows::pass_event_cleaning() // sequential
{
    return true;
}

bool yt_cutflows::pass_GRL()
{
    return true;
}

bool yt_cutflows::pass_global_flags() // LAr/Tile/SCT errors and core flags
{
    return true;
}

bool yt_cutflows::pass_primary_vertex()
{
    return true;
}

bool yt_cutflows::pass_bad_muon()
{
    return true;
}

bool yt_cutflows::pass_bad_jet()
{
    return true;
}

// Non-sequential (after cleaning)
// Electrons
bool yt_cutflows::pass_at_least_one_baseline_electron(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 1) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 1 ? true : false;
}

bool yt_cutflows::pass_at_least_one_signal_electron(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 1) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 1 ? true : false;
}

bool yt_cutflows::pass_at_least_two_baseline_electrons(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 2) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 2 ? true : false;
}

bool yt_cutflows::pass_at_least_two_signal_electrons(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 2) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 2 ? true : false;
}

bool yt_cutflows::pass_exactly_three_baseline_electrons(int Nlept)
{
    // bool pass = false;
    // if (Nlept == 3) {
    //     pass = true;
    // }
    // return pass;
    return Nlept == 3 ? true : false;
}

bool yt_cutflows::pass_exactly_three_signal_electrons(int Nlept)
{
    // bool pass = false;
    // if (Nlept == 3) {
    //     pass = true;
    // }
    // return pass;
    return Nlept == 3 ? true : false;
}

// Muons
bool yt_cutflows::pass_at_least_one_baseline_muon(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 1) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 1 ? true : false;
}

bool yt_cutflows::pass_at_least_one_signal_muon(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 1) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 1 ? true : false;
}

bool yt_cutflows::pass_at_least_two_baseline_muons(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 2) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 2 ? true : false;
}

bool yt_cutflows::pass_at_least_two_signal_muons(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 2) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 2 ? true : false;
}

bool yt_cutflows::pass_exactly_three_baseline_muons(int Nlept)
{
    // bool pass = false;
    // if (Nlept == 3) {
    //     pass = true;
    // }
    // return pass;
    return Nlept == 3 ? true : false;
}

bool yt_cutflows::pass_exactly_three_signal_muons(int Nlept)
{
    // bool pass = false;
    // if (Nlept == 3) {
    //     pass = true;
    // }
    // return pass;
    return Nlept == 3 ? true : false;
}

// Leptons
bool yt_cutflows::pass_at_least_two_baseline_leptons(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 2) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 2 ? true : false;
}

bool yt_cutflows::pass_at_least_two_signal_leptons(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 2) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 2 ? true : false;
}

bool yt_cutflows::pass_exactly_three_baseline_leptons(int Nlept)
{
    // bool pass = false;
    // if (Nlept == 3) {
    //     pass = true;
    // }
    // return pass;
    return Nlept == 3 ? true : false;
}

bool yt_cutflows::pass_exactly_three_signal_leptons(int Nlept)
{
    // bool pass = false;
    // if (Nlept == 3) {
    //     pass = true;
    // }
    // return pass;
    return Nlept == 3 ? true : false;
}

// Jets
bool yt_cutflows::pass_at_least_one_baseline_jet(int Njet)
{
    // bool pass = false;
    // if (Njet >= 1) {
    //     pass = true;
    // }
    // return pass;
    return Njet >= 1 ? true : false;
}

bool yt_cutflows::pass_at_least_one_signal_jet(int Njet)
{
    // bool pass = false;
    // if (Njet >= 1) {
    //     pass = true;
    // }
    // return pass;
    return Njet >= 1 ? true : false;
}

bool yt_cutflows::pass_zero_bjet(int Njet)
{
    // bool pass = false;
    // if (Njet == 0) {
    //     pass = true;
    // }
    // return pass;
    return Njet == 0 ? true : false;
}

// Triggers
bool yt_cutflows::pass_mu4_j125_xe90_mht(bool HLT)
{
    // bool pass = false;
    // if (HLT) {
    //     pass = true;
    // }
    // return pass;
    return HLT;
}

bool yt_cutflows::pass_2mu4_j85_xe50_mht(bool HLT)
{
    // bool pass = false;
    // if (HLT) {
    //     pass = true;
    // }
    // return pass;
    return HLT;
}

bool yt_cutflows::pass_met110_mht(bool HLT)
{
    // bool pass = false;
    // if (HLT) {
    //     pass = true;
    // }
    // return pass;
    return HLT;
}

//
// Sequential (after cleaning)
//
bool yt_cutflows::pass_seq_at_least_two_baseline_leptons(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 2) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 2 ? true : false;
}

bool yt_cutflows::pass_seq_at_least_two_signal_leptons(int Nlept)
{
    // bool pass = false;
    // if (Nlept >= 2) {
    //     pass = true;
    // }
    // return pass;
    return Nlept >= 2 ? true : false;
}

bool yt_cutflows::pass_seq_SFOS(int lep1Charge, int lep2Charge, int lep1Flavor, int lep2Flavor)
{
    bool pass = false;
    if ((lep1Flavor == lep2Flavor) && // Same flavor
        (lep1Charge != lep2Charge)) { // Opposite sign
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_leading_lepton_pT_less_than_50_GeV(float pT)
{
    // bool pass = false;
    // if (pT < 50) {
    //     pass = true;
    // }
    // return pass;
    return pT < 50. ? true : false;
}

bool yt_cutflows::pass_seq_at_least_one_signal_jet(int Njet)
{
    // bool pass = false;
    // if (Njet >= 1) {
    //     pass = true;
    // }
    // return pass;
    return Njet >= 1 ? true : false;
}

bool yt_cutflows::pass_seq_leading_jet_pT_greater_than_150_GeV(float pT)
{
    // bool pass = false;
    // if (pT > 150) {
    //     pass = true;
    // }
    // return pass;
    return pT > 150. ? true : false;
}

bool yt_cutflows::pass_seq_bjet_veto(int Njet)
{
    // bool pass = false;
    // if (Njet == 0) {
    //     pass = true;
    // }
    // return pass;
    return Njet == 0 ? true : false;
}

bool yt_cutflows::pass_seq_MET_greater_than_150_GeV(float MET)
{
    // bool pass = false;
    // if (MET > 150.) {
    //     pass = true;
    // }
    // return pass;
    return MET > 150. ? true : false;
}

bool yt_cutflows::pass_seq_Dphi_jet_MET_greater_than_2dot5(float dPhi_jet_MET)
{
    // bool pass = false;
    // if (dPhi_jet_MET > 2.5) {
    //     pass = true;
    // }
    // return pass;
    return dPhi_jet_MET > 2.5 ? true : false;
}

bool yt_cutflows::pass_seq_mll_less_than_50_GeV(float mll)
{
    // bool pass = false;
    // if (mll < 50.) {
    //     pass = true;
    // }
    // return pass;
    return mll < 50. ? true : false;
}

bool yt_cutflows::pass_seq_Rll_less_than_1dot5(float rll)
{
    // bool pass = false;
    // if (rll < 1.5) {
    //     pass = true;
    // }
    // return pass;
    return rll < 1.5 ? true : false;
}

bool yt_cutflows::pass_seq_mtt_less_than_0(float mtt)
{
    // bool pass = false;
    // if (mtt < 0.) {
    //     pass = true;
    // }
    // return pass;
    return mtt < 0. ? true : false;
}

// This part is used for the cutflow table in the note
bool yt_cutflows::pass_table_met_trigger(bool trigMatch_metTrig)
{
    return trigMatch_metTrig ? true :false;
}

bool yt_cutflows::pass_table_Stau_veto(int FS)
{
    return (FS != 206 && FS != 207) ? true : false;
}

bool yt_cutflows::pass_table_two_baseline_leptons(int nLep_base)
{
    return nLep_base == 2 ? true : false;
}

bool yt_cutflows::pass_table_two_signal_leptons(int nLep_signal)
{
    return nLep_signal == 2 ? true : false;
}

bool yt_cutflows::pass_table_same_flavor(int lep1Flavor, int lep2Flavor)
{
    return (lep1Flavor == lep2Flavor) ? true : false;
}

bool yt_cutflows::pass_table_opposit_charge(int lep1Charge, int lep2Charge)
{
    return (lep1Charge * lep2Charge == -1) ? true : false;
}

bool yt_cutflows::pass_table_lepton_truth_matching(bool lep1TruthMatched, bool lep2TruthMatched, int DatasetNumber)
{
    if ((lep1TruthMatched && lep2TruthMatched) ||
        (DatasetNumber >= 407311 && DatasetNumber <= 407315))
        return true;
    else
        return false;
}

bool yt_cutflows::pass_table_lepton_author_16_veto(int lep1Author, int lep2Author)
{
    return (lep1Author != 16 && lep2Author != 16) ? true : false;
}

bool yt_cutflows::pass_table_met_greater_than_200(float met_Et)
{
    return met_Et > 200. ? true : false;
}

bool yt_cutflows::pass_table_bjet_veto(int nBJet20_MV2c10)
{
    return nBJet20_MV2c10 == 0 ? true : false;
}

bool yt_cutflows::pass_table_leading_jet_pT_greater_than_100(float jetPt)
{
    return jetPt > 100. ? true : false;
}

bool yt_cutflows::pass_table_Dphi_jet_MET_greater_than_2(float DPhiJ1Met)
{
    return DPhiJ1Met > 2. ? true : false;
}

bool yt_cutflows::pass_table_min_Dphi_greater_than_0dot4(float minDPhiAllJetsMet)
{
    return minDPhiAllJetsMet > 0.4 ? true : false;
}

bool yt_cutflows::pass_table_mtautau_veto(float MTauTau)
{
    if (MTauTau > 0. && MTauTau < 160.) // veto
        return false;
    else
        return true;
}

bool yt_cutflows::pass_table_lep1Pt_greater_than_5(float lep1Pt)
{
    return lep1Pt > 5. ? true : false;
}

bool yt_cutflows::pass_table_mll_greater_than_1(float mll)
{
    return mll > 1. ? true : false;
}

bool yt_cutflows::pass_table_veto_mll_3_to_3dot2(float mll)
{
    if (mll > 3. && mll < 3.2) // veto
        return false;
    else
        return true;
}

bool yt_cutflows::pass_table_mll_less_than_60(float mll)
{
    return mll < 60. ? true : false;
}

bool yt_cutflows::pass_table_Rll_greater_than_0dot05(float Rll)
{
    return Rll > 0.05 ? true : false;
}

bool yt_cutflows::pass_table_METOverHT(float METOverHTLep, float mll)
{
    return METOverHTLep > max(5., 15. - 2. * mll) ? true : false;
}

bool yt_cutflows::pass_table_Rll_less_then_2(float Rll)
{
    return Rll < 2. ? true : false;
}

bool yt_cutflows::pass_table_lep1_mT_less_than_70(float mt_lep1)
{
    return mt_lep1 < 70. ? true : false;
}
