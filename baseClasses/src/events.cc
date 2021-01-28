//#include "TChain.h"
#include "nTupleAnalysis/baseClasses/interface/events.h"

using namespace nTupleAnalysis;

events::events(std::string name, fwlite::TFileService& fs) {

  dir = fs.mkdir(name);
  
  events_all  = dir.make<TH1F>("all_Jets",  (name+"/JetCount; ;Entries").c_str(), 12, 0, 12);
  events_pt   = dir.make<TH1F>("Jets_pt",   (name+"/JetCount; ;Entries").c_str(), 12, 0, 12);
  events_eta  = dir.make<TH1F>("Jets_eta",  (name+"/JetCount; ;Entries").c_str(), 12, 0, 12);
  events_b    = dir.make<TH1F>("Jets_b",    (name+"/JetCount; ;Entries").c_str(), 12, 0, 12);
  events_L1   = dir.make<TH1F>("Jets_L1",   (name+"/JetCount; ;Entries").c_str(), 12, 0, 12);
  events_quad = dir.make<TH1F>("Jets_quad", (name+"/JetCount; ;Entries").c_str(), 12, 0, 12);
  events_ht   = dir.make<TH1F>("Jets_Ht",   (name+"/JetCount; ;Entries").c_str(), 12, 0, 12);
  events_tri  = dir.make<TH1F>("Jets_tri",  (name+"/JetCount; ;Entries").c_str(), 12, 0, 12);
}


void events::FillAll(std::vector<int> count){
  
  events_all   ->Fill(count.at(0));
  
  if(count.at(1)!=0){
    events_pt    ->Fill(count.at(1));
  }
  
  if(count.at(2)!=0){
    events_eta   ->Fill(count.at(2));
  }  
  
  if(count.at(3)!=0){
    events_b     ->Fill(count.at(3));
  }  
  
  if(count.at(4)!=0){
    events_L1    ->Fill(count.at(4));
  }
  
  if(count.at(5)!=0){
    events_quad  ->Fill(count.at(5));
  }
  
  if(count.at(6)!=0){
    events_ht    ->Fill(count.at(6));
  }
  
  if(count.at(7)!=0){
    events_tri   ->Fill(count.at(7));
  }

  return;
}





events::~events(){} 

