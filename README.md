#Investigating the mass of the Z boson using CMS Open Data
##Calculating the mass of the W-boson and the Weinberg mixing angle

#INTRODUCTION
The purpose of this whole code is to investigate CMS Open Data in order to obtain a value for the mass of the Z-boson.
The analysis looks at: 
1. CMS collaboration (2020). Single primary dataset in AOD format from RunB of 2011 (/SingleMu/Run2011B-12Oct2013-v1/AOD). CERN Open Data Portal. DOI: 10.7483/OPENDATA.CMS.XBTD.NKD3 - regarded as Experimental data in explanation
2. CMS collaboration (2016). Simulated dataset DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola in AODSIM format for 2011 collision data(SM inclusive). CERN Open Data Portal. DOI: 10.7483/OPENDATA.CMS.4475.SSXE - regarded as DY-MC in explanation.
This code takes either one of those datasets, (optionally) applies selections of your choice, and produces histograms related to the investigation of the mass of the Z-boson.

To prefice this, this code does not have to be altered in order to get it working. That being said, you are completely free to make adjustments as you like. 
However, in order for your computer to be able to read and execute the code, you must already have ROOT Framework installed on your device, and it must work. Instructions for installation can be found here -> https://root.cern/install/

#INSTRUCTIONS
1. Boot up ROOT Framework. Paste in the line: root -l firstAna.cc
2. The terminal will now start compiling the code, and it will start asking you questions about what exactly it is you want to investigate. If you wish to follow the same process I did: 
- To the question whether you want your data with selections, answer pre-cut. This way you will get your histograms without any selections applied. 
- To the question whether the data you want to see is experimental, answer no. This will the results to be DY-MC, which means you will be able to see processes before the events were detected in the detector system. In other words, you will have access to the Generated Particles collection, where you will be able to see the initial values of your events before they go into the detector system. 
- To the question of how many events you want the script to run on, answer whatever you like. If you wish to use anything except the total amount of events (35 million), simply answer the specific number you want. If you, however, want to use the entire population, write -1 (keep in mind that it will take about 2-3 hours).  
3.  When the terminal is done executing the code, write in the empty root prompt: new TBrowser. 
This will launch a TBrowser, where you will be able to see all the histograms. At the top of your page, you will see your current working directory, and below it your newly generated file, called my_histograms_mc_precut.root
4. Open the file, and check the different folders and the histograms in them. When choosing appropripriate selections, I investigated the histograms in the directory finalHist. Decide on what selections you would like to apply (I have applied selections to Muon_pt, MET_pt, Muon_eta, Muon_iso04, Muon_dxy, Muon_dz, Dimuon_cosDeltaPhi, if you wish to apply cuts to anything else, in your copy of the code, add your wanted selections).
5. After you have looked at those, take a look at genHist. Here, hGenPart_ZMass and hGenPart_dimuonMass interest you the most. 

Now, after choosing your selections, exit your root session. Load the script again, but this time: 
1. To the question whether you want your data with selections, answer cut.
2. To the question whether the data you want to see is experimental, answer no.
3. You will now get a series of questions about your desired selection. State what you want yours to be (the ones are used are stated as default, so if you wish to use those, copy the number you see).
4. Write the number of events you want (it would be best if this number coincides with the one before).
5. When it is done executing the code, repeat the process of opening a TBrowser, and navigate to the new files called: my_histograms_cut_mc.root. 
Now, go to the genHist folder again. In order to get an explicit value for the Z-boson mass, you must fit those histograms with a Breit-Wigner function. Make sure that in your TBrowser, you have either histogram open. Then, paste in the code: 

TF1 *bw = new TF1("bw", "[0]*[1]*[1]*[2]*[2]/((x*x - [1]*[1])*(x*x - [1]*[1]) + [1]*[1]*[2]*[2])", 60., 120.);

bw->SetParNames("Norm", "Mass", "Width");

bw->SetParameters(hGenPart_dimuonMass->GetMaximum(), 91., 2.5);

hGenPart_dimuonMass->Sumw2();

hGenPart_dimuonMass->Fit(bw, "R"," ", 60., 120.);

gStyle->SetOptFit(1);
	
If you wish to place the same fit on a different histogram, in the last 3 lines of the code above, change the name of the histogram before you write them in root. 
You will now see the value for the Z-boson in your terminal. 

Do not fit the hDimuon_mass histogram yet, because firstly, this is a Z-boson reconstruction, which means you have other processes, alongside the one you're investigating, so your answer will not be accurate, and, secondly, because these are data which go into the detector system, which means you have uncertainty from the detector itself. To bypass this, you will need to use a Breit-Wigner and Gaussian convulsion (alternative name: Voigtian function). The Breit-Wigner function is specifically used for particle peak reconstruction. The Gaussian distribution is used to offset the uncertainty from the detector system itself. 

You got your first values of Z, congratulations! However, you still haven't reached the meat and potatoes of this analysis yet, sadly. 

Exit your root session, again, and load the script. This time: 
1. To the question whether you want your data with selections, answer cut.
2. To the question whether the data you want to see is experimental, answer yes.
3. When asked, use the selections you have settled on. 
4. Write the number of events you want. 
5. When it is done executing the code, repeat the process of opening a TBrowser, and navigate to the new files called: my_histograms_experimental_mc.root. 
Go to the finalHist folder, and it is finally time to use the hDimuon_mass histograms. Make sure that in your TBrowser, this specific histogram is open, and paste in the code: 

TF1 *voigtFit = new TF1("voigtFit", "[0]*TMath::Voigt(x - [1], [2], [3])", 60., 120.);

voigtFit->SetParNames("Norm", "Mass", "Sigma", "Width");

voigtFit->SetParameters(hDimuon_mass->GetMaximum(), 91., 2.5, 2.5);

hDimuon_mass->Sumw2();

hDimuon_mass->Fit(voigtFit, "R", " ", 60., 120.);

gStyle->SetOptFit(1);

You have now fitted your hDimuon_mass histogram with a Voigtian function, and you have gotten a final answer for the mass of the Z-boson!!!!!
