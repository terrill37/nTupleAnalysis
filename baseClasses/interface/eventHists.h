// -*- C++ -*-
#if !defined(eventHists_H)
#define eventHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"

namespace nTupleAnalysis {

  class eventHists {
  public:
    TFileDirectory dir;
    
    TH1F* nPV;
    TH1F* pu;

    eventHists(std::string, fwlite::TFileService&);
    void Fill(float, float, float);
    ~eventHists(); 

  };

}
#endif // eventHists_H
