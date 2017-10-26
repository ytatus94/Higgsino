#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1.h>

#include "FuncMllDistr_modified.C"
#include "ytUtility.C"

#include <string>
#include <iostream>
using namespace std;

void get_names(int, int, int, string &, string &, string &, string &);
void copy_tree(string, string, string, string);
void add_weight(int, int, int, string, string);
double get_weight_mass();
double get_Xsec_ratio(int, int);

void add_weight_to_common_ntuple(int n2, int n1, int m12)
{
    string inputfile = "", outputfile = "";
    string tree_name = "", new_tree_name = "";

    get_names(n2, n1, m12, inputfile, outputfile, tree_name, new_tree_name);
    // cout << "inputfile=" << inputfile << endl;
    // cout << "outputfile=" << outputfile << endl;
    // cout << "tree_name=" << tree_name << endl;
    // cout << "new_tree_name=" << new_tree_name << endl;

    copy_tree(inputfile, outputfile, tree_name, new_tree_name);
    add_weight(n2, n1, m12, outputfile, new_tree_name);
}

void get_names(int n2, int n1, int m12, string &f_old, string &f_new, string &t_old, string &t_new)
{
    string path = "/Users/ytshen/Desktop/";
    string f_160_100 = "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
    string f_170_150 = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
    string f_190_150 = "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
    string f_m12_350 = "reweighted_m12_350.root";
    string f_m12_400 = "reweighted_m12_400.root";
    string f_m12_500 = "reweighted_m12_500.root";
    string f_m12_600 = "reweighted_m12_600.root";
    string f_m12_700 = "reweighted_m12_700.root";
    string f_m12_800 = "reweighted_m12_800.root";

    if (n2 == 160 && n1 == 100 && m12 == 350) {
        f_old = path + f_160_100;
        f_new = path + f_m12_350;
        t_old = "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_NoSys";
        t_new = t_old + "_reweighted_m12_350";
    }
    else if (n2 == 190 && n1 == 150 && m12 == 400) {
        f_old = path + f_190_150;
        f_new = path + f_m12_400;
        t_old = "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_NoSys";
        t_new = t_old + "_reweighted_m12_400";
    }
    else if (n2 == 190 && n1 == 150 && m12 == 500) {
        f_old = path + f_190_150;
        f_new = path + f_m12_500;
        t_old = "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_NoSys";
        t_new = t_old + "_reweighted_m12_500";
    }
    else if (n2 == 190 && n1 == 150 && m12 == 600) {
        f_old = path + f_190_150;
        f_new = path + f_m12_600;
        t_old = "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_NoSys";
        t_new = t_old + "_reweighted_m12_600";
    }
    else if (n2 == 170 && n1 == 150 && m12 == 700) {
        f_old = path + f_170_150;
        f_new = path + f_m12_700;
        t_old = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_NoSys";
        t_new = t_old + "_reweighted_m12_700";
    }
    else if (n2 == 170 && n1 == 150 && m12 == 800) {
        f_old = path + f_170_150;
        f_new = path + f_m12_800;
        t_old = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_NoSys";
        t_new = t_old + "_reweighted_m12_800";
    }
}

void copy_tree(string f_old, string f_new, string t_old, string t_new)
{
    TFile *fin = new TFile(f_old.c_str(), "READ");
    TTree *tree_in = (TTree *)fin->Get(t_old.c_str());
    TFile *fout = new TFile(f_new.c_str(), "RECREATE");
    TTree *tree_out = (TTree *)tree_in->CloneTree();
    tree_out->SetName(t_new.c_str());

    // cout << "fin=" << fin->GetName() << endl;
    // cout << "fout=" << fout->GetName() << endl;

    // Save into file
    fout->cd();
    tree_out->Write();
    fout->Close();
    fin->Close();
}

