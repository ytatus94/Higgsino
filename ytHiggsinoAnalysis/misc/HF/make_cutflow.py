#!/usr/bin/env python
'''
Welcome to pyCut/make_cutflow.py
Principally, this takes input samples processed by SusySkimHiggsino
Performs sequential cutflow given input samples and outputs LaTeX table
Things to configure:
 - List of samples to analyse
 - Cuts for Higgsino and slepton selections
'''
# So Root ignores command line inputs so we can use argparse
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
from ROOT import *
import time 
from math import sqrt
from random import gauss
import os, sys, time, argparse
from pprint import pprint

from samples import *
from cuts import *

savePDG_rounding = True # save rounded values in TeX tables 

# Paths to ntuples
TOPPATH = '/afs/cern.ch/user/y/yushen/afsWorkingArea/private/Higgsino/MC'
#BKGPATH = TOPPATH + '/SusySkimHiggsino_v1.8_SUSY16_Bkgs_tree/skimmed'
#BKGPATH = TOPPATH + '/SusySkimHiggsino_v1.9_SUSY16_Bkgs_tree'
BKGPATH = '/afs/cern.ch/work/j/jeliu/public/HiggsinoFitterTrees/v1_9'
#SIGPATH = TOPPATH + '/SusySkimHiggsino_v1.9b_SUSY16_Signal_NUHM2_tree'
SIGPATH = TOPPATH + '/SusySkimHiggsino_v1.8b_SUSY16_Signal_tree'

apply_process_selection = True

#____________________________________________________________________________
def main():
  
  t0 = time.time()
  
  #================================================
  # default values
  var     = 'DPhiJ1Met'
  sig_reg = 'preselect'
  lumi    = 36.1 # [1/fb]
  # check user has inputted variables or not
  parser = argparse.ArgumentParser(description='Analyse background/signal TTrees and make plots. Written by Jesse Liu')
  parser.add_argument('-v', '--variable',  type=str, nargs='?', help='String name for the variable (as appearing in the TTree) to make N-1 in.', default=var)
  parser.add_argument('-s', '--sigReg',    type=str, nargs='?', help='String name of selection (signal/control) region to perform N-1 selection.', default=sig_reg)
  parser.add_argument('-l', '--lumi',      type=str, nargs='?', help='Float of integrated luminosity to normalise MC to.', default=lumi)
  
  args = parser.parse_args()
  if args.variable:
    var      = args.variable
  if args.sigReg:
    sig_reg = args.sigReg
  if args.lumi:
    lumi = args.lumi
  print( '=========================================' )
  print( 'Plotting variable: {0}'.format(var) )
  print( 'Selection region: {0}'.format(sig_reg) )
  print( 'Normalising luminosity: {0}'.format(lumi) )
  print( '=========================================\n' )
  
  #================================================
  # make (relative) save directory if needed 
  savedir = 'cutflows/v1_9/rounded/ee'
  savedir = 'cutflows/v1_9/rounded/mm'
  savedir = 'cutflows/v1_9/rounded/SF'
  mkdir(savedir)
 

  save_var = var
  save_name = savedir + '/cutflow_bkgs.tex'
  
  #==========================================================
  # List samples to analyse 
  #==========================================================
