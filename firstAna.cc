#include <algorithm>
#include <functional>


void firstAna(){
//TFile *f = TFile::Open("root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/Run2011A_SingleMu/94000E51-36DE-4AE5-939B-12EE231D9755.root");
TFile *f = TFile::Open("script.root");

TTree *t1 = (TTree*)f->Get("Events");

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
///////////////////////////////////////////////////////////////////////////
//Branches
TFile *fout = new TFile("my_histograms.root", "RECREATE");

t1->SetBranchAddress("nMuon", &nMuon);	//number of muons
t1->SetBranchAddress("Muon_charge", &Muon_charge);  //muon charge
t1->SetBranchAddress("Muon_tightCharge", &Muon_tightCharge);  //global and local muon
t1->SetBranchAddress("Muon_pt", &Muon_pt); //transverse momentum of muons
t1->SetBranchAddress("Muon_ptErr", &Muon_ptErr); //error in pt measurement
t1->SetBranchAddress("Muon_eta", &Muon_eta); //deflection angle relative to beam axis
t1->SetBranchAddress("Muon_phi", &Muon_phi); //azimuthal angle of muon trajectory - horizontal compass direction 
t1->SetBranchAddress("Muon_mass", &Muon_mass); // mass of muons
t1->SetBranchAddress("Muon_dxy", &Muon_dxy);	//dxy - otklonenie spriamo interaction point v ravninata XY
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
///////////////////////////////////////////////////////////////////
//Histograms definitions
  TH1F *hnMuon = new TH1F("hnMuon", "hnMuon", 50, 0.5, 50.5);
  TH1F *hMuon_charge = new TH1F("hMuon_charge", "hMuon_charge", 3, -1.5, 1.5);
  TH1F *hMuon_tightCharge = new TH1F("hMuon_tightCharge", "hMuon_tightCharge", 5, -1., 4);
  TH1F *hMuon_pt = new TH1F("hMuon_pt", "hMuon_pt", 100, 0., 100.);
  TH1F *hMuon_ptErr = new TH1F("hMuon_ptErr", "hMuon_ptErr", 200, 0., 2.);
  
  TH1F *hMuon_eta = new TH1F("hMuon_eta", "hMuon_eta", 50, -3.4, 3.4);
  TH1F *hMuon_etaAll = new TH1F("hMuon_etaAll", "hMuon_etaAll", 1000, -100., 100.);
  
  TH1F *hMuon_phi = new TH1F("hMuon_phi", "hMuon_phi", 50, -5., 5.);
  TH1F *hMuon_mass = new TH1F("hMuon_mass", "hMuon_mass", 100, -2., 2.);
  
  TH1F *hMuon_dxy = new TH1F("hMuon_dxy", "hMuon_dxy", 100, -4., 4.);
  TH1F *hMuon_dxyAll = new TH1F("hMuon_dxyAll", "hMuon_dxyAll", 1000, -100., 100.);
  
  TH1F *hMET_pt = new TH1F("hMET_pt","hMET_pt", 1000, 0., 100.);
  TH1F *hMET_phi = new TH1F("hMET_phi", "hMET_phi", 50, -5., 5.);
  TH1F *hMET_sumEt = new TH1F("hMET_sumEt", "hMET_sumEt", 10000, 0., 1000.);
  TH1F *hMET_significance = new TH1F("hMET_significance", "hMET_significance", 100, 0., 25.);
  TH1F *hMET_covXX = new TH1F("hMET_covXX", "hMET_covXX", 100, -0., 50.);
  TH1F *hMET_covXY = new TH1F("hMET_covXY", "hMET_covXY", 400, -20., 20.);
  TH1F *hMET_covYY = new TH1F("hMET_covYY", "hMET_covYY", 500, -0., 50.);
  TH1F *hCaloMET_pt = new TH1F("hCaloMET_pt", "hCaloMET_pt", 250, 0., 50.);
  TH1F *hCaloMET_phi = new TH1F("hCaloMET_phi", "hCaloMET_phi", 50, -5., 5.);
  TH1F *hCaloMET_sumEt = new TH1F("hCaloMET_sumEt", "hCaloMET_sumEt", 250, 5., 55.);
  TH1F *hMuon_leadingPt = new TH1F("hMuon_leadingPt", "hMuon_leadingPt", 100, 0., 200.);
  TH2F *hnMuonVMuon_leadingPt = new TH2F("hnMuonVMuon_leadingPt", "hnMuonVMuon_leadingPt", 10, -0.5, 9.5, 100, 0., 150.);
  TH1F *hMuon_eta1 = new TH1F ("hMuon_eta1", "hMuon_eta1", 50, -5., 5.);
  TH1F *hMuon_deltaPhi = new TH1F ("hMuon_deltaPhi", "hMuon_deltaPhi", 60, -6., 6.);
  TH2F *hMuon_phiVMuon_eta = new TH2F ("hMuon_phiVMuon_eta", "hMuon_phiVMuon_eta", 50, -5., 5., 50, -5., 5.);
  TH2F *hMuon_ptVMuon_etaPlus = new TH2F ("hMuon_ptVMuon_etaPlus", "hMuon_ptVMuon_etaPlus", 100, 0., 100., 50, -5., 5.);
  TH2F *hMuon_ptVMuon_etaMinus = new TH2F ("hMuon_ptVMuon_etaMinus", "hMuon_ptVMuon_etaMinus", 100, 0., 100., 50, -5., 5.);
  TH1F *hDimuon_mass = new TH1F ("hDimuon_mass", "hDimuon_mass", 300, 0., 150.);
  TH2F *hDimuon_massVMuon_dxy = new TH2F ("hDimuon_massVMuon_dxy", "hDimuon_massVMuon_dxy", 300, 0., 150., 100, -4., 4.);
  TH2F *hMET_significanceVMET_phi = new TH2F ("hMET_significanceVMET_phi", "hMET_significanceVMET_phi", 100, 0., 25., 50, -5., 5.);
  TH2F *hMuon_deltaPhiVDimuon_mass = new TH2F ("Muon_deltaPhiVDimuon_mass", "Muon_deltaPhiVDimuon_mass", 60, -6., 6., 300, 0., 150.);
  
  TH1F *hDimuon_pt = new TH1F ("hDimuon_pt", "hDimuon_pt", 1000, 0., 200.);
  TH1F *hDimuon_pz = new TH1F ("hDimuon_pz", "hDimuon_pz", 2000, -200., 200.);
  TH2F *hDimuon_ptVDimuon_mass = new TH2F("hDimuon_ptVDimuon_mass", "hDimuon_ptVDimuon_mass", 1000, 0., 200., 300, 0., 150.);
  TH2F *hDimuon_pzVDimuon_mass = new TH2F("hDimuon_pzVDimuon_mass", "hDimuon_pzVDimuon_mass", 2000, -200., 200., 300, 0., 150.);
////////////////////////////////////////////////////////////////  
//Tcanvaces
TCanvas cnMuon("cnMuon", "nMuon", 800, 600);
TCanvas cMuon_charge("cMuon_charge", "Muon Charge", 800, 600);
TCanvas cMuon_tightCharge("cMuon_tightCharge", "Muon Tight Charge", 800, 600);
TCanvas cMuon_pt("cMuon_pt", "Muon pt", 800, 600);
TCanvas cMuon_ptErr("cMuon_ptErr", "Muon pt error", 800, 600);
TCanvas cMuon_eta("cMuon_eta", "Muon eta", 800, 600);
TCanvas cMuon_phi("cMuon_phi", "Muon phi", 800, 600);
TCanvas cMuon_mass("cMuon_mass", "Muon mass", 800, 600);
TCanvas cMuon_dxy("cMuon_dxy", "Muon dxy", 800, 600);
TCanvas cMET_pt("cMET_pt", "MET pt", 800, 600);
TCanvas cMET_phi("cMET_phi", "MET phi", 800, 600);
TCanvas cMET_sumEt("cMET_sumEt", "MET sum Et", 800, 600);
TCanvas cMET_significance("cMET_significance", "MET significance", 800, 600);
TCanvas cMET_covXX("cMET_covXX", "MET covXX", 800, 600);
TCanvas cMET_covXY("cMET_covXY", "MET covXY", 800, 600);
TCanvas cMET_covYY("cMET_covYY", "MET covYY", 800, 600);
TCanvas cCaloMET_pt("cCaloMET_pt", "CaloMET pt", 800, 600);
TCanvas cCaloMET_phi("cCaloMET_phi", "CaloMET phi", 800, 600);
TCanvas cCaloMET_sumEt("cCaloMET_sumEt", "CaloMET sumEt", 800, 600);
TCanvas cMuon_leadingPt("cMuon_leadingPt", "Muon leading pt", 800, 600);
TCanvas cnMuonVMuon_leadingPt("cnMuonVMuon_leadingPt", "nMuon vs leading pt", 800, 600);
TCanvas cMuon_eta1("cMuon_eta1", "Muon Eta 1", 800, 600);
TCanvas cMuon_deltaPhi("cMuon_deltaPhi", "Muon delta phi", 800, 600);
TCanvas cMuon_phiVMuon_eta("cMuon_phiVMuon_eta", "Muon phi vs Muon eta", 800, 600);
TCanvas cMuon_ptVMuon_etaPlus("cMuon_ptVMuon_etaPlus", "Muon pt vs Muon eta Positive charge", 800, 600);
TCanvas cMuon_ptVMuon_etaMinus("cMuon_ptVMuon_etaMinus", "Muon pt vs Muon eta Negative charge", 800, 600);
TCanvas cDimuon_mass("cDimuon_mass", "Mass of a dimuon", 800, 600);
TCanvas cDimuon_massVMuon_dxy("cDimuon_massVMuon_dxy", "Dimuon mass vs Muon dxy", 800, 600);
TCanvas cMET_significanceVMET_phi("cMET_significanceVMET_phi", "MET significance vs MET phi", 800, 600);
TCanvas cMuon_deltaPhiVDimuon_mass("cMuon_deltaPhiVDimuon_mass", "Dimuon_deltaPhiVDimuon_mass", 800, 600);
TCanvas cDimuon_pt("cDimuon_pt", "Dimuon pt", 800, 600); //transverse momentum of dimuon - two muon events
TCanvas cDimuon_pz("cDimuon_pz", "Dimuon pz", 800, 600); // momentum along z axis
TCanvas cDimuon_ptVDimuon_mass("cDimuon_ptVDimuon_mass", "Dimuon pt vs Dimuon mass", 800, 600);
TCanvas cDimuon_pzVDimuon_mass("cDimuon_pzVDimuon_mass", "Dimuon pz vs Dimuon mass", 800, 600);

//////////////////////////////////////////////////////////////////////
Int_t nentries = (Int_t)t1->GetEntries();
cout << "Number of events in the file: " << nentries << endl;

for (int i =0; i<nentries; i++){
//for (int i =0; i<1000; i++){
  t1->GetEntry(i);
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
  
    if(nMuon == 2 && Muon_charge[0] * Muon_charge[1] == -1){
       double Muon_deltaPhi = Muon_phi[0] - Muon_phi[1];
       hMuon_eta1->Fill(Muon_eta[0]);
       hMuon_eta1->Fill(Muon_eta[1]);
       hMuon_deltaPhi->Fill(Muon_deltaPhi);
       hMuon_phiVMuon_eta->Fill(Muon_phi[0], Muon_eta[0]);
       hMuon_phiVMuon_eta->Fill(Muon_phi[1], Muon_eta[1]);
       /////////////////////////////////
       TLorentzVector mu1, mu2, dimuon;
       mu1.SetPtEtaPhiM(Muon_pt[0], Muon_eta[0], Muon_phi[0], Muon_mass[0]);
       mu2.SetPtEtaPhiM(Muon_pt[1], Muon_eta[1], Muon_phi[1], Muon_mass[1]);
       dimuon = mu1 + mu2;
       
       double dimuon_pt = dimuon.Pt();
       double dimuon_pz = dimuon.Pz();
       
       hDimuon_mass->Fill(dimuon.M());
       hDimuon_massVMuon_dxy->Fill(dimuon.M(), Muon_dxy[0]);
       hDimuon_massVMuon_dxy->Fill(dimuon.M(), Muon_dxy[1]);
       hMuon_deltaPhiVDimuon_mass->Fill(Muon_deltaPhi, dimuon.M());
       hDimuon_pt->Fill(dimuon.Pt());
       hDimuon_pz->Fill(dimuon.Pz());
       hDimuon_ptVDimuon_mass->Fill(dimuon.Pt(), dimuon.M());
       hDimuon_pzVDimuon_mass->Fill(dimuon.Pz(), dimuon.M());
       
       
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
//  cout << i << ": number of muons = " << nMuon << endl;
  for(UInt_t mu = 0; mu < nMuon; mu++){
//    cout << "in muon loop; mu = " << mu << "\ti = " << i << endl;
   
    hMuon_charge->Fill(Muon_charge[mu]);
    hMuon_tightCharge->Fill(Muon_tightCharge[mu]);
    hMuon_pt->Fill(Muon_pt[mu]);
    hMuon_ptErr->Fill(Muon_ptErr[mu]);
    hMuon_eta->Fill(Muon_eta[mu]);
    hMuon_etaAll->Fill(Muon_eta[mu]);
    hMuon_phi->Fill(Muon_phi[mu]);
    hMuon_mass->Fill(Muon_mass[mu]);
    hMuon_dxy->Fill(Muon_dxy[mu]);
    hMuon_dxyAll->Fill(Muon_dxy[mu]);
    
    
    }
}   
    /*
    cnMuon.cd();
    hnMuon->Draw();
    cnMuon.SaveAs("nMuon.png");
    cnMuon.SaveAs("nMuon.C");
    cnMuon.Close();
    
    cMuon_charge.cd();
    hMuon_charge->Draw();
    cMuon_charge.SaveAs("Muon_charge.png");
    cMuon_charge.SaveAs("Muon_charge.C");
    cMuon_charge.Close();
    
    cMuon_tightCharge.cd();
    hMuon_tightCharge->Draw();
    cMuon_tightCharge.SaveAs("Muon_tightCharge.png");
    cMuon_tightCharge.SaveAs("Muon_tightCharge.C");
    cMuon_tightCharge.Close();
    
    cMuon_pt.cd();
    hMuon_pt->Draw();
    cMuon_pt.SaveAs("Muon_pt.png");
    cMuon_pt.SaveAs("Muon_pt.C");
    cMuon_pt.Close();
    
    cMuon_ptErr.cd();
    hMuon_ptErr->Draw();
    cMuon_ptErr.SaveAs("Muon_ptErr.png");
    cMuon_ptErr.SaveAs("Muon_ptErr.C");
    cMuon_ptErr.Close();
    
    cMuon_eta.cd();
    hMuon_eta->Draw();
    cMuon_eta.SaveAs("Muon_eta.png");
    cMuon_eta.SaveAs("Muon_eta.C");
    cMuon_eta.Close();
    
    cMuon_phi.cd();
    hMuon_phi->Draw();
    cMuon_phi.SaveAs("Muon_phi.png");
    cMuon_phi.SaveAs("Muon_phi.C");
    cMuon_phi.Close();
    
    cMuon_mass.cd();
    hMuon_mass->Draw();
    cMuon_mass.SaveAs("Muon_mass.png");
    cMuon_mass.SaveAs("Muon_mass.C");
    cMuon_mass.Close();
    
    cMuon_dxy.cd();
    hMuon_dxy->Draw();
    cMuon_dxy.SaveAs("Muon_dxy.png");
    cMuon_dxy.SaveAs("Muon_dxy.C");
    cMuon_dxy.Close();
    
    cMET_pt.cd();
    hMET_pt->Draw();
    cMET_pt.SaveAs("MET_pt.png");
    cMET_pt.SaveAs("MET_pt.C");
    cMET_pt.Close();
    
    cMET_phi.cd();
    hMET_phi->Draw();
    cMET_phi.SaveAs("MET_phi.png");
    cMET_phi.SaveAs("MET_phi.C");
    cMET_phi.Close();
    
    cMET_sumEt.cd();
    hMET_sumEt->Draw();
    cMET_sumEt.SaveAs("MET_sumEt.png");
    cMET_sumEt.SaveAs("MET_sumEt.C");
    cMET_sumEt.Close();

    cMET_significance.cd();
    hMET_significance->Draw();
    cMET_significance.SaveAs("MET_significance.png");
    cMET_significance.SaveAs("MET_significance.C");
    cMET_significance.Close();
    
    cMET_covXX.cd();
    hMET_covXX->Draw();
    cMET_covXX.SaveAs("MET_covXX.png");
    cMET_covXX.SaveAs("MET_covXX.C");
    cMET_covXX.Close();
    
    cMET_covXY.cd();
    hMET_covXY->Draw();
    cMET_covXY.SaveAs("MET_covXY.png");
    cMET_covXY.SaveAs("MET_covXY.C");
    cMET_covXY.Close();
    
    cMET_covYY.cd();
    hMET_covYY->Draw();
    cMET_covYY.SaveAs("MET_covYY.png");
    cMET_covYY.SaveAs("MET_covYY.C");
    cMET_covYY.Close();
    
    cCaloMET_pt.cd();
    hCaloMET_pt->Draw();
    cCaloMET_pt.SaveAs("CaloMET_pt.png");
    cCaloMET_pt.SaveAs("CaloMET_pt.C");
    cCaloMET_pt.Close();
    
    cCaloMET_phi.cd();
    hCaloMET_phi->Draw();
    cCaloMET_phi.SaveAs("CaloMET_phi.png");
    cCaloMET_phi.SaveAs("CaloMET_phi.C");
    cCaloMET_phi.Close();
    
    cCaloMET_sumEt.cd();
    hCaloMET_sumEt->Draw();
    cCaloMET_sumEt.SaveAs("CaloMET_sumEt.png");
    cCaloMET_sumEt.SaveAs("CaloMET_sumEt.C");
    cCaloMET_sumEt.Close();
    
    cMuon_leadingPt.cd();
    hMuon_leadingPt->Draw();
    cMuon_leadingPt.SaveAs("Muon_leadingPt.png");
    cMuon_leadingPt.SaveAs("Muon_leadingPt.C");
    cMuon_leadingPt.Close();
    
    cnMuonVMuon_leadingPt.cd();
    hnMuonVMuon_leadingPt->Draw();
    cnMuonVMuon_leadingPt.SaveAs("nMuonVMuon_leadingPt.png");
    cnMuonVMuon_leadingPt.SaveAs("nMuonVMuon_leadingPt.C");
    cnMuonVMuon_leadingPt.Close(); 
    
    
    cMuon_eta1.cd();
    hMuon_eta1->Draw();
    cMuon_eta1.SaveAs("Muon_eta1.png");
    cMuon_eta1.SaveAs("Muon_eta1.C");
    cMuon_eta1.Close();
    
    cMuon_deltaPhi.cd();
    hMuon_deltaPhi->Draw();
    cMuon_deltaPhi.SaveAs("Muon_deltaPhi.png");
    cMuon_deltaPhi.SaveAs("Muon_deltaPhi.C");
    cMuon_deltaPhi.Close();
    
    cMuon_phiVMuon_eta.cd();
    hMuon_phiVMuon_eta->Draw();
    cMuon_phiVMuon_eta.SaveAs("Muon_phiVMuon_eta.png");
    cMuon_phiVMuon_eta.SaveAs("Muon_phiVMuon_eta.C");
    cMuon_phiVMuon_eta.Close();
      
    cMuon_ptVMuon_etaPlus.cd();
    hMuon_ptVMuon_etaPlus->Draw();
    cMuon_ptVMuon_etaPlus.SaveAs("Muon_ptVMuon_etaPlus.png");
    cMuon_ptVMuon_etaPlus.SaveAs("Muon_ptVMuon_etaPlus.C");
    cMuon_ptVMuon_etaPlus.Close();
    
    cMuon_ptVMuon_etaMinus.cd();
    hMuon_ptVMuon_etaMinus->Draw();
    cMuon_ptVMuon_etaMinus.SaveAs("Muon_ptVMuon_etaMinus.png");
    cMuon_ptVMuon_etaMinus.SaveAs("Muon_ptVMuon_etaMinus.C");
    cMuon_ptVMuon_etaMinus.Close(); 
    
    cDimuon_mass.cd();
    hDimuon_mass->Draw();
    cDimuon_mass.SaveAs("Dimuon_mass.png");
    cDimuon_mass.SaveAs("Dimuon_mass.C");
    cDimuon_mass.Close();
    
    cMuon_massVMuon_dxy.cd();
    hMuon_massVMuon_dxy->Draw();
    cMuon_massVMuon_dxy.SaveAs("Muon_massVMuon_dxy");
    cMuon_massVMuon_dxy.SaveAs("Muon_massVMuon_dxy");
    cMuon_massVMuon_dxy.Close();
    
    cMET_significanceVMET_phi.cd();
    hMET_significanceVMET_phi->Draw();
    cMET_significanceVMET_phi.SaveAs("MET_significanceVMET_phi.png");
    cMET_significanceVMET_phi.SaveAs("MET_significanceVMET_phi.C");
    cMET_significanceVMET_phi.Close();

    
    */
  ///////////////////////////////////////////////
  //saving all info in file
  
    fout->mkdir("muHist");
    fout->mkdir("METHist");
    fout->mkdir("CaloMETHist");
    fout->mkdir("anaHist");
    
    
    fout->cd("muHist");
    hnMuon->Write();
    hMuon_dxy->Write();
    hMuon_charge->Write();
    hMuon_tightCharge->Write();
    hMuon_pt->Write();
    hMuon_ptErr->Write();
    hMuon_eta->Write();
    hMuon_phi->Write();
    hMuon_mass->Write();
  
    fout->cd("METHist");
    hMET_pt->Write();
    hMET_phi->Write();
    hMET_sumEt->Write();
    hMET_significance->Write();
    hMET_covXX->Write();
    hMET_covXY->Write();
    hMET_covYY->Write();
    hMET_significanceVMET_phi->Write();
    
    fout->cd("CaloMETHist");
    hCaloMET_pt->Write();
    hCaloMET_phi->Write();
    hCaloMET_sumEt->Write();
    
    fout->cd("anaHist");
    hMuon_leadingPt->Write();
    hMuon_eta1->Write();
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
    
    fout->cd("");
    
    
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
    
    fout->Close();
}







