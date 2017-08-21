// Masses of N1, N2 for NUHM2
double par_NUHM2_m12_300[2] = {105.631409, 161.307800};
double par_NUHM2_m12_350[2] = {115.618103, 161.675125};
double par_NUHM2_m12_400[2] = {122.974541, 161.142700};
double par_NUHM2_m12_500[2] = {132.279099, 160.295654};
double par_NUHM2_m12_600[2] = {137.607727, 159.657379};
double par_NUHM2_m12_700[2] = {140.978836, 159.170868};
double par_NUHM2_m12_800[2] = {143.288208, 158.783905};

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

double get_cross_section(string decay, int n2, int n1, int m12, bool isHiggsino)
{
    double xsec = 0.;

    if (isHiggsino) {
        // Higgsino
        if (n2 == 160 && n1 == 100) {
            if (decay == "N2N1")
                xsec = 1.165897;
            else if (decay == "C1C1")
                xsec = 1.179878;
            else if (decay == "N2C1p")
                xsec = 0.907085;
            else if (decay == "N2C1m")
                xsec = 0.529987;
        }
        else if (n2 == 170 && n1 == 150) {
            if (decay == "N2N1")
                xsec = 0.562441;
            else if (decay == "C1C1")
                xsec = 0.563417;
            else if (decay == "N2C1p")
                xsec = 0.578138;
            else if (decay == "N2C1m")
                xsec = 0.328355;
        }
        else if (n2 == 190 && n1 == 150) {
            if (decay == "N2N1")
                xsec = 0.444892;
            else if (decay == "C1C1")
                xsec = 0.45304;
            else if (decay == "N2C1p")
                xsec = 0.423038;
            else if (decay == "N2C1m")
                xsec = 0.235433;
        }
    }
    else {
        // NUHM2
        if (m12 == 300) {
            if (decay == "N2N1")
                xsec = 0.0009775530;
            else if (decay == "C1C1")
                xsec = 1.1640104660;
            else if (decay == "N2C1p")
                xsec = 0.4768609298;
            else if (decay == "N2C1m")
                xsec = 0.2784795051;
        }
        else if (m12 == 350) {
            if (decay == "N2N1")
                xsec = 0.5835187445;
            else if (decay == "C1C1")
                xsec = 0.9548695995;
            else if (decay == "N2C1p")
                xsec = 0.6833463531;
            else if (decay == "N2C1m")
                xsec = 0.3983657446;
        }
        else if (m12 == 400) {
            if (decay == "N2N1")
                xsec = 0.6255603991;
            else if (decay == "C1C1")
                xsec = 0.8415837349;
            else if (decay == "N2C1p")
                xsec = 0.6845201512;
            else if (decay == "N2C1m")
                xsec = 0.3976839861;
        }
        else if (m12 == 500) {
            if (decay == "N2N1")
                xsec = 0.6603094819;
            else if (decay == "C1C1")
                xsec = 0.7280789222;
            else if (decay == "N2C1p")
                xsec = 0.6819165298;
            else if (decay == "N2C1m")
                xsec = 0.3955900373;
        }
        else if (m12 == 600) {
            if (decay == "N2N1")
                xsec = 0.6656504736;
            else if (decay == "C1C1")
                xsec = 0.6745140438;
            else if (decay == "N2C1p")
                xsec = 0.6791453722;
            else if (decay == "N2C1m")
                xsec = 0.3930396433;
        }
        else if (m12 == 700) {
            if (decay == "N2N1")
                xsec = 0.6643270342;
            else if (decay == "C1C1")
                xsec = 0.6438838471;
            else if (decay == "N2C1p")
                xsec = 0.6766070496;
            else if (decay == "N2C1m")
                xsec = 0.3913281838;
        }
        else if (m12 == 800) {
            if (decay == "N2N1")
                xsec = 0.6598118363;
            else if (decay == "C1C1")
                xsec = 0.6240319555;
            else if (decay == "N2C1p")
                xsec = 0.6748686972;
            else if (decay == "N2C1m")
                xsec = 0.3906074836;
        }
    }

    return xsec;
}

