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
    TH1F*   deepCSVb_l    ;
    TH1F*   deepCSVbb_l    ;

    TH1F*   SoftMu     ;
    TH1F*   nSoftMu        ;
    TH1F*   pt_wo_bRegCorr;
    TH1F*   bRegCorr;

    TH1F*   SoftEl     ;
    TH1F*   nSoftEl        ;

    TH1F* flavour       ;
    TH1F* flavourCleaned;
    TH1F* partonFlavour ;
    TH1F* hadronFlavour ;
    TH1F* nbHadrons     ;
    TH1F* ncHadrons     ;
    TH1F* SF     ;

    TH1F* matched_dPt      = NULL;
    TH1F* matched_dEta     ;
    TH1F* matched_dPhi     ;
    TH1F* matched_dR       ;
    TH1F* matched_dcsv     ;
    TH1F* matched_dDeepcsv ;

    TH1F* matched_dRAll    = NULL ;
    TH1F* matched_dRBjet   = NULL ;

    trackHists* tracks = NULL;
    trackHists* tracks_noV0 = NULL;

    btaggingHists* btags = NULL;
    btaggingHists* btags_noV0 = NULL;

    jetHists(std::string, fwlite::TFileService&, std::string title = "", std::string jetDetailLevel = "");
    void Fill(const std::shared_ptr<jet>&, float);
    ~jetHists(); 

  };

}
#endif // jetHists_H
