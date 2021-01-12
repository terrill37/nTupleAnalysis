//#include "TChain.h"
#include "nTupleAnalysis/baseClasses/interface/triggers.h"

using namespace nTupleAnalysis;

triggers::triggers(std::string name, fwlite::TFileService& fs) {

  dir = fs.mkdir(name);
  full = dir.make<TH1F>("full", (name+"/test; ;Entries").c_str(), 64, 0, 64);
  trig_count = dir.make<TH1F>("trig_count", (name+"/trig_count; ;Entries").c_str(), 1, 1, 2);
  //trig_count2= dir.make<TH1F>("trig_count2", (name+"/trig_count2; ;Entries").c_str(), 1, 1, 2);
  pt_all = dir.make<TH1F>("pt_all", (name+"/test; Entries").c_str(), 100, 0, 1000);
  pt_cut = dir.make<TH1F>("pt_cut", (name+"/test; Entries").c_str(), 100, 0, 1000);
  pt_initial = dir.make<TH1F>("pt_initial", (name+"/test; Entries").c_str(), 100, 0, 1000); 
 
 // cutL1  = dir.make<TH1F>("cutL1", (name+"/test; ;Entries").c_str(), 64, 0, 64);
}


void triggers::Fill(long unsigned int cut){
  full  ->Fill(cut);
  //cutL1 ->Fill(cut);

  return;
}

void triggers::AddTrig(std::string cut){
  trig_count ->GetXaxis()->FindBin(cut.c_str());
 // trig_count2 ->GetXaxis()->FindBin(cut.c_str()); 
  return;
}

void triggers::Fill_trigCount(std::string cut){
  trig_count ->Fill(cut.c_str(), 1);
  //weighted  ->Fill(cut.c_str(), weight);
  return;
}

/*void triggers::Fill_trigCount2(std::string cut){
  trig_count2 ->Fill(cut.c_str(), 1);
  return;
}*/

void triggers::Fillpt_all(float pt){
  pt_all->Fill(pt);
  return;
}

void triggers::Fillpt_cut(float pt){
  pt_cut->Fill(pt);
  return;
}

void triggers::Fillpt_initial(float pt){
  pt_initial->Fill(pt);
  return;
}

triggers::~triggers(){} 

