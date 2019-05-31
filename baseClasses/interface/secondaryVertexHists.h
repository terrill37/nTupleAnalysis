// -*- C++ -*-
#if !defined(secondaryVertexHists_H)
#define secondaryVertexHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/btaggingData.h"

namespace nTupleAnalysis {

  class secondaryVertexHists {
  public:
    
    TH1F*   NTracks                    ;
    TH1F*   Mass                       ;
    TH1F*   JetDeltaR                  ;
    TH1F*   FitProb                    ;
    TH1F*   EnergyRatio                ;
    TH1F*   R          ;
    TH1F*   Z          ;
    TH1F*   Chi2       ;
    TH1F*   NDF        ;
    TH1F*   Flight     ;
    TH1F*   FlightSig  ;
    TH1F*   Flight2D   ;
    TH1F*   FlightSig2D;
    TH1F*   Pt         ;
    TH1F*   Eta        ;
    TH1F*   Phi        ;
    TH1F*   DistJetAxis;

    secondaryVertexHists(std::string,       TFileDirectory&, std::string title = "");
    secondaryVertexHists(std::string, fwlite::TFileService&, std::string title = "");

    void makeHists(std::string, TFileDirectory&, std::string title);
    void Fill(const svPtr&, float);

    ~secondaryVertexHists(); 

  };

}
#endif // secondaryVertexHists_H
