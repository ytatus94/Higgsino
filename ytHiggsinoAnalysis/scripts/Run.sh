#!/bin/bash

function run_NUMH2_signal() {
    # echo "run_NUMH2_signal"
    # NUHM2
    Run optimization analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_300_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_350_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_400_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_500_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_600_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_700_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_800_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
}

function run_Higgsino_signal() {
    # echo "run_Higgsino_signal"
    # Higgsino
    Run optimization analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SM_Higgsino_160_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
}

function run_bkg() {
    # echo "run_bkg..."
    # Bkg
    Run optimization analysis_type=MC sample_type=backgrounds sample=AllBkgsButFakes_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root

    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_DY_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_Wgamma_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_Zgamma_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_Zttgamma_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_Zvvgamma_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_diboson1L_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_diboson1L_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_diboson2L_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_diboson2L_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_diboson3L_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_diboson3L_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_diboson4L_PowPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_diboson4L_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_triboson_Sherpa222_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_ttbar_MGPy_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_ttbar_PowPy8_dilep_hdamp258p75_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_ttbar_PowPy8_nonallhad_hdamp172p5_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_ttbar_PowPy8_nonallhad_hdamp258p75_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_ttbar_Sherpa_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_ttbar_aMcAtNlo_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=alt_ttbar_nonallhad_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root

    Run optimization analysis_type=MC sample_type=backgrounds sample=diboson0L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=diboson1L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=diboson2L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=diboson3L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=diboson4L_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=triboson_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=higgs_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=singletop_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=topOther_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=ttbar_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=Wgamma_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=Wjets_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=Zgamma_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=Zjets_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=Zttgamma_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=Zttjets_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run optimization analysis_type=MC sample_type=backgrounds sample=Zvvjets_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
}

function run_cutflow() {
    echo "run_cutflow..."
    # Higgsino
    # Run cutflow analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SM_Higgsino_105_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
    # Slepton
    # Run cutflow analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SlepSlep_direct_110p0_100p0_MET50_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
    # Data
    # Run cutflow analysis_type=Data sample_type=data sample=data_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root
    # Bkg
    # Run cutflow analysis_type=MC sample_type=backgrounds sample=diboson3L_SusySkimHiggsino_v1.8_SUSY16_tree_NoSys.root

    # Cutflow comparison which Till requested
    # Higgsion
    Run cutflow analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run cutflow analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SM_Higgsino_160_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run cutflow analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    Run cutflow analysis_type=MC sample_type=signals sample=MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root
    # NUHM2
    Run cutflow analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_300_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run cutflow analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_350_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run cutflow analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_400_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run cutflow analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_500_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run cutflow analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_600_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run cutflow analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_700_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
    Run cutflow analysis_type=MC sample_type=NUHM2 sample=MGPy8EG_A14N23LO_NUHM2_m12_800_weak_2LMET50_MadSpin_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root
}

if [ $1 != "" ]; then
    if [ $1 == "NUHM2" ]; then
        run_NUMH2_signal
    elif [ $1 == "Higgsino" ]; then
        run_Higgsino_signal
    elif [ $1 == "bkg" ]; then
        run_bkg
    elif [ $1 == "cutflow" ]; then
        run_cutflow
    else
        echo "Error: $1 does not support! Using NUHM2, Higgsino, bkg or cutflow." 
    fi
fi
