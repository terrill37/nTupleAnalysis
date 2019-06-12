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

    TH1F*   ntracks    ;
    TH1F*   nseltracks ;
    TH1F*   CSVv2_l    ;
    TH1F*   deepCSV_l    ;

    TH1F*   SoftMu     ;
    TH1F*   nSoftMu        ;

    TH1F*   SoftEl     ;
    TH1F*   nSoftEl        ;

    TH1F* flavour       ;
    TH1F* flavourCleaned;
    TH1F* partonFlavour ;
    TH1F* hadronFlavour ;
    TH1F* nbHadrons     ;
    TH1F* ncHadrons     ;

    trackHists* tracks;
    btaggingHists* btags;

    btaggingHists* btags_noV0;
    trackHists*    tracks_noV0;

    jetHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(const std::shared_ptr<jet>&, float);
    ~jetHists(); 

  };

}
#endif // jetHists_H
