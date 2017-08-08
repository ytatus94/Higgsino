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

    TFile *f1 = new TFile(file.c_str());

    h_name = "h_" + var;
    TH1F  *h1 = new TH1F(h_name.c_str(), var.c_str(), nbins, xmin, xmax);

    TTree *t1 = (TTree *)f1->Get("EwkHiggsino2016__ntuple");
    t1->Project(h_name.c_str(), var.c_str(), cut.c_str());

    return h1;
}

TH1F *get_combined_hist(string f_N2N1, string f_C1C1, string f_N2C1p, string f_N2C1m)
{
    TH1F *h_N2N1  = (TH1F *)get_histogram(f_N2N1);
    TH1F *h_C1C1  = (TH1F *)get_histogram(f_C1C1);
    TH1F *h_N2C1p = (TH1F *)get_histogram(f_N2C1p);
    TH1F *h_N2C1m = (TH1F *)get_histogram(f_N2C1m);

    double integral_N2N1  = h_N2N1->Integral();
    double integral_C1C1  = h_C1C1->Integral();
    double integral_N2C1p = h_N2C1p->Integral();
    double integral_N2C1m = h_N2C1m->Integral();

    h_N2N1->Scale(1./integral_N2N1);
    h_C1C1->Scale(1./integral_C1C1);
    h_N2C1p->Scale(1./integral_N2C1p);
    h_N2C1m->Scale(1./integral_N2C1m);

    h_N2N1->Scale(integral_N2N1 / (integral_N2N1 + integral_C1C1 + integral_N2C1p + integral_N2C1m) );
    h_C1C1->Scale(integral_C1C1 / (integral_N2N1 + integral_C1C1 + integral_N2C1p + integral_N2C1m) );
    h_N2C1p->Scale(integral_N2C1p / (integral_N2N1 + integral_C1C1 + integral_N2C1p + integral_N2C1m) );
    h_N2C1m->Scale(integral_N2C1m / (integral_N2N1 + integral_C1C1 + integral_N2C1p + integral_N2C1m) );

    TH1F *h_Combined = (TH1F *)h_N2N1->Clone();
    h_Combined->Add(h_C1C1);
    h_Combined->Add(h_N2C1p);
    h_Combined->Add(h_N2C1m);

    h_Combined->SetLineColor(kBlack);
    h_Combined->SetFillColor(kBlack);
    h_Combined->SetFillStyle(0); // hollow
    h_Combined->SetXTitle("m_{ll} [GeV]");
    h_Combined->SetYTitle("Normalized event counts");

    return h_Combined;
}
