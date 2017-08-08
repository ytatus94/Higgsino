#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TTree.h>
#include <TCanvas.h>

#include "FuncMllDistr.C"

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

void fit_and_reweight_plot(string, string, int);
double get_reweight_ratio_1(string, int, double);

void reweight_common_ntuple()
{
    string path = "/Users/ytshen/Desktop/";
    string f_140_100 = "MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
    string f_160_100 = "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
    string f_170_150 = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";

    fit_and_reweight_plot(path + f_140_100, "140_100", 350);
    fit_and_reweight_plot(path + f_140_100, "140_100", 400);
    // fit_and_reweight_plot(path + f_160_100, "160_100");
    fit_and_reweight_plot(path + f_170_150, "170_150", 500);
    fit_and_reweight_plot(path + f_170_150, "170_150", 600);
    fit_and_reweight_plot(path + f_170_150, "170_150", 700);
    fit_and_reweight_plot(path + f_170_150, "170_150", 800);
}

void fit_and_reweight_plot(string input_file, string n2_n1, int m12)
{
    TFile *file = new TFile(input_file.c_str());

    string hist_name = "h_" + n2_n1;
    TH1F *hist = new TH1F(hist_name.c_str(), "", 100, 0, 100);

    string tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 + "_2LMET50_MadSpin_NoSys";
    TTree *tree = (TTree *)file->Get(tree_name.c_str());
    tree->Project(hist_name.c_str(), "truthMll", "truthMll>0");

    TCanvas *c = new TCanvas("c", "", 800, 600);
    c->SetLeftMargin(0.12);
    bool logY = false;

    if (logY)
        gPad->SetLogy();

    double n2 = stod(n2_n1.substr(0, n2_n1.find("_"))); // stod() converts string to double
    double n1 = stod(n2_n1.substr(n2_n1.find("_") + 1, n2_n1.length()));
    double dm = n2 - n1;

    // Fitting
    TF1 *fit_func = new TF1("fit_func", FuncMllDistr, 0, dm, 3);
    fit_func->SetParameters(1., n1, -1 * n2);

    hist->Fit(fit_func, "R0");
    hist->Fit(fit_func, "R0");
    hist->Fit(fit_func, "R0+");

    

    gStyle->SetOptFit(1111);

    // Reweight
    TH1F *h_reweight = new TH1F("h_reweight", "", 100, 0, 100);

    TTreeReader myReader(tree_name.c_str(), file);
    TTreeReaderValue<double> original_mll(myReader, "truthMll");

    while (myReader.Next()) {
        double ratio = get_reweight_ratio_1(n2_n1, m12, *original_mll);
        double reweight_mll = (*original_mll) * ratio;
        h_reweight->Fill(reweight_mll);
    }

    double x_max = 0;
    if (m12 < 400)
        x_max = 100.;
    else if (m12 >= 400)
        x_max = 50.;

    double y_max = max(hist->GetMaximum(), h_reweight->GetMaximum()) * 1.2;

    hist->SetXTitle("m_{ll} [GeV]");
    hist->SetYTitle("Events / 1GeV");
    hist->GetXaxis()->SetRangeUser(0, x_max);
    hist->GetYaxis()->SetTitleOffset(1.2);
    hist->SetMaximum(y_max);
    hist->SetLineColor(kGreen);
    hist->Draw();

    fit_func->SetLineColor(kGreen);
    fit_func->SetLineStyle(2);
    fit_func->Draw("same");

    h_reweight->SetLineColor(kRed);
    h_reweight->Draw("same");

    TLegend *legend = new TLegend(0.4, 0.2, 0.8, 0.4);
    legend->AddEntry(hist, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_reweight, ("reweight Higgsino to NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->AddEntry(fit_func, ("fit Higgsino_" + n2_n1).c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "fit_and_reweight_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());
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
