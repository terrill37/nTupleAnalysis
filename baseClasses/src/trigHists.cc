#include "nTupleAnalysis/baseClasses/interface/trigHists.h"
#include <bitset>

using namespace nTupleAnalysis;

trigHists::trigHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir);

    l1pt_s = dir.make<TH1F>("l1pt_s", (name+"/l1pt_s; "+title+" L1 p_T [GeV]; Entries").c_str(),  100,0, 100);
    l1pt_m = dir.make<TH1F>("l1pt_m", (name+"/l1pt_m; "+title+" L1 p_T [GeV]; Entries").c_str(),  100,0, 500);
    l1pt_l = dir.make<TH1F>("l1pt_l", (name+"/l1pt_l; "+title+" L1 p_T [GeV]; Entries").c_str(),  100,0,1000);

    l1_2pt_s = dir.make<TH1F>("l1_2pt_s", (name+"/l1_2pt_s; "+title+" L1_2 p_T [GeV]; Entries").c_str(),  100,0, 100);
    l1_2pt_m = dir.make<TH1F>("l1_2pt_m", (name+"/l1_2pt_m; "+title+" L1_2 p_T [GeV]; Entries").c_str(),  100,0, 500);
    l1_2pt_l = dir.make<TH1F>("l1_2pt_l", (name+"/l1_2pt_l; "+title+" L1_2 p_T [GeV]; Entries").c_str(),  100,0,1000);

    id     = dir.make<TH1F>("id",     (name+"/id; "    +title+" TrigID; Entries").c_str(), 30,-0.5,29.5);
    filterBits     = dir.make<TH1F>("filterBits",     (name+"/filterBits; "    +title+" filterBits; Entries").c_str(), 10,-0.5,9.5);

} 

void trigHists::Fill(std::shared_ptr<trig> &trigInfo, float weight){

  v->Fill(trigInfo->p, weight);

  l1pt_s->Fill(trigInfo->l1pt, weight);
  l1pt_m->Fill(trigInfo->l1pt, weight);
  l1pt_l->Fill(trigInfo->l1pt, weight);

  l1_2pt_s->Fill(trigInfo->l1pt_2, weight);
  l1_2pt_m->Fill(trigInfo->l1pt_2, weight);
  l1_2pt_l->Fill(trigInfo->l1pt_2, weight);

  id->Fill(trigInfo->id, weight);

  //std::cout << trigInfo->id << " " << trigInfo->filterBits << std::endl;
  std::bitset<10> b2(trigInfo->filterBits);
  for(unsigned int iidx = 0; iidx < 10; ++iidx){
    if(b2[iidx])
      filterBits->Fill(iidx, weight);
  }
  return;
}

trigHists::~trigHists(){} 
