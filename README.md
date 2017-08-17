# Higgsino
The NUHM2 Higgsino study

---


### v24. New EwkNUHM22016.cxx
* `EwkNUHM22016.cxx`: Checkout the newest version from simple analysis.
* `fit_common_ntuple.py`:
  * remove ";" in some lines
  * Use Lorenzo's modified function
* `file_path.C`: Use new directory `20170817/`
* `mll_ratio.C`: Use new directory `20170817/`
* `overlap_histograms.C`: Use new directory `20170817/`
* `test_fit.C`: Use new directory `20170817/`
* `test_Higgsino_160_100.C`: Use new directory `20170817/`
* `view_combine_hist.C`: Use new directory `20170817/`
* `reweight_truth3.C`:
  * Use new directory `20170817/`
  * Add `preselection` and `2LChannel`
* `show_normalization_factor.C`: Use Lorenzo's modified function


### v23. Use 20170815 results and add preselection and 2L requirements
* `EwkNUHM22016.cxx`: New code modified from `EwkHiggsino2016`
* `RunSimpleAnalysis.sh`: Change `EwkHiggsino2016` to `EwkNUHM22016`
* `file_path.C`: Use new directory `20170815/`
* `get_combined_hist.C`: Change `EwkHiggsino2016` to `EwkNUHM22016`
* `mll_ratio.C`: Change `EwkHiggsino2016` to `EwkNUHM22016`
* `overlap_histograms.C`: Use new directory `20170815/`
* `view_combine_hist.C`: Use new directory `20170815/`
* `test_fit.C`:
  * Change function declaration.
  * Use new directory `20170815/`
  * Include `ytUtility.C` so I can use `get_dm_NUHM2()`
  * Add `xrange_max` for `SetRangeUser()`
  * Fix the line color
  * Change the legend coordinate
* `test_Higgsino_160_100.C`: Use new directory `20170815/`
* `reweight_truth3.C`:
  * Use new directory `20170815/`
  * Remove `get_func_ratio_parameters()`
  * Change `EwkHiggsino2016` to `EwkNUHM22016`
  * Add `preselection` and `2LChannel`
* `reweight_kinematic_variables.C`:
  * Use new directory `20170815/`
  * Add `y_scale_factor` and change `y_max`
  * Change the legend coordinate and font size
  * Fix the output file name.
  * Change `EwkHiggsino2016` to `EwkNUHM22016`
  * Add `preselection` and `2LChannel`
  * Add `pTLep1` and `nJet30` plots
  * Change some cosmetic of plots 


### v22. reweight kinematic variables
* `AtlasStyle.py`: Comment ROOT color
* `BR_calculation.py`: Add `sum_BR()` into `main()` but comment it
* `Nevents.py`: Add comments
* `get_yields.py`: Add horizontal lines to separate the function definition.
* `reweight_truth3.C`:
  * Bug fix in `plot_Lorenzo()`
  * Use bin-by-bin weight in `plot_Mike()`
  * Remove unnecessary TH1 in `tree_reader()`
* `get_combined_hist.C`: Add new function overload `get_histogram()`
* `reweight_truth3.C`: Change the order of n2 and n1 in the input arguments.
* `view_combine_hist.C`: Add new script to check the distributions
* `reweight_kinematic_variables.C`: Add new script to check the distributions of reweighted kinematic variables.


### v21. add tree_reader()
* `FuncMllDistr_modified.C`: add comment
* `file_path.C`: add space
* `get_combined_hist.C`:
  * remove unnecessary part
  * add if condition when there are only histograms in the input.
* `mll_ratio.C`: remove unnecessary part
* `overlap_histograms.C`: use `combine_histogram()`
* `reweight_common_ntuple.C`: remove unnecessary part
* `reweight_truth3.C`:
  * remove unnecessary part
  * Add `tree_reader()` and use it.
* `test_Higgsino_160_100.C`: remove unnecessary part


### v20. Correct Lorenzo's approach
* `get_combined_hist.C`:
  * add new function `combine_histogram()`
  * modify `get_combined_hist()`
* `fit_common_ntuple.C`: Change to modified function
* `reweight_common_ntuple.C`:
  * Use modified function
  * Use `ytUtility.C`
  * Use function to reweight
* `reweight_truth3.C`:
  * Correct Lorenzo's approach
  * Add Mike's approach
* `FuncMllDistr_modified.C`: add new script
* `file_path.C`:: add new script
* `mll_ratio.C`:: add new script
* `test_Higgsino_160_100.C`: add new script
* `ytUtility.C`: add new script


### v19. Rewrite the reweighting script
* `show_normalization_factor.C`: add new script
* `test_120_100.C`: add new script
* `test_Higgsino_170_150_m12_600.C`: add new script
* `FuncMllDistr.C`: Add comment
* `RunSimpleAnalysis.sh`: Add Higgsino 190_150 samples
* `convert_EVNT_to_TRUTH.sh`: Add Higgsino 190_150 samples
* `overlap_histograms.C`: Change input path
* `fit_common_ntuple.C`:
  * Add Higgsino 190_150
  * New fit plot method
