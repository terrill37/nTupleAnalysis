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
truthParticle::truthParticle(std::string name, TTree* tree, bool readIn){

  m_name = name;

  connectBranches(readIn, tree);


}

void truthParticle::connectBranches(bool readIn, TTree* tree){

  std::string truthName =  m_name;
  std::string NTruthName = "n"+m_name;

  connectBranch(readIn, tree, NTruthName, nTruth, "i" );

  connectBranch(readIn, tree, truthName+"_pt"  , pt  , "F");  
  connectBranch(readIn, tree, truthName+"_eta" , eta , "F");  
  connectBranch(readIn, tree, truthName+"_phi" , phi , "F");  
  connectBranch(readIn, tree, truthName+"_mass", m   , "F");  

  connectBranch(readIn, tree, truthName+"_genPartIdxMother", genPartIdxMother, "I" );
  connectBranch(readIn, tree, truthName+"_pdgId", pdgId, "I" );
  //inputBranch(tree, (name+"_").c_str(),  );


}

std::vector< std::shared_ptr<particle> > truthParticle::getParticles(Int_t absPDG, Int_t absMomPDG){
  
  std::vector< std::shared_ptr<particle> > outputParticles;

  for(UInt_t i = 0; i < nTruth; ++i){
    if(    absPDG != -1 && abs(pdgId[i])                   != absPDG    ) continue;
    if( absMomPDG != -1 && abs(pdgId[genPartIdxMother[i]]) != absMomPDG ) continue;
    outputParticles.push_back(std::make_shared<particle>(particle(i, this)));
  }

  return outputParticles;
}

truthParticle::~truthParticle(){}
