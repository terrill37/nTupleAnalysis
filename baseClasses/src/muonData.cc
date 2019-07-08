
#include "TChain.h"
#include "TFile.h"

#include "nTupleAnalysis/baseClasses/interface/muonData.h"

using namespace nTupleAnalysis;

//muon object
muon::muon(UInt_t i, muonData* data){
  

  pt  = data->pt [i];
  eta = data->eta[i];
  phi = data->phi[i];
  m   = data->m  [i];
  if(m < 0.10) m = 0.1057;
    
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);

  softId   = data->softId[i];
  highPtId = data->highPtId[i];

  mediumId = data->mediumId[i];
  tightId  = data->tightId[i];

  quality  = mediumId + tightId;

  jetIdx    = data->jetIdx[i];
  isolation = data->pfRelIso04_all[i];
  isolation_corrected = data->isolation_corrected[i];
  isolation_trackerOnly = data->isolation_trkIsoOnly[i];

  //
  // Load the SFs
  //
  if(data->m_isMC && data->m_SFHistTight && data->m_SFHistIso){
    //std::cout << "Muon Iso SF " << data->m_SFHistIso  ->GetBinContent(data->m_SFHistIso  ->FindBin(fabs(eta), pt)) << std::endl;;
    SF *= data->m_SFHistIso  ->GetBinContent(data->m_SFHistIso  ->FindBin(pt, fabs(eta)));
    //std::cout << "Muon Tight SF " << data->m_SFHistTight  ->GetBinContent(data->m_SFHistTight  ->FindBin(fabs(eta), pt)) << std::endl;;
    SF *= data->m_SFHistTight->GetBinContent(data->m_SFHistTight->FindBin(pt, fabs(eta)));
  }
  

}

muon::~muon(){}


//access tree
muonData::muonData(std::string name, TChain* tree, bool isMC, std::string SFName){
  
  m_name = name;
  m_isMC = isMC;

  initBranch(tree, ("n"+name).c_str(), n );

  initBranch(tree, (name+"_pt"  ).c_str(), pt );  
  initBranch(tree, (name+"_eta" ).c_str(), eta );  
  initBranch(tree, (name+"_phi" ).c_str(), phi );  
  initBranch(tree, (name+"_mass").c_str(), m );

  if(initBranch(tree, (name+"_softId"  ).c_str(), softId ) == -1){
    std::cout << "\tUsing " << (name+"_isSoftMuon"        ) << " for softId " << std::endl;
    initBranch(tree, (name+"_isSoftMuon"  ).c_str(), softId );
  }
  initBranch(tree, (name+"_highPtId").c_str(), highPtId );

  if(initBranch(tree, (name+"_mediumId").c_str(), mediumId ) == -1){
    std::cout << "\tUsing " << (name+"_isMediumMuon"        ) << " for mediumId " << std::endl;
    initBranch(tree, (name+"_isMediumMuon").c_str(), mediumId );
  }

  if(initBranch(tree, (name+"_tightId" ).c_str(), tightId ) == -1){
    std::cout << "\tUsing " << (name+"_isTightMuon"        ) << " for tightId " << std::endl;
    initBranch(tree, (name+"_isTightMuon" ).c_str(), tightId );
  }

  initBranch(tree, (name+"_jetIdx").c_str(), jetIdx );
  initBranch(tree, (name+"_pfRelIso04_all").c_str(), pfRelIso04_all );
  initBranch(tree, (name+"_iso").c_str(), isolation_corrected );
  initBranch(tree, (name+"_isoTrackerOnly").c_str(), isolation_trkIsoOnly );

//  *Br   25 :nPatMuon  : nPatMuon/I                                             *
//    *Br   34 :PatMuon_IP : PatMuon_IP[nPatMuon]/F                                *
//    *Br   35 :PatMuon_IPsig : PatMuon_IPsig[nPatMuon]/F                          *
//    *Br   36 :PatMuon_IP2D : PatMuon_IP2D[nPatMuon]/F                            *
//    *Br   37 :PatMuon_IP2Dsig : PatMuon_IP2Dsig[nPatMuon]/F                      *
    

  //
  // Load the muon SFs
  //
  if(m_isMC){

    if(SFName != "2017" && SFName != "2018"){
      std::cout << "muonData::Warning no scale factors for " << m_name << std::endl;
    }else{

      std::string IDSFName = "";
      std::string IsoSFName = "";
      
      if(SFName == "2017"){
	
	IDSFName = "nTupleAnalysis/baseClasses/data/MuonSF2017/RunBCDEF_SF_ID.root";
	IsoSFName = "nTupleAnalysis/baseClasses/data/MuonSF2017/RunBCDEF_SF_ISO.root";

	m_SFFileID = new TFile(IDSFName.c_str(),"READ");
	m_SFHistTight = (TH2D*)m_SFFileID->Get("NUM_TightID_DEN_genTracks_pt_abseta");
      
	m_SFFileIso = new TFile(IsoSFName.c_str(),"READ");
	m_SFHistIso = (TH2D*)m_SFFileIso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

      }else{
	IDSFName = "nTupleAnalysis/baseClasses/data/MuonSF2018/RunABCD_SF_ID.root";
	IsoSFName = "nTupleAnalysis/baseClasses/data/MuonSF2018/RunABCD_SF_ISO.root";

	m_SFFileID = new TFile(IDSFName.c_str(),"READ");
	m_SFHistTight = (TH2D*)m_SFFileID->Get("NUM_TightID_DEN_TrackerMuons_pt_abseta");
      
	m_SFFileIso = new TFile(IsoSFName.c_str(),"READ");
	m_SFHistIso = (TH2D*)m_SFFileIso->Get("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta");

      }

      std::cout << "muonData::Loading SF from files: \n\t" << IDSFName << "\n and \n\t" << IsoSFName  << "\n For muons " << m_name << std::endl;

    }

  }// isMC



}

std::vector<std::shared_ptr<muon>> muonData::getMuons(float ptMin, float etaMax, int tag, bool isolation){

  std::vector<std::shared_ptr<muon>> outputMuons;

  for(Int_t i = 0; i < n; ++i){
    if(i > int(MAXMUONS-1)) {
      std::cout  << m_name << "::Warning too many muons! " << n << " muons. Skipping. "<< std::endl;
      break;
    }

    if(tag == 0 && softId[i]   == 0) continue;
    if(tag == 1 && highPtId[i] == 0) continue;
    if(tag == 2 && mediumId[i] == 0) continue;
    if(tag == 3 && tightId[i]  == 0) continue;
    if(isolation && pfRelIso04_all[i] > 0.20) continue; //working points here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SWGuideMuonIdRun2

    if(      pt[i] < ptMin) continue;
    if(fabs(eta[i])>etaMax) continue;

    outputMuons.push_back(std::make_shared<muon>(muon(i, this)));
  }

  return outputMuons;
}

muonData::~muonData(){
  std::cout << "muonData::destroyed " << std::endl;
}