* `reweight_truth3.C`: Complete rewrite this script.
* `test_fit.py`: rewrite this script


### v18. Add scripts for reweighting
* `test_fit.C`: Add new script. This works for FuncMllDistr.
* `get_combined_hist.C`: Add new script.
* `fit_common_ntuple.C`: Add new script. This works for FuncMllDistr.
* `FuncMllDistr.C`: Add new script.
* `GetWeightFunction.C`: Add Lorenzo's script as an example.
* `test_fit.py`:
  * Add new functions `get_histogram()`, `funcMllDistr()`, `reweight_method_1()`, and `reweight_method_2()`
* `overlap_histograms.C`: Add new script.
* `reweight_common_ntuple.C`: Add new script.
* `reweight_truth3.C`: Add new script.


### v17. Add new Higgsino samples and scripts for these new samples
* `RunSimpleAnalysis.sh`: Add new Higgsino samples
* `check_slha.py`: Add new script
* `get_mass_difference.py`: Add new script
* `Xsec.pdf`: Cross section for N2N1, C1C1, N2C1p, N2C1m
* `convert_EVNT_to_TRUTH.sh`: modified for new Higgsino samples
* `test_fit.py`: Add new script


### v16. Add new branches
* `NUHM2.h`: New TSelector for v1.8
* `ytEventSelection.h`: Add new branches
* `ytEventSelection.cxx`: Add new branches
* Joey removed METOverHTLep12 on Jun/20. Fix `METOverHTLep12` to `METOverHT`


### v15. Add new scripts
* `NUHM2_DSID.tar`: Judita's JO
* `BR_calculation.py`: new script
* `Nevents.py`: new script
* `sum_BR.py`: remove this script (move the function to `BR_calculation.py`)
* `list_trees.py`: change to v1.8
* `Run.sh`: Add v1.8 new samples
* `Run.cxx`: Add v1.8 new samples
* `truth3_plots_comparison.py`:
  * Read the cross-section, branching ratio, and filter efficiency from the files.
  * Use 20170716 results to compare the plots
  * Remove `met>50` cut because it already applied in MET50 filter.
  * Add new function `weight()`


### v14. Use new SR definitions
* `RunSimpleAnalysis.sh`: Add new samples for the truth study
* `convert_EVNT_to_TRUTH.sh`: Add new script
* `MGPy8EG_A14N23LO_Higgsino_2L.txt`: Add Higgsino simplified model file
* `read_Xsec.py`: Add new python script.
* `EwkHiggsino2016.cxx`: Use new SR definitions


### v13. Add new function
* `RunSimpleAnalysis.sh`: Add new samples for the truth study
* `truth3_mll_study.py`: Add new function `compare_n2_decay()`


### v12. Add new script
* `sum_BR.py`: new script to calculate the summation of BR.
* `spectrum.py`: `Xsec_plots_weak()` function call with different arguments.
* `truth3_mll_study.py`: new function `compare_pythia_madgraph_madspin()`.


### v11. Finish spectrum.py
* `spectrum.py`:
  * Modify `read_cross_section()`
  * Rename `Xsec_plots()` to `Xsec_plots_all_FS()`
  * Add new functions `Xsec_plots_weak()`, `sum_of_Xsec()`, `read_slha()`, `mass_spectra()`, and `mass_difference_spectra()`


### v10. Variables are nitialized to -99999
* `truth3_plots_comparison.py`:
  * Change the samples for making plots.
  * Add met > 50 cut for NUHM2
  * Remove most of other cuts and only keep HT30, HTIncl, and mT2 because they have 0
* `EwkHiggsino2016.cxx`:
  * Comment `addHistogram()` 
  * Sort baseline and signal objects after we get them.
  * Remove met cut.
  * Add number of baseline electrons and baseline muons in the ntuple
  * Change the initializatin value from 0 to -99999.


### v09. Add stack plots function and mll study python script
* `RunSimpleAnalysis.sh`: Add new samples for the truth study
* `EwkHiggsino2016.cxx`:
  * Add `baselineTaus` and `nTaus`
  * Set `MTauTau` initial to -99999
  * Comment met cut
  * Move `MTauTau` calculation to `if` condition
* `truth3_plots_comparison.py`:
  * Add more samples
  * Add new function `compare_stack_curves` and make stack plots
  * Bugs fix
* `truth3_mll_study.py`: New python script


### v08. Bugs fixed in `EwkHiggsino2016.cxx`
* `RunSimpleAnalysis.sh`: Add new samples for the truth study
* `truth3_plots_comparison.py`:
  * Add new samples
  * Set log Y for some plots and modify the Y maximum of the plots
  * Change the X range for mll plot
  * Add cuts for some plots when project `TTree` to histogram
