#include <TROOT.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TLegend.h>
#include <TH1.h>
#include <TF1.h>

#include "FuncMllDistr.C"

#include <string>
#include <iostream>

void test_Higgsino_170_150_m12_600()
{
    TF1 *f1 = new TF1("f1", FuncMllDistr, 0, 20, 3);
    // f1->SetParameters(1., 150., -170.);
    f1->SetParameters(1.31473, 150., -170.);
    double area_f1 = f1->Integral(0, 20);
    // f1->SetParameter(0, 1./area_f1);
    // double area_f1_new = f1->Integral(0, 20);

    TF1 *f2 = new TF1("f2", FuncMllDistr, 0, 22, 3);
    f2->SetParameters(1., 137.607727, -159.657379);
    double area_f2 = f2->Integral(0, 22);

    cout << "area_f1=" << area_f1 << ", area_f2=" << area_f2 << endl;
    // cout << "area_f1_new=" << area_f1_new << endl;
    cout << "area_f1 / area_f2=" << area_f1 / area_f2 << endl;
    cout << "area_f2 / area_f1=" << area_f2 / area_f1 << endl;
}
