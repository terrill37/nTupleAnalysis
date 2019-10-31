// -*- C++ -*-
#if !defined(trijetHists_H)
#define trijetHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/trijet.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"
#include "nTupleAnalysis/baseClasses/interface/dijetHists.h"

namespace nTupleAnalysis {

  class trijetHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;
    dijetHists* W;
    TH1F* dRbW;
    TH1F* mbW;
    TH1F* xWt;

    TH2F* mW_vs_mt;
    TH2F* xW_vs_xt;

    TH1F* deepFlavB_b;
    TH1F* deepFlavB_j;
    TH1F* deepFlavB_l;

    trijetHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(std::shared_ptr<trijet>&, float);
    ~trijetHists(); 

  };

}
#endif // trijetHists_H