double get_filter_efficiency(string decay, int n2, int n1, int m12, bool isHiggsino)
{
    double eff = 0.;

    if (isHiggsino) {
        // Higgsino
        if (n2 == 160 && n1 == 100) {
            if (decay == "N2N1")
                eff = 0.2668501;
            else if (decay == "C1C1")
                eff = 0.120497;
            else if (decay == "N2C1p")
                eff = 0.2915957;
            else if (decay == "N2C1m")
                eff = 0.2992532;
        }
        else if (n2 == 170 && n1 == 150) {
            if (decay == "N2N1")
                eff = 0.1582031;
            else if (decay == "C1C1")
                eff = 0.07314584;
            else if (decay == "N2C1p")
                eff = 0.1704238;
            else if (decay == "N2C1m")
                eff = 0.1668405;
        }
        else if (n2 == 190 && n1 == 150) {
            if (decay == "N2N1")
                eff = 0.2558509;
            else if (decay == "C1C1")
                eff = 0.1232668;
            else if (decay == "N2C1p")
                eff = 0.2481373;
            else if (decay == "N2C1m")
                eff = 0.2505845;
        }
    }
    else {
        // NUHM2
        if (m12 == 300) {
            if (decay == "N2N1")
                eff = 0.414405;
            else if (decay == "C1C1")
                eff = 0.164017;
            else if (decay == "N2C1p")
                eff = 0.265627;
            else if (decay == "N2C1m")
                eff = 0.277531;
        }
        else if (m12 == 350) {
            if (decay == "N2N1")
                eff = 0.248245;
            else if (decay == "C1C1")
                eff = 0.148728;
            else if (decay == "N2C1p")
                eff = 0.273310;
            else if (decay == "N2C1m")
                eff = 0.275627;
        }
        else if (m12 == 400) {
            if (decay == "N2N1")
                eff = 0.231079;
            else if (decay == "C1C1")
                eff = 0.141000;
            else if (decay == "N2C1p")
                eff = 0.244031;
            else if (decay == "N2C1m")
                eff = 0.249081;
        }
        else if (m12 == 500) {
            if (decay == "N2N1")
                eff = 0.198565;
            else if (decay == "C1C1")
                eff = 0.125613;
            else if (decay == "N2C1p")
                eff = 0.206531;
            else if (decay == "N2C1m")
                eff = 0.207577;
        }
        else if (m12 == 600) {
            if (decay == "N2N1")
                eff = 0.177126;
            else if (decay == "C1C1")
                eff = 0.115093;
            else if (decay == "N2C1p")
                eff = 0.182043;
            else if (decay == "N2C1m")
                eff = 0.188051;
        }
        else if (m12 == 700) {
            if (decay == "N2N1")
                eff = 0.160043;
            else if (decay == "C1C1")
                eff = 0.103832;
            else if (decay == "N2C1p")
                eff = 0.174270;
            else if (decay == "N2C1m")
                eff = 0.176030;
        }
        else if (m12 == 800) {
            if (decay == "N2N1")
                eff = 0.146843;
            else if (decay == "C1C1")
                eff = 0.101354;
            else if (decay == "N2C1p")
                eff = 0.161460;
            else if (decay == "N2C1m")
                eff = 0.165694;
        }
    }

    return eff;
}

double get_luminosity()
{
    return 36.1;
}

