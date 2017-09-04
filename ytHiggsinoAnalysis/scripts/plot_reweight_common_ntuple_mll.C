#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TLegend.h>

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

void plot(string);

void plot_reweight_common_ntuple_mll()
{
    string path = "/Users/ytshen/Desktop/";
    string f_m12_350 = "reweighted_m12_350.root";
    string f_m12_400 = "reweighted_m12_400.root";
    string f_m12_500 = "reweighted_m12_500.root";
    string f_m12_600 = "reweighted_m12_600.root";
    string f_m12_700 = "reweighted_m12_700.root";
    string f_m12_800 = "reweighted_m12_800.root";

    plot(path + f_m12_350);
    plot(path + f_m12_400);
    plot(path + f_m12_500);
    plot(path + f_m12_600);
    plot(path + f_m12_700);
    plot(path + f_m12_800);
}

void plot(string f)
{
    TFile *file = new TFile(f.c_str());
    string f_name = file->GetName();
    cout << "f_name=" << f_name << endl;

    int start_index = f_name.find("m12_") + string("m12_").length();
    int end_index = f_name.find(".root");
    cout << "start_index=" << start_index << endl;
    cout << "end_index=" << end_index << endl;
    string m12 = f.substr(start_index, end_index - start_index);
    cout << "m12=" << m12 << endl;

    TH1F *h_truth_Mll = (TH1F *)file->Get("h_truth_Mll");
    TH1F *h_reweighted_Mll = (TH1F *)file->Get("h_reweighted_Mll");

    TCanvas *c = new TCanvas("c", "", 800, 600);
    c->SetLeftMargin(0.12);
    bool logY = true;
    if (logY)
        gPad->SetLogy();

    double y_max = max(h_truth_Mll->GetMaximum(), h_reweighted_Mll->GetMaximum());
    if (logY)
        y_max *= 5;

    double range_user_xmin = 0, range_user_xmax = 0;
    if (m12 == "350")
        range_user_xmax = 100;
    else
        range_user_xmax = 50;

    h_truth_Mll->SetTitle("");
    h_truth_Mll->SetXTitle("m_{ll} [GeV]");
    h_truth_Mll->SetYTitle("Events");
    h_truth_Mll->GetXaxis()->SetRangeUser(range_user_xmin, range_user_xmax);
    h_truth_Mll->GetYaxis()->SetTitleOffset(1.4);
    h_truth_Mll->SetMaximum(y_max);
    h_truth_Mll->SetLineColor(kGreen);
    h_truth_Mll->SetStats(0);
    h_truth_Mll->Draw("hist");

    h_reweighted_Mll->SetLineColor(kRed);
    h_reweighted_Mll->Draw("hist,same");

    string s1 = "", s2 = "";
    if (m12 == "350") {
        s1 = "Higgsino 160_100";
        s2 = "Reweighted " + s1 + " (i.e NUHM2 m12=350)";
    }
    else if (m12 == "400") {
        s1 = "Higgsino 190_150";
        s2 = "Reweighted " + s1 + " (i.e NUHM2 m12=400)";
    }
    else if (m12 == "500") {
        s1 = "Higgsino 190_150";
        s2 = "Reweighted " + s1 + " (i.e NUHM2 m12=500)";
    }
    else if (m12 == "600") {
        s1 = "Higgsino 190_150";
        s2 = "Reweighted " + s1 + " (i.e NUHM2 m12=600)";
    }
    else if (m12 == "700") {
        s1 = "Higgsino 170_150";
        s2 = "Reweighted " + s1 + " (i.e NUHM2 m12=700)";
    }
    else if (m12 == "800") {
        s1 = "Higgsino 170_150";
        s2 = "Reweighted " + s1 + " (i.e NUHM2 m12=800)";
    }

    TLegend *legend = new TLegend(0.2, 0.75, 0.7, 0.85);
    legend->AddEntry(h_truth_Mll, s1.c_str(), "l");
    legend->AddEntry(h_reweighted_Mll, s2.c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "reweight_Higgsino_common_ntuple_v1.8b_to_m12_" + m12 + ".pdf";
    c->SaveAs(output.c_str());
    c->Close();
}
