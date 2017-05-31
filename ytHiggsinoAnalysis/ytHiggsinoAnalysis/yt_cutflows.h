#ifndef YT_CUTFLOWS_H
#define YT_CUTFLOWS_H

#include <TROOT.h>

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

enum cuts {
    all_events,
    event_cleaning,
    grl,
    global_flags,
    primary_vertex,
    bad_muon,
    bad_jet,
    // Non-sequential
    at_least_one_baseline_electron,
    at_least_one_signal_electron,
    at_least_one_baseline_muon,
    at_least_one_signal_muon,
    at_least_two_baseline_electron,
    at_least_two_signal_electron,
    at_least_two_baseline_muon,
    at_least_two_signal_muon,
    at_least_two_baseline_leptons,
    at_least_two_signal_leptons,
    exactly_three_baseline_electrons,
    exactly_three_signal_electrons,
    exactly_three_baseline_muons,
    exactly_three_signal_muons,
    exactly_three_baseline_leptons,
    exactly_three_signal_leptons,
    at_least_one_baseline_jet,
    at_least_one_signal_jet,
    zero_bjet,
    cut_mu4_j125_xe90_mht,
    cut_2mu4_j85_xe50_mht,
    cut_met110_mht,
    Ncuts,
    // Sequential
    seq_at_least_two_baseline_leptons,
    seq_at_least_two_signal_leptons,
    seq_SFOS,
    seq_leading_lepton_pT_less_than_50_GeV,
    seq_at_least_one_signal_jet,
    seq_leading_jet_pT_greater_than_150_GeV,
    seq_bjet_veto,
    seq_MET_greater_than_150_GeV,
    seq_Dphi_jet_MET_greater_than_2dot5,
    seq_mll_less_than_50_GeV,
    seq_Rll_less_than_1dot5,
    seq_mtt_less_than_zero,
    seq_Ncuts
};

class yt_cutflows
{
public:
    vector<double> events_pass_cutflows;
    vector<double> weighted_events_pass_cutflows;

public:
    yt_cutflows();
    virtual ~yt_cutflows();
    void update(int cut, bool passed, float weight);
    void print(bool is_sequential);

    // user defined cutflow methods
    bool pass_all_events();
    bool pass_event_cleaning(); // sequential
    bool pass_GRL();
    bool pass_global_flags(); // LAr/Tile/SCT errors and core flags
    bool pass_primary_vertex();
    bool pass_bad_muon();
    bool pass_bad_jet();

    // Non-sequential (after cleaning)
    // Electrons
    bool pass_at_least_one_baseline_electron(int Nlept);
    bool pass_at_least_one_signal_electron(int Nlept);
    bool pass_at_least_two_baseline_electrons(int Nlept);
    bool pass_at_least_two_signal_electrons(int Nlept);
    bool pass_exactly_three_baseline_electrons(int Nlept);
    bool pass_exactly_three_signal_electrons(int Nlept);
    // Muons
    bool pass_at_least_one_baseline_muon(int Nlept);
    bool pass_at_least_one_signal_muon(int Nlept);
    bool pass_at_least_two_baseline_muons(int Nlept);
    bool pass_at_least_two_signal_muons(int Nlept);
    bool pass_exactly_three_baseline_muons(int Nlept);
    bool pass_exactly_three_signal_muons(int Nlept);
    // Leptons
    bool pass_at_least_two_baseline_leptons(int Nlept);
    bool pass_at_least_two_signal_leptons(int Nlept);
    bool pass_exactly_three_baseline_leptons(int Nlept);
    bool pass_exactly_three_signal_leptons(int Nlept);
    // Jets
    bool pass_at_least_one_baseline_jet(int Njet);
    bool pass_at_least_one_signal_jet(int Njet);
    bool pass_zero_bjet(int Njet);
    // Triggers
    bool pass_mu4_j125_xe90_mht(bool HLT);
    bool pass_2mu4_j85_xe50_mht(bool HLT);
    bool pass_met110_mht(bool HLT);

    // Sequential (after cleaning)
    bool pass_seq_at_least_two_baseline_leptons(int Nlept, float weight);
    bool pass_seq_at_least_two_signal_leptons(int Nlept, float weight);
    bool pass_seq_SFOS(int lep1Charge, int lep2Charge, int lep1Flavor, int lep2Flavor, float weight);
    bool pass_seq_leading_lepton_pT_less_than_50_GeV(float pT, float weight);
    bool pass_seq_at_least_one_signal_jet(int Njet, float weight);
    bool pass_seq_leading_jet_pT_greater_than_150_GeV(float pT, float weight);
    bool pass_seq_bjet_veto(int Njet, float weight);
    bool pass_seq_MET_greater_than_150_GeV(float MET, float weight);
    bool pass_seq_Dphi_jet_MET_greater_than_2dot5(float dPhi_jet_MET, float weight);
    bool pass_seq_mll_less_than_50_GeV(float mll, float weight);
    bool pass_seq_Rll_less_than_1dot5(float rll, float weight);
    bool pass_seq_mtt_less_than_0(float mtt, float weight);

    ClassDef(yt_cutflows, 0); //Set ClassVersionID=0 in case you don't need object I/O.
};

#endif // #ifndef YT_CUTFLOWS_H
