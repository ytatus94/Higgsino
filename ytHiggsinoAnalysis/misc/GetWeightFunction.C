double EventWeightTotal;
double eventWeight;
double genWeight;
double targetLumi;
double weight_mass;


double FuncMllDistr(double x, double *par){ 

  //taken from https://arxiv.org/abs/0704.2515
  //equation 4, page 9 
  //NB there is a typo in the formula (just in writing it in the the paper, not in the work)
  //the correct formula is in this code

  double m1=par[1];
  double m2=par[2];
  double mu=m2-m1;
  double m=x;
  double M=m1+m2;
  double m_Z=91;
  double norm=par[0]*m;
  

  double radice=sqrt( pow(m,4) -pow(m,2)*(pow(mu,2) + pow(M,2) ) + pow(mu*M,2) );

  double normalizzazione = pow(  pow(m,2) -pow(m_Z,2),2);
  double var= (norm* radice)/ normalizzazione  ;
  var = var* (-2*pow(m,4)+ pow(m,2)*(2*pow(M,2) - pow(mu,2)) +pow((mu*M),2));
  if(x>fabs(m2) - fabs(m1)) var=1;
  return var; 
}

void GetWeightMass(double mass){
// The weight depends on the mass splitting

int isData = DatasetNumber; // Is the dataset DIDS. This is used to differentiate the mass splittings
double var=1.;
weight_mass=1.;
double parH[3];
double parS[3];

if(isData == 393463 || isData == 393512 || isData == 393414 || isData ==393561 && isData== 393407|| isData== 393456 || isData==393400 || isData==393449){ 
//Delta M = 3 GeV
 parH[0]=3.00049;  // normalization factor in order that the two curves have the same area.
 parH[1]=100;      // N1 mass higgsino
 parH[2]=-103;     // N2 mass higgsino
 parS[0]=1;        // normalization
 parS[1]=100;      // N1 mass wino bino
 parS[2]=103;      // N2 mass wino bino
}  

if(isData== 393429 || isData== 393478 || isData==393415 || isData== 393422 || isData== 393471 || isData==393408 || isData==393457 || isData==393436 || isData==393450 || isData==393443 || isData==393464 || isData==393492){
//Delta M = 5 GeV
 parH[0]=3.00142;
 parH[1]=100;
 parH[2]=-105;
 parS[0]=1;
 parS[1]=100;
 parS[2]=105;

}

if(isData== 393416 || isData==393465 || isData== 393430 || isData== 393479 || isData==393409 || isData==393458 || isData==393402 || isData==393423|| isData==393437 || isData==393444 || isData==393486 || isData==393451 || isData==393472){
 //Delta M = 10 GeV

 parH[0]=3.0061;
 parH[1]=100;
 parH[2]=-110;
 parS[0]=1;
 parS[1]=100;
 parS[2]=110;
 
}
if(isData== 393417 || isData== 393466 || isData==393410 || isData==393459 || isData==393431 || isData==393480 || isData==393403 || isData==393424 || isData==393445 || isData==393452 || isData==393487 || isData==393494){
 //Delta M = 20 GeV

 parH[0]=3.02817;
 parH[1]=100;
 parH[2]=-120;
 parS[0]=1;
 parS[1]=100;
 parS[2]=120;

}

if(isData== 393404 || isData== 393453 || isData== 393418 || isData== 393467|| isData==393432 || isData==393439 || isData==393446 || isData==393460 || isData==393474 || isData==393481 || isData==393488){
//Delta M = 34 GeV

 parH[0]=3.15156;
 parH[1]=100;
 parH[2]=-140;
 parS[0]=1;
 parS[1]=100;
 parS[2]=140;


}

if(isData== 393419 || isData== 393468|| isData==393405 || isData==393412 || isData==393426 || isData==393433 || isData==393440 || isData==393447 || isData==393454 || isData==393482 || isData==393489 || isData==393495){
//Delta M = 100 GeV

 parH[0]=3.50164;
 parH[1]=100;
 parH[2]=-160;
 parS[0]=1;
 parS[1]=100;
 parS[2]=160;

}


double hig_w=FuncMllDistr(mass,parH);
double stop_w=FuncMllDistr(mass,parS);
var=stop_w/hig_w;
weight_mass= var;



}

