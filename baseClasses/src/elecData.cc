#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/elecData.h"

using namespace nTupleAnalysis;

//elec object
elec::elec(UInt_t i, elecData* data){

  pt  = data->pt [i];
  eta = data->eta[i];
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

}

elec::~elec(){}


//access tree
elecData::elecData(std::string name, TChain* tree){

  initBranch(tree, ("n"+name).c_str(), n );

  initBranch(tree, (name+"_pt"  ).c_str(), pt );  
  initBranch(tree, (name+"_eta" ).c_str(), eta );  
  initBranch(tree, (name+"_phi" ).c_str(), phi );  
  initBranch(tree, (name+"_mass").c_str(), m );

  initBranch(tree, (name+"_softId"  ).c_str(), softId );
  initBranch(tree, (name+"_highPtId").c_str(), highPtId );

  initBranch(tree, (name+"_mediumId").c_str(), mediumId );
  initBranch(tree, (name+"_tightId" ).c_str(), tightId );

  initBranch(tree, (name+"_jetIdx").c_str(), jetIdx );
  initBranch(tree, (name+"_pfRelIso04_all").c_str(), pfRelIso04_all );
  //initBranch(tree, (name+"_").c_str(),  );

//  *Br   72 :nPFElectron : nPFElectron/I                                        *
//    *Br   73 :PFElectron_IdxJet : PFElectron_IdxJet[nPFElectron]/I               *
//    *Br   77 :PFElectron_ptrel : PFElectron_ptrel[nPFElectron]/F                 *
//    *Br   78 :PFElectron_deltaR : PFElectron_deltaR[nPFElectron]/F               *
//    *Br   79 :PFElectron_ratio : PFElectron_ratio[nPFElectron]/F                 *
//    *Br   80 :PFElectron_ratioRel : PFElectron_ratioRel[nPFElectron]/F           *
//    *Br   81 :PFElectron_IP : PFElectron_IP[nPFElectron]/F                       *
//    *Br   82 :PFElectron_IP2D : PFElectron_IP2D[nPFElectron]/F                   *
    
    

}

std::vector<std::shared_ptr<elec>> elecData::getElecs(float ptMin, float etaMax, int tag, bool isolation){

  std::vector<std::shared_ptr<elec>> outputElecs;
  for(UInt_t i = 0; i < n; ++i){
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

elecData::~elecData(){}
