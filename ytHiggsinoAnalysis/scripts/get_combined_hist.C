#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TTree.h>

#include <string>

TH1F *get_histogram(string file)
{
    // Get the combined histogram
    string var = "mll";
    int    nbins = 200.;
    double xmin  = 0.;
    double xmax  = 200.;
    string cut = "";

    // string tree_name = "EwkHiggsino2016__ntuple";
    string tree_name = "EwkNUHM22016__ntuple";

    TFile *f1 = new TFile(file.c_str());

    h_name = "h_" + var;
    TH1F  *h1 = new TH1F(h_name.c_str(), var.c_str(), nbins, xmin, xmax);

    TTree *t1 = (TTree *)f1->Get(tree_name.c_str());
    t1->Project(h_name.c_str(), var.c_str(), cut.c_str());

    return h1;
}

TH1F *get_histogram(string file, string Var, int Nbins, double Xmin, double Xmax, string Cut)
{
    // Get the combined histogram
    string var = Var;
    int    nbins = Nbins;
    double xmin  = Xmin;
    double xmax  = Xmax;
    string cut = Cut;

    // string tree_name = "EwkHiggsino2016__ntuple";
    string tree_name = "EwkNUHM22016__ntuple";

    TFile *f1 = new TFile(file.c_str());

    h_name = "h_" + var;
    TH1F  *h1 = new TH1F(h_name.c_str(), var.c_str(), nbins, xmin, xmax);

    TTree *t1 = (TTree *)f1->Get(tree_name.c_str());
    t1->Project(h_name.c_str(), var.c_str(), cut.c_str());

    return h1;
}

TH1F *combine_histogram(TH1F *h1, TH1F *h2, TH1F *h3, TH1F *h4 = NULL)
{
    double integral_h1 = h1->Integral();
    double integral_h2 = h2->Integral();
    double integral_h3 = h3->Integral();
    double integral_h4 = 0;
    if (h4) // h4 is not empty
        integral_h4 = h4->Integral();

    double sum = integral_h1 + integral_h2 + integral_h3 + integral_h4;

    h1->Scale(1./integral_h1);
    h2->Scale(1./integral_h2);
    h3->Scale(1./integral_h3);
    if (h4)
        h4->Scale(1./integral_h4);

    h1->Scale(integral_h1 / sum);
    h2->Scale(integral_h2 / sum);
    h3->Scale(integral_h3 / sum);
    if (h4)
        h4->Scale(integral_h4 / sum);

    TH1F *h_combined = (TH1F *)h1->Clone();
    h_combined->Add(h2);
    h_combined->Add(h3);
    if (h4)
        h_combined->Add(h4);
    h_combined->SetName("h_combined");

    return h_combined;
}

TH1F *get_combined_hist(string f_N2N1, string f_C1C1, string f_N2C1p, string f_N2C1m)
{
    TH1F *h_N2N1  = (TH1F *)get_histogram(f_N2N1);
    TH1F *h_C1C1  = (TH1F *)get_histogram(f_C1C1);
    TH1F *h_N2C1p = (TH1F *)get_histogram(f_N2C1p);
    TH1F *h_N2C1m = (TH1F *)get_histogram(f_N2C1m);

    TH1F *h_Combined = combine_histogram(h_N2N1, h_C1C1, h_N2C1p, h_N2C1m);

    h_Combined->SetLineColor(kBlack);
    h_Combined->SetFillColor(kBlack);
    h_Combined->SetFillStyle(0); // hollow
    h_Combined->SetXTitle("m_{ll} [GeV]");
    h_Combined->SetYTitle("Normalized event counts");

    return h_Combined;
}
