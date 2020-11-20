//#include "TChain.h"
#include "nTupleAnalysis/baseClasses/interface/mass.h"

using namespace nTupleAnalysis;

mass::mass(std::string name, fwlite::TFileService& fs) {

  dir = fs.mkdir(name);
  DeepCSV = dir.make<TH1F>("deepCSV", (name+"/deepCSV; ;Entries").c_str(), 120, -0.2, 1.2);
  invariant_mass    = dir.make<TH1F>("mass", (name+"/mass; ;Entries").c_str(), 100, 0, 1000);
  Ht  = dir.make<TH1F>("Ht", (name+"/Ht; ;Entries").c_str(), 100, 0, 1000);
}


void mass::Fill(const std::shared_ptr<jet> &jet, float weight){
  DeepCSV  ->Fill(jet->DeepCSV, weight);

  return;
}

void mass::FillMass(const float mass_val){
  invariant_mass -> Fill(mass_val);
  
  return;
}

void mass::FillHt(const float mass_val){
    Ht -> Fill(Ht_val);
    return;
}

/*void triggers::AddCut(std::string cut){
  DeepCSV ->GetXaxis()->FindBin(cut.c_str());
  mass    ->GetXaxis()->FindBin(cut.c_str());
  //cutL1->GetXaxis()->FindBin(cut.c_str()); 
  return;
}*/


mass::~mass(){} 

