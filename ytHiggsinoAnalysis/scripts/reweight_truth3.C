#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TLegend.h>

// #include "FuncMllDistr.C"
#include "get_combined_hist.C"

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

// Masses of N1, N2 for NUHM2
double par_NUHM2_m12_300[2] = {105.631409, 161.307800};
double par_NUHM2_m12_350[2] = {115.618103, 161.675125};
double par_NUHM2_m12_400[2] = {122.974541, 161.142700};
double par_NUHM2_m12_500[2] = {132.279099, 160.295654};
double par_NUHM2_m12_600[2] = {137.607727, 159.657379};
double par_NUHM2_m12_700[2] = {140.978836, 159.170868};
double par_NUHM2_m12_800[2] = {143.288208, 158.783905};

// Declare functions
double FuncMllDistr(double *, double *);
double get_dm_NUHM2(int);
double get_NUHM2_N1_mass(int);
double get_NUHM2_N2_mass(int);
void plot(int, int, int);

// main function
void reweight_truth3()
{
    // plot(100, 160, 300);
    plot(100, 160, 350);
    plot(100, 160, 400);
    plot(150, 190, 500);
    plot(150, 190, 600);
    plot(150, 170, 700);
    plot(150, 170, 800);
}

double FuncMllDistr(double *x, double *par)
{
    double m1 = par[1];
    double m2 = par[2];
    double mu = m2 - m1;
    double m = x[0];
    double M = m1 + m2;
    double m_Z = 91;
    double norm = par[0] * m;
    double var = 0;
    double delta = fabs(m2) - fabs(m1);
    //cout<<"m "<<m <<" mu "<<mu<<endl;

    if (m < delta){
        double radice=sqrt( pow(m,4) -pow(m,2)*(pow(mu,2) + pow(M,2) ) + pow(mu*M,2) );

        double normalizzazione = pow(  pow(m,2) -pow(m_Z,2),2);
        var= (norm* radice)/ normalizzazione  ;
        var = var* (-2*pow(m,4)+ pow(m,2)*(2*pow(M,2) - pow(mu,2)) +pow((mu*M),2));
    }

    return var;
}

double get_dm_NUHM2(int m12)
{
    double dm_NUHM2 = 0.;
    if (m12 == 300)
        dm_NUHM2 = par_NUHM2_m12_300[1] - par_NUHM2_m12_300[0];
    else if (m12 == 350)
        dm_NUHM2 = par_NUHM2_m12_350[1] - par_NUHM2_m12_350[0];
    else if (m12 == 400)
        dm_NUHM2 = par_NUHM2_m12_400[1] - par_NUHM2_m12_400[0];
    else if (m12 == 500)
        dm_NUHM2 = par_NUHM2_m12_500[1] - par_NUHM2_m12_500[0];
    else if (m12 == 600)
        dm_NUHM2 = par_NUHM2_m12_600[1] - par_NUHM2_m12_600[0];
    else if (m12 == 700)
        dm_NUHM2 = par_NUHM2_m12_700[1] - par_NUHM2_m12_700[0];
    else if (m12 == 800)
        dm_NUHM2 = par_NUHM2_m12_800[1] - par_NUHM2_m12_800[0];
    return dm_NUHM2;
}

double get_NUHM2_N1_mass(int m12)
{
    double mass_N1 = 0;
    if (m12 == 300)
        mass_N1 = par_NUHM2_m12_300[0];
    else if (m12 == 350)
        mass_N1 = par_NUHM2_m12_350[0];
    else if (m12 == 400)
        mass_N1 = par_NUHM2_m12_400[0];
    else if (m12 == 500)
        mass_N1 = par_NUHM2_m12_500[0];
    else if (m12 == 600)
        mass_N1 = par_NUHM2_m12_600[0];
    else if (m12 == 700)
        mass_N1 = par_NUHM2_m12_700[0];
    else if (m12 == 800)
        mass_N1 = par_NUHM2_m12_800[0];
    return mass_N1;
}

double get_NUHM2_N2_mass(int m12)
{
    double mass_N2 = 0;
    if (m12 == 300)
        mass_N2 = par_NUHM2_m12_300[1];
    else if (m12 == 350)
        mass_N2 = par_NUHM2_m12_350[1];
    else if (m12 == 400)
        mass_N2 = par_NUHM2_m12_400[1];
    else if (m12 == 500)
        mass_N2 = par_NUHM2_m12_500[1];
    else if (m12 == 600)
        mass_N2 = par_NUHM2_m12_600[1];
    else if (m12 == 700)
        mass_N2 = par_NUHM2_m12_700[1];
    else if (m12 == 800)
        mass_N2 = par_NUHM2_m12_800[1];
    return mass_N2;
}

