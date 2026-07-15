#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <cmath>

void firstAna(){

std::string mode;
std::cout << "enter your preference (cut or pre-cut): ";
std::cin >> mode;

bool applyCuts = false;
if(mode == "cut"){
	applyCuts = true;
}
else if(mode == "pre-cut"){
	applyCuts = false;
}
else{
	std::cerr << "invalid option. use only 'cut' or 'pre-cut' \n";
	return;
}

//TFile *f = TFile::Open("root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2011A_SingleMu/94000E51-36DE-4AE5-939B-12EE231D9755.root");
//TTree *t1 = (TTree*)f->Get("Events");
//t1->Print();
//TFile *f = TFile::Open("/media/maia/NO_LABEL/data.root");
//TTree *t1 = (TTree*)f->Get("Events");

/*const char* fileNames[4] = {"root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2011A_SingleMu_merged.root", "root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2011B_SingleMu_merged.root", "root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2012B_SingleMu_merged.root", "root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2012C_SingleMu_merged.root"};

const char* fileLabels[4] = {"Run2011A", "Run2011B", "Run2012B", "Run2012C"};
*/

const char* fileNames[1] = {"root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola_merged.root"};

const char* fileLabels[1] = {"drellYan"};

TFile *fout = nullptr;
if(applyCuts){
	fout = new TFile("my_histograms_cut.root", "RECREATE");
} else{
	fout = new TFile("my_histograms_precut.root", "RECREATE");
}

for (int fileIdx = 0; fileIdx < 1; fileIdx++){
    TString label = fileLabels[fileIdx];
    
    TChain *t1 = new TChain("Events");
    t1->Add(fileNames[fileIdx]);
    

    //.ls()
    t1->Print();


    //data collections and types
    //ULong64_t Events;	niama takova
    UInt_t nMuon;		//number of muons
    Int_t Muon_charge[1000];
    Int_t Muon_tightCharge[1000];
    Float_t Muon_pt[1000]; 
    Float_t Muon_ptErr[1000];
    Float_t Muon_eta[1000];
    Float_t Muon_phi[1000];
    Float_t Muon_mass[1000];
    Float_t Muon_dxy[1000]; 
    Float_t Muon_dz[1000];
    Float_t MET_pt;
    Float_t MET_phi;
    Float_t MET_sumEt;
    Float_t MET_significance;
    Float_t MET_covXX;
    Float_t MET_covXY;
    Float_t MET_covYY;
    Float_t CaloMET_pt;
    Float_t CaloMET_phi;
    Float_t CaloMET_sumEt;
    Float_t Muon_leadingPt = -1;
    Int_t nGenPart;
    Float_t GenPart_mass[5000];
    Float_t GenPart_pt[5000];
    Float_t GenPart_eta[5000];
    Float_t GenPart_phi[5000];
    Int_t GenPart_pdgId[5000];
    Int_t GenPart_status[5000];
    Int_t GenPart_statusFlags[5000];
    Int_t GenPart_genPartIdxMother[5000];
    Int_t GenPart_Id[5000];
    Int_t GenPart_parpdgId[5000];
    Float_t Muon_pfRelIso03_all[5000];
    Float_t Muon_pfRelIso04_all[5000];
      
    ///////////////////////////////////////////////////////////////////////////
    //Branches

    t1->SetBranchAddress("nMuon", &nMuon);	//number of muons
    t1->SetBranchAddress("Muon_charge", &Muon_charge);  //muon charge
    t1->SetBranchAddress("Muon_tightCharge", &Muon_tightCharge);  //global and local muon
    t1->SetBranchAddress("Muon_pt", &Muon_pt); //transverse momentum of muons
    t1->SetBranchAddress("Muon_ptErr", &Muon_ptErr); //error in pt measurement
    t1->SetBranchAddress("Muon_eta", &Muon_eta); //deflection angle relative to beam axis
    t1->SetBranchAddress("Muon_phi", &Muon_phi); //azimuthal angle of muon trajectory - horizontal compass direction 
    t1->SetBranchAddress("Muon_mass", &Muon_mass); // mass of muons
    t1->SetBranchAddress("Muon_dxy", &Muon_dxy);	//dxy - otklonenie spriamo interaction point v ravninata XY
    t1->SetBranchAddress("Muon_dz", &Muon_dz);
    t1->SetBranchAddress("MET_pt", &MET_pt); //transverse momentum of missing energy transfers
    t1->SetBranchAddress("MET_phi", &MET_phi); //azimuthal angle of MET
    t1->SetBranchAddress("MET_sumEt", &MET_sumEt); //scalar sum of transverse energy of METs
    t1->SetBranchAddress("MET_significance", &MET_significance); //distinguishes between errors and actual MET
    t1->SetBranchAddress("MET_covXX", &MET_covXX); //xx-component variance of MET covariance matrix
    t1->SetBranchAddress("MET_covXY", &MET_covXY); //xy-component variance of MET covariance matrix
    t1->SetBranchAddress("MET_covYY", &MET_covYY); //yy-component variance of MET covariance matrix
    t1->SetBranchAddress("CaloMET_pt", &CaloMET_pt); //transverse momentum of MET caught in calorimeter
    t1->SetBranchAddress("CaloMET_phi", &CaloMET_phi); //azimuthal angle of MET caught in calorimeter
    t1->SetBranchAddress("CaloMET_sumEt", &CaloMET_sumEt); //scalar sum of transverse energy of met
    //t1->SetBranchAddress("HLT_DoubleMu3_Jpsi", &HLT_DoubleMu3_Jpsi);
    t1->SetBranchAddress("nGenPart", &nGenPart);
    t1->SetBranchAddress("GenPart_pt", &GenPart_pt);
    t1->SetBranchAddress("GenPart_eta", &GenPart_eta);
    t1->SetBranchAddress("GenPart_phi", &GenPart_phi);
    t1->SetBranchAddress("GenPart_mass", &GenPart_mass);
    t1->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId);
    t1->SetBranchAddress("GenPart_status", &GenPart_status);
    t1->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags);
    t1->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother);
    t1->SetBranchAddress("GenPart_Id", &GenPart_Id);
    t1->SetBranchAddress("GenPart_parpdgId", &GenPart_parpdgId);
    t1->SetBranchAddress("Muon_pfRelIso03_all", &Muon_pfRelIso03_all);
    t1->SetBranchAddress("Muon_pfRelIso04_all", &Muon_pfRelIso04_all);
    
    ///////////////////////////////////////////////////////////////////
    //Histograms definitions
    
    /////////muons//////////////////////
      TH1F *hnMuon = new TH1F("hnMuon", "hnMuon", 50, 0.5, 50.5);
      TH1F *hMuon_charge = new TH1F("hMuon_charge", "hMuon_charge", 3, -1.5, 1.5);
      TH1F *hMuon_tightCharge = new TH1F("hMuon_tightCharge", "hMuon_tightCharge", 5, -1., 4);
      TH1F *hMuon_ptErr = new TH1F("hMuon_ptErr", "hMuon_ptErr", 20, 0., 2.);
      TH1F *hMuon_etaAll = new TH1F("hMuon_etaAll", "hMuon_etaAll", 200, -100., 100.);
      TH1F *hMuon_phi = new TH1F("hMuon_phi", "#varphi of #mu", 100, -5., 5.);
      TH1F *hMuon_mass = new TH1F("hMuon_mass", "hMuon_mass", 40, -2., 2.);
      TH1F *hMuon_dxy = new TH1F("hMuon_dxy", "Muon dxy", 2, -0.1, 0.1);
      TH1F *hMuon_dxyAll = new TH1F("hMuon_dxyAll", "dxy of all muons", 200, -100., 100.);
      TH1F *hMuon_dz = new TH1F("hMuon_dz", "dz of all muons", 200, -100., 100.);
    
    /////////MET///////////////////////// 
      TH1F *hMET_pt = new TH1F("hMET_pt","MET p_{t}", 1000, 0., 100.);
      TH1F *hMET_phi = new TH1F("hMET_phi", "MET #varphi", 50, -5., 5.);
      TH1F *hMET_sumEt = new TH1F("hMET_sumEt", "CaloMET scalar sum of transverse mass", 10000, 0., 1000.);
      TH1F *hMET_significance = new TH1F("hMET_significance", "MET significance", 100, 0., 25.);
      TH1F *hMET_covXX = new TH1F("hMET_covXX", "MET covariance XX", 100, -0., 50.);
      TH1F *hMET_covXY = new TH1F("hMET_covXY", "MET covariance XY", 400, -20., 20.);
      TH1F *hMET_covYY = new TH1F("hMET_covYY", "MET covariance YY", 500, -0., 50.);
      
      TH2F *hMET_significanceVMET_phi = new TH2F ("hMET_significanceVMET_phi", "#varphi(MET) vs MET significance", 100, 0., 25., 50, -5., 5.);
      hMET_significanceVMET_phi->SetYTitle("#varphi(MET) rad");
      hMET_significanceVMET_phi->SetXTitle("MET significance");
      
    ////////CaloMET//////////////////////////////////
      TH1F *hCaloMET_pt = new TH1F("hCaloMET_pt", "CaloMET p_{t}", 250, 0., 50.);
      TH1F *hCaloMET_phi = new TH1F("hCaloMET_phi", "CaloMET #varphi", 50, -5., 5.);
      TH1F *hCaloMET_sumEt = new TH1F("hCaloMET_sumEt", "CaloMET scalar sum of transverse mass", 250, 5., 55.);
      
    ////////analysis/////////////////////////////////
      TH1F *hMuon_leadingPt = new TH1F("hMuon_leadingPt", "leading p_{t}", 200, 0., 200.);
      TH1F *hMuon_deltaPhi = new TH1F ("hMuon_deltaPhi", "#Delta#varphi(#mu#mu)", 130, -6.5, 6.5);
      
      TH2F *hMuon_phiVMuon_eta = new TH2F ("hMuon_phiVMuon_eta", "#eta(#mu) vs #phi(#mu)", 50, -5., 5., 50, -5., 5.);
      hMuon_phiVMuon_eta->SetYTitle("#eta(#mu) rad");
      hMuon_phiVMuon_eta->SetXTitle("#phi(#mu) rad");
      
      TH2F *hMuon_ptVMuon_etaPlus = new TH2F ("hMuon_ptVMuon_etaPlus", "#eta(#mu_{+}) vs p_{t}(#mu_{+})", 100, 0., 100., 100, -5., 5.);
      hMuon_ptVMuon_etaPlus->SetYTitle("#eta(#mu_{+}) rad");
      hMuon_ptVMuon_etaPlus->SetXTitle("p_{t}(#mu_{+}) GeV/c");
      
      TH2F *hMuon_ptVMuon_etaMinus = new TH2F ("hMuon_ptVMuon_etaMinus", "#eta(#mu_{-}) vs p_{t}(#mu_{-})", 100, 0., 100., 100, -5., 5.);
      hMuon_ptVMuon_etaMinus->SetYTitle("#eta(#mu_{-}) rad");
      hMuon_ptVMuon_etaMinus->SetXTitle("p_{t}(#mu_{-}) GeV/c");
      
      TH2F *hnMuonVMuon_leadingPt = new TH2F("hnMuonVMuon_leadingPt", "leading p_{t} vs number of muons", 10, -0.5, 9.5, 150, 0., 150.);
      hnMuonVMuon_leadingPt->SetYTitle("leading p_{t} GeV/c");
      hnMuonVMuon_leadingPt->SetXTitle("number of muons");
      
      TH2F *hDimuon_massVMuon_dxy = new TH2F ("hDimuon_massVMuon_dxy", "dxy(#mu) vs dimuon mass", 300, 0., 150., 80, -4., 4.);
      hDimuon_massVMuon_dxy->SetYTitle("dxy(#mu) m");
      hDimuon_massVMuon_dxy->SetXTitle("dimuon mass GeV/c^{2}");
      
      TH2F *hMuon_deltaPhiVDimuon_mass = new TH2F ("Muon_deltaPhiVDimuon_mass", "dimuon mass vs #Delta#varphi(#mu#mu)", 130, -6.5, 6.5, 150, 0., 150.);
      hMuon_deltaPhiVDimuon_mass->SetYTitle("dimuon mass GeV/c^{2}");
      hMuon_deltaPhiVDimuon_mass->SetXTitle("#Delta#varphi(#mu#mu) rad");
      
      TH1F *hDimuon_pt = new TH1F ("hDimuon_pt", "Dimuon p_{t}", 300, 0., 300.);
      TH1F *hDimuon_pz = new TH1F ("hDimuon_pz", "Dimuon p_{z}", 600, -300., 300.);
      
      TH2F *hDimuon_ptVDimuon_mass = new TH2F("hDimuon_ptVDimuon_mass", "dimuon mass vs dimuon p_{t}", 200, 0., 200., 300, 0., 150.);
      hDimuon_ptVDimuon_mass->SetYTitle("dimuon mass GeV/c^{2}");
      hDimuon_ptVDimuon_mass->SetXTitle("p_{t} of dimuon event GeV/c");
      

      TH2F *hDimuon_pzVDimuon_mass = new TH2F("hDimuon_pzVDimuon_mass", "dimuon mass vs dimuon p_{z}", 400, -200., 200., 300, 0., 150.);
      hDimuon_pzVDimuon_mass->SetYTitle("dimuon mass GeV/c^{2}");
      hDimuon_pzVDimuon_mass->SetXTitle("p_{z} of dimuon event GeV/c");
      

      //////////final(what's in google doc)///////////
      TH1F *hDimuon_mass = new TH1F ("hDimuon_mass", "dimuon mass", 300, 0., 150.);
      TH1F *hDimuon_transverseMass = new TH1F("hDimuon_transverseMass", "transverse mass of dimuon event", 100, 0., 100.);
      TH1F *hMuon_pt = new TH1F("hMuon_pt", "p_{t} of all muons", 100, 0., 100.);
      
      TH2F *hMuon_leadingPtVDimuon_mass = new TH2F("hMuon_leadingPtVDimuon_mass", "leading p_{t} vs mass of dimuon event", 150, 0., 150., 200, 0., 200.);
      hMuon_leadingPtVDimuon_mass->SetYTitle("leading p_{t} /GeV/c");
      hMuon_leadingPtVDimuon_mass->SetXTitle("mass of mother particle /GeV/c^{2}");
      
      TH1F *hDimuon_phi = new TH1F ("hDimuon_phi", "#varphi of dimuon event", 130, -6.5, 6.5);
      TH1F *hDimuon_cosDeltaPhi = new TH1F("hDimuon_cosDeltaPhi", "cos(#Delta#varphi) of dimuon event", 20, -1., 1.);
      
      TH2F *hDimuon_cosDeltaPhiVDimuon_mass = new TH2F ("hDimuon_cosDeltaPhiVDimuon_mass", "cos (#Delta#varphi) vs mass of dimuon event", 300., 0., 150., 20, -1., 1.);
      hDimuon_cosDeltaPhiVDimuon_mass->SetYTitle("cos(#Delta#varphi)");
      hDimuon_cosDeltaPhiVDimuon_mass->SetXTitle("mass of dimuon event, Gev/c^{2}");
      
      TH1F *hMuon_eta = new TH1F("hMuon_eta", "#eta of all muon events", 50, -2.5, 2.5);
      TH1F *hDimuon_eta = new TH1F ("hDimuon_eta", "#eta(#mu#mu)", 80, -4., 4.);
      TH1F *hDimuon_deltaEta = new TH1F ("hDimuon_deltaEta", "#Delta#eta of dimuon event", 80, -4, 4);
      
      TH2F *hDimuon_etaPlusVetaMinus = new TH2F ("hDimuon_etaPlusVetaMinus", "#eta of #mu_{-} vs #eta of #mu_{+}", 50, -2.5, 2.5, 50, -2.5, 2.5);
      hDimuon_etaPlusVetaMinus->SetYTitle("#eta of #mu_{-}");
      hDimuon_etaPlusVetaMinus->SetYTitle("#eta of #mu_{+}");
      
      TH1F *hMuon_iso3 = new TH1F("hMuon_iso3", "isolation using particle flow - 03", 100, 0., 10.);
      TH1F *hMuon_iso4 = new TH1F("hMuon_iso4", "isolation using particle flow - 04", 100, 0., 10.);
      
      TH2F *hMuon_iso3VDimuon_mass = new TH2F("hMuon_iso3VDimuon_mass", "mass of dimuon event vs iso-3", 100, 0., 10., 300, 0., 150.);
      hMuon_iso3VDimuon_mass->SetYTitle("mass of dimuon pair, GeV/c^{2}");
      hMuon_iso3VDimuon_mass->SetXTitle("isolation of pf-3");
      
      TH2F *hMuon_iso4VDimuon_mass = new TH2F("hMuon_iso4VDimuon_mass", "mass of dimuon event vs iso-4", 100, 0., 10., 300, 0., 150.);
      hMuon_iso4VDimuon_mass->SetYTitle("mass of dimuon pair, GeV/c^{2}");
      hMuon_iso4VDimuon_mass->SetXTitle("isolation of pf 4");
      
      TH2F *hMuon_ptVMuon_eta = new TH2F ("hMuon_ptVMuon_eta", "p_{t} against #eta of all #mu events (between 60 and 120 GeV/c^{2})", 50, -2.5, 2.5, 200, 0., 200.);
      hMuon_ptVMuon_eta->SetXTitle("#eta");
      hMuon_ptVMuon_eta->SetYTitle("p_{t} / GeV/c");
      
      TH1F *hDimuon_rapidity = new TH1F("hDimuon_rapidity", "rapidity of dimuon event", 60, -3., 3.);
      
      TH2F *hMET_ptVDimuon_transverseMass = new TH2F("hMET_ptVDimuon_transverseMass", "transverse mass of dimuon event vs pt of MET", 20, 0., 100., 20, 0., 100.);
      hMET_ptVDimuon_transverseMass->SetYTitle("transverse mass of dimuon event, GeV/c^{2}");
      hMET_ptVDimuon_transverseMass->SetXTitle("p_{t} of missing energy transfer, GeV/c");
      
      TH2F *hMET_ptVDimuon_mass = new TH2F("hMET_ptVDimuon_mass", "dimuon mass vs p_{t} of MET", 20, 0., 100., 20, 0., 100.);
      hMET_ptVDimuon_mass->SetYTitle("dimuon mass, GeV/c^{2}");
      hMET_ptVDimuon_mass->SetXTitle("p_{t} of MET, GeV/c");
      
      ////////////////////////////////////////////////////////////////////////////////////////
      TH1F *hnGenPart = new TH1F ("hnGenPart", "number of gen particles in drell yan sim", 100, 0., 100.);
      TH1F *hGenPart_mass = new TH1F ("hGenPart_mass", "mass of gen particles in GeV/c^{2}", 500., 0., 500.);
      TH1F *hGenPart_pt = new TH1F ("hGenPart_pt", "gen particles p_{t}", 200., 0., 200.);
      TH1F *hGenPart_phi = new TH1F ("hGenPart_phi", "#varphi of gen particles", 130, -6.5, 6.5);
      TH1F *hGenPart_eta = new TH1F ("hGenPart_eta", "#eta of gen particle events", 50, -2.5, 2.5);
      TH1F *hGenPart_ZMass = new TH1F("hGenPart_ZMass", "mass of gen particles with id = 23 and flag isLastCopy", 300, 0., 150.);
      TH1F *hGenPart_dimuonMass = new TH1F("hGenPart_dimuonMass", "mass of dimuon event of gen particles with id = 13 and id = -13 and flag isLastCopy", 300, 0., 150.);
      TH1F *hGenPart_muMomPdgId = new TH1F("hGenPart_muMomPdgId", "pdgId of muon mother particle - gen level", 3000, 0., 3000.);
    ////////////////////////////////////////////////////////////////  
      // After creating all histograms, put them in a vector
      std::vector<TH1*> histos = {
          hnMuon, hMuon_charge, hMuon_tightCharge,
          hMuon_pt, hMuon_ptErr, hMuon_eta, hMuon_etaAll,
          hMuon_phi, hMuon_mass, hMuon_dxy, hMuon_dxyAll, hMuon_dz,
          hMET_pt, hMET_phi, hMET_sumEt, hMET_significance,
          hMET_covXX, hMET_covXY, hMET_covYY,
          hCaloMET_pt, hCaloMET_phi, hCaloMET_sumEt,
          hMuon_leadingPt, hnMuonVMuon_leadingPt,
          hDimuon_eta, hMuon_deltaPhi, hMuon_phiVMuon_eta,
          hMuon_ptVMuon_etaPlus, hMuon_ptVMuon_etaMinus,
          hDimuon_mass, hDimuon_massVMuon_dxy,
          hMET_significanceVMET_phi, hMuon_deltaPhiVDimuon_mass,
          hDimuon_pt, hDimuon_pz, hDimuon_ptVDimuon_mass,
          hDimuon_pzVDimuon_mass,
          hDimuon_transverseMass, hMuon_leadingPtVDimuon_mass, 
          hDimuon_phi, hDimuon_cosDeltaPhiVDimuon_mass, hDimuon_deltaEta, 
          hDimuon_etaPlusVetaMinus, hnGenPart, hGenPart_mass,
          hGenPart_pt, hGenPart_phi, hGenPart_eta, hMuon_iso3, 
          hMuon_iso4, hMuon_ptVMuon_eta, hDimuon_cosDeltaPhi, 
          hMuon_iso3VDimuon_mass, hMuon_iso4VDimuon_mass, 
          hDimuon_rapidity, hMET_ptVDimuon_transverseMass, 
          hGenPart_ZMass, hGenPart_dimuonMass, hGenPart_muMomPdgId,
          hMET_ptVDimuon_mass
	            
      };

  
        for (auto* h : histos) h->SetDirectory(0);
    
    //////////////////////////////////////////////////////////////////
    //Tcanvaces

    //////////////////////////////////////////////////////////////////////
    Int_t nentries = (Int_t)t1->GetEntries();
    cout << "Number of events in the file: " << nentries << endl;
    
      
     //for (int i = 0; i< nentries; i++){
  
      for (int i = 0; i<100000; i++){
      
      t1->GetEntry(i);
      bool isZpeak = false;
      
      
      // cout << "before hlt" << endl;

     /* if(!HLT_DoubleMu3_Jpsi){
      continue;
      }
      
     
     if(!HLT_IsoMu20_eta2p1){
     continue;
     }
     */
     
     // cout << "after hlt" << "\t" << i << endl;
      
      if (nMuon > 0){
        Muon_leadingPt = Muon_pt[0];
        for (UInt_t mu = 1; mu < nMuon; mu++){
          if (Muon_pt[mu] > Muon_leadingPt){
            Muon_leadingPt = Muon_pt[mu];  
          }
        }      
        hMuon_leadingPt->Fill(Muon_leadingPt);
        hnMuonVMuon_leadingPt->Fill(nMuon, Muon_leadingPt);
      }
      
      //////////////////////////////////////////////////////////////////////////////////////////////////
        if(nMuon == 2 && Muon_charge[0] * Muon_charge[1] == -1){
           
           double Muon_deltaPhi, etaPlus, etaMinus, Dimuon_deltaEta;        
           
           
           if (Muon_charge[0] < 0){
              Muon_deltaPhi = Muon_phi[0] - Muon_phi[1];
              Dimuon_deltaEta = Muon_eta[0] - Muon_eta[1];
              etaMinus = Muon_eta[0];
              etaPlus = Muon_eta[1];
           } else {
              Muon_deltaPhi = Muon_phi[1] - Muon_phi[0];
              Dimuon_deltaEta = Muon_eta[1] - Muon_eta[0];
              etaPlus = Muon_eta[0];
              etaMinus = Muon_eta[1];    
          }
           
           /////////////////////////////////
           
           double cosDeltaPhi = TMath::Cos(Muon_deltaPhi);
           hDimuon_cosDeltaPhi->Fill(cosDeltaPhi);           
           TLorentzVector mu1, mu2, dimuon;
           mu1.SetPtEtaPhiM(Muon_pt[0], Muon_eta[0], Muon_phi[0], Muon_mass[0]);
           mu2.SetPtEtaPhiM(Muon_pt[1], Muon_eta[1], Muon_phi[1], Muon_mass[1]);
           dimuon = mu1 + mu2;
           
           double dimuon_pt = dimuon.Pt();
           double dimuon_pz = dimuon.Pz();
           double dimuon_mt = TMath::Sqrt(2.0*Muon_pt[0]*Muon_pt[1]*(1-TMath::Cos(Muon_deltaPhi)));
           double dimuon_rapidity = dimuon.Rapidity();
           
           if(applyCuts){
           	const double ptCut = 30.0;
	        const double etaMax = 2.1;
	        const double isoCut = 0.1;
	        const double dxy = 0.1;
	        const double dz = 15;
		const double met_pt = 35;
		
                if (Muon_pt[0] <= ptCut || Muon_pt[1] <= ptCut) continue;
           
                if (fabs(Muon_eta[0]) >= etaMax || fabs(Muon_eta[1]) >= etaMax) continue;
           
                if (Muon_pfRelIso04_all[0] > isoCut || Muon_pfRelIso04_all[1] > isoCut) continue;
           
                if (fabs(Muon_dxy[0]) >= dxy || fabs(Muon_dxy[1]) >= dxy) continue;
           
                if (fabs(Muon_dz[0]) >= dz || fabs(Muon_dz[1]) >= dz) continue;
           
                if (cosDeltaPhi >= -0.2 && cosDeltaPhi <= 0.9) continue; 
                
                if (MET_pt >= met_pt) continue;
           }
             
           
           hMuon_deltaPhi->Fill(Muon_deltaPhi);
           hMuon_phiVMuon_eta->Fill(Muon_phi[0], Muon_eta[0]);
           hMuon_phiVMuon_eta->Fill(Muon_phi[1], Muon_eta[1]);
           hDimuon_eta->Fill(Muon_eta[0]);
           hDimuon_eta->Fill(Muon_eta[1]);
           hDimuon_deltaEta->Fill(Dimuon_deltaEta);
           hDimuon_transverseMass->Fill(dimuon_mt);
           hDimuon_mass->Fill(dimuon.M());
           hDimuon_massVMuon_dxy->Fill(dimuon.M(), Muon_dxy[0]);
           hDimuon_massVMuon_dxy->Fill(dimuon.M(), Muon_dxy[1]);
           hMuon_deltaPhiVDimuon_mass->Fill(Muon_deltaPhi, dimuon.M());
           hDimuon_pt->Fill(dimuon.Pt());
           hDimuon_pz->Fill(dimuon.Pz());
           hDimuon_ptVDimuon_mass->Fill(dimuon.Pt(), dimuon.M());
           hDimuon_pzVDimuon_mass->Fill(dimuon.Pz(), dimuon.M());
           hDimuon_phi->Fill(dimuon.Phi());
           hDimuon_cosDeltaPhiVDimuon_mass->Fill(dimuon.M(), cosDeltaPhi);
           hMuon_leadingPtVDimuon_mass->Fill(dimuon.M(), Muon_leadingPt);
           
           hMuon_iso3VDimuon_mass->Fill(Muon_pfRelIso03_all[0], dimuon.M());
           hMuon_iso3VDimuon_mass->Fill(Muon_pfRelIso03_all[1], dimuon.M());

           hMuon_iso4VDimuon_mass->Fill(Muon_pfRelIso04_all[0], dimuon.M());
           hMuon_iso4VDimuon_mass->Fill(Muon_pfRelIso04_all[1], dimuon.M());
           hDimuon_rapidity->Fill(dimuon_rapidity);
           hMET_ptVDimuon_transverseMass->Fill(MET_pt, dimuon_mt);
           hMET_ptVDimuon_mass->Fill(MET_pt, dimuon.M());
           
           if (dimuon.M() > 60. && dimuon.M() < 120.){
              isZpeak = true;
              hDimuon_etaPlusVetaMinus->Fill(etaPlus, etaMinus);
           }
           
           
           if (Muon_charge[0] > 0){
              hMuon_ptVMuon_etaPlus->Fill(Muon_pt[0], Muon_eta[0]);
              hMuon_ptVMuon_etaMinus->Fill(Muon_pt[1], Muon_eta[1]);
          }
           if (Muon_charge[0] < 0){
              hMuon_ptVMuon_etaMinus->Fill(Muon_pt[0], Muon_eta[0]);
              hMuon_ptVMuon_etaPlus->Fill(Muon_pt[1], Muon_eta[1]);   
          }
        }

      
      hnMuon->Fill(nMuon);
      hMET_pt->Fill(MET_pt);
      hMET_phi->Fill(MET_phi);
      hMET_sumEt->Fill(MET_sumEt);
      hMET_significance->Fill(MET_significance);
      hMET_covXX->Fill(MET_covXX);
      hMET_covXY->Fill(MET_covXY);
      hMET_covYY->Fill(MET_covYY);
      hCaloMET_pt->Fill(CaloMET_pt);
      hCaloMET_phi->Fill(CaloMET_phi);
      hCaloMET_sumEt->Fill(CaloMET_sumEt);
      hMET_significanceVMET_phi->Fill(MET_significance, MET_phi);
      hnGenPart->Fill(nGenPart);
   
      
    //  cout << i << ": number of muons = " << nMuon << endl;
    
      for(UInt_t mu = 0; mu < nMuon; mu++){
  
       
        hMuon_charge->Fill(Muon_charge[mu]);
        hMuon_tightCharge->Fill(Muon_tightCharge[mu]);
        hMuon_pt->Fill(Muon_pt[mu]);
        hMuon_ptErr->Fill(Muon_ptErr[mu]);
        hMuon_eta->Fill(Muon_eta[mu]);
        hMuon_etaAll->Fill(Muon_eta[mu]);
        hMuon_phi->Fill(Muon_phi[mu]);
        hMuon_mass->Fill(Muon_mass[mu]);
        hMuon_dxy->Fill(Muon_dxy[mu]);
        hMuon_dz->Fill(Muon_dz[mu]);
        hMuon_dxyAll->Fill(Muon_dxy[mu]);
        hMuon_iso3->Fill(Muon_pfRelIso03_all[mu]);
        hMuon_iso4->Fill(Muon_pfRelIso04_all[mu]);
        
        
        if (isZpeak){
              hMuon_ptVMuon_eta->Fill(Muon_eta[mu], Muon_pt[mu]);
        }
        
        }
        ///////////////////////////////////GEN ANALYSIS////////////////////////////////////////////////

        TLorentzVector genMuMinus, genMuPlus, genDimuon;
        double massDimuonGen = -99.;
        int momIdxMinus = -99;	//enumeration index in the event of the mother particle of mu-
        int momIdxPlus = -99;  //enumeration index in the event of the mother particle of mu+
        int momPdgIdMinus = -99;  //pdg id of the mother particle of mu-
        int momPdgIdPlus = -99;  //pdg id of the mother particle of mu+

        for (Int_t gp = 0; gp < nGenPart; gp++){
           hGenPart_mass->Fill(GenPart_mass[gp]);	//mass of any generated particle
           hGenPart_phi->Fill(GenPart_phi[gp]);		// phi of any generated particle
           hGenPart_eta->Fill(GenPart_eta[gp]);		//eta of any generated particle
           hGenPart_pt->Fill(GenPart_pt[gp]);		//pt of any generated particle

           /////MASS DISTRIBUTION USING GEN PARTICLES//////////////////////

           if(GenPart_pdgId[gp] == 23 && GenPart_status[gp] == 2){
              hGenPart_ZMass->Fill(GenPart_mass[gp]);
           }

           if (GenPart_status[gp] == 3){
             hGenPart_muMomPdgId->Fill(GenPart_pdgId[GenPart_genPartIdxMother[gp]]);
           }

           if(GenPart_pdgId[gp] == 13 && GenPart_status[gp] == 3){
             genMuMinus.SetPtEtaPhiM(GenPart_pt[gp], GenPart_eta[gp], GenPart_phi[gp], GenPart_mass[gp]);
             momIdxMinus = GenPart_genPartIdxMother[gp];
             momPdgIdMinus = GenPart_pdgId[momIdxMinus];
           }

           if(GenPart_pdgId[gp] == -13 && GenPart_status[gp] == 3){
             genMuPlus.SetPtEtaPhiM(GenPart_pt[gp], GenPart_eta[gp], GenPart_phi[gp], GenPart_mass[gp]);
             momIdxPlus = GenPart_genPartIdxMother[gp];
             momPdgIdPlus = GenPart_pdgId[momIdxPlus];
           }
           
           genDimuon = genMuMinus + genMuPlus;
           if(momPdgIdMinus == 23 && momPdgIdPlus == 23){
             massDimuonGen = genDimuon.M();
             //cout << "massDimuonGen: " << massDimuonGen << endl;
             hGenPart_dimuonMass->Fill(massDimuonGen);
           }
         }
   }
      ///////////////////////////////////////////////
      //saving all info in file
       
        
        fout->mkdir(label + "/muHist");
        fout->mkdir(label + "/METHist");
        fout->mkdir(label + "/CaloMETHist");
        fout->mkdir(label + "/anaHist");
        fout->mkdir(label + "/finalHist");
        fout->mkdir(label + "/genHist");

        fout->cd(label + "/muHist");
        hnMuon->Write();
        hMuon_dxy->Write();
        hMuon_charge->Write();
        hMuon_tightCharge->Write();
        hMuon_ptErr->Write();
        hMuon_phi->Write();
        hMuon_mass->Write();
      
        fout->cd(label + "/METHist");
        hMET_pt->Write();
        hMET_phi->Write();
        hMET_sumEt->Write();
        hMET_significance->Write();
        hMET_covXX->Write();
        hMET_covXY->Write();
        hMET_covYY->Write();
        hMET_significanceVMET_phi->Write();
        
        fout->cd(label + "/CaloMETHist");
        hCaloMET_pt->Write();
        hCaloMET_phi->Write();
        hCaloMET_sumEt->Write();
        
        fout->cd(label + "/anaHist");
        hMuon_leadingPt->Write();
        hMuon_deltaPhi->Write();
        hMuon_phiVMuon_eta->Write();
        hMuon_ptVMuon_etaPlus->Write();
        hMuon_ptVMuon_etaMinus->Write();
        hnMuonVMuon_leadingPt->Write();
        hDimuon_massVMuon_dxy->Write();
        hDimuon_mass->Write();
        hMuon_deltaPhiVDimuon_mass->Write();
        hDimuon_pt->Write();
        hDimuon_pz->Write();
        hDimuon_ptVDimuon_mass->Write();
        hDimuon_pzVDimuon_mass->Write();
        hDimuon_transverseMass->Write();
        
        fout->cd(label + "/finalHist");
        hMuon_pt->Write();
        hMuon_leadingPtVDimuon_mass->Write();
        hDimuon_phi->Write();
        hDimuon_cosDeltaPhi->Write();
        hDimuon_cosDeltaPhiVDimuon_mass->Write();
        hDimuon_eta->Write();
        hMuon_eta->Write();
        hDimuon_deltaEta->Write();
        hDimuon_etaPlusVetaMinus->Write();
        hMuon_ptVMuon_eta->Write();
        hMuon_iso3->Write();
        hMuon_iso4->Write();
        hMuon_iso3VDimuon_mass->Write();
        hMuon_iso4VDimuon_mass->Write();
        hDimuon_rapidity->Write();
        hMET_ptVDimuon_transverseMass->Write();
        hMET_ptVDimuon_mass->Write();
        fout->cd(label + "/genHist");
        hnGenPart->Write();
        hGenPart_mass->Write();
        hGenPart_pt->Write();
        hGenPart_phi->Write();
        hGenPart_eta->Write();
        hGenPart_ZMass->Write();
        hGenPart_dimuonMass->Write();
        hGenPart_muMomPdgId->Write();
        ////////////////////////////////////////////////////////////////////
       /* Int_t bin1 = hMuon_deltaPhi->FindBin(2.0);
        Int_t bin2 = hMuon_deltaPhi->FindBin(4.0);
        
        double integral_inside = hMuon_deltaPhi->Integral(bin1, bin2);
        double integral_total = hMuon_deltaPhi->Integral(0, hMuon_deltaPhi->GetNbinsX() + 1);
        cout << "entries in interval [2, 4]: " << integral_inside << endl;
        cout << "entries along whole domain: " << integral_total << endl;
        cout << "percent cut off when restricting domain to [2, 4]: " << (1 - integral_inside/integral_total) * 100 << "%" << endl;
        */
        ////////////////////////////////////////////////////////////////////
        
        /*
        Int_t xBin1 = hMuon_leadingPtVDimuon_mass->GetXaxis()->FindBin(60.);
        Int_t xBin2 = hMuon_leadingPtVDimuon_mass->GetXaxis()->FindBin(120.);
        Int_t yBin1 = hMuon_leadingPtVDimuon_mass->GetYaxis()->FindBin(30.);
        Int_t yBin2 = hMuon_leadingPtVDimuon_mass->GetNbinsY();
        
        double integral_inside = hMuon_leadingPtVDimuon_mass->Integral(xBin1, xBin2, yBin1, yBin2);
        double integral_total = hMuon_leadingPtVDimuon_mass->Integral(0, hMuon_leadingPtVDimuon_mass->GetNbinsX() + 1, 0, hMuon_leadingPtVDimuon_mass->GetNbinsY() + 1);
        
        double percent_cut = (1. - integral_inside / integral_total) * 100;
        
        cout << "entries in total region of leading pt vs dimuon mass: " << integral_total << endl;
        cout << "entries when we restrict mass to between 60 to 120 GeV/c^2 and pt to above 30GeV/c " << integral_inside << endl;
        cout << "percent lost: " << percent_cut << "%" << endl;
        
        /////////////////////////////////////////////////////////
        Int_t xBins1 = hDimuon_cosDeltaPhiVDimuon_mass->GetXaxis()->FindBin(60.);
        Int_t xBins2 = hDimuon_cosDeltaPhiVDimuon_mass->GetXaxis()->FindBin(120.);
        
        double integral_full = hDimuon_cosDeltaPhiVDimuon_mass->Integral(0, hDimuon_cosDeltaPhiVDimuon_mass->GetNbinsX() + 1, 0, hDimuon_cosDeltaPhiVDimuon_mass->GetNbinsY() + 1);
        double cuts[3] = {-0.4, -0.6, -0.8};
        
        for(int c = 0; c < 3; c++){
            Int_t yBins1 = hDimuon_cosDeltaPhiVDimuon_mass->GetYaxis()->FindBin(-1.);
            Int_t yBins2 = hDimuon_cosDeltaPhiVDimuon_mass->GetYaxis()->FindBin(cuts[c]);
            
            double integral_partial = hDimuon_cosDeltaPhiVDimuon_mass->Integral(xBins1, xBins2, yBins1, yBins2);
            double percent_cutOff = (1. - integral_partial / integral_full) * 100;
            
            cout << "entries of cos(dphi) vs dimuon mass along full domain: " << integral_full << endl;
            cout << "entries when restricting mass to 60-120GeV/c^2 and cos(dphi) from (-1, " << cuts[c] << ") are:"<< integral_partial << endl;
            cout << "percent cut off: " << percent_cutOff << "%" << endl;
            
        }
        */
        /////////////////////////////////////////////////////////////////
        
        fout->cd("");
        for (auto* h : histos) delete h;
        delete t1;
        
    }
        
        
        ///////////////////////////////////////////////
        /*
        Int_t bin1 = hMuon_dxyAll->FindBin(-4.0);
        Int_t bin2 = hMuon_dxyAll->FindBin(4.0);
        
        double integral_inside1 = hMuon_dxyAll->Integral(bin1, bin2);
        double integral_total1 = hMuon_dxyAll->Integral(0, hMuon_dxyAll->GetNbinsX() + 1);
        
        cout << "entries in interval [-4, 4]: " << integral_inside1 << endl;
        cout << "entries in [-50, 50], regarded as full domain: " << integral_total1 << endl;
        cout << "percent cut off when restricting domain to [-4, 4]: " << (1 - integral_inside1/integral_total1) * 100 << "%" << endl;
          
        
        //////////////////////////////////////////////
        Int_t bin1_1 = hMuon_etaAll->FindBin(-3.4);
        Int_t bin2_1 = hMuon_etaAll->FindBin(3.4);
        
        double integral_inside2= hMuon_etaAll->Integral(bin1_1, bin2_1);
        double integral_total2 = hMuon_etaAll->Integral(0, hMuon_etaAll->GetNbinsX() + 1);
        
        cout << "entries in interval [-3.4, 3.4]: " << integral_inside2 << endl;
        cout << "entries in interval [-100, 100], regarded as full domain: " << integral_total2 << endl;
        cout << "percent cut off when restricting domain: " << (1 - integral_inside2/integral_total2) * 100 << "%" << endl;
        
        */
        

        fout->Write();
        fout->Close(); 
        
    }
