#include <string>

// Common ntuple v1.8b
string path_common_ntuple = "/Users/ytshen/Desktop/";

string f_140_100 = "MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
string f_160_100 = "MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
string f_170_150 = "MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";
string f_190_150 = "MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root";

string file_140_100 = path_common_ntuple + f_140_100;
string file_160_100 = path_common_ntuple + f_160_100;
string file_170_150 = path_common_ntuple + f_170_150;
string file_190_150 = path_common_ntuple + f_190_150;

// Higgsino TRUTH3
string path_Higgsino = "/Users/ytshen/Desktop/20170810/";

string n2_n1 = to_string(n2) + "_" + to_string(n1);

string file_Higgsino_N2N1  = path_Higgsino + "user.yushen.SM_N2N1_"  + n2_n1 + "_2LMET50.root";
string file_Higgsino_C1C1  = path_Higgsino + "user.yushen.SM_C1C1_"  + n2_n1 + "_2LMET50.root";
string file_Higgsino_N2C1p = path_Higgsino + "user.yushen.SM_N2C1p_" + n2_n1 + "_2LMET50.root";
string file_Higgsino_N2C1m = path_Higgsino + "user.yushen.SM_N2C1m_" + n2_n1 + "_2LMET50.root";

// NUHM2 TRUTH3
string path_NUHM2 = "/Users/ytshen/Desktop/20170730/";

string file_NUHM2_N2N1  = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2N1.TestJob.root";
string file_NUHM2_C1C1  = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_C1C1.TestJob.root";
string file_NUHM2_N2C1p = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1p.TestJob.root";
string file_NUHM2_N2C1m = path_NUHM2 + "user.yushen.run_" + to_string(m12) + "_N2C1m.TestJob.root";
