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
  
  std::cout<<"truthName: "<<m_name<<std::endl;

  if(connectBranch(readIn, tree, NTruthName, nTruth, "i" ) == -1){
    connectBranch(readIn, tree, NTruthName+"s", nTruth, "i"); 
  }

  if(connectBranchArr(readIn, tree, truthName+"_pt"  , pt  , NTruthName, "F") == -1){
    connectBranchArr(readIn, tree, truthName+"_pT", pt, NTruthName, "F");
  }

  connectBranchArr(readIn, tree, truthName+"_eta" , eta , NTruthName, "F");  
  connectBranchArr(readIn, tree, truthName+"_phi" , phi , NTruthName, "F");  
  connectBranchArr(readIn, tree, truthName+"_mass", m   , NTruthName, "F");  

  connectBranchArr(readIn, tree, truthName+"_genPartIdxMother", genPartIdxMother, NTruthName, "I" );
  connectBranchArr(readIn, tree, truthName+"_pdgId", pdgId, NTruthName, "I" );
  //inputBranch(tree, (name+"_").c_str(),  );


}


void truthParticle::writeTruth(std::vector< std::shared_ptr<particle> > outputTruth){
  
  int nOutputTruth = outputTruth.size();
  this->nTruth = outputTruth.size();
 
  for(Int_t i = 0; i < int(this->nTruth); ++i){
    if(i > int(MAXTRUTH-1)) {
      std::cout  << m_name << "::Warning too much truth! " << nOutputTruth << " particles. Skipping. "<< std::endl;
      break;
    }

    const particlePtr& thisParticle = outputTruth.at(i);

    this->pt    [i] = thisParticle->pt         ;
    this->eta   [i] = thisParticle->eta        ;
    this->phi   [i] = thisParticle->phi        ;
    this->m     [i] = thisParticle->m          ;
    this->genPartIdxMother  [i] = thisParticle->genPartIdxMother       ;
    this->pdgId [i] = thisParticle->pdgId	   ;

  }

  return ;
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