* `EwkHiggsino2016.cxx`:
  * Add some histograms which Jesse used in his code
  * Copy `calc_massive_MT2` and `calc_MTauTau` from Jesse's code
  * Comment the radius for OR
  * Add OR(jet, mu), and OR(el, mu) but comment them
  * Add MET < 50 cuts and it only works on NUHM2 samples
  * Fix the bug of `HTLep12` and `METOverHTLep12` calculations
  * Use Jesse's function to calculate `MTauTau`


### v07. Add codes for SimpleAnalysis
* Add new codes `EwkHiggsino2016.cxx` for SimpleAnalysis
* Add new script `RunSimpleAnalysis.sh` for running SimpleAnalysis
* Add new plotting python script `truth3_plots_comparison.py`
* Add `spectrum.py`


### v06. New script for significance
* `AtlasStyle.py`: New script
* `significance.py`: New script
* `plots_making.py`:
  * Add version for the input file
  * Add ATLASLabel
  * Add plot cosmetics
* `get_yields.py`: change version of the input file to v1.5
* `.gitignore`: ignores python `.pyc` file
* `ytEventSelection.cxx`:
  * Use emul triggers: `HLT_mu4_j125_xe90_mht_emul` and `HLT_2mu4_j85_xe50_mht_emul`


### v05. Update to common ntuple v1.5
* `Run.sh`: Update to common ntuple v1.5
* `Run.cxx`: Update to common ntuple v1.5
* `ytEventSelection.h`: Comment some histograms related to `METOverHT` and `METOverHTLep12`
* `ytEventSelection.cxx`: 
  * Comment some histograms related to `METOverHT` and `METOverHTLep12`
  * Add FS protection to reject FS=86 in NUHM2 m12=600
  * Remove `bTagWeight` from the weight calculation
  * Move cutflow related code into `if` condition
  * Modify same flavor, opposit sign, and number of baseline and signal lepton requirement
  * Use all SR cuts including METOverHT cut
* `get_yields.py`: Recoding this script
* `plots_making.py`: Add some new histograms


### v04. Finish implement the cutflow and add all signal samples
* `yt_cutflows.h`:
  * Add numbers for enumeration
  * Remove argument of `print()` method
  * Remove `float weight` from sequential cut methods
* `ytEventSelection.h`:
  * Add `isMC` and `sample`
  * Add `set_isMC()` and `set_sample()`
* `yt_cutflows.cxx`:
  * Add numbers for `cut_name`
  * Modify `print()`
  * Modify all `pass_xxx()` methods
* `ytEventSelection.cxx`:
  * Select sample depends on DSID for cutflow study
  * Calculate weight for MC only
  * Add sequential cuts
  * print out cutflow results
* `Run.cxx`
  * Add `isMC` and related codes
  * Fix typo for `submitDir` for cutflow
  * Change the data `inputFilePath`
  * Add all signal samples for Higgsino and Slepton
* Add new script `Run.sh`


### v03. Add two new classes
* `yt_regions`:
  * Add this new class files: `yt_regions.h` and `yt_regions.cxx`
  * Add this new class into `LinkDef.h`
* `yt_cutflows`:
  * Add this new class files: `yt_cutflows.h` and `yt_cutflows.cxx`
  * Add this new class into `LinkDef.h`
* `ytEventSelection.h`:
  * Add `yt_regions` and `yt_cutflows` objects and related codes
  * Add `isCutflow`, `sample_type`, and `luminosity`
  * Add histograms for the distributions and yields
  * Add `set_isCutflow()`, `set_sample_type()`, and `set_luminosity()` methods
  * Add `debug_print()` method
* `ytEventSelection.cxx`:
  * Add `yt_regions` and `yt_cutflows` objects
  * Add histograms for the distributions and yields
  * Add weight calculation
  * Add cutflows
  * Implement `debug_print()`
* `Run.cxx`:
  * Add descriptions for the usage
  * Add `isCutflow` and the related things
  * Change the input files path and file name
  * Specify the tree name
  * Add the luminosity
* Add python script `plots_making.py` to make distribution plots
* `setupHiggsino.sh`: Add path for the scripts
* Add `.gitignore`
* Add `get_yields.py` to show the yields and weighted yields
* Add `list_trees.py` to list the name of trees in root files


### v02. Add new directories and files
* LinkDef.h: Add `ytEventSelection`
* Add new directories and files
  * ytHiggsinoAnalysis/Root/ytEventSelection.cxx
  * ytHiggsinoAnalysis/misc/NUHM2.C
  * ytHiggsinoAnalysis/misc/NUHM2.h
  * ytHiggsinoAnalysis/util/Run.cxx
  * ytHiggsinoAnalysis/ytHiggsinoAnalysis/ytEventSelection.h


### v01. Initialize the `ytHiggsinoAnalysis` framework
