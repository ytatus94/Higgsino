#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TTree.h>
#include <TCanvas.h>

// #include "FuncMllDistr.C"
#include "FuncMllDistr_modified.C"

#include <string>
#include <iostream>
using namespace std;

void fit_plot(string, string);

void fit_common_ntuple()
{
    string path = "/Users/ytshen/Desktop/";
    string f_140_100 = "MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
    string f_160_100 = "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
    string f_170_150 = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
    string f_190_150 = "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";

    fit_plot(path + f_140_100, "140_100");
    fit_plot(path + f_160_100, "160_100");
    fit_plot(path + f_170_150, "170_150");
    fit_plot(path + f_190_150, "190_150");
}

void fit_plot(string input_file, string n2_n1)
{
    TFile *file = new TFile(input_file.c_str());

    string hist_name = "h_" + n2_n1;
    TH1F *hist = new TH1F(hist_name.c_str(), "", 100, 0, 100);

    string tree_name = "MGPy8EG_A14N23LO_SM_Higgsino_" + n2_n1 + "_2LMET50_MadSpin_NoSys";
    TTree *tree = (TTree *)file->Get(tree_name.c_str());
    tree->Project(hist_name.c_str(), "truthMll", "truthMll>0");

    double n2 = stod(n2_n1.substr(0, n2_n1.find("_"))); // stod() converts string to double
    double n1 = stod(n2_n1.substr(n2_n1.find("_") + 1, n2_n1.length()));
    double dm = n2 - n1;

    // We don't fit. Simply use n1 and n2 to calculate the function values.
    // So we can have the shape of the function.
    // But we have to normalize the function before calculating function values.
    TF1 *fit_func = new TF1("fit_func", FuncMllDistr, 0, dm, 3);
    fit_func->SetParameters(1., n1, -1 * n2);
    double area_fit_func = fit_func->Integral(0, dm);
    fit_func->SetParameter(0, 1./area_fit_func);
    fit_func->FixParameter(1, n1);
    fit_func->FixParameter(2, -1 * n2);
    fit_func->SetLineColor(kRed);
    fit_func->SetLineStyle(2);

    // In order to get the same area between function and histogram, we do fit at here to get the normalization coefficient.
    hist->Fit(fit_func, "R+");

    TCanvas *c = new TCanvas("c", "", 800, 600);
    c->SetLeftMargin(0.12);
    bool logY = false;

    if (logY)
        gPad->SetLogy();

    hist->SetXTitle("m_{ll} [GeV]");
    hist->SetYTitle("Events / 1GeV");
    hist->GetYaxis()->SetTitleOffset(1.2);
    hist->SetLineColor(kBlue);
    hist->Draw("hist");

    fit_func->Draw("same");

    gStyle->SetOptFit(1111);

    TLegend *legend = new TLegend(0.3, 0.3, 0.9, 0.4);
    legend->AddEntry(hist, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(fit_func, ("Calculated Higgsino_" + n2_n1 + "(fix N2 and N1)").c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "fit_Higgsino_" + n2_n1 + ".pdf";
    c->SaveAs(output.c_str());
}

void fit_plot_v1(string input_file, string n2_n1)
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

    hist->SetXTitle("m_{ll} [GeV]");
    hist->SetYTitle("Events / 1GeV");
    hist->GetYaxis()->SetTitleOffset(1.2);
    hist->Draw();

    double n2 = stod(n2_n1.substr(0, n2_n1.find("_"))); // stod() converts string to double
    double n1 = stod(n2_n1.substr(n2_n1.find("_") + 1, n2_n1.length()));
    double dm = n2 - n1;

    TF1 *fit_func = new TF1("fit_func", FuncMllDistr, 0, dm, 3);
    fit_func->SetParameters(1., n1, -1 * n2);

    hist->Fit(fit_func, "R0");
    hist->Fit(fit_func, "R0");
    hist->Fit(fit_func, "R+");

    gStyle->SetOptFit(1111);

    string output = "fit_Higgsino_" + n2_n1 + ".pdf";
    c->SaveAs(output.c_str());
}

void fit_common_ntuple_v1()
{
    TFile *file1 = new TFile("/Users/ytshen/Desktop/MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root");
    TH1F *h1 = new TH1F("h1", "", 100, 0, 100);
    TTree *t1 = (TTree *)file1->Get("MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_NoSys");
    t1->Project("h1","truthMll","truthMll>0");
    TCanvas *c1 = new TCanvas("c1", "", 800, 600);
    h1->SetXTitle("m_{ll} [GeV]");
    h1->SetYTitle("Events/1GeV");
    h1->Draw();
    TF1 *f1 = new TF1("f1", FuncMllDistr, 0, 40, 3);
    f1->SetParameters(1.,100,-140);
    h1->Fit(f1);
    h1->Fit(f1);
    h1->Fit(f1);
    c1->SaveAs("fit_Higgsino_140_100.pdf");

    TFile *file2 = new TFile("/Users/ytshen/Desktop/MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root");
    TH1F *h2 = new TH1F("h2", "", 100, 0, 100);
    TTree *t2 = (TTree *)file2->Get("MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_NoSys");
    t2->Project("h2","truthMll","truthMll>0");
    TCanvas *c2 = new TCanvas("c2", "", 800, 600);
    h2->SetXTitle("m_{ll} [GeV]");
    h2->SetYTitle("Events/1GeV");
    h2->Draw();
    TF1 *f2 = new TF1("f2", FuncMllDistr, 0, 60, 3);
    f2->SetParameters(1.,100,-160);
    h2->Fit(f2);
    h2->Fit(f2);
    h2->Fit(f2);
    c2->SaveAs("fit_Higgsino_160_100.pdf");

    TFile *file3 = new TFile("/Users/ytshen/Desktop/MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root");
    TH1F *h3 = new TH1F("h3", "", 100, 0, 100);
    TTree *t3 = (TTree *)file3->Get("MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_NoSys");
    t3->Project("h3","truthMll","truthMll>0");
    TCanvas *c3 = new TCanvas("c3", "", 800, 600);
    h3->SetXTitle("m_{ll} [GeV]");
    h3->SetYTitle("Events/1GeV");
    h3->Draw();
    TF1 *f3 = new TF1("f3", FuncMllDistr, 0, 20, 3);
    f3->SetParameters(1.,150,-170);
    h3->Fit(f3);
    h3->Fit(f3);
    h3->Fit(f3);
    c3->SaveAs("fit_Higgsino_170_150.pdf");
}
