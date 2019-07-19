#include "TChain.h"
#include "TFile.h"

#include "nTupleAnalysis/baseClasses/interface/elecData.h"

using namespace nTupleAnalysis;

//elec object
elec::elec(UInt_t i, elecData* data){

  pt  = data->pt [i];
  eta = data->eta[i];
  superClusterEta = data->superClusterEta[i];
  phi = data->phi[i];
  m   = data->m  [i];
  if(m < 0.10) m = 0.0005;
    
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);

  softId   = data->softId[i];
  highPtId = data->highPtId[i];

  mediumId = data->mediumId[i];
  tightId  = data->tightId[i];

  quality  = mediumId + tightId;

  jetIdx    = data->jetIdx[i];
  isolation = data->pfRelIso04_all[i];

  sumChargedHadronPt = data->sumChargedHadronPt[i]; 
  sumNeutralHadronEt = data->sumNeutralHadronEt[i]; 
  sumPhotonEt        = data->sumPhotonEt       [i]; 
  sumPUPt            = data->sumPUPt           [i]; 

  
  float isoCorrection = (data->sumNeutralHadronEt[i] + data->sumPhotonEt[i] - 0.5 * data->sumPUPt[i]);
  isolation_corrected = (isoCorrection > 0) ? (data->sumChargedHadronPt[i] + isoCorrection) / pt : data->sumChargedHadronPt[i] / pt;

  //
  // Load the SFs
  //
  if(data->m_isMC && data->m_SFHistTight && data->m_SFHistReco){
    SF *= data->m_SFHistReco ->GetBinContent(data->m_SFHistReco ->FindBin(superClusterEta, pt));
    SF *= data->m_SFHistTight->GetBinContent(data->m_SFHistTight->FindBin(superClusterEta, pt));
  }
  
}

elec::~elec(){}


//access tree
elecData::elecData(std::string name, TChain* tree, bool isMC, std::string SFName){

  m_name = name;
  m_isMC = isMC;

  initBranch(tree, ("n"+name).c_str(), n );

  initBranch(tree, (name+"_pt"  ).c_str(), pt );  
  initBranch(tree, (name+"_eta" ).c_str(), eta );  
  initBranch(tree, (name+"_superClusterEta" ).c_str(), superClusterEta );  
  initBranch(tree, (name+"_phi" ).c_str(), phi );  
  initBranch(tree, (name+"_mass").c_str(), m );

  initBranch(tree, (name+"_softId"  ).c_str(), softId );
  initBranch(tree, (name+"_highPtId").c_str(), highPtId );

  if(initBranch(tree, (name+"_mediumId").c_str(), mediumId ) == -1){
    std::cout << "\tUsing " << (name+"_isMediumElec"        ) << " for mediumId " << std::endl;
    initBranch(tree, (name+"_isMediumElec"        ).c_str(),         mediumId        ); 
  }

  if(initBranch(tree, (name+"_tightId" ).c_str(), tightId ) == -1){
    std::cout << "\tUsing " << (name+"_isTightElec"        ) << " for tightId " << std::endl;
    initBranch(tree, (name+"_isTightElec"        ).c_str(),         tightId        ); 
  }

  initBranch(tree, (name+"_jetIdx").c_str(), jetIdx );
  initBranch(tree, (name+"_pfRelIso04_all").c_str(), pfRelIso04_all );


  initBranch(tree, (name+"_sumChargedHadronPt").c_str(),    sumChargedHadronPt );
  initBranch(tree, (name+"_sumNeutralHadronEt").c_str(),    sumNeutralHadronEt );
  initBranch(tree, (name+"_sumPhotonEt"       ).c_str(),    sumPhotonEt        );
  initBranch(tree, (name+"_sumPUPt"           ).c_str(),    sumPUPt            );


  //initBranch(tree, (name+"_").c_str(),  );

//  *Br   72 :nPFElectron : nPFElectron/I                                        *
//    *Br   73 :PFElectron_IdxJet : PFElectron_IdxJet[nPFElectron]/I               *
//    *Br   77 :PFElectron_ptrel : PFElectron_ptrel[nPFElectron]/F                 *
//    *Br   78 :PFElectron_deltaR : PFElectron_deltaR[nPFElectron]/F               *
//    *Br   79 :PFElectron_ratio : PFElectron_ratio[nPFElectron]/F                 *
//    *Br   80 :PFElectron_ratioRel : PFElectron_ratioRel[nPFElectron]/F           *
//    *Br   81 :PFElectron_IP : PFElectron_IP[nPFElectron]/F                       *
//    *Br   82 :PFElectron_IP2D : PFElectron_IP2D[nPFElectron]/F                   *

//  *Br   38 :nPatElec  : nPatElec/I                                             *
//    *Br   43 :PatElec_isLooseElec : PatElec_isLooseElec[nPatElec]/I              *

  //
  // Load the electron SFs
  //
  if(m_isMC){

    if(SFName != "2017" && SFName != "2018"){
      std::cout << "elecData::Warning no scale factors for " << m_name << std::endl;
    }else{

      std::string tightSFName = "nTupleAnalysis/baseClasses/data/ElecSF2017/egammaEffi.txt_EGM2D_runBCDEF_passingTight94X.root";
      std::string recoSFName  = "nTupleAnalysis/baseClasses/data/ElecSF2017/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root";
      if(SFName == "2018"){
	tightSFName = "nTupleAnalysis/baseClasses/data/ElecSF2018/2018_ElectronTight.root";
	recoSFName  = "nTupleAnalysis/baseClasses/data/ElecSF2018/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root";
      }

      std::cout << "elecData::Loading SF from files: \n\t" << tightSFName << "\n and \n\t" << recoSFName  << "\n For elecs " << m_name << std::endl;

      m_SFFileTight = new TFile(tightSFName.c_str(),"READ");
      m_SFHistTight = (TH2D*)m_SFFileTight->Get("EGamma_SF2D");
      
      m_SFFileReco = new TFile(recoSFName.c_str(),"READ");
      m_SFHistReco = (TH2D*)m_SFFileReco->Get("EGamma_SF2D");
    }
    
  }// isMC
  
  
}

std::vector<std::shared_ptr<elec> > elecData::getElecs(float ptMin, float etaMax, int tag, bool isolation){

  std::vector<std::shared_ptr<elec>> outputElecs;
  for(Int_t i = 0; i < n; ++i){
    if(i > int(MAXELECS-1)) {
      std::cout  << m_name << "::Warning too many elecs! " << n << " elecs. Skipping. "<< std::endl;
      break;
    }

    //if(tag == 0 && softId[i]   == 0) continue;
    //if(tag == 1 && highPtId[i] == 0) continue;
    //if(tag == 2 && mediumId[i] == 0) continue;
    //if(tag == 3 && tightId[i]  == 0) continue;
    //if(isolation && pfRelIso04_all[i] > 0.20) continue; 

    if(      pt[i] < ptMin) continue;
    if(fabs(eta[i])>etaMax) continue;

    outputElecs.push_back(std::make_shared<elec>(elec(i, this)));
  }

  return outputElecs;
}

elecData::~elecData(){
  std::cout << "elecData::destroyed " << std::endl;
}
