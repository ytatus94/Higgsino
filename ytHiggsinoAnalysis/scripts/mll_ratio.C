#include <TROOT.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TLegend.h>

#include "get_combined_hist.C"
#include "ytUtility.C"

#include <string>
#include <iostream>
using namespace std;

void plot_mll_ratio_with_tail(int, int, int);
void plot_mll_ratio_without_tail(int, int, int);
void tree_reader(string, double, TH1F *);

void mll_ratio()
{
    plot_mll_ratio_with_tail(160, 100, 350);
    plot_mll_ratio_with_tail(190, 150, 400);
    plot_mll_ratio_with_tail(190, 150, 500);
    plot_mll_ratio_with_tail(190, 150, 600);
    plot_mll_ratio_with_tail(170, 150, 700);
    plot_mll_ratio_with_tail(170, 150, 800);

    // plot_mll_ratio_without_tail(160, 100, 350);
    // plot_mll_ratio_without_tail(190, 150, 400);
    // plot_mll_ratio_without_tail(190, 150, 500);
    // plot_mll_ratio_without_tail(190, 150, 600);
    // plot_mll_ratio_without_tail(170, 150, 700);
    // plot_mll_ratio_without_tail(170, 150, 800);
}

void plot_mll_ratio_with_tail(int n2, int n1, int m12)
{
    // Get histograms
    string path_NUHM2 = "/Users/ytshen/Desktop/20170817/";
    string path_Higgsino = "/Users/ytshen/Desktop/20170817/";

    string n2_n1 = to_string(n2) + "_" + to_string(n1);

    string file_NUHM2_N2N1 = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    string file_NUHM2_C1C1 = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string file_NUHM2_N2C1p = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string file_NUHM2_N2C1m = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    string file_Higgsino_N2N1 = path_Higgsino + "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root";
    string file_Higgsino_C1C1 = path_Higgsino + "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1p = path_Higgsino + "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1m = path_Higgsino + "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    TH1F *h_NUHM2 = get_combined_hist(file_NUHM2_N2N1, file_NUHM2_C1C1, file_NUHM2_N2C1p, file_NUHM2_N2C1m);
    h_NUHM2->SetLineColor(kBlue);
    h_NUHM2->SetTitle("");
    h_NUHM2->SetXTitle("m_{ll} [GeV]");
    h_NUHM2->SetYTitle("Normalized event counts");
    h_NUHM2->GetYaxis()->SetTitleOffset(1.3);

    TH1F *h_Higgsino = get_combined_hist(file_Higgsino_N2N1, file_Higgsino_C1C1, file_Higgsino_N2C1p, file_Higgsino_N2C1m);
    h_Higgsino->SetLineColor(kGreen);
    h_Higgsino->SetTitle("");
    h_Higgsino->SetXTitle("m_{ll} [GeV]");
    h_Higgsino->SetYTitle("Normalized event counts");
    h_Higgsino->GetYaxis()->SetTitleOffset(1.3);

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
    pad2->SetTopMargin(0.1);
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

    double y_max = max(h_NUHM2->GetMaximum(), h_Higgsino->GetMaximum()) * 1.2;

    h_NUHM2->GetXaxis()->SetRangeUser(0, x_max);
    h_NUHM2->SetMaximum(y_max);
    h_NUHM2->Draw("hist");
    h_Higgsino->Draw("hist,same");

    double dm_NUHM2 = get_dm_NUHM2(m12);
    double dm_Higgsino = n2 - n1;

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

    TH1F *h_ratio = (TH1F *)h_NUHM2->Clone();
    h_ratio->SetName("h_ratio");
    h_ratio->Divide(h_Higgsino);
    h_ratio->SetLineColor(kBlack);
    h_ratio->SetLineWidth(1);
    h_ratio->SetMarkerSize(0.5);
    h_ratio->SetMarkerStyle(20);
    h_ratio->Draw("E1,SAME");

    TF1 *fit_ratio = new TF1("fit_ratio", "pol2", 0, dm_NUHM2);
    fit_ratio->SetParameters(1., 1., 1.);
    fit_ratio->SetLineColor(kRed);
    fit_ratio->SetLineStyle(2);

    h_ratio->Fit(fit_ratio, "R0");
    h_ratio->Fit(fit_ratio, "R0");
    h_ratio->Fit(fit_ratio, "R+");
    // fit->Draw("same");

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
    legend->AddEntry(h_NUHM2, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->AddEntry(h_Higgsino, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(line_1, "dm_{NUHM2}", "l");
    legend->AddEntry(line_2, "dm_{Higgsino}", "l");
    legend->AddEntry(h_ratio, "ratio", "pe");
    legend->AddEntry(fit_ratio, "Fit ratio using pol2", "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.05);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "ratio_with_tail_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());
}

void plot_mll_ratio_without_tail(int n2, int n1, int m12)
{
    double dm_NUHM2 = get_dm_NUHM2(m12);
    double dm_Higgsino = n2 - n1;

    // Get histograms
    string path_NUHM2 = "/Users/ytshen/Desktop/20170817/";
    string path_Higgsino = "/Users/ytshen/Desktop/20170817/";

    string n2_n1 = to_string(n2) + "_" + to_string(n1);

    string f_NUHM2_N2N1 = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    string f_NUHM2_C1C1 = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string f_NUHM2_N2C1p = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string f_NUHM2_N2C1m = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    string f_Higgsino_N2N1 = path_Higgsino + "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_C1C1 = path_Higgsino + "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1p = path_Higgsino + "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1m = path_Higgsino + "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    // Get the NUHM2 truth3 MC sample
    TH1F *h_NUHM2_N2N1 = new TH1F("h_NUHM2_N2N1", "", 200, 0, 200);
    TH1F *h_NUHM2_C1C1 = new TH1F("h_NUHM2_C1C1", "", 200, 0, 200);
    TH1F *h_NUHM2_N2C1p = new TH1F("h_NUHM2_N2C1p", "", 200, 0, 200);
    TH1F *h_NUHM2_N2C1m = new TH1F("h_NUHM2_N2C1m", "", 200, 0, 200);

    tree_reader(f_NUHM2_N2N1, dm_NUHM2, h_NUHM2_N2N1);
    tree_reader(f_NUHM2_C1C1, dm_NUHM2, h_NUHM2_C1C1);
    tree_reader(f_NUHM2_N2C1p, dm_NUHM2, h_NUHM2_N2C1p);
    tree_reader(f_NUHM2_N2C1m, dm_NUHM2, h_NUHM2_N2C1m);

    TH1F *h_NUHM2_Combined = combine_histogram(h_NUHM2_N2N1, h_NUHM2_C1C1, h_NUHM2_N2C1p, h_NUHM2_N2C1m);
    h_NUHM2_Combined->SetName("h_NUHM2_Combined");
    h_NUHM2_Combined->SetTitle("");
    h_NUHM2_Combined->SetXTitle("m_{ll} [GeV]");
    h_NUHM2_Combined->SetYTitle("Normalized event counts");
    h_NUHM2_Combined->SetLineColor(kBlue);

    // Get the Higgsino truth3 MC sample
    TH1F *h_Higgsino_N2N1_original = new TH1F("h_Higgsino_N2N1_original", "", 200, 0, 200);
    TH1F *h_Higgsino_C1C1_original = new TH1F("h_Higgsino_C1C1_original", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1p_original = new TH1F("h_Higgsino_N2C1p_original", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1m_original = new TH1F("h_Higgsino_N2C1m_original", "", 200, 0, 200);

    tree_reader(f_Higgsino_N2N1, dm_Higgsino, h_Higgsino_N2N1_original);
    tree_reader(f_Higgsino_C1C1, dm_Higgsino, h_Higgsino_C1C1_original);
    tree_reader(f_Higgsino_N2C1p, dm_Higgsino, h_Higgsino_N2C1p_original);
    tree_reader(f_Higgsino_N2C1m, dm_Higgsino, h_Higgsino_N2C1m_original);

    TH1F *h_Higgsino_combined_original = combine_histogram(h_Higgsino_N2N1_original, h_Higgsino_C1C1_original, h_Higgsino_N2C1p_original, h_Higgsino_N2C1m_original);
    h_Higgsino_combined_original->SetName("h_Higgsino_combined_original");
    h_Higgsino_combined_original->SetTitle("");
    h_Higgsino_combined_original->SetXTitle("m_{ll} [GeV]");
    h_Higgsino_combined_original->SetYTitle("Normalized event counts");
    h_Higgsino_combined_original->SetLineColor(kGreen);

    TH1F *h_ratio = (TH1F *)h_NUHM2_Combined->Clone();
    h_ratio->SetName("h_ratio");
    h_ratio->Divide(h_Higgsino_combined_original);
    h_ratio->SetLineColor(kBlack);
    h_ratio->SetLineWidth(1);
    h_ratio->SetMarkerSize(0.5);
    h_ratio->SetMarkerStyle(20);

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
    pad2->SetTopMargin(0.1);
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

    double y_max = max(h_NUHM2_Combined->GetMaximum(), h_Higgsino_combined_original->GetMaximum()) * 1.2;

    h_NUHM2_Combined->GetXaxis()->SetRangeUser(0, x_max);
    h_NUHM2_Combined->SetMaximum(y_max);
    h_NUHM2_Combined->Draw("hist");
    h_Higgsino_combined_original->Draw("hist,same");

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

    h_ratio->Draw("E1,SAME");

    TF1 *fit_ratio = new TF1("fit_ratio", "pol2", 0, dm_NUHM2);
    fit_ratio->SetParameters(1., 1., 1.);
    fit_ratio->SetLineColor(kRed);
    fit_ratio->SetLineStyle(2);

    h_ratio->Fit(fit_ratio, "R0");
    h_ratio->Fit(fit_ratio, "R0");
    h_ratio->Fit(fit_ratio, "R+");    

    // Put legend on pad1
    pad1->cd();

    TLegend *legend = new TLegend(0.5, 0.3, 0.9, 0.8);
    legend->AddEntry(h_NUHM2_Combined, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->AddEntry(h_Higgsino_combined_original, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_ratio, "ratio", "pe");
    legend->AddEntry(fit_ratio, "Fit ratio using pol2", "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.05);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "ratio_without_tail_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());
}

void tree_reader(string f, double dm, TH1F *h1)
{
    // string tree_name = "EwkHiggsino2016__ntuple";
    string tree_name = "EwkNUHM22016__ntuple";

    TFile *file = new TFile(f.c_str());
    TTreeReader myReader(tree_name.c_str(), file);
    TTreeReaderValue<float> truth_mll(myReader, "mll");

    TH1F *h_NUHM2_N2N1 = new TH1F("h_NUHM2_N2N1", "", 200, 0, 200);

    while (myReader.Next()) {
        double truthMll = *truth_mll;
        if (truthMll < dm)
            h1->Fill(truthMll);
    }
}
