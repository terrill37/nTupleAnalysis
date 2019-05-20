# nTupleAnalysis
Base classes for flat ROOT nTuple processing

# Quickstart example

Setup your CMSSW release area:

> cd CMSSW_10_2_0/src

> cmsenv

Clone this repo with the flat nTuple analysis base class definitions:

> git clone git@github.com:patrickbryant/nTupleAnalysis.git 

Clone the ZZ4b analysis repo:

> git clone git@github.com:patrickbryant/ZZ4b.git

Compile:

> scram b ZZ4b/nTupleAnalysis

Initialize grid certificate:

> voms-proxy-init -voms cms

Run on a simulated data sample:

> nTupleAnalysis ZZ4b/nTupleAnalysis/scripts/nTupleAnalysis_cfg.py -i ZZ4b/fileLists/ZH4b2018.txt -o $PWD -y 2018 -l 59.6e3 --histogramming 1 --histFile hists.root --isMC --nevents 1000

This makes a skimmed nTuple called ZH4b2018/picoAOD.root and a ROOT file with histograms from the event loop called ZH4b2018/hists.root