#  d_samp_set = {
#    'Zjets'    : ['Zjets', 'Zttjets'],
#    'Zgamma'   : ['Zgamma', 'Zttgamma'],
#    #'Zjets'    : ['Zjets', 'Zvvjets', 'Zttjets'],
#    #'Zgamma'   : ['Zgamma', 'Zvvgamma', 'Zttgamma'],
#    #'DY'    : ['alt_DY_PowPy'],
#    #'W'     : ['Wjets', 'Wgamma'], 
#    'data'     : ['data'], 
#    'Fakes'     : ['fakes'], 
#    #'VV2LExt'    : ['diboson2LExtPrivate'],
#    'VV2L'    : ['diboson2L', 'diboson3L', 'diboson4L'],
#    'higgsVVV'       : [ 'higgs', 'triboson'],
#    'top'       : ['singletop', 'ttbar', 'topOther'],
#    'ttbar'     : ['ttbar', 'ttV', 'topOther'],
#    'Higgsino'   : ['MGPy8EG_A14N23LO_SM_Higgsino_103_100_2LMET50_MadSpin',
#                   'MGPy8EG_A14N23LO_SM_Higgsino_110_100_2LMET50_MadSpin',
#                   'MGPy8EG_A14N23LO_SM_Higgsino_120_100_2LMET50_MadSpin',
#      #             'MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin',
#                   ],
#    'Slepton'   : [ 'MGPy8EG_A14N23LO_SlepSlep_direct_102p0_100p0_MET50',
#                   'MGPy8EG_A14N23LO_SlepSlep_direct_110p0_100p0_MET50',
#                   'MGPy8EG_A14N23LO_SlepSlep_direct_120p0_100p0_MET50',
#      #             'MGPy8EG_A14N23LO_SlepSlep_direct_140p0_100p0_MET50',
#                   ]
#      }
#  d_samp_set = {
#    'Higgsino'   : [
#                    'MGPy8EG_A14N23LO_SM_Higgsino_110_100_2LMET50_MadSpin',
#                    'MGPy8EG_A14N23LO_SlepSlep_direct_110p0_100p0_MET50',
#                      ]
#              }
#
#  
#  d_samp_set = {
#    'Higgsino'   :  [ 'MGPy8EG_A14N23LO_SM_Higgsino_110_100_2LMET50_MadSpin']
#              }
  
  d_samp_set = {
#    'NUHM2' : [	
#                'MGPy8EG_A14N23LO_NUHM2_m12_300_weak_2LMET50_MadSpin',
#                'MGPy8EG_A14N23LO_NUHM2_m12_350_weak_2LMET50_MadSpin',
#                'MGPy8EG_A14N23LO_NUHM2_m12_400_weak_2LMET50_MadSpin',
#                'MGPy8EG_A14N23LO_NUHM2_m12_500_weak_2LMET50_MadSpin',
#                'MGPy8EG_A14N23LO_NUHM2_m12_600_weak_2LMET50_MadSpin',
#                'MGPy8EG_A14N23LO_NUHM2_m12_700_weak_2LMET50_MadSpin',
#                'MGPy8EG_A14N23LO_NUHM2_m12_800_weak_2LMET50_MadSpin'
#              ],
#    'Higgsino' : ['MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin',
#                  'MGPy8EG_A14N23LO_SM_Higgsino_160_150_2LMET50_MadSpin',
#                  'MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin',
#                  'MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin'
#                 ],
    'fakes'   : ['fakes2Lb_DijetFFs'],
    'top'     : ['top'],
    'Zttjets' : ['Zttjets'],
    'diboson' : ['diboson'],
    'other'   : ['other']
               }
  # Higgsino processes
  l_proc = [
              'FS == 125', # N2C1p
              #'FS == 127', # N2C1m
              'FS == 112', # N2N1
              'FS == 157', # C1C1
              ]


  #==========================================================
  # Cuts to impose sequentially
  #==========================================================
  l_common_cuts = [
    'trigMatch_metTrig',
#    'FS != 206 && FS != 207',
#    'FS == 157', # N2C1p
    'nLep_base==2',
    'nLep_signal==2',
    'lep1Flavor == lep2Flavor',
    #'lep1Flavor == 1 && lep2Flavor == 1',
    #'lep1Flavor == 2 && lep2Flavor == 2',
    'lep1Charge != lep2Charge',
    #'(lep1TruthMatched && lep2TruthMatched)',
    '((lep1TruthMatched && lep2TruthMatched) || (DatasetNumber >= 407311 && DatasetNumber <= 407315))',
    '(lep1Author != 16 && lep2Author != 16)',
    'met_Et>200',
    'nBJet20_MV2c10 == 0',
    'jetPt[0]>100',
    'DPhiJ1Met > 2.0',
    'minDPhiAllJetsMet > 0.4',
    '(MTauTau < 0 || MTauTau > 160)',
    'lep1Pt > 5',
    'mll > 1',
    '(mll < 3 || mll > 3.2)',
    'mll < 60',
#    'Rll > 0.05',
  ]

  l_higgsino = [
    'METOverHTLep > max(5.0, 15 - 2*mll)',
    'Rll < 2',
    'mt_lep1 < 70',
    'mll < 40',
    'mll < 30',
    'mll < 20',
    'mll < 10',
    'mll < 5',
    'mll < 3',
  ]
 
  l_slepton = [
    'METOverHTLep > max(3.0, 15 - 2*(mt2leplsp_100 - 100))',
    'mt2leplsp_100 < 130',
    'mt2leplsp_100 < 120',
    'mt2leplsp_100 < 110',
    'mt2leplsp_100 < 105',
    'mt2leplsp_100 < 102',
  ] 

  d_samp_cutflow = {}
  
  for samp_set in d_samp_set: 
  #for samp_set in ['higgsVVV']: 
    l_samp = d_samp_set[samp_set] 
    # sequentially add cuts for cutflow
    for count, samp in enumerate( l_samp ):
      d_samp_cutflow[samp] = { 'yield'  : [], 
                                  'unc' : [], 
                                  'raw' : [],
                        'rounded_yield' : [],
                     'rounded_yieldUnc' : [],
                                 }
      
      # apply a process selection if we want
      #if apply_process_selection:
      #  l_common_cuts = [ l_proc[count] ] + l_common_cuts_0
      #else:
      #  l_common_cuts = l_common_cuts_0
             
      l_cutflow = l_common_cuts + l_higgsino + l_slepton
      l_cutflow_common = []
      l_cutflow_higgsino = []
      l_cutflow_slepton = []
      # Compute the cutflow common to higgsino and slepton SRs
      for cut in l_common_cuts:
        # Add cuts cumulatively sequentially
        l_cutflow_common.append(cut)
        add_cut = ' && '.join(l_cutflow_common)
        nYield, yieldUnc, nRaw, rounded_nYield, rounded_yieldUnc = calc_selections(samp, var, add_cut, lumi)
        d_samp_cutflow[samp]['yield'].append(nYield)
        d_samp_cutflow[samp]['unc'].append(yieldUnc)
        d_samp_cutflow[samp]['raw'].append(nRaw)
        d_samp_cutflow[samp]['rounded_yield'].append(rounded_nYield)
        d_samp_cutflow[samp]['rounded_yieldUnc'].append(rounded_yieldUnc)
      
      # Now the cutflow diverges for higgsinos and sleptons
      # Compute the sequential cutflow for higgsino SRs
      for cut in l_higgsino:
        # Add cuts cumulatively sequentially
        l_cutflow_higgsino.append(cut)
        add_cut = ' && '.join(l_cutflow_common + l_cutflow_higgsino)
        nYield, yieldUnc, nRaw, rounded_nYield, rounded_yieldUnc = calc_selections(samp, var, add_cut, lumi)
        d_samp_cutflow[samp]['yield'].append(nYield)
        d_samp_cutflow[samp]['unc'].append(yieldUnc)
        d_samp_cutflow[samp]['raw'].append(nRaw)
        d_samp_cutflow[samp]['rounded_yield'].append(rounded_nYield)
        d_samp_cutflow[samp]['rounded_yieldUnc'].append(rounded_yieldUnc)
      
      # Compute the sequential cutflow for slepton SRs
      for cut in l_slepton:
        # Add cuts cumulatively sequentially
        l_cutflow_slepton.append(cut)
        add_cut = ' && '.join(l_cutflow_common + l_cutflow_slepton)
        nYield, yieldUnc, nRaw, rounded_nYield, rounded_yieldUnc = calc_selections(samp, var, add_cut, lumi)
        d_samp_cutflow[samp]['yield'].append(nYield)
        d_samp_cutflow[samp]['unc'].append(yieldUnc)
        d_samp_cutflow[samp]['raw'].append(nRaw)
        d_samp_cutflow[samp]['rounded_yield'].append(rounded_nYield)
        d_samp_cutflow[samp]['rounded_yieldUnc'].append(rounded_yieldUnc)
    
    #pprint(d_samp_cutflow)
    
    # now print out cutflow
    for samp in l_samp:
      
      print('=================================================')
      print('Printing cutflow for sample {0}'.format(samp))
      print('Cut,36.1/fb_weighted_yield,uncertainty,raw')
      csv_name = '{0}/{1}.csv'.format(savedir, samp)
      with open(csv_name, 'w') as f_csv:
        f_csv.write('Cut,36.1/fb_weighted_yield,uncertainty,raw,PDG_rounded_yield,PDG_rounded_uncertainty\n')
        count = 0
        for my_cut, my_yield, my_unc, my_raw, my_rounded_nYield, my_rounded_nYieldUnc in zip(l_cutflow, 
                                                          d_samp_cutflow[samp]['yield'], 
                                                          d_samp_cutflow[samp]['unc'], 
                                                          d_samp_cutflow[samp]['raw'],
                                                          d_samp_cutflow[samp]['rounded_yield'],
                                                          d_samp_cutflow[samp]['rounded_yieldUnc'],
                                                          ):
          my_cut = my_cut.replace(',', ';')
          print('{0},{1:.3f},{2:.3f},{3},{4},{5}'.format(my_cut, my_yield, my_unc, my_raw, my_rounded_nYield, my_rounded_nYieldUnc))
          f_csv.write('{0},{1:.3f},{2:.3f},{3},{4},{5}\n'.format(my_cut, my_yield, my_unc, int(my_raw), my_rounded_nYield, my_rounded_nYieldUnc))
          count += 1
          if len(l_cutflow_common) <= count < len(l_cutflow_common) + 1:
            print('==============================================')
          if len(l_cutflow_common + l_cutflow_higgsino) <= count < len(l_cutflow_common + l_cutflow_higgsino) + 1:
            print('----------------------------------------------')
      print('=================================================')

      make_latex(samp_set, l_samp, l_cutflow, d_samp_cutflow, savedir, l_cutflow_common, l_cutflow_higgsino)

  tfinish = time.time()
  telapse = tfinish - t0
  print( '{0:.3f}s'.format(telapse))

