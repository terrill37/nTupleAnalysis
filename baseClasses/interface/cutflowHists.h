// -*- C++ -*-
#if !defined(cutflowHists_H)
#define cutflowHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"

namespace nTupleAnalysis {

  class cutflowHists {
  public:
    TFileDirectory dir;
    
    TH1F* unitWeight;
    TH1F* weighted;
    //TH1F* test;

    cutflowHists(std::string, fwlite::TFileService&);
    void Fill(std::string, float weight);
    void AddCut(std::string cut);
    ~cutflowHists(); 

  };

}
#endif // cutflowHists_H
