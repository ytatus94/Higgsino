//
// This is used to reweight Higgsino common ntuple to NUHM2
//

// Masses of N1, N2 for NUHM2
double par_NUHM2_m12_300[2] = {105.631409, 161.307800};
double par_NUHM2_m12_350[2] = {115.618103, 161.675125};
double par_NUHM2_m12_400[2] = {122.974541, 161.142700};
double par_NUHM2_m12_500[2] = {132.279099, 160.295654};
double par_NUHM2_m12_600[2] = {137.607727, 159.657379};
double par_NUHM2_m12_700[2] = {140.978836, 159.170868};
double par_NUHM2_m12_800[2] = {143.288208, 158.783905};

double HiggsinoSelector::get_dm_NUHM2(int m12)
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

double HiggsinoSelector::get_NUHM2_N1_mass(int m12)
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

double HiggsinoSelector::get_NUHM2_N2_mass(int m12)
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

double HiggsinoSelector::get_NUHM2_FuncMllDistr(double *x, double *par)
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

double HiggsinoSelector::get_NUHM2_weight(int DSID, double mass, int m12)
{
    // Don't calculate a weight unless it is one of the specified DSIDs
    double NUHM2_weight = 1.0;

    double NUHM2_N1_mass = get_NUHM2_N1_mass(m12);
    double NUHM2_N2_mass = get_NUHM2_N2_mass(m12);
    double par_NUHM2[3] = {1., NUHM2_N1_mass, -1. * NUHM2_N2_mass};

    // Mapping:
    // Higgsino_160_100 <---> m12 = 350
    // Higgsino_190_150 <---> m12 = 400, 500, 600
    // Higgsino_170_150 <---> m12 = 700, 800

    // Area ratio:
    // NUHM2 m12=300 / Higgsino 160_100: area_f5/area_f2=0.704021
    // NUHM2 m12=350 / Higgsino 160_100: area_f6/area_f2=0.277169
    // NUHM2 m12=400 / Higgsino 190_150: area_f7/area_f4=0.9631
    // NUHM2 m12=500 / Higgsino 190_150: area_f8/area_f4=0.211929
    // NUHM2 m12=600 / Higgsino 190_150: area_f9/area_f4=0.0655574
    // NUHM2 m12=700 / Higgsino 170_150: area_f10/area_f3=0.511249
    // NUHM2 m12=800 / Higgsino 170_150: area_f11/area_f3=0.232064

    double par_Higgsino[3] = {0., 0., 0.};

    // Higgsino_160_100
    if (DSID == 393510 || // N2N1
        DSID == 393559 || // C1C1
        DSID == 393412 || // N2C1p
        DSID == 393461) { // N2C1m
        if (m12 == 350) {
            par_Higgsino[0] = 0.277169; // normalization factor in order that the two curves have the same area.
            par_Higgsino[1] = 100.; // N1 mass higgsino
            par_Higgsino[2] = -160.; // N2 mass higgsino
        }
    }
    // Higgsino_170_150
    else if (DSID == 393515 || // N2N1
             DSID == 393564 || // C1C1
             DSID == 393417 || // N2C1p
             DSID == 393466) { // N2C1m
        if (m12 == 700) {
            par_Higgsino[0] = 0.511249;
        }
        else if (m12 == 800) {
            par_Higgsino[0] = 0.232064;
        }
        par_Higgsino[1] = 150.;
        par_Higgsino[2] = -170.;
    }
    // Higgsino_190_150
    else if (DSID == 393516 || // N2N1
             DSID == 393565 || // C1C1
             DSID == 393418 || // N2C1p
             DSID == 393467) { // N2C1m
        if (m12 == 400) {
            par_Higgsino[0] = 0.9631;
        }
        else if (m12 == 500) {
            par_Higgsino[0] = 0.211929;
        }
        else if (m12 == 600) {
            par_Higgsino[0] = 0.0655574;
        }
        par_Higgsino[1] = 150.;
        par_Higgsino[2] = -190.;
    }

    double Higgsino_w = get_NUHM2_FuncMllDistr(mass, par_Higgsino);
    double NUHM2_w = get_NUHM2_FuncMllDistr(mass, par_NUHM2);
    double weight_mass = NUHM2_w / Higgsino_w;

    double NUHM2_weight = weight_mass;

    // weight for the different xsec
    // weight = Xsec_NUHM2 / Xsec_Higgsino
    // For N2N1
    if (DSID == 393510 && m12 == 350)
        NUHM2_weight *= 0.500489103669;
    else if (DSID == 393516 && m12 == 400)
        NUHM2_weight *= 1.40609496035;
    else if (DSID == 393516 && m12 == 500)
        NUHM2_weight *= 1.48420174312;
    else if (DSID == 393516 && m12 == 600)
        NUHM2_weight *= 1.49620688527;
    else if (DSID == 393515 && m12 == 700)
        NUHM2_weight *= 1.18114972806;
    else if (DSID == 393515 && m12 == 800)
        NUHM2_weight *= 1.17312186754;
    // For C1C1
    else if (DSID == 393559 && m12 == 350)
        NUHM2_weight *= 0.809295197893;
    else if (DSID == 393565 && m12 == 400)
        NUHM2_weight *= 1.85763670956;
    else if (DSID == 393565 && m12 == 500)
        NUHM2_weight *= 1.60709633189;
    else if (DSID == 393565 && m12 == 600)
        NUHM2_weight *= 1.48886200733;
    else if (DSID == 393564 && m12 == 700)
        NUHM2_weight *= 1.14281934535;
    else if (DSID == 393564 && m12 == 800)
        NUHM2_weight *= 1.10758453419;
    // For N2C1p
    else if (DSID == 393412 && m12 == 350)
        NUHM2_weight *= 0.75334324027;
    else if (DSID == 393418 && m12 == 400)
        NUHM2_weight *= 1.61810558673;
    else if (DSID == 393418 && m12 == 500)
        NUHM2_weight *= 1.61195100629;
    else if (DSID == 393418 && m12 == 600)
        NUHM2_weight *= 1.60540039476;
    else if (DSID == 393417 && m12 == 700)
        NUHM2_weight *= 1.17032101263;
    else if (DSID == 393417 && m12 == 800)
        NUHM2_weight *= 1.16731420042;
    // For N2C1m
    else if (DSID == 393461 && m12 == 350)
        NUHM2_weight *= 0.751651917122;
    else if (DSID == 393467 && m12 == 400)
        NUHM2_weight *= 1.68915991429;
    else if (DSID == 393467 && m12 == 500)
        NUHM2_weight *= 1.68026588159;
    else if (DSID == 393467 && m12 == 600)
        NUHM2_weight *= 1.66943310114;
    else if (DSID == 393466 && m12 == 700)
        NUHM2_weight *= 1.1917838431;
    else if (DSID == 393466 && m12 == 800)
        NUHM2_weight *= 1.18958896195;

    return NUHM2_weight;

}
