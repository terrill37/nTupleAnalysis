// -*- C++ -*-
#if !defined(muonHists_H)
#define muonHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/muonData.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"

namespace nTupleAnalysis {

  class muonHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;
    TH1F* quality;
    TH1F* isolation;
    TH1F* isolation_cor;
    TH1F* isolation_cor_s;
    TH1F* dR;
    TH1F* nMuons;
    TH1F* SF;

    muonHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(const muonPtr&, float);
    ~muonHists(); 

  };

}
#endif // muonHists_H
