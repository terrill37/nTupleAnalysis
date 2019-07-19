#include "nTupleAnalysis/baseClasses/interface/eventHists.h"

using namespace nTupleAnalysis;

eventHists::eventHists(std::string name, fwlite::TFileService& fs) {

    dir = fs.mkdir(name);
    
    nPV      = dir.make<TH1F>("nPV",  (name+"/nPV  ;nPV ;Entries").c_str(),  100,-0.5, 99.5);
    pu       = dir.make<TH1F>("pu",   (name+"/pu   ;pu  ;Entries").c_str(),  100,-0.5, 99.5);

} 

void eventHists::Fill(float input_nPV, float input_pu, float weight){

  nPV -> Fill(input_nPV, weight);
  pu  -> Fill(input_pu , weight);

  return;
}

eventHists::~eventHists(){} 
