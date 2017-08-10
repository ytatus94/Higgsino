#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TTree.h>

#include "get_combined_hist.C"

#include <string>
#include <iostream>
using namespace std;

TH1F *get_TRUTH3_histograms(string n2_n1);
TH1F *get_common_ntuple_histogram(string n2_n1);

void overlap_histograms(string n2_n1)
{
    TH1F *h_truth3 = get_TRUTH3_histograms(n2_n1);
    TH1F *h_ntuple = get_common_ntuple_histogram(n2_n1);

    TCanvas *c = new TCanvas("c", "", 800, 600);
    c->SetLeftMargin(0.12);

    double area_ntuple = h_ntuple->Integral();
    h_ntuple->SetName(("h_" + n2_n1).c_str());
    h_ntuple->SetLineColor(kBlue);
    h_ntuple->SetXTitle("m_{ll} [GeV]");
    h_ntuple->SetYTitle("Events / 1GeV");
    h_ntuple->Draw();

    double area_truth3 = h_truth3->Integral();
    cout << "area_truth3=" << area_truth3 << endl; // Should be 1
    h_truth3->Scale(area_ntuple);
    h_truth3->SetLineColor(kRed);
    h_truth3->Draw("hist,same");
}

TH1F *get_TRUTH3_histograms(string n2_n1)
{
    // TRUTH3
    string path_truth3 = "/Users/ytshen/Desktop/20170810/";

    string f_N2N1 = "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root";
    string f_C1C1 = "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root";
    string f_N2C1p = "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string f_N2C1m = "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    TH1F *h_N2N1 = (TH1F *)get_histogram(path_truth3 + f_N2N1);
    TH1F *h_C1C1 = (TH1F *)get_histogram(path_truth3 + f_C1C1);
    TH1F *h_N2C1p = (TH1F *)get_histogram(path_truth3 + f_N2C1p);
    TH1F *h_N2C1m = (TH1F *)get_histogram(path_truth3 + f_N2C1m);

    double integral_N2N1  = h_N2N1->Integral();
    // double integral_C1C1  = h_C1C1->Integral(); // in common ntuple v1.8b, the C1C1 is not included in truthMll
    double integral_N2C1p = h_N2C1p->Integral();
    double integral_N2C1m = h_N2C1m->Integral();

    h_N2N1->Scale(1./integral_N2N1);
    // h_C1C1->Scale(1./integral_C1C1);
    h_N2C1p->Scale(1./integral_N2C1p);
    h_N2C1m->Scale(1./integral_N2C1m);

    // h_N2N1->Scale(integral_N2N1 / (integral_N2N1 + integral_C1C1 + integral_N2C1p + integral_N2C1m) );
    // h_C1C1->Scale(integral_C1C1 / (integral_N2N1 + integral_C1C1 + integral_N2C1p + integral_N2C1m) );
    // h_N2C1p->Scale(integral_N2C1p / (integral_N2N1 + integral_C1C1 + integral_N2C1p + integral_N2C1m) );
    // h_N2C1m->Scale(integral_N2C1m / (integral_N2N1 + integral_C1C1 + integral_N2C1p + integral_N2C1m) );
    h_N2N1->Scale(integral_N2N1 / (integral_N2N1 + integral_N2C1p + integral_N2C1m) );
    h_N2C1p->Scale(integral_N2C1p / (integral_N2N1 + integral_N2C1p + integral_N2C1m) );
    h_N2C1m->Scale(integral_N2C1m / (integral_N2N1 + integral_N2C1p + integral_N2C1m) );

    TH1F *h_Combined = (TH1F *)h_N2N1->Clone();
    // h_Combined->Add(h_C1C1);
    h_Combined->Add(h_N2C1p);
    h_Combined->Add(h_N2C1m);

    return h_Combined;
}

TH1F *get_common_ntuple_histogram(string n2_n1)
{
    // common ntuple v1.8
    string path_ntuple = "/Users/ytshen/Desktop/";
    string f_n2_n1 = "MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 + "_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";

    TFile *f_ntuple = new TFile((path_ntuple + f_n2_n1).c_str());

    TH1F *h_n2_n1 = new TH1F("h_n2_n1", "", 100, 0, 100);

    string tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 + "_2LMET50_MadSpin_NoSys";
    TTree *tree_n2_n1 = (TTree *)f_ntuple->Get(tree_name.c_str());
    tree_n2_n1->Project("h_n2_n1", "truthMll", "truthMll>0");
 
    return h_n2_n1;
}

