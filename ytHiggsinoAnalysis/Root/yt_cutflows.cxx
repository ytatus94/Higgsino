#define YT_CUTFLOWS_CXX
#include "ytHiggsinoAnalysis/yt_cutflows.h"

ClassImp(yt_cutflows)

const char* cut_name[] = {
    // Non-sequential
    "Cut: All events",
    "Cut: >= 1 baseline electron",
    "Cut: >= 1 signal electron",
    "Cut: >= 1 baseline muon",
    "Cut: >= 1 signal muon",
    "Cut: >= 2 baseline electron",
    "Cut: >= 2 signal electron",
    "Cut: >= 2 baseline muon",
    "Cut: >= 2 signal muon",
    "Cut: >= 2 baseline leptons",
    "Cut: >= 2 signal leptons",
    "Cut: exactly 3 baseline electrons",
    "Cut: exactly 3 signal electrons",
    "Cut: exactly 3 baseline muons",
    "Cut: exactly 3 signal muons",
    "Cut: exactly 3 baseline leptons",
    "Cut: exactly 3 signal leptons",
    "Cut: >= 1 baseline jet",
    "Cut: >= 1 signal jet",
    "Cut: zero b-jet",
    "Cut: pass mu4_j125_xe90_mht",
    "Cut: pass 2mu4_j85_xe50_mht",
    "Cut: pass met110_mht",
    // Sequential
    "Cut 1: >= 2 baseline leptons",
    "Cut 2: >= 2 signal leptons",
    "Cut 3: SFOS",
    "Cut 4: leading lepton pT < 50 GeV",
    "Cut 5: >= 1 signal jet",
    "Cut 6: leading jet pT > 150 GeV",
    "Cut 7: b-jet veto",
    "Cut 8: MET > 150 GeV",
    "Cut 9: Dphi(jet, MET) > 2.5",
    "Cut 10: mll < 50 GeV",
    "Cut 11: Rll < 1.5",
    "Cut 12: mtt < 0"
};

