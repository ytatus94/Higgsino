#____________________________________________________________________________
def configure_cuts(var, add_cuts, sig_reg, print_cuts=True):

  # Putting cuts as lists allows easy construction of N-1

  nLep2 = ['nLep_signal == 2 && nLep_base == 2']
  # OS = opposite sign, SS = same sign
  l_OS  = ['lep1Charge != lep2Charge']
  l_SS  = ['lep1Charge == lep2Charge']

  # SF = same flavour (ee, mm), DF = different flavour (em, me), AF = all flavour (ee, mm, em, me)
  l_SF  = ['lep1Flavor == lep2Flavor']
  l_DF  = ['lep1Flavor != lep2Flavor']
 
  l_2e  = ['lep1Flavor == 1 && lep2Flavor == 1']
  l_2m  = ['lep1Flavor == 2 && lep2Flavor == 2']
  l_em  = ['lep1Flavor == 1 && lep2Flavor == 2']
  l_me  = ['lep1Flavor == 2 && lep2Flavor == 1']
  l_ee_me = ['( (lep1Flavor == 1 && lep2Flavor == 1) || (lep1Flavor == 2 && lep2Flavor == 1) )']
  l_mm_em = ['( (lep1Flavor == 2 && lep2Flavor == 2) || (lep1Flavor == 1 && lep2Flavor == 2) )']
  
  l_common = [
    'met_Et>200',
    'jetPt[0]>100',
    'DPhiJ1Met > 2.0',
    'minDPhiAllJetsMet > 0.4',
    'FS != 206 && FS != 207', 
    'trigMatch_metTrig',
    'lep1Pt > 5',
    'Rll > 0.05',
    'mll > 1',
    '(mll < 3 || mll > 3.2)',
    'mll < 60',
    '(lep1Author != 16 && lep2Author != 16)',
    '((lep1TruthMatched && lep2TruthMatched) || (DatasetNumber >= 407311 && DatasetNumber <= 407315))'
  ]  

  l_common_OS = l_common + nLep2 + l_OS
  l_common_SS = l_common + nLep2 + l_SS

  # Define regions
  l_CR_top = [
    'METOverHTLep > 5.0',
    '(MTauTau < 0 || MTauTau > 160)',
    'nBJet20_MV2c10 >= 1',
  ]

  l_CR_tau = [
    '( METOverHTLep > 4.0 ) && ( METOverHTLep < 8.0 )',
    '(MTauTau > 60 && MTauTau < 120)',
    'nBJet20_MV2c10 == 0',
  ]
  
  l_VR_VV = [
    'METOverHTLep < 3.0',
    '(MTauTau < 0 || MTauTau > 160)',
    'nBJet20_MV2c10 == 0',
  ]

  l_VR_SS = [
    'METOverHTLep > 5.0',
    '(MTauTau < 0 || MTauTau > 160)',
    'nBJet20_MV2c10 == 0',
  ]

  l_VR_SS_loose = [
    '(MTauTau < 0 || MTauTau > 160)',
    'nBJet20_MV2c10 == 0',
  ]

  l_SR_MLL = [
    'METOverHTLep > max(5.0, 15 - 2*mll)',
    '(MTauTau < 0 || MTauTau > 160)',
    'nBJet20_MV2c10 == 0',
    'Rll < 2.0',
    'mt_lep1 < 70',
  ]

  l_SR_MT2 = [
    'METOverHTLep > max( 3.0, 15 - 2*(mt2leplsp_100 - 100) )',
    #'METOverHTLep > 5',
    '(MTauTau < 0 || MTauTau > 160)',
    'nBJet20_MV2c10 == 0',
  ]
  
  l_eMLLa = ['mll >= 1 && mll < 3']
  l_eMLLb = ['mll >= 3.2 && mll < 5']
  l_eMLLc = ['mll >= 5 && mll < 10']
  
  l_iMLLa = ['mll < 3']
  l_iMLLb = ['mll < 5']
  l_iMLLc = ['mll < 10']
  l_iMLLd = ['mll < 20']
  l_iMLLe = ['mll < 30']
  l_iMLLf = ['mll < 40']
  l_iMLLg = ['mll < 60']
  
  l_iMT2a = ['mt2leplsp_100 < 102']
  l_iMT2b = ['mt2leplsp_100 < 105']
  l_iMT2c = ['mt2leplsp_100 < 110']
  l_iMT2d = ['mt2leplsp_100 < 120']
  l_iMT2e = ['mt2leplsp_100 < 130']
  l_iMT2f = ['mt2leplsp_100 >= 100']
  l_iMT2f = []
  
  # =============================================
  d_cuts = {
    'preselect'     : ['FS != 206 && FS != 207'],
    'CR-top-AF'     : l_common_OS +  l_CR_top,
    'CR-tau-AF'     : l_common_OS +  l_CR_tau,

    'CR-top-ee'     : l_common_OS +  l_CR_top + l_2e,
    'CR-tau-ee'     : l_common_OS +  l_CR_tau + l_2e,

    'CR-top-mm'     : l_common_OS +  l_CR_top + l_2m,
    'CR-tau-mm'     : l_common_OS +  l_CR_tau + l_2m,

    'CR-top-em'     : l_common_OS +  l_CR_top + l_em,
    'CR-tau-em'     : l_common_OS +  l_CR_tau + l_em,

    'CR-top-me'     : l_common_OS +  l_CR_top + l_me,
    'CR-tau-me'     : l_common_OS +  l_CR_tau + l_me,

    'CR-top-DF'     : l_common_OS +  l_CR_top + l_DF,
    'CR-tau-DF'     : l_common_OS +  l_CR_tau + l_DF,

    'CR-top-SF'     : l_common_OS +  l_CR_top + l_SF,
    'CR-tau-SF'     : l_common_OS +  l_CR_tau + l_SF, 
    
    'VR-top-SS-ee'  : l_common_SS +  l_CR_top + l_2e,
    'VR-top-SS-mm'  : l_common_SS +  l_CR_top + l_2m,

    'VR-top-SS-ee-me'  : l_common_SS +  l_CR_top + l_ee_me,
    'VR-top-SS-mm-em'  : l_common_SS +  l_CR_top + l_mm_em,
    
    'VR-VV-AF'      : l_common_OS +  l_VR_VV,
    'VR-VV-ee'      : l_common_OS +  l_VR_VV  + l_2e,
    'VR-VV-mm'      : l_common_OS +  l_VR_VV  + l_2m,
    'VR-VV-em'      : l_common_OS +  l_VR_VV  + l_em,
    'VR-VV-me'      : l_common_OS +  l_VR_VV  + l_me,
    'VR-VV-DF'      : l_common_OS +  l_VR_VV  + l_DF,
    'VR-VV-SF'      : l_common_OS +  l_VR_VV  + l_SF,
    
    'VR-SS-AF'      : l_common_SS + l_VR_SS,
    'VR-SS-SF'      : l_common_SS + l_VR_SS + l_SF,
    'VR-SS-ee-me'   : l_common_SS + l_VR_SS + l_ee_me,
    'VR-SS-mm-em'   : l_common_SS + l_VR_SS + l_mm_em,
    'VR-SS-me'      : l_common_SS + l_VR_SS + l_me,
    'VR-SS-em'      : l_common_SS + l_VR_SS + l_em,
    'VR-SS-ee'      : l_common_SS + l_VR_SS + l_2e,
    'VR-SS-mm'      : l_common_SS + l_VR_SS + l_2m,
    'VR-SS-ee-me-loose'   : l_common_SS + l_VR_SS_loose + l_ee_me,
    'VR-SS-mm-em-loose'   : l_common_SS + l_VR_SS_loose + l_mm_em,

    'VRem-iMLLg-em' : l_common_OS + l_SR_MLL + l_iMLLg + l_em,
    'VRme-iMLLg-me' : l_common_OS + l_SR_MLL + l_iMLLg + l_me,
    'VRem-iMT2f-ee' : l_common_OS + l_SR_MT2 + l_iMT2f + l_em,
    'VRme-iMT2f-me' : l_common_OS + l_SR_MT2 + l_iMT2f + l_me,
    'VRDF-iMT2f-DF' : l_common_OS + l_SR_MT2 + l_iMT2f + l_DF, 
    'VRDF-iMLLg-DF' : l_common_OS + l_SR_MLL + l_iMLLg + l_DF, 

    'SRee-iMLLa-ee' : l_common_OS + l_SR_MLL + l_iMLLa + l_2e,
    'SRmm-iMLLa-mm' : l_common_OS + l_SR_MLL + l_iMLLa + l_2m,
    'SRSF-iMLLa-SF' : l_common_OS + l_SR_MLL + l_iMLLa + l_SF,
    'SRee-eMLLa-ee' : l_common_OS + l_SR_MLL + l_eMLLa + l_2e,
    'SRmm-eMLLa-mm' : l_common_OS + l_SR_MLL + l_eMLLa + l_2m,
    
    'SRee-iMLLb-ee' : l_common_OS + l_SR_MLL + l_iMLLb + l_2e,
    'SRmm-iMLLb-mm' : l_common_OS + l_SR_MLL + l_iMLLb + l_2m,
    'SRSF-iMLLb-SF' : l_common_OS + l_SR_MLL + l_iMLLb + l_SF,
    'SRee-eMLLb-ee' : l_common_OS + l_SR_MLL + l_eMLLb + l_2e,
    'SRmm-eMLLb-mm' : l_common_OS + l_SR_MLL + l_eMLLb + l_2m,
    
    'SRee-iMLLc-ee' : l_common_OS + l_SR_MLL + l_iMLLc + l_2e,
    'SRmm-iMLLc-mm' : l_common_OS + l_SR_MLL + l_iMLLc + l_2m,
    'SRSF-iMLLc-SF' : l_common_OS + l_SR_MLL + l_iMLLc + l_SF,

    'SRee-iMLLd-ee' : l_common_OS + l_SR_MLL + l_iMLLd + l_2e, 
    'SRmm-iMLLd-mm' : l_common_OS + l_SR_MLL + l_iMLLd + l_2m,
    'SRSF-iMLLd-SF' : l_common_OS + l_SR_MLL + l_iMLLd + l_SF,
    'SRee-iMLLe-ee' : l_common_OS + l_SR_MLL + l_iMLLe + l_2e,
    'SRmm-iMLLe-mm' : l_common_OS + l_SR_MLL + l_iMLLe + l_2m,
    'SRSF-iMLLe-SF' : l_common_OS + l_SR_MLL + l_iMLLe + l_SF,
    'SRee-iMLLf-ee' : l_common_OS + l_SR_MLL + l_iMLLf + l_2e,
    'SRmm-iMLLf-mm' : l_common_OS + l_SR_MLL + l_iMLLf + l_2m,
    'SRSF-iMLLf-SF' : l_common_OS + l_SR_MLL + l_iMLLf + l_SF,
    'SRee-iMLLg-ee' : l_common_OS + l_SR_MLL + l_iMLLg + l_2e,
    'SRmm-iMLLg-mm' : l_common_OS + l_SR_MLL + l_iMLLg + l_2m,
    'SRSF-iMLLg-SF' : l_common_OS + l_SR_MLL + l_iMLLg + l_SF, 

    'SRee-iMT2a-ee' : l_common_OS + l_SR_MT2 + l_iMT2a + l_2e,
    'SRmm-iMT2a-mm' : l_common_OS + l_SR_MT2 + l_iMT2a + l_2m,
    'SRSF-iMT2a-SF' : l_common_OS + l_SR_MT2 + l_iMT2a + l_SF,
    'SRee-iMT2b-ee' : l_common_OS + l_SR_MT2 + l_iMT2b + l_2e,
    'SRmm-iMT2b-mm' : l_common_OS + l_SR_MT2 + l_iMT2b + l_2m,
    'SRSF-iMT2b-SF' : l_common_OS + l_SR_MT2 + l_iMT2b + l_SF,
    'SRee-iMT2c-ee' : l_common_OS + l_SR_MT2 + l_iMT2c + l_2e,
    'SRmm-iMT2c-mm' : l_common_OS + l_SR_MT2 + l_iMT2c + l_2m,
    'SRSF-iMT2c-SF' : l_common_OS + l_SR_MT2 + l_iMT2c + l_SF,
    'SRee-iMT2d-ee' : l_common_OS + l_SR_MT2 + l_iMT2d + l_2e,
    'SRmm-iMT2d-mm' : l_common_OS + l_SR_MT2 + l_iMT2d + l_2m,
    'SRSF-iMT2d-SF' : l_common_OS + l_SR_MT2 + l_iMT2d + l_SF,
    'SRee-iMT2e-ee' : l_common_OS + l_SR_MT2 + l_iMT2e + l_2e,
    'SRmm-iMT2e-mm' : l_common_OS + l_SR_MT2 + l_iMT2e + l_2m,
    'SRSF-iMT2e-SF' : l_common_OS + l_SR_MT2 + l_iMT2e + l_SF,
    'SRee-iMT2f-ee' : l_common_OS + l_SR_MT2 + l_iMT2f + l_2e,
    'SRmm-iMT2f-mm' : l_common_OS + l_SR_MT2 + l_iMT2f + l_2m,
    'SRSF-iMT2f-SF' : l_common_OS + l_SR_MT2 + l_iMT2f + l_SF, 
  }

  # From cut lists, build cut string doing N-1 appropriately
  l_cuts = d_cuts[sig_reg]

  l_cuts_nMinus1 = []
  # If a control or validation region, do not do N-1, do all N cuts
  if 'VR' in sig_reg or 'CR' in sig_reg:
    
    l_cuts_nMinus1 = l_cuts
  else:
    # if safe to do so, exclude the cut that involves var
    #l_cuts_nMinus1 = [cut for cut in l_cuts if var not in cut]
    for cut in l_cuts:
      # Make sure METOverHTLep cuts are still applied in mll and mt2leplsp_100 N-1 plots
      if ('METOverHTLep' in cut and 'mll' in cut) and ('mll' in var):
        l_cuts_nMinus1.append(cut)
        continue
      elif ('METOverHTLep' in cut and 'mt2leplsp_100' in cut) and ('mt2leplsp_100' in var):
        l_cuts_nMinus1.append(cut)
        continue
      # (N-1) if variable to be plotted is in cut, do not cut on it 
      elif var in cut: continue
      
      l_cuts_nMinus1.append(cut) 
  # join cuts with && (AND) operator
  cuts = ' && '.join(l_cuts_nMinus1)
  added_cuts = cuts + ' && ' + add_cuts
  
  if print_cuts:
    print('===============================================')
    print('Cuts applied:')
    for x in l_cuts_nMinus1:
      print x
    print('-----------------------------------------------')
    print 'Unweighted final cut-string:', added_cuts
    print('===============================================')
 
  return added_cuts
