//#include "TChain.h"
#include "nTupleAnalysis/baseClasses/interface/mass.h"

using namespace nTupleAnalysis;

mass::mass(std::string name, fwlite::TFileService& fs) {

  dir = fs.mkdir(name);
  DeepCSV = dir.make<TH1F>("deepCSV", (name+"/deepCSV; ;Entries").c_str(), 120, -0.2, 1.2);
  invariant_mass    = dir.make<TH1F>("mass", (name+"/mass; ;Entries").c_str(), 500, 0, 100);
  
 // cutL1  = dir.make<TH1F>("cutL1", (name+"/test; ;Entries").c_str(), 64, 0, 64);
}


void mass::Fill(const std::shared_ptr<jet> &jet, float weight){
  DeepCSV  ->Fill(jet->DeepCSV, weight);
  //invariant_mass     ->Fill(jet->DeepCSV);
  //cutL1 ->Fill(cut);

  return;
}

void mass::FillMass(const float mass_val){
  invariant_mass -> Fill(mass_val);
  
  return;
}

/*void triggers::AddCut(std::string cut){
  DeepCSV ->GetXaxis()->FindBin(cut.c_str());
  mass    ->GetXaxis()->FindBin(cut.c_str());
  //cutL1->GetXaxis()->FindBin(cut.c_str()); 
  return;
}*/


mass::~mass(){} 

