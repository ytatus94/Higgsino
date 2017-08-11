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