void add_weight(int n2, int n1, int m12, string f, string t)
{
    TFile *file = new TFile(f.c_str(), "UPDATE");
    TTree *tree = (TTree *)file->Get(t.c_str());

    double truthMll = 0.0;
    int FS = 0;
    // Connect branches to variables
    tree->SetBranchAddress("truthMll", &truthMll);
    tree->SetBranchAddress("FS", &FS);

    // Variables for new branches
    double weight_mass = -1.;
    double Xsec_ratio = -1.;
    double NUHM2_weight = -1.;
    // Bulidling the new branches
    TBranch *b_weight_mass = tree->Branch("weight_mass", &weight_mass, "weight_mass/D");
    TBranch *b_Xsec_ratio = tree->Branch("Xsec_ratio", &Xsec_ratio, "Xsec_ratio/D");
    TBranch *b_NUHM2_weight = tree->Branch("NUHM2_weight", &NUHM2_weight, "NUHM2_weight/D");

    double dm_Higgsino = n2 - n1;
    double par_Higgsino[3] = {1., static_cast<double>(n1), -1. * static_cast<double>(n2)};

    double dm_NUHM2 = get_dm_NUHM2(m12);
    double NUHM2_N1_mass = get_NUHM2_N1_mass(m12);
    double NUHM2_N2_mass = get_NUHM2_N2_mass(m12);
    double par_NUHM2[3] = {1., NUHM2_N1_mass, -1. * NUHM2_N2_mass};
    // cout << "NUHM2_N1_mass=" << NUHM2_N1_mass << endl;
    // cout << "NUHM2_N2_mass=" << NUHM2_N2_mass << endl;

    // Higgsino curve
    TF1 *func_Higgsino = new TF1("func_Higgsino", FuncMllDistr, 0, dm_Higgsino, 3);
    func_Higgsino->SetParameter(0, 1);
    func_Higgsino->SetParameter(1, n1);
    func_Higgsino->SetParameter(2, -1*n2);
    func_Higgsino->FixParameter(1, n1);
    func_Higgsino->FixParameter(2, -1*n2);
    func_Higgsino->SetLineColor(kGreen);
    func_Higgsino->SetLineStyle(2);

    // NUHM2 curve
    TF1 *func_NUHM2= new TF1("func_NUHM2", FuncMllDistr, 0, dm_NUHM2, 3);
    func_NUHM2->SetParameter(0, 1);
    func_NUHM2->SetParameter(1, NUHM2_N1_mass);
    func_NUHM2->SetParameter(2, -1*NUHM2_N2_mass);
    func_NUHM2->FixParameter(1, NUHM2_N1_mass);
    func_NUHM2->FixParameter(2, -1*NUHM2_N2_mass);
    func_NUHM2->SetLineColor(kRed);
    func_NUHM2->SetLineStyle(2);

    //normalize the two curve to the same area (=1)
    double integral_func_Higgsino = func_Higgsino->Integral(0, dm_Higgsino);
    double integral_func_NUHM2 = func_NUHM2->Integral(0, dm_NUHM2);
    func_Higgsino->SetParameter(0, 1./integral_func_Higgsino);
    func_NUHM2->SetParameter(0, 1./integral_func_NUHM2);

    par_Higgsino[0] = 1./integral_func_Higgsino;
    par_NUHM2[0] = 1./integral_func_NUHM2;
    // cout << "par_Higgsino[0]=" << par_Higgsino[0] << endl;
    // cout << "par_Higgsino[1]=" << par_Higgsino[1] << endl;
    // cout << "par_Higgsino[2]=" << par_Higgsino[2] << endl;
    // cout << "par_NUHM2[0]=" << par_NUHM2[0] << endl;
    // cout << "par_NUHM2[1]=" << par_NUHM2[1] << endl;
    // cout << "par_NUHM2[2]=" << par_NUHM2[2] << endl;
    // cout << "integral_func_Higgsino=" << func_Higgsino->Integral(0, dm_Higgsino) << endl;
    // cout << "integral_func_NUHM2=" << func_NUHM2->Integral(0, dm_NUHM2) << endl;

    TH1F *h_truth_Mll = new TH1F("h_truth_Mll", "truth Mll", 200, 0, 200);
    TH1F *h_reweighted_Mll = new TH1F("h_reweighted_Mll", "reweighted Mll", 200, 0, 200);

    // loop over events
    int nevents = tree->GetEntries();
    // cout << "nevents=" << nevents << endl;
    for (int i = 0; i < nevents; i++) {
        tree->GetEntry(i);
        //tree->Fill();

        double Higgsino_w = FuncMllDistr(&truthMll, par_Higgsino);
        double NUHM2_w = FuncMllDistr(&truthMll, par_NUHM2);
        weight_mass = NUHM2_w / Higgsino_w;

        Xsec_ratio = get_Xsec_ratio(FS, m12);

        NUHM2_weight = weight_mass * Xsec_ratio;

        b_weight_mass->Fill();
        b_Xsec_ratio->Fill();
        b_NUHM2_weight->Fill();

        h_truth_Mll->Fill(truthMll);
        h_reweighted_Mll->Fill(truthMll, NUHM2_weight);

        // cout << i << ": " << truthMll
        // << ", NUHM2_w/Higgsino_w=" << NUHM2_w << "/" << Higgsino_w << "=" << weight_mass 
        // << ", Xsec_ratio=" << Xsec_ratio
        // << ", NUHM2_weight=" << NUHM2_weight
        // << endl;
    }

    tree->Write();
    h_truth_Mll->Write();
    h_reweighted_Mll->Write();
    file->Close();
}

double get_Xsec_ratio(int FS, int m12)
{
    double Xsec_ratio = 1.0;
    if (FS == 112) { // N2N1
        if (m12 == 350)      Xsec_ratio = 0.500489103669;
        else if (m12 == 400) Xsec_ratio = 1.40609496035;
        else if (m12 == 500) Xsec_ratio = 1.48420174312;
        else if (m12 == 600) Xsec_ratio = 1.49620688527;
        else if (m12 == 700) Xsec_ratio = 1.18114972806;
        else if (m12 == 800) Xsec_ratio = 1.17312186754;
    }
    else if (FS == 157) { // C1C1
        if (m12 == 350)      Xsec_ratio = 0.809295197893;
        else if (m12 == 400) Xsec_ratio = 1.85763670956;
        else if (m12 == 500) Xsec_ratio = 1.60709633189;
        else if (m12 == 600) Xsec_ratio = 1.48886200733;
        else if (m12 == 700) Xsec_ratio = 1.14281934535;
        else if (m12 == 800) Xsec_ratio = 1.10758453419;
    }
    else if (FS == 125) { // N2C1p
        if (m12 == 350)      Xsec_ratio = 0.75334324027;
        else if (m12 == 400) Xsec_ratio = 1.61810558673;
        else if (m12 == 500) Xsec_ratio = 1.61195100629;
        else if (m12 == 600) Xsec_ratio = 1.60540039476;
        else if (m12 == 700) Xsec_ratio = 1.17032101263;
        else if (m12 == 800) Xsec_ratio = 1.16731420042;
    }
    else if (FS == 127) { // N2C1m
        if (m12 == 350)      Xsec_ratio = 0.751651917122;
        else if (m12 == 400) Xsec_ratio = 1.68915991429;
        else if (m12 == 500) Xsec_ratio = 1.68026588159;
        else if (m12 == 600) Xsec_ratio = 1.66943310114;
        else if (m12 == 700) Xsec_ratio = 1.1917838431;
        else if (m12 == 800) Xsec_ratio = 1.18958896195;
    }
    return Xsec_ratio;
}