#____________________________________________________________________________
def calc_selections(samp, var, add_cuts, lumi):
  '''
  Extract trees given a relevant variable
  ''' 
  #==========================================================
  # Prepare information and objects for analysis and plots
  #==========================================================
  # obtain cut to apply (string)
  d_files = {}
  d_hists = {}
  sig_reg = 'preselect'
  #normCutsAfter = configure_cuts(var, add_cuts, sig_reg) 
  
  # get dictionary defining sample properties
  d_samp = configure_samples()
  
  #==========================================================
  # loop through samples, fill histograms and legend
  #==========================================================
  Nsignal_count = 0
  #if 'SR' in sig_reg:
  #  if 'data' in samp:
  # obtain sample attributes 
  sample_type = d_samp[samp]['type']
  path        = d_samp[samp]['path']

  # choose full path of sample by its type  
  full_path = ''
  if sample_type == 'sig':
    full_path = SIGPATH + '/' + path
    #full_path = TOPPATH + '/nopreselection/AllSignals_SusySkimHiggsino_v1.9b_SUSY16_tree_NoSys_nopreselection.root'
  if sample_type == 'bkg':
    full_path = BKGPATH + '/' + path 
  if sample_type == 'data':
    full_path = BKGPATH + '/' + path
  print(full_path)
 
   
  #--------------------------------------------------------------------- 
  # Dealing with fakes
  #--------------------------------------------------------------------- 
  # For now handling minimally: assume subleading is fake
  # manipulate the SR name to the fake CR 
  
  #cutsAfter = normCutsAfter 
  cutsAfter = add_cuts 

  #print('cuts to apply: {0}'.format(cutsAfter))     
  # assign TFile to a dictionary entry
  d_files[samp] = TFile(full_path)

  # obtain histogram from file and store to dictionary entry
  hNbins = 1
  hXmin  = 0
  hXmax  = 5
  d_hists[samp] = tree_get_th1f( d_files[samp], samp, var, cutsAfter, hNbins, hXmin, hXmax, lumi )

  # extract key outputs of histogram 
  nYield, nYieldErr, nRaw, rounded_nYield, rounded_nYieldErr = d_hists[samp]
  #print('In cut: {0},{1},{2}'.format(nYield, nYieldErr, nRaw)) 
   
  return nYield, nYieldErr, nRaw, rounded_nYield, rounded_nYieldErr


   
