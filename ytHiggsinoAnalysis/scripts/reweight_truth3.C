#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TLegend.h>

// #include "FuncMllDistr.C"
#include "FuncMllDistr_modified.C"
#include "get_combined_hist.C"
#include "ytUtility.C"

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

// Declare functions
void get_func_ratio_parameters(int, double *);
void plot_Lorenzo(int, int, int);
void plot_Mike(int, int, int);
void tree_reader(string, double, TH1F *, TH1F *h2 = NULL, TF1 *func1 = NULL, TF1 *func2 = NULL);

// main function
void reweight_truth3()
{
    // Use Lorenzo's way
    plot_Lorenzo(100, 160, 350);
    plot_Lorenzo(100, 160, 400);
    plot_Lorenzo(150, 190, 500);
    plot_Lorenzo(150, 190, 600);
    plot_Lorenzo(150, 170, 700);
    plot_Lorenzo(150, 170, 800);

    // Use Mike's way
    // plot_Mike(100, 160, 350);
    // plot_Mike(100, 160, 400);
    // plot_Mike(150, 190, 500);
    // plot_Mike(150, 190, 600);
    // plot_Mike(150, 170, 700);
    // plot_Mike(150, 170, 800);
}

void get_func_ratio_parameters(int m12, double *par)
{
    if (m12 == 300) {
        par[0] = 0.;
        par[1] = 0.;
        par[2] = 0.;
    }
    else if (m12 == 350) {
        par[0] = 1.36291;
        par[1] = 0.0256363;
        par[2] = -0.00112278;
    }
    else if (m12 == 400) {
        par[0] = 2.02296;
        par[1] = 0.0183473;
        par[2] = -0.00178666;
    }
    else if (m12 == 500) {
        par[0] = 1.77105;
        par[1] = 0.01694;
        par[2] = -0.00259439;
    }
    else if (m12 == 600) {
        par[0] = 2.88514;
        par[1] = -0.0124539;
        par[2] = -0.00499686;
    }
    else if (m12 == 700) {
        par[0] = 1.21747;
        par[1] = 0.004116;
        par[2] = -0.00197311;

    }
    else if (m12 == 800) {
        par[0] = 1.59017;
        par[1] = 0.0318019;
        par[2] = -0.00740787;
    }
}

