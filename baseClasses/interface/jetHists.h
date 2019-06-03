// -*- C++ -*-
#if !defined(jetHists_H)
#define jetHists_H

#include <iostream>
#include <TH1F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"
#include "nTupleAnalysis/baseClasses/interface/fourVectorHists.h"
#include "nTupleAnalysis/baseClasses/interface/trackHists.h"
#include "nTupleAnalysis/baseClasses/interface/btaggingHists.h"

namespace nTupleAnalysis {

  class jetHists {
  public:
    TFileDirectory dir;
    
    fourVectorHists* v;
    TH1F* cleanmask;
    TH1F* deepB;
    TH1F* CSVv2;
    TH1F* deepFlavB;
    TH1F* nJets;
    TH1F* nTrksExpected;

    trackHists* tracks;
    btaggingHists* btags;

    jetHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(const std::shared_ptr<jet>&, float);
    ~jetHists(); 

  };

}
#endif // jetHists_H