#_______________________________________________________
def tree_get_th1f(f, hname, var, cutsAfter='', Nbins=100, xmin=0, xmax=100, lumifb=35):
  '''
  from a TTree, project a leaf 'var' and return a TH1F
  '''
  h_AfterCut   = TH1D(hname, "", Nbins, xmin, xmax)
  
  lumi     = lumifb * 10 ** 3 # convert to [pb^{-1}]
  weights = "(genWeight * eventWeight * leptonWeight * jvtWeight * bTagWeight * pileupWeight * FFWeight)"
  cut_after = '({0}) * {1} * ({2})'.format(cutsAfter, weights, lumi) 
  print('Weighted final cut string: {0}'.format(cut_after))
  
  # ========================================================= 
  if hname == 'fakes2Lb_DijetFFs':
    hname = 'fakes'
  print hname
  if 'data' in hname:
    t = f.Get(hname + '_NoSys') 
    t.Project( hname,           var, cutsAfter )
  else:
    t = f.Get(hname + '_NoSys') 
    #t = f.Get(hname + '_LOOSE_NOMINAL') 
    t.Project( hname,           var, cut_after )
  # =========================================================
  # Perform integrals to find total yield
  nYieldErr = ROOT.Double(0)
  nYield    = h_AfterCut.IntegralAndError(0, Nbins+1, nYieldErr)
 
  rounded_nYield, rounded_nYieldErr = pdgRound(nYield, nYieldErr)

  print( 'Sample {0} has integral {1:.3f} +/- {2:.3f}, PDG rounded to {3} +/- {4}'.format( hname, nYield, nYieldErr, rounded_nYield, rounded_nYieldErr ) )
  # =========================================================
  
  nRaw = h_AfterCut.GetEntries()
  
  return nYield, nYieldErr, nRaw, rounded_nYield, rounded_nYieldErr
 
