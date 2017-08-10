#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TTree.h>

#include "FuncMllDistr.C"

#include <string>
#include <iostream>
using namespace std;

void test_120_100()
{
    TFile *file1 = new TFile("/Users/ytshen/Desktop/MGPy8EG_A14N23LO_SM_Higgsino_120_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root");
    TH1F *hist = new TH1F("hist", "", 25, 0, 25);
    TTree *tree = (TTree *)file1->Get("MGPy8EG_A14N23LO_SM_Higgsino_120_100_2LMET50_MadSpin_NoSys");
    tree->Project("hist", "truthMll", "truthMll>0");
    hist->Draw();
    double area = hist->Integral(0, 20);
    cout << "area=" << area << endl;
    TH1F *h2 = new TH1F("h2", "", 25, 0, 25);
    double par[3] = {1., 100., -120.};
    for (double i = 0; i <= 20; i++) {
        double var = FuncMllDistr(&i, par);
        int bin = h2->GetXaxis()->FindBin(i);
        // cout << "i=" << i << ", bin=" << bin << ", var=" << var << endl;
        h2->SetBinContent(bin, var);
    }
    double area_h2 = h2->Integral(0, 20);
    cout << "area_h2=" << area_h2 << endl;
    h2->Scale(1./area_h2);
    h2->Scale(area);
    h2->SetLineColor(kRed);
    h2->Draw("same");
    TF1 *func = new TF1("func", FuncMllDistr, 0, 20, 3);
    func->SetParameters(1.,100., -120.);
    func->SetLineColor(kGreen);
    double area_func = func->Integral(0,20);
    cout << "area_func=" << area_func << endl;
    TF1 *f2 = new TF1("f2", FuncMllDistr, 0, 20, 3);
    f2->SetParameters(area/area_func, 100.,-120.);
    f2->SetLineColor(kGreen);
    f2->Draw("same");
}
