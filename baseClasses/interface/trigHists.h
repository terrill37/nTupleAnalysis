// -*- C++ -*-
#if !defined(trigHists_H)
#define trigHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/trigData.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"

namespace nTupleAnalysis {

  class trigHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;    
    TH1F* l1pt_s;
    TH1F* l1pt_m;
    TH1F* l1pt_l;

    TH1F* l1_2pt_s;
    TH1F* l1_2pt_m;
    TH1F* l1_2pt_l;

    TH1F* id;
    TH1F* filterBits;


    trigHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(std::shared_ptr<trig>&, float);
    ~trigHists(); 

  };

}
#endif // trigHists_H
