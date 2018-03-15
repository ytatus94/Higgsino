# Higgsino
The NUHM2 Higgsino study

---
### v52. Modify script 
* Modify `reweight_truth3_mll.C` so it can make Higgsino and NUHM2 mll comparison plot as shown in Fig1 in paper.


### v51. Align the files on lxplus
* Add new files:
  * `ytHiggsinoAnalysis/misc/NUHM2_Strong.txt`
  * `ytHiggsinoAnalysis/misc/NUHM2_Strong_SUSYTools.txt`
  * `ytHiggsinoAnalysis/misc/NUHM2_Weak_SUSYTools.txt`
* Add new folders:
  * `ytHiggsinoAnalysis/misc/NUHM2/`
  * `ytHiggsinoAnalysis/misc/StrongSLHA/`
  * `ytHiggsinoAnalysis/misc/WeakSLHA/`
* Modify script: `ytHiggsinoAnalysis/pythons/plot_truth3_kinematics.py`


### v50. Add new csv files
* Add new csv files:
  * `NUHM2_all_points_upperlimit_upperlimit_only_MCprod_NoSys_doNewFFs.csv`
  * `NUHM2_all_points_upperlimit_upperlimit_only_MCprod_AllSys_doNewFFs.csv`
* `upperlimit_xsec.py`: change input file


### v49. Add new csv files
* Add new csv files:
  * `NUHM2_all_points_upperlimit_upperlimit_only_Judita_MCprod_AllSys_doNewFFs.csv`
  * `NUHM2_all_points_upperlimit_upperlimit_only_reweighting_AllSys_doNewFFs.csv`
  * `NUHM2_all_points_upperlimit_upperlimit_only_reweighting_NoSys_doNewFFs.csv`
* `upperlimit_xsec.py`:
  * re-draw y-axis to show ticks
  * Instead of using `j = i + 1`, use `m12` to find the correct element in list


### v48. Script for upper limit plot
* `AtlasStyle.py`: Set font
* `NUHM2_Weak.txt`: New SUSYTools cross-section file
* `upperlimit_xsec.py`: New script to make cross-section upper limit plot.


### v47. Modify the cutflow to fit the internal note
* `yt_cutflows.h` and `yt_cutflows.cxx`: Add codes for cutflow table in the note.
* `ytEventSelection.cxx`:
  * Add codes for cutflow table in the note.
  * Add `bTagWeight` and `FFWeight` in the weight calculation.
* `Run.cxx` and `Run.sh`:
  * Use `/afs/cern.ch/work/j/jeliu/public/HiggsinoFitterTrees/v1_9/AllSignals_SusySkimHiggsino_v1.9b_SUSY16_tree_AllSys.root`.


### v46. Modify script
* `truth3_mll_study.py`:
  * Fix the typo in efficiency
  * Use the accurate value for BRs
* `plot_distributions_in_SR.py`:
  * Use thicker line size for NUHM2
  * NUHM2 yields are multiply by 10 before making plot


### v45. Modify script
* `plot_distributions_in_SR.py`: modify histogram xmax range


### v44. Modify scripts
* `reweight_mc_event_weight.C`: change plot style
* `reweight_truth3_mll.C`:
  * rename `reweight_truth3.C` to `reweight_truth3_mll.C`
  * change plot style
* `truth3_mll_study.py`: change plot style
* `plot_distributions_in_SR.py`: add SFOS results


### v43. Modify scripts
* `Nevents.py`: change the output format
* `compare_files.py`: Add comments
* `get_mass_difference.py`: Remove extra space
* `get_yields.py`: Remove extra space
* `plot_distributions_in_SR.py`: Add comments
* `plot_truth3_kinematics.py`: Add comments
* `read_Xsec.py`: Add comments
* `truth3_mll_study.py`: Add comments
* `reweight_mc_event_weight.C`: Change input path
* `reweight_truth3.C`: Change input path


### v42. Move old scripts to obsolete directory
* `misc/obsolete/`: Create new directory and move the following files to this directory
  * from `python/`:
    * `BR_calculation.py`
    * `fit_common_ntuple.py`
    * `make_weight_plot.py`
    * `plots_making.py`
    * `reweight.py`
    * `show_AMI_info.py`
    * `test_fit.py`
    * `truth3_plots_comparison.py`
  * from `scripts/`:
    * `FuncMllDistr.C`
    * `file_path.C`
    * `fit_common_ntuple.C`
    * `mll_ratio.C`
    * `overlap_histograms.C`
    * `plot_reweight_common_ntuple_mll.C`
    * `reweight_common_ntuple.C`
    * `reweight_kinematic_variables.C`
    * `test_120_100.C`
    * `test_Higgsino_160_100.C`
    * `test_Higgsino_190_150_m12_600.C`
    * `test_fit.C`
    * `view_combine_hist.C`


### v41. Add new cutflow results
* `make_cutflow.py`: modify script
* `cutflows_20171027/`: rename `cutflows/` to `cutflows_20171027/`
* `cutflows_20171028/`: new results
* `cutflows_20171029/`: new results
* `plot_distributions_in_SR.py`: change outptu digits
* `significance.py`: Use new results for nsig and nbkg


### v40. modify python scripts
* `fit_common_ntuple.py`: Use new input files
* `test_fit.py`: Change the input path
* `AtlasStyle.py`: Change the sapce for input string
* `truth3_mll_study.py`:
  * fix typo
  * Change the input path, y title and draw option


### v39. Add new cutflow results
* `ytHiggsinoAnalysis/misc/HF/`: New results for cutflows


