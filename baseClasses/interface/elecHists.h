// -*- C++ -*-
#if !defined(elecHists_H)
#define elecHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/elecData.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"

namespace nTupleAnalysis {

  class elecHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;
    TH1F* quality;
    TH1F* isolation;
    TH1F* isolation_cor;
    TH1F* isolation_cor_s;
    TH1F* dR;
    TH1F* nElecs;
    TH1F* SF;

    elecHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(const elecPtr&, float);
    ~elecHists(); 

  };

}
#endif // elecHists_H
