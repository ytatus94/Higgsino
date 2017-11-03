#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TF1.h>
#include <TLegend.h>

#include "FuncMllDistr_modified.C"
#include "get_combined_hist.C"
#include "ytUtility.C"

#include <string>
// #include <algorithm>
// #include <typeinfo>
#include <iostream>
using namespace std;

// Declare functions
void plot(string, int, int, int, bool = false);
TH1F *tree_reader(string, string, int, int, int, bool);
string get_x_title(string);
string get_y_title(string);
void get_nbins_xmin_xmax(string, int &, double &, double &);
void get_range_user(string, double &, double &);
void ATLASLabel(Double_t x, Double_t y, const char* text, Color_t color);

void reweight_mc_event_weight(int n2, int n1, int m12, bool normalize = false)
{
    vector<string> vars_type_vector_float = {
        // type=vector<float>:
        "baselineElectrons_pt",
        "baselineMuons_pt",
        "baselineJets_pt",
        "signalMuons_pt",
        "signalJets_pt",
        "signalBjets_pt",
        "baselineLeptons_pt",
        "signalLeptons_pt",
        "baselineElectrons_eta",
        "baselineMuons_eta",
        "baselineJets_eta",
        "signalElectrons_eta",
        "signalMuons_eta",
        "signalJets_eta",
        "signalBjets_eta",
        "baselineLeptons_eta",
        "signalLeptons_eta",   
        "baselineElectrons_phi",
        "baselineMuons_phi",
        "baselineJets_phi",
        "signalElectrons_phi",
        "signalMuons_phi",
        "signalJets_phi",
        "signalBjets_phi",
        "baselineLeptons_phi",
        "signalLeptons_phi"
    };

    vector <string> vars_type_int = {
        // type=int:
        "nBaselineLeptons",
        "nBaselineElectrons",
        "nBaselineMuons",
        "nSignalLeptons",
        "nElectrons",
        "nMuons",
        "nJets",
        "nJet30",
        "nJet25",
        "nBjets"
    };

    vector <string> var_type_float = {
        // type=float:
        "dphiMin1",
        "mT",
        "mT2",
        "meffIncl",
        "HTIncl",
        "HT30",
        "HTLep12",
        "METOverHT",
        "METOverHTLep12",
        "mll",
        "pTll",
        "Rll",
        "MTauTau",
        "met"
    };

    for (auto &var : vars_type_int) {
    // for (auto &var : var_type_float) {
    // for (auto &var : vars_type_vector_float) {
        // cout << var << endl;
        plot(var, n2, n1, m12, false);
    }
    // plot("pTLep1", n2, n1, m12, false);
    // plot("pTLep2", n2, n1, m12, false);
    // plot("nJet30", n2, n1, m12);

    // plot("mll", 190, 150, 400, false);
}

