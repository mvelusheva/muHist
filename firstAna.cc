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
Float_t Muon_leadingPt = -1.;
double mu1Et = -9.;
double mu2Et = -9.;
double invMass = -9.;
//.....
///////////////////////////////////////////////////////////////////////////
//Branches
  TFile *fout = new TFile("my_histograms.root", "RECREATE");
  
    t1->SetBranchAddress("nMuon", &nMuon);
    t1->SetBranchAddress("Muon_charge", Muon_charge);
    t1->SetBranchAddress("Muon_tightCharge", Muon_tightCharge);
    t1->SetBranchAddress("Muon_pt", Muon_pt);
    t1->SetBranchAddress("Muon_ptErr", Muon_ptErr);
    t1->SetBranchAddress("Muon_eta", Muon_eta);
    t1->SetBranchAddress("Muon_phi", Muon_phi);
    t1->SetBranchAddress("Muon_mass", Muon_mass);
    t1->SetBranchAddress("Muon_dxy", Muon_dxy);
    
    
    t1->SetBranchAddress("MET_pt", &MET_pt);
    t1->SetBranchAddress("MET_phi", &MET_phi);
    t1->SetBranchAddress("MET_sumEt", &MET_sumEt);
    t1->SetBranchAddress("MET_significance", &MET_significance);
    t1->SetBranchAddress("MET_covXX", &MET_covXX);
    t1->SetBranchAddress("MET_covXY", &MET_covXY);
    t1->SetBranchAddress("MET_covYY", &MET_covYY);
    t1->SetBranchAddress("CaloMET_pt", &CaloMET_pt);
    t1->SetBranchAddress("CaloMET_phi", &CaloMET_phi);
    t1->SetBranchAddress("CaloMET_sumEt", &CaloMET_sumEt);

  
//Histograms definitions
  TH1F *hnMuon = new TH1F("hnMuon", "hnMuon", 50, 0.5, 50.5);
  TH1F *hMuon_charge = new TH1F("hMuon_charge", "hMuon_charge", 3, -1.5, 1.5);
  TH1F *hMuon_tightCharge = new TH1F("hMuon_tightCharge", "hMuon_tightCharge", 5, -1., 4);
  TH1F *hMuon_pt = new TH1F("hMuon_pt", "hMuon_pt", 100, 0., 100.);
  TH1F *hMuon_ptErr = new TH1F("hMuon_ptErr", "hMuon_ptErr", 10, 0., 2.);
  TH1F *hMuon_eta = new TH1F("hMuon_eta", "hMuon_eta", 50, -5., 5.);
  TH1F *hMuon_phi = new TH1F("hMuon_phi", "hMuon_phi", 50, -5., 5.);
  TH1F *hMuon_mass = new TH1F("hMuon_mass", "hMuon_mass", 100, -2., 2.);
  TH1F *hMuon_dxy = new TH1F("hMuon_dxy", "hMuon_dxy", 100, -4., 4.);
  TH1F *hMET_pt = new TH1F("hMET_pt","hMET_pt", 250, 0., 50.);
  TH1F *hMET_phi = new TH1F("hMET_phi", "hMET_phi", 50, -5., 5.);
  TH1F *hMET_sumEt = new TH1F("hMET_sumEt", "hMET_sumEt", 250, -5., 50.);
  TH1F *hMET_significance = new TH1F("hMET_significance", "hMET_significance", 100, 0., 25.);
  TH1F *hMET_covXX = new TH1F("hMET_covXX", "hMET_covXX", 100, -0., 50.);
  TH1F *hMET_covXY = new TH1F("hMET_covXY", "hMET_covXY", 400, -20., 20.);
  TH1F *hMET_covYY = new TH1F("hMET_covYY", "hMET_covYY", 100, -2., 2.);
  TH1F *hCaloMET_pt = new TH1F("hCaloMET_pt", "hCaloMET_pt", 250, 0., 50.);
  TH1F *hCaloMET_phi = new TH1F("hCaloMET_phi", "hCaloMET_phi", 50, -5., 5.);
  TH1F *hCaloMET_sumEt = new TH1F("hCaloMET_sumEt", "hCaloMET_sumEt", 250, 5., 55.);
  TH1F *hMuon_leadingPt = new TH1F("hMuon_leadingPt", "hMuon_leadingPt", 100, 0., 200.);
  TH2F *hnMuonVMuon_leadingPt = new TH2F("hnMuonVMuon_leadingPt", "hnMuonVMuon_leadingPt", 10, -0.5, 9.5, 100, 0., 150.);
  TH1F *hMuon_eta1 = new TH1F ("hMuon_eta1", "hMuon_eta1", 50, -5., 5.);
  TH1F *hMuon_deltaPhi = new TH1F ("hMuon_deltaPhi", "hMuon_deltaPhi", 50, -5., 5.);
  TH2F *hMuon_phiVMuon_eta = new TH2F ("hMuon_phiVMuon_eta", "hMuon_phiVMuon_eta", 50, -5., 5., 50, -5., 5.);
  TH2F *hMuon_ptVMuon_etaPlus = new TH2F ("hMuon_ptVMuon_etaPlus", "hMuon_ptVMuon_etaPlus", 100, 0., 100., 50, -5., 5.);
  TH2F *hMuon_ptVMuon_etaMinus = new TH2F ("hMuon_ptVMuon_etaMinus", "hMuon_ptVMuon_etaMinus", 100, 0., 100., 50, -5., 5.);
  
  
  
 
 // x: pT на муона (0-200 GeV), y: MET pt (0-200 GeV)
  TH2F *hMETvsMuonPt = new TH2F("hMETvsMuonPt", "MET vs Muon p_{T} (nMuon == 1);Muon p_{T} [GeV];MET [GeV]", 100, 0, 200, 100, 0, 200);
  TH2F *hMETvsLeadingMuPt = new TH2F("hMETvsLeadingMuPt", "MET vs Leading Muon p_{T};Leading Muon p_{T} [GeV];MET [GeV]", 100, 0, 200, 100, 0, 200);// leading muon
  TH2F *hnMuonVMET = new TH2F("hnMuonVMET", "nMuon vs MET;nMuon;MET pt [GeV]", 10, -0.5, 9.5, 100, 0, 200);//METvsnMUons
  TH1F *hMassDifference = new TH1F("hMassDifference", "Difference (Hand - TLorentzVector)", 200, -0.01, 0.01);//Търсим разлика между ТЛоренц и ръчно смятане
  // Търсим пик около 80 GeV, затова правим обхват до 120-150
  TH1F *hW_transverseMass = new TH1F("hW_transverseMass", "W Transverse Mass;M_{T} [GeV];Events", 100, 0, 150);// Търсим напречна маса на W-boson
  TH1F *hW_transverseMass_Lorentz = new TH1F("hW_transverseMass_Lorentz", "W Transverse Mass (TLorentzVector);M_{T} [GeV];Events", 100, 0, 150);//С Тлоренц
  TH1F *hDiff_TVector_Hand = new TH1F("hDiff_TVector_Hand", "Difference: TVector - Hand;Difference [GeV];Events", 200, -0.0001, 0.0001);//сравнявам твектор и ръзно смятане
  TH1F *hDiff2_TVector_Lorentz = new TH1F("hDiff2_TVector_Lorentz", "Difference: TVector - Lorentz;Difference [GeV];Events", 200, -0.0001, 0.0001);// сравнявам твектор и тлоренц
  TH1F *hW_transverseMass_Hand = new TH1F("hW_transverseMassHand", "W Transverse Mass (Hand Calc);M_{T} [GeV];Events", 100, 0, 150);
  TH1F *hDimuon_MassRuka = new TH1F("hDimuon_MassRuka", "Invariant Mass Hand Calc", 300, 0, 150);//Inv mass
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

