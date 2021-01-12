//#include "TChain.h"
#include "nTupleAnalysis/baseClasses/interface/mass.h"

using namespace nTupleAnalysis;

mass::mass(std::string name, fwlite::TFileService& fs) {

  dir = fs.mkdir(name);
  flavour = dir.make<TH1F>("flavour", (name+"/flavour; ;Entries").c_str(), 6, 0, 6);
  invariant_mass    = dir.make<TH1F>("mass", (name+"/mass; ;Entries").c_str(), 100, 0, 1000);
  Ht  = dir.make<TH1F>("Ht", (name+"/Ht; ;Entries").c_str(), 100, 0, 1000);
  pt_1 = dir.make<TH1F>("pt_1", (name+"/pt_1; ;Entries").c_str(), 100, 0, 1000);
  pt_2 = dir.make<TH1F>("pt_2", (name+"/pt_2; ;Entries").c_str(), 100, 0, 1000);
  pt_3 = dir.make<TH1F>("pt_3", (name+"/pt_3; ;Entries").c_str(), 100, 0, 1000);
  pt_4 = dir.make<TH1F>("pt_4", (name+"/pt_4; ;Entries").c_str(), 50, 0, 500);

  pt_1_cut = dir.make<TH1F>("pt_1_cut", (name+"/pt_1_cut; ;Entries").c_str(), 100, 0, 1000);
  pt_2_cut = dir.make<TH1F>("pt_2_cut", (name+"/pt_2_cut; ;Entries").c_str(), 100, 0, 1000);
  pt_3_cut = dir.make<TH1F>("pt_3_cut", (name+"/pt_3_cut; ;Entries").c_str(), 100, 0, 1000);
  pt_4_cut = dir.make<TH1F>("pt_4_cut", (name+"/pt_4_cut; ;Entries").c_str(), 50, 0, 500);

}


void mass::Fill(const std::shared_ptr<jet> &jet, float weight){
  
  flavour  ->Fill(jet->flavour, weight);

  return;
}

void mass::FillMass(const float mass_val){
  invariant_mass -> Fill(mass_val);
  
  return;
}

void mass::FillHt(const float Ht_val){
    Ht -> Fill(Ht_val);
    return;
}

void mass::Fillpts(std::vector<float> pts){
    pt_1 -> Fill(pts.at(0));
    pt_2 -> Fill(pts.at(1));
    pt_3 -> Fill(pts.at(2));
    pt_4 -> Fill(pts.at(3));
    
    pt_4_cut -> Fill(pts.at(3));
    if(pts.at(3)>200){
        pt_3_cut -> Fill(pts.at(2));

        if(pts.at(2)>100){
            pt_2_cut -> Fill(pts.at(1));

            if(pts.at(1)>0){
                pt_1_cut -> Fill(pts.at(0));
            }
        }
    }
    return;
}

/*void triggers::AddCut(std::string cut){
  DeepCSV ->GetXaxis()->FindBin(cut.c_str());
  mass    ->GetXaxis()->FindBin(cut.c_str());
  //cutL1->GetXaxis()->FindBin(cut.c_str()); 
  return;
}*/


mass::~mass(){} 

