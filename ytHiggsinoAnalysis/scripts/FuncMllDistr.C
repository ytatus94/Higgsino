// Copy from Lorenzo
double FuncMllDistr(double *x, double *par){ 

    //taken from https://arxiv.org/abs/0704.2515
    //equation 4, page 9 
    //NB there is a typo in the formula (just in writing it in the the paper, not in the work)
    //the correct formula is in this code

    double m1=par[1];
    double m2=par[2];
    double mu=m2-m1;
    double m=x[0];
    double M=m1+m2;
    double m_Z=91;
    double norm=par[0]*m;

    double radice=sqrt( pow(m,4) -pow(m,2)*(pow(mu,2) + pow(M,2) ) + pow(mu*M,2) );

    double normalizzazione = pow(  pow(m,2) -pow(m_Z,2),2);
    double var= (norm* radice)/ normalizzazione  ;
    var = var* (-2*pow(m,4)+ pow(m,2)*(2*pow(M,2) - pow(mu,2)) +pow((mu*M),2));

    if(x[0]>fabs(m2) - fabs(m1)) var=1;
    return var;
}
