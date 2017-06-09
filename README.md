# Higgsino
The NUHM2 Higgsino study

---

### v06. New script for significance
* `AtlasStyle.py`: New script
* `significance.py`: New script
* `plots_making.py`:
  * Add version for the input file.
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
  * Add FS protection to reject FS=86 in NUHM2 m12=600.
  * Remove `bTagWeight` from the weight calculation.
  * Move cutflow related code into `if` condition
  * Modify same flavor, opposit sign, and number of baseline and signal lepton requirement.
  * Use all SR cuts including METOverHT cut.
* `get_yields.py`: Recoding this script.
* `plots_making.py`: Add some new histograms


### v04. Finish implement the cutflow and add all signal samples.
* `yt_cutflows.h`:
  * Add numbers for enumeration.
  * Remove argument of `print()` method.
  * Remove `float weight` from sequential cut methods.
* `ytEventSelection.h`:
  * Add `isMC` and `sample`.
  * Add `set_isMC()` and `set_sample()`.
* `yt_cutflows.cxx`:
  * Add numbers for `cut_name`.
  * Modify `print()`.
  * Modify all `pass_xxx()` methods.
* `ytEventSelection.cxx`:
  * Select sample depends on DSID for cutflow study.
  * Calculate weight for MC only.
  * Add sequential cuts.
  * print out cutflow results.
* `Run.cxx`
  * Add `isMC` and related codes.
  * Fix typo for `submitDir` for cutflow.
  * Change the data `inputFilePath`.
  * Add all signal samples for Higgsino and Slepton.
* Add new script `Run.sh`


### v03. Add two new classes
* `yt_regions`:
  * Add this new class files: `yt_regions.h` and `yt_regions.cxx`.
  * Add this new class into `LinkDef.h`.
* `yt_cutflows`:
  * Add this new class files: `yt_cutflows.h` and `yt_cutflows.cxx`.
  * Add this new class into `LinkDef.h`.
* `ytEventSelection.h`:
  * Add `yt_regions` and `yt_cutflows` objects and related codes.
  * Add `isCutflow`, `sample_type`, and `luminosity`.
  * Add histograms for the distributions and yields.
  * Add `set_isCutflow()`, `set_sample_type()`, and `set_luminosity()` methods.
  * Add `debug_print()` method.
* `ytEventSelection.cxx`:
  * Add `yt_regions` and `yt_cutflows` objects.
  * Add histograms for the distributions and yields.
  * Add weight calculation.
  * Add cutflows.
  * Implement `debug_print()`.
* `Run.cxx`:
  * Add descriptions for the usage
  * Add `isCutflow` and the related things.
  * Change the input files path and file name.
  * Specify the tree name
  * Add the luminosity
* Add python script `plots_making.py` to make distribution plots
* `setupHiggsino.sh`: Add path for the scripts
* Add `.gitignore`
* Add `get_yields.py` to show the yields and weighted yields
* Add `list_trees.py` to list the name of trees in root files.


### v02. Add new directories and files
* LinkDef.h: Add `ytEventSelection`
* Add new directories and files
  * ytHiggsinoAnalysis/Root/ytEventSelection.cxx
  * ytHiggsinoAnalysis/misc/NUHM2.C
  * ytHiggsinoAnalysis/misc/NUHM2.h
  * ytHiggsinoAnalysis/util/Run.cxx
  * ytHiggsinoAnalysis/ytHiggsinoAnalysis/ytEventSelection.h

### v01. Initialize the `ytHiggsinoAnalysis` framework
