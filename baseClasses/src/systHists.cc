#include "nTupleAnalysis/baseClasses/interface/systHists.h"

using namespace nTupleAnalysis;

// systHists::systHists(std::string name, fwlite::TFileService& fs, std::string title) {
//   TFileDirectory dir = fs.mkdir(name);
//   this->makeHists(name, dir, title);
// }

systHists::systHists(TH1F* nominal, std::vector<std::string>& variations) {
  this->makeHists(nominal, variations);
}

void systHists::makeHists(TH1F* nominal, std::vector<std::string>& variations) {

  for(auto &variation: variations){
    hists[variation] = (TH1F*) nominal->Clone((std::string(nominal->GetName())+"_"+variation).c_str());
  }

  return;
} 

void systHists::Fill(float x, float weight, std::map<std::string, float>& variations, float denom){

  for(auto &variation: variations){
    hists[variation.first]->Fill(x, weight * variation.second / denom);
  }

  return;
}

systHists::~systHists(){} 
