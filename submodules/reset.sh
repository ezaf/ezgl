#!/bin/bash

###############################################################################
#### WARNING: Make sure you're calling this script from its own directory! ####
###############################################################################

# Clean all directories
for dir in `ls -d */`; do
    rm -rf $dir
done

# Initialize and re-download all submodules
git submodule init
git submodule update
