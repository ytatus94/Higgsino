#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TTree.h>
#include <TCanvas.h>

#include "FuncMllDistr_modified.C"
#include "ytUtility.C"

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

void fit_and_reweight_plot(string, string, int);

void reweight_common_ntuple()
{
    string path = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/";
    // string f_140_100 = "MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
    string f_160_100 = "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root";
    string f_170_150 = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root";
    string f_190_150 = "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8e_SUSY16_tree_NoSys.root";

    fit_and_reweight_plot(path + f_160_100, "160_100", 350);
    fit_and_reweight_plot(path + f_160_100, "160_100", 400);
    // fit_and_reweight_plot(path + f_160_100, "160_100");
    fit_and_reweight_plot(path + f_190_150, "190_150", 500);
    fit_and_reweight_plot(path + f_190_150, "190_150", 600);
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
    double dm_Higgsino = n2 - n1;

    double n1_NUHM2 = get_NUHM2_N1_mass(m12);
    double n2_NUHM2 = get_NUHM2_N2_mass(m12);
    double dm_NUHM2 = get_dm_NUHM2(m12);

    // Theoretical
    TF1 *func_Higgsino = new TF1("func_Higgsino", FuncMllDistr, 0, dm_Higgsino, 3);
    func_Higgsino->SetParameters(1., n1, -1 * n2);
    double area_func_Higgsino = func_Higgsino->Integral(0, dm_Higgsino);
    func_Higgsino->SetParameter(0, 1./area_func_Higgsino);
    func_Higgsino->FixParameter(1, n1);
    func_Higgsino->FixParameter(2, -1 * n2);

    TF1 *func_NUHM2 = new TF1("func_NUHM2", FuncMllDistr, 0, dm_NUHM2, 3);
    func_NUHM2->SetParameters(1., n1_NUHM2, -1 * n2_NUHM2);
    double area_func_NUHM2 = func_NUHM2->Integral(0, dm_NUHM2);
    func_NUHM2->SetParameter(0, 1./area_func_NUHM2);
    func_NUHM2->FixParameter(1, n1_NUHM2);
    func_NUHM2->FixParameter(2, -1 * n2_NUHM2);

    gStyle->SetOptFit(1111);

    // Reweight
    TH1F *h_reweight = new TH1F("h_reweight", "", 100, 0, 100);

    TTreeReader myReader(tree_name.c_str(), file);
    TTreeReaderValue<double> original_mll(myReader, "truthMll");

    while (myReader.Next()) {
        double truthMll = *original_mll;
        double weight = func_NUHM2->Eval(truthMll) / func_Higgsino->Eval(truthMll);
        h_reweight->Fill(truthMll, weight);
    }

    double x_max = 0;
    if (m12 <= 400)
        x_max = 100.;
    else if (m12 > 400)
        x_max = 50.;

    double y_max = max(hist->GetMaximum(), h_reweight->GetMaximum()) * 1.2;

    hist->SetXTitle("m_{ll} [GeV]");
    hist->SetYTitle("Events / 1GeV");
    hist->GetXaxis()->SetRangeUser(0, x_max);
    hist->GetYaxis()->SetTitleOffset(1.2);
    hist->SetMaximum(y_max);
    hist->SetLineColor(kGreen);
    hist->Draw();

    hist->Fit(func_Higgsino, "R0");
    hist->Fit(func_Higgsino, "R0");
    hist->Fit(func_Higgsino, "R0+");

    func_Higgsino->SetLineColor(kGreen);
    func_Higgsino->SetLineStyle(2);
    func_Higgsino->Draw("same");

    h_reweight->SetLineColor(kRed);
    h_reweight->Draw("hist,same");

    TLegend *legend = new TLegend(0.4, 0.2, 0.8, 0.4);
    legend->AddEntry(hist, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(func_Higgsino, ("Theoretical Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_reweight, ("reweight Higgsino to NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "fit_and_reweight_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());
}
