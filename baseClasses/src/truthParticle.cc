#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/truthParticle.h"

using namespace nTupleAnalysis;

//particle object
particle::particle(){}
particle::particle(UInt_t i, truthParticle* data){

  pt  = data->pt [i];
  eta = data->eta[i];
  phi = data->phi[i];
  m   = data->m  [i];
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);
  e = p.E();

  pdgId = data->pdgId[i];
  genPartIdxMother = data->genPartIdxMother[i];

}

particle::~particle(){}


//access tree
truthParticle::truthParticle(std::string name, TChain* tree){

  inputBranch(tree, ("n"+name).c_str(), n );

  inputBranch(tree, (name+"_pt"  ).c_str(), pt  );  
  inputBranch(tree, (name+"_eta" ).c_str(), eta );  
  inputBranch(tree, (name+"_phi" ).c_str(), phi );  
  inputBranch(tree, (name+"_mass").c_str(), m   );  

  inputBranch(tree, (name+"_genPartIdxMother").c_str(), genPartIdxMother );
  inputBranch(tree, (name+"_pdgId").c_str(), pdgId );
  //inputBranch(tree, (name+"_").c_str(),  );

}

std::vector< std::shared_ptr<particle> > truthParticle::getParticles(Int_t absPDG, Int_t absMomPDG){
  
  std::vector< std::shared_ptr<particle> > outputParticles;

  for(UInt_t i = 0; i < n; ++i){
    if(    absPDG != -1 && abs(pdgId[i])                   != absPDG    ) continue;
    if( absMomPDG != -1 && abs(pdgId[genPartIdxMother[i]]) != absMomPDG ) continue;
    outputParticles.push_back(std::make_shared<particle>(particle(i, this)));
  }

  return outputParticles;
}

truthParticle::~truthParticle(){}
