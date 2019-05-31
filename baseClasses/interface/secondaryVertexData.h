// -*- C++ -*-

#if !defined(secondaryVertexData_H)
#define secondaryVertexData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"


namespace nTupleAnalysis {


  //forward declaration for use in secondaryVertex constructor from tree
  class secondaryVertexData;
  //secondaryVertex object
  class secondaryVertex {

  public:

    float x                 ;
    float y                 ;
    float z                 ;
    float ex                ;    
    float ey                ;
    float ez                ;
    float chi2              ;
    float ndf               ;
    float flight            ;
    float flightErr         ;
    float deltaR_jet        ;
    float deltaR_sum_jet    ;
    float deltaR_sum_dir    ;
    float vtx_pt            ;
    float flight2D          ;
    float flight2DErr       ;
    float totCharge         ;
    float vtxDistJetAxis    ;
    float nTrk              ;
    float mass              ;
    float vtx_eta           ;
    float vtx_phi           ;
    float EnergyRatio       ;
    float dir_x             ;
    float dir_y             ;
    float dir_z             ;

    secondaryVertex();
    secondaryVertex(UInt_t, secondaryVertexData*); 

    ~secondaryVertex(); 

    //void dump();
  };

  typedef std::shared_ptr<secondaryVertex> svPtr;


  //class for tree access
  class secondaryVertexData {

  public:

    //int   nSV;
    float x                 [100];
    float y                 [100];
    float z                 [100];
    float ex                [100];
    float ey                [100];
    float ez                [100];
    float chi2              [100];
    float ndf               [100];
    float flight            [100];
    float flightErr         [100];
    float deltaR_jet        [100];
    float deltaR_sum_jet    [100];
    float deltaR_sum_dir    [100];
    float vtx_pt            [100];
    float flight2D          [100];
    float flight2DErr       [100];
    float totCharge         [100];
    float vtxDistJetAxis    [100];
    float nTrk              [100];
    float mass              [100];
    float vtx_eta           [100];
    float vtx_phi           [100];
    float EnergyRatio       [100];
    float dir_x             [100];
    float dir_y             [100];
    float dir_z             [100];

    secondaryVertexData(std::string, TChain*); 
    std::vector< std::shared_ptr<secondaryVertex> > getSecondaryVertices(int nFirstSV, int nLastSV);

    ~secondaryVertexData(); 

    //void dump();
  };



}
#endif // secondaryVertexData_H