double get_sum_of_event_weight(string decay, int n2, int n1, int m12, bool isHiggsino)
{
    double sum_of_event_weight = 0.;
    string s1 = decay + "_" + to_string(n2) + "_" + to_string(n1);
    string s2 = to_string(m12) + "_" + decay;

    if (isHiggsino) {
        // Higgsino_140_100
        if (s1 == "N2N1_140_100")
            sum_of_event_weight = 13317.6;
        else if (s1 == "C1C1_140_100")
            sum_of_event_weight = 13299.4;
        else if (s1 == "N2C1p_140_100")
            sum_of_event_weight = 13499.4;
        else if (s1 == "N2C1m_140_100")
            sum_of_event_weight = 13614.9;
        // Higgsino_160_100
        else if (s1 == "N2N1_160_100")
            sum_of_event_weight = 12811.5;
        else if (s1 == "C1C1_160_100")
            sum_of_event_weight = 13277.6;
        else if (s1 == "N2C1p_160_100")
            sum_of_event_weight = 13242.3;
        else if (s1 == "N2C1m_160_100")
            sum_of_event_weight = 13161.1;
        // Higgsino_170_150
        else if (s1 == "N2N1_170_150")
            sum_of_event_weight = 13743.6;
        else if (s1 == "C1C1_170_150")
            sum_of_event_weight = 13611.9;
        else if (s1 == "N2C1p_170_150")
            sum_of_event_weight = 14133.3;
        else if (s1 == "N2C1m_170_150")
            sum_of_event_weight = 14225.8;
        // Higgsino_190_150
        else if (s1 == "N2N1_190_150")
            sum_of_event_weight = 13357.2;
        else if (s1 == "C1C1_190_150")
            sum_of_event_weight = 13626.4;
        else if (s1 == "N2C1p_190_150")
            sum_of_event_weight = 14092.4;
        else if (s1 == "N2C1m_190_150")
            sum_of_event_weight = 14135.8;
    }
    else {
        // m12 = 300
        if (s2 == "300_N2N1")
            sum_of_event_weight = 6496.44;
        else if (s2 == "300_C1C1")
            sum_of_event_weight = 7001.82;
        else if (s2 == "300_N2C1p")
            sum_of_event_weight = 7045.99;
        else if (s2 == "300_N2C1m")
            sum_of_event_weight = 7069.03;
        // m12 = 350
        else if (s2 == "350_N2N1")
            sum_of_event_weight = 6981.82;
        else if (s2 == "350_C1C1")
            sum_of_event_weight = 7081.17;
        else if (s2 == "350_N2C1p")
            sum_of_event_weight = 7100.28;
        else if (s2 == "350_N2C1m")
            sum_of_event_weight = 7127.21;
        // m12 = 400
        else if (s2 == "400_N2N1")
            sum_of_event_weight = 7110.09;
        else if (s2 == "400_C1C1")
            sum_of_event_weight = 7118.36;
        else if (s2 == "400_N2C1p")
            sum_of_event_weight = 7194.43;
        else if (s2 == "400_N2C1m")
            sum_of_event_weight = 7210.78;
        // m12 = 500
        else if (s2 == "500_N2N1")
            sum_of_event_weight = 7091.72;
        else if (s2 == "500_C1C1")
            sum_of_event_weight = 7096;
        else if (s2 == "500_N2C1p")
            sum_of_event_weight = 7291.28;
        else if (s2 == "500_N2C1m")
            sum_of_event_weight = 7240.86;
        // m12 = 600
        else if (s2 == "600_N2N1")
            sum_of_event_weight = 7149.2;
        else if (s2 == "600_C1C1")
            sum_of_event_weight = 7081.05;
        else if (s2 == "600_N2C1p")
            sum_of_event_weight = 7201.25;
        else if (s2 == "600_N2C1m")
            sum_of_event_weight = 7306.76;
        // m12 = 700
        else if (s2 == "700_N2N1")
            sum_of_event_weight = 7140.61;
        else if (s2 == "700_C1C1")
            sum_of_event_weight = 7011.84;
        else if (s2 == "700_N2C1p")
            sum_of_event_weight = 7254.92;
        else if (s2 == "700_N2C1m")
            sum_of_event_weight = 7300.16;
        // m12 = 800
        else if (s2 == "800_N2N1")
            sum_of_event_weight = 7142.99;
        else if (s2 == "800_C1C1")
            sum_of_event_weight = 7028.66;
        else if (s2 == "800_N2C1p")
            sum_of_event_weight = 7249.96;
        else if (s2 == "800_N2C1m")
            sum_of_event_weight = 7274.96;
    }

    return sum_of_event_weight;
}

double get_mc_weight(double xsec, double filterEff, double lumi, double event_weight, double sum_of_event_weight)
{
    return xsec * filterEff * lumi * 1000. * event_weight / sum_of_event_weight;
}
