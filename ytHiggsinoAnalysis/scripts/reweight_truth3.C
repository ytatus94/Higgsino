#include <TROOT.h>
#include <TFile.h>
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
void plot_Lorenzo(int, int, int);
void plot_Mike(int, int, int);
void tree_reader(string, double, TH1F *, TH1F *h2 = NULL, TF1 *func1 = NULL, TF1 *func2 = NULL);

// main function
void reweight_truth3()
{
    // Use Lorenzo's way
    plot_Lorenzo(160, 100, 350);
    plot_Lorenzo(190, 150, 400);
    plot_Lorenzo(190, 150, 500);
    plot_Lorenzo(190, 150, 600);
    plot_Lorenzo(170, 150, 700);
    plot_Lorenzo(170, 150, 800);

    // Use Mike's way
    // plot_Mike(160, 100, 350);
    // plot_Mike(190, 150, 400);
    // plot_Mike(190, 150, 500);
    // plot_Mike(190, 150, 600);
    // plot_Mike(170, 150, 700);
    // plot_Mike(170, 150, 800);
}

void plot_Lorenzo(int n2, int n1, int m12)
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
    string path_Higgsino = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170817/";
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
    string path_NUHM2 = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170817/";

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

    TH1F *h_NUHM2_combined = combine_histogram(h_NUHM2_N2N1, h_NUHM2_N2C1p, h_NUHM2_N2C1m);
    h_NUHM2_combined->SetName("h_NUHM2_combined");
    h_NUHM2_combined->SetTitle("");
    h_NUHM2_combined->SetXTitle("m_{ll} [GeV]");
    h_NUHM2_combined->SetYTitle("Normalized event counts");
    h_NUHM2_combined->SetLineColor(kBlue);

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

    h_NUHM2_combined->Draw("hist,same");

    TLegend *legend = new TLegend(0.4, 0.6, 0.9, 0.8);
    legend->AddEntry(h_Higgsino_combined_original, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(func_Higgsino, ("Calculated Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_Higgsino_combined_reweight, ("reweight Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(func_NUHM2, ("Calculated reweighted Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_NUHM2_combined, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "reweight_Lorenzo_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());
    c->Close();
}

void plot_Mike(int n2, int n1, int m12)
{
    double dm_Higgsino = n2 - n1;
    double dm_NUHM2 = get_dm_NUHM2(m12);

    //Get the higgsino truth3 MC sample
    string path_Higgsino = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170817/";
    string n2_n1 = to_string(n2) + "_" + to_string(n1);

    string f_Higgsino_N2N1 = path_Higgsino + "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_C1C1 = path_Higgsino + "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1p = path_Higgsino + "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1m = path_Higgsino + "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    TH1F *h_Higgsino_combined_original = get_combined_hist(f_Higgsino_N2N1, f_Higgsino_C1C1, f_Higgsino_N2C1p, f_Higgsino_N2C1m);
    h_Higgsino_combined_original->SetLineColor(kGreen);

    // Get the NUHM2 truth3 MC sample
    string path_NUHM2 = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170817/";

    string f_NUHM2_N2N1 = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    string f_NUHM2_C1C1 = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string f_NUHM2_N2C1p = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string f_NUHM2_N2C1m = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    TH1F *h_NUHM2_combined = get_combined_hist(f_NUHM2_N2N1, f_NUHM2_C1C1, f_NUHM2_N2C1p, f_NUHM2_N2C1m);
    h_NUHM2_combined->SetLineColor(kBlue);

    // Ratio histograms
    TH1F *h_ratio_combined = (TH1F *)h_NUHM2_combined->Clone();
    h_ratio_combined->Divide(h_Higgsino_combined_original);
    h_ratio_combined->SetLineColor(kBlack);
    h_ratio_combined->SetLineWidth(1);
    h_ratio_combined->SetMarkerSize(0.5);
    h_ratio_combined->SetMarkerStyle(20);

    // int nbins = h_ratio_combined->GetXaxis()->GetNbins();
    // for (int i = 0; i <= nbins + 1; i++) {
    //     // double x_low = h_ratio_combined->GetBinLowEdge(i);
    //     double x_low = h_ratio_combined->GetXaxis()->GetBinLowEdge(i);
    //     double x_up = h_ratio_combined->GetXaxis()->GetBinUpEdge(i);
    //     double y = h_ratio_combined->GetBinContent(i);
    //     cout << x_low << "< pt <" << x_up << ", ratio=" << y << endl;
    // }

    TH1F *h_Higgsino_combined_reweight = new TH1F("h_Higgsino_combined_reweight", "", 200, 0, 200);
    h_Higgsino_combined_reweight->SetLineColor(kRed);
    h_Higgsino_combined_reweight->SetLineStyle(2);

    int nbins = h_ratio_combined->GetXaxis()->GetNbins();
    for (int i = 0; i <= nbins + 1; i++) {
        double x_low = h_ratio_combined->GetXaxis()->GetBinLowEdge(i);
        double x_up = h_ratio_combined->GetXaxis()->GetBinUpEdge(i);
        double weight = h_ratio_combined->GetBinContent(i);
        double y_original = h_Higgsino_combined_original->GetBinContent(i);
        double y_reweight = y_original * weight;
        h_Higgsino_combined_reweight->SetBinContent(i, y_reweight);
    }

    // Making plot
    TCanvas *c = new TCanvas("c", "", 800, 600);
    gStyle->SetOptStat(0);
    // gStyle->SetOptFit(1111);
    bool logY = false;

    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0); // Upper and lower plot are joined
    //pad1->SetGridy(); // grid lines
    pad1->SetLeftMargin(0.12);
    if (logY)
        pad1->SetLogy();
    pad1->Draw();

    // lower plot will be in pad
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.3);
    pad2->SetLeftMargin(0.12);
    pad2->SetGridy(); // grid lines
    pad2->Draw();

    //
    // pad1: top pad
    //
    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here
    double x_max = 0;
    if (m12 <= 400)
        x_max = 100.;
    else if (m12 > 400)
        x_max = 50.;

    double y_max = max(h_NUHM2_combined ->GetMaximum(), h_Higgsino_combined_original->GetMaximum()) * 1.2;

    h_NUHM2_combined->GetXaxis()->SetRangeUser(0, x_max);
    h_NUHM2_combined->SetMaximum(y_max);
    h_NUHM2_combined->Draw("hist");
    h_Higgsino_combined_original->Draw("hist,same");
    h_Higgsino_combined_reweight->Draw("hist,same");

    TLine *line_1 = new TLine(dm_NUHM2, 0., dm_NUHM2, y_max);
    line_1->SetLineColor(kBlue);
    line_1->SetLineStyle(2);
    line_1->SetLineWidth(1);
    line_1->Draw("SAME");

    TLine *line_2 = new TLine(dm_Higgsino, 0., dm_Higgsino, y_max);
    line_2->SetLineColor(kGreen);
    line_2->SetLineStyle(2);
    line_2->SetLineWidth(1);
    line_2->Draw("SAME");

    //
    // pad2: bottom pad
    //
    pad2->cd(); // pad2 becomes the current pad

    double pad2_X_min = 0., pad2_X_max = x_max;
    double pad2_Y_min = 0., pad2_Y_max = 5;
    string pad2_X_title = "m_{ll} [GeV]";
    string pad2_Y_title = "NUHM2 / Higgsino";

    TH1F *frame = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
    frame->GetXaxis()->SetNdivisions(510);
    frame->GetYaxis()->SetNdivisions(405);
    frame->SetLineWidth(1);
    frame->SetXTitle(pad2_X_title.c_str());
    frame->GetXaxis()->SetTitleSize(20);
    frame->GetXaxis()->SetTitleFont(47);
    frame->GetXaxis()->SetTitleOffset(4.0);
    frame->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetXaxis()->SetLabelSize(20);
    frame->SetYTitle(pad2_Y_title.c_str());
    frame->GetYaxis()->SetTitleSize(15);
    frame->GetYaxis()->SetTitleFont(43);
    frame->GetYaxis()->SetTitleOffset(1.6);
    frame->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetYaxis()->SetLabelSize(20);
    frame->Draw();

    h_ratio_combined->Draw("E1,SAME");

    TLine *line_3 = new TLine(dm_NUHM2, pad2_Y_min, dm_NUHM2, pad2_Y_max);
    line_3->SetLineColor(kBlue);
    line_3->SetLineStyle(2);
    line_3->SetLineWidth(1);
    line_3->Draw("SAME");

    TLine *line_4 = new TLine(dm_Higgsino, pad2_Y_min, dm_Higgsino, pad2_Y_max);
    line_4->SetLineColor(kGreen);
    line_4->SetLineStyle(2);
    line_4->SetLineWidth(1);
    line_4->Draw("SAME");

    // Put legend on pad1
    pad1->cd();

    TLegend *legend = new TLegend(0.5, 0.3, 0.9, 0.8);
    legend->AddEntry(h_NUHM2_combined, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->AddEntry(h_Higgsino_combined_original, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_Higgsino_combined_reweight, ("Reweight Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(line_1, "dm_{NUHM2}", "l");
    legend->AddEntry(line_2, "dm_{Higgsino}", "l");
    legend->AddEntry(h_ratio_combined, "ratio", "pe");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.05);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "reweight_Mike_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());
    c->Close();
}

void tree_reader(string f, double dm, TH1F *h1, TH1F *h2 = NULL, TF1 *func1 = NULL, TF1 *func2 = NULL)
{
    // string tree_name = "EwkHiggsino2016__ntuple";
    string tree_name = "EwkNUHM22016__ntuple";

    TFile *file = new TFile(f.c_str());
    TTreeReader myReader(tree_name.c_str(), file);
    TTreeReaderValue<float> truth_mll(myReader, "mll");
    TTreeReaderValue<int> truth_preselection(myReader, "preselection");
    TTreeReaderValue<int> truth_is2LChannel(myReader, "is2LChannel");

    while (myReader.Next()) {
        double truthMll = *truth_mll;
        int preselection = *truth_preselection;
        int is2LChannel = *truth_is2LChannel;
        if (preselection == 1 && is2LChannel == 1) {
            if (truthMll < dm) {
                h1->Fill(truthMll);
                if (h2 && func1 && func2) {
                    double weight = func2->Eval(truthMll) / func1->Eval(truthMll); //ratio NUHM2/higgsino
                    h2->Fill(truthMll, weight);
                }
            }
        }
    }
}
