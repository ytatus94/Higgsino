// Provided by Lorenzo
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

    if (m < delta) {
        double radice=sqrt( pow(m,4) -pow(m,2)*(pow(mu,2) + pow(M,2) ) + pow(mu*M,2) );

        double normalizzazione = pow(  pow(m,2) -pow(m_Z,2),2);
        var= (norm* radice)/ normalizzazione  ;
        var = var* (-2*pow(m,4)+ pow(m,2)*(2*pow(M,2) - pow(mu,2)) +pow((mu*M),2));
    }

    return var;
}