#____________________________________________________________________________
def make_latex(samp_set, l_samp, l_cuts, d_samp_cutflow, savedir, l_cutflow_common, l_cutflow_higgsino):
  '''
  Produce the LaTeX table
  '''

  # Mapping ntuple selections to LaTeX
  d_cuts_latex = {
    '(HLT_xe70 || HLT_xe90_mht_L1XE50 || HLT_xe100_mht_L1XE50 || HLT_xe110_mht_L1XE50)' : r'\met triggers, $\met>150$ GeV, $N_\text{baseline}^\ell \geq 2$',
    'trigMatch_metTrig'              : r'\met triggers, $\met>150$ GeV, $N_\text{baseline}^\ell \geq 2$',
#    'FS != 206 && FS != 207'         : r'Stau veto',
#    'FS == 125'                      : r'$\chitz\chiop$',
#    'FS == 127'                      : r'$\chitz\chiom$',
#    'FS == 112'                      : r'$\chitz\chioz$',
#    'FS == 157'                      : r'$\chiop\chiom$',
#    'trigMatch_metTrig'              : r'\met triggers',
    'nLep_base==2'                   : r'$N_\text{baseline}^\ell = 2$',
    'nLep_signal==2'                 : r'$N_\text{signal}^\ell = 2$',
    'lep1Flavor == lep2Flavor'       : r'Same flavour',
    'lep1Flavor == 1 && lep2Flavor == 1' : r'Two electrons',
    'lep1Flavor == 2 && lep2Flavor == 2' : r'Two muons',
    'lep1Charge != lep2Charge'       : r'Opposite charge',
    'met_Et>200'                     : r'$\met > 200$ GeV',
    'nJet30 >= 1 && nJet30 <= 4'     : r'$1 \leq N_\text{jets}^{30} \leq 4$',
    'jetPt[0]>100'                   : r'$\pt(j_1) > 100$ GeV',
    'DPhiJ1Met > 2.0'                : r'$\Delta\phi\left(j_1, \mathbf{p}_\text{T}^\text{miss}\right) > 2.0$',
    'minDPhiAllJetsMet > 0.4'        : r'min($\Delta\phi\left(\text{any jet}, \mathbf{p}_\text{T}^\text{miss}\right)) > 0.4$',
    'nBJet20_MV2c10 == 0'            : r'$N_\text{b-jets} = 0$',
    #'nBJet20_MV2c10_FixedCutBEff_85 == 0'  : r'$N_\text{b-jets}^{20} = 0$',
    '(MTauTau < 0 || MTauTau > 160)' : r'Veto $m_{\tau\tau} \in [0, 160]$ GeV',
    'lep1Pt > 5'                     : r'$p_\text{T}^{\ell_1} > 5$ GeV',
    '(lep1Author != 16 && lep2Author != 16)' : r'Lepton author 16 veto',
    '(lep1TruthMatched && lep2TruthMatched)' : r'Lepton truth matching',
    '((lep1TruthMatched && lep2TruthMatched) || (DatasetNumber >= 407311 && DatasetNumber <= 407315))' : r'Lepton truth matching',
    'METOverHTLep > max(5.0, 15 - 2*mll)'   : r'$\met / \HT^\text{lep} > \text{max}(5, 15-2\cdot m_{\ell\ell}/\text{GeV})$',
    'METOverHTLep > max(3.0, 15 - 2*(mt2leplsp_100 - 100))'   : r'$\met / \HT^\text{lep} > \text{max}\left(3, 15-2\cdot \left[m_\text{T2}^{100}/\text{GeV} - 100\right]\right)$',
    'Rll < 2'                        : r'$\Delta R_{\ell\ell} < 2.0$ GeV',
    'Rll > 0.05'                     : r'$\Delta R_{\ell\ell} > 0.05$ GeV',
    'mt_lep1 < 70'                   : r'$m_\text{T}^{\ell_1} < 70$ GeV',
    'mll > 1'                        : r'$m_{\ell\ell} > 1$ GeV',
    'mll < 60'                       : r'$m_{\ell\ell} < 60$ GeV',
    'mll < 40'                       : r'$m_{\ell\ell} < 40$ GeV',
    'mll < 30'                       : r'$m_{\ell\ell} < 30$ GeV',
    'mll < 20'                       : r'$m_{\ell\ell} < 20$ GeV',
    'mll < 10'                       : r'$m_{\ell\ell} < 10$ GeV',
    'mll < 5'                        : r'$m_{\ell\ell} < 5$ GeV',
    'mll < 3'                        : r'$m_{\ell\ell} < 3$ GeV',
    '(mll < 3 || mll > 3.2)'         : r'Veto $m_{\ell\ell} \in [3, 3.2]$ GeV',
    'mt2leplsp_100 < 102'            : r'$m_\text{T2}^{100} < 102$ GeV',
    'mt2leplsp_100 < 105'            : r'$m_\text{T2}^{100} < 105$ GeV',
    'mt2leplsp_100 < 110'            : r'$m_\text{T2}^{100} < 110$ GeV',
    'mt2leplsp_100 < 120'            : r'$m_\text{T2}^{100} < 120$ GeV',
    'mt2leplsp_100 < 130'            : r'$m_\text{T2}^{100} < 130$ GeV',
    'mt2leplsp_100 >= 100'           : r'$m_\text{T2}^{100} \geq 100$ GeV',
  }
  
  
  # Mapping short sample name to LaTeX
  d_samp_latex = {
#    'alt_ttbar_nonallhad' : r'PowPy $t\bar{t} (\geq 1\ell)$', 
#    'alt_ttbar_MGPy'      : r'MGPy $t\bar{t}$', 
#    'alt_ttbar_Sherpa'    : r'Sherpa $t\bar{t}$', 
#    'alt_ttbar_aMCAtNlo'  : r'aMCAtNlo $t\bar{t}$', 
#    
#    'fakes'            : r'Fakes (2Li ntuples)', 
#    'diboson4L'        : r'$VV (4\ell$)',
#    'diboson4LExt'     : r'$VV (4\ell$) ext.',
#    'diboson3L'        : r'$VV (3\ell$)',
#    'diboson3LExt'     : r'$VV (3\ell$) ext.',
#    'diboson2L'        : r'$VV (2\ell$)',
#    'diboson2LExt' : r'$VV (2\ell$) official ext.', 
#    'diboson2LExtPrivate' : r'$VV (2\ell$) truth ext.', 
#    'diboson1L'        : r'$VV (1\ell$)',
#    'diboson0L'        : r'$VV (0\ell$)',
#
#    'alt_diboson4L_PowPy' : r'$VV (4\ell$)',
#    'alt_diboson3L_PowPy' : r'$VV (3\ell$)',
#    'alt_diboson2L_PowPy' : r'$VV (2\ell$)', 
#    'alt_diboson1L_PowPy' : r'$VV (1\ell$)', 
#  
#    'WWlvqq'           : r'PowPy $WW\to \ell\nu qq$',
#    'Wlvlv'            : r'PowPy $WW \to \ell\nu\ell\nu$',
#    'WZqqll'           : r'PowPy $WZ \to qq \ell\ell$',
#    'ZZvvll'           : r'PowPy $ZZ \to\nu\nu \ell\ell$',
#    'WZlvll'           : r'PowPy $WZ\to \ell\nu\ell\ell$',
#    
#    'alt_DY_PowPy'          : r'PowPy DY $(ee, \mu\mu, \tau\tau)$',
#
#    'Zjets'            : r'$Z(\to ee, \mu\mu)$ + jets',
#    'ZjetsExt'         : r'$Z(\to ee, \mu\mu)$ + jets Ext',
#    'Zgamma'           : r'$Z(\to ee, \mu\mu) + \gamma$',
#    'Zttjets'          : r'$Z(\to\tau\tau)$+jets',
#    'ZttjetsExt'       : r'$Z(\to\tau\tau)$+jets Ext',
#    'Zttgamma'         : r'$Z(\to\tau\tau)$+gamma',
#    'Zvvjets'          : r'$Z(\to\nu\nu)$+jets',
#    'Zvvgamma'         : r'$Z(\to\nu\nu)$+gamma',
#    
#    'alt_Zgamma_Sherpa222'   : r'$Z(\to ee, \mu\mu) + \gamma$ Shrp222',
#    'alt_Zttgamma_Sherpa222' : r'$Z(\to \tau\tau) + \gamma$ Shrp222',
#    'alt_Zvvgamma_Sherpa222' : r'$Z(\to \nu\nu) + \gamma$ Shrp222',
#
#    'Wjets'            : r'$W$+jets',
#    'Wgamma'           : r'$W+ \gamma$',
#    
#    'higgs'            : r'Higgs',
#    'triboson'         : r'$VVV$',
#
#    'ttV'              : r'$t\bar{t} + V$',
#    'singletop'        : r'$t, tW$',
#    'tZ'               : r'$tZ$', 
#    'ttbar'            : r'PowPy $t\bar{t} (2\ell)$', 
#    'topOther'         : r'$3t, 4t, t\bar{t}WW$', 
#    'data'             : r'Data',
#    
#    
#    'MGPy8EG_A14N23LO_SlepSlep_direct_102p0_100p0_MET50'   : r'$\tilde{\ell} (102, 100)$',
#    'MGPy8EG_A14N23LO_SlepSlep_direct_110p0_100p0_MET50'   : r'$\tilde{\ell} (110, 100)$',
#    'MGPy8EG_A14N23LO_SlepSlep_direct_120p0_100p0_MET50'   : r'$\tilde{\ell} (120, 100)$',
#    'MGPy8EG_A14N23LO_SlepSlep_direct_140p0_100p0_MET50'   : r'$\tilde{\ell} (140, 100)$',
#    'MGPy8EG_A14N23LO_SM_Higgsino_103_100_2LMET50_MadSpin' : r'$\tilde{H} (103, 100)$',
#    'MGPy8EG_A14N23LO_SM_Higgsino_110_100_2LMET50_MadSpin' : r'$\tilde{H} (110, 100)$',
#    'MGPy8EG_A14N23LO_SM_Higgsino_120_100_2LMET50_MadSpin' : r'$\tilde{H} (120, 100)$',
#    'MGPy8EG_A14N23LO_SM_Higgsino_140_100_2LMET50_MadSpin' : r'$\tilde{H} (140, 100)$',

    'MGPy8EG_A14N23LO_SM_Higgsino_160_100_2LMET50_MadSpin' : r'$\tilde{H} (160, 100)$',
    'MGPy8EG_A14N23LO_SM_Higgsino_160_150_2LMET50_MadSpin' : r'$\tilde{H} (160, 150)$',
    'MGPy8EG_A14N23LO_SM_Higgsino_170_150_2LMET50_MadSpin' : r'$\tilde{H} (170, 150)$',
    'MGPy8EG_A14N23LO_SM_Higgsino_190_150_2LMET50_MadSpin' : r'$\tilde{H} (190, 150)$',

    'MGPy8EG_A14N23LO_NUHM2_m12_300_weak_2LMET50_MadSpin' : r'NUHM2 m12=300',
    'MGPy8EG_A14N23LO_NUHM2_m12_350_weak_2LMET50_MadSpin' : r'NUHM2 m12=350',
    'MGPy8EG_A14N23LO_NUHM2_m12_400_weak_2LMET50_MadSpin' : r'NUHM2 m12=400',
    'MGPy8EG_A14N23LO_NUHM2_m12_500_weak_2LMET50_MadSpin' : r'NUHM2 m12=500',
    'MGPy8EG_A14N23LO_NUHM2_m12_600_weak_2LMET50_MadSpin' : r'NUHM2 m12=600',
    'MGPy8EG_A14N23LO_NUHM2_m12_700_weak_2LMET50_MadSpin' : r'NUHM2 m12=700',
    'MGPy8EG_A14N23LO_NUHM2_m12_800_weak_2LMET50_MadSpin' : r'NUHM2 m12=800',
 
    'fakes'   : 'fakes',
    'top'     : 'top',
    'Zttjets' : 'Zttjets',
    'diboson' : 'diboson',
    'other'   : 'other',
  }

  tab_head = r'''
\begin{table}
\begin{center}
\tiny
\renewcommand{\arraystretch}{1.5}
  '''

  tab_top_line = r'\begin{tabular*}{\textwidth}{@{\extracolsep{\fill}}l'
  tab_samp_header   = r'''
  \toprule
  Selection common to all SRs '''
  tab_count_header = r''
  # Add headers of samples
  for samp in l_samp:
    if samp == 'fakes2Lb_DijetFFs':
      samp = 'fakes'
    tab_top_line += 'rr'
    tab_samp_header += r' & \multicolumn{2}{c}{' + d_samp_latex[samp] + '} \n'
    tab_count_header += r' & Weighted & Raw '
  tab_top_line += r'}'
  tab_samp_header += r'\\' 
  tab_count_header += r'''\\ 
  \midrule
  '''
  tab_line = ''
  # Go through each cut as new horizontal entry
  for count, cut in enumerate(l_cuts):
    tab_line += d_cuts_latex[cut]
    for samp in l_samp:
      
      my_yield         = d_samp_cutflow[samp]['yield'][count]
      my_unc           = d_samp_cutflow[samp]['unc'][count]
      my_raw           = d_samp_cutflow[samp]['raw'][count]
      my_rounded_yield = d_samp_cutflow[samp]['rounded_yield'][count]
      my_rounded_unc   = d_samp_cutflow[samp]['rounded_yieldUnc'][count]
      if savePDG_rounding:
        #tab_line += r' & ${0} \pm {1}$ ({2})     '.format(my_rounded_yield, my_rounded_unc, int(my_raw) )
        tab_line += r' & ${0}$ & ${1}$   '.format(my_rounded_yield, int(my_raw) )
      else:
        tab_line += r' & ${0:.1f}$ & ${1:.1f}$ '.format(my_yield, int(my_raw) )

    tab_line += r'''\\ 
    '''
    count += 1
    # Add rules where the cutflow diverges
    if len(l_cutflow_common) <= count < len(l_cutflow_common) + 1:
      tab_line += r'''
\midrule
SR$\ell\ell$-$m_{\ell\ell}$ selection'''  
      for samp in l_samp: 
        tab_line += r' & '
      tab_line += r'''\\ 
\midrule
'''       
    if len(l_cutflow_common + l_cutflow_higgsino) <= count < len(l_cutflow_common + l_cutflow_higgsino) + 1:
      tab_line += r'''\midrule
SR$\ell\ell$-$m_\text{T2}^{100}$ selection'''       
      for samp in l_samp: 
        tab_line += r' & '
      tab_line += r'''\\ 
\midrule
'''       

  tab_foot = r'''
  \bottomrule
  \end{tabular*}
\end{center}
\caption{ Yields after initial preselection and sequentially with each addition requirement 
for selections common to all signal regions (SRs), 
followed by those optimised for Higgsinos and sleptons. 
Weighted events are normalised to 36.1~fb$^{-1}$ and the raw Monte Carlo events are also displayed.
}
\label{tab:cutflow_%s}
\end{table} 
  ''' % samp_set
  
  final_tab = tab_head + tab_top_line + tab_samp_header + tab_count_header +  tab_line + tab_foot
  save_name = '{0}/cutflow_{1}.tex'.format(savedir, samp_set)
  with open(save_name, 'w') as f_out:
    print('Saving {0}'.format(save_name))
    f_out.write(final_tab)
  #print(final_tab)


