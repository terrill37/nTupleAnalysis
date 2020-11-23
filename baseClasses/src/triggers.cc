//#include "TChain.h"
#include "nTupleAnalysis/baseClasses/interface/triggers.h"

using namespace nTupleAnalysis;

triggers::triggers(std::string name, fwlite::TFileService& fs) {

  dir = fs.mkdir(name);
  full = dir.make<TH1F>("full", (name+"/test; ;Entries").c_str(), 64, 0, 64);
  pt_all = dir.make<TH1F>("pt_all", (name+"/test; Entries").c_str(), 100, 0, 1000);
  pt_cut = dir.make<TH1F>("pt_cut", (name+"/test; Entries").c_str(), 100, 0, 1000);
 
 
 // cutL1  = dir.make<TH1F>("cutL1", (name+"/test; ;Entries").c_str(), 64, 0, 64);
}


void triggers::Fill(long unsigned int cut){
  full  ->Fill(cut);
  //cutL1 ->Fill(cut);

  return;
}

void triggers::AddCut(std::string cut){
  full ->GetXaxis()->FindBin(cut.c_str());
  //cutL1->GetXaxis()->FindBin(cut.c_str()); 
  return;
}

void triggers::Fillpt_all(float pt){
  pt_all->Fill(pt);
}

void triggers::Fillpt_cut(float pt){
  pt_cut->Fill(pt);
}

triggers::~triggers(){} 