### v38. modify python scripts
* `plot_distributions_in_SR.py`: merge `plot_N_minus_one.py` into this script
* `plot_N_minus_one.py`: delete this script
* `truth3_plots_comparison.py`: Use new input files


### v37. Add new script
* `plot_N_minus_one.py`: new script for N-1 plots


### v36. modify python scripts
* `AtlasStyle.py`: change font size
* `BR_calculation.py`: change input path
* `compare_files.py`: Add new line at the end of file
* `get_mass_difference.py`: change the output format
* `Nevents.py`: change the BR, Eff, weighted events, N_SR values
* `ytEventSelection.cxx`: Use b-jet pT>20
* `add_weight_to_common_ntuple.C`: remove empty line
* `Run.sh`: remove empty line


### v35. Add new python scripts:
* `get_truth3_information.py`: new script to get TRUTH3 information
* `plot_distributions_in_SR.py`: new script to make kinematic distribution in SR
* `plot_truth3_kinematics.py`: new script to make kinematic distributions using official TRUTH3
* `show_AMI_info.py`: new script to get filter efficiency


### v34. modify python scripts
* `BR_calculation.py`: modify the comments
* `compare_files.py`: rename `check_slha.py` and add new function
* `get_yields.py`: add SRee, SRmm, SRSF yields and weighted yields
* `spectrum.py`: Bug fixed
* `make_weight_plot.py`: change the input path
* `plots_making.py`: change the input path and files
* `reweight.py`: change the input path and files


### v33. Update to v1.9 and v1.9b ntuples
* `ytEventSelection.h`: Use v1.9b ntuple
* `ytEventSelection.cxx`: Use v1.9b ntuple and add weight to optimize SR histograms.
* `Run.cxx`: Use v1.9 and v1.9b ntuples
* `Run.sh`: Use v1.9 and v1.9b ntuples


### v32. Modify python scripts
* `BR_calculation.py`: modify script to run SLHA and SusyHit
* `Nevents.py`: Use official TRUTH3 SimpleAnalysis results
* `check_slha.py`: Add commons and fix typo
* `get_mass_difference.py`: Add common
* `list_trees.py`: Add commons and change to v1.9
* `cutflow_v1.9.txt`: Add a new log file.
* `file_path.C`: Use the official TRUTH3 SimpleAnalysis results


### v31. New TRUTH3
* `BR_calculation.py`: Add code to read SusyHit output.
* `RunSimpleAnalysis.sh`: Add new official TRUTH3 samples.
* `EwkNUHM22016.cxx`: Use new SR, CR, and VR definitions


### v30. Add Higgsino optimised SR
* `show_normalization_factor.C`: fix bugs
* `plot_reweight_common_ntuple_mll.C`: change output file name
* `get_yields.py`: Change path
* `make_weight_plot.py`: New script
* `yt_regions.h`: Add new functions
* `yt_regions.cxx`: Implement new functions
* `ytEventSelection.h`: Add new histograms
* `ytEventSelection.cxx`:
  * Implement new histograms
  * Add common cut, 2l channel cut, and Higgsino SR cuts
  * B-jet uses `nBJet20_MV2c10`
  * Fill yields to new histograms


### v29. add new branches to common ntuple
* `add_weight_to_common_ntuple.C`: New script
* `plot_reweight_common_ntuple_mll.C`: New script
* `get_mass_difference.py`: modify output
* `Joana_reweight.cxx`: Add DSID for C1C1, N2C1p, and N2C1m
* `reweight_mc_event_weight.C`: Add weight when fill histogram


### v28. reweight to luminosity
* `fit_common_ntuple.py`: move to `misc/`
* `test_fit.py`: move to `misc/`
* `Joana_reweight.cxx`: fix typo
* `reweight_truth3.C`: remove `TChain.h`
* `show_normalization_factor.C`: fix typo
* `reweight_kinematic_variables.C`: remove extra spaces.
* `ytUtility.C`:
  * `get_cross_section()`: New function
  * `get_filter_efficiency()`: New function
  * `get_luminosity()`: New function
  * `get_sum_of_event_weight()`: New function
  * `get_mc_weight()`: New function
* `reweight.py`: New script
* `reweight_mc_event_weight.C`: New script. This is based on `reweight_kinematic_variables.C`


### v27. minor corrections
* `Xsec.pdf`: Change legend position and move to `log/`
* `yields.txt`: Remove file, but add two files (yields_v1.6.txt and yields_v1.8.txt) in `log/` 
* `BR_calculation.py`: Add new functions `list_branching_ratio()` and `get_slha_file()`
* `Nevents.py`: Add new function `total_number_of_events_produced()` and change legend position.
* `check_slha.py`: New end of line
* `read_Xsec.py`: Add new function `cross_section_ratio()`
* `significance.py`: print information
* `test_fit.py`: Use new directory `20170817/`
* `Run.sh`: Use v1.8b samples
* `fit_common_ntuple.C`: Change legend position
* `show_normalization_factor.C`: Use new mapping
* `Run.cxx`: Use v1.8b samples
* `test_Higgsino_170_150_m12_600.C`: Change name to `test_Higgsino_190_150_m12_600.C`
* `ytUtility.C`: New end of line
* `test_fit.C`: Remove unnecessary lines
* `test_fit.py`: Remove unnecessary parts.


### v26. v1.8 yields
* `yields.txt`: Add v1.8 yields
* `get_yields.py`: Fix the v1.8 path


### v25. Update to common ntuple v1.8
* `ytEventSelection.cxx`: Fix the bus error
  * All vector container pointers need to set to zero at the beginning


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