void plot(int n1, int n2, int m12)
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
    string path_Higgsino = "/Users/ytshen/Desktop/20170810/";
    string n2_n1 = to_string(n2) + "_" + to_string(n1);

    string f_Higgsino_N2N1 = "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root";
    // string f_Higgsino_C1C1 = "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1p = "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1m = "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    TFile *file_Higgsino_N2N1 = new TFile( (path_Higgsino + f_Higgsino_N2N1).c_str() );
    // TFile *file_Higgsino_C1C1 = new TFile( (path_Higgsino + f_Higgsino_C1C1).c_str() );
    TFile *file_Higgsino_N2C1p = new TFile( (path_Higgsino + f_Higgsino_N2C1p).c_str() );
    TFile *file_Higgsino_N2C1m = new TFile( (path_Higgsino + f_Higgsino_N2C1m).c_str() );

    TTreeReader Reader_Higgsino_N2N1("EwkHiggsino2016__ntuple", file_Higgsino_N2N1);
    // TTreeReader Reader_Higgsino_C1C1("EwkHiggsino2016__ntuple", file_Higgsino_C1C1);
    TTreeReader Reader_Higgsino_N2C1p("EwkHiggsino2016__ntuple", file_Higgsino_N2C1p);
    TTreeReader Reader_Higgsino_N2C1m("EwkHiggsino2016__ntuple", file_Higgsino_N2C1m);

    TTreeReaderValue<float> truth_mll_Higgsino_N2N1(Reader_Higgsino_N2N1, "mll");
    // TTreeReaderValue<float> truth_mll_Higgsino_C1C1(Reader_Higgsino_C1C1, "mll");
    TTreeReaderValue<float> truth_mll_Higgsino_N2C1p(Reader_Higgsino_N2C1p, "mll");
    TTreeReaderValue<float> truth_mll_Higgsino_N2C1m(Reader_Higgsino_N2C1m, "mll");

    TH1F *h_Higgsino_N2N1_original = new TH1F("h_Higgsino_N2N1_original", "", 200, 0, 200);
    // TH1F *h_Higgsino_C1C1_original = new TH1F("h_Higgsino_C1C1_original", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1p_original = new TH1F("h_Higgsino_N2C1p_original", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1m_original = new TH1F("h_Higgsino_N2C1m_original", "", 200, 0, 200);

    TH1F *h_Higgsino_N2N1_reweight = new TH1F("h_Higgsino_N2N1_reweight", "", 200, 0, 200);
    // TH1F *h_Higgsino_C1C1_reweight = new TH1F("h_Higgsino_C1C1_reweight", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1p_reweight = new TH1F("h_Higgsino_N2C1p_reweight", "", 200, 0, 200);
    TH1F *h_Higgsino_N2C1m_reweight = new TH1F("h_Higgsino_N2C1m_reweight", "", 200, 0, 200);

    while (Reader_Higgsino_N2N1.Next()) {
        double truthMll = *truth_mll_Higgsino_N2N1;
        if (truthMll < dm_Higgsino) {
            h_Higgsino_N2N1_original->Fill(truthMll);
            double weight = func_NUHM2->Eval(truthMll) / func_Higgsino->Eval(truthMll); //ratio NUHM2/higgsino
            // if (weight > 10) {
            //     cout << "N2N1 truthMll=" << truthMll
            //     << ", weight=" << weight
            //     << ", func_NUHM2->Eval(truthMll)=" << func_NUHM2->Eval(truthMll)
            //     << ", func_Higgsino->Eval(truthMll)=" << func_Higgsino->Eval(truthMll)
            //     << endl;
            // }
            h_Higgsino_N2N1_reweight->Fill(truthMll, weight);
        }
    }
    // while (Reader_Higgsino_C1C1.Next()) {
    //     double truthMll = *truth_mll_Higgsino_C1C1;
    //     if (truthMll < dm_Higgsino) {
    //         h_Higgsino_C1C1_original->Fill(truthMll);
    //         double weight = func_NUHM2->Eval(truthMll) / func_Higgsino->Eval(truthMll); //ratio NUHM2/higgsino
    //         if (weight > 10) {
    //             cout << "C1C1 truthMll=" << truthMll
    //             << ", weight=" << weight
    //             << ", func_NUHM2->Eval(truthMll)=" << func_NUHM2->Eval(truthMll)
    //             << ", func_Higgsino->Eval(truthMll)=" << func_Higgsino->Eval(truthMll)
    //             << endl;
    //         }
    //         h_Higgsino_C1C1_reweight->Fill(truthMll, weight);
    //     }
    // }
    while (Reader_Higgsino_N2C1p.Next()) {
        double truthMll = *truth_mll_Higgsino_N2C1p;
        if (truthMll < dm_Higgsino) {
            h_Higgsino_N2C1p_original->Fill(truthMll);
            double weight = func_NUHM2->Eval(truthMll) / func_Higgsino->Eval(truthMll); //ratio NUHM2/higgsino
            // if (weight > 10) {
            //     cout << "N2C1p truthMll=" << truthMll
            //     << ", weight=" << weight
            //     << ", func_NUHM2->Eval(truthMll)=" << func_NUHM2->Eval(truthMll)
            //     << ", func_Higgsino->Eval(truthMll)=" << func_Higgsino->Eval(truthMll)
            //     << endl;
            // }
            h_Higgsino_N2C1p_reweight->Fill(truthMll, weight);
        }
    }
    while (Reader_Higgsino_N2C1m.Next()) {
        double truthMll = *truth_mll_Higgsino_N2C1m;
        if (truthMll < dm_Higgsino) {
            h_Higgsino_N2C1m_original->Fill(truthMll);
            double weight = func_NUHM2->Eval(truthMll) / func_Higgsino->Eval(truthMll); //ratio NUHM2/higgsino
            // if (weight > 10) {
            //     cout << "N2C1m truthMll=" << truthMll
            //     << ", weight=" << weight
            //     << ", func_NUHM2->Eval(truthMll)=" << func_NUHM2->Eval(truthMll)
            //     << ", func_Higgsino->Eval(truthMll)=" << func_Higgsino->Eval(truthMll)
            //     << endl;
            // }
            h_Higgsino_N2C1m_reweight->Fill(truthMll, weight);
        }
    }

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
    double area_Higgsino_N2N1_original = h_Higgsino_N2N1_original->Integral();
    // double area_Higgsino_C1C1_original = h_Higgsino_C1C1_original->Integral();
    double area_Higgsino_N2C1p_original = h_Higgsino_N2C1p_original->Integral();
    double area_Higgsino_N2C1m_original = h_Higgsino_N2C1m_original->Integral();
    // double sum_Higgsino_original = area_Higgsino_N2N1_original + area_Higgsino_C1C1_original + area_Higgsino_N2C1p_original + area_Higgsino_N2C1m_original;
    double sum_Higgsino_original = area_Higgsino_N2N1_original + area_Higgsino_N2C1p_original + area_Higgsino_N2C1m_original;

    h_Higgsino_N2N1_original->Scale(1./area_Higgsino_N2N1_original); // normalize to 1.
    // h_Higgsino_C1C1_original->Scale(1./area_Higgsino_C1C1_original);
    h_Higgsino_N2C1p_original->Scale(1./area_Higgsino_N2C1p_original);
    h_Higgsino_N2C1m_original->Scale(1./area_Higgsino_N2C1m_original);

    h_Higgsino_N2N1_original->Scale(area_Higgsino_N2N1_original / sum_Higgsino_original); // scale to the correction contribution
    // h_Higgsino_C1C1_original->Scale(area_Higgsino_C1C1_original / sum_Higgsino_original);
    h_Higgsino_N2C1p_original->Scale(area_Higgsino_N2C1p_original / sum_Higgsino_original);
    h_Higgsino_N2C1m_original->Scale(area_Higgsino_N2C1m_original / sum_Higgsino_original);

    TH1F *h_Higgsino_combined_original = (TH1F *)h_Higgsino_N2N1_original->Clone();
    // h_Higgsino_combined_original->Add(h_Higgsino_C1C1_original);
    h_Higgsino_combined_original->Add(h_Higgsino_N2C1p_original);
    h_Higgsino_combined_original->Add(h_Higgsino_N2C1m_original);
    h_Higgsino_combined_original->SetName("h_Higgsino_combined_original");
    h_Higgsino_combined_original->SetTitle("");
    h_Higgsino_combined_original->SetXTitle("m_{ll} [GeV]");
    h_Higgsino_combined_original->SetYTitle("Normalized event counts");
    h_Higgsino_combined_original->SetLineColor(kGreen);

    // Reweight
    double area_Higgsino_N2N1_reweight = h_Higgsino_N2N1_reweight->Integral();
    // double area_Higgsino_C1C1_reweight = h_Higgsino_C1C1_reweight->Integral();
    double area_Higgsino_N2C1p_reweight = h_Higgsino_N2C1p_reweight->Integral();
    double area_Higgsino_N2C1m_reweight = h_Higgsino_N2C1m_reweight->Integral();
    // double sum_Higgsino_reweight = area_Higgsino_N2N1_reweight + area_Higgsino_C1C1_reweight + area_Higgsino_N2C1p_reweight + area_Higgsino_N2C1m_reweight;
    double sum_Higgsino_reweight = area_Higgsino_N2N1_reweight + area_Higgsino_N2C1p_reweight + area_Higgsino_N2C1m_reweight;

    h_Higgsino_N2N1_reweight->Scale(1./area_Higgsino_N2N1_reweight); // normalize to 1.
    // h_Higgsino_C1C1_reweight->Scale(1./area_Higgsino_C1C1_reweight);
    h_Higgsino_N2C1p_reweight->Scale(1./area_Higgsino_N2C1p_reweight);
    h_Higgsino_N2C1m_reweight->Scale(1./area_Higgsino_N2C1m_reweight);

    h_Higgsino_N2N1_reweight->Scale(area_Higgsino_N2N1_reweight / sum_Higgsino_reweight); // scale to the correction contribution
    // h_Higgsino_C1C1_reweight->Scale(area_Higgsino_C1C1_reweight / sum_Higgsino_reweight);
    h_Higgsino_N2C1p_reweight->Scale(area_Higgsino_N2C1p_reweight / sum_Higgsino_reweight);
    h_Higgsino_N2C1m_reweight->Scale(area_Higgsino_N2C1m_reweight / sum_Higgsino_reweight);

    TH1F *h_Higgsino_combined_reweight = (TH1F *)h_Higgsino_N2N1_reweight->Clone();
    // h_Higgsino_combined_reweight->Add(h_Higgsino_C1C1_reweight);
    h_Higgsino_combined_reweight->Add(h_Higgsino_N2C1p_reweight);
    h_Higgsino_combined_reweight->Add(h_Higgsino_N2C1m_reweight);
    h_Higgsino_combined_reweight->SetName("h_Higgsino_combined_reweight");
    h_Higgsino_combined_reweight->SetTitle("");
    h_Higgsino_combined_reweight->SetXTitle("m_{ll} [GeV]");
    h_Higgsino_combined_reweight->SetYTitle("Normalized event counts");
    h_Higgsino_combined_reweight->SetLineColor(kRed);

    double area_Higgsino_combined_original = h_Higgsino_combined_original->Integral(0, dm_Higgsino);
    double area_Higgsino_combined_reweight = h_Higgsino_combined_reweight->Integral(0, dm_NUHM2);
    cout << "area_Higgsino_combined_original=" << area_Higgsino_combined_original << endl;
    cout << "area_Higgsino_combined_reweight=" << area_Higgsino_combined_reweight << endl;

    // func_Higgsino->SetParameter(0, area_Higgsino_combined_original);
    // func_NUHM2->SetParameter(0, area_Higgsino_combined_reweight);
    // cout << "func_Higgsino->Integral(0, dm_Higgsino)=" << func_Higgsino->Integral(0, dm_Higgsino) << endl;
    // cout << "func_NUHM2->Integral(0, dm_NUHM2)=" << func_NUHM2->Integral(0, dm_NUHM2) << endl;

    h_Higgsino_combined_original->Fit(func_Higgsino, "R0+");
    h_Higgsino_combined_reweight->Fit(func_NUHM2, "R0+");
    // cout << "func_Higgsino->Integral(0, dm_Higgsino)=" << func_Higgsino->Integral(0, dm_Higgsino) << endl;
    // cout << "func_NUHM2->Integral(0, dm_NUHM2)=" << func_NUHM2->Integral(0, dm_NUHM2) << endl;

    // Get the NUHM2 truth3 MC sample
    string path_NUHM2 = "/Users/ytshen/Desktop/20170730/";

    string f_NUHM2_N2N1 = "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    // string f_NUHM2_C1C1 = "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string f_NUHM2_N2C1p = "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string f_NUHM2_N2C1m = "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    // string file5 = path_NUHM2 + f_NUHM2_N2N1;
    // string file6 = path_NUHM2 + f_NUHM2_C1C1;
    // string file7 = path_NUHM2 + f_NUHM2_N2C1p;
    // string file8 = path_NUHM2 + f_NUHM2_N2C1m;

    // If I use this way, then the tail is included.
    // I need to set tail to zero.
    // TH1F *h_N2N1 = get_histogram(file5);
    // TH1F *h_C1C1 = get_histogram(file6);
    // TH1F *h_N2C1p = get_histogram(file7);
    // TH1F *h_N2C1m = get_histogram(file8);

    TFile *file_NUHM2_N2N1 = new TFile( (path_NUHM2 + f_NUHM2_N2N1).c_str() );
    // TFile *file_NUHM2_C1C1 = new TFile( (path_NUHM2 + f_NUHM2_C1C1).c_str() );
    TFile *file_NUHM2_N2C1p = new TFile( (path_NUHM2 + f_NUHM2_N2C1p).c_str() );
    TFile *file_NUHM2_N2C1m = new TFile( (path_NUHM2 + f_NUHM2_N2C1m).c_str()) ;

    TTreeReader Reader_NUHM2_N2N1("EwkHiggsino2016__ntuple", file_NUHM2_N2N1);
    // TTreeReader Reader_NUHM2_C1C1("EwkHiggsino2016__ntuple", file_NUHM2_C1C1);
    TTreeReader Reader_NUHM2_N2C1p("EwkHiggsino2016__ntuple", file_NUHM2_N2C1p);
    TTreeReader Reader_NUHM2_N2C1m("EwkHiggsino2016__ntuple", file_NUHM2_N2C1m);

    TTreeReaderValue<float> truth_mll_NUHM2_N2N1(Reader_NUHM2_N2N1, "mll");
    // TTreeReaderValue<float> truth_mll_NUHM2_C1C1(Reader_NUHM2_C1C1, "mll");
    TTreeReaderValue<float> truth_mll_NUHM2_N2C1p(Reader_NUHM2_N2C1p, "mll");
    TTreeReaderValue<float> truth_mll_NUHM2_N2C1m(Reader_NUHM2_N2C1m, "mll");

    TH1F *h_NUHM2_N2N1 = new TH1F("h_NUHM2_N2N1", "", 200, 0, 200);
    TH1F *h_NUHM2_C1C1 = new TH1F("h_NUHM2_C1C1", "", 200, 0, 200);
    TH1F *h_NUHM2_N2C1p = new TH1F("h_NUHM2_N2C1p", "", 200, 0, 200);
    TH1F *h_NUHM2_N2C1m = new TH1F("h_NUHM2_N2C1m", "", 200, 0, 200);

    while (Reader_NUHM2_N2N1.Next()) {
        double truthMll = *truth_mll_NUHM2_N2N1;
        if (truthMll < dm_NUHM2)
            h_NUHM2_N2N1->Fill(truthMll);
    }
    // while (Reader_NUHM2_C1C1.Next()) {
    //     double truthMll = *truth_mll_NUHM2_C1C1;
    //     if (truthMll < dm_NUHM2)
    //         h_NUHM2_C1C1->Fill(truthMll);
    // }
    while (Reader_NUHM2_N2C1p.Next()) {
        double truthMll = *truth_mll_NUHM2_N2C1p;
        if (truthMll < dm_NUHM2)
            h_NUHM2_N2C1p->Fill(truthMll);
    }
    while (Reader_NUHM2_N2C1m.Next()) {
        double truthMll = *truth_mll_NUHM2_N2C1m;
        if (truthMll < dm_NUHM2)
            h_NUHM2_N2C1m->Fill(truthMll);
    }

    // h_NUHM2_N2N1->SetLineColor(1);
    // h_NUHM2_C1C1->SetLineColor(2);
    // h_NUHM2_N2C1p->SetLineColor(3);
    // h_NUHM2_N2C1m->SetLineColor(4);

    // h_NUHM2_N2N1->Draw("hist");
    // h_NUHM2_C1C1->Draw("hist,same");
    // h_NUHM2_N2C1p->Draw("hist,same");
    // h_NUHM2_N2C1m->Draw("hist,same");

    double integral_NUHM2_N2N1  = h_NUHM2_N2N1->Integral();
    // double integral_NUHM2_C1C1  = h_NUHM2_C1C1->Integral();
    double integral_NUHM2_N2C1p  = h_NUHM2_N2C1p->Integral();
    double integral_NUHM2_N2C1m  = h_NUHM2_N2C1m->Integral();
    // double sum_NUHM2 = integral_NUHM2_N2N1 + integral_NUHM2_C1C1 + integral_NUHM2_N2C1p + integral_NUHM2_N2C1m;
    double sum_NUHM2 = integral_NUHM2_N2N1 + integral_NUHM2_N2C1p + integral_NUHM2_N2C1m;

    h_NUHM2_N2N1->Scale(1./integral_NUHM2_N2N1);
    // h_NUHM2_C1C1->Scale(1./integral_NUHM2_C1C1);
    h_NUHM2_N2C1p->Scale(1./integral_NUHM2_N2C1p);
    h_NUHM2_N2C1m->Scale(1./integral_NUHM2_N2C1m);

    h_NUHM2_N2N1->Scale(integral_NUHM2_N2N1 / sum_NUHM2);
    // h_NUHM2_C1C1->Scale(integral_NUHM2_C1C1 / sum_NUHM2);
    h_NUHM2_N2C1p->Scale(integral_NUHM2_N2C1p / sum_NUHM2);
    h_NUHM2_N2C1m->Scale(integral_NUHM2_N2C1m / sum_NUHM2);

    TH1F *h_NUHM2_Combined = (TH1F *)h_NUHM2_N2N1->Clone();
    // h_NUHM2_Combined->Add(h_NUHM2_C1C1);
    h_NUHM2_Combined->Add(h_NUHM2_N2C1p);
    h_NUHM2_Combined->Add(h_NUHM2_N2C1m);
    h_NUHM2_Combined->SetName("h_NUHM2_Combined");
    h_NUHM2_Combined->SetTitle("");
    h_NUHM2_Combined->SetXTitle("m_{ll} [GeV]");
    h_NUHM2_Combined->SetYTitle("Normalized event counts");
    h_NUHM2_Combined->SetLineColor(kBlue);

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

    h_NUHM2_Combined->Draw("hist,same");

    TLegend *legend = new TLegend(0.4, 0.6, 0.9, 0.8);
    legend->AddEntry(h_Higgsino_combined_original, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(func_Higgsino, ("Calculated Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_Higgsino_combined_reweight, ("reweight Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(func_NUHM2, ("Calculated reweighted Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_NUHM2_Combined, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "reweight_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());

}






// TH1F *get_truth3_NUHM2(int);
// TH1F *get_truth3_Higgsino(bool, string, int);
// TH1F *treeReader(bool, string, int, string, string);
/*
// void treeReader(bool, string, int, string, string, TH1F *, TH1F *);
double get_reweight_ratio_1(string, int, double);
double get_reweight_ratio_2(string, int, double);
*/

// Masses of N1, N2 for NUHM2
// Remember m(N2) is supposed to be negative
// double par_NUHM2_m12_300[2] = {105.631409, 161.307800};
// double par_NUHM2_m12_350[2] = {115.618103, 161.675125};
// double par_NUHM2_m12_400[2] = {122.974541, 161.142700};
// double par_NUHM2_m12_500[2] = {132.279099, 160.295654};
// double par_NUHM2_m12_600[2] = {137.607727, 159.657379};
// double par_NUHM2_m12_700[2] = {140.978836, 159.170868};
// double par_NUHM2_m12_800[2] = {143.288208, 158.783905};
/*
void reweight_truth3(string n2_n1, int m12)
{
    TH1F *h_NUHM2 = get_truth3_NUHM2(m12);
    TH1F *h_Higgsino_original = get_truth3_Higgsino(false, n2_n1, m12);
    TH1F *h_Higgsino_reweight = get_truth3_Higgsino(true, n2_n1, m12);

    double dm_NUHM2 = 0.;
    if (m12 == 300){
        dm_NUHM2 = par_NUHM2_m12_300[1] - par_NUHM2_m12_300[0];
    }
    else if (m12 == 350) {
        dm_NUHM2 = par_NUHM2_m12_350[1] - par_NUHM2_m12_350[0];
    }
    else if (m12 == 400) {
        dm_NUHM2 = par_NUHM2_m12_400[1] - par_NUHM2_m12_400[0];
    }
    else if (m12 == 500) {
        dm_NUHM2 = par_NUHM2_m12_500[1] - par_NUHM2_m12_500[0];
    }
    else if (m12 == 600) {
        dm_NUHM2 = par_NUHM2_m12_600[1] - par_NUHM2_m12_600[0];
    }
    else if (m12 == 700) {
        dm_NUHM2 = par_NUHM2_m12_700[1] - par_NUHM2_m12_700[0];
    }
    else if (m12 == 800) {
        dm_NUHM2 = par_NUHM2_m12_800[1] - par_NUHM2_m12_800[0];
    }

    double n2 = stod(n2_n1.substr(0, n2_n1.find("_"))); // stod() converts string to double
    double n1 = stod(n2_n1.substr(n2_n1.find("_") + 1, n2_n1.length()));
    double dm_Higgsino = n2 - n1;

    double area_NUHM2 = h_NUHM2->Integral(0, dm_NUHM2);
    double area_Higgsino_original = h_Higgsino_original->Integral(0, dm_Higgsino);
    double area_Higgsino_reweight = h_Higgsino_reweight->Integral(0, dm_NUHM2);
    cout << "area_NUHM2=" << area_NUHM2 << endl;
    cout << "area_Higgsino_original=" << area_Higgsino_original << endl;
    cout << "area_Higgsino_reweight=" << area_Higgsino_reweight << endl;

    TCanvas *c = new TCanvas("c", "", 800, 600);
    c->SetLeftMargin(0.12);
    bool logY = false;

    if (logY)
        gPad->SetLogy();

    double x_max = 0;
    if (m12 < 400)
        x_max = 100.;
    else if (m12 >= 400)
        x_max = 50.;

    double y_max_Higgsino = max(h_Higgsino_original->GetMaximum(), h_Higgsino_reweight->GetMaximum());
    double y_max = max(y_max_Higgsino, h_NUHM2->GetMaximum()) * 1.2;

    h_Higgsino_original->SetTitle("");
    h_Higgsino_original->SetXTitle("m_{ll} [GeV]");
    h_Higgsino_original->SetYTitle("Events / 1 GeV");
    h_Higgsino_original->GetXaxis()->SetRangeUser(0, x_max);
    h_Higgsino_original->GetYaxis()->SetTitleOffset(1.4);
    // h_Higgsino_original->SetMaximum(y_max);
    h_Higgsino_original->SetLineColor(kGreen);
    h_Higgsino_original->SetStats(0);
    h_Higgsino_original->Draw("hist,same");

    h_Higgsino_reweight->SetLineColor(kRed);
    h_Higgsino_reweight->Draw("hist,same");

    h_NUHM2->Scale( (1./h_NUHM2->Integral() ) * h_Higgsino_original->Integral());
    h_NUHM2->SetLineColor(kBlue);
    h_NUHM2->Draw("hist,same");

    TLegend *legend = new TLegend(0.5, 0.6, 0.9, 0.8);
    legend->AddEntry(h_Higgsino_original, ("Higgsino_" + n2_n1).c_str(), "l");
    legend->AddEntry(h_NUHM2, ("NUHM2 m12=" + to_string(m12)).c_str(), "l");
    legend->AddEntry(h_Higgsino_reweight, ("reweighted Higgsino_" + n2_n1).c_str(), "l");
    legend->SetBorderSize(0);
    legend->SetTextFont(42);
    legend->SetTextSize(0.03);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw();

    string output = "reweight_2_Higgsino_" + n2_n1 + "_m12_" + to_string(m12) + ".pdf";
    c->SaveAs(output.c_str());
}

TH1F *get_truth3_NUHM2(int m12)
{
    // string path_NUHM2 = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/SimpleAnalysis/Results/20170730/";
    string path_NUHM2 = "/Users/ytshen/Desktop/20170730/";

    string f_NUHM2_N2N1 = "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
    string f_NUHM2_C1C1 = "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
    string f_NUHM2_N2C1p = "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
    string f_NUHM2_N2C1m = "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";

    string file5 = path_NUHM2 + f_NUHM2_N2N1;
    string file6 = path_NUHM2 + f_NUHM2_C1C1;
    string file7 = path_NUHM2 + f_NUHM2_N2C1p;
    string file8 = path_NUHM2 + f_NUHM2_N2C1m;

    TH1F *h_NUHM2 = get_combined_hist(file5, file6, file7, file8);

    return h_NUHM2;
}

TH1F *get_truth3_Higgsino(bool is_reweight, string n2_n1, int m12)
{
    // string path_Higgsino = "/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/SimpleAnalysis/Results/20170802/";
    string path_Higgsino = "/Users/ytshen/Desktop/20170802/";

    string f_Higgsino_N2N1 = "user.yushen.SM_N2N1_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_C1C1 = "user.yushen.SM_C1C1_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1p = "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string f_Higgsino_N2C1m = "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    double n2 = stod(n2_n1.substr(0, n2_n1.find("_"))); // stod() converts string to double
    double n1 = stod(n2_n1.substr(n2_n1.find("_") + 1, n2_n1.length()));
    double dm_Higgsino = n2 - n1;

    string file1 = path_Higgsino + f_Higgsino_N2N1;
    string file2 = path_Higgsino + f_Higgsino_C1C1;
    string file3 = path_Higgsino + f_Higgsino_N2C1p;
    string file4 = path_Higgsino + f_Higgsino_N2C1m;

    // TH1F *h_N2N1_original = treeReader(false, n2_n1, m12, file1, "EwkHiggsino2016__ntuple");
    // TH1F *h_C1C1_original = treeReader(false, n2_n1, m12, file2, "EwkHiggsino2016__ntuple");
    // TH1F *h_N2C1p_original = treeReader(false, n2_n1, m12, file3, "EwkHiggsino2016__ntuple");
    // TH1F *h_N2C1m_original = treeReader(false, n2_n1, m12, file4, "EwkHiggsino2016__ntuple");

    // TH1F *h_N2N1_reweight = treeReader(true, n2_n1, m12, file1, "EwkHiggsino2016__ntuple");
    // TH1F *h_C1C1_reweight = treeReader(true, n2_n1, m12, file2, "EwkHiggsino2016__ntuple");
    // TH1F *h_N2C1p_reweight = treeReader(true, n2_n1, m12, file3, "EwkHiggsino2016__ntuple");
    // TH1F *h_N2C1m_reweight = treeReader(true, n2_n1, m12, file4, "EwkHiggsino2016__ntuple");

    TFile *f_N2N1 = new TFile(file1.c_str());
    TFile *f_C1C1 = new TFile(file2.c_str());
    TFile *f_N2C1p = new TFile(file3.c_str());
    TFile *f_N2C1m = new TFile(file4.c_str());

    TTreeReader myReader_N2N1("EwkHiggsino2016__ntuple", f_N2N1);
    TTreeReader myReader_C1C1("EwkHiggsino2016__ntuple", f_C1C1);
    TTreeReader myReader_N2C1p("EwkHiggsino2016__ntuple", f_N2C1p);
    TTreeReader myReader_N2C1m("EwkHiggsino2016__ntuple", f_N2C1m);

    TTreeReaderValue<float> original_mll_N2N1(myReader_N2N1, "mll");
    TTreeReaderValue<float> original_mll_C1C1(myReader_C1C1, "mll");
    TTreeReaderValue<float> original_mll_N2C1p(myReader_N2C1p, "mll");
    TTreeReaderValue<float> original_mll_N2C1m(myReader_N2C1m, "mll");

    TH1F *h_Combined = new TH1F("h_Combined", "", 200, 0, 200);

    if (!is_reweight) { // original
        while (myReader_N2N1.Next()) {
            h_Combined->Fill(*original_mll_N2N1);
        }
        while (myReader_C1C1.Next()) {
            h_Combined->Fill(*original_mll_C1C1);
        }
        while (myReader_N2C1p.Next()) {
            h_Combined->Fill(*original_mll_N2C1p);
        }
        while (myReader_N2C1m.Next()) {
            h_Combined->Fill(*original_mll_N2C1m);
        }
    }
    else { // reweight
        double dm_NUHM2 = 0., par0 = 0., par1 = 0., par2 = 0.;
        if (m12 == 300){
            dm_NUHM2 = par_NUHM2_m12_300[1] - par_NUHM2_m12_300[0];
            par0 = 0.704021;
            par1 = par_NUHM2_m12_300[0];
            par2 = par_NUHM2_m12_300[1];
        }
        else if (m12 == 350) {
            dm_NUHM2 = par_NUHM2_m12_350[1] - par_NUHM2_m12_350[0];
            par0 = 3.26126;
            par1 = par_NUHM2_m12_350[0];
            par2 = par_NUHM2_m12_350[1];
        }
        else if (m12 == 400) {
            dm_NUHM2 = par_NUHM2_m12_400[1] - par_NUHM2_m12_400[0];
            par0 = 1.29167;
            par1 = par_NUHM2_m12_400[0];
            par2 = par_NUHM2_m12_400[1];
        }
        else if (m12 == 500) {
            dm_NUHM2 = par_NUHM2_m12_500[1] - par_NUHM2_m12_500[0];
            par0 = 4.25016;
            par1 = par_NUHM2_m12_500[0];
            par2 = par_NUHM2_m12_500[1];
        }
        else if (m12 == 600) {
            dm_NUHM2 = par_NUHM2_m12_600[1] - par_NUHM2_m12_600[0];
            par0 = 1.31473;
            par1 = par_NUHM2_m12_600[0];
            par2 = par_NUHM2_m12_600[1];
        }
        else if (m12 == 700) {
            dm_NUHM2 = par_NUHM2_m12_700[1] - par_NUHM2_m12_700[0];
            par0 = 0.511249;
            par1 = par_NUHM2_m12_700[0];
            par2 = par_NUHM2_m12_700[1];
        }
        else if (m12 == 800) {
            dm_NUHM2 = par_NUHM2_m12_800[1] - par_NUHM2_m12_800[0];
            par0 = 0.232064;
            par1 = par_NUHM2_m12_800[0];
            par2 = par_NUHM2_m12_800[1];
        }

        TF1 *func_Higgsino = new TF1("func_Higgsino", FuncMllDistr, 0, dm_Higgsino, 3);
        // func_Higgsino->SetParameters(par0, n1, -1 * n2);
        func_Higgsino->SetParameters(1, n1, -1 * n2);
        double area_Higgsino = func_Higgsino->Integral(0, dm_Higgsino);
        // cout << "area_Higgsino=" << area_Higgsino << endl;
        func_Higgsino->SetParameter(0, (1./area_Higgsino) );

        TF1 *func_NUHM2 = new TF1("func_NUHM2", FuncMllDistr, 0, dm_NUHM2, 3);
        func_NUHM2->SetParameters(1., par1, -1 * par2);
        double area_NUHM2 = func_NUHM2->Integral(0, dm_NUHM2);
        // cout << "area_NUHM2=" << area_NUHM2 << endl;
        func_NUHM2->SetParameter(0, (1./area_NUHM2) );

        while (myReader_N2N1.Next()) {
            if (*original_mll_N2N1 > 0) {
                double weight = func_NUHM2->Eval(*original_mll_N2N1) / func_Higgsino->Eval(*original_mll_N2N1);
                if (weight > 1.) {
                    cout << "original_mll_N2N1=" << *original_mll_N2N1
                    << ", func_NUHM2->Eval(*original_mll_N2N1)=" << func_NUHM2->Eval(*original_mll_N2N1)
                    << ", func_Higgsino->Eval(*original_mll_N2N1)=" << func_Higgsino->Eval(*original_mll_N2N1)
                    << ", weight=" << weight << endl;
                }
                h_Combined->Fill(*original_mll_N2N1, weight);
            }
        }
        while (myReader_C1C1.Next()) {
            if (*original_mll_C1C1 > 0) {
                double weight = func_NUHM2->Eval(*original_mll_C1C1) / func_Higgsino->Eval(*original_mll_C1C1);
                // if (weight > 1.) {
                //     cout << "original_mll_C1C1=" << *original_mll_C1C1
                //     << ", func_NUHM2->Eval(*original_mll_C1C1)=" << func_NUHM2->Eval(*original_mll_C1C1)
                //     << ", func_Higgsino->Eval(*original_mll_C1C1)=" << func_Higgsino->Eval(*original_mll_C1C1)
                //     << ", weight=" << weight << endl;
                // }
                h_Combined->Fill(*original_mll_C1C1, weight);
            }
        }
        while (myReader_N2C1p.Next()) {
            if (*original_mll_N2C1p > 0) {
                double weight = func_NUHM2->Eval(*original_mll_N2C1p) / func_Higgsino->Eval(*original_mll_N2C1p);
                // if (weight > 1.) {
                //     cout << "original_mll_N2C1p=" << *original_mll_N2C1p
                //     << ", func_NUHM2->Eval(*original_mll_N2C1p)=" << func_NUHM2->Eval(*original_mll_N2C1p)
                //     << ", func_Higgsino->Eval(*original_mll_N2C1p)=" << func_Higgsino->Eval(*original_mll_N2C1p)
                //     << ", weight=" << weight << endl;
                // }
                h_Combined->Fill(*original_mll_N2C1p, weight);
            }
        }
        while (myReader_N2C1m.Next()) {
            if (*original_mll_N2C1m > 0) {
                double weight = func_NUHM2->Eval(*original_mll_N2C1m) / func_Higgsino->Eval(*original_mll_N2C1m);
                // if (weight > 1.) {
                //     cout << "original_mll_N2C1m=" << *original_mll_N2C1m
                //     << "func_NUHM2->Eval(*original_mll_N2C1m)=" << func_NUHM2->Eval(*original_mll_N2C1m)
                //     << ", func_Higgsino->Eval(*original_mll_N2C1m)=" << func_Higgsino->Eval(*original_mll_N2C1m)
                //     << ", weight=" << weight << endl;
                // }
                h_Combined->Fill(*original_mll_N2C1m, weight);
            }
        }
    }

    return h_Combined;
}
*/
/*
TH1F *treeReader(bool is_reweight, string n2_n1, int m12, string file_name, string tree_name)
// void treeReader(bool is_reweight, string n2_n1, int m12, string file_name, string tree_name, TH1F *h_original, TH1F *h_reweight)
{
    TH1F *h_original = new TH1F("h_original", "", 200, 0, 200);
    TH1F *h_reweight = new TH1F("h_reweight", "", 200, 0, 200);

    TFile *f = new TFile(file_name.c_str());
    TTreeReader myReader(tree_name.c_str(), f);
    TTreeReaderValue<float> original_mll(myReader, "mll");

    while (myReader.Next()) {
        h_original->Fill(*original_mll);

        // double ratio = get_reweight_ratio_1(n2_n1, m12, *original_mll);
        double ratio = get_reweight_ratio_2(n2_n1, m12, *original_mll);
        double reweight_mll = (*original_mll) * ratio;
        //cout << "reweight_mll=" << reweight_mll << ", *original_mll=" << *original_mll << ", ratio=" << ratio << endl;
        h_reweight->Fill(reweight_mll);
    }

    if (is_reweight)
        return h_reweight;
    else
        return h_original;
}

double get_reweight_ratio_1(string n2_n1, int m12, double mll)
{
    double n2 = stod(n2_n1.substr(0, n2_n1.find("_"))); // stod() converts string to double
    double n1 = stod(n2_n1.substr(n2_n1.find("_") + 1, n2_n1.length()));
    double dm_Higgsino = n2 - n1;

    double dm_NUHM2 = 0;
    if (m12 == 300)
        dm_NUHM2 = 55.;
    else if (m12 == 350)
        dm_NUHM2 = 46.;
    else if (m12 == 400)
        dm_NUHM2 = 38.;
    else if (m12 == 500)
        dm_NUHM2 = 28.;
    else if (m12 == 600)
        dm_NUHM2 = 22.;
    else if (m12 == 700)
        dm_NUHM2 = 18.;
    else if (m12 == 800)
        dm_NUHM2 = 15.;

    return dm_NUHM2 / dm_Higgsino;
}

double get_reweight_ratio_2(string n2_n1, int m12, double mll)
{
    double x[1] = {mll};
    double par_Higgsino[3] = {0};
    double par_NUHM2[3] = {0};

    if (n2_n1 == "140_100") {
        par_Higgsino[0] = 2.10628E-07;
        par_Higgsino[1] = 1.00083E+02;
        par_Higgsino[2] = -1.39583E+02;
    }
    else if (n2_n1 == "160_100") {
        par_Higgsino[0] = 3.97789E-08;
        par_Higgsino[1] = 6.69586E+01;
        par_Higgsino[2] = -1.26459E+02;
    }
    else if (n2_n1 == "170_150") {
        par_Higgsino[0] = 3.40869E-07;
        par_Higgsino[1] = 2.94691E+02;
        par_Higgsino[2] = -3.15499E+02;
    }

    if (m12 == 300) {
        par_NUHM2[0] = 8.12264E-08;
        par_NUHM2[1] = 3.50058E+01;
        par_NUHM2[2] = -9.91722E+01;
    }
    
    else if (m12 == 350) {
        par_NUHM2[0] = 8.14450E-08;
        par_NUHM2[1] = 1.03884E+02;
        par_NUHM2[2] = -1.49384E+02;
    }
    else if (m12 == 400) {
        par_NUHM2[0] = 5.56669E-10;
        par_NUHM2[1] = 8.88082E+02;
        par_NUHM2[2] = -9.26435E+02;
    }
    else if (m12 == 500) {
        par_NUHM2[0] = 6.29717E-09;
        par_NUHM2[1] = 6.45114E+02;
        par_NUHM2[2] = -6.73877E+02;
    }
    else if (m12 == 600) {
        par_NUHM2[0] = 2.09419E-07;
        par_NUHM2[1] = 2.84535E+02;
        par_NUHM2[2] = -3.07564E+02;
    }
    else if (m12 == 700) {
        par_NUHM2[0] = 5.72898E-07;
        par_NUHM2[1] = 2.74570E+02;
        par_NUHM2[2] = -2.93799E+02;
    }
    else if (m12 == 800) {
        par_NUHM2[0] = 1.26533E-06;
        par_NUHM2[1] = 2.73757E+02;
        par_NUHM2[2] = -2.90133E+02;
    }

    double var_Higgsino = FuncMllDistr(x, par_Higgsino);
    double var_NUHM2 = FuncMllDistr(x, par_NUHM2);

    return var_NUHM2 / var_Higgsino;
}
*/
