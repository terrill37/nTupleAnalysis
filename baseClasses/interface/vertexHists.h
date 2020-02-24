// -*- C++ -*-
#if !defined(vertexHists_H)
#define vertexHists_H

#include <iostream>
#include <vector>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/vertexData.h"

namespace nTupleAnalysis {

  class vertexHists {
  public:
    TFileDirectory dir;
    
    TH1F* x     ;
    TH1F* y     ;
    TH1F* z     ;
    TH1F* ex    ;
    TH1F* ey    ;
    TH1F* ez    ;
    TH1F* chi2  ;
    TH1F* ndf   ;
    TH1F* isgood;
    TH1F* isfake;

    vertexHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(const std::vector<vertexPtr>& vtxs, float weight);
    ~vertexHists(); 

  };

}
#endif // vertexHists_H
