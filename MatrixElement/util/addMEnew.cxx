#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TLegend.h>

#include "MatrixElement/AddME.h"
#include "MadGraphME/ComputeMGME.h"

using namespace std;

TString dir = "/afs/cern.ch/atlas/groups/HSG2/H4l/run2/2016/MiniTrees/Prod_v08/mc/Nominal/";
TString newdir = "/afs/cern.ch/user/l/lveloce/h4l/ME/data/recoME/";

void FileNames(vector<string> *fileList);
void VBFVHCardNames(vector<string> *vbfvhcardList);
void ggFCardNames(vector<string> *ggfcardList);


vector<TLorentzVector> getFermionsVBFVH(Float_t *jeteta, Float_t *jetm, Float_t *jetphi, Float_t *jetpt, 
				 				   Float_t *leptoneta, Float_t *leptonm, Float_t *leptonphi, Float_t *leptonpt, 
				 				   Int_t jetnum) {

	vector<TLorentzVector> fermions;
	
	//Kinematic vectors 
	TLorentzVector lepton1, lepton2, lepton3, lepton4, jet1, jet2; //leptons and jets
							
	lepton1.SetPtEtaPhiM(leptonpt[0],leptoneta[0],leptonphi[0],leptonm[0]);
	lepton2.SetPtEtaPhiM(leptonpt[1],leptoneta[1],leptonphi[1],leptonm[1]);
	lepton3.SetPtEtaPhiM(leptonpt[2],leptoneta[2],leptonphi[2],leptonm[2]);
	lepton4.SetPtEtaPhiM(leptonpt[3],leptoneta[3],leptonphi[3],leptonm[3]);

	jet1.SetPtEtaPhiM(jetpt[0],jeteta[0],jetphi[0],jetm[0]);
	jet2.SetPtEtaPhiM(jetpt[1],jeteta[1],jetphi[1],jetm[1]);
		
	fermions.push_back(jet1);
	fermions.push_back(jet2);
		
	fermions.push_back(lepton1);
	fermions.push_back(lepton2);
	fermions.push_back(lepton3);
	fermions.push_back(lepton4);
			
	//cout << "jet1 " << jet1.Pt() << endl;
	//cout << "Fermion Vector jet1 " << (fermions.at(0)).Pt() << endl;

	return fermions; //returns fermion vector in the correct order for process type

}

vector<TLorentzVector> getFermionsggF1j(Float_t *jeteta, Float_t *jetm, Float_t *jetphi, Float_t *jetpt, 
				 				   Float_t *leptoneta, Float_t *leptonm, Float_t *leptonphi, Float_t *leptonpt, 
				 				   Int_t jetnum) {
	
	vector<TLorentzVector> fermions;
	
	//Kinematic vectors 
	TLorentzVector lepton1, lepton2, lepton3, lepton4, jet1; //leptons and jet

	lepton1.SetPtEtaPhiM(leptonpt[0],leptoneta[0],leptonphi[0],leptonm[0]);
	lepton2.SetPtEtaPhiM(leptonpt[1],leptoneta[1],leptonphi[1],leptonm[1]);
	lepton3.SetPtEtaPhiM(leptonpt[2],leptoneta[2],leptonphi[2],leptonm[2]);
	lepton4.SetPtEtaPhiM(leptonpt[3],leptoneta[3],leptonphi[3],leptonm[3]);

	jet1.SetPtEtaPhiM(jetpt[0],jeteta[0],jetphi[0],jetm[0]);
		
	fermions.push_back(lepton1);
	fermions.push_back(lepton2);
	fermions.push_back(lepton3);
	fermions.push_back(lepton4);
		
	fermions.push_back(jet1);		
		
	return fermions;		 				   
				 				   
}


float getlogME(vector<float>& mtxelem) {

	float logME;
	float bareME = 0;

	for (unsigned int i=0; i < mtxelem.size(); i++) {
		bareME += mtxelem.at(i); 
	}
	logME = log(bareME);
	//cout << "function log ME2 is " << logME << endl;

	return logME;
	
}


