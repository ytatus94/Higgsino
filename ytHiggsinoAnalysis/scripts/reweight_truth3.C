#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TLegend.h>

#include "FuncMllDistr.C"
#include "get_combined_hist.C"

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

TH1F *get_truth3_nuhm2(int);
TH1F *get_truth3_higgsino(bool, string, int);
TH1F *treeReader(bool, string, int, string, string);
// void treeReader(bool, string, int, string, string, TH1F *, TH1F *);
double get_reweight_ratio_1(string, int, double);
double get_reweight_ratio_2(string, int, double);

void reweight_truth3(string n2_n1, int m12)
{
    TH1F *h_nuhm2 = get_truth3_nuhm2(m12);
    TH1F *h_higgsino_original = get_truth3_higgsino(false, n2_n1, m12);
    TH1F *h_higgsino_reweight = get_truth3_higgsino(true, n2_n1, m12);

    TCanvas *c = new TCanvas("c", "", 800, 600);
    c->SetLeftMargin(0.12);
    bool logY = false;

    if (logY)
        gPad->SetLogy();

    double x_max = 0;
    if (m12 < 400)
        x_max = 100.;
    else if (m12 >= 400)
        x_max = 50.;

    double y_max_higgsino = max(h_higgsino_original->GetMaximum(), h_higgsino_reweight->GetMaximum());
    double y_max = max(y_max_higgsino, h_nuhm2->GetMaximum()) * 1.2;

    h_higgsino_original->SetTitle("");
    h_higgsino_original->SetXTitle("m_{ll} [GeV]");
    h_higgsino_original->SetYTitle("Normalized event counts");
    h_higgsino_original->GetXaxis()->SetRangeUser(0, x_max);
    h_higgsino_original->GetYaxis()->SetTitleOffset(1.2);
    h_higgsino_original->SetMaximum(y_max);
    h_higgsino_original->SetLineColor(kGreen);
    h_higgsino_original->SetStats(0);
    h_higgsino_original->Draw("hist,same");

    h_higgsino_reweight->SetLineColor(kRed);
    h_higgsino_reweight->Draw("hist,same");

    h_nuhm2->SetLineColor(kBlue);
    h_nuhm2->Draw("hist,same");

    TLegend *legend = new TLegend(0.5, 0.6, 0.9, 0.8);
    legend->AddEntry(h_higgsino_original, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_nuhm2, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->AddEntry(h_higgsino_reweight, ("reweighted Higgsino_" + n2_n1).c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "reweight_2_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());
}

TH1F *get_truth3_nuhm2(int m12)
{
    // string path_nuhm2 = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/SimpleAnalysis/Results/20170730/";
    string path_nuhm2 = "/Users/ytshen/Desktop/20170730/";

    string f_nuhm2_N2N1 = "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    string f_nuhm2_C1C1 = "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string f_nuhm2_N2C1p = "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string f_nuhm2_N2C1m = "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    string file5 = path_nuhm2 + f_nuhm2_N2N1;
    string file6 = path_nuhm2 + f_nuhm2_C1C1;
    string file7 = path_nuhm2 + f_nuhm2_N2C1p;
    string file8 = path_nuhm2 + f_nuhm2_N2C1m;

    TH1F *h_nuhm2 = get_combined_hist(file5, file6, file7, file8);

    return h_nuhm2;
}

TH1F *get_truth3_higgsino(bool is_reweight, string n2_n1, int m12)
{
    // string path_higgsino = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/SimpleAnalysis/Results/20170802/";
    string path_higgsino = "/Users/ytshen/Desktop/20170802/";

    string f_higgsino_N2N1 = "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root";
    string f_higgsino_C1C1 = "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root";
    string f_higgsino_N2C1p = "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string f_higgsino_N2C1m = "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    double n2 = stod(n2_n1.substr(0, n2_n1.find("_"))); // stod() converts string to double
    double n1 = stod(n2_n1.substr(n2_n1.find("_") + 1, n2_n1.length()));
    double dm_higgsino = n2 - n1;

    string file1 = path_higgsino + f_higgsino_N2N1;
    string file2 = path_higgsino + f_higgsino_C1C1;
    string file3 = path_higgsino + f_higgsino_N2C1p;
    string file4 = path_higgsino + f_higgsino_N2C1m;

    // TH1F *h_N2N1_original = treeReader(false, n2_n1, m12, file1, "EwkHiggsino2016__ntuple");
    // TH1F *h_C1C1_original = treeReader(false, n2_n1, m12, file2, "EwkHiggsino2016__ntuple");
    // TH1F *h_N2C1p_original = treeReader(false, n2_n1, m12, file3, "EwkHiggsino2016__ntuple");
    // TH1F *h_N2C1m_original = treeReader(false, n2_n1, m12, file4, "EwkHiggsino2016__ntuple");

    // TH1F *h_N2N1_reweight = treeReader(true, n2_n1, m12, file1, "EwkHiggsino2016__ntuple");
    // TH1F *h_C1C1_reweight = treeReader(true, n2_n1, m12, file2, "EwkHiggsino2016__ntuple");
    // TH1F *h_N2C1p_reweight = treeReader(true, n2_n1, m12, file3, "EwkHiggsino2016__ntuple");
    // TH1F *h_N2C1m_reweight = treeReader(true, n2_n1, m12, file4, "EwkHiggsino2016__ntuple");

    if (!is_reweight) { // original
        TH1F *h_N2N1_original = treeReader(false, n2_n1, m12, file1, "EwkHiggsino2016__ntuple");
        TH1F *h_C1C1_original = treeReader(false, n2_n1, m12, file2, "EwkHiggsino2016__ntuple");
        TH1F *h_N2C1p_original = treeReader(false, n2_n1, m12, file3, "EwkHiggsino2016__ntuple");
        TH1F *h_N2C1m_original = treeReader(false, n2_n1, m12, file4, "EwkHiggsino2016__ntuple");

        double integral_N2N1_original  = h_N2N1_original->Integral();
        double integral_C1C1_original  = h_C1C1_original->Integral();
        double integral_N2C1p_original = h_N2C1p_original->Integral();
        double integral_N2C1m_original = h_N2C1m_original->Integral();

        double sum_original = integral_N2N1_original + integral_C1C1_original + integral_N2C1p_original + integral_N2C1m_original;

        h_N2N1_original->Scale(1./integral_N2N1_original);
        h_C1C1_original->Scale(1./integral_C1C1_original);
        h_N2C1p_original->Scale(1./integral_N2C1p_original);
        h_N2C1m_original->Scale(1./integral_N2C1m_original);

        h_N2N1_original->Scale(integral_N2N1_original / sum_original);
        h_C1C1_original->Scale(integral_C1C1_original / sum_original);
        h_N2C1p_original->Scale(integral_N2C1p_original / sum_original);
        h_N2C1m_original->Scale(integral_N2C1m_original / sum_original);

        TH1F *h_Combined_original = (TH1F *)h_N2N1_original->Clone();
        h_Combined_original->Add(h_C1C1_original);
        h_Combined_original->Add(h_N2C1p_original);
        h_Combined_original->Add(h_N2C1m_original);

        return h_Combined_original;
    }
    else {
        TH1F *h_N2N1_reweight = treeReader(true, n2_n1, m12, file1, "EwkHiggsino2016__ntuple");
        TH1F *h_C1C1_reweight = treeReader(true, n2_n1, m12, file2, "EwkHiggsino2016__ntuple");
        TH1F *h_N2C1p_reweight = treeReader(true, n2_n1, m12, file3, "EwkHiggsino2016__ntuple");
        TH1F *h_N2C1m_reweight = treeReader(true, n2_n1, m12, file4, "EwkHiggsino2016__ntuple");

        double integral_N2N1_reweight  = h_N2N1_reweight->Integral();
        double integral_C1C1_reweight  = h_C1C1_reweight->Integral();
        double integral_N2C1p_reweight = h_N2C1p_reweight->Integral();
        double integral_N2C1m_reweight = h_N2C1m_reweight->Integral();

        double sum_reweight = integral_N2N1_reweight + integral_C1C1_reweight + integral_N2C1p_reweight + integral_N2C1m_reweight;

        h_N2N1_reweight->Scale(1./integral_N2N1_reweight);
        h_C1C1_reweight->Scale(1./integral_C1C1_reweight);
        h_N2C1p_reweight->Scale(1./integral_N2C1p_reweight);
        h_N2C1m_reweight->Scale(1./integral_N2C1m_reweight);

        h_N2N1_reweight->Scale(integral_N2N1_reweight / sum_reweight);
        h_C1C1_reweight->Scale(integral_C1C1_reweight / sum_reweight);
        h_N2C1p_reweight->Scale(integral_N2C1p_reweight / sum_reweight);
        h_N2C1m_reweight->Scale(integral_N2C1m_reweight / sum_reweight);

        TH1F *h_Combined_reweight = (TH1F *)h_N2N1_reweight->Clone();
        h_Combined_reweight->Add(h_C1C1_reweight);
        h_Combined_reweight->Add(h_N2C1p_reweight);
        h_Combined_reweight->Add(h_N2C1m_reweight);

        return h_Combined_reweight;
    }
}

TH1F *treeReader(bool is_reweight, string n2_n1, int m12, string file_name, string tree_name)
// void treeReader(bool is_reweight, string n2_n1, int m12, string file_name, string tree_name, TH1F *h_original, TH1F *h_reweight)
{
    TH1F *h_original = new TH1F("h_original", "", 200, 0, 200);
    TH1F *h_reweight = new TH1F("h_reweight", "", 200, 0, 200);

    TFile *f = new TFile(file_name.c_str());
    TTreeReader myReader(tree_name.c_str(), f);
    TTreeReaderValue<float> original_mll(myReader, "mll");

    while (myReader.Next()) {
        h_original->Fill(*original_mll);

        // double ratio = get_reweight_ratio_1(n2_n1, m12, *original_mll);
        double ratio = get_reweight_ratio_2(n2_n1, m12, *original_mll);
        double reweight_mll = (*original_mll) * ratio;
        //cout << "reweight_mll=" << reweight_mll << ", *original_mll=" << *original_mll << ", ratio=" << ratio << endl;
        h_reweight->Fill(reweight_mll);
    }

    if (is_reweight)
        return h_reweight;
    else
        return h_original;
}

double get_reweight_ratio_1(string n2_n1, int m12, double mll)
{
    double n2 = stod(n2_n1.substr(0, n2_n1.find("_"))); // stod() converts string to double
    double n1 = stod(n2_n1.substr(n2_n1.find("_") + 1, n2_n1.length()));
    double dm_higgsino = n2 - n1;

    double dm_nuhm2 = 0;
    if (m12 == 300)
        dm_nuhm2 = 55.;
    else if (m12 == 350)
        dm_nuhm2 = 46.;
    else if (m12 == 400)
        dm_nuhm2 = 38.;
    else if (m12 == 500)
        dm_nuhm2 = 28.;
    else if (m12 == 600)
        dm_nuhm2 = 22.;
    else if (m12 == 700)
        dm_nuhm2 = 18.;
    else if (m12 == 800)
        dm_nuhm2 = 15.;

    return dm_nuhm2 / dm_higgsino;
}

double get_reweight_ratio_2(string n2_n1, int m12, double mll)
{
    double x[1] = {mll};
    double par_higgsino[3] = {0};
    double par_nuhm2[3] = {0};

    if (n2_n1 == "140_100") {
        par_higgsino[0] = 2.10628E-07;
        par_higgsino[1] = 1.00083E+02;
        par_higgsino[2] = -1.39583E+02;
    }
    else if (n2_n1 == "160_100") {
        par_higgsino[0] = 3.97789E-08;
        par_higgsino[1] = 6.69586E+01;
        par_higgsino[2] = -1.26459E+02;
    }
    else if (n2_n1 == "170_150") {
        par_higgsino[0] = 3.40869E-07;
        par_higgsino[1] = 2.94691E+02;
        par_higgsino[2] = -3.15499E+02;
    }

    if (m12 == 300) {
        par_nuhm2[0] = 8.12264E-08;
        par_nuhm2[1] = 3.50058E+01;
        par_nuhm2[2] = -9.91722E+01;
    }
    
    else if (m12 == 350) {
        par_nuhm2[0] = 8.14450E-08;
        par_nuhm2[1] = 1.03884E+02;
        par_nuhm2[2] = -1.49384E+02;
    }
    else if (m12 == 400) {
        par_nuhm2[0] = 5.56669E-10;
        par_nuhm2[1] = 8.88082E+02;
        par_nuhm2[2] = -9.26435E+02;
    }
    else if (m12 == 500) {
        par_nuhm2[0] = 6.29717E-09;
        par_nuhm2[1] = 6.45114E+02;
        par_nuhm2[2] = -6.73877E+02;
    }
    else if (m12 == 600) {
        par_nuhm2[0] = 2.09419E-07;
        par_nuhm2[1] = 2.84535E+02;
        par_nuhm2[2] = -3.07564E+02;
    }
    else if (m12 == 700) {
        par_nuhm2[0] = 5.72898E-07;
        par_nuhm2[1] = 2.74570E+02;
        par_nuhm2[2] = -2.93799E+02;
    }
    else if (m12 == 800) {
        par_nuhm2[0] = 1.26533E-06;
        par_nuhm2[1] = 2.73757E+02;
        par_nuhm2[2] = -2.90133E+02;
    }

    double var_higgsino = FuncMllDistr(x, par_higgsino);
    double var_nuhm2 = FuncMllDistr(x, par_nuhm2);

    return var_nuhm2 / var_higgsino;
}