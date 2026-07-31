# READ ME
Below this README file is a code with which we investigate the masses of the Z and W bosons, and the ElectroWeak mixing data.

#INSTRUCTIONS
This code takes the CMS Open Data files: 
root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola_merged.root - Drell-Yan Monte Carlo simulated data, 
root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2011B_SingleMu_merged.root - Run2011B experimental data
and it performs different analyses on said data. 
This code does not need to be touched in order to get it working. Everything you need to set happens from the terminal. 
That said, to get it working, you must already have a pre-installed ROOT Framework to your device. If you don't, instructions for installation can be found here: https://root.cern/install/
After you are sure you have the Framework on your device, you can now access the code!
Simply paste in the line: root -l firstAna.cc in your terminal. 
This will cause the program to start compiling. Now, it's going to ask you a few questions about what exactly you want to investigate. Some of the questions include whether you want raw data or ones with selection, what type of data you would like to use - experimental or simulated, and how many events you would like to see. Keep in mind, if you select cut data (with selections), you have the opportunity to change them however you like - the default is always stated, in case you feel a bit lost at the beginning.
After your program is done complining, and you see an empty root prompt:
root[2] 
you need to paste in the line new TBrowser. This will allow you to see what your program has generated. All histograms will be available for you to see.
The ones used in my project were the ones in folder finalHist and some from genHist (available only for DY MC). Browse through all of them, and if you feel like it, do a similar investigation by yourself.
After all the hard work, you will start to understand how physicists get excited by numbers and histograms -_-
