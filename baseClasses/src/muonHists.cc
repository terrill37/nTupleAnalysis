#include "nTupleAnalysis/baseClasses/interface/muonHists.h"

using namespace nTupleAnalysis;

muonHists::muonHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir);

    quality   = dir.make<TH1F>("quality",   (name+"/quality;   "+title+" Quality;   Entries").c_str(), 3,-0.5,2.5);
    isolation = dir.make<TH1F>("isolation", (name+"/isolation; "+title+" Isolation; Entries").c_str(), 50,0,1);
    isolation_cor = dir.make<TH1F>("iso_cor", (name+"/iso_cor; "+title+" Isolation; Entries").c_str(), 50,0,1);
    isolation_cor_s = dir.make<TH1F>("iso_cor_s", (name+"/iso_cor_s; "+title+" Isolation; Entries").c_str(), 50,0,0.1);
    dR        = dir.make<TH1F>("dR",        (name+"/dR;        "+title+" Min #DeltaR(muon,jet); Entries").c_str(), 50, 0, 5);
    nMuons    = dir.make<TH1F>("nMuons",    (name+"/nMuons;    "+title+" Number of Muons; Entries").c_str(),  6,-0.5,5.5);

} 

void muonHists::Fill(std::shared_ptr<muon> &muon, float weight){

  v->Fill(muon->p, weight);

  quality  ->Fill(muon->quality,   weight);
  isolation->Fill(muon->isolation, weight);
  isolation_cor->Fill(muon->isolation_corrected, weight);
  isolation_cor_s->Fill(muon->isolation_corrected, weight);
  dR       ->Fill(muon->dR,        weight);

  return;
}

muonHists::~muonHists(){} 
