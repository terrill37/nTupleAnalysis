// -*- C++ -*-
#if !defined(vertexHists_H)
#define vertexHists_H

#include <iostream>
#include <vector>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/vertexData.h"

namespace nTupleAnalysis {

  class vertexHists {
  public:
    TFileDirectory dir;
    
    TH1F* n     ;
    TH1F* nGood    ;
    TH1F* nReal    ;
    TH1F* nRealGood;

    TH1F* x     ;
    TH1F* y     ;
    TH1F* z     ;
    TH1F* ex    ;
    TH1F* ey    ;
    TH1F* ez    ;
    TH1F* chi2  ;
    TH1F* ndf   ;
    TH1F* ndf_l   ;
    TH1F* isgood;
    TH1F* isfake;

    //  Diff Hits
    TH1F*  dx   ;
    TH1F*  dy   ;
    TH1F*  dz   ;
    TH1F*  dz_l ;
    TH1F*  dex   ;
    TH1F*  dey   ;
    TH1F*  dez   ;
    TH1F*  dchi2  ;
    TH1F*  dndf   ;
    TH2F*  nVsN ;

    vertexHists(std::string, fwlite::TFileService&, std::string title = "");
    void makeDiffHists(std::string, fwlite::TFileService&, std::string title = "");
    void Fill(const std::vector<vertexPtr>& vtxs, float weight);
    void FillDiffHists(const std::vector<vertexPtr> &vtxs1, const std::vector<vertexPtr> &vtxs2, float weight);
    ~vertexHists(); 

  };

}
#endif // vertexHists_H
