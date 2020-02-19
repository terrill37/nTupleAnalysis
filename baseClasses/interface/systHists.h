// -*- C++ -*-
#if !defined(systHists_H)
#define systHists_H

#include <iostream>
#include <TH1F.h>
#include <TLorentzVector.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"

namespace nTupleAnalysis {

  class systHists {
  public:
    
    std::map <std::string, TH1F*> hists;

    systHists(TH1F*, std::vector<std::string>&);

    void makeHists(TH1F*, std::vector<std::string>&);
    void Fill(float, float, std::map<std::string, float>&, float denom = 1);

    ~systHists(); 

  };

}
#endif // systHists_H
