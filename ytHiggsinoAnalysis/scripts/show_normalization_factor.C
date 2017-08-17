#include <TROOT.h>
#include <TF1.h>
#include "FuncMllDistr_modified.C"
#include <iostream>

void show_normalization_factor()
{
    // Higgsino 140_100
    TF1 *f1 = new TF1("f1", FuncMllDistr, 0, 40, 3);
    f1->SetParameters(1., 100., -140.);
    double area_f1 = f1->Integral(0, 40);
    cout << "Higgsino 140_100: area_f1=" << area_f1 << endl;
    // Higgsino 160_100
    TF1 *f2 = new TF1("f2", FuncMllDistr, 0, 60, 3);
    f2->SetParameters(1., 100, -160.);
    double area_f2 = f2->Integral(0, 60);
    cout << "Higgsino 160_100: area_f2=" << area_f2 << endl;
    // Higgsino 170_150
    TF1 *f3 = new TF1("f3", FuncMllDistr, 0, 20, 3);
    f3->SetParameters(1., 150, -170.);
    double area_f3 = f3->Integral(0, 20);
    cout << "Higgsino 170_150: area_f3=" << area_f3 << endl;

    // NUHM2 m12=300
    TF1 *f4 = new TF1("f4", FuncMllDistr, 0, 55.676391, 3);
    f4->SetParameters(1., 105.631409, -161.307800);
    double area_f4 = f4->Integral(0, 55.676391);
    cout << "NUHM2 m12=300: area_f4=" << area_f4 << endl;
    // NUHM2 m12=350
    TF1 *f5 = new TF1("f5", FuncMllDistr, 0, 46.057022, 3);
    f5->SetParameters(1., 115.618103, -161.675125);
    double area_f5 = f5->Integral(0, 46.057022);
    cout << "NUHM2 m12=350: area_f5=" << area_f5 << endl;
    // NUHM2 m12=400
    TF1 *f6 = new TF1("f6", FuncMllDistr, 0, 38.168159, 3);
    f6->SetParameters(1., 122.974541, -161.142700);
    double area_f6 = f6->Integral(0, 38.168159);
    cout << "NUHM2 m12=400: area_f6=" << area_f6 << endl;
    // NUHM2 m12=500
    TF1 *f7 = new TF1("f7", FuncMllDistr, 0, 28.016555, 3);
    f7->SetParameters(1., 132.279099, -160.295654);
    double area_f7 = f7->Integral(0, 28.016555);
    cout << "NUHM2 m12=500: area_f7=" << area_f7 << endl;
    // NUHM2 m12=600
    TF1 *f8 = new TF1("f8", FuncMllDistr, 0, 22.049652, 3);
    f8->SetParameters(1., 137.607727, -159.657379);
    double area_f8 = f8->Integral(0, 22.049652);
    cout << "NUHM2 m12=600: area_f8=" << area_f8 << endl;
    // NUHM2 m12=700
    TF1 *f9 = new TF1("f9", FuncMllDistr, 0, 18.192032, 3);
    f9->SetParameters(1., 140.978836, -159.170868);
    double area_f9 = f9->Integral(0, 18.192032);
    cout << "NUHM2 m12=700: area_f9=" << area_f9 << endl;
    // NUHM2 m12=800
    TF1 *f10 = new TF1("f10", FuncMllDistr, 0, 15.495697, 3);
    f10->SetParameters(1., 143.288208, -158.783905);
    double area_f10 = f10->Integral(0, 15.495697);
    cout << "NUHM2 m12=800: area_f10=" << area_f10 << endl;

    cout << "Area ratio:" << endl;
    cout << "NUHM2 m12=300 / Higgsino 160_100: area_f4/area_f2=" << area_f4 / area_f2 << endl;
    cout << "NUHM2 m12=350 / Higgsino 140_100: area_f5/area_f1=" << area_f5 / area_f1 << endl;
    cout << "NUHM2 m12=400 / Higgsino 140_100: area_f6/area_f1=" << area_f6 / area_f1 << endl;
    cout << "NUHM2 m12=500 / Higgsino 170_150: area_f7/area_f3=" << area_f7 / area_f3 << endl;
    cout << "NUHM2 m12=600 / Higgsino 170_150: area_f8/area_f3=" << area_f8 / area_f3 << endl;
    cout << "NUHM2 m12=700 / Higgsino 170_150: area_f9/area_f3=" << area_f9 / area_f3 << endl;
    cout << "NUHM2 m12=800 / Higgsino 170_150: area_f10/area_f3=" << area_f10 / area_f3 << endl;
}

