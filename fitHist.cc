void fitHist(){
	TFile *file1 = TFile::Open("my_histograms_cut_mc.root");
	TFile *file2 = TFile::Open("my_histograms_cut_experimental.root");
	
	TH1F *hGenPart_dimuonMass = (TH1F*)file1->Get("drellYan/genHist/hGenPart_dimuonMass");
	TH1F *hDimuon_mass = (TH1F*)file2->Get("Run2011B/finalHist/hDimuon_mass");
	
	gStyle->SetOptFit(1);
	gStyle->SetFitFormat("5.6g");
	
	TCanvas *c = new TCanvas("c", "Z-boson reconstruction masses", 1200, 600);
	c->Divide(2, 1);
	////////////////FITTING MC HISTOGRAMS WITH BREIT-WIGNER////////////////////
	TF1 *bw = new TF1("bw", "[0]*[1]*[1]*[2]*[2]/((x*x - [1]*[1])*(x*x - [1]*[1]) + [1]*[1]*[2]*[2])", 60., 120.);
	bw->SetParNames("Norm", "Mass", "Width");
	bw->SetParameters(hGenPart_dimuonMass->GetMaximum(), 91., 2.5);
	
	hGenPart_dimuonMass->Sumw2();
	c->cd(1);
	hGenPart_dimuonMass->Fit(bw, "R", " ", 60., 120.);
	///////////////FITTING EXPERIMENTAL HISTOGRAMS WITH VOIGTIAN//////////////
	TF1 *voigtFit = new TF1("voigtFit", "[0]*TMath::Voigt(x - [1], [2], [3])", 60., 120.);
	voigtFit->SetParNames("Norm", "Mass", "Sigma", "Width");
	voigtFit->SetParameters(hDimuon_mass->GetMaximum(), 91., 2.5, 2.5);
	
	hDimuon_mass->Sumw2();
	hDimuon_mass->Fit(voigtFit, "R");
	
	///////////////DRAWING GENPART HISTOGRAM/////////////////////////////////
	hGenPart_dimuonMass->GetXaxis()->SetTitle("mass(#mu#mu) [GeV/c^{2}]");
	hGenPart_dimuonMass->GetYaxis()->SetTitle("events / 0.5[GeV/c^{2}]");
	hGenPart_dimuonMass->SetTitle("Mass of di-muon event - DY MC");
	
	auto legGen = new TLegend(0.6, 0.7, 0.88, 0.88);
	legGen->AddEntry(hGenPart_dimuonMass, "CMS Open Data - DY MC");
	legGen->AddEntry(bw, "Breit-Wigner fit", "lpf");
	
	gStyle->SetOptStat("e");
	hGenPart_dimuonMass->Draw();
	legGen->Draw();
	
	/////////////////DRAWING EXPERIMENTAL HISTOGRAM//////////////////////////
	c->cd(2);
	hDimuon_mass->GetXaxis()->SetTitle("mass(#mu#mu) [GeV/c^{2}]");
	hDimuon_mass->GetYaxis()->SetTitle("events / 0.5[GeV/c^{2}]");
	hDimuon_mass->SetTitle("Mass of di-muon event - Run2011B");
	
	auto legExp = new TLegend(0.6, 0.7, 0.88, 0.88);
	legExp->AddEntry(hDimuon_mass, "CMS Open Data - Run2011B");
	legExp->AddEntry(voigtFit, "Voigtian fit", "lpf");
	
	gStyle->SetOptStat("e");
	hDimuon_mass->Draw();
	legExp->Draw();	
}
	
