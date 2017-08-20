#include <TROOT.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1.h>
#include <TF1.h>

#include "get_combined_hist.C"
#include "FuncMllDistr.C"
#include "ytUtility.C"

#include <string>

void test_fit(string n2_n1, int m12, string var = "mll")
{
    string path_higgsino = "/Users/ytshen/Desktop/20170817/";

    string f_higgsino_N2N1 = "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root";
    string f_higgsino_C1C1 = "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root";
    string f_higgsino_N2C1p = "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string f_higgsino_N2C1m = "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    double n2 = stod(n2_n1.substr(0, n2_n1.find("_"))); // stod() converts string to double
    double n1 = stod(n2_n1.substr(n2_n1.find("_") + 1, n2_n1.length()));
    double dm_higgsino = n2 - n1;

    string path_nuhm2 = "/Users/ytshen/Desktop/20170817/";

    string f_nuhm2_N2N1 = "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    string f_nuhm2_C1C1 = "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string f_nuhm2_N2C1p = "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string f_nuhm2_N2C1m = "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    double dm_nuhm2 = get_dm_NUHM2(m12);

    string file1 = path_higgsino + f_higgsino_N2N1;
    string file2 = path_higgsino + f_higgsino_C1C1;
    string file3 = path_higgsino + f_higgsino_N2C1p;
    string file4 = path_higgsino + f_higgsino_N2C1m;
    string file5 = path_nuhm2 + f_nuhm2_N2N1;
    string file6 = path_nuhm2 + f_nuhm2_C1C1;
    string file7 = path_nuhm2 + f_nuhm2_N2C1p;
    string file8 = path_nuhm2 + f_nuhm2_N2C1m;

    TCanvas *canvas =  new TCanvas("c","", 800,600);
    canvas->SetLeftMargin(0.12);
    // bool logY = true;
    bool logY = false;
    bool stat_box = false;

    if (logY)
        gPad->SetLogy();

    if (stat_box)
        gStyle->SetOptFit(1111);

    double xrange_max = 0.;
    if (m12 <= 400)
        xrange_max = 100.;
    else
        xrange_max = 50.;

    TH1F *h_higgsino = (TH1F *)get_combined_hist(file1, file2, file3, file4);
    // h_higgsino->SetLineColor(kBlack);
    h_higgsino->SetLineColor(kGreen);
    h_higgsino->SetTitle("");
    h_higgsino->GetXaxis()->SetRangeUser(0, xrange_max);
    h_higgsino->GetYaxis()->SetTitleOffset(1.3);
    h_higgsino->SetName("h_higgsino");
    if (!stat_box)
        h_higgsino->SetStats(0); // no stats box

    TH1F *h_nuhm2 = (TH1F *)get_combined_hist(file5, file6, file7, file8);
    // h_nuhm2->SetLineColor(kBlue);
    h_nuhm2->SetLineColor(kBlue);
    h_nuhm2->GetYaxis()->SetTitleOffset(1.2);
    h_nuhm2->SetName("h_nuhm2");
    if (!stat_box)
        h_nuhm2->SetStats(0); // no stats box

    double max_value = 0;
    if (logY)
        max_value = max(h_higgsino->GetMaximum(), h_nuhm2->GetMaximum()) * 10;
    else
        max_value = max(h_higgsino->GetMaximum(), h_nuhm2->GetMaximum()) * 1.2;

    h_higgsino->SetMinimum(0.0001);
    h_higgsino->SetMaximum(max_value);
    h_higgsino->Draw("hist");
    h_nuhm2->Draw("hist,same");

    // Method 1
    // Use a Gaussian to fit the core and an exponential function to fit the tail
    // Firstly, fit core and tail separately to get the parameters,
    // then use the parameters as initial parameters for combined fit.

    // Fitting histogram (with predefined function):
    // TF1 *fit_higgsino_core = new TF1("fit_higgsino_core", "gaus", 0., dm_higgsino);
    // fit_higgsino_core->SetLineColor(kRed-8);
    // fit_higgsino_core->SetLineWidth(3);
    TF1 *fit_higgsino_core = new TF1("fit_higgsino_core", FuncMllDistr, 0, dm_higgsino, 3); // need to provide number of parameters as the last argument
    fit_higgsino_core->SetParameters(1, n1, -1.*n2); // n1 and n2 should be opposite sign
    // fit_higgsino_core.FixParameter(1, n1)
    // fit_higgsino_core.FixParameter(2, -1.*n2)
    // fit_higgsino_core->SetLineColor(kRed-8);
    fit_higgsino_core->SetLineColor(kGreen);
    fit_higgsino_core->SetLineWidth(3);
    h_higgsino->Fit(fit_higgsino_core, "R0");// “R” Use the range specified in the function range
    h_higgsino->Fit(fit_higgsino_core, "R0");
    h_higgsino->Fit(fit_higgsino_core, "R0+");
    double *higgsino_core_parameters = fit_higgsino_core->GetParameters();

    fit_higgsino_core->SetLineStyle(2);
    fit_higgsino_core->Draw("same");

    // TF1 *fit_higgsino_tail = new TF1("fit_higgsino_tail", "expo", dm_higgsino, h_higgsino->GetXaxis()->GetXmax());
    // fit_higgsino_tail->SetLineColor(kRed-8);
    // fit_higgsino_tail->SetLineWidth(3);
    // h_higgsino->Fit(fit_higgsino_tail, "R0");
    // h_higgsino->Fit(fit_higgsino_tail, "R0");
    // h_higgsino->Fit(fit_higgsino_tail, "R0+");
    // double *higgsino_tail_parameters = fit_higgsino_tail->GetParameters();

    // fit_higgsino_tail->Draw("same");

    // TF1 *fit_higgsino_total = new TF1("fit_higgsino_total", "gaus(0)+expo(3)", h_higgsino->GetXaxis()->GetXmin(), h_higgsino->GetXaxis()->GetXmax());
    // fit_higgsino_total->SetLineColor(kRed-8);
    // fit_higgsino_total->SetLineWidth(3);
    // fit_higgsino_total->SetParameters(higgsino_core_parameters[0],
    //                                   higgsino_core_parameters[1],
    //                                   higgsino_core_parameters[2],
    //                                   higgsino_tail_parameters[0], 
    //                                   higgsino_tail_parameters[1]);
    // h_higgsino->Fit(fit_higgsino_total, "R0");
    // h_higgsino->Fit(fit_higgsino_total, "R0");
    // h_higgsino->Fit(fit_higgsino_total, "R+");

    // fit_higgsino_total->Draw("same");

    // TPaveStats *ps1 = (TPaveStats *)h_higgsino->GetListOfFunctions()->FindObject("stats");
    // ps1->SetX1NDC(.2);
    // ps1->SetX2NDC(.4);
    // ps1->SetY1NDC(.7);
    // ps1->SetY2NDC(.9);
    // ps1->SetTextColor(4);
    // gPad->Modified();

    // Fitting histogram (with predefined function):
    // TF1 *fit_nuhm2_core = new TF1("fit_nuhm2_core", "gaus", 0, dm_nuhm2);
    TF1 *fit_nuhm2_core = new TF1("fit_nuhm2_core", FuncMllDistr, 0, dm_nuhm2, 3); // need to provide number of parameters as the last argument
    fit_nuhm2_core->SetParameters(1, n1, -1.*n2); // n1 and n2 should be opposite sign
    // fit_nuhm2_core->SetLineColor(kGreen-7);
    fit_nuhm2_core->SetLineColor(kBlue);
    fit_nuhm2_core->SetLineWidth(3);
    h_nuhm2->Fit(fit_nuhm2_core, "R0");
    h_nuhm2->Fit(fit_nuhm2_core, "R0");
    h_nuhm2->Fit(fit_nuhm2_core, "R0+");
    double *nuhm2_core_parameters = fit_nuhm2_core->GetParameters();

    fit_nuhm2_core->SetLineStyle(2);
    fit_nuhm2_core->Draw("same");

    // TF1 *fit_nuhm2_tail = new TF1("fit_nuhm2_tail", "expo", dm_nuhm2, h_nuhm2->GetXaxis()->GetXmax());
    // fit_nuhm2_tail->SetLineColor(kGreen-7);
    // fit_nuhm2_tail->SetLineWidth(3);
    // h_nuhm2->Fit(fit_nuhm2_tail, "R0");
    // h_nuhm2->Fit(fit_nuhm2_tail, "R0");
    // h_nuhm2->Fit(fit_nuhm2_tail, "R0+");
    // double *nuhm2_tail_parameters = fit_nuhm2_tail->GetParameters();

    // fit_nuhm2_tail->Draw("same");

    // TF1 *fit_nuhm2_total = new TF1("fit_nuhm2_total", "gaus(0)+expo(3)", h_nuhm2->GetXaxis()->GetXmin(), h_nuhm2->GetXaxis()->GetXmax());
    // fit_nuhm2_total->SetLineColor(kGreen-7);
    // fit_nuhm2_total->SetLineWidth(3);
    // fit_nuhm2_total->SetParameters(nuhm2_core_parameters[0],
    //                               nuhm2_core_parameters[1],
    //                               nuhm2_core_parameters[2],
    //                               nuhm2_tail_parameters[0], 
    //                               nuhm2_tail_parameters[1]);
    // h_nuhm2->Fit(fit_nuhm2_total, "R0");
    // h_nuhm2->Fit(fit_nuhm2_total, "R0");
    // h_nuhm2->Fit(fit_nuhm2_total, "R+");

    // fit_nuhm2_total->Draw("same");

    // TPaveStats *ps2 = (TPaveStats *)h_nuhm2->->GetListOfFunctions()->FindObject("stats");
    // ps2->SetX1NDC(.5);
    // ps2->SetX2NDC(.9);
    // ps2->SetY1NDC(.3);
    // ps2->SetY2NDC(.5);
    // ps2->SetTextColor(2);
    // gPad->Modified();

    TLegend *legend = new TLegend(0.6, 0.6, 0.9, 0.8);
    legend->AddEntry(h_higgsino, ("Higgsino" + n2_n1).c_str(), "l");
    legend->AddEntry(h_nuhm2, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    // legend->AddEntry(fit_higgsino_total, "fitting Higgsino", "l");
    // legend->AddEntry(fit_nuhm2_total, "fitting NUHM2", "l");
    legend->AddEntry(fit_higgsino_core, "fitting Higgsino", "l");
    legend->AddEntry(fit_nuhm2_core, "fitting NUHM2", "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    // AtlasStyle.ATLASLabel(0.15, 0.85, "internal", ROOT.kBlack)

    string output = "fit_" + var + "_" + to_string(m12) + ".pdf";
    canvas->SaveAs(output.c_str());
}