yt_cutflows::yt_cutflows()
{
    events_pass_cutflows = vector<double>(seq_Ncuts, 0); // initialize Ncuts elements to zero.
    weighted_events_pass_cutflows = vector<double>(seq_Ncuts, 0); // initialize Ncuts elements to zero.
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

void yt_cutflows::print(bool is_sequential)
{
    cout << "********** Cutflow **********" << endl;
    if (!is_sequential) { // non-sequential
        for (int cuts = 0; cuts < Ncuts; cuts++) {
            cout << setw(20) << left << cut_name[cuts] << " = "
                 << setw(10) << events_pass_cutflows[cuts] << " / " 
                 << setw(10) << weighted_events_pass_cutflows[cuts] << "(weighted)" << endl;
        }
    }
    else {
        for (int cuts = Ncuts; cuts < seq_Ncuts; cuts++) {
            cout << setw(20) << left << cut_name[cuts] << " = "
                 << setw(10) << events_pass_cutflows[cuts] << " / " 
                 << setw(10) << weighted_events_pass_cutflows[cuts] << "(weighted)" << endl;
        }
    }
    cout << "******************************" << endl;
}

// user defined cutflow methods
bool yt_cutflows::pass_all_events()
{
    bool pass = false;
    if (true) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_event_cleaning() // sequential
{
    bool pass = false;
    if (true) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_GRL()
{
    bool pass = false;
    if (true) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_global_flags() // LAr/Tile/SCT errors and core flags
{
    bool pass = false;
    if (true) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_primary_vertex()
{
    bool pass = false;
    if (true) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_bad_muon()
{
    bool pass = false;
    if (true) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_bad_jet()
{
    bool pass = false;
    if (true) {
        pass = true;
    }
    return pass;
}

// Non-sequential (after cleaning)
// Electrons
bool yt_cutflows::pass_at_least_one_baseline_electron(int Nlept)
{
    bool pass = false;
    if (Nlept >= 1) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_at_least_one_signal_electron(int Nlept)
{
    bool pass = false;
    if (Nlept >= 1) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_at_least_two_baseline_electrons(int Nlept)
{
    bool pass = false;
    if (Nlept >= 2) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_at_least_two_signal_electrons(int Nlept)
{
    bool pass = false;
    if (Nlept >= 2) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_exactly_three_baseline_electrons(int Nlept)
{
    bool pass = false;
    if (Nlept == 3) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_exactly_three_signal_electrons(int Nlept)
{
    bool pass = false;
    if (Nlept == 3) {
        pass = true;
    }
    return pass;
}

// Muons
bool yt_cutflows::pass_at_least_one_baseline_muon(int Nlept)
{
    bool pass = false;
    if (Nlept >= 1) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_at_least_one_signal_muon(int Nlept)
{
    bool pass = false;
    if (Nlept >= 1) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_at_least_two_baseline_muons(int Nlept)
{
    bool pass = false;
    if (Nlept >= 2) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_at_least_two_signal_muons(int Nlept)
{
    bool pass = false;
    if (Nlept >= 2) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_exactly_three_baseline_muons(int Nlept)
{
    bool pass = false;
    if (Nlept == 3) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_exactly_three_signal_muons(int Nlept)
{
    bool pass = false;
    if (Nlept == 3) {
        pass = true;
    }
    return pass;
}

// Leptons
bool yt_cutflows::pass_at_least_two_baseline_leptons(int Nlept)
{
    bool pass = false;
    if (Nlept >= 2) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_at_least_two_signal_leptons(int Nlept)
{
    bool pass = false;
    if (Nlept >= 2) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_exactly_three_baseline_leptons(int Nlept)
{
    bool pass = false;
    if (Nlept == 3) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_exactly_three_signal_leptons(int Nlept)
{
    bool pass = false;
    if (Nlept == 3) {
        pass = true;
    }
    return pass;
}

// Jets
bool yt_cutflows::pass_at_least_one_baseline_jet(int Njet)
{
    bool pass = false;
    if (Njet >= 1) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_at_least_one_signal_jet(int Njet)
{
    bool pass = false;
    if (Njet >= 1) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_zero_bjet(int Njet)
{
    bool pass = false;
    if (Njet == 0) {
        pass = true;
    }
    return pass;
}

// Triggers
bool yt_cutflows::pass_mu4_j125_xe90_mht(bool HLT)
{
    bool pass = false;
    if (HLT) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_2mu4_j85_xe50_mht(bool HLT)
{
    bool pass = false;
    if (HLT) {
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_met110_mht(bool HLT)
{
    bool pass = false;
    if (HLT) {
        pass = true;
    }
    return pass;
}

//
// Sequential (after cleaning)
//
bool yt_cutflows::pass_seq_at_least_two_baseline_leptons(int Nlept, float weight)
{
    bool pass = false;
    if (Nlept >= 2) {
        update(seq_at_least_two_baseline_leptons, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_at_least_two_signal_leptons(int Nlept, float weight)
{
    bool pass = false;
    if (Nlept >= 2) {
        update(seq_at_least_two_signal_leptons, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_SFOS(int lep1Charge, int lep2Charge, int lep1Flavor, int lep2Flavor, float weight)
{
    bool pass = false;
    if ((lep1Flavor == lep2Flavor) && // Same flavor
        (lep1Charge != lep2Charge)) { // Opposite sign
        update(seq_SFOS, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_leading_lepton_pT_less_than_50_GeV(float pT, float weight)
{
    bool pass = false;
    if (pT < 50) {
        update(seq_leading_lepton_pT_less_than_50_GeV, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_at_least_one_signal_jet(int Njet, float weight)
{
    bool pass = false;
    if (Njet >= 1) {
        update(seq_at_least_one_signal_jet, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_leading_jet_pT_greater_than_150_GeV(float pT, float weight)
{
    bool pass = false;
    if (pT > 150) {
        update(seq_leading_jet_pT_greater_than_150_GeV, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_bjet_veto(int Njet, float weight)
{
    bool pass = false;
    if (Njet == 0) {
        update(seq_bjet_veto, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_MET_greater_than_150_GeV(float MET, float weight)
{
    bool pass = false;
    if (MET > 150.) {
        update(seq_MET_greater_than_150_GeV, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_Dphi_jet_MET_greater_than_2dot5(float dPhi_jet_MET, float weight)
{
    bool pass = false;
    if (dPhi_jet_MET > 2.5) {
        update(seq_Dphi_jet_MET_greater_than_2dot5, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_mll_less_than_50_GeV(float mll, float weight)
{
    bool pass = false;
    if (mll < 50.) {
        update(seq_mll_less_than_50_GeV, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_Rll_less_than_1dot5(float rll, float weight)
{
    bool pass = false;
    if (rll < 1.5) {
        update(seq_Rll_less_than_1dot5, true, weight);
        pass = true;
    }
    return pass;
}

bool yt_cutflows::pass_seq_mtt_less_than_0(float mtt, float weight)
{
    bool pass = false;
    if (mtt < 0.) {
        update(seq_mtt_less_than_zero, true, weight);
        pass = true;
    }
    return pass;
}