void plot(string var, int n2, int n1, int m12, bool normalize = false)
{
    double dm_NUHM2 = get_dm_NUHM2(m12);
    double dm_Higgsino = n2 - n1;

    // Higgsino TRUTH3
    string path_Higgsino = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170817/";

    string n2_n1 = to_string(n2) + "_" + to_string(n1);

    string file_Higgsino_N2N1  = path_Higgsino + "user.yushen.SM_N2N1_"  + n2_n1 + "_2LMET50.root";
    // string file_Higgsino_C1C1  = path_Higgsino + "user.yushen.SM_C1C1_"  + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1p = path_Higgsino + "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1m = path_Higgsino + "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    bool is_reweight = false;

    TH1F *h_Higgsino_N2N1_original = tree_reader(file_Higgsino_N2N1, var, n1, n2, m12, is_reweight);
    // TH1F *h_Higgsino_C1C1_original = tree_reader(file_Higgsino_C1C1, var, n1, n2, m12, is_reweight);
    TH1F *h_Higgsino_N2C1p_original = tree_reader(file_Higgsino_N2C1p, var, n1, n2, m12, is_reweight);
    TH1F *h_Higgsino_N2C1m_original = tree_reader(file_Higgsino_N2C1m, var, n1, n2, m12, is_reweight);

    h_Higgsino_N2N1_original->SetName("h_Higgsino_N2N1_original");
    // h_Higgsino_C1C1_original->SetName("h_Higgsino_C1C1_original");
    h_Higgsino_N2C1p_original->SetName("h_Higgsino_N2C1p_original");
    h_Higgsino_N2C1m_original->SetName("h_Higgsino_N2C1m_original");

    TH1F *h_Higgsino_combined_original = 0;
    if (normalize) {
        h_Higgsino_combined_original = combine_histogram(h_Higgsino_N2N1_original, h_Higgsino_N2C1p_original, h_Higgsino_N2C1m_original);
        h_Higgsino_combined_original->SetYTitle("Normalized event counts");
    }
    else {
        h_Higgsino_combined_original = (TH1F *)h_Higgsino_N2N1_original->Clone();
        h_Higgsino_combined_original->Add(h_Higgsino_N2C1p_original);
        h_Higgsino_combined_original->Add(h_Higgsino_N2C1m_original);
        // h_Higgsino_combined_original->SetYTitle("Events");
    }
    h_Higgsino_combined_original->SetTitle("");
    h_Higgsino_combined_original->SetXTitle( (get_x_title(var)).c_str() );
    h_Higgsino_combined_original->SetYTitle( (get_y_title(var)).c_str() );
    h_Higgsino_combined_original->SetLineColor(kGreen);

    is_reweight = true;
    TH1F *h_Higgsino_N2N1_reweight = tree_reader(file_Higgsino_N2N1, var, n1, n2, m12, is_reweight);
    // TH1F *h_Higgsino_C1C1_reweight = tree_reader(file_Higgsino_C1C1, var, n1, n2, m12, is_reweight);
    TH1F *h_Higgsino_N2C1p_reweight = tree_reader(file_Higgsino_N2C1p, var, n1, n2, m12, is_reweight);
    TH1F *h_Higgsino_N2C1m_reweight = tree_reader(file_Higgsino_N2C1m, var, n1, n2, m12, is_reweight);

    h_Higgsino_N2N1_reweight->SetName("h_Higgsino_N2N1_reweight");
    // h_Higgsino_C1C1_reweight->SetName("h_Higgsino_C1C1_reweight");
    h_Higgsino_N2C1p_reweight->SetName("h_Higgsino_N2C1p_reweight");
    h_Higgsino_N2C1m_reweight->SetName("h_Higgsino_N2C1m_reweight");

    TH1F *h_Higgsino_combined_reweight = 0;
    if (normalize) {
        h_Higgsino_combined_reweight = combine_histogram(h_Higgsino_N2N1_reweight, h_Higgsino_N2C1p_reweight, h_Higgsino_N2C1m_reweight);
        h_Higgsino_combined_reweight->SetYTitle("Normalized event counts");
    }
    else {
        h_Higgsino_combined_reweight = (TH1F *)h_Higgsino_N2N1_reweight->Clone();
        h_Higgsino_combined_reweight->Add(h_Higgsino_N2C1p_reweight);
        h_Higgsino_combined_reweight->Add(h_Higgsino_N2C1m_reweight);
    }
    h_Higgsino_combined_reweight->SetTitle("");
    h_Higgsino_combined_reweight->SetXTitle( (get_x_title(var)).c_str() );
    h_Higgsino_combined_reweight->SetYTitle( (get_y_title(var)).c_str() );
    h_Higgsino_combined_reweight->SetLineColor(kRed);

    // NUHM2 TRUTH3
    string path_NUHM2 = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170817/";

    string file_NUHM2_N2N1  = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    // string file_NUHM2_C1C1  = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string file_NUHM2_N2C1p = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string file_NUHM2_N2C1m = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    is_reweight = false;
    TH1F *h_NUHM2_N2N1 = tree_reader(file_NUHM2_N2N1, var, n1, n2, m12, is_reweight);
    // TH1F *h_NUHM2_C1C1 = tree_reader(file_NUHM2_C1C1, var, n1, n2, m12, is_reweight);
    TH1F *h_NUHM2_N2C1p = tree_reader(file_NUHM2_N2C1p, var, n1, n2, m12, is_reweight);
    TH1F *h_NUHM2_N2C1m = tree_reader(file_NUHM2_N2C1m, var, n1, n2, m12, is_reweight);

    h_NUHM2_N2N1->SetName("h_NUHM2_N2N1");
    // h_NUHM2_C1C1->SetName("h_NUHM2_C1C1");
    h_NUHM2_N2C1p->SetName("h_NUHM2_N2C1p");
    h_NUHM2_N2C1m->SetName("h_NUHM2_N2C1m");

    TH1F *h_NUHM2_combined = 0;
    if (normalize) {
        h_NUHM2_combined = combine_histogram(h_NUHM2_N2N1, h_NUHM2_N2C1p, h_NUHM2_N2C1m);
        h_NUHM2_combined->SetYTitle("Normalized event counts");
    }
    else {
        h_NUHM2_combined = (TH1F *)h_NUHM2_N2N1->Clone();
        h_NUHM2_combined->Add(h_NUHM2_N2C1p);
        h_NUHM2_combined->Add(h_NUHM2_N2C1m);
        // h_NUHM2_combined->SetYTitle("Events");
    }
    h_NUHM2_combined->SetTitle("");
    h_NUHM2_combined->SetXTitle( (get_x_title(var)).c_str() );
    h_NUHM2_combined->SetYTitle( (get_y_title(var)).c_str() );
    h_NUHM2_combined->SetLineColor(kBlue);

    TH1F *h_ratio_NUHM2_original_Higgsino = (TH1F *)h_NUHM2_combined->Clone();
    h_ratio_NUHM2_original_Higgsino->Divide(h_Higgsino_combined_original);
    h_ratio_NUHM2_original_Higgsino->SetLineColor(kGreen);
    h_ratio_NUHM2_original_Higgsino->SetMarkerColor(kGreen);
    h_ratio_NUHM2_original_Higgsino->SetMarkerStyle(kFullCircle);

    TH1F *h_ratio_NUHM2_reweight_Higgsino = (TH1F *)h_NUHM2_combined->Clone();
    h_ratio_NUHM2_reweight_Higgsino->Divide(h_Higgsino_combined_reweight);
    h_ratio_NUHM2_reweight_Higgsino->SetLineColor(kRed);
    h_ratio_NUHM2_reweight_Higgsino->SetMarkerColor(kRed);
    h_ratio_NUHM2_reweight_Higgsino->SetMarkerStyle(kFullCircle);

    // Making plot
    TCanvas *c = new TCanvas("c", "", 800, 800);
    // c->SetLeftMargin(0.15);
    // c->SetBottomMargin(0.1);
    gStyle->SetOptStat(0);
    // gStyle->SetOptFit(1111);

    bool logY = false;

    if (var.compare("HTIncl") == 0 ||
        var.compare("HT30") == 0 ||
        var.compare("HTLep12") == 0 ||
        var.compare("METOverHTLep12") == 0 ||
        var.compare("mll") == 0 ||
        var.compare("pTll") == 0 ||
        var.compare("Rll") == 0 ||
        var.compare("mT") == 0 ||
        var.compare("mT2") == 0) {
        logY = true;
    }

    //Upper plot will be in pad1
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    // pad1->SetBottomMargin(0); // Upper and lower plot are joined
    // pad1->SetLeftMargin(0.12);
    //pad1->SetGridy(); // grid lines
    pad1->SetBottomMargin(0.05);
    // pad1->SetRightMargin(0.05);
    pad1->SetLeftMargin(0.16);

    if (logY)
        pad1->SetLogy();
    pad1->Draw();

    // lower plot will be in pad
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
    // pad2->SetTopMargin(0);
    // pad2->SetBottomMargin(0.3);
    // pad2->SetLeftMargin(0.12);
    pad2->SetTopMargin(0.05);
    pad2->SetBottomMargin(0.35);
    // pad2->SetRightMargin(0.05);
    pad2->SetLeftMargin(0.16);
    pad2->SetGridy(); // grid lines
    pad2->Draw();

    //
    // pad1: top pad
    //
    pad1->cd(); // pad1 becomes the current pad
    //pad1->SetFrameLineWidth(2);

    // Draw curve here
    double range_user_xmin = 0., range_user_xmax = 0.;
    get_range_user(var, range_user_xmin, range_user_xmax);

    double y_scale_factor = 0;
    if (logY)
        y_scale_factor = 1000;
    else
        y_scale_factor = 1.5;

    double y_max1 = max(h_Higgsino_combined_original->GetMaximum(), h_Higgsino_combined_reweight->GetMaximum());
    double y_max = max(y_max1, h_NUHM2_combined->GetMaximum()) * y_scale_factor;

    h_Higgsino_combined_original->GetXaxis()->SetRangeUser(range_user_xmin, range_user_xmax);
    h_Higgsino_combined_original->GetXaxis()->SetTitleOffset(1.5);
    h_Higgsino_combined_original->GetYaxis()->SetTitleOffset(1.7);
    h_Higgsino_combined_original->GetXaxis()->SetLabelSize(0);
    // h_Higgsino_combined_original->GetYaxis()->SetTitleOffset(0.9);
    h_Higgsino_combined_original->GetYaxis()->SetTitleSize(0.05);
    h_Higgsino_combined_original->GetYaxis()->SetTitleOffset(1.3);
    h_Higgsino_combined_original->GetYaxis()->SetLabelSize(0.048);
    h_Higgsino_combined_original->GetYaxis()->SetLabelOffset(0.015);
    h_Higgsino_combined_original->SetMaximum(y_max);
    h_Higgsino_combined_original->SetStats(0);
    h_Higgsino_combined_original->Draw("hist");

    h_Higgsino_combined_reweight->Draw("hist,same");

    h_NUHM2_combined->Draw("hist,same");

    // cout << "h_Higgsino_combined_original->Integral()=" << h_Higgsino_combined_original->Integral() << endl;
    // cout << "h_Higgsino_combined_reweight->Integral()=" << h_Higgsino_combined_reweight->Integral() << endl;
    // cout << "h_NUHM2_combined->Integral()=" << h_NUHM2_combined->Integral() << endl;

    //
    // pad2: bottom pad
    //
    pad2->cd(); // pad2 becomes the current pad

    double pad2_X_min = range_user_xmin, pad2_X_max = range_user_xmax;
    // double pad2_Y_min = 0., pad2_Y_max = 4.9;
    double pad2_Y_min = 0., pad2_Y_max = 2;
    string pad2_X_title = get_x_title(var);
    string pad2_Y_title = "ratio";

    TH1F *frame = pad2->DrawFrame(pad2_X_min, pad2_Y_min, pad2_X_max, pad2_Y_max);
    frame->GetXaxis()->SetNdivisions(510);
    frame->GetYaxis()->SetNdivisions(405);
    frame->SetLineWidth(1);
    frame->SetXTitle(pad2_X_title.c_str());
    frame->GetXaxis()->SetTitleSize(25);
    frame->GetXaxis()->SetTitleFont(47);
    frame->GetXaxis()->SetTitleOffset(4.0);
    frame->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetXaxis()->SetLabelSize(20);
    frame->GetXaxis()->SetLabelOffset(0.05);
    frame->SetYTitle(pad2_Y_title.c_str());
    frame->GetYaxis()->SetTitleSize(25);
    frame->GetYaxis()->SetTitleFont(43);
    frame->GetYaxis()->SetTitleOffset(1.8);
    frame->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
    frame->GetYaxis()->SetLabelSize(20);
    frame->GetYaxis()->SetLabelOffset(0.015);
    frame->Draw();

    for (int i = 0; i < h_ratio_NUHM2_original_Higgsino->GetXaxis()->GetNbins() + 1; i++) {
        if (h_ratio_NUHM2_original_Higgsino->GetBinContent(i) == 0) {
            h_ratio_NUHM2_original_Higgsino->SetBinContent(i, -99.);
        }
    }
    h_ratio_NUHM2_original_Higgsino->Draw("e1,same");
    for (int i = 0; i < h_ratio_NUHM2_reweight_Higgsino->GetXaxis()->GetNbins() + 1; i++) {
        if (h_ratio_NUHM2_reweight_Higgsino->GetBinContent(i) == 0) {
            h_ratio_NUHM2_reweight_Higgsino->SetBinContent(i, -99.);
        }
    }
    h_ratio_NUHM2_reweight_Higgsino->Draw("e1,same");

    // Put legend on pad1
    pad1->cd();

    ATLASLabel(0.2, 0.83, "internal", kBlack);

    TLegend *legend = new TLegend(0.5, 0.45, 0.7, 0.88);
    legend->AddEntry(h_NUHM2_combined, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->AddEntry(h_Higgsino_combined_original, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_Higgsino_combined_reweight, ("Reweight Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_ratio_NUHM2_original_Higgsino, "ratio = NUHM2 / Higgsino", "lpe");
    legend->AddEntry(h_ratio_NUHM2_reweight_Higgsino, "ratio = NUHM2 / reweight Higgsino", "lpe");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.04);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "";
    if (normalize) {
        output = "reweight_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + "_" + var + "_normalize.pdf";
    }
    else {
        output = "reweight_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + "_" + var + ".pdf";
    }
    c->SaveAs(output.c_str());
    c->Close();
}

TH1F *tree_reader(string f, string var, int n1, int n2, int m12, bool is_reweight)
{
    // Set the histogram ranges
    int nbins = 0;
    double xmin = 0., xmax = 0.;

    get_nbins_xmin_xmax(var, nbins, xmin, xmax);

    string h_name;
    if (!is_reweight) // original
        h_name = "h_" + var;
    else // reweight
        h_name = "h_" + var + "_reweight";

    TH1F *h1 = new TH1F(h_name.c_str(), "", nbins, xmin, xmax);

    double dm_Higgsino = n2 - n1;
    double dm_NUHM2 = get_dm_NUHM2(m12);
    double par1 = get_NUHM2_N1_mass(m12);
    double par2 = get_NUHM2_N2_mass(m12);

    string n2_n1 = to_string(n2) + "_" + to_string(n1);
    double dm = 0;
    string decay = "";
    bool isHiggsino = false;
    if (f.find(".SM_") != string::npos &&
        f.find(n2_n1 + "_2LMET50.root") != string::npos) {
        dm = dm_Higgsino;
        int start_index = f.find(".SM_") + 4;
        int end_index = f.find(n2_n1 + "_2LMET50.root") - 2;
        int len = end_index - start_index + 1;
        decay = f.substr(start_index, len);
        isHiggsino = true;
    }
    if (f.find("run_" + to_string(m12)) != string::npos &&
        f.find("TestJob.root") != string::npos) {
        dm = dm_NUHM2;
        int start_index = f.find(to_string(m12)) + 4;
        int end_index = f.find(".TestJob.root") - 1;
        int len = end_index - start_index + 1;
        decay = f.substr(start_index, len);
        isHiggsino = false;
    }
    // cout << "decay=" << decay << endl;

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

    // string tree_name = "EwkHiggsino2016__ntuple";
    string tree_name = "EwkNUHM22016__ntuple";

    TFile *file = new TFile(f.c_str());
    TTreeReader myReader(tree_name.c_str(), file);
    TTreeReaderValue<float> truth_mll(myReader, "mll");
    TTreeReaderValue<int> truth_preselection(myReader, "preselection");
    TTreeReaderValue<int> truth_is2LChannel(myReader, "is2LChannel");
    TTreeReaderValue<float> event_weight(myReader, "eventWeight");

    TTreeReaderValue<int> truth_var(myReader, var.c_str());
    // TTreeReaderValue<float> truth_var(myReader, var.c_str());
    // TTreeReaderValue<vector<float>> truth_var(myReader, var.c_str());
    // TTreeReaderValue<vector<float>> truth_var(myReader, "signalLeptons_pt");

    double xsec = get_cross_section(decay, n2, n1, m12, isHiggsino);
    double xsec_ratio = get_cross_section(decay, n2, n1, m12, false) / get_cross_section(decay, n2, n1, m12, true);
    double filterEff = get_filter_efficiency(decay, n2, n1, m12, isHiggsino);
    double lumi = get_luminosity();
    double sum_of_event_weight = get_sum_of_event_weight(decay, n2, n1, m12, isHiggsino);

    // cout << "xsec=" << xsec << endl;
    // cout << "xsec_ratio=" << xsec_ratio << endl;
    // cout << "filterEff=" << filterEff << endl;
    // cout << "lumi=" << lumi << endl;
    // cout << "sum_of_event_weight=" << sum_of_event_weight << endl;

    while (myReader.Next()) {
        double truthMll = *truth_mll;
        double eventWeight = *event_weight;

        int preselection = *truth_preselection;
        int is2LChannel = *truth_is2LChannel;

        double weight = func_NUHM2->Eval(truthMll) / func_Higgsino->Eval(truthMll); //ratio NUHM2/higgsino        
        double mc_weight = get_mc_weight(xsec, filterEff, lumi, eventWeight, sum_of_event_weight);

        // Uncomment this part for vector<float>
        // if (var.compare("baselineElectrons_pt") == 0 ||
        //     var.compare("baselineMuons_pt") == 0 ||
        //     var.compare("baselineJets_pt") == 0 ||
        //     var.compare("signalMuons_pt") == 0 ||
        //     var.compare("signalJets_pt") == 0 ||
        //     var.compare("signalBjets_pt") == 0 ||
        //     var.compare("baselineLeptons_pt") == 0 ||
        //     var.compare("signalLeptons_pt") == 0 ||
        //     var.compare("baselineElectrons_eta") == 0 ||
        //     var.compare("baselineMuons_eta") == 0 ||
        //     var.compare("baselineJets_eta") == 0 ||
        //     var.compare("signalElectrons_eta") == 0 ||
        //     var.compare("signalMuons_eta") == 0 ||
        //     var.compare("signalJets_eta") == 0 ||
        //     var.compare("signalBjets_eta") == 0 ||
        //     var.compare("baselineLeptons_eta") == 0 ||
        //     var.compare("signalLeptons_eta") == 0 ||
        //     var.compare("baselineElectrons_phi") == 0 ||
        //     var.compare("baselineMuons_phi") == 0 ||
        //     var.compare("baselineJets_phi") == 0 ||
        //     var.compare("signalElectrons_phi") == 0 ||
        //     var.compare("signalMuons_phi") == 0 ||
        //     var.compare("signalJets_phi") == 0 ||
        //     var.compare("signalBjets_phi") == 0 ||
        //     var.compare("baselineLeptons_phi") == 0 ||
        //     var.compare("signalLeptons_phi") == 0) {
        //     // special for pt, eta, and phi because they are vector<float> type
        //     int var_size = (*truth_var).size();
        //     for (int i_var = 0; i_var < var_size; i_var++) {
        //         double truthVar = (*truth_var)[i_var];
        //         if (preselection == 1 &&
        //             is2LChannel == 1) {
        //             if (truthMll < dm) {
        //                 if (!is_reweight) {// original
        //                     h1->Fill(truthVar, mc_weight);
        //                 }
        //                 else {// reweight
        //                     h1->Fill(truthVar, weight * mc_weight * xsec_ratio);
        //                 }
        //             }
        //         }
        //     }
        // }
        // else if (var.compare("pTLep1") == 0 ||
        //          var.compare("pTLep2") == 0) {
        //     double truthVar = 0;
        //     if (var.compare("pTLep1") == 0 &&
        //         (*truth_var).size() >= 1) {
        //         truthVar = (*truth_var)[0];
        //     }
        //     else if (var.compare("pTLep2") == 0 &&
        //              (*truth_var).size() >= 2) {
        //         truthVar = (*truth_var)[1];
        //     }
        //     if (preselection == 1 &&
        //         is2LChannel == 1) {
        //         if (truthMll < dm &&
        //             truthVar > 0) {
        //             if (!is_reweight) {// original
        //                 h1->Fill(truthVar, mc_weight);
        //             }
        //             else {// reweight
        //                 h1->Fill(truthVar, weight * mc_weight * xsec_ratio);
        //             }
        //         }
        //     }
        // }

        // Uncomment this part for int or float
        double truthVar = *truth_var;

        // cout << "truthMll=" << truthMll
        // << ", truthVar=" << truthVar
        // << ", weight=" << weight
        // << ", mc_weight=" << mc_weight
        // << endl;

        if (var.compare("HT30") == 0 ||
            var.compare("HTIncl") == 0 ||
            var.compare("HTLep12") == 0 ||
            var.compare("METOverHT") == 0 ||
            var.compare("meffIncl") == 0 ||
            var.compare("Rll") == 0 ||
            var.compare("dphiMin1") == 0 ||
            var.compare("mT") == 0 ||
            var.compare("mT2") == 0 ||
            var.compare("met") == 0 ||
            var.compare("mll") == 0 ||
            var.compare("pTll") == 0) {
            if (truthVar > 0. &&
                preselection == 1 &&
                is2LChannel == 1) {
                if (truthMll < dm) {
                    if (!is_reweight) {// original
                        h1->Fill(truthVar, mc_weight);
                    }
                    else {// reweight
                        h1->Fill(truthVar, weight * mc_weight * xsec_ratio);
                    }
                }
            }
        }
        else if (var.compare("MTauTau") == 0) {
            if (truthVar != 0 &&
                preselection == 1 &&
                is2LChannel == 1) {
                if (truthMll < dm) {
                    if (!is_reweight) {// original
                        h1->Fill(truthVar, mc_weight);
                    }
                    else {// reweight
                        h1->Fill(truthVar, weight * mc_weight * xsec_ratio);
                    }
                }
            }
        }
        else {
            if (preselection == 1 &&
                is2LChannel == 1) {
                if (truthMll < dm) {
                    if (!is_reweight) {// original
                        h1->Fill(truthVar, mc_weight);
                    }
                    else {// reweight
                        h1->Fill(truthVar, weight * mc_weight * xsec_ratio);
                    }
                }
            }
        }

    }

    return h1;
}

void get_nbins_xmin_xmax(string var, int &nbins, double &xmin, double &xmax)
{
    // Set the histogram ranges
    // int nbins = 0;
    // double xmin = 0., xmax = 0.;

    if (var.compare("baselineElectrons_pt") == 0 ||
        var.compare("baselineMuons_pt") == 0 ||
        // var.compare("baselineJets_pt") == 0 ||
        var.compare("signalMuons_pt") == 0 ||
        // var.compare("signalJets_pt") == 0 ||
        // var.compare("signalBjets_pt") == 0 ||
        var.compare("baselineLeptons_pt") == 0 ||
        var.compare("signalLeptons_pt") == 0 ||
        var.compare("pTLep1") == 0 ||
        var.compare("pTLep2") == 0) {
        nbins = 50;
        xmin = 0.;
        xmax = 100.;
    }
    else if (var.compare("baselineElectrons_eta") == 0 ||
             var.compare("baselineMuons_eta") == 0 ||
             var.compare("baselineJets_eta") == 0 ||
             var.compare("signalElectrons_eta") == 0 ||
             var.compare("signalMuons_eta") == 0 ||
             var.compare("signalJets_eta") == 0 ||
             var.compare("signalBjets_eta") == 0 ||
             var.compare("baselineLeptons_eta") == 0 ||
             var.compare("signalLeptons_eta") == 0) {
        nbins = 60;
        xmin = -3.;
        xmax = 3.;
    }
    else if (var.compare("baselineElectrons_phi") == 0 ||
             var.compare("baselineMuons_phi") == 0 ||
             var.compare("baselineJets_phi") == 0 ||
             var.compare("signalElectrons_phi") == 0 ||
             var.compare("signalMuons_phi") == 0 ||
             var.compare("signalJets_phi") == 0 ||
             var.compare("signalBjets_phi") == 0 ||
             var.compare("baselineLeptons_phi") == 0 ||
             var.compare("signalLeptons_phi") == 0) {
        nbins = 80;
        xmin = -4.;
        xmax = 4.;
    }
    else if (var.compare("met") == 0) {
        nbins = 50;
        xmin = 0.;
        xmax = 500.;
    }
    else if (var.compare("baselineJets_pt") == 0 ||
             var.compare("signalJets_pt") == 0 ||
             var.compare("signalBjets_pt") == 0) {
        nbins = 250;
        xmin = 0.;
        xmax = 500.;
    }
    else if (var.compare("nBaselineLeptons") == 0 ||
             var.compare("nBaselineElectrons") == 0 ||
             var.compare("nBaselineMuons") == 0 ||
             // var.compare("nBaselineTaus") == 0 ||
             var.compare("nSignalLeptons") == 0 ||
             var.compare("nElectrons") == 0 ||
             var.compare("nMuons") == 0) {
        nbins = 10;
        xmin = 0.;
        xmax = 10.;
    }
    else if (var.compare("nJets") == 0 ||
             var.compare("nJet30") == 0 ||
             var.compare("nJet25") == 0 ||
             var.compare("nBjets") == 0) {
        nbins = 10;
        xmin = 0.;
        xmax = 10.;
    }
    else if (var.compare("dphiMin1") == 0) {
        nbins = 50;
        xmin = 0.;
        xmax = 5.;
    }
    else if (var.compare("mT") == 0 ||
             var.compare("mT2") == 0) {
        nbins = 50;
        xmin = 0.;
        xmax = 100;
    }
    else if (var.compare("meffIncl") == 0) {
        nbins = 50;
        xmin = 0.;
        xmax = 1000.;
    }
    else if (var.compare("HTIncl") == 0 ||
             var.compare("HT30") == 0) {
        nbins = 50;
        xmin = 0.;
        xmax = 500.;
    }
    else if (var.compare("HTLep12") == 0) {
        nbins = 10;
        xmin = 0.;
        xmax = 50.;
    }
    else if (var.compare("METOverHT") == 0 ||
             var.compare("Rll") == 0) {
        nbins = 50;
        xmin = 0.;
        xmax = 5.;
    }
    else if (var.compare("mll") == 0 ||
             var.compare("pTll") == 0) {
        nbins = 100;
        xmin = 0.;
        xmax = 200.;
    }
    else if (var.compare("METOverHTLep12") == 0) {
        nbins = 200;
        xmin = 0.;
        xmax = 200.;
    }
    else if (var.compare("MTauTau") == 0) {
        nbins = 30;
        xmin = -300.;
        xmax = 300.;
    }
}

string get_x_title(string var)
{
    string x_title;
    if (var.compare("baselineElectrons_pt") == 0 ||
        var.compare("baselineMuons_pt") == 0 ||
        var.compare("baselineJets_pt") == 0 ||
        var.compare("signalMuons_pt") == 0 ||
        var.compare("signalJets_pt") == 0 ||
        var.compare("signalBjets_pt") == 0 ||
        var.compare("baselineLeptons_pt") == 0 ||
        var.compare("signalLeptons_pt") == 0) {
        x_title = "p_{T} [GeV]";
    }
    else if (var.compare("pTLep1") == 0) {
        x_title = "p_{T}(#font[12]{l}_{1}) [GeV]";
    }
    else if (var.compare("pTLep2") == 0) {
        x_title = "p_{T}(#font[12]{l}_{2}) [GeV]";
    }
    else if (var.compare("baselineElectrons_eta") == 0 ||
             var.compare("baselineMuons_eta") == 0 ||
             var.compare("baselineJets_eta") == 0 ||
             var.compare("signalElectrons_eta") == 0 ||
             var.compare("signalMuons_eta") == 0 ||
             var.compare("signalJets_eta") == 0 ||
             var.compare("signalBjets_eta") == 0 ||
             var.compare("baselineLeptons_eta") == 0 ||
             var.compare("signalLeptons_eta") == 0) {
        x_title = "#eta";
    }
    else if (var.compare("baselineElectrons_phi") == 0 ||
             var.compare("baselineMuons_phi") == 0 ||
             var.compare("baselineJets_phi") == 0 ||
             var.compare("signalElectrons_phi") == 0 ||
             var.compare("signalMuons_phi") == 0 ||
             var.compare("signalJets_phi") == 0 ||
             var.compare("signalBjets_phi") == 0 ||
             var.compare("baselineLeptons_phi") == 0 ||
             var.compare("signalLeptons_phi") == 0) {
        x_title = "#phi";
    }
    else if (var.compare("met") == 0) {
        x_title = "E^{miss}_{T} [GeV]";
    }
    else if (var.compare("nBaselineLeptons") == 0 ||
             var.compare("nBaselineElectrons") == 0 ||
             var.compare("nBaselineMuons") == 0 ||
             // var.compare("nBaselineTaus") == 0 ||
             var.compare("nSignalLeptons") == 0 ||
             var.compare("nElectrons") == 0 ||
             var.compare("nMuons") == 0 ||
             var.compare("nJets") == 0 ||
             var.compare("nJet30") == 0 ||
             var.compare("nJet25") == 0 ||
             var.compare("nBjets") == 0){
        x_title = "N_{" + var.substr(1) + "}";
    }
    else if (var.compare("dphiMin1") == 0) {
        // x_title = "#Delta#phi(E_{T}^{miss}, j_{1})";
        x_title = "#Delta#phi(#font[62]{p}^{j1}_{T}, #font[62]{p}^{miss}_{T})";
    }
    // else if (var.compare("mT") == 0 ||
    //          var.compare("mT2") == 0 ||
    //          var.compare("meffIncl") == 0 ||
    //          var.compare("HTIncl") == 0 ||
    //          var.compare("HT30") == 0 ||
    //          var.compare("HTLep12") == 0 ||
    //          var.compare("mll") == 0 ||
    //          var.compare("pTll") == 0 ||
    //          var.compare("MTauTau") == 0) {
    //     x_title = var + " [GeV]";
    // }
    else if (var.compare("mT") == 0) {
        x_title = "m_{T}(#font[12]{l}_{1}) [GeV]";
    }
    else if (var.compare("mT2") == 0) {
        x_title = "m_{T2}(#font[12]{l}_{1}, #font[12]{l}_{2}) [GeV]";
    }
    else if (var.compare("meffIncl") == 0) {
        x_title = "m_{eff}^{Incl} [GeV]";
    }
    else if (var.compare("HTIncl") == 0) {
        x_title = "H_{T}^{Incl} [GeV]";
    }
    else if (var.compare("HT30") == 0) {
        x_title = "H_{T}^{p_{T}^{jet}>30 GeV} [GeV]";
    }
    else if (var.compare("HTLep12") == 0) {
        x_title = "H_{T}^{lep12} [GeV]";
    }
    else if (var.compare("mll") == 0) {
        x_title = "m(#font[12]{l}#font[12]{l}) [GeV]";
    }
    else if (var.compare("pTll") == 0) {
        x_title = "p_{T}(#font[12]{l}#font[12]{l}) [GeV]";
    }
    else if (var.compare("MTauTau") == 0) {
        x_title = "m(#tau#tau) [GeV]";
    }
    else if (var.compare("METOverHT") == 0) {// ||
             // var.compare("METOverHTLep12") == 0) {
        // x_title = var;
        x_title = "E^{miss}_{T}/H^{p_{T}^{jet}>30 GeV}_{T}";
    }
    else if (var.compare("METOverHTLep12") == 0) {
        x_title = "E^{miss}_{T}/H^{leptons}_{T}";
    }
    else if (var.compare("Rll") == 0) {
        x_title = "#Delta R(#font[12]{l}#font[12]{l})";
    }

    // cout << x_title << endl;

    return x_title;
}

string get_y_title(string var)
{
    string y_title;
    if (var.compare("baselineElectrons_pt") == 0 ||
        var.compare("baselineMuons_pt") == 0 ||
        var.compare("baselineJets_pt") == 0 ||
        var.compare("signalMuons_pt") == 0 ||
        var.compare("signalJets_pt") == 0 ||
        var.compare("signalBjets_pt") == 0 ||
        var.compare("baselineLeptons_pt") == 0 ||
        var.compare("signalLeptons_pt") == 0 ||
        var.compare("pTLep1") == 0 ||
        var.compare("pTLep2") == 0) {
        y_title = "Events / 2 GeV";
    }
    else if (var.compare("baselineElectrons_eta") == 0 ||
             var.compare("baselineMuons_eta") == 0 ||
             var.compare("baselineJets_eta") == 0 ||
             var.compare("signalElectrons_eta") == 0 ||
             var.compare("signalMuons_eta") == 0 ||
             var.compare("signalJets_eta") == 0 ||
             var.compare("signalBjets_eta") == 0 ||
             var.compare("baselineLeptons_eta") == 0 ||
             var.compare("signalLeptons_eta") == 0 ||
             // phi
             var.compare("baselineElectrons_phi") == 0 ||
             var.compare("baselineMuons_phi") == 0 ||
             var.compare("baselineJets_phi") == 0 ||
             var.compare("signalElectrons_phi") == 0 ||
             var.compare("signalMuons_phi") == 0 ||
             var.compare("signalJets_phi") == 0 ||
             var.compare("signalBjets_phi") == 0 ||
             var.compare("baselineLeptons_phi") == 0 ||
             var.compare("signalLeptons_phi") == 0) {
        y_title = "Events";
    }
    else if (var.compare("nBaselineLeptons") == 0 ||
             var.compare("nBaselineElectrons") == 0 ||
             var.compare("nBaselineMuons") == 0 ||
             // var.compare("nBaselineTaus") == 0 ||
             var.compare("nSignalLeptons") == 0 ||
             var.compare("nElectrons") == 0 ||
             var.compare("nMuons") == 0 ||
             var.compare("nJets") == 0 ||
             var.compare("nJet30") == 0 ||
             var.compare("nJet25") == 0 ||
             var.compare("nBjets") == 0 ||
             var.compare("METOverHTLep12") == 0){
        y_title = "Events / 1";
    }
    else if (var.compare("dphiMin1") == 0 ||
             var.compare("Rll") == 0 ||
             var.compare("METOverHT") == 0) {
        y_title = "Events / 0.1";
    }
    else if (var.compare("mT") == 0 ||
             var.compare("mT2") == 0 ||
             var.compare("mll") == 0 ||
             var.compare("pTll") == 0) {
        y_title = "Events / 2 GeV";
    }
    else if (var.compare("HTLep12") == 0) {
        y_title = "Events / 5 GeV";
    }
    else if (var.compare("HTIncl") == 0 ||
             var.compare("HT30") == 0 ||
             var.compare("met") == 0) {
        y_title = "Events / 10 GeV";
    }
    else if (var.compare("meffIncl") == 0 ||
             var.compare("MTauTau") == 0) {
        y_title = "Events / 20 GeV";
    }

    return y_title;
}

void get_range_user(string var, double &range_user_xmin, double &range_user_xmax)
{
    if (var.compare("baselineElectrons_pt") == 0 ||
        var.compare("baselineMuons_pt") == 0 ||
        var.compare("baselineJets_pt") == 0 ||
        var.compare("signalMuons_pt") == 0 ||
        var.compare("signalJets_pt") == 0 ||
        var.compare("signalBjets_pt") == 0 ||
        var.compare("baselineLeptons_pt") == 0 ||
        var.compare("signalLeptons_pt") == 0 ||
        var.compare("pTLep1") == 0 ||
        var.compare("pTLep2") == 0) {
        range_user_xmin = 0.;
        range_user_xmax = 100.;
    }
    else if (var.compare("baselineElectrons_eta") == 0 ||
             var.compare("baselineMuons_eta") == 0 ||
             var.compare("baselineJets_eta") == 0 ||
             var.compare("signalElectrons_eta") == 0 ||
             var.compare("signalMuons_eta") == 0 ||
             var.compare("signalJets_eta") == 0 ||
             var.compare("signalBjets_eta") == 0 ||
             var.compare("baselineLeptons_eta") == 0 ||
             var.compare("signalLeptons_eta") == 0) {
        range_user_xmin = -3.;
        range_user_xmax = 3.;
    }
    else if (var.compare("baselineElectrons_phi") == 0 ||
             var.compare("baselineMuons_phi") == 0 ||
             var.compare("baselineJets_phi") == 0 ||
             var.compare("signalElectrons_phi") == 0 ||
             var.compare("signalMuons_phi") == 0 ||
             var.compare("signalJets_phi") == 0 ||
             var.compare("signalBjets_phi") == 0 ||
             var.compare("baselineLeptons_phi") == 0 ||
             var.compare("signalLeptons_phi") == 0) {
        range_user_xmin = -4;
        range_user_xmax = 4;
    }
    else if (var.compare("met") == 0 ||
             var.compare("HTIncl") == 0 ||
             var.compare("HT30") == 0) {
        range_user_xmin = 0.;
        range_user_xmax = 500.;
    }
    else if (var.compare("nBaselineLeptons") == 0 ||
             var.compare("nBaselineElectrons") == 0 ||
             var.compare("nBaselineMuons") == 0 ||
             // var.compare("nBaselineTaus") == 0 ||
             var.compare("nSignalLeptons") == 0 ||
             var.compare("nElectrons") == 0 ||
             var.compare("nMuons") == 0 ||
             var.compare("nJets") == 0 ||
             var.compare("nJet30") == 0 ||
             var.compare("nJet25") == 0 ||
             var.compare("nBjets") == 0){
        range_user_xmin = 0.;
        range_user_xmax = 10.;
    }
    else if (var.compare("dphiMin1") == 0 ||
             var.compare("METOverHT") == 0 ||
             var.compare("Rll") == 0) {
        range_user_xmin = 0.;
        range_user_xmax = 5.;
    }
    else if (var.compare("mT") == 0 ||
             var.compare("mT2") == 0 ||
             var.compare("mll") == 0 ||
             var.compare("pTll") == 0) {
        range_user_xmin = 0.;
        range_user_xmax = 100.;
    }
    else if (var.compare("meffIncl") == 0) {
        range_user_xmin = 0.;
        range_user_xmax = 1000.;
    }
    else if (var.compare("MTauTau") == 0) {
        range_user_xmin = -300.;
        range_user_xmax = 300.;
    }
    else if (var.compare("HTLep12") == 0 ||
             var.compare("METOverHTLep12") == 0) {
        range_user_xmin = 0.;
        range_user_xmax = 50.;
    }
}

void ATLASLabel(Double_t x, Double_t y, const char* text, Color_t color)
{
    TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize);
    l.SetNDC();
    l.SetTextFont(72);
    l.SetTextColor(color);

    double delx = 0.085*696*gPad->GetWh()/(472*gPad->GetWw());

    l.DrawLatex(x,y,"ATLAS");
    if (text) {
        TLatex p;
        p.SetNDC();
        p.SetTextFont(42);
        p.SetTextColor(color);
        p.DrawLatex(x+delx,y,text);
        // p.DrawLatex(x,y,"#sqrt{s}=900GeV");
    }
}
