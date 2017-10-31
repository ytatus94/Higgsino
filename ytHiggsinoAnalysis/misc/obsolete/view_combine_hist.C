#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>

#include "get_combined_hist.C"

#include <string>
#include <iostream>
using namespace std;

// void view_combine_hist(int n2 = 170, int n1 = 150, string var = "mll")
void view_combine_hist(int n2 = 170, int n1 = 150)
{
    string var = "METOverHTLep12";
    string cut = "METOverHTLep12>0";

    int nbins = 100;
    double xmin = 0., xmax = 100.;

    // Higgsino TRUTH3
    string path_Higgsino = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170817/";

    string n2_n1 = to_string(n2) + "_" + to_string(n1);

    string file_Higgsino_N2N1  = path_Higgsino + "user.yushen.SM_N2N1_"  + n2_n1 + "_2LMET50.root";
    string file_Higgsino_C1C1  = path_Higgsino + "user.yushen.SM_C1C1_"  + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1p = path_Higgsino + "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1m = path_Higgsino + "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    TH1F *h_N2N1  = get_histogram(file_Higgsino_N2N1, var.c_str(), nbins, xmin, xmax, cut.c_str());
    TH1F *h_C1C1  = get_histogram(file_Higgsino_C1C1, var.c_str(), nbins, xmin, xmax, cut.c_str());
    TH1F *h_N2C1p = get_histogram(file_Higgsino_N2C1p, var.c_str(), nbins, xmin, xmax, cut.c_str());
    TH1F *h_N2C1m = get_histogram(file_Higgsino_N2C1m, var.c_str(), nbins, xmin, xmax, cut.c_str());

    // TH1F *h_N2N1  = get_histogram(file_Higgsino_N2N1, "pTll", 100, 0., 100., "pTll>0");
    // TH1F *h_C1C1  = get_histogram(file_Higgsino_C1C1, "pTll", 100, 0., 100., "pTll>0");
    // TH1F *h_N2C1p = get_histogram(file_Higgsino_N2C1p, "pTll", 100, 0., 100., "pTll>0");
    // TH1F *h_N2C1m = get_histogram(file_Higgsino_N2C1m, "pTll", 100, 0., 100., "pTll>0");

    TH1F *h_Higgsino_combine = combine_histogram(h_N2N1, h_C1C1, h_N2C1p, h_N2C1m);
    h_Higgsino_combine->Draw("hist");
}