/*TCanvas cnMuon("cnMuon", "nMuon", 800, 600);
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
TCanvas cDimuon_pt("cDimuon_pt", "Dimuon pt", 800, 600); //transverse momentum of dimuon - two muon events
TCanvas cDimuon_pz("cDimuon_pz", "Dimuon pz", 800, 600); // momentum along z axis
TCanvas cDimuon_ptVDimuon_mass("cDimuon_ptVDimuon_mass", "Dimuon pt vs Dimuon mass", 800, 600);
TCanvas cDimuon_pzVDimuon_mass("cDimuon_pzVDimuon_mass", "Dimuon pz vs Dimuon mass", 800, 600);
/////////////////////////////////////////////////////////////TLorentzVector/////////
*/
 //////////////////////////////////////////////////////////////////////
Int_t nentries = (Int_t)t1->GetEntries();
cout << "Number of events in the file: " << nentries << endl;

double myMuon_mass = 0.106;
double myMuon_mass2 = 0.0112;

for (int i =0; i<nentries; i++){
//for (int i =0; i<1000; i++){
  t1->GetEntry(i);
  
  
  if (nMuon == 1) {
  
    float ptMu = Muon_pt[0]; // Вземаме pT на единствения муон
        hMETvsMuonPt->Fill(ptMu, MET_pt);
        
        
   // НАпречната маса на w-boson
    double phiMu  = Muon_phi[0];
    double met    = MET_pt;
    double phiMet = MET_phi;
    double etaMu = Muon_eta[0];
    const double PI = 3.1415926535;
    
//    if (ptMu > 25.0 && met > 25.0) {
    
    TLorentzVector mu, nu, W;

   // Залагам Eta = 0 и за муона, и за неутриното
   mu.SetPtEtaPhiM(ptMu, etaMu, phiMu, 0.105); 
   nu.SetPtEtaPhiM(met, 0, phiMet, 0); 

   W = mu + nu;
   double mTW_Lorentz = W.M(); 
   hW_transverseMass_Lorentz->Fill(mTW_Lorentz);	//ne e transverse
    
    double dPhi_TVector = TVector2::Phi_mpi_pi(phiMu - phiMet);
    double mTW_TVector = sqrt(2 * ptMu * met * (1 - cos(dPhi_TVector)));
    hW_transverseMass->Fill(mTW_TVector);
   
    
    //Искам да пробвам да сметна напречната маса на ръка също
        double dPhi_Hand = phiMu - phiMet;
        while (dPhi_Hand >  PI) dPhi_Hand -= 2 * PI;
        while (dPhi_Hand < -PI) dPhi_Hand += 2 * PI;
        
        double mTW_Hand = sqrt(2 * ptMu * met * (1 - cos(dPhi_Hand)));
        hW_transverseMass_Hand->Fill(mTW_Hand);
        
   // Смятам разликата
    double diff = mTW_TVector - mTW_Hand;
    double diff2 = mTW_TVector - mTW_Lorentz;
    
    // Пълня хистограмите за разликата
    hDiff_TVector_Hand->Fill(diff);
    hDiff2_TVector_Lorentz->Fill(diff2);
    
//        }
    }
  if (nMuon > 0){
    Muon_leadingPt = Muon_pt[0];
    for (UInt_t mu = 1; mu < nMuon; mu++){
      if (Muon_pt[mu] > Muon_leadingPt){
        Muon_leadingPt = Muon_pt[mu];
    }
    }
    hMETvsLeadingMuPt->Fill(Muon_leadingPt, MET_pt);
  }
    
      
    
    if(nMuon == 2 && Muon_charge[0] * Muon_charge[1] == -1){
    
    double dPhi_mumu = TVector2::Phi_mpi_pi(Muon_phi[0] - Muon_phi[1]);
    dPhi_mumu = fabs(dPhi_mumu); 
    
    hnMuonVMET->Fill(nMuon, MET_pt);
    hMuon_leadingPt->Fill(Muon_leadingPt);
    hnMuonVMuon_leadingPt->Fill(nMuon, Muon_leadingPt);
       
       double mu1Et = sqrt(Muon_pt[0]*Muon_pt[0] + Muon_mass[0]*Muon_mass[0]);
       //mu1Et = sqrt(Muon_pt[0]*Muon_pt[0] + myMuon_mass2);
       double mu2Et = sqrt(Muon_pt[1]*Muon_pt[1]+ Muon_mass[1]*Muon_mass[1]);
       //std::cout << "energy transverse muon 1= " << mu1Et << std::endl;
       
       
       
       //Smqtam Naprechna masa na ruka
       double Muon_deltaPhi = Muon_phi[0] - Muon_phi[1];
       double Muon_deltaEta = Muon_eta[0] - Muon_eta[1];
       
       
       //skalarno proizvedenie na pt
       double pt_dot_pt = Muon_pt[0] * Muon_pt[1] * cos(Muon_deltaPhi);
       
       double m1 = Muon_mass[0];
       double m2 = Muon_mass[1];
       
       double M2 = (m1*m1) + (m2*m2) + 2 * (mu1Et * mu2Et * cosh(Muon_deltaEta) - Muon_pt[0] * Muon_pt[1] * cos(Muon_deltaPhi));
       
       double invMass = sqrt(M2);
       
       
       hDimuon_MassRuka->Fill(invMass);//ruchnata stoinost
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
       
       
       double diff = invMass - dimuon.M(); 
       
       hMassDifference->Fill(diff);//Разликата
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
    hMuon_phi->Fill(Muon_phi[mu]);
    hMuon_mass->Fill(Muon_mass[mu]);
    hMuon_dxy->Fill(Muon_dxy[mu]);
    
    
    
    }
}


    fout->mkdir("Mu_Plots");
    fout->mkdir("MET_Plots");
    fout->mkdir("CaloMET_Plots");
    fout->mkdir("Dimuon_Ana");
    
    
    fout->cd("Mu_Plots");
    hnMuon->Write();
    hMuon_dxy->Write();
    hMuon_charge->Write();
    hMuon_tightCharge->Write();
    hMuon_pt->Write();
    hMuon_ptErr->Write();
    hMuon_eta->Write();
    hMuon_phi->Write();
    hMuon_mass->Write();
  
    fout->cd("MET_Plots");
    hMET_pt->Write();
    hMET_phi->Write();
    hMET_sumEt->Write();
    hMET_significance->Write();
    hMET_covXX->Write();
    hMET_covXY->Write();
    hMET_covYY->Write();
    hMET_significanceVMET_phi->Write();
    
    fout->cd("CaloMET_Plots");
    hCaloMET_pt->Write();
    hCaloMET_phi->Write();
    hCaloMET_sumEt->Write();
    
    fout->cd("Dimuon_Ana");
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
    hDimuon_MassRuka->Write();
    hMassDifference->Write();
    hnMuonVMET->Write();
    hMETvsMuonPt->Write();
    hMETvsLeadingMuPt->Write();
    hW_transverseMass->Write();
    hW_transverseMass_Hand->Write();
    hW_transverseMass_Lorentz->Write();
    hDiff_TVector_Hand->Write();
    hDiff2_TVector_Lorentz->Write();
    
  
    
    
    fout->cd(""); 
    fout->Write(); 
    fout->Close(); 
}
    

