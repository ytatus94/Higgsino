# Higgsino
The NUHM2 Higgsino study

---

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
* `Run.cxx`
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
