#include <TROOT.h>
#include "FuncMllDistr_modified.C"
#include "get_combined_hist.C"
#include <string>

void test_Higgsino_160_100()
{
    string path_Higgsino = "/Users/ytshen/Documents/Working/OU/HEP/my_codes/Higgsino/data/truth3_Results/20170817/";

    int n1 = 100, n2 = 160;
    double dm_Higgsino = n2 - n1;

    string n2_n1 = to_string(n2) + "_" + to_string(n1);

    string file_Higgsino_N2N1  = path_Higgsino + "user.yushen.SM_N2N1_"  + n2_n1 + "_2LMET50.root";
    string file_Higgsino_C1C1  = path_Higgsino + "user.yushen.SM_C1C1_"  + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1p = path_Higgsino + "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
    string file_Higgsino_N2C1m = path_Higgsino + "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

    TH1F *h_combined = get_combined_hist(file_Higgsino_N2N1, file_Higgsino_C1C1, file_Higgsino_N2C1p, file_Higgsino_N2C1m);
    h_combined->Draw("hist");

    // Theoretical function
    TF1 *func_Higgsino = new TF1("func_Higgsino", FuncMllDistr, 0, dm_Higgsino, 3);
    func_Higgsino->SetParameters(1., n1, -1 * n2);
    double area_func_Higgsino = func_Higgsino->Integral(0, dm_Higgsino);
    func_Higgsino->SetParameter(0, 1./area_func_Higgsino);
    func_Higgsino->FixParameter(1, n1);
    func_Higgsino->FixParameter(2, -1 * n2);

    h_combined->Fit(func_Higgsino, "R0");
    h_combined->Fit(func_Higgsino, "R0");
    h_combined->Fit(func_Higgsino, "R");

    func_Higgsino->Draw("same");
}
