#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <cmath>

void Wana(){

std::string mode;
std::cout << "enter your preference (cut or pre-cut): ";
std::cin >> mode;

const char* fileNames[1] = {"root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2011B_SingleMu_merged.root"};
const char* fileLabels[1] = {"Run2011B"};
int nFiles = 1;

double ptCut = 30.0;
double etaCut = 2.1;
double isoCut = 0.1;
double dxyCut = 0.1;
double dzCut = 15.0;
double metCut = 25.0;
double cosCut = 0.8;

bool applyCuts = false;
if(mode == "cut"){
	applyCuts = true;
	
	std::cout << "enter pt cut (default = 30): ";
	std::cin >> ptCut;
	
	std::cout << "enter eta cut (default = 2.1): ";
	std::cin >> etaCut;
	
	std::cout << "enter isolation cut (default = 0.1): ";
	std::cin >> isoCut;
	
	std::cout << "enter dxy cut (default = 0.1): ";
	std::cin >> dxyCut;
	
	std::cout << "enter dz cut (default = 15): ";
	std::cin >> dzCut;
	
	std::cout << "enter MET pt cut (default = 35): ";
	std::cin >> metCut;
	
	std::cout << "enter cos(deltaPhi) cut (default = 0.8): ";
	std::cin >> cosCut;
}
else if(mode == "pre-cut"){
	applyCuts = false;
}
else{
	std::cerr << "invalid option. use only 'cut' or 'pre-cut' \n";
	return;
}

Int_t maxEntries;
std::cout << "enter desired amount of entries (use -1 for entire population) \n";
std::cin >> maxEntries;

std::string outputFile = "W_histograms_";
outputFile += (applyCuts ? "cut" : "precut");
outputFile += ".root";

TFile *fout = new TFile(outputFile.c_str(), "RECREATE");
cout << "output file name: " << outputFile << endl;

for (int fileIdx = 0; fileIdx < nFiles; fileIdx++){
	TString label = fileLabels[fileIdx];
	
	TChain *t1 = new TChain("Events");
	t1->Add(fileNames[fileIdx]);
	t1->Print();
	
	UInt_t nMuon;
	Int_t Muon_charge[5000];
	Float_t Muon_pt[5000];
	Float_t Muon_eta[5000];
	Float_t Muon_phi[5000];
	Float_t Muon_mass[5000];
	Float_t Muon_dxy[5000];
	Float_t Muon_dz[5000];
	Float_t Muon_pfRelIso04_all[5000];
	Float_t MET_pt;
	Float_t MET_phi;
	
	t1->SetBranchAddress("nMuon", &nMuon);
   	t1->SetBranchAddress("Muon_charge", &Muon_charge);
        t1->SetBranchAddress("Muon_pt", &Muon_pt);
    	t1->SetBranchAddress("Muon_eta", &Muon_eta);
    	t1->SetBranchAddress("Muon_phi", &Muon_phi);
    	t1->SetBranchAddress("Muon_mass", &Muon_mass);
    	t1->SetBranchAddress("Muon_dxy", &Muon_dxy);
    	t1->SetBranchAddress("Muon_dz", &Muon_dz);
    	t1->SetBranchAddress("Muon_pfRelIso04_all", &Muon_pfRelIso04_all);
    	t1->SetBranchAddress("MET_pt", &MET_pt);
    	t1->SetBranchAddress("MET_phi", &MET_phi);
    	
    	TH1F *hMuon_pt = new TH1F("hMuon_pt", "Leading muon p_{T};p_{T} [GeV/c];Events / 1 [GeV/c]", 200, 0., 200.);
        TH1F *hMET_pt = new TH1F("hMET_pt", "Transverse momentum of METs;p_{T}(MET) [GeV/c];Events / 1 [GeV/c]", 200, 0., 200.);
        TH1F *hW_deltaPhi= new TH1F("hW_deltaPhi", "#Delta#varphi of W-boson reconstruction;#Delta#varphi(#mu, MET);Events / 0.1", 130, -6.5, 6.5);
        TH1F *hW_transverseMass = new TH1F("hW_transverseMass", "W transverse mass;mass(#mu, MET) [GeV/c^{2}];Events / 1 [GeV/c^{2}]", 200, 0., 200.);
        TH2F *hW_MtVMuon_pt = new TH2F("hW_MtVMuon_pt", "Transverse mass of W boson against transverse momentum of muon events;p_{T} of all muon events [GeV/c];transverse mass(W) [GeV/c^{2}]", 200, 0., 200., 200, 0., 200.);
        TH1F *hW_cosDeltaPhi = new TH1F("hW_cosDeltaPhi", "cos(#Delta#varphi) of W-boson reconstruction;cos(#Delta#varphi)(#mu, MET);Entries / 0.1", 20, -1., 1.);
        
        std::vector<TH1*> histos = {
        hMuon_pt, hMET_pt, hW_deltaPhi, hW_transverseMass, hW_MtVMuon_pt, hW_cosDeltaPhi
        };
	for (auto* h : histos) h->SetDirectory(0);
	
	Int_t nentries = t1->GetEntries();
	cout << "Number of events in file: " << nentries << endl;
	
	Int_t entriesToRun = nentries;
	if(maxEntries > 0 && maxEntries < nentries) entriesToRun = maxEntries;
	cout << "entries to process: " << entriesToRun << endl;
	
	for(Int_t i = 0; i < entriesToRun; i++){
		t1->GetEntry(i);
		
		if (nMuon < 1) continue;
		
		int leadIdx = 0;
		for (UInt_t mu = 1; mu < nMuon; mu++){
			if (Muon_pt[mu] > Muon_pt[leadIdx]) leadIdx = mu;
		}
		
		double deltaPhi = TVector2::Phi_mpi_pi(Muon_phi[leadIdx] - MET_phi);
		double cosDeltaPhi = TMath::Cos(deltaPhi);
		
		if(applyCuts){
			if (Muon_pt[leadIdx] <= ptCut) continue;
			if (fabs(Muon_eta[leadIdx]) >= etaCut) continue;
			if (Muon_pfRelIso04_all[leadIdx] > isoCut) continue;
			if (fabs(Muon_dxy[leadIdx]) >= dxyCut) continue;
			if (fabs(Muon_dz[leadIdx]) >= dzCut) continue;
			if (MET_pt <= metCut) continue;	
			if (cosDeltaPhi >= cosCut) continue;
		}

		double Mt = TMath::Sqrt(2.0 * Muon_pt[leadIdx] * MET_pt * (1 - cosDeltaPhi));
		
		hMuon_pt->Fill(Muon_pt[leadIdx]);
		hMET_pt->Fill(MET_pt);
		hW_deltaPhi->Fill(deltaPhi);
		hW_transverseMass->Fill(Mt);
		hW_MtVMuon_pt->Fill(Muon_pt[leadIdx], Mt);
		hW_cosDeltaPhi->Fill(cosDeltaPhi);
	}
	
	fout->mkdir(label + "/Whist");
	fout->cd(label + "/Whist");
	for (auto* h : histos) h->Write();
	fout->cd("");
	
	for (auto* h : histos) delete h;
	delete t1;
}
fout->Write();
fout->Close();
}