int main (int argc, const char** argv) { //argc is number of arguments you pass to the program when you run
										 //argv is the values you passed to the program
 	argc = argc;
  	argv = argv;

	vector<string> ListofFiles;
  	FileNames(&ListofFiles); 
  	cout << "Calculating ME for the following files: " << '\n'; 
  	for (vector<string>::iterator it = ListofFiles.begin() ; it != ListofFiles.end(); ++it)
	{
  		cout << *it << ".root" << '\n';
 	}
 	 std::cout << std::string(80,'-') << endl;
 	 
  	for (vector<string>::iterator ifile = ListofFiles.begin() ; ifile != ListofFiles.end(); ++ifile)
	{
  		//here is where we get the four vectors from the original root files
  		TString filename = *ifile;
		TFile *oldfile = TFile::Open(dir+filename+".root");
		if (!oldfile) {
			cout <<  filename << ".root could not be opened." << endl; 
			exit(1); }
		else {
			cout << '\n' << "Opening file " << filename << ".root" << " and adding ME information." << endl; }
		
		TTree *oldT = (TTree*) oldfile->Get("tree_incl_all");

		TString newfilename = filename+"_ME.root";
		TFile *newfile = new TFile(newdir+newfilename, "RECREATE");

		TH1F *hME_VBF_SM 			= new TH1F("ME_VBF_SM", "ME SM; ME; Events", 50, -150, -0);
		TH1F *hME_VBF_bSM_Hvv1		= new TH1F("ME_VBF_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_VBF_SMbSM_Hvv1	= new TH1F("ME_VBF_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hME_VBF_bSM_Hvv2p5	= new TH1F("ME_VBF_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_VBF_SMbSM_Hvv2p5	= new TH1F("ME_VBF_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hOO1_VBF_Hvv1			= new TH1F("OO1_VBF_Hvv1", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_VBF_Hvv1			= new TH1F("OO2_VBF_Hvv1", "OO_2; OO_2; Events", 20, -20, 20);
		TH1F *hOO1_VBF_Hvv2p5		= new TH1F("OO1_VBF_Hvv2p5", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_VBF_Hvv2p5		= new TH1F("OO2_VBF_Hvv2p5", "OO_2; OO_2; Events", 20, -20, 20);
		TH1F *hME_VBF_bSM_Avv1		= new TH1F("ME_VBF_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_VBF_SMbSM_Avv1	= new TH1F("ME_VBF_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hME_VBF_bSM_Avv2p5	= new TH1F("ME_VBF_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_VBF_SMbSM_Avv2p5	= new TH1F("ME_VBF_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hOO1_VBF_Avv1			= new TH1F("OO1_VBF_Avv1", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_VBF_Avv1			= new TH1F("OO2_VBF_Avv1", "OO_2; OO_2; Events", 20, -20, 20);
		TH1F *hOO1_VBF_Avv2p5		= new TH1F("OO1_VBF_Avv2p5", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_VBF_Avv2p5		= new TH1F("OO2_VBF_Avv2p5", "OO_2; OO_2; Events", 20, -20, 20);
		
		TH1F *hME_VH_SM 			= new TH1F("ME_VBF_SM", "ME SM; ME; Events", 50, -150, -0);
		TH1F *hME_VH_bSM_Hvv1		= new TH1F("ME_VBF_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_VH_SMbSM_Hvv1		= new TH1F("ME_VBF_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hME_VH_bSM_Hvv2p5		= new TH1F("ME_VBF_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_VH_SMbSM_Hvv2p5	= new TH1F("ME_VBF_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hOO1_VH_Hvv1			= new TH1F("OO1_VH_Hvv1", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_VH_Hvv1			= new TH1F("OO2_VH_Hvv1", "OO_2; OO_2; Events", 20, -20, 20);
		TH1F *hOO1_VH_Hvv2p5		= new TH1F("OO1_VH_Hvv2p5", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_VH_Hvv2p5		= new TH1F("OO2_VH_Hvv2p5", "OO_2; OO_2; Events", 20, -20, 20);
		TH1F *hME_VH_bSM_Avv1		= new TH1F("ME_VBF_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_VH_SMbSM_Avv1		= new TH1F("ME_VBF_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hME_VH_bSM_Avv2p5		= new TH1F("ME_VBF_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_VH_SMbSM_Avv2p5	= new TH1F("ME_VBF_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hOO1_VH_Avv1			= new TH1F("OO1_VH_Avv1", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_VH_Avv1			= new TH1F("OO2_VH_Avv1", "OO_2; OO_2; Events", 20, -20, 20);
		TH1F *hOO1_VH_Avv2p5		= new TH1F("OO1_VH_Avv2p5", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_VH_Avv2p5		= new TH1F("OO2_VH_Avv2p5", "OO_2; OO_2; Events", 20, -20, 20);
		
		TH1F *hME_ggF1j_SM 			= new TH1F("ME_ggF1j_SM", "ME SM; ME; Events", 50, -150, -0);
		TH1F *hME_ggF1j_bSM_Hvv1	= new TH1F("ME_ggF1j_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_ggF1j_SMbSM_Hvv1	= new TH1F("ME_ggF1j_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hME_ggF1j_bSM_Hvv2p5	= new TH1F("ME_ggF1j_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_ggF1j_SMbSM_Hvv2p5= new TH1F("ME_ggF1j_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hOO1_ggF1j_Hvv1		= new TH1F("OO1_ggF1j_Hvv1", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_ggF1j_Hvv1		= new TH1F("OO2_ggF1j_Hvv1", "OO_2; OO_2; Events", 20, -20, 20);
		TH1F *hOO1_ggF1j_Hvv2p5		= new TH1F("OO1_ggF1j_Hvv2p5", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_ggF1j_Hvv2p5		= new TH1F("OO2_ggF1j_Hvv2p5", "OO_2; OO_2; Events", 20, -20, 20);		
		TH1F *hME_ggF1j_bSM_Avv1	= new TH1F("ME_ggF1j_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_ggF1j_SMbSM_Avv1	= new TH1F("ME_ggF1j_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hME_ggF1j_bSM_Avv2p5	= new TH1F("ME_ggF1j_bSM", "ME bSM; ME; Events", 50, -150, -0);
		TH1F *hME_ggF1j_SMbSM_Avv2p5= new TH1F("ME_ggF1j_SMbSM", "ME SMbSM; ME; Events", 50, -150, -0);
		TH1F *hOO1_ggF1j_Avv1		= new TH1F("OO1_ggF1j_Avv1", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_ggF1j_Avv1		= new TH1F("OO2_ggF1j_Avv1", "OO_2; OO_2; Events", 20, -20, 20);
		TH1F *hOO1_ggF1j_Avv2p5		= new TH1F("OO1_ggF1j_Avv2p5", "OO_1; OO_1; Events", 20, -20, 20);
		TH1F *hOO2_ggF1j_Avv2p5		= new TH1F("OO2_ggF1j_Avv2p5", "OO_2; OO_2; Events", 20, -20, 20);
		
		//Original Variables:
		Int_t			n_jets;
 		Float_t 		weight;
		Int_t	 		lepton_id[4];
  		Float_t			jet_eta[4];
		Float_t			jet_m[4];
		Float_t 		jet_phi[4];
		Float_t 		jet_pt[4];
		Float_t 		lepton_eta[4];
		Float_t 		lepton_m[4];
		Float_t 		lepton_phi[4];
		Float_t 		lepton_pt[4];
		
		//New variables TBA:
		Float_t 		ME_VBF_SM;
		Float_t			ME_VBF_bSM_Hvv1;
		Float_t			ME_VBF_SMbSM_Hvv1;
		Float_t			ME_VBF_bSM_Hvv2p5; //i.e.: 2p5 = 2.5 "two point five" (limit on kHvv and kAvv)
		Float_t			ME_VBF_SMbSM_Hvv2p5;
		Float_t 		OO1_VBF_Hvv1;
		Float_t 		OO1_VBF_Hvv2p5;
		Float_t			OO2_VBF_Hvv1;
		Float_t			OO2_VBF_Hvv2p5;
		Float_t			ME_VBF_bSM_Avv1;
		Float_t			ME_VBF_SMbSM_Avv1;
		Float_t			ME_VBF_bSM_Avv2p5; 
		Float_t			ME_VBF_SMbSM_Avv2p5;
		Float_t 		OO1_VBF_Avv1;
		Float_t 		OO1_VBF_Avv2p5;
		Float_t			OO2_VBF_Avv1;
		Float_t			OO2_VBF_Avv2p5;
		
		Float_t 		ME_VH_SM;
		Float_t			ME_VH_bSM_Hvv1;
		Float_t			ME_VH_SMbSM_Hvv1;
		Float_t			ME_VH_bSM_Hvv2p5; 
		Float_t			ME_VH_SMbSM_Hvv2p5;
		Float_t 		OO1_VH_Hvv1;
		Float_t 		OO1_VH_Hvv2p5;
		Float_t			OO2_VH_Hvv1;
		Float_t			OO2_VH_Hvv2p5;
		Float_t			ME_VH_bSM_Avv1;
		Float_t			ME_VH_SMbSM_Avv1;
		Float_t			ME_VH_bSM_Avv2p5; 
		Float_t			ME_VH_SMbSM_Avv2p5;
		Float_t 		OO1_VH_Avv1;
		Float_t 		OO1_VH_Avv2p5;
		Float_t			OO2_VH_Avv1;
		Float_t			OO2_VH_Avv2p5;
				
		Float_t 		ME_ggF1j_SM;
		Float_t			ME_ggF1j_bSM_Hvv1;
		Float_t			ME_ggF1j_SMbSM_Hvv1;
		Float_t			ME_ggF1j_bSM_Hvv2p5; 
		Float_t			ME_ggF1j_SMbSM_Hvv2p5;
		Float_t 		OO1_ggF1j_Hvv1;
		Float_t 		OO1_ggF1j_Hvv2p5;
		Float_t			OO2_ggF1j_Hvv1;
		Float_t			OO2_ggF1j_Hvv2p5;
		Float_t			ME_ggF1j_bSM_Avv1;
		Float_t			ME_ggF1j_SMbSM_Avv1;
		Float_t			ME_ggF1j_bSM_Avv2p5; 
		Float_t			ME_ggF1j_SMbSM_Avv2p5;
		Float_t 		OO1_ggF1j_Avv1;
		Float_t 		OO1_ggF1j_Avv2p5;
		Float_t			OO2_ggF1j_Avv1;
		Float_t			OO2_ggF1j_Avv2p5;
		
		//Get branches needed for ME calculation from old tree
		TBranch *b_n_jets 			= oldT->GetBranch("n_jets");
		TBranch *b_weight 			= oldT->GetBranch("weight");
 		TBranch *b_lepton_id 		= oldT->GetBranch("lepton_id");
   		TBranch *b_jet_eta 			= oldT->GetBranch("jet_eta");
   		TBranch *b_jet_m 			= oldT->GetBranch("jet_m");
   		TBranch *b_jet_phi 			= oldT->GetBranch("jet_phi");
   		TBranch *b_jet_pt 			= oldT->GetBranch("jet_pt");
   		TBranch *b_lepton_eta 		= oldT->GetBranch("lepton_eta");
   		TBranch *b_lepton_m 		= oldT->GetBranch("lepton_m");
   		TBranch *b_lepton_phi 		= oldT->GetBranch("lepton_phi");
   		TBranch *b_lepton_pt 		= oldT->GetBranch("lepton_pt");
   		
   		//Set branch addresses, including new branches to be added	
   		//old branches:
		oldT->SetBranchAddress("n_jets",		&n_jets);
 		oldT->SetBranchAddress("weight",     	&weight);
  		oldT->SetBranchAddress("lepton_id",  	&lepton_id);
  		oldT->SetBranchAddress("jet_eta",	  	&jet_eta);
		oldT->SetBranchAddress("jet_m",	  		&jet_m);
		oldT->SetBranchAddress("jet_phi",		&jet_phi);
		oldT->SetBranchAddress("jet_pt",		&jet_pt);
		oldT->SetBranchAddress("lepton_eta",	&lepton_eta);
		oldT->SetBranchAddress("lepton_m",	  	&lepton_m);
		oldT->SetBranchAddress("lepton_phi",	&lepton_phi);
		oldT->SetBranchAddress("lepton_pt",		&lepton_pt);
		
		//new branches
		oldT->SetBranchAddress("ME_VBF_SM",				&ME_VBF_SM);
		oldT->SetBranchAddress("ME_VBF_bSM_Hvv1", 		&ME_VBF_bSM_Hvv1);
		oldT->SetBranchAddress("ME_VBF_SMbSM_Hvv1",		&ME_VBF_SMbSM_Hvv1);
		oldT->SetBranchAddress("ME_VBF_bSM_Hvv2p5",		&ME_VBF_bSM_Hvv2p5);
		oldT->SetBranchAddress("ME_VBF_SMbSM_Hvv2p5",	&ME_VBF_SMbSM_Hvv2p5);
		oldT->SetBranchAddress("OO1_VBF_Hvv1",			&OO1_VBF_Hvv1);
		oldT->SetBranchAddress("OO1_VBF_Hvv2p5",		&OO1_VBF_Hvv2p5);
		oldT->SetBranchAddress("OO2_VBF_Hvv1",			&OO2_VBF_Hvv1);
		oldT->SetBranchAddress("OO2_VBF_Hvv2p5",		&OO2_VBF_Hvv2p5);
		oldT->SetBranchAddress("ME_VBF_bSM_Avv1", 		&ME_VBF_bSM_Avv1);
		oldT->SetBranchAddress("ME_VBF_SMbSM_Avv1",		&ME_VBF_SMbSM_Avv1);
		oldT->SetBranchAddress("ME_VBF_bSM_Avv2p5",		&ME_VBF_bSM_Avv2p5);
		oldT->SetBranchAddress("ME_VBF_SMbSM_Avv2p5",	&ME_VBF_SMbSM_Avv2p5);
		oldT->SetBranchAddress("OO1_VBF_Avv1",			&OO1_VBF_Avv1);
		oldT->SetBranchAddress("OO1_VBF_Avv2p5",		&OO1_VBF_Avv2p5);
		oldT->SetBranchAddress("OO2_VBF_Avv1",			&OO2_VBF_Avv1);
		oldT->SetBranchAddress("OO2_VBF_Avv2p5",		&OO2_VBF_Avv2p5);

		oldT->SetBranchAddress("ME_VH_SM",				&ME_VH_SM);
		oldT->SetBranchAddress("ME_VH_bSM_Hvv1", 		&ME_VH_bSM_Hvv1);
		oldT->SetBranchAddress("ME_VH_SMbSM_Hvv1",		&ME_VH_SMbSM_Hvv1);
		oldT->SetBranchAddress("ME_VH_bSM_Hvv2p5",		&ME_VH_bSM_Hvv2p5);
		oldT->SetBranchAddress("ME_VH_SMbSM_Hvv2p5",	&ME_VH_SMbSM_Hvv2p5);
		oldT->SetBranchAddress("OO1_VH_Hvv1",			&OO1_VH_Hvv1);
		oldT->SetBranchAddress("OO1_VH_Hvv2p5",			&OO1_VH_Hvv2p5);
		oldT->SetBranchAddress("OO2_VH_Hvv1",			&OO2_VH_Hvv1);
		oldT->SetBranchAddress("OO2_VH_Hvv2p5",			&OO2_VH_Hvv2p5);
		oldT->SetBranchAddress("ME_VH_bSM_Avv1", 		&ME_VH_bSM_Avv1);
		oldT->SetBranchAddress("ME_VH_SMbSM_Avv1",		&ME_VH_SMbSM_Avv1);
		oldT->SetBranchAddress("ME_VH_bSM_Avv2p5",		&ME_VH_bSM_Avv2p5);
		oldT->SetBranchAddress("ME_VH_SMbSM_Avv2p5",	&ME_VH_SMbSM_Avv2p5);
		oldT->SetBranchAddress("OO1_VH_Avv1",			&OO1_VH_Avv1);
		oldT->SetBranchAddress("OO1_VH_Avv2p5",			&OO1_VH_Avv2p5);
		oldT->SetBranchAddress("OO2_VH_Avv1",			&OO2_VH_Avv1);
		oldT->SetBranchAddress("OO2_VH_Avv2p5",			&OO2_VH_Avv2p5);
		
		oldT->SetBranchAddress("ME_ggF1j_SM",			&ME_ggF1j_SM);
		oldT->SetBranchAddress("ME_ggF1j_bSM_Hvv1", 	&ME_ggF1j_bSM_Hvv1);
		oldT->SetBranchAddress("ME_ggF1j_SMbSM_Hvv1",	&ME_ggF1j_SMbSM_Hvv1);
		oldT->SetBranchAddress("ME_ggF1j_bSM_Hvv2p5",	&ME_ggF1j_bSM_Hvv2p5);
		oldT->SetBranchAddress("ME_ggF1j_SMbSM_Hvv2p5",	&ME_ggF1j_SMbSM_Hvv2p5);
		oldT->SetBranchAddress("OO1_ggF1j_Hvv1",		&OO1_ggF1j_Hvv1);
		oldT->SetBranchAddress("OO1_ggF1j_Hvv2p5",		&OO1_ggF1j_Hvv2p5);
		oldT->SetBranchAddress("OO2_ggF1j_Hvv1",		&OO2_ggF1j_Hvv1);
		oldT->SetBranchAddress("OO2_ggF1j_Hvv2p5",		&OO2_ggF1j_Hvv2p5);
		oldT->SetBranchAddress("ME_ggF1j_bSM_Avv1", 	&ME_ggF1j_bSM_Avv1);
		oldT->SetBranchAddress("ME_ggF1j_SMbSM_Avv1",	&ME_ggF1j_SMbSM_Avv1);
		oldT->SetBranchAddress("ME_ggF1j_bSM_Avv2p5",	&ME_ggF1j_bSM_Avv2p5);
		oldT->SetBranchAddress("ME_ggF1j_SMbSM_Avv2p5",	&ME_ggF1j_SMbSM_Avv2p5);
		oldT->SetBranchAddress("OO1_ggF1j_Avv1",		&OO1_ggF1j_Avv1);
		oldT->SetBranchAddress("OO1_ggF1j_Avv2p5",		&OO1_ggF1j_Avv2p5);
		oldT->SetBranchAddress("OO2_ggF1j_Avv1",		&OO2_ggF1j_Avv1);
		oldT->SetBranchAddress("OO2_ggF1j_Avv2p5",		&OO2_ggF1j_Avv2p5);
		//they are with oldT but their addresses will be copied into newT, branches created, and then filled! 
		
		//clone the original tree
		TTree *newT = oldT->CloneTree(0);	//clones the old tree including the branch addresses I just added to the old tree

		//add the new branches	
		newT->Branch("ME_VBF_SM",				&ME_VBF_SM, 			"log of SM matrix element squared /F");
		newT->Branch("ME_VBF_bSM_Hvv1", 		&ME_VBF_bSM_Hvv1, 		"log of bSM matrix element squared with Hvv=1 /F");
		newT->Branch("ME_VBF_SMbSM_Hvv1",		&ME_VBF_SMbSM_Hvv1, 	"log of SM + bSM matrix element squared with Hvv=1 /F");
		newT->Branch("ME_VBF_bSM_Hvv2p5",		&ME_VBF_bSM_Hvv2p5,		"log of bSM matrix element squared with Hvv=2.5 /F");
		newT->Branch("ME_VBF_SMbSM_Hvv2p5",		&ME_VBF_SMbSM_Hvv2p5,	"log of SM + bSM matrix element squared with Hvv=2.5 /F");
		newT->Branch("OO1_VBF_Hvv1",			&OO1_VBF_Hvv1,			"Optimal Observable 1 for VBF and Hvv = 1 /F");
		newT->Branch("OO1_VBF_Hvv2p5",			&OO1_VBF_Hvv2p5,		"Optimal Observable 1 for VBF and Hvv = 2.5 /F");
		newT->Branch("OO2_VBF_Hvv1",			&OO2_VBF_Hvv1,			"Optimal Observable 2 for VBF and Hvv = 1 /F");
		newT->Branch("OO2_VBF_Hvv2p5",			&OO2_VBF_Hvv2p5,		"Optimal Observable 2 for VBF and Hvv = 2.5 /F");
		newT->Branch("ME_VBF_bSM_Avv1", 		&ME_VBF_bSM_Avv1, 		"log of bSM matrix element squared with Avv=1 /F");
		newT->Branch("ME_VBF_SMbSM_Avv1",		&ME_VBF_SMbSM_Avv1, 	"log of SM + bSM matrix element squared with Avv=1 /F");
		newT->Branch("ME_VBF_bSM_Avv2p5",		&ME_VBF_bSM_Avv2p5,		"log of bSM matrix element squared with Avv=2.5 /F");
		newT->Branch("ME_VBF_SMbSM_Avv2p5",		&ME_VBF_SMbSM_Avv2p5,	"log of SM + bSM matrix element squared with Avv=2.5 /F");
		newT->Branch("OO1_VBF_Avv1",			&OO1_VBF_Avv1,			"Optimal Observable 1 for VBF and Avv = 1 /F");
		newT->Branch("OO1_VBF_Avv2p5",			&OO1_VBF_Avv2p5,		"Optimal Observable 1 for VBF and Avv = 2.5 /F");
		newT->Branch("OO2_VBF_Avv1",			&OO2_VBF_Avv1,			"Optimal Observable 2 for VBF and Avv = 1 /F");
		newT->Branch("OO2_VBF_Avv2p5",			&OO2_VBF_Avv2p5,		"Optimal Observable 2 for VBF and Avv = 2.5 /F");

		newT->Branch("ME_VH_SM",				&ME_VH_SM, 				"log of SM matrix element squared /F");
		newT->Branch("ME_VH_bSM_Hvv1", 			&ME_VH_bSM_Hvv1, 		"log of bSM matrix element squared with Hvv=1 /F");
		newT->Branch("ME_VH_SMbSM_Hvv1",		&ME_VH_SMbSM_Hvv1, 		"log of SM + bSM matrix element squared with Hvv=1 /F");
		newT->Branch("ME_VH_bSM_Hvv2p5",		&ME_VH_bSM_Hvv2p5,		"log of bSM matrix element squared with Hvv=2.5 /F");
		newT->Branch("ME_VH_SMbSM_Hvv2p5",		&ME_VH_SMbSM_Hvv2p5,	"log of SM + bSM matrix element squared with Hvv=2.5 /F");
		newT->Branch("OO1_VH_Hvv1",				&OO1_VH_Hvv1,			"Optimal Observable 1 for VH and Hvv = 1 /F");
		newT->Branch("OO1_VH_Hvv2p5",			&OO1_VH_Hvv2p5,			"Optimal Observable 1 for VH and Hvv = 2.5 /F");
		newT->Branch("OO2_VH_Hvv1",				&OO2_VH_Hvv1,			"Optimal Observable 2 for VH and Hvv = 1 /F");
		newT->Branch("OO2_VH_Hvv2p5",			&OO2_VH_Hvv2p5,			"Optimal Observable 2 for VH and Hvv = 2.5 /F");
		newT->Branch("ME_VH_bSM_Avv1", 			&ME_VH_bSM_Avv1, 		"log of bSM matrix element squared with Avv=1 /F");
		newT->Branch("ME_VH_SMbSM_Avv1",		&ME_VH_SMbSM_Avv1, 		"log of SM + bSM matrix element squared with Avv=1 /F");
		newT->Branch("ME_VH_bSM_Avv2p5",		&ME_VH_bSM_Avv2p5,		"log of bSM matrix element squared with Avv=2.5 /F");
		newT->Branch("ME_VH_SMbSM_Avv2p5",		&ME_VH_SMbSM_Avv2p5,	"log of SM + bSM matrix element squared with Avv=2.5 /F");
		newT->Branch("OO1_VH_Avv1",				&OO1_VH_Avv1,			"Optimal Observable 1 for VH and Avv = 1 /F");
		newT->Branch("OO1_VH_Avv2p5",			&OO1_VH_Avv2p5,			"Optimal Observable 1 for VH and Avv = 2.5 /F");
		newT->Branch("OO2_VH_Avv1",				&OO2_VH_Avv1,			"Optimal Observable 2 for VH and Avv = 1 /F");
		newT->Branch("OO2_VH_Avv2p5",			&OO2_VH_Avv2p5,			"Optimal Observable 2 for VH and Avv = 2.5 /F");

		newT->Branch("ME_ggF1j_SM",				&ME_ggF1j_SM, 			"log of SM matrix element squared /F");
		newT->Branch("ME_ggF1j_bSM_Hvv1", 		&ME_ggF1j_bSM_Hvv1, 	"log of bSM matrix element squared with Hvv=1 /F");
		newT->Branch("ME_ggF1j_SMbSM_Hvv1",		&ME_ggF1j_SMbSM_Hvv1, 	"log of SM + bSM matrix element squared with Hvv=1 /F");
		newT->Branch("ME_ggF1j_bSM_Hvv2p5",		&ME_ggF1j_bSM_Hvv2p5,	"log of bSM matrix element squared with Hvv=2.5 /F");
		newT->Branch("ME_ggF1j_SMbSM_Hvv2p5",	&ME_ggF1j_SMbSM_Hvv2p5,	"log of SM + bSM matrix element squared with Hvv=2.5 /F");
		newT->Branch("OO1_ggF1j_Hvv1",			&OO1_ggF1j_Hvv1,		"Optimal Observable 1 for ggF1j and Hvv = 1 /F");
		newT->Branch("OO1_ggF1j_Hvv2p5",		&OO1_ggF1j_Hvv2p5,		"Optimal Observable 1 for ggF1j and Hvv = 2.5 /F");
		newT->Branch("OO2_ggF1j_Hvv1",			&OO2_ggF1j_Hvv1,		"Optimal Observable 2 for ggF1j and Hvv = 1 /F");
		newT->Branch("OO2_ggF1j_Hvv2p5",		&OO2_ggF1j_Hvv2p5,		"Optimal Observable 2 for ggF1j and Hvv = 2.5 /F");
		newT->Branch("ME_ggF1j_bSM_Avv1", 		&ME_ggF1j_bSM_Avv1, 	"log of bSM matrix element squared with Avv=1 /F");
		newT->Branch("ME_ggF1j_SMbSM_Avv1",		&ME_ggF1j_SMbSM_Avv1, 	"log of SM + bSM matrix element squared with Avv=1 /F");
		newT->Branch("ME_ggF1j_bSM_Avv2p5",		&ME_ggF1j_bSM_Avv2p5,	"log of bSM matrix element squared with Avv=2.5 /F");
		newT->Branch("ME_ggF1j_SMbSM_Avv2p5",	&ME_ggF1j_SMbSM_Avv2p5,	"log of SM + bSM matrix element squared with Avv=2.5 /F");
		newT->Branch("OO1_ggF1j_Avv1",			&OO1_ggF1j_Avv1,		"Optimal Observable 1 for ggF1j and Avv = 1 /F");
		newT->Branch("OO1_ggF1j_Avv2p5",		&OO1_ggF1j_Avv2p5,		"Optimal Observable 1 for ggF1j and Avv = 2.5 /F");
		newT->Branch("OO2_ggF1j_Avv1",			&OO2_ggF1j_Avv1,		"Optimal Observable 2 for ggF1j and Avv = 1 /F");
		newT->Branch("OO2_ggF1j_Avv2p5",		&OO2_ggF1j_Avv2p5,		"Optimal Observable 2 for ggF1j and Avv = 2.5 /F");
		
		int oldnEntries = oldT->GetEntries(); 
		cout << "Number of entries in original tree is " << oldnEntries << endl;
	
		vector<string> VBFVHListofCards;
  		VBFVHCardNames(&VBFVHListofCards);
  		vector<string> ggFListofCards;
  		ggFCardNames(&ggFListofCards);
  		string madgraphcard = "";
  		
  		try {
  			//list the processes that you want to try here
  			
  			//VBF
  			madgraphcard = VBFVHListofCards[0];
  			VBF_m_ud_udepemepem_SM = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem(); 
			VBF_m_ud_udepemepem_SM->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[1];
			VBF_m_ud_udepemepem_bSM_Hvv1 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem();
			VBF_m_ud_udepemepem_bSM_Hvv1->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[2];
			VBF_m_ud_udepemepem_SMbSM_Hvv1 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem();
			VBF_m_ud_udepemepem_SMbSM_Hvv1->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[3];
			VBF_m_ud_udepemepem_bSM_Hvv2p5 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem();
			VBF_m_ud_udepemepem_bSM_Hvv2p5->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[4];
			VBF_m_ud_udepemepem_SMbSM_Hvv2p5 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem();
			VBF_m_ud_udepemepem_SMbSM_Hvv2p5->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[5];
			VBF_m_ud_udepemepem_bSM_Avv1 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem();
			VBF_m_ud_udepemepem_bSM_Avv1->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[6];
			VBF_m_ud_udepemepem_SMbSM_Avv1 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem();
			VBF_m_ud_udepemepem_SMbSM_Avv1->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[7];
			VBF_m_ud_udepemepem_bSM_Avv2p5 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem();
			VBF_m_ud_udepemepem_bSM_Avv2p5->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[8];
			VBF_m_ud_udepemepem_SMbSM_Avv2p5 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_pp_Xjj_4l_HC_NLO_X0_UFO_ud_udepemepem();
			VBF_m_ud_udepemepem_SMbSM_Avv2p5->initProc(madgraphcard.c_str());

			
			//VH
  			madgraphcard = VBFVHListofCards[0];
  			VH_m_udxepemmupmum_SM = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum(); 
			VH_m_udxepemmupmum_SM->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[1];
			VH_m_udxepemmupmum_bSM_Hvv1 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum();
			VH_m_udxepemmupmum_bSM_Hvv1->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[2];
			VH_m_udxepemmupmum_SMbSM_Hvv1 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum();
			VH_m_udxepemmupmum_SMbSM_Hvv1->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[3];
			VH_m_udxepemmupmum_bSM_Hvv2p5 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum();
			VH_m_udxepemmupmum_bSM_Hvv2p5->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[4];
			VH_m_udxepemmupmum_SMbSM_Hvv2p5 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum();
			VH_m_udxepemmupmum_SMbSM_Hvv2p5->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[5];
			VH_m_udxepemmupmum_bSM_Avv1 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum();
			VH_m_udxepemmupmum_bSM_Avv1->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[6];
			VH_m_udxepemmupmum_SMbSM_Avv1 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum();
			VH_m_udxepemmupmum_SMbSM_Avv1->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[7];
			VH_m_udxepemmupmum_bSM_Avv2p5 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum();
			VH_m_udxepemmupmum_bSM_Avv2p5->initProc(madgraphcard.c_str());
			
			madgraphcard = VBFVHListofCards[8];
			VH_m_udxepemmupmum_SMbSM_Avv2p5 = new CPPProcess_P0_Sigma_HC_NLO_X0_UFO_VH_udx_udxepemmupmum();
			VH_m_udxepemmupmum_SMbSM_Avv2p5->initProc(madgraphcard.c_str());
			
			//ggF1j
			madgraphcard = ggFListofCards[0];
  			ggF1j_m_gg_epemepemg_SM = new CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg(); 
			ggF1j_m_gg_epemepemg_SM->initProc(madgraphcard.c_str());
			
			madgraphcard = ggFListofCards[1];
			ggF1j_m_gg_epemepemg_bSM_Hvv1 = new CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg();
			ggF1j_m_gg_epemepemg_bSM_Hvv1->initProc(madgraphcard.c_str());
			
			madgraphcard = ggFListofCards[2];
			ggF1j_m_gg_epemepemg_SMbSM_Hvv1 = new CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg();
			ggF1j_m_gg_epemepemg_SMbSM_Hvv1->initProc(madgraphcard.c_str());
			
			madgraphcard = ggFListofCards[3];
			ggF1j_m_gg_epemepemg_bSM_Hvv2p5 = new CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg();
			ggF1j_m_gg_epemepemg_bSM_Hvv2p5->initProc(madgraphcard.c_str());
			
			madgraphcard = ggFListofCards[4];
			ggF1j_m_gg_epemepemg_SMbSM_Hvv2p5 = new CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg();
			ggF1j_m_gg_epemepemg_SMbSM_Hvv2p5->initProc(madgraphcard.c_str());
			
			madgraphcard = ggFListofCards[5];
			ggF1j_m_gg_epemepemg_bSM_Avv1 = new CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg();
			ggF1j_m_gg_epemepemg_bSM_Avv1->initProc(madgraphcard.c_str());
			
			madgraphcard = ggFListofCards[6];
			ggF1j_m_gg_epemepemg_SMbSM_Avv1 = new CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg();
			ggF1j_m_gg_epemepemg_SMbSM_Avv1->initProc(madgraphcard.c_str());
			
			madgraphcard = ggFListofCards[7];
			ggF1j_m_gg_epemepemg_bSM_Avv2p5 = new CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg();
			ggF1j_m_gg_epemepemg_bSM_Avv2p5->initProc(madgraphcard.c_str());
			
			madgraphcard = ggFListofCards[8];
			ggF1j_m_gg_epemepemg_SMbSM_Avv2p5 = new CPPProcess_P0_Sigma_ggf_1jet_LO_HC_NLO_X0_UFO_heft_gg_epemepemg();
			ggF1j_m_gg_epemepemg_SMbSM_Avv2p5->initProc(madgraphcard.c_str());
			
		} catch (const char* e) {
		    cout << "Exception: " << e << " " <<  madgraphcard << endl;
		} 
	
		//form fermion vectors
		for (int iEnt = 0; iEnt < oldnEntries; iEnt++) {
		
			oldT->GetEntry(iEnt); 	
						
			if (n_jets != 0) {
				
				//Initialize numbers
				ME_VBF_SM = 0;
				ME_VBF_bSM_Hvv1 = 0;
				ME_VBF_SMbSM_Hvv1 = 0;
				ME_VBF_bSM_Hvv2p5 = 0; 
				ME_VBF_SMbSM_Hvv2p5 = 0;
				OO1_VBF_Hvv1 = 0;
				OO1_VBF_Hvv2p5 = 0;
				OO2_VBF_Hvv1 = 0;
				OO2_VBF_Hvv2p5 = 0;
				ME_VBF_bSM_Avv1 = 0;
				ME_VBF_SMbSM_Avv1 = 0;
				ME_VBF_bSM_Avv2p5 = 0; 
				ME_VBF_SMbSM_Avv2p5 = 0;
				OO1_VBF_Avv1 = 0;
				OO1_VBF_Avv2p5 = 0;
				OO2_VBF_Avv1 = 0;
				OO2_VBF_Avv2p5 = 0;
		
				ME_VH_SM = 0;
				ME_VH_bSM_Hvv1 = 0;
				ME_VH_SMbSM_Hvv1 = 0;
				ME_VH_bSM_Hvv2p5 = 0; 
				ME_VH_SMbSM_Hvv2p5 = 0;
				OO1_VH_Hvv1 = 0;
				OO1_VH_Hvv2p5 = 0;
				OO2_VH_Hvv1 = 0;
				OO2_VH_Hvv2p5 = 0;
				ME_VH_bSM_Avv1 = 0;
				ME_VH_SMbSM_Avv1 = 0;
				ME_VH_bSM_Avv2p5 = 0; 
				ME_VH_SMbSM_Avv2p5 = 0;
				OO1_VH_Avv1 = 0;
				OO1_VH_Avv2p5 = 0;
				OO2_VH_Avv1 = 0;
				OO2_VH_Avv2p5 = 0;
				
				ME_ggF1j_SM = 0;
				ME_ggF1j_bSM_Hvv1 = 0;
				ME_ggF1j_SMbSM_Hvv1 = 0;
				ME_ggF1j_bSM_Hvv2p5 = 0; 
				ME_ggF1j_SMbSM_Hvv2p5 = 0;
				OO1_ggF1j_Hvv1 = 0;
				OO1_ggF1j_Hvv2p5 = 0;
				OO2_ggF1j_Hvv1 = 0;
				OO2_ggF1j_Hvv2p5 = 0;
				ME_ggF1j_bSM_Avv1 = 0;
				ME_ggF1j_SMbSM_Avv1 = 0;
				ME_ggF1j_bSM_Avv2p5 = 0; 
				ME_ggF1j_SMbSM_Avv2p5 = 0;
				OO1_ggF1j_Avv1 = 0;
				OO1_ggF1j_Avv2p5 = 0;
				OO2_ggF1j_Avv1 = 0;
				OO2_ggF1j_Avv2p5 = 0;
			
				if (n_jets >=2) {
					//calculate the matrix elements here - hopefully I can put this into a function eventually
					
					vector<TLorentzVector> fermionvector = getFermionsVBFVH(jet_eta, jet_m, jet_phi, jet_pt, lepton_eta, lepton_m, lepton_phi, lepton_pt, n_jets);
					TLorentzVector cms, cms4l;
					//cout << "From return fermion vector " << (fermionvector.at(0)).Pt() << endl;
			
					for(unsigned i = 0 ; i < fermionvector.size() ; ++i) {
    					cms += fermionvector[i];
    				if( i > 1 ) cms4l += fermionvector[i];
  					}
					
					//VBF
					vector<float> mtxElem = ComputeMGME_cmsM4l(*VBF_m_ud_udepemepem_SM, fermionvector, cms, cms4l); //here is where the ME is calculated
					float logME = getlogME(mtxElem); //add and log the ME
					hME_VBF_SM->Fill(logME); //Fill the ME plot
					ME_VBF_SM = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VBF_m_ud_udepemepem_bSM_Hvv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VBF_bSM_Hvv1->Fill(logME); //Fill the ME plot
					ME_VBF_bSM_Hvv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VBF_m_ud_udepemepem_SMbSM_Hvv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VBF_SMbSM_Hvv1->Fill(logME); //Fill the ME plot
					ME_VBF_SMbSM_Hvv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VBF_m_ud_udepemepem_bSM_Hvv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VBF_bSM_Hvv2p5->Fill(logME); //Fill the ME plot
					ME_VBF_bSM_Hvv2p5 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VBF_m_ud_udepemepem_SMbSM_Hvv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VBF_SMbSM_Hvv2p5->Fill(logME); //Fill the ME plot
					ME_VBF_SMbSM_Hvv2p5 = logME;
					
					OO1_VBF_Hvv1 = log((exp(ME_VBF_SMbSM_Hvv1) - exp(ME_VBF_bSM_Hvv1) - exp(ME_VBF_SM))/exp(ME_VBF_SM));
					OO1_VBF_Hvv2p5 = log((exp(ME_VBF_SMbSM_Hvv2p5) - exp(ME_VBF_bSM_Hvv2p5) - exp(ME_VBF_SM))/exp(ME_VBF_SM));
					OO2_VBF_Hvv1 = log((exp(ME_VBF_bSM_Hvv1))/(exp(ME_VBF_SM)));
					OO2_VBF_Hvv2p5 = log((exp(ME_VBF_bSM_Hvv2p5))/(exp(ME_VBF_SM)));		
					
					if( isnan(OO1_VBF_Hvv1) )	OO1_VBF_Hvv1 = -999; 
   					if( isnan(OO1_VBF_Hvv2p5) ) OO1_VBF_Hvv2p5 = -999;
   					
   					hOO1_VBF_Hvv1->Fill(OO1_VBF_Hvv1);
					hOO2_VBF_Hvv1->Fill(OO2_VBF_Hvv1);
					hOO1_VBF_Hvv2p5->Fill(OO1_VBF_Hvv2p5);
					hOO2_VBF_Hvv2p5->Fill(OO2_VBF_Hvv2p5);
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VBF_m_ud_udepemepem_bSM_Avv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VBF_bSM_Avv1->Fill(logME); //Fill the ME plot
					ME_VBF_bSM_Avv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VBF_m_ud_udepemepem_SMbSM_Avv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VBF_SMbSM_Avv1->Fill(logME); //Fill the ME plot
					ME_VBF_SMbSM_Avv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VBF_m_ud_udepemepem_bSM_Avv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VBF_bSM_Avv2p5->Fill(logME); //Fill the ME plot
					ME_VBF_bSM_Avv2p5 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VBF_m_ud_udepemepem_SMbSM_Avv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VBF_SMbSM_Avv2p5->Fill(logME); //Fill the ME plot
					ME_VBF_SMbSM_Avv2p5 = logME;
					
					OO1_VBF_Avv1 = log((exp(ME_VBF_SMbSM_Avv1) - exp(ME_VBF_bSM_Avv1) - exp(ME_VBF_SM))/exp(ME_VBF_SM));
					OO1_VBF_Avv2p5 = log((exp(ME_VBF_SMbSM_Avv2p5) - exp(ME_VBF_bSM_Avv2p5) - exp(ME_VBF_SM))/exp(ME_VBF_SM));
					OO2_VBF_Avv1 = log((exp(ME_VBF_bSM_Avv1))/(exp(ME_VBF_SM)));
					OO2_VBF_Avv2p5 = log((exp(ME_VBF_bSM_Avv2p5))/(exp(ME_VBF_SM)));		
					
					if( isnan(OO1_VBF_Avv1) )	OO1_VBF_Avv1 = -999; 
   					if( isnan(OO1_VBF_Avv2p5) ) OO1_VBF_Avv2p5 = -999;
   					
   					hOO1_VBF_Avv1->Fill(OO1_VBF_Avv1);
					hOO2_VBF_Avv1->Fill(OO2_VBF_Avv1);
					hOO1_VBF_Avv2p5->Fill(OO1_VBF_Avv2p5);
					hOO2_VBF_Avv2p5->Fill(OO2_VBF_Avv2p5);
					
					mtxElem.clear();
					
					//VH
					 mtxElem = ComputeMGME_cmsM4l(*VH_m_udxepemmupmum_SM, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VH_SM->Fill(logME); //Fill the ME plot
					ME_VH_SM = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VH_m_udxepemmupmum_bSM_Hvv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VH_bSM_Hvv1->Fill(logME); //Fill the ME plot
					ME_VH_bSM_Hvv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VH_m_udxepemmupmum_SMbSM_Hvv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VH_SMbSM_Hvv1->Fill(logME); //Fill the ME plot
					ME_VH_SMbSM_Hvv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VH_m_udxepemmupmum_bSM_Hvv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VH_bSM_Hvv2p5->Fill(logME); //Fill the ME plot
					ME_VH_bSM_Hvv2p5 = logME;				
	
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VH_m_udxepemmupmum_SMbSM_Hvv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VH_SMbSM_Hvv2p5->Fill(logME); //Fill the ME plot
					ME_VH_SMbSM_Hvv2p5 = logME;
					
					OO1_VH_Hvv1 = log((exp(ME_VH_SMbSM_Hvv1) - exp(ME_VH_bSM_Hvv1) - exp(ME_VH_SM))/exp(ME_VH_SM));
					OO1_VH_Hvv2p5 = log((exp(ME_VH_SMbSM_Hvv2p5) - exp(ME_VH_bSM_Hvv2p5) - exp(ME_VH_SM))/exp(ME_VH_SM));
					OO2_VH_Hvv1 = log((exp(ME_VH_bSM_Hvv1))/(exp(ME_VH_SM)));
					OO2_VH_Hvv2p5 = log((exp(ME_VH_bSM_Hvv2p5))/(exp(ME_VH_SM)));	
					
					if( isnan(OO1_VH_Hvv1) )	OO1_VH_Hvv1 = -999; 
   					if( isnan(OO1_VH_Hvv2p5) ) OO1_VH_Hvv2p5 = -999;	
   					
   					hOO1_VH_Hvv1->Fill(OO1_VH_Hvv1);
					hOO2_VH_Hvv1->Fill(OO2_VH_Hvv1);
					hOO1_VH_Hvv2p5->Fill(OO1_VH_Hvv2p5);
					hOO2_VH_Hvv2p5->Fill(OO2_VH_Hvv2p5);					

					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VH_m_udxepemmupmum_bSM_Avv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VH_bSM_Avv1->Fill(logME); //Fill the ME plot
					ME_VH_bSM_Avv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VH_m_udxepemmupmum_SMbSM_Avv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VH_SMbSM_Avv1->Fill(logME); //Fill the ME plot
					ME_VH_SMbSM_Avv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VH_m_udxepemmupmum_bSM_Avv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VH_bSM_Avv2p5->Fill(logME); //Fill the ME plot
					ME_VH_bSM_Avv2p5 = logME;				
	
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*VH_m_udxepemmupmum_SMbSM_Avv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_VH_SMbSM_Avv2p5->Fill(logME); //Fill the ME plot
					ME_VH_SMbSM_Avv2p5 = logME;
					
					OO1_VH_Avv1 = log((exp(ME_VH_SMbSM_Avv1) - exp(ME_VH_bSM_Avv1) - exp(ME_VH_SM))/exp(ME_VH_SM));
					OO1_VH_Avv2p5 = log((exp(ME_VH_SMbSM_Avv2p5) - exp(ME_VH_bSM_Avv2p5) - exp(ME_VH_SM))/exp(ME_VH_SM));
					OO2_VH_Avv1 = log((exp(ME_VH_bSM_Avv1))/(exp(ME_VH_SM)));
					OO2_VH_Avv2p5 = log((exp(ME_VH_bSM_Avv2p5))/(exp(ME_VH_SM)));	
					
					if( isnan(OO1_VH_Avv1) )	OO1_VH_Avv1 = -999; 
   					if( isnan(OO1_VH_Avv2p5) ) OO1_VH_Avv2p5 = -999;	
   					
   					hOO1_VH_Avv1->Fill(OO1_VH_Avv1);
					hOO2_VH_Avv1->Fill(OO2_VH_Avv1);
					hOO1_VH_Avv2p5->Fill(OO1_VH_Avv2p5);
					hOO2_VH_Avv2p5->Fill(OO2_VH_Avv2p5);					

						
				} //end of 2 jet block
			
				if (n_jets >=1) {
				
					vector<TLorentzVector> fermionvector = getFermionsggF1j(jet_eta, jet_m, jet_phi, jet_pt, lepton_eta, lepton_m, lepton_phi, lepton_pt, n_jets);
					TLorentzVector cms, cms4l;
					//cout << "From return fermion vector " << (fermionvector.at(0)).Pt() << endl;
			
					for(unsigned i = 0 ; i < fermionvector.size() ; ++i) {
    					cms += fermionvector[i];
    				if( i < 4 ) cms4l += fermionvector[i];
  					}
 					
					//ggF1j
					vector<float> mtxElem = ComputeMGME_cmsM4l(*ggF1j_m_gg_epemepemg_SM, fermionvector, cms, cms4l); //here is where the ME is calculated
					float logME = getlogME(mtxElem); //add and log the ME
					hME_ggF1j_SM->Fill(logME); //Fill the ME plot
					ME_ggF1j_SM = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*ggF1j_m_gg_epemepemg_bSM_Hvv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_ggF1j_bSM_Hvv1->Fill(logME); //Fill the ME plot
					ME_ggF1j_bSM_Hvv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*ggF1j_m_gg_epemepemg_SMbSM_Hvv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_ggF1j_SMbSM_Hvv1->Fill(logME); //Fill the ME plot
					ME_ggF1j_SMbSM_Hvv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*ggF1j_m_gg_epemepemg_bSM_Hvv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_ggF1j_bSM_Hvv2p5->Fill(logME); //Fill the ME plot
					ME_ggF1j_bSM_Hvv2p5 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*ggF1j_m_gg_epemepemg_SMbSM_Hvv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_ggF1j_SMbSM_Hvv2p5->Fill(logME); //Fill the ME plot
					ME_ggF1j_SMbSM_Hvv2p5 = logME;
					
					OO1_ggF1j_Hvv1 = log((exp(ME_ggF1j_SMbSM_Hvv1) - exp(ME_ggF1j_bSM_Hvv1) - exp(ME_ggF1j_SM))/exp(ME_ggF1j_SM));
					OO1_ggF1j_Hvv2p5 = log((exp(ME_ggF1j_SMbSM_Hvv2p5) - exp(ME_ggF1j_bSM_Hvv2p5) - exp(ME_ggF1j_SM))/exp(ME_ggF1j_SM));
					OO2_ggF1j_Hvv1 = log((exp(ME_ggF1j_bSM_Hvv1))/(exp(ME_ggF1j_SM)));
					OO2_ggF1j_Hvv2p5 = log((exp(ME_ggF1j_bSM_Hvv2p5))/(exp(ME_ggF1j_SM)));	
					
					if( isnan(OO1_ggF1j_Hvv1) )	OO1_ggF1j_Hvv1 = -999; 
   					if( isnan(OO1_ggF1j_Hvv2p5) ) OO1_ggF1j_Hvv2p5 = -999;	
		
					hOO1_ggF1j_Hvv1->Fill(OO1_ggF1j_Hvv1);
					hOO2_ggF1j_Hvv1->Fill(OO2_ggF1j_Hvv1);
					hOO1_ggF1j_Hvv2p5->Fill(OO1_ggF1j_Hvv2p5);
					hOO2_ggF1j_Hvv2p5->Fill(OO2_ggF1j_Hvv2p5);
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*ggF1j_m_gg_epemepemg_bSM_Avv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_ggF1j_bSM_Avv1->Fill(logME); //Fill the ME plot
					ME_ggF1j_bSM_Avv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*ggF1j_m_gg_epemepemg_SMbSM_Avv1, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_ggF1j_SMbSM_Avv1->Fill(logME); //Fill the ME plot
					ME_ggF1j_SMbSM_Avv1 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*ggF1j_m_gg_epemepemg_bSM_Avv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_ggF1j_bSM_Avv2p5->Fill(logME); //Fill the ME plot
					ME_ggF1j_bSM_Avv2p5 = logME;
					
					mtxElem.clear();
					
					mtxElem = ComputeMGME_cmsM4l(*ggF1j_m_gg_epemepemg_SMbSM_Avv2p5, fermionvector, cms, cms4l); //here is where the ME is calculated
					logME = getlogME(mtxElem); //add and log the ME
					hME_ggF1j_SMbSM_Avv2p5->Fill(logME); //Fill the ME plot
					ME_ggF1j_SMbSM_Avv2p5 = logME;
					
					OO1_ggF1j_Avv1 = log((exp(ME_ggF1j_SMbSM_Avv1) - exp(ME_ggF1j_bSM_Avv1) - exp(ME_ggF1j_SM))/exp(ME_ggF1j_SM));
					OO1_ggF1j_Avv2p5 = log((exp(ME_ggF1j_SMbSM_Avv2p5) - exp(ME_ggF1j_bSM_Avv2p5) - exp(ME_ggF1j_SM))/exp(ME_ggF1j_SM));
					OO2_ggF1j_Avv1 = log((exp(ME_ggF1j_bSM_Avv1))/(exp(ME_ggF1j_SM)));
					OO2_ggF1j_Avv2p5 = log((exp(ME_ggF1j_bSM_Avv2p5))/(exp(ME_ggF1j_SM)));	
					
					if( isnan(OO1_ggF1j_Avv1) )	OO1_ggF1j_Avv1 = -999; 
   					if( isnan(OO1_ggF1j_Avv2p5) ) OO1_ggF1j_Avv2p5 = -999;	
		
					hOO1_ggF1j_Avv1->Fill(OO1_ggF1j_Avv1);
					hOO2_ggF1j_Avv1->Fill(OO2_ggF1j_Avv1);
					hOO1_ggF1j_Avv2p5->Fill(OO1_ggF1j_Avv2p5);
					hOO2_ggF1j_Avv2p5->Fill(OO2_ggF1j_Avv2p5);

		
				} //end of 1 jet block
				
				if (n_jets < 2) {
				
					ME_VBF_SM = -999;	
					ME_VBF_bSM_Hvv1 = -999;
					ME_VBF_SMbSM_Hvv1 = -999;
					OO1_VBF_Hvv1 = -999;
	    			OO2_VBF_Hvv1 = -999;
					ME_VBF_bSM_Hvv2p5 = -999;
					ME_VBF_SMbSM_Hvv2p5 = -999;
					OO1_VBF_Hvv2p5 = -999;
					OO2_VBF_Hvv2p5 = -999;	
					ME_VBF_bSM_Avv1 = -999;
					ME_VBF_SMbSM_Avv1 = -999;
					OO1_VBF_Avv1 = -999;
	    			OO2_VBF_Avv1 = -999;
					ME_VBF_bSM_Avv2p5 = -999;
					ME_VBF_SMbSM_Avv2p5 = -999;
					OO1_VBF_Avv2p5 = -999;
					OO2_VBF_Avv2p5 = -999;	
			
					ME_VH_SM = -999;	
					ME_VH_bSM_Hvv1 = -999;
					ME_VH_SMbSM_Hvv1 = -999;
					OO1_VH_Hvv1 = -999;
	    			OO2_VH_Hvv1 = -999;
					ME_VH_bSM_Hvv2p5 = -999;
					ME_VH_SMbSM_Hvv2p5 = -999;
					OO1_VH_Hvv2p5 = -999;
					OO2_VH_Hvv2p5 = -999;	
					ME_VH_bSM_Avv1 = -999;
					ME_VH_SMbSM_Avv1 = -999;
					OO1_VH_Avv1 = -999;
	    			OO2_VH_Avv1 = -999;
					ME_VH_bSM_Avv2p5 = -999;
					ME_VH_SMbSM_Avv2p5 = -999;
					OO1_VH_Avv2p5 = -999;
					OO2_VH_Avv2p5 = -999;	
		
				}
					
			} //end of !=0 jet block
			else {
					ME_VBF_SM = -999;	
					ME_VBF_bSM_Hvv1 = -999;
					ME_VBF_SMbSM_Hvv1 = -999;
					OO1_VBF_Hvv1 = -999;
	    			OO2_VBF_Hvv1 = -999;
					ME_VBF_bSM_Hvv2p5 = -999;
					ME_VBF_SMbSM_Hvv2p5 = -999;
					OO1_VBF_Hvv2p5 = -999;
					OO2_VBF_Hvv2p5 = -999;	
					ME_VBF_bSM_Avv1 = -999;
					ME_VBF_SMbSM_Avv1 = -999;
					OO1_VBF_Avv1 = -999;
	    			OO2_VBF_Avv1 = -999;
					ME_VBF_bSM_Avv2p5 = -999;
					ME_VBF_SMbSM_Avv2p5 = -999;
					OO1_VBF_Avv2p5 = -999;
					OO2_VBF_Avv2p5 = -999;	
			
					ME_VH_SM = -999;	
					ME_VH_bSM_Hvv1 = -999;
					ME_VH_SMbSM_Hvv1 = -999;
					OO1_VH_Hvv1 = -999;
	    			OO2_VH_Hvv1 = -999;
					ME_VH_bSM_Hvv2p5 = -999;
					ME_VH_SMbSM_Hvv2p5 = -999;
					OO1_VH_Hvv2p5 = -999;
					OO2_VH_Hvv2p5 = -999;	
					ME_VH_bSM_Avv1 = -999;
					ME_VH_SMbSM_Avv1 = -999;
					OO1_VH_Avv1 = -999;
	    			OO2_VH_Avv1 = -999;
					ME_VH_bSM_Avv2p5 = -999;
					ME_VH_SMbSM_Avv2p5 = -999;
					OO1_VH_Avv2p5 = -999;
					OO2_VH_Avv2p5 = -999;	
					
					ME_ggF1j_SM = -999;	
					ME_ggF1j_bSM_Hvv1 = -999;
					ME_ggF1j_SMbSM_Hvv1 = -999;
					OO1_ggF1j_Hvv1 = -999;
	    			OO2_ggF1j_Hvv1 = -999;
					ME_ggF1j_bSM_Hvv2p5 = -999;
					ME_ggF1j_SMbSM_Hvv2p5 = -999;
					OO1_ggF1j_Hvv2p5 = -999;
					OO2_ggF1j_Hvv2p5 = -999;
					ME_ggF1j_bSM_Avv1 = -999;
					ME_ggF1j_SMbSM_Avv1 = -999;
					OO1_ggF1j_Avv1 = -999;
	    			OO2_ggF1j_Avv1 = -999;
					ME_ggF1j_bSM_Avv2p5 = -999;
					ME_ggF1j_SMbSM_Avv2p5 = -999;
					OO1_ggF1j_Avv2p5 = -999;
					OO2_ggF1j_Avv2p5 = -999;	
			}	
			
			newT->Fill();		
						
		} //end of iEnt
		
		newfile->Write();
		
		TLegend *Legend_VBF_Hvv1 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_VBF_Hvv1->AddEntry(hME_VBF_SM, "VBF SM", "f");    	
		Legend_VBF_Hvv1->AddEntry(hME_VBF_bSM_Hvv1, "VBF k_{Hvv} = 1", "f");
		Legend_VBF_Hvv1->AddEntry(hME_VBF_SMbSM_Hvv1, "VBF SM+k_{Hvv} = 1", "f");

		TLegend *Legend_VBF_Hvv2p5 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_VBF_Hvv2p5->AddEntry(hME_VBF_SM, "VBF SM", "f");    	
		Legend_VBF_Hvv2p5->AddEntry(hME_VBF_bSM_Hvv2p5, "VBF k_{Hvv} = 2.5", "f");
		Legend_VBF_Hvv2p5->AddEntry(hME_VBF_SMbSM_Hvv2p5, "VBF SM+k_{Hvv} = 2.5", "f");
		
		TLegend *Legend_VH_Hvv1 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_VH_Hvv1->AddEntry(hME_VH_SM, "VH SM", "f");    	
		Legend_VH_Hvv1->AddEntry(hME_VH_bSM_Hvv1, "VH k_{Hvv} = 1", "f");
		Legend_VH_Hvv1->AddEntry(hME_VH_SMbSM_Hvv1, "VH SM+k_{Hvv} = 1", "f");

		TLegend *Legend_VH_Hvv2p5 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_VH_Hvv2p5->AddEntry(hME_VH_SM, "VH SM", "f");    	
		Legend_VH_Hvv2p5->AddEntry(hME_VH_bSM_Hvv2p5, "VH k_{Hvv} = 2.5", "f");
		Legend_VH_Hvv2p5->AddEntry(hME_VH_SMbSM_Hvv2p5, "VH SM+k_{Hvv} = 2.5", "f");
		
		TLegend *Legend_ggF1j_Hvv1 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_ggF1j_Hvv1->AddEntry(hME_ggF1j_SM, "ggF1j SM", "f");    	
		Legend_ggF1j_Hvv1->AddEntry(hME_ggF1j_bSM_Hvv1, "ggF1j k_{Hvv} = 1", "f");
		Legend_ggF1j_Hvv1->AddEntry(hME_ggF1j_SMbSM_Hvv1, "ggF1j SM+k_{Hvv} = 1", "f");

		TLegend *Legend_ggF1j_Hvv2p5 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_ggF1j_Hvv2p5->AddEntry(hME_ggF1j_SM, "ggF1j SM", "f");    	
		Legend_ggF1j_Hvv2p5->AddEntry(hME_ggF1j_bSM_Hvv2p5, "ggF1j k_{Hvv} = 2.5", "f");
		Legend_ggF1j_Hvv2p5->AddEntry(hME_ggF1j_SMbSM_Hvv2p5, "ggF1j SM+k_{Hvv} = 2.5", "f");
		
		TLegend *Legend_VBF_Avv1 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_VBF_Avv1->AddEntry(hME_VBF_SM, "VBF SM", "f");    	
		Legend_VBF_Avv1->AddEntry(hME_VBF_bSM_Avv1, "VBF k_{Avv} = 1", "f");
		Legend_VBF_Avv1->AddEntry(hME_VBF_SMbSM_Avv1, "VBF SM+k_{Avv} = 1", "f");

		TLegend *Legend_VBF_Avv2p5 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_VBF_Avv2p5->AddEntry(hME_VBF_SM, "VBF SM", "f");    	
		Legend_VBF_Avv2p5->AddEntry(hME_VBF_bSM_Avv2p5, "VBF k_{Avv} = 2.5", "f");
		Legend_VBF_Avv2p5->AddEntry(hME_VBF_SMbSM_Avv2p5, "VBF SM+k_{Avv} = 2.5", "f");
		
		TLegend *Legend_VH_Avv1 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_VH_Avv1->AddEntry(hME_VH_SM, "VH SM", "f");    	
		Legend_VH_Avv1->AddEntry(hME_VH_bSM_Avv1, "VH k_{Avv} = 1", "f");
		Legend_VH_Avv1->AddEntry(hME_VH_SMbSM_Avv1, "VH SM+k_{Avv} = 1", "f");

		TLegend *Legend_VH_Avv2p5 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_VH_Avv2p5->AddEntry(hME_VH_SM, "VH SM", "f");    	
		Legend_VH_Avv2p5->AddEntry(hME_VH_bSM_Avv2p5, "VH k_{Avv} = 2.5", "f");
		Legend_VH_Avv2p5->AddEntry(hME_VH_SMbSM_Avv2p5, "VH SM+k_{Avv} = 2.5", "f");
		
		TLegend *Legend_ggF1j_Avv1 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_ggF1j_Avv1->AddEntry(hME_ggF1j_SM, "ggF1j SM", "f");    	
		Legend_ggF1j_Avv1->AddEntry(hME_ggF1j_bSM_Avv1, "ggF1j k_{Avv} = 1", "f");
		Legend_ggF1j_Avv1->AddEntry(hME_ggF1j_SMbSM_Avv1, "ggF1j SM+k_{Avv} = 1", "f");

		TLegend *Legend_ggF1j_Avv2p5 =  new TLegend (0.605, 0.75, 0.90, 0.925);
		Legend_ggF1j_Avv2p5->AddEntry(hME_ggF1j_SM, "ggF1j SM", "f");    	
		Legend_ggF1j_Avv2p5->AddEntry(hME_ggF1j_bSM_Avv2p5, "ggF1j k_{Avv} = 2.5", "f");
		Legend_ggF1j_Avv2p5->AddEntry(hME_ggF1j_SMbSM_Avv2p5, "ggF1j SM+k_{Avv} = 2.5", "f");
		
		//Plots for ME and OO variables
		//VBF
		TCanvas* cME = new TCanvas();
		hME_VBF_SM->Scale(1/hME_VBF_SM->Integral()); 
		hME_VBF_SM->Draw();
		cME->Print("plots/reco/VBF_SM/"+filename+"_VBF_ME_SM.pdf"); 
		
		hME_VBF_bSM_Hvv1->Scale(1/hME_VBF_bSM_Hvv1->Integral()); 
		hME_VBF_bSM_Hvv1->Draw();
		cME->Print("plots/reco/VBF_bSM/"+filename+"_VBF_ME_bSM_Hvv1.pdf"); 
		
		hME_VBF_SMbSM_Hvv1->Scale(1/hME_VBF_SMbSM_Hvv1->Integral()); 
		hME_VBF_SMbSM_Hvv1->Draw();
		cME->Print("plots/reco/VBF_SMbSM/"+filename+"_VBF_ME_SMbSM_Hvv1.pdf"); 
		
		TCanvas* cME_compare = new TCanvas();
		hME_VBF_SM->SetMaximum(0.5);
		hME_VBF_SM->Draw();
		hME_VBF_bSM_Hvv1->SetLineColor(kRed);
		hME_VBF_bSM_Hvv1->Draw("same");
		hME_VBF_SMbSM_Hvv1->SetLineColor(kGreen);
		hME_VBF_SMbSM_Hvv1->Draw("same");
		Legend_VBF_Hvv1->Draw("same");
		cME_compare->Print("plots/reco/VBF_compare/"+filename+"_VBF_ME_compare_Hvv1.pdf");
		
		cME->cd();
		hME_VBF_bSM_Hvv2p5->Scale(1/hME_VBF_bSM_Hvv2p5->Integral()); 
		hME_VBF_bSM_Hvv2p5->Draw();
		cME->Print("plots/reco/VBF_bSM/"+filename+"_VBF_ME_bSM_Hvv2p5.pdf"); 
		
		hME_VBF_SMbSM_Hvv2p5->Scale(1/hME_VBF_SMbSM_Hvv2p5->Integral()); 
		hME_VBF_SMbSM_Hvv2p5->Draw();
		cME->Print("plots/reco/VBF_SMbSM/"+filename+"_VBF_ME_SMbSM_Hvv2p5.pdf"); 
		
		cME_compare->cd();
		hME_VBF_SM->SetMaximum(0.5);
		hME_VBF_SM->Draw();
		hME_VBF_bSM_Hvv2p5->SetLineColor(kRed);
		hME_VBF_bSM_Hvv2p5->Draw("same");
		hME_VBF_SMbSM_Hvv2p5->SetLineColor(kGreen);
		hME_VBF_SMbSM_Hvv2p5->Draw("same");
		Legend_VBF_Hvv2p5->Draw("same");
		cME_compare->Print("plots/reco/VBF_compare/"+filename+"_VBF_ME_compare_Hvv2p5.pdf");
		
		TCanvas* cOO = new TCanvas();
		hOO1_VBF_Hvv1->Scale(1/hOO1_VBF_Hvv1->Integral());
		hOO1_VBF_Hvv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VBF_OO1_Hvv1.pdf");
		
		hOO2_VBF_Hvv1->Scale(1/hOO1_VBF_Hvv1->Integral());
		hOO2_VBF_Hvv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VBF_OO2_Hvv1.pdf");
		
		hOO1_VBF_Hvv2p5->Scale(1/hOO1_VBF_Hvv2p5->Integral());
		hOO1_VBF_Hvv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VBF_OO1_Hvv2p5.pdf");
		
		hOO2_VBF_Hvv2p5->Scale(1/hOO1_VBF_Hvv2p5->Integral());
		hOO2_VBF_Hvv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VBF_OO2_Hvv2p5.pdf");
		
		hME_VBF_bSM_Avv1->Scale(1/hME_VBF_bSM_Avv1->Integral()); 
		hME_VBF_bSM_Avv1->Draw();
		cME->Print("plots/reco/VBF_bSM/"+filename+"_VBF_ME_bSM_Avv1.pdf"); 
		
		hME_VBF_SMbSM_Avv1->Scale(1/hME_VBF_SMbSM_Avv1->Integral()); 
		hME_VBF_SMbSM_Avv1->Draw();
		cME->Print("plots/reco/VBF_SMbSM/"+filename+"_VBF_ME_SMbSM_Avv1.pdf"); 
		
		cME_compare->cd();
		hME_VBF_SM->SetMaximum(0.5);
		hME_VBF_SM->Draw();
		hME_VBF_bSM_Avv1->SetLineColor(kRed);
		hME_VBF_bSM_Avv1->Draw("same");
		hME_VBF_SMbSM_Avv1->SetLineColor(kGreen);
		hME_VBF_SMbSM_Avv1->Draw("same");
		Legend_VBF_Avv1->Draw("same");
		cME_compare->Print("plots/reco/VBF_compare/"+filename+"_VBF_ME_compare_Avv1.pdf");
		
		cME->cd();
		hME_VBF_bSM_Avv2p5->Scale(1/hME_VBF_bSM_Avv2p5->Integral()); 
		hME_VBF_bSM_Avv2p5->Draw();
		cME->Print("plots/reco/VBF_bSM/"+filename+"_VBF_ME_bSM_Avv2p5.pdf"); 
		
		hME_VBF_SMbSM_Avv2p5->Scale(1/hME_VBF_SMbSM_Avv2p5->Integral()); 
		hME_VBF_SMbSM_Avv2p5->Draw();
		cME->Print("plots/reco/VBF_SMbSM/"+filename+"_VBF_ME_SMbSM_Avv2p5.pdf"); 
		
		cME_compare->cd();
		hME_VBF_SM->SetMaximum(0.5);
		hME_VBF_SM->Draw();
		hME_VBF_bSM_Avv2p5->SetLineColor(kRed);
		hME_VBF_bSM_Avv2p5->Draw("same");
		hME_VBF_SMbSM_Avv2p5->SetLineColor(kGreen);
		hME_VBF_SMbSM_Avv2p5->Draw("same");
		Legend_VBF_Avv2p5->Draw("same");
		cME_compare->Print("plots/reco/VBF_compare/"+filename+"_VBF_ME_compare_Avv2p5.pdf");
		
		cOO->cd();
		hOO1_VBF_Avv1->Scale(1/hOO1_VBF_Avv1->Integral());
		hOO1_VBF_Avv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VBF_OO1_Avv1.pdf");
		
		hOO2_VBF_Avv1->Scale(1/hOO1_VBF_Avv1->Integral());
		hOO2_VBF_Avv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VBF_OO2_Avv1.pdf");
		
		hOO1_VBF_Avv2p5->Scale(1/hOO1_VBF_Avv2p5->Integral());
		hOO1_VBF_Avv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VBF_OO1_Avv2p5.pdf");
		
		hOO2_VBF_Avv2p5->Scale(1/hOO1_VBF_Avv2p5->Integral());
		hOO2_VBF_Avv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VBF_OO2_Avv2p5.pdf");

		
		//VH
		cME->cd();
		hME_VH_SM->Scale(1/hME_VH_SM->Integral()); 
		hME_VH_SM->Draw();
		cME->Print("plots/reco/VH_SM/"+filename+"_VH_ME_SM.pdf"); 
		
		hME_VH_bSM_Hvv1->Scale(1/hME_VH_bSM_Hvv1->Integral()); 
		hME_VH_bSM_Hvv1->Draw();
		cME->Print("plots/reco/VH_bSM/"+filename+"_VH_ME_bSM_Hvv1.pdf"); 
		
		hME_VH_SMbSM_Hvv1->Scale(1/hME_VH_SMbSM_Hvv1->Integral()); 
		hME_VH_SMbSM_Hvv1->Draw();
		cME->Print("plots/reco/VH_SMbSM/"+filename+"_VH_ME_SMbSM_Hvv1.pdf"); 
		
		cME_compare->cd();
		hME_VH_SM->SetMaximum(0.5);
		hME_VH_SM->Draw();
		hME_VH_bSM_Hvv1->SetLineColor(kRed);
		hME_VH_bSM_Hvv1->Draw("same");
		hME_VH_SMbSM_Hvv1->SetLineColor(kGreen);
		hME_VH_SMbSM_Hvv1->Draw("same");
		Legend_VH_Hvv1->Draw("same");
		cME_compare->Print("plots/reco/VH_compare/"+filename+"_VH_ME_compare_Hvv1.pdf");
		
		cME->cd();
		hME_VH_bSM_Hvv2p5->Scale(1/hME_VH_bSM_Hvv2p5->Integral()); 
		hME_VH_bSM_Hvv2p5->Draw();
		cME->Print("plots/reco/VH_bSM/"+filename+"_VH_ME_bSM_Hvv2p5.pdf"); 
		
		hME_VH_SMbSM_Hvv2p5->Scale(1/hME_VH_SMbSM_Hvv2p5->Integral()); 
		hME_VH_SMbSM_Hvv2p5->Draw();
		cME->Print("plots/reco/VH_SMbSM/"+filename+"_VH_ME_SMbSM_Hvv2p5.pdf"); 
		
		cME_compare->cd();
		hME_VH_SM->SetMaximum(0.5);
		hME_VH_SM->Draw();
		hME_VH_bSM_Hvv2p5->SetLineColor(kRed);
		hME_VH_bSM_Hvv2p5->Draw("same");
		hME_VH_SMbSM_Hvv2p5->SetLineColor(kGreen);
		hME_VH_SMbSM_Hvv2p5->Draw("same");
		Legend_VH_Hvv2p5->Draw("same");
		cME_compare->Print("plots/reco/VH_compare/"+filename+"_VH_ME_compare_Hvv2p5.pdf");
		
		cOO->cd();
		hOO1_VH_Hvv1->Scale(1/hOO1_VH_Hvv1->Integral());
		hOO1_VH_Hvv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VH_OO1_Hvv1.pdf");
		
		hOO2_VH_Hvv1->Scale(1/hOO1_VH_Hvv1->Integral());
		hOO2_VH_Hvv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VH_OO2_Hvv1.pdf");
		
		hOO1_VH_Hvv2p5->Scale(1/hOO1_VH_Hvv2p5->Integral());
		hOO1_VH_Hvv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VH_OO1_Hvv2p5.pdf");
		
		hOO2_VH_Hvv2p5->Scale(1/hOO1_VH_Hvv2p5->Integral());
		hOO2_VH_Hvv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VH_OO2_Hvv2p5.pdf");

		hME_VH_bSM_Avv1->Scale(1/hME_VH_bSM_Avv1->Integral()); 
		hME_VH_bSM_Avv1->Draw();
		cME->Print("plots/reco/VH_bSM/"+filename+"_VH_ME_bSM_Avv1.pdf"); 
		
		hME_VH_SMbSM_Avv1->Scale(1/hME_VH_SMbSM_Avv1->Integral()); 
		hME_VH_SMbSM_Avv1->Draw();
		cME->Print("plots/reco/VH_SMbSM/"+filename+"_VH_ME_SMbSM_Avv1.pdf"); 
		
		cME_compare->cd();
		hME_VH_SM->SetMaximum(0.5);
		hME_VH_SM->Draw();
		hME_VH_bSM_Avv1->SetLineColor(kRed);
		hME_VH_bSM_Avv1->Draw("same");
		hME_VH_SMbSM_Avv1->SetLineColor(kGreen);
		hME_VH_SMbSM_Avv1->Draw("same");
		Legend_VH_Avv1->Draw("same");
		cME_compare->Print("plots/reco/VH_compare/"+filename+"_VH_ME_compare_Avv1.pdf");
		
		cME->cd();
		hME_VH_bSM_Avv2p5->Scale(1/hME_VH_bSM_Avv2p5->Integral()); 
		hME_VH_bSM_Avv2p5->Draw();
		cME->Print("plots/reco/VH_bSM/"+filename+"_VH_ME_bSM_Avv2p5.pdf"); 
		
		hME_VH_SMbSM_Avv2p5->Scale(1/hME_VH_SMbSM_Avv2p5->Integral()); 
		hME_VH_SMbSM_Avv2p5->Draw();
		cME->Print("plots/reco/VH_SMbSM/"+filename+"_VH_ME_SMbSM_Avv2p5.pdf"); 
		
		cME_compare->cd();
		hME_VH_SM->SetMaximum(0.5);
		hME_VH_SM->Draw();
		hME_VH_bSM_Avv2p5->SetLineColor(kRed);
		hME_VH_bSM_Avv2p5->Draw("same");
		hME_VH_SMbSM_Avv2p5->SetLineColor(kGreen);
		hME_VH_SMbSM_Avv2p5->Draw("same");
		Legend_VH_Avv2p5->Draw("same");
		cME_compare->Print("plots/reco/VH_compare/"+filename+"_VH_ME_compare_Avv2p5.pdf");
		
		cOO->cd();
		hOO1_VH_Avv1->Scale(1/hOO1_VH_Avv1->Integral());
		hOO1_VH_Avv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VH_OO1_Avv1.pdf");
		
		hOO2_VH_Avv1->Scale(1/hOO1_VH_Avv1->Integral());
		hOO2_VH_Avv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VH_OO2_Avv1.pdf");
		
		hOO1_VH_Avv2p5->Scale(1/hOO1_VH_Avv2p5->Integral());
		hOO1_VH_Avv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VH_OO1_Avv2p5.pdf");
		
		hOO2_VH_Avv2p5->Scale(1/hOO1_VH_Avv2p5->Integral());
		hOO2_VH_Avv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_VH_OO2_Avv2p5.pdf");

		
		//ggF1j
		cME->cd();
		hME_ggF1j_SM->Scale(1/hME_ggF1j_SM->Integral()); 
		hME_ggF1j_SM->Draw();
		cME->Print("plots/reco/ggF1j_SM/"+filename+"_ggF1j_ME_SM.pdf"); 
		
		hME_ggF1j_bSM_Hvv1->Scale(1/hME_ggF1j_bSM_Hvv1->Integral()); 
		hME_ggF1j_bSM_Hvv1->Draw();
		cME->Print("plots/reco/ggF1j_bSM/"+filename+"_ggF1j_ME_bSM_Hvv1.pdf"); 
		
		hME_ggF1j_SMbSM_Hvv1->Scale(1/hME_ggF1j_SMbSM_Hvv1->Integral()); 
		hME_ggF1j_SMbSM_Hvv1->Draw();
		cME->Print("plots/reco/ggF1j_SMbSM/"+filename+"_ggF1j_ME_SMbSM_Hvv1.pdf"); 
		
 		cME_compare->cd();
 		hME_ggF1j_SM->SetMaximum(0.5);
		hME_ggF1j_SM->Draw();
		hME_ggF1j_bSM_Hvv1->SetLineColor(kRed);
		hME_ggF1j_bSM_Hvv1->Draw("same");
		hME_ggF1j_SMbSM_Hvv1->SetLineColor(kGreen);
		hME_ggF1j_SMbSM_Hvv1->Draw("same");
		Legend_ggF1j_Hvv1->Draw("same");
		cME_compare->Print("plots/reco/ggF1j_compare/"+filename+"_ggF1j_ME_compare_Hvv1.pdf");
		
		cME->cd();
		hME_ggF1j_bSM_Hvv2p5->Scale(1/hME_ggF1j_bSM_Hvv2p5->Integral()); 
		hME_ggF1j_bSM_Hvv2p5->Draw();
		cME->Print("plots/reco/ggF1j_bSM/"+filename+"_ggF1j_ME_bSM_Hvv2p5.pdf"); 
		
		hME_ggF1j_SMbSM_Hvv2p5->Scale(1/hME_ggF1j_SMbSM_Hvv2p5->Integral()); 
		hME_ggF1j_SMbSM_Hvv2p5->Draw();
		cME->Print("plots/reco/ggF1j_SMbSM/"+filename+"_ggF1j_ME_SMbSM_Hvv2p5.pdf"); 
		
		cME_compare->cd();
		hME_ggF1j_SM->SetMaximum(0.5);
		hME_ggF1j_SM->Draw();
		hME_ggF1j_bSM_Hvv2p5->SetLineColor(kRed);
		hME_ggF1j_bSM_Hvv2p5->Draw("same");
		hME_ggF1j_SMbSM_Hvv2p5->SetLineColor(kGreen);
		hME_ggF1j_SMbSM_Hvv2p5->Draw("same");
		Legend_ggF1j_Hvv2p5->Draw("same");
		cME_compare->Print("plots/reco/ggF1j_compare/"+filename+"_ggF1j_ME_compare_Hvv2p5.pdf");
		
		cOO->cd();
		hOO1_ggF1j_Hvv1->Scale(1/hOO1_ggF1j_Hvv1->Integral());
		hOO1_ggF1j_Hvv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_ggF1j_OO1_Hvv1.pdf");
		
		hOO2_ggF1j_Hvv1->Scale(1/hOO1_ggF1j_Hvv1->Integral());
		hOO2_ggF1j_Hvv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_ggF1j_OO2_Hvv1.pdf");
		
		hOO1_ggF1j_Hvv2p5->Scale(1/hOO1_ggF1j_Hvv2p5->Integral());
		hOO1_ggF1j_Hvv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_ggF1j_OO1_Hvv2p5.pdf");
		
		hOO2_ggF1j_Hvv2p5->Scale(1/hOO1_ggF1j_Hvv2p5->Integral());
		hOO2_ggF1j_Hvv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_ggF1j_OO2_Hvv2p5.pdf");
		
				hME_ggF1j_bSM_Avv1->Scale(1/hME_ggF1j_bSM_Avv1->Integral()); 
		hME_ggF1j_bSM_Avv1->Draw();
		cME->Print("plots/reco/ggF1j_bSM/"+filename+"_ggF1j_ME_bSM_Avv1.pdf"); 
		
		hME_ggF1j_SMbSM_Avv1->Scale(1/hME_ggF1j_SMbSM_Avv1->Integral()); 
		hME_ggF1j_SMbSM_Avv1->Draw();
		cME->Print("plots/reco/ggF1j_SMbSM/"+filename+"_ggF1j_ME_SMbSM_Avv1.pdf"); 
		
 		cME_compare->cd();
 		hME_ggF1j_SM->SetMaximum(0.5);
		hME_ggF1j_SM->Draw();
		hME_ggF1j_bSM_Avv1->SetLineColor(kRed);
		hME_ggF1j_bSM_Avv1->Draw("same");
		hME_ggF1j_SMbSM_Avv1->SetLineColor(kGreen);
		hME_ggF1j_SMbSM_Avv1->Draw("same");
		Legend_ggF1j_Avv1->Draw("same");
		cME_compare->Print("plots/reco/ggF1j_compare/"+filename+"_ggF1j_ME_compare_Avv1.pdf");
		
		cME->cd();
		hME_ggF1j_bSM_Avv2p5->Scale(1/hME_ggF1j_bSM_Avv2p5->Integral()); 
		hME_ggF1j_bSM_Avv2p5->Draw();
		cME->Print("plots/reco/ggF1j_bSM/"+filename+"_ggF1j_ME_bSM_Avv2p5.pdf"); 
		
		hME_ggF1j_SMbSM_Avv2p5->Scale(1/hME_ggF1j_SMbSM_Avv2p5->Integral()); 
		hME_ggF1j_SMbSM_Avv2p5->Draw();
		cME->Print("plots/reco/ggF1j_SMbSM/"+filename+"_ggF1j_ME_SMbSM_Avv2p5.pdf"); 
		
		cME_compare->cd();
		hME_ggF1j_SM->SetMaximum(0.5);
		hME_ggF1j_SM->Draw();
		hME_ggF1j_bSM_Avv2p5->SetLineColor(kRed);
		hME_ggF1j_bSM_Avv2p5->Draw("same");
		hME_ggF1j_SMbSM_Avv2p5->SetLineColor(kGreen);
		hME_ggF1j_SMbSM_Avv2p5->Draw("same");
		Legend_ggF1j_Avv2p5->Draw("same");
		cME_compare->Print("plots/reco/ggF1j_compare/"+filename+"_ggF1j_ME_compare_Avv2p5.pdf");
		
		cOO->cd();
		hOO1_ggF1j_Avv1->Scale(1/hOO1_ggF1j_Avv1->Integral());
		hOO1_ggF1j_Avv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_ggF1j_OO1_Avv1.pdf");
		
		hOO2_ggF1j_Avv1->Scale(1/hOO1_ggF1j_Avv1->Integral());
		hOO2_ggF1j_Avv1->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_ggF1j_OO2_Avv1.pdf");
		
		hOO1_ggF1j_Avv2p5->Scale(1/hOO1_ggF1j_Avv2p5->Integral());
		hOO1_ggF1j_Avv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_ggF1j_OO1_Avv2p5.pdf");
		
		hOO2_ggF1j_Avv2p5->Scale(1/hOO1_ggF1j_Avv2p5->Integral());
		hOO2_ggF1j_Avv2p5->Draw();
		cOO->Print("plots/reco/ggF1j_OO/"+filename+"_ggF1j_OO2_Avv2p5.pdf");

	cout << string(80,'-') << endl;	
					
	} //end of file list
} //end of main


void VBFVHCardNames(vector<string> *vbfvhcardList) {

	vbfvhcardList->push_back("MadGraphME/Cards/param_card_VBFVH_SM.dat");
	vbfvhcardList->push_back("MadGraphME/Cards/param_card_VBFVH_bSM_Hvv1.dat");
	vbfvhcardList->push_back("MadGraphME/Cards/param_card_VBFVH_SMbSM_Hvv1.dat");
	vbfvhcardList->push_back("MadGraphME/Cards/param_card_VBFVH_bSM_Hvv2p5.dat");
	vbfvhcardList->push_back("MadGraphME/Cards/param_card_VBFVH_SMbSM_Hvv2p5.dat");
	vbfvhcardList->push_back("MadGraphME/Cards/param_card_VBFVH_bSM_Avv1.dat");
	vbfvhcardList->push_back("MadGraphME/Cards/param_card_VBFVH_SMbSM_Avv1.dat");
	vbfvhcardList->push_back("MadGraphME/Cards/param_card_VBFVH_bSM_Avv2p5.dat");
	vbfvhcardList->push_back("MadGraphME/Cards/param_card_VBFVH_SMbSM_Avv2p5.dat");

}

void ggFCardNames(vector<string> *ggfcardList) {

	ggfcardList->push_back("MadGraphME/Cards/param_card_ggF_SM.dat");
	ggfcardList->push_back("MadGraphME/Cards/param_card_ggF_bSM_Hvv1.dat");
	ggfcardList->push_back("MadGraphME/Cards/param_card_ggF_SMbSM_Hvv1.dat");
	ggfcardList->push_back("MadGraphME/Cards/param_card_ggF_bSM_Hvv2p5.dat");
	ggfcardList->push_back("MadGraphME/Cards/param_card_ggF_SMbSM_Hvv2p5.dat");
	ggfcardList->push_back("MadGraphME/Cards/param_card_ggF_bSM_Avv1.dat");
	ggfcardList->push_back("MadGraphME/Cards/param_card_ggF_SMbSM_Avv1.dat");
	ggfcardList->push_back("MadGraphME/Cards/param_card_ggF_bSM_Avv2p5.dat");
	ggfcardList->push_back("MadGraphME/Cards/param_card_ggF_SMbSM_Avv2p5.dat");

}

void FileNames(vector<string> *fileList)
{   
    fileList->push_back("mc15_13TeV.341505.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_ggH125_ZZ4lep_noTau");
    fileList->push_back("mc15_13TeV.341518.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH125_ZZ4lep_noTau");
    fileList->push_back("mc15_13TeV.341947.Pythia8EvtGen_A14NNPDF23LO_ZH125_ZZ4l");
    fileList->push_back("mc15_13TeV.341964.Pythia8EvtGen_A14NNPDF23LO_WH125_ZZ4l");
    fileList->push_back("mc15_13TeV.342556.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_100_150");
    fileList->push_back("mc15_13TeV.342561.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_ttH125_4l");

    fileList->push_back("mc15_13TeV.343212.Powheggg2vvPythia8EvtGen_gg_ZZ_bkg_2e2mu_13TeV");
    fileList->push_back("mc15_13TeV.343213.Powheggg2vvPythia8EvtGen_gg_ZZ_bkg_4l_noTau_13TeV");
    fileList->push_back("mc15_13TeV.343232.PowhegPy8EG_CT10nloME_AZNLOCTEQ6L1_ZZllll_mll4_m4l_500_13000");

	fileList->push_back("mc15_13TeV.343247.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0p");

	fileList->push_back("mc15_13TeV.343248.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0phkHdz10");
	fileList->push_back("mc15_13TeV.343249.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0phkHv10");
	fileList->push_back("mc15_13TeV.343250.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHv5kAv10");
	fileList->push_back("mc15_13TeV.343251.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHvm10kAv10");
	fileList->push_back("mc15_13TeV.343252.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0mkAv15");
	fileList->push_back("mc15_13TeV.343253.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkAv5");
	fileList->push_back("mc15_13TeV.343254.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkAv2p5");	
	fileList->push_back("mc15_13TeV.343255.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkAvm5");
	fileList->push_back("mc15_13TeV.343256.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkAvm2p5");
	fileList->push_back("mc15_13TeV.343257.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHdz5");
	fileList->push_back("mc15_13TeV.343258.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHdzm10");
	fileList->push_back("mc15_13TeV.343259.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHv5");
	fileList->push_back("mc15_13TeV.343260.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHv2p5");
	fileList->push_back("mc15_13TeV.343261.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHvm5");
	fileList->push_back("mc15_13TeV.343262.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphkHvm2p5");
	fileList->push_back("mc15_13TeV.344152.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHv2p5kAvm5");
	fileList->push_back("mc15_13TeV.344153.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHv5kAv5");
	fileList->push_back("mc15_13TeV.344154.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHv5kAv6");
	fileList->push_back("mc15_13TeV.344155.MGPy8EG_A14NNPDF23LO_vbfhzz4l_0pphmkHvm2p5kAvm5");
	fileList->push_back("mc15_13TeV.344156.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHvm5kAv5");
	fileList->push_back("mc15_13TeV.344157.MadGraphPythia8EvtGen_A14NNPDF23LO_vbfhzz4l_0pphmkHvm5kAvm6");

	fileList->push_back("mc15_13TeV.344135.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0p");

	fileList->push_back("mc15_13TeV.344136.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphkHv5");
	fileList->push_back("mc15_13TeV.344137.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphkHvm5");
	fileList->push_back("mc15_13TeV.344138.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphkHv2p5");
	fileList->push_back("mc15_13TeV.344139.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphkHvm2p5");
	fileList->push_back("mc15_13TeV.344140.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0phkHv10");
	fileList->push_back("mc15_13TeV.344141.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkAv5");
	fileList->push_back("mc15_13TeV.344142.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkAvm5");
	fileList->push_back("mc15_13TeV.344143.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkAv2p5");
	fileList->push_back("mc15_13TeV.344144.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkAvm2p5");
	fileList->push_back("mc15_13TeV.344145.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0mkAv15");
	fileList->push_back("mc15_13TeV.344146.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHv2p5kAvm5");
	fileList->push_back("mc15_13TeV.344147.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHvm2p5kAvm5");
	fileList->push_back("mc15_13TeV.344148.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHvm5kAv5");
	fileList->push_back("mc15_13TeV.344149.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHvm5kAvm6");
	fileList->push_back("mc15_13TeV.344150.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHv5kAv6");
	fileList->push_back("mc15_13TeV.344151.MGPy8EG_A14NNPDF23LO_vhlep125_4l_0pphmkHv5kAv5");
	
	fileList->push_back("mc15_13TeV.344158.aMcAtNloPythia8EvtGen_A14NNPDF23LO_ppx0_FxFx_Np012_SM");
	fileList->push_back("mc15_13TeV.344159.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kHvv1_cosa1p0");
	fileList->push_back("mc15_13TeV.344160.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kHvv6_cosa1p0");
	fileList->push_back("mc15_13TeV.344161.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kHvvn6_cosa1p0");
	fileList->push_back("mc15_13TeV.344162.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAvv1_cosa0p707");
	fileList->push_back("mc15_13TeV.344163.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAvv6_cosa0p707");
	fileList->push_back("mc15_13TeV.344164.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAvvn6_cosa0p707");
	fileList->push_back("mc15_13TeV.344165.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAHvv6_cosa0p707");
	fileList->push_back("mc15_13TeV.344166.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAHvvn6_cosa0p707");
	fileList->push_back("mc15_13TeV.344167.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAgg0p5_cosa0p707");
	fileList->push_back("mc15_13TeV.344168.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAggn0p5_cosa0p707");
	fileList->push_back("mc15_13TeV.344169.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAgg1p41_cosa0p707");
	fileList->push_back("mc15_13TeV.344170.aMcAtNloPythia8EvtGen_A14NNPDF23LO_FxFx_kAgg1_cosa0p707");
}
