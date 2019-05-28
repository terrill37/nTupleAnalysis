#include "nTupleAnalysis/baseClasses/interface/elecHists.h"

using namespace nTupleAnalysis;

elecHists::elecHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir);

    quality   = dir.make<TH1F>("quality",   (name+"/quality;   "+title+" Quality;   Entries").c_str(), 3,-0.5,2.5);
    isolation = dir.make<TH1F>("isolation", (name+"/isolation; "+title+" Isolation; Entries").c_str(), 50,0,1);
    dR        = dir.make<TH1F>("dR",        (name+"/dR;        "+title+" Min #DeltaR(elec,jet); Entries").c_str(), 50, 0, 5);
    nElecs    = dir.make<TH1F>("nElecs",    (name+"/nElecs;    "+title+" Number of Electrons; Entries").c_str(),  6,-0.5,5.5);
} 

void elecHists::Fill(std::shared_ptr<elec> &elec, float weight){

  v->Fill(elec->p, weight);

  quality  ->Fill(elec->quality,   weight);
  isolation->Fill(elec->isolation, weight);
  dR       ->Fill(elec->dR,        weight);

  return;
}

elecHists::~elecHists(){} 
