from ROOT import TColor
from ROOT import kBlack,kWhite,kGray,kRed,kPink,kMagenta,kViolet,kBlue,kAzure,kCyan,kTeal,kGreen,kSpring,kYellow,kOrange

#____________________________________________________________________________
def configure_samples():


  # Blues
  #myLighterBlue=TColor.GetColor('#deebf7')
  myLighterBlue=kAzure-2
  myLightBlue  =TColor.GetColor('#9ecae1')
  myMediumBlue =TColor.GetColor('#0868ac')
  myDarkBlue   =TColor.GetColor('#08306b')

  # Greens
  myLightGreen   =TColor.GetColor('#c7e9c0')
  myMediumGreen  =TColor.GetColor('#41ab5d')
  myDarkGreen    =TColor.GetColor('#006d2c')

  # Oranges
  myLighterOrange=TColor.GetColor('#ffeda0')
  myLightOrange  =TColor.GetColor('#fec49f')
  myMediumOrange =TColor.GetColor('#fe9929')

  # Greys
  myLightestGrey=TColor.GetColor('#f0f0f0')
  myLighterGrey=TColor.GetColor('#e3e3e3')
  myLightGrey  =TColor.GetColor('#969696')

  # Pinks
  myLightPink = TColor.GetColor('#fde0dd')
  myMediumPink = TColor.GetColor('#fcc5c0')
  myDarkPink = TColor.GetColor('#dd3497')

  # background path bkg_suffix
  # Joey's configuration
  #bkg_suffix='_SusySkimHiggsino_v1.9_SUSY16_tree_LOOSE_NOMINAL.root'
  #sig_suffix='_SusySkimHiggsino_v1.9_SUSY16_tree_LOOSE_NOMINAL.root'
  
  # Jesse's configuration
  #bkg_suffix='_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root'
  bkg_suffix='_SusySkimHiggsino_v1.9_hadded_tree.root'
  #sig_suffix='_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root'
  #sig_suffix='_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys.root'
  sig_suffix='_SusySkimHiggsino_v1.8b_SUSY16_tree_NoSys.root'
  d_samp = {

    'data'     :{'type':'data','leg':'Data',                        'f_color':0,'l_color':0,  'path':'data'+bkg_suffix},
    #'fakes'    :{'type':'bkg','leg':'Fake leptons',                        'f_color':myLighterGrey,  'path':'fakes'+bkg_suffix},
    'fakes2Lb_DijetFFs'    :{'type':'bkg','leg':'Fake leptons',                        'f_color':myLighterGrey,  'path':'fakes2Lb_DijetFFs_SusySkimHiggsino_v1.9_SUSY16_tree_NoSys.root'},
    'top'      :{'type':'bkg', 'leg':'t#bar{t} & Single top',       'f_color':myLightBlue,   'path':'top'+bkg_suffix},
    'Zttjets'  :{'type':'bkg', 'leg':'Z(#rightarrow#tau#tau)+jets', 'f_color':myMediumGreen,  'path':'Zttjets'+bkg_suffix},
    'diboson'  :{'type':'bkg', 'leg':'Diboson',                     'f_color':myMediumOrange, 'path':'diboson'+bkg_suffix},
    'other'    :{'type':'bkg', 'leg':'Others',                       'f_color':myLighterOrange,'path':'other'+bkg_suffix},

    # Signals
    'MGPy8EG_A14N23LO_SlepSlep_direct_100p0_90p0_MET50' :{'type':'sig','leg':'#tilde{#font[12]{l}} [100, 90]','l_color':kOrange+3,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_100p0_90p0_MET50'+sig_suffix},
    'MGPy8EG_A14N23LO_SlepSlep_direct_110p0_90p0_MET50' :{'type':'sig','leg':'#tilde{#font[12]{l}} [110, 90]','l_color':kRed+3,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_110p0_90p0_MET50'+sig_suffix},
    'MGPy8EG_A14N23LO_SlepSlep_direct_102p0_100p0_MET50':{'type':'sig','leg':'#tilde{#font[12]{l}} [102, 100]','l_color':kAzure+4,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_102p0_100p0_MET50'+sig_suffix},
    'MGPy8EG_A14N23LO_SlepSlep_direct_105p0_100p0_MET50':{'type':'sig','leg':'#tilde{#font[12]{l}} [105, 100]','l_color':kCyan+2,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_105p0_100p0_MET50'+sig_suffix},
    'MGPy8EG_A14N23LO_SlepSlep_direct_110p0_100p0_MET50':{'type':'sig','leg':'#tilde{#font[12]{l}} [110, 100]','l_color':kViolet+2,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_110p0_100p0_MET50'+sig_suffix},
    'MGPy8EG_A14N23LO_SlepSlep_direct_120p0_100p0_MET50':{'type':'sig','leg':'#tilde{#font[12]{l}} [120, 100]','l_color':kMagenta-9,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_120p0_100p0_MET50'+sig_suffix},
    'MGPy8EG_A14N23LO_SlepSlep_direct_140p0_100p0_MET50':{'type':'sig','leg':'#tilde{#font[12]{l}} [140, 100]','l_color':kOrange+2,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_140p0_100p0_MET50'+sig_suffix},
    
    'MGPy8EG_A14N23LO_SlepSlep_direct_100p0_90p0_MET50':{'type':'sig','leg':'#tilde{#font[12]{l}} [100, 90]','l_color':kAzure+4,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_100p0_90p0_MET50'+sig_suffix},
    'MGPy8EG_A14N23LO_SlepSlep_direct_130p0_120p0_MET50':{'type':'sig','leg':'#tilde{#font[12]{l}} [130, 120]','l_color':kCyan-3,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_130p0_120p0_MET50'+sig_suffix},
    'MGPy8EG_A14N23LO_SlepSlep_direct_150p0_140p0_MET50':{'type':'sig','leg':'#tilde{#font[12]{l}} [150, 140]','l_color':kGray+1,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_150p0_140p0_MET50'+sig_suffix},
    'MGPy8EG_A14N23LO_SlepSlep_direct_190p0_180p0_MET50':{'type':'sig','leg':'#tilde{#font[12]{l}} [190, 180]','l_color':kMagenta-9,'path':'MGPy8EG_A14N23LO_SlepSlep_direct_190p0_180p0_MET50'+sig_suffix},

    'MGPy8EG_A14N23LO_SM_Higgsino_90_80_2LMET50_MadSpin'  :{'type':'sig','leg':'#tilde{H} [90,  80]', 'l_color':kBlue+3,'path':'MGPy8EG_A14N23LO_SM_Higgsino_90_80_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_100_80_2LMET50_MadSpin' :{'type':'sig','leg':'#tilde{H} [100, 80]', 'l_color':kMagenta-3,'path':'MGPy8EG_A14N23LO_SM_Higgsino_100_80_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_103_100_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [103, 100]','l_color':kAzure+4,'path':'MGPy8EG_A14N23LO_SM_Higgsino_103_100_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_105_100_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [105, 100]','l_color':kCyan+2,'path':'MGPy8EG_A14N23LO_SM_Higgsino_105_100_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_110_100_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [110, 100]','l_color':kRed+2,'path':'MGPy8EG_A14N23LO_SM_Higgsino_110_100_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_120_100_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [120, 100]','l_color':kViolet+5,'path':'MGPy8EG_A14N23LO_SM_Higgsino_120_100_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [140, 100]','l_color':kAzure+3,'path':'MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_220_200_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [220, 200]','l_color':kAzure+3,'path':'MGPy8EG_A14N23LO_SM_Higgsino_220_200_2LMET50_MadSpin'+sig_suffix},
    
    'MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [160, 100]','l_color':kViolet+1,'path':'MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_160_150_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [160, 150]','l_color':kViolet+2,'path':'MGPy8EG_A14N23LO_SM_Higgsino_160_150_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [170, 150]','l_color':kViolet+3,'path':'MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin':{'type':'sig','leg':'#tilde{H} [190, 150]','l_color':kViolet+4,'path':'MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin'+sig_suffix},

    'MGPy8EG_A14N23LO_NUHM2_m12_300_weak_2LMET50_MadSpin':{'type':'sig','leg':'NUHM2 m12=300','l_color':kRed,'path':'MGPy8EG_A14N23LO_NUHM2_m12_300_weak_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_NUHM2_m12_350_weak_2LMET50_MadSpin':{'type':'sig','leg':'NUHM2 m12=350','l_color':kRed-1,'path':'MGPy8EG_A14N23LO_NUHM2_m12_350_weak_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_NUHM2_m12_400_weak_2LMET50_MadSpin':{'type':'sig','leg':'NUHM2 m12=400','l_color':kRed-2,'path':'MGPy8EG_A14N23LO_NUHM2_m12_400_weak_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_NUHM2_m12_500_weak_2LMET50_MadSpin':{'type':'sig','leg':'NUHM2 m12=500','l_color':kRed-3,'path':'MGPy8EG_A14N23LO_NUHM2_m12_500_weak_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_NUHM2_m12_600_weak_2LMET50_MadSpin':{'type':'sig','leg':'NUHM2 m12=600','l_color':kRed-4,'path':'MGPy8EG_A14N23LO_NUHM2_m12_600_weak_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_NUHM2_m12_700_weak_2LMET50_MadSpin':{'type':'sig','leg':'NUHM2 m12=700','l_color':kRed-5,'path':'MGPy8EG_A14N23LO_NUHM2_m12_700_weak_2LMET50_MadSpin'+sig_suffix},
    'MGPy8EG_A14N23LO_NUHM2_m12_800_weak_2LMET50_MadSpin':{'type':'sig','leg':'NUHM2 m12=800','l_color':kRed-6,'path':'MGPy8EG_A14N23LO_NUHM2_m12_800_weak_2LMET50_MadSpin'+sig_suffix},


    }

  return d_samp


