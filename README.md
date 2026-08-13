#Investigating the mass of the Z boson using CMS Open Data
##Calculating the mass of the W-boson and the Weinberg mixing angle

#INTRODUCTION
The purpose of this whole code is to investigate CMS Open Data in order to obtain a value for the mass of the Z-boson.
The analysis looks at: 
1. CMS collaboration (2020). Single primary dataset in AOD format from RunB of 2011 (/SingleMu/Run2011B-12Oct2013-v1/AOD). CERN Open Data Portal. DOI: 10.7483/OPENDATA.CMS.XBTD.NKD3 - regarded as Experimental data or Run2011B in explanation
2. CMS collaboration (2016). Simulated dataset DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola in AODSIM format for 2011 collision data(SM inclusive). CERN Open Data Portal. DOI: 10.7483/OPENDATA.CMS.4475.SSXE - regarded as DY-MC in explanation.
This code takes either one of those datasets, (optionally) applies selections of your choice, and produces histograms related to the investigation of the mass of the Z-boson.

To prefice, this code does not have to be altered in order to get it working. That being said, you are completely free to make adjustments as you like. 
However, in order for your computer to be able to read and execute the code, you must already have ROOT Framework installed on your device, and it must work. Instructions for installation can be found here -> https://root.cern/install/

#INSTRUCTIONS
1. You need to initialize your root, which means going to the folder where you have downloaded it (using your terminal), and writing: source root/bin/thisroot.sh
2. After that is done, navigate to the folder where you have saved a copy of this repository. Paste in the line: root -l firstAna.cc
3. The terminal will now start compiling the code, and it will start asking you questions about what exactly it is you want to investigate. If you wish to follow the same process I did: 
- To the question whether you want your data with selections, answer pre-cut. This way you will get your histograms without any selections applied. 
- To the question whether the data you want to see is experimental, answer no. This will the results to be DY-MC, which means you will be able to see processes before the events were let into the detector system. In other words, you will have access to the Generated Particles collection, where you will be able to see the initial values of your events before they go into the detector system. 
- To the question of how many events you want the script to run on, answer whatever you like. If you wish to use anything except the total amount of events (~35 million), simply answer the specific number you want. If you, however, want to use the entire population, write -1 (keep in mind that it will take about 2-3 hours to execute the code).
4.  When the terminal is done executing the code, write in the empty root prompt: new TBrowser. 
This will launch a TBrowser, where you will be able to see all the histograms. At the top of your page, you will see your current working directory, and below it, your newly generated file called my_histograms_mc_precut.root
5. Open the file, and check the different folders and the histograms in them. When choosing appropripriate selections, I investigated the histograms in the directory finalHist. Decide on what selections you would like to apply (I have applied selections to Muon_pt, MET_pt, Muon_eta, Muon_iso04, Muon_dxy, Muon_dz, Dimuon_cosDeltaPhi and those are the only selections the terminal will ask you about when running the program again, so if you wish to apply cuts to anything else, in your copy of the code add your wanted selections).
6. After you have looked at those, take a look at genHist. Here, hGenPart_ZMass and hGenPart_dimuonMass interest you the most. Take a look at them, and when you are done exit your root session. 

Load the script again, but this time: 
1. To the question whether you want your data with selections, answer cut.
2. To the question whether the data you want to see is experimental, answer no.
3. You will now get a series of questions about your desired selection. State what you want yours to be (the ones I used are stated as default, so if you wish to use those, copy the number you see).
4. Write the number of events you want (it would be best if this number coincides with the one before).
5. When it is done executing the code, repeat the process of opening a TBrowser, and navigate to the new file called: my_histograms_cut_mc.root. 
Take a look at the genHist folder, and to the aforementioned hGenPart_ZMass and hGenPart_dimuonMass. Take a look at what has changed compared to last time, and most importantly, keep track of the root file your program has just generated - you will need it later. 

Now, the fun is about to begin (not after a little bit more suffering though).

Exit your current root session, again, and load the script. This time: 
1. To the question whether you want your data with selections, answer cut.
2. To the question whether the data you want to see is experimental, answer yes.
3. When prompted, use the selections you have settled on. 
4. Write the number of events you want. 
5. When it is done executing the code, repeat the process of opening a TBrowser, and navigate to the new files called: my_histograms_experimental_mc.root. 
Go to the finalHist folder, and it is finally time to get some values of the Z boson. 
Exit your root session, for the final time, and in your copy of my repository locate the file called fitHist.cc.
- Paste in the line: root -l fitHist.cc
This will cause a separate code to load, which applies appropriate fits to your histograms. In order not to load you with too much (probably unnecessary information), this code only applies a fit to hGenPart_dimuonMass (from the DY MC data) and to hDimuon_Mass (from the Run2011B data). I have selected only those because they are both reconstructions of a di-muon event but in 2 very different cases. Feel free to change the code, and edit which histograms you want to fit and with what distribution exactly. 

When the script executes, you will get 2 histograms on the same Canvas side-by-side. Look closely at the legend and you will notice that there are 2 different distributions for both cases. That is so because the data used in the Generated Particles collection (from which we reconstruct di-muon events in order to get Z), the events never really reach the detector system of the collider - they are just simulated. This means that, essentially, we can use the Breit-Wigner distribution to fit these data (we use this distribution exactly because it is a mathematical function created to best describe mass distributions of short-lived, unstable particles like the Z boson). Then, the other histogram (hDimuon_mass from Run2011B) has been fitted using a so-called Voigtian distribution - that is just a convulsion of the Breit-Wigner and Gaussian distributions. We use the Gaussian distribution because these events are no longer simulated. They pass through the detector system, which will cause our Z-peak to be a bit "smudged" due to the uncertainty, coming from the detector system. So, the Gaussian is used to further clarify our value of the mass of Z. 

If you move the legends a bit, you will see what results your fitting has led to. The Mass and the Width concern you the most. Check their values, and see how they compare to the results in this website -> https://pdglive.lbl.gov/Particle.action?node=S044&init=0
These are the current best values for Z, from the Particle Data Group 

And, you are done! You have obtained values for the mass of the Z-boson! 

Now, as a bit of an exercise, load your DY MC data without selections, and take a look at hDimuon_mass. Take logs on both the X and the Y-axis:
- Load the histogram, and hover on either axis with your cursor, and move around until it becomes a plus sign. 
- When that happens, right click, and from the menu that pops up, select LogX and LogY. You will get a very strange looking histogram, but don't worry, we want that to happen. 
- Hover with your cursor on the X-axis, and wait until it becomes a little hand. Once that happens, in the menu, find SetRangeUser, and click on it. Write 1 and 100 in each box - we set the range of the X-axis as from 0.5 to 150. 
- You will now see many different strange bumps, with the most prominent being at around 90. 

My task for you is to search "Drell-Yan spectra" on Google. Looking at the Google results as reference, can you determine which bosons you can identify in your own histogram?

(F. Takahashi et al. (Particle Data Group), to be published in Int. J. Mod. Phys. A41, 2630011 (2026))