#_________________________________________________________________________
def pdgRound(value, error) :
# This class implements the pdg rounding rules indicated in
# section 5.3 of doi:10.1088/0954-3899/33/1/001
#
# Note: because it uses round (and in general floats), it is affected
# by the limitations described in
# http://docs.python.org/library/functions.html#round
#  and
# http://dx.doi.org/10.1145/103162.103163
#
# davide.gerbaudo@gmail.com
# September 2012

  "Given a value and an error, round and format them according to the PDG rules for significant digits"
  def threeDigits(value) :
    "extract the three most significant digits and return them as an int"
    return int(("%.2e"%float(error)).split('e')[0].replace('.','').replace('+','').replace('-',''))
  def nSignificantDigits(threeDigits) :
    assert threeDigits<1000,"three digits (%d) cannot be larger than 10^3"%threeDigits
    if threeDigits<101 : return 2 # not sure
    elif threeDigits<356 : return 2
    elif threeDigits<950 : return 1
    else : return 2
  def frexp10(value) :
    "convert to mantissa+exp representation (same as frex, but in base 10)"
    valueStr = ("%e"%float(value)).split('e')
    return float(valueStr[0]), int(valueStr[1])
  def nDigitsValue(expVal, expErr, nDigitsErr) :
    "compute the number of digits we want for the value, assuming we keep nDigitsErr for the error"
    return expVal-expErr+nDigitsErr
  def formatValue(value, exponent, nDigits, extraRound=0) :
    "Format the value; extraRound is meant for the special case of threeDigits>950"
    roundAt = nDigits-1-exponent - extraRound
    nDec = roundAt if exponent<nDigits else 0
    nDec = max([nDec, 0])
    return ('%.'+str(nDec)+'f')%round(value,roundAt)
  tD = threeDigits(error)
  nD = nSignificantDigits(tD)
  expVal, expErr = frexp10(value)[1], frexp10(error)[1]
  extraRound = 1 if tD>=950 else 0
  return (formatValue(value, expVal, nDigitsValue(expVal, expErr, nD), extraRound),
          formatValue(error,expErr, nD, extraRound))


#_________________________________________________________________________
def mkdir(dirPath):
  '''
  make directory for given input path
  '''
  try:
    os.makedirs(dirPath)
    print 'Successfully made new directory ' + dirPath
  except OSError:
    pass
 
if __name__ == "__main__":
  #main(sys.argv)
  main()
