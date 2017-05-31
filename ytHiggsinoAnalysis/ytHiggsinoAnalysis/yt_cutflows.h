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
    all_events, // 0
    event_cleaning, // 1
    grl, // 2
    global_flags, // 3
    primary_vertex, // 4
    bad_muon, // 5
    bad_jet, // 6
    // Non-sequential
    at_least_one_baseline_electron, // 7
    at_least_one_signal_electron, // 8
    at_least_one_baseline_muon, // 9
    at_least_one_signal_muon,  // 10
    at_least_two_baseline_electron, // 11
    at_least_two_signal_electron, // 12
    at_least_two_baseline_muon, // 13
    at_least_two_signal_muon, // 14
    at_least_two_baseline_leptons, // 15
    at_least_two_signal_leptons, // 16
    exactly_three_baseline_electrons, // 17
    exactly_three_signal_electrons, // 18
    exactly_three_baseline_muons, // 19
    exactly_three_signal_muons, // 20
    exactly_three_baseline_leptons, // 21
    exactly_three_signal_leptons, // 22
    at_least_one_baseline_jet, // 23
    at_least_one_signal_jet, // 24
    zero_bjet, // 25
    cut_mu4_j125_xe90_mht, // 26
    cut_2mu4_j85_xe50_mht, // 27
    cut_met110_mht, // 28
    Ncuts, // 29
    // Sequential
    seq_at_least_two_baseline_leptons, // 30
    seq_at_least_two_signal_leptons, // 31
    seq_SFOS, // 32
    seq_leading_lepton_pT_less_than_50_GeV, // 33
    seq_at_least_one_signal_jet, // 34
    seq_leading_jet_pT_greater_than_150_GeV, // 35
    seq_bjet_veto, // 36
    seq_MET_greater_than_150_GeV, // 37
    seq_Dphi_jet_MET_greater_than_2dot5, // 38
    seq_mll_less_than_50_GeV, // 39
    seq_Rll_less_than_1dot5, // 40
    seq_mtt_less_than_zero, // 41
    seq_Ncuts // 42
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
    void print();

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
    bool pass_seq_at_least_two_baseline_leptons(int Nlept);
    bool pass_seq_at_least_two_signal_leptons(int Nlept);
    bool pass_seq_SFOS(int lep1Charge, int lep2Charge, int lep1Flavor, int lep2Flavor);
    bool pass_seq_leading_lepton_pT_less_than_50_GeV(float pT);
    bool pass_seq_at_least_one_signal_jet(int Njet);
    bool pass_seq_leading_jet_pT_greater_than_150_GeV(float pT);
    bool pass_seq_bjet_veto(int Njet);
    bool pass_seq_MET_greater_than_150_GeV(float MET);
    bool pass_seq_Dphi_jet_MET_greater_than_2dot5(float dPhi_jet_MET);
    bool pass_seq_mll_less_than_50_GeV(float mll);
    bool pass_seq_Rll_less_than_1dot5(float rll);
    bool pass_seq_mtt_less_than_0(float mtt);

    ClassDef(yt_cutflows, 0); //Set ClassVersionID=0 in case you don't need object I/O.
};

#endif // #ifndef YT_CUTFLOWS_H
