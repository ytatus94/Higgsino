#!/bin/bash

# Standard setup of NUHM2
setupATLAS
if [ -e rcSetup.sh ]; then
    echo ">>>>> Using the existing rcSetup.sh."
    rcSetup # defaults to whatever was previously set up
else
    echo ">>>>> Setup rcSetup Base,2.5.1"
    rcSetup Base,2.5.1
fi

# Find and compile these packages
echo ">>>>> Compile the packages"
rc find_packages
rc clean
rc compile

# For python scripts
export PYTHONPATH=$PYTHONPATH:$PWD/ytHiggsinoAnalysis/pythons
export PATH=$PATH:$PWD/ytHiggsinoAnalysis/scripts