void plot_Lorenzo(int n1, int n2, int m12)
{
    double dm_Higgsino = n2 - n1;
    double dm_NUHM2 = get_dm_NUHM2(m12);
    double par1 = get_NUHM2_N1_mass(m12);
    double par2 = get_NUHM2_N2_mass(m12);

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
    func_NUHM2->SetParameter(1, par1);
    func_NUHM2->SetParameter(2, -1*par2);
    func_NUHM2->FixParameter(1, par1);
    func_NUHM2->FixParameter(2, -1*par2);
    func_NUHM2->SetLineColor(kRed);
    func_NUHM2->SetLineStyle(2);

    //normalize the two curve to the same area (=1)
    double integral_func_Higgsino = func_Higgsino->Integral(0, dm_Higgsino);
    double integral_func_NUHM2 = func_NUHM2->Integral(0, dm_NUHM2);
    func_Higgsino->SetParameter(0, 1./integral_func_Higgsino);
    func_NUHM2->SetParameter(0, 1./integral_func_NUHM2);

    //Get the higgsino truth3 MC sample
    string path_Higgsino = "/Users/ytshen/Desktop/20170810/";
    string n2_n1 = to_string(n2) + "_" + to_string(n1);

    string file_Higgsino_N2N1  = path_Higgsino + "user.yushen.SM_N2N1_"  + n2_n1 + "_2LMET50.root";
    // string file_Higgsino_C1C1  = path_Higgsino + "user.yushen.SM_C1C1_"  + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1p = path_Higgsino + "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1m = path_Higgsino + "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    TH1F *h_Higgsino_N2N1_original = new TH1F("h_Higgsino_N2N1_original", "", 200, 0, 200);
    // TH1F *h_Higgsino_C1C1_original = new TH1F("h_Higgsino_C1C1_original", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1p_original = new TH1F("h_Higgsino_N2C1p_original", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1m_original = new TH1F("h_Higgsino_N2C1m_original", "", 200, 0, 200);

    TH1F *h_Higgsino_N2N1_reweight = new TH1F("h_Higgsino_N2N1_reweight", "", 200, 0, 200);
    // TH1F *h_Higgsino_C1C1_reweight = new TH1F("h_Higgsino_C1C1_reweight", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1p_reweight = new TH1F("h_Higgsino_N2C1p_reweight", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1m_reweight = new TH1F("h_Higgsino_N2C1m_reweight", "", 200, 0, 200);

    tree_reader(file_Higgsino_N2N1, dm_Higgsino, h_Higgsino_N2N1_original, h_Higgsino_N2N1_reweight, func_Higgsino, func_NUHM2);
    // tree_reader(file_Higgsino_C1C1, dm_Higgsino, h_Higgsino_C1C1_original, h_Higgsino_C1C1_reweight, func_Higgsino, func_NUHM2);
    tree_reader(file_Higgsino_N2C1p, dm_Higgsino, h_Higgsino_N2C1p_original, h_Higgsino_N2C1p_reweight, func_Higgsino, func_NUHM2);
    tree_reader(file_Higgsino_N2C1m, dm_Higgsino, h_Higgsino_N2C1m_original, h_Higgsino_N2C1m_reweight, func_Higgsino, func_NUHM2);

    // h_Higgsino_N2N1_original->SetLineColor(1);
    // h_Higgsino_C1C1_original->SetLineColor(2);
    // h_Higgsino_N2C1p_original->SetLineColor(3);
    // h_Higgsino_N2C1m_original->SetLineColor(4);

    // h_Higgsino_N2N1_original->Draw("hist");
    // h_Higgsino_C1C1_original->Draw("hist,same");
    // h_Higgsino_N2C1p_original->Draw("hist,same");
    // h_Higgsino_N2C1m_original->Draw("hist,same");

    // h_Higgsino_N2N1_reweight->SetLineColor(1);
    // h_Higgsino_C1C1_reweight->SetLineColor(2);
    // h_Higgsino_N2C1p_reweight->SetLineColor(3);
    // h_Higgsino_N2C1m_reweight->SetLineColor(4);

    // h_Higgsino_N2N1_reweight->Draw("hist");
    // h_Higgsino_C1C1_reweight->Draw("hist,same");
    // h_Higgsino_N2C1p_reweight->Draw("hist,same");
    // h_Higgsino_N2C1m_reweight->Draw("hist,same");

    // Combine N2N1, C1C1, N2C1p, N2C1m
    // Original
    TH1F *h_Higgsino_combined_original = combine_histogram(h_Higgsino_N2N1_original, h_Higgsino_N2C1p_original, h_Higgsino_N2C1m_original);
    h_Higgsino_combined_original->SetName("h_Higgsino_combined_original");
    h_Higgsino_combined_original->SetTitle("");
    h_Higgsino_combined_original->SetXTitle("m_{ll} [GeV]");
    h_Higgsino_combined_original->SetYTitle("Normalized event counts");
    h_Higgsino_combined_original->SetLineColor(kGreen);

    // Reweight
    TH1F *h_Higgsino_combined_reweight = combine_histogram(h_Higgsino_N2N1_reweight, h_Higgsino_N2C1p_reweight, h_Higgsino_N2C1m_reweight);
    h_Higgsino_combined_reweight->SetName("h_Higgsino_combined_reweight");
    h_Higgsino_combined_reweight->SetTitle("");
    h_Higgsino_combined_reweight->SetXTitle("m_{ll} [GeV]");
    h_Higgsino_combined_reweight->SetYTitle("Normalized event counts");
    h_Higgsino_combined_reweight->SetLineColor(kRed);

    // double area_Higgsino_combined_original = h_Higgsino_combined_original->Integral(0, dm_Higgsino);
    // double area_Higgsino_combined_reweight = h_Higgsino_combined_reweight->Integral(0, dm_NUHM2);
    // cout << "area_Higgsino_combined_original=" << area_Higgsino_combined_original << endl;
    // cout << "area_Higgsino_combined_reweight=" << area_Higgsino_combined_reweight << endl;

    // func_Higgsino->SetParameter(0, area_Higgsino_combined_original);
    // func_NUHM2->SetParameter(0, area_Higgsino_combined_reweight);
    // cout << "func_Higgsino->Integral(0, dm_Higgsino)=" << func_Higgsino->Integral(0, dm_Higgsino) << endl;
    // cout << "func_NUHM2->Integral(0, dm_NUHM2)=" << func_NUHM2->Integral(0, dm_NUHM2) << endl;

    h_Higgsino_combined_original->Fit(func_Higgsino, "R0+");
    h_Higgsino_combined_reweight->Fit(func_NUHM2, "R0+");
    // cout << "func_Higgsino->Integral(0, dm_Higgsino)=" << func_Higgsino->Integral(0, dm_Higgsino) << endl;
    // cout << "func_NUHM2->Integral(0, dm_NUHM2)=" << func_NUHM2->Integral(0, dm_NUHM2) << endl;

    // Get the NUHM2 truth3 MC sample
    string path_NUHM2 = "/Users/ytshen/Desktop/20170730/";

    string f_NUHM2_N2N1 = "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    // string f_NUHM2_C1C1 = "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string f_NUHM2_N2C1p = "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string f_NUHM2_N2C1m = "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    string file_NUHM2_N2N1  = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    // string file_NUHM2_C1C1  = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string file_NUHM2_N2C1p = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string file_NUHM2_N2C1m = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    TH1F *h_NUHM2_N2N1 = new TH1F("h_NUHM2_N2N1", "", 200, 0, 200);
    // TH1F *h_NUHM2_C1C1 = new TH1F("h_NUHM2_C1C1", "", 200, 0, 200);
    TH1F *h_NUHM2_N2C1p = new TH1F("h_NUHM2_N2C1p", "", 200, 0, 200);
    TH1F *h_NUHM2_N2C1m = new TH1F("h_NUHM2_N2C1m", "", 200, 0, 200);

    tree_reader(file_NUHM2_N2N1, dm_NUHM2, h_NUHM2_N2N1);
    // tree_reader(file_NUHM2_C1C1, dm_NUHM2, h_NUHM2_C1C1);
    tree_reader(file_NUHM2_N2C1p, dm_NUHM2, h_NUHM2_N2C1p);
    tree_reader(file_NUHM2_N2C1m, dm_NUHM2, h_NUHM2_N2C1m);

    // h_NUHM2_N2N1->SetLineColor(1);
    // h_NUHM2_C1C1->SetLineColor(2);
    // h_NUHM2_N2C1p->SetLineColor(3);
    // h_NUHM2_N2C1m->SetLineColor(4);

    // h_NUHM2_N2N1->Draw("hist");
    // h_NUHM2_C1C1->Draw("hist,same");
    // h_NUHM2_N2C1p->Draw("hist,same");
    // h_NUHM2_N2C1m->Draw("hist,same");

    TH1F *h_NUHM2_Combined = combine_histogram(h_NUHM2_N2N1, h_NUHM2_N2C1p, h_NUHM2_N2C1m);
    h_NUHM2_Combined->SetName("h_NUHM2_Combined");
    h_NUHM2_Combined->SetTitle("");
    h_NUHM2_Combined->SetXTitle("m_{ll} [GeV]");
    h_NUHM2_Combined->SetYTitle("Normalized event counts");
    h_NUHM2_Combined->SetLineColor(kBlue);

    // Making plot
    TCanvas *c = new TCanvas("c", "", 800, 600);
    c->SetLeftMargin(0.12);
    bool logY = false;

    if (logY)
        gPad->SetLogy();

    double x_max = 0;
    if (m12 <= 400)
        x_max = 100.;
    else if (m12 > 400)
        x_max = 50.;

    double y_max = max(h_Higgsino_combined_original->GetMaximum(), h_Higgsino_combined_reweight->GetMaximum()) * 1.2;

    h_Higgsino_combined_original->GetXaxis()->SetRangeUser(0, x_max);
    h_Higgsino_combined_original->GetYaxis()->SetTitleOffset(1.4);
    h_Higgsino_combined_original->SetMaximum(y_max);
    h_Higgsino_combined_original->SetStats(0);
    h_Higgsino_combined_original->Draw("hist");

    h_Higgsino_combined_reweight->Draw("hist,same");

    func_Higgsino->Draw("same");
    func_NUHM2->Draw("same");

    h_NUHM2_Combined->Draw("hist,same");

    TLegend *legend = new TLegend(0.4, 0.6, 0.9, 0.8);
    legend->AddEntry(h_Higgsino_combined_original, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(func_Higgsino, ("Calculated Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_Higgsino_combined_reweight, ("reweight Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(func_NUHM2, ("Calculated reweighted Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_NUHM2_Combined, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "reweight_Lorenzo_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());
}

void plot_Mike(int n1, int n2, int m12)
{
    double dm_Higgsino = n2 - n1;
    double dm_NUHM2 = get_dm_NUHM2(m12);
    // double par[3] = {0., 0., 0.};
    // get_func_ratio_parameters(m12, par);

    //Get the higgsino truth3 MC sample
    string path_Higgsino = "/Users/ytshen/Desktop/20170810/";
    string n2_n1 = to_string(n2) + "_" + to_string(n1);

    string f_Higgsino_N2N1 = "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_C1C1 = "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1p = "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1m = "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    TFile *file_Higgsino_N2N1 = new TFile( (path_Higgsino + f_Higgsino_N2N1).c_str() );
    TFile *file_Higgsino_C1C1 = new TFile( (path_Higgsino + f_Higgsino_C1C1).c_str() );
    TFile *file_Higgsino_N2C1p = new TFile( (path_Higgsino + f_Higgsino_N2C1p).c_str() );
    TFile *file_Higgsino_N2C1m = new TFile( (path_Higgsino + f_Higgsino_N2C1m).c_str() );

    TTreeReader Reader_Higgsino_N2N1("EwkHiggsino2016__ntuple", file_Higgsino_N2N1);
    TTreeReader Reader_Higgsino_C1C1("EwkHiggsino2016__ntuple", file_Higgsino_C1C1);
    TTreeReader Reader_Higgsino_N2C1p("EwkHiggsino2016__ntuple", file_Higgsino_N2C1p);
    TTreeReader Reader_Higgsino_N2C1m("EwkHiggsino2016__ntuple", file_Higgsino_N2C1m);

    TTreeReaderValue<float> truth_mll_Higgsino_N2N1(Reader_Higgsino_N2N1, "mll");
    TTreeReaderValue<float> truth_mll_Higgsino_C1C1(Reader_Higgsino_C1C1, "mll");
    TTreeReaderValue<float> truth_mll_Higgsino_N2C1p(Reader_Higgsino_N2C1p, "mll");
    TTreeReaderValue<float> truth_mll_Higgsino_N2C1m(Reader_Higgsino_N2C1m, "mll");

    TH1F *h_Higgsino_N2N1_original = new TH1F("h_Higgsino_N2N1_original", "", 200, 0, 200);
    TH1F *h_Higgsino_C1C1_original = new TH1F("h_Higgsino_C1C1_original", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1p_original = new TH1F("h_Higgsino_N2C1p_original", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1m_original = new TH1F("h_Higgsino_N2C1m_original", "", 200, 0, 200);

    while (Reader_Higgsino_N2N1.Next()) {
        double truthMll = *truth_mll_Higgsino_N2N1;
        if (truthMll < dm_Higgsino) {
            h_Higgsino_N2N1_original->Fill(truthMll);
            // double weight = 0.;
            // if (truthMll < dm_NUHM2)
            //     weight = func_ratio->Eval(truthMll);
            // h_Higgsino_N2N1_reweight->Fill(truthMll, weight);
        }
    }
    while (Reader_Higgsino_C1C1.Next()) {
        double truthMll = *truth_mll_Higgsino_C1C1;
        if (truthMll < dm_Higgsino) {
            h_Higgsino_C1C1_original->Fill(truthMll);
            // double weight = 0.;
            // if (truthMll < dm_NUHM2)
            //     weight = func_ratio->Eval(truthMll);
            // h_Higgsino_C1C1_reweight->Fill(truthMll, weight);
        }
    }
    while (Reader_Higgsino_N2C1p.Next()) {
        double truthMll = *truth_mll_Higgsino_N2C1p;
        if (truthMll < dm_Higgsino) {
            h_Higgsino_N2C1p_original->Fill(truthMll);
            // double weight = 0.;
            // if (truthMll < dm_NUHM2)
            //     weight = func_ratio->Eval(truthMll);
            // h_Higgsino_N2C1p_reweight->Fill(truthMll, weight);
        }
    }
    while (Reader_Higgsino_N2C1m.Next()) {
        double truthMll = *truth_mll_Higgsino_N2C1m;
        if (truthMll < dm_Higgsino) {
            h_Higgsino_N2C1m_original->Fill(truthMll);
            // double weight = 0.;
            // if (truthMll < dm_NUHM2)
            //     weight = func_ratio->Eval(truthMll);
            // h_Higgsino_N2C1m_reweight->Fill(truthMll, weight);
        }
    }

    // h_Higgsino_N2N1_original->SetLineColor(1);
    // h_Higgsino_C1C1_original->SetLineColor(2);
    // h_Higgsino_N2C1p_original->SetLineColor(3);
    // h_Higgsino_N2C1m_original->SetLineColor(4);

    // h_Higgsino_N2N1_original->Draw("hist");
    // h_Higgsino_C1C1_original->Draw("hist,same");
    // h_Higgsino_N2C1p_original->Draw("hist,same");
    // h_Higgsino_N2C1m_original->Draw("hist,same");

    double area_Higgsino_N2N1_original = h_Higgsino_N2N1_original->Integral();
    double area_Higgsino_C1C1_original = h_Higgsino_C1C1_original->Integral();
    double area_Higgsino_N2C1p_original = h_Higgsino_N2C1p_original->Integral();
    double area_Higgsino_N2C1m_original = h_Higgsino_N2C1m_original->Integral();
    double sum_Higgsino_original = area_Higgsino_N2N1_original + area_Higgsino_C1C1_original + area_Higgsino_N2C1p_original + area_Higgsino_N2C1m_original;
    // double sum_Higgsino_original = area_Higgsino_N2N1_original + area_Higgsino_N2C1p_original + area_Higgsino_N2C1m_original;

    h_Higgsino_N2N1_original->Scale(1./area_Higgsino_N2N1_original); // normalize to 1.
    h_Higgsino_C1C1_original->Scale(1./area_Higgsino_C1C1_original);
    h_Higgsino_N2C1p_original->Scale(1./area_Higgsino_N2C1p_original);
    h_Higgsino_N2C1m_original->Scale(1./area_Higgsino_N2C1m_original);

    // Get the NUHM2 truth3 MC sample
    string path_NUHM2 = "/Users/ytshen/Desktop/20170730/";

    string f_NUHM2_N2N1 = "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    string f_NUHM2_C1C1 = "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string f_NUHM2_N2C1p = "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string f_NUHM2_N2C1m = "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    TFile *file_NUHM2_N2N1 = new TFile( (path_NUHM2 + f_NUHM2_N2N1).c_str() );
    TFile *file_NUHM2_C1C1 = new TFile( (path_NUHM2 + f_NUHM2_C1C1).c_str() );
    TFile *file_NUHM2_N2C1p = new TFile( (path_NUHM2 + f_NUHM2_N2C1p).c_str() );
    TFile *file_NUHM2_N2C1m = new TFile( (path_NUHM2 + f_NUHM2_N2C1m).c_str()) ;

    TTreeReader Reader_NUHM2_N2N1("EwkHiggsino2016__ntuple", file_NUHM2_N2N1);
    TTreeReader Reader_NUHM2_C1C1("EwkHiggsino2016__ntuple", file_NUHM2_C1C1);
    TTreeReader Reader_NUHM2_N2C1p("EwkHiggsino2016__ntuple", file_NUHM2_N2C1p);
    TTreeReader Reader_NUHM2_N2C1m("EwkHiggsino2016__ntuple", file_NUHM2_N2C1m);

    TTreeReaderValue<float> truth_mll_NUHM2_N2N1(Reader_NUHM2_N2N1, "mll");
    TTreeReaderValue<float> truth_mll_NUHM2_C1C1(Reader_NUHM2_C1C1, "mll");
    TTreeReaderValue<float> truth_mll_NUHM2_N2C1p(Reader_NUHM2_N2C1p, "mll");
    TTreeReaderValue<float> truth_mll_NUHM2_N2C1m(Reader_NUHM2_N2C1m, "mll");

    TH1F *h_NUHM2_N2N1 = new TH1F("h_NUHM2_N2N1", "", 200, 0, 200);
    TH1F *h_NUHM2_C1C1 = new TH1F("h_NUHM2_C1C1", "", 200, 0, 200);
    TH1F *h_NUHM2_N2C1p = new TH1F("h_NUHM2_N2C1p", "", 200, 0, 200);
    TH1F *h_NUHM2_N2C1m = new TH1F("h_NUHM2_N2C1m", "", 200, 0, 200);

    while (Reader_NUHM2_N2N1.Next()) {
        double truthMll = *truth_mll_NUHM2_N2N1;
        if (truthMll < dm_NUHM2)
            h_NUHM2_N2N1->Fill(truthMll);
    }
    while (Reader_NUHM2_C1C1.Next()) {
        double truthMll = *truth_mll_NUHM2_C1C1;
        if (truthMll < dm_NUHM2)
            h_NUHM2_C1C1->Fill(truthMll);
    }
    while (Reader_NUHM2_N2C1p.Next()) {
        double truthMll = *truth_mll_NUHM2_N2C1p;
        if (truthMll < dm_NUHM2)
            h_NUHM2_N2C1p->Fill(truthMll);
    }
    while (Reader_NUHM2_N2C1m.Next()) {
        double truthMll = *truth_mll_NUHM2_N2C1m;
        if (truthMll < dm_NUHM2)
            h_NUHM2_N2C1m->Fill(truthMll);
    }

    // h_NUHM2_N2N1->SetLineColor(1);
    // h_NUHM2_C1C1->SetLineColor(2);
    // h_NUHM2_N2C1p->SetLineColor(3);
    // h_NUHM2_N2C1m->SetLineColor(4);

    // h_NUHM2_N2N1->Draw("hist");
    // h_NUHM2_C1C1->Draw("hist,same");
    // h_NUHM2_N2C1p->Draw("hist,same");
    // h_NUHM2_N2C1m->Draw("hist,same");

    double integral_NUHM2_N2N1  = h_NUHM2_N2N1->Integral();
    double integral_NUHM2_C1C1  = h_NUHM2_C1C1->Integral();
    double integral_NUHM2_N2C1p  = h_NUHM2_N2C1p->Integral();
    double integral_NUHM2_N2C1m  = h_NUHM2_N2C1m->Integral();
    double sum_NUHM2 = integral_NUHM2_N2N1 + integral_NUHM2_C1C1 + integral_NUHM2_N2C1p + integral_NUHM2_N2C1m;
    // double sum_NUHM2 = integral_NUHM2_N2N1 + integral_NUHM2_N2C1p + integral_NUHM2_N2C1m;

    h_NUHM2_N2N1->Scale(1./integral_NUHM2_N2N1);
    h_NUHM2_C1C1->Scale(1./integral_NUHM2_C1C1);
    h_NUHM2_N2C1p->Scale(1./integral_NUHM2_N2C1p);
    h_NUHM2_N2C1m->Scale(1./integral_NUHM2_N2C1m);

    // Ratio histograms
    TH1F *h_ratio_N2N1 = (TH1F *)h_NUHM2_N2N1->Clone();
    TH1F *h_ratio_C1C1 = (TH1F *)h_NUHM2_C1C1->Clone();
    TH1F *h_ratio_N2C1p = (TH1F *)h_NUHM2_N2C1p->Clone();
    TH1F *h_ratio_N2C1m = (TH1F *)h_NUHM2_N2C1m->Clone();

    h_ratio_N2N1->SetName("h_ratio_N2N1");
    h_ratio_C1C1->SetName("h_ratio_C1C1");
    h_ratio_N2C1p->SetName("h_ratio_N2C1p");
    h_ratio_N2C1m->SetName("h_ratio_N2C1m");

    h_ratio_N2N1->Divide(h_Higgsino_N2N1_original);
    h_ratio_C1C1->Divide(h_Higgsino_C1C1_original);
    h_ratio_N2C1p->Divide(h_Higgsino_N2C1p_original);
    h_ratio_N2C1m->Divide(h_Higgsino_N2C1m_original);

    // Fit ratio curve (NUHM2 / Higgsino)
    TF1 *func_ratio_N2N1 = new TF1("func_ratio_N2N1", "pol2", 0, dm_NUHM2);
    TF1 *func_ratio_C1C1 = new TF1("func_ratio_C1C1", "pol2", 0, dm_NUHM2);
    TF1 *func_ratio_N2C1p = new TF1("func_ratio_N2C1p", "pol2", 0, dm_NUHM2);
    TF1 *func_ratio_N2C1m = new TF1("func_ratio_N2C1m", "pol2", 0, dm_NUHM2);

    func_ratio_N2N1->SetParameters(1., 1., 1.);
    func_ratio_C1C1->SetParameters(1., 1., 1.);
    func_ratio_N2C1p->SetParameters(1., 1., 1.);
    func_ratio_N2C1m->SetParameters(1., 1., 1.);

    // TCanvas *c_test = new TCanvas("c_test", "", 800, 800);
    // c_test->Divide(2,2);

    // c_test->cd(1);
    h_ratio_N2N1->Fit(func_ratio_N2N1, "R0");
    h_ratio_N2N1->Fit(func_ratio_N2N1, "R0");
    h_ratio_N2N1->Fit(func_ratio_N2N1, "R+");

    // c_test->cd(2);
    h_ratio_C1C1->Fit(func_ratio_C1C1, "R0");
    h_ratio_C1C1->Fit(func_ratio_C1C1, "R0");
    h_ratio_C1C1->Fit(func_ratio_C1C1, "R+");

    // c_test->cd(3);
    h_ratio_N2C1p->Fit(func_ratio_N2C1p, "R0");
    h_ratio_N2C1p->Fit(func_ratio_N2C1p, "R0");
    h_ratio_N2C1p->Fit(func_ratio_N2C1p, "R+");

    // c_test->cd(4);
    h_ratio_N2C1m->Fit(func_ratio_N2C1m, "R0");
    h_ratio_N2C1m->Fit(func_ratio_N2C1m, "R0");
    h_ratio_N2C1m->Fit(func_ratio_N2C1m, "R+");
/*
    // Combine N2N1, C1C1, N2C1p, N2C1m
    // Original Higgsino
    h_Higgsino_N2N1_original->Scale(area_Higgsino_N2N1_original / sum_Higgsino_original); // scale to the correction contribution
    h_Higgsino_C1C1_original->Scale(area_Higgsino_C1C1_original / sum_Higgsino_original);
    h_Higgsino_N2C1p_original->Scale(area_Higgsino_N2C1p_original / sum_Higgsino_original);
    h_Higgsino_N2C1m_original->Scale(area_Higgsino_N2C1m_original / sum_Higgsino_original);
*/
    TH1F *h_Higgsino_combined_original = (TH1F *)h_Higgsino_N2N1_original->Clone();
    // h_Higgsino_combined_original->Add(h_Higgsino_C1C1_original);
    // h_Higgsino_combined_original->Add(h_Higgsino_N2C1p_original);
    // h_Higgsino_combined_original->Add(h_Higgsino_N2C1m_original);
    h_Higgsino_combined_original->SetName("h_Higgsino_combined_original");
    h_Higgsino_combined_original->SetTitle("");
    h_Higgsino_combined_original->SetXTitle("m_{ll} [GeV]");
    h_Higgsino_combined_original->SetYTitle("Normalized event counts");
    h_Higgsino_combined_original->SetLineColor(kGreen);
/*
    // NUHM2
    h_NUHM2_N2N1->Scale(integral_NUHM2_N2N1 / sum_NUHM2);
    h_NUHM2_C1C1->Scale(integral_NUHM2_C1C1 / sum_NUHM2);
    h_NUHM2_N2C1p->Scale(integral_NUHM2_N2C1p / sum_NUHM2);
    h_NUHM2_N2C1m->Scale(integral_NUHM2_N2C1m / sum_NUHM2);
*/
    TH1F *h_NUHM2_Combined = (TH1F *)h_NUHM2_N2N1->Clone();
    // h_NUHM2_Combined->Add(h_NUHM2_C1C1);
    // h_NUHM2_Combined->Add(h_NUHM2_N2C1p);
    // h_NUHM2_Combined->Add(h_NUHM2_N2C1m);
    h_NUHM2_Combined->SetName("h_NUHM2_Combined");
    h_NUHM2_Combined->SetTitle("");
    h_NUHM2_Combined->SetXTitle("m_{ll} [GeV]");
    h_NUHM2_Combined->SetYTitle("Normalized event counts");
    h_NUHM2_Combined->SetLineColor(kBlue);

    // Reweight Higgsino
    TH1F *h_Higgsino_N2N1_reweight = new TH1F("h_Higgsino_N2N1_reweight", "", 200, 0, 200);
    TH1F *h_Higgsino_C1C1_reweight = new TH1F("h_Higgsino_C1C1_reweight", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1p_reweight = new TH1F("h_Higgsino_N2C1p_reweight", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1m_reweight = new TH1F("h_Higgsino_N2C1m_reweight", "", 200, 0, 200);

    while (Reader_Higgsino_N2N1.Next()) {
        double truthMll = *truth_mll_Higgsino_N2N1;
        if (truthMll < dm_Higgsino) {
            double weight = 0.;
            if (truthMll < dm_NUHM2)
                weight = func_ratio_N2N1->Eval(truthMll);
            cout << "truthMll=" << truthMll << ", weight=" << weight << endl;
            h_Higgsino_N2N1_reweight->Fill(truthMll, weight);
        }
    }
    while (Reader_Higgsino_C1C1.Next()) {
        double truthMll = *truth_mll_Higgsino_C1C1;
        if (truthMll < dm_Higgsino) {
            double weight = 0.;
            if (truthMll < dm_NUHM2)
                weight = func_ratio_C1C1->Eval(truthMll);
            h_Higgsino_C1C1_reweight->Fill(truthMll, weight);
        }
    }
    while (Reader_Higgsino_N2C1p.Next()) {
        double truthMll = *truth_mll_Higgsino_N2C1p;
        if (truthMll < dm_Higgsino) {
            double weight = 0.;
            if (truthMll < dm_NUHM2)
                weight = func_ratio_N2C1p->Eval(truthMll);
            h_Higgsino_N2C1p_reweight->Fill(truthMll, weight);
        }
    }
    while (Reader_Higgsino_N2C1m.Next()) {
        double truthMll = *truth_mll_Higgsino_N2C1m;
        if (truthMll < dm_Higgsino) {
            double weight = 0.;
            if (truthMll < dm_NUHM2)
                weight = func_ratio_N2C1m->Eval(truthMll);
            h_Higgsino_N2C1m_reweight->Fill(truthMll, weight);
        }
    }

    // h_Higgsino_N2N1_reweight->SetLineColor(1);
    // h_Higgsino_C1C1_reweight->SetLineColor(2);
    // h_Higgsino_N2C1p_reweight->SetLineColor(3);
    // h_Higgsino_N2C1m_reweight->SetLineColor(4);

    // h_Higgsino_N2N1_reweight->Draw("hist");
    // h_Higgsino_C1C1_reweight->Draw("hist,same");
    // h_Higgsino_N2C1p_reweight->Draw("hist,same");
    // h_Higgsino_N2C1m_reweight->Draw("hist,same");

    double area_Higgsino_N2N1_reweight = h_Higgsino_N2N1_reweight->Integral();
    double area_Higgsino_C1C1_reweight = h_Higgsino_C1C1_reweight->Integral();
    double area_Higgsino_N2C1p_reweight = h_Higgsino_N2C1p_reweight->Integral();
    double area_Higgsino_N2C1m_reweight = h_Higgsino_N2C1m_reweight->Integral();
    double sum_Higgsino_reweight = area_Higgsino_N2N1_reweight + area_Higgsino_C1C1_reweight + area_Higgsino_N2C1p_reweight + area_Higgsino_N2C1m_reweight;
    // double sum_Higgsino_reweight = area_Higgsino_N2N1_reweight + area_Higgsino_N2C1p_reweight + area_Higgsino_N2C1m_reweight;

    h_Higgsino_N2N1_reweight->Scale(1./area_Higgsino_N2N1_reweight); // normalize to 1.
    h_Higgsino_C1C1_reweight->Scale(1./area_Higgsino_C1C1_reweight);
    h_Higgsino_N2C1p_reweight->Scale(1./area_Higgsino_N2C1p_reweight);
    h_Higgsino_N2C1m_reweight->Scale(1./area_Higgsino_N2C1m_reweight);
/*
    h_Higgsino_N2N1_reweight->Scale(area_Higgsino_N2N1_reweight / sum_Higgsino_reweight); // scale to the correction contribution
    h_Higgsino_C1C1_reweight->Scale(area_Higgsino_C1C1_reweight / sum_Higgsino_reweight);
    h_Higgsino_N2C1p_reweight->Scale(area_Higgsino_N2C1p_reweight / sum_Higgsino_reweight);
    h_Higgsino_N2C1m_reweight->Scale(area_Higgsino_N2C1m_reweight / sum_Higgsino_reweight);
*/
    TH1F *h_Higgsino_combined_reweight = (TH1F *)h_Higgsino_N2N1_reweight->Clone();
    // h_Higgsino_combined_reweight->Add(h_Higgsino_C1C1_reweight);
    // h_Higgsino_combined_reweight->Add(h_Higgsino_N2C1p_reweight);
    // h_Higgsino_combined_reweight->Add(h_Higgsino_N2C1m_reweight);
    h_Higgsino_combined_reweight->SetName("h_Higgsino_combined_reweight");
    h_Higgsino_combined_reweight->SetTitle("");
    h_Higgsino_combined_reweight->SetXTitle("m_{ll} [GeV]");
    h_Higgsino_combined_reweight->SetYTitle("Normalized event counts");
    h_Higgsino_combined_reweight->SetLineColor(kRed);

    // Making plot
    TCanvas *c = new TCanvas("c", "", 800, 600);
    c->SetLeftMargin(0.12);
    bool logY = false;

    if (logY)
        gPad->SetLogy();

    double x_max = 0;
    if (m12 <= 400)
        x_max = 100.;
    else if (m12 > 400)
        x_max = 50.;

    double y_max = max(h_Higgsino_combined_original->GetMaximum(), h_Higgsino_combined_reweight->GetMaximum()) * 1.2;

    h_Higgsino_combined_original->GetXaxis()->SetRangeUser(0, x_max);
    h_Higgsino_combined_original->GetYaxis()->SetTitleOffset(1.4);
    h_Higgsino_combined_original->SetMaximum(y_max);
    h_Higgsino_combined_original->SetStats(0);
    h_Higgsino_combined_original->Draw("hist");

    h_Higgsino_combined_reweight->Draw("hist,same");

    h_NUHM2_Combined->Draw("hist,same");

    TLegend *legend = new TLegend(0.4, 0.6, 0.9, 0.8);
    legend->AddEntry(h_Higgsino_combined_original, ("Higgsino_" + n2_n1).c_str(), "l");
    // legend->AddEntry(func_Higgsino, ("Calculated Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_Higgsino_combined_reweight, ("reweight Higgsino_" + n2_n1).c_str(), "l");
    // legend->AddEntry(func_NUHM2, ("Calculated reweighted Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_NUHM2_Combined, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    // string output = "reweight_Mike_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    // c->SaveAs(output.c_str());
}

void tree_reader(string f, double dm, TH1F *h1, TH1F *h2 = NULL, TF1 *func1 = NULL, TF1 *func2 = NULL)
{
    TFile *file = new TFile(f.c_str());
    TTreeReader myReader("EwkHiggsino2016__ntuple", file);
    TTreeReaderValue<float> truth_mll(myReader, "mll");

    TH1F *h_NUHM2_N2N1 = new TH1F("h_NUHM2_N2N1", "", 200, 0, 200);

    while (myReader.Next()) {
        double truthMll = *truth_mll;
        if (truthMll < dm) {
            h1->Fill(truthMll);
            if (h2 && func1 && func2) {
                double weight = func2->Eval(truthMll) / func1->Eval(truthMll); //ratio NUHM2/higgsino
                h2->Fill(truthMll, weight);
            }
        }
    }
}
