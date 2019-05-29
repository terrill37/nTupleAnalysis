// -*- C++ -*-

#if !defined(trackData_H)
#define trackData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"


namespace nTupleAnalysis {


  //forward declaration for use in track constructor from tree
  class trackData;
  //track object
  class track {

  public:

    float pt;
    float eta;
    float phi;
    float m;
    float e;
    TLorentzVector p;
    float dR                   ;

    float dxy                  ;
    float dz                   ;
    float dxyError             ;
    float dzError              ;
    int   sign2D               ;
    int   sign3D               ;
    float length               ;
    float dist                 ;
    float IP2D                 ;
    float IP2Dsig              ;
    float IP2Derr              ;
    float IP                   ;
    float IPsig                ;
    float IPerr                ;
    float Proba                ;
    float chi2                 ;
    int   charge               ;
    int   history              ;
    int   nHitStrip            ;
    int   nHitPixel            ;
    int   nHitAll              ;
    int   nHitTIB              ;
    int   nHitTID              ;
    int   nHitTOB              ;
    int   nHitTEC              ;
    int   nHitPXB              ;
    int   nHitPXF              ;
    int   isHitL1              ;
    int   PV                   ;
    int   SV                   ;
    float PVweight             ;
    float SVweight             ;
    int   isfromSV             ;
    int   isfromV0             ;
    int   category             ;
    int   algo                 ;
    int   originalAlgo         ;
    float TPAssociationQuality ;
    int   idxMatchedTP         ;

    float match_dR = -99;
    int   nMatches = 0;
    std::shared_ptr<track>  matchedTrack  = nullptr;
    std::shared_ptr<track>  secondClosest = nullptr;

    track();
    track(UInt_t, trackData*); 

    ~track(); 

    //void dump();
  };

  typedef std::shared_ptr<track> trackPtr;


  //class for tree access
  class trackData {

  public:

    int   nTrack;
    float dxy                   [100];
    float dz                    [100];
    float dxyError              [100];
    float dzError               [100];
    int   sign2D                [100];
    int   sign3D                [100];
    float length                [100];
    float dist                  [100];
    float IP2D                  [100];
    float IP2Dsig               [100];
    float IP2Derr               [100];
    float IP                    [100];
    float IPsig                 [100];
    float IPerr                 [100];
    float Proba                 [100];
    float p                     [100];
    float pt                    [100];
    float eta                   [100];
    float phi                   [100];
    float chi2                  [100];
    int   charge                [100];
    int   history               [100];
    int   nHitStrip             [100];
    int   nHitPixel             [100];
    int   nHitAll               [100];
    int   nHitTIB               [100];
    int   nHitTID               [100];
    int   nHitTOB               [100];
    int   nHitTEC               [100];
    int   nHitPXB               [100];
    int   nHitPXF               [100];
    int   isHitL1               [100];
    int   PV                    [100];
    int   SV                    [100];
    float PVweight              [100];
    float SVweight              [100];
    int   isfromSV              [100];
    int   isfromV0              [100];
    int   category              [100];
    int   algo                  [100];
    int   originalAlgo          [100];
    float TPAssociationQuality  [100];
    int   idxMatchedTP          [100];


    trackData(std::string, TChain*); 
    std::vector< std::shared_ptr<track> > getTracks(int nFirstTrack, int nLastTrack);

    ~trackData(); 

    //void dump();
  };



}
#endif // trackData_H