void EventLoopLike(){

TH1F *h_mll = new TH1F("h_mll","h_mll",100,0.,100.); //mll histogram
  //Get events somehow
  int counter=-1; // 

  for(int i=0; i<counter; i++){
    //evaluate invariant mass
    double mll = (lep1+lep2).M(); // or take it from ntuples

    //Get weights
    EventWeightTotal =   eventWeight  *  genWeight   *  targetLumi; // like this, or all the weight that you like

    weight_mass = 1.; // set to one just in case

    // insert here your higgsino shaped mll 
    GetWeightMass(mll); //mll MUST be in GeV
    //now you have a wino-bino shape

    EventWeightTotal=EventWeightTotal*weight_mass;  // multiply multiply weight_mass  

    //now you have to change the cross section. Is ~ X 4.3 for N2C1 and X 2.6 for N2N1 

    int isData = DatasetNumber; 
    if (isData == 393400) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_83_80_2LMET50_MadSpin
    else if(isData == 393463 ) EventWeightTotal=EventWeightTotal*4.3;
    else if(isData == 393414 ) EventWeightTotal=EventWeightTotal*4.3;
    else if(isData == 393512 ) EventWeightTotal=EventWeightTotal*2.6;
    else if (isData == 393401) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_85_80_2LMET50_MadSpin
    else if (isData == 393402) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_90_80_2LMET50_MadSpin
    else if (isData == 393403) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_100_80_2LMET50_MadSpin
    else if (isData == 393404) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_120_80_2LMET50_MadSpin
    else if (isData == 393405) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_140_80_2LMET50_MadSpin
    else if (isData == 393406) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_180_80_2LMET50_MadSpin
    else if (isData == 393407) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_103_100_2LMET50_MadSpin
    else if (isData == 393408) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_105_100_2LMET50_MadSpin
    else if (isData == 393409) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_110_100_2LMET50_MadSpin
    else if (isData == 393410) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_120_100_2LMET50_MadSpin
    else if (isData == 393411) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_140_100_2LMET50_MadSpin
    else if (isData == 393412) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_160_100_2LMET50_MadSpin
    else if (isData == 393413) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_200_100_2LMET50_MadSpin
    else if (isData == 393415) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_155_150_2LMET50_MadSpin
    else if (isData == 393416) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_160_150_2LMET50_MadSpin
    else if (isData == 393417) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_170_150_2LMET50_MadSpin
    else if (isData == 393418) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_190_150_2LMET50_MadSpin
    else if (isData == 393419) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_210_150_2LMET50_MadSpin
    else if (isData == 393420) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_250_150_2LMET50_MadSpin
    else if (isData == 393421) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_203_200_2LMET50_MadSpin
    else if (isData == 393422) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_205_200_2LMET50_MadSpin
    else if (isData == 393423) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_210_200_2LMET50_MadSpin
    else if (isData == 393424) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_220_200_2LMET50_MadSpin
    else if (isData == 393425) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_240_200_2LMET50_MadSpin
    else if (isData == 393426) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_260_200_2LMET50_MadSpin
    else if (isData == 393427) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_300_200_2LMET50_MadSpin
    else if (isData == 393428) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_253_250_2LMET50_MadSpin
    else if (isData == 393429) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_255_250_2LMET50_MadSpin
    else if (isData == 393430) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_260_250_2LMET50_MadSpin
    else if (isData == 393431) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_270_250_2LMET50_MadSpin
    else if (isData == 393432) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_290_250_2LMET50_MadSpin
    else if (isData == 393433) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_310_250_2LMET50_MadSpin
    else if (isData == 393434) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_350_250_2LMET50_MadSpin
    else if (isData == 393436) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_305_300_2LMET50_MadSpin
    else if (isData == 393437) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_310_300_2LMET50_MadSpin
    else if (isData == 393438) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_320_300_2LMET50_MadSpin
    else if (isData == 393439) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_340_300_2LMET50_MadSpin
    else if (isData == 393440) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_360_300_2LMET50_MadSpin
    else if (isData == 393441) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_400_300_2LMET50_MadSpin
    else if (isData == 393442) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_403_400_2LMET50_MadSpin
    else if (isData == 393443) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_405_400_2LMET50_MadSpin
    else if (isData == 393444) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_410_400_2LMET50_MadSpin
    else if (isData == 393445) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_420_400_2LMET50_MadSpin
    else if (isData == 393446) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_440_400_2LMET50_MadSpin
    else if (isData == 393447) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_460_400_2LMET50_MadSpin
    else if (isData == 393448) EventWeightTotal=EventWeightTotal*4.3; //N2C1p_500_400_2LMET50_MadSpin
    else if (isData == 393449) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_83_80_2LMET50_MadSpin
    else if (isData == 393450) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_85_80_2LMET50_MadSpin
    else if (isData == 393451) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_90_80_2LMET50_MadSpin
    else if (isData == 393452) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_100_80_2LMET50_MadSpin
    else if (isData == 393453) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_120_80_2LMET50_MadSpin
    else if (isData == 393454) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_140_80_2LMET50_MadSpin
    else if (isData == 393455) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_180_80_2LMET50_MadSpin
    else if (isData == 393456) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_103_100_2LMET50_MadSpin
    else if (isData == 393457) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_105_100_2LMET50_MadSpin
    else if (isData == 393458) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_110_100_2LMET50_MadSpin
    else if (isData == 393459) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_120_100_2LMET50_MadSpin
    else if (isData == 393460) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_140_100_2LMET50_MadSpin
    else if (isData == 393461) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_160_100_2LMET50_MadSpin
    else if (isData == 393462) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_200_100_2LMET50_MadSpin
    else if (isData == 393463) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_153_150_2LMET50_MadSpin
    else if (isData == 393464) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_155_150_2LMET50_MadSpin
    else if (isData == 393465) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_160_150_2LMET50_MadSpin
    else if (isData == 393466) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_170_150_2LMET50_MadSpin
    else if (isData == 393467) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_190_150_2LMET50_MadSpin
    else if (isData == 393468) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_210_150_2LMET50_MadSpin
    else if (isData == 393469) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_250_150_2LMET50_MadSpin
    else if (isData == 393471) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_205_200_2LMET50_MadSpin
    else if (isData == 393472) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_210_200_2LMET50_MadSpin
    else if (isData == 393473) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_220_200_2LMET50_MadSpin
    else if (isData == 393474) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_240_200_2LMET50_MadSpin
    else if (isData == 393475) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_260_200_2LMET50_MadSpin
    else if (isData == 393476) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_300_200_2LMET50_MadSpin
    else if (isData == 393478) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_255_250_2LMET50_MadSpin
    else if (isData == 393479) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_260_250_2LMET50_MadSpin
    else if (isData == 393480) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_270_250_2LMET50_MadSpin
    else if (isData == 393481) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_290_250_2LMET50_MadSpin
    else if (isData == 393482) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_310_250_2LMET50_MadSpin
    else if (isData == 393483) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_350_250_2LMET50_MadSpin
    else if (isData == 393485) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_305_300_2LMET50_MadSpin
    else if (isData == 393486) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_310_300_2LMET50_MadSpin
    else if (isData == 393487) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_320_300_2LMET50_MadSpin
    else if (isData == 393488) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_340_300_2LMET50_MadSpin
    else if (isData == 393489) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_360_300_2LMET50_MadSpin
    else if (isData == 393490) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_400_300_2LMET50_MadSpin
    else if (isData == 393492) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_405_400_2LMET50_MadSpin
    else if (isData == 393493) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_410_400_2LMET50_MadSpin
    else if (isData == 393494) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_420_400_2LMET50_MadSpin
    else if (isData == 393495) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_440_400_2LMET50_MadSpin
    else if (isData == 393496) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_460_400_2LMET50_MadSpin
    else if (isData == 393497) EventWeightTotal=EventWeightTotal*4.3; //N2C1m_500_400_2LMET50_MadSpin
    else if (isData == 393498) EventWeightTotal=EventWeightTotal*2.6; //N2N1_83_80_2LMET50_MadSpin
    else if (isData == 393499) EventWeightTotal=EventWeightTotal*2.6; //N2N1_85_80_2LMET50_MadSpin
    else if (isData == 393500) EventWeightTotal=EventWeightTotal*2.6; //N2N1_90_80_2LMET50_MadSpin
    else if (isData == 393501) EventWeightTotal=EventWeightTotal*2.6; //N2N1_100_80_2LMET50_MadSpin
    else if (isData == 393502) EventWeightTotal=EventWeightTotal*2.6; //N2N1_120_80_2LMET50_MadSpin
    else if (isData == 393503) EventWeightTotal=EventWeightTotal*2.6; //N2N1_140_80_2LMET50_MadSpin
    else if (isData == 393505) EventWeightTotal=EventWeightTotal*2.6; //N2N1_103_100_2LMET50_MadSpin
    else if (isData == 393506) EventWeightTotal=EventWeightTotal*2.6; //N2N1_105_100_2LMET50_MadSpin
    else if (isData == 393507) EventWeightTotal=EventWeightTotal*2.6; //N2N1_110_100_2LMET50_MadSpin
    else if (isData == 393508) EventWeightTotal=EventWeightTotal*2.6; //N2N1_120_100_2LMET50_MadSpin
    else if (isData == 393509) EventWeightTotal=EventWeightTotal*2.6; //N2N1_140_100_2LMET50_MadSpin
    else if (isData == 393510) EventWeightTotal=EventWeightTotal*2.6; //N2N1_160_100_2LMET50_MadSpin
    else if (isData == 393511) EventWeightTotal=EventWeightTotal*2.6; //N2N1_200_100_2LMET50_MadSpin
    else if (isData == 393514) EventWeightTotal=EventWeightTotal*2.6; //N2N1_160_150_2LMET50_MadSpin
    else if (isData == 393515) EventWeightTotal=EventWeightTotal*2.6; //N2N1_170_150_2LMET50_MadSpin
    else if (isData == 393516) EventWeightTotal=EventWeightTotal*2.6; //N2N1_190_150_2LMET50_MadSpin
    else if (isData == 393517) EventWeightTotal=EventWeightTotal*2.6; //N2N1_210_150_2LMET50_MadSpin
    else if (isData == 393518) EventWeightTotal=EventWeightTotal*2.6; //N2N1_250_150_2LMET50_MadSpin
    else if (isData == 393519) EventWeightTotal=EventWeightTotal*2.6; //N2N1_203_200_2LMET50_MadSpin
    else if (isData == 393520) EventWeightTotal=EventWeightTotal*2.6; //N2N1_205_200_2LMET50_MadSpin
    else if (isData == 393521) EventWeightTotal=EventWeightTotal*2.6; //N2N1_210_200_2LMET50_MadSpin
    else if (isData == 393522) EventWeightTotal=EventWeightTotal*2.6; //N2N1_220_200_2LMET50_MadSpin
    else if (isData == 393523) EventWeightTotal=EventWeightTotal*2.6; //N2N1_240_200_2LMET50_MadSpin
    else if (isData == 393524) EventWeightTotal=EventWeightTotal*2.6; //N2N1_260_200_2LMET50_MadSpin
    else if (isData == 393525) EventWeightTotal=EventWeightTotal*2.6; //N2N1_300_200_2LMET50_MadSpin
    else if (isData == 393527) EventWeightTotal=EventWeightTotal*2.6; //N2N1_255_250_2LMET50_MadSpin
    else if (isData == 393528) EventWeightTotal=EventWeightTotal*2.6; //N2N1_260_250_2LMET50_MadSpin
    else if (isData == 393529) EventWeightTotal=EventWeightTotal*2.6; //N2N1_270_250_2LMET50_MadSpin
    else if (isData == 393530) EventWeightTotal=EventWeightTotal*2.6; //N2N1_290_250_2LMET50_MadSpin
    else if (isData == 393531) EventWeightTotal=EventWeightTotal*2.6; //N2N1_310_250_2LMET50_MadSpin
    else if (isData == 393532) EventWeightTotal=EventWeightTotal*2.6; //N2N1_350_250_2LMET50_MadSpin
    else if (isData == 393534) EventWeightTotal=EventWeightTotal*2.6; //N2N1_305_300_2LMET50_MadSpin
    else if (isData == 393535) EventWeightTotal=EventWeightTotal*2.6; //N2N1_310_300_2LMET50_MadSpin
    else if (isData == 393536) EventWeightTotal=EventWeightTotal*2.6; //N2N1_320_300_2LMET50_MadSpin
    else if (isData == 393537) EventWeightTotal=EventWeightTotal*2.6; //N2N1_340_300_2LMET50_MadSpin
    else if (isData == 393538) EventWeightTotal=EventWeightTotal*2.6; //N2N1_360_300_2LMET50_MadSpin
    else if (isData == 393539) EventWeightTotal=EventWeightTotal*2.6; //N2N1_400_300_2LMET50_MadSpin
    else if (isData == 393541) EventWeightTotal=EventWeightTotal*2.6; //N2N1_405_400_2LMET50_MadSpin
    else if (isData == 393542) EventWeightTotal=EventWeightTotal*2.6; //N2N1_410_400_2LMET50_MadSpin
    else if (isData == 393543) EventWeightTotal=EventWeightTotal*2.6; //N2N1_420_400_2LMET50_MadSpin
    else if (isData == 393544) EventWeightTotal=EventWeightTotal*2.6; //N2N1_440_400_2LMET50_MadSpin
    else if (isData == 393545) EventWeightTotal=EventWeightTotal*2.6; //N2N1_460_400_2LMET50_MadSpin
    else if (isData == 393546) EventWeightTotal=EventWeightTotal*2.6; //N2N1_500_400_2LMET50_MadSpin

    h_mll->Fill(mll,EventWeightTotal);            // Fill histogram

    
  }

  //the rest of the program
}
