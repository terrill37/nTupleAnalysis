// -*- C++ -*-
#if !defined(events_H)
#define events_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"

namespace nTupleAnalysis {

  class events {
  public:
    TFileDirectory dir;
    
    TH1F* events_all;
    TH1F* events_pt;
    TH1F* events_eta;
    TH1F* events_b;
    TH1F* events_L1;
    TH1F* events_quad;
    TH1F* events_ht;
    TH1F* events_tri;

    events(std::string, fwlite::TFileService&);
    void FillAll(std::vector<int>);
    //void AddCut(std::string cut);
    ~events(); 

  };

}
#endif // cutflowHists_H
