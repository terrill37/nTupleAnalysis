
#include "TChain.h"
#include "TFile.h"

#include "nTupleAnalysis/baseClasses/interface/vertexData.h"

using namespace nTupleAnalysis;

//vertex object
vertex::vertex(UInt_t i, vertexData* data){


  x      =  data->x[i];
  y      =  data->y[i]; 
  z      =  data->z[i]; 
  ex     =  data->ex[i];
  ey     =  data->ey[i];
  ez     =  data->ez[i];
  chi2   =  data->chi2[i];
  ndf    =  data->ndf[i]; 
  isgood =  data->isgood[i];
  isfake =  data->isfake[i];


}

vertex::~vertex(){}


//access tree
vertexData::vertexData(std::string name, TTree* tree, bool readIn, bool isMC){
  
  m_name = name;
  m_isMC = isMC;

  connectBranches(readIn, tree);

}

void vertexData::connectBranches(bool readIn, TTree* tree){

  std::string vtxName =  m_name;
  std::string NPVName = "n"+m_name;

  connectBranch(readIn, tree, NPVName, nPV, "i" );

  // Following are redudant with data->z[0] and data->ez[0] 
  //connectBranch(readIn, tree, "PVz", PVz, "F" ); 
  //connectBranch(readIn, tree, "PVez", PVez, "F" );

  connectBranch(readIn, tree, vtxName+"_x"     , x,        "F"); 
  connectBranch(readIn, tree, vtxName+"_y"     , y,        "F"); 
  connectBranch(readIn, tree, vtxName+"_z"     , z,        "F");  
  connectBranch(readIn, tree, vtxName+"_ex"    , ex,       "F");
  connectBranch(readIn, tree, vtxName+"_ey"    , ey,       "F");
  connectBranch(readIn, tree, vtxName+"_ez"    , ez,       "F");
  connectBranch(readIn, tree, vtxName+"_chi2"  , chi2,     "F");
  connectBranch(readIn, tree, vtxName+"_ndf"   , ndf,      "F");
  connectBranch(readIn, tree, vtxName+"_isgood", isgood,   "I");
  connectBranch(readIn, tree, vtxName+"_isfake", isfake,   "I");

}    


void vertexData::writeVerticies(std::vector< std::shared_ptr<vertex> > outputVtx){
  
  int nOutputVtx = outputVtx.size();
  this->nPV = outputVtx.size();
 
  for(Int_t i = 0; i < int(this->nPV); ++i){
    if(i > int(MAXPVS-1)) {
      std::cout  << m_name << "::Warning too many verticies! " << nOutputVtx << " verticies. Skipping. "<< std::endl;
      break;
    }

    const vertexPtr& thisVtx = outputVtx.at(i);
    
    this->x      [i]        = thisVtx->x     ;
    this->y      [i]        = thisVtx->y     ;
    this->z      [i]        = thisVtx->z     ;
    this->ex     [i]        = thisVtx->ex    ;
    this->ey     [i]        = thisVtx->ey    ;
    this->ez     [i]        = thisVtx->ez    ;
    this->chi2   [i]        = thisVtx->chi2  ;
    this->ndf    [i]        = thisVtx->ndf   ;
    this->isgood [i]        = thisVtx->isgood;
    this->isfake [i]        = thisVtx->isfake;

  }

  return ;
}



std::vector<std::shared_ptr<vertex>> vertexData::getVerticies(){

  std::vector<std::shared_ptr<vertex>> outputVtxs;

  for(Int_t i = 0; i < int(nPV); ++i){
    if(i > int(MAXPVS-1)) {
      std::cout  << m_name << "::Warning too many verticies! " << nPV << " verticies. Skipping. "<< std::endl;
      break;
    }

    //if(      pt[i] < ptMin) continue;

    outputVtxs.push_back(std::make_shared<vertex>(vertex(i, this)));
  }

  return outputVtxs;
}

vertexData::~vertexData(){
  std::cout << "vertexData::destroyed " << std::endl;
}
