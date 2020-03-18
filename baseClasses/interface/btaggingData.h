// -*- C++ -*-

#if !defined(btaggingData_H)
#define btaggingData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"


namespace nTupleAnalysis {


  //forward declaration for use in secondaryVertex constructor from tree
  class btaggingData;
  //secondaryVertex object
  class secondaryVertex {

  public:
    float e;
    TLorentzVector p;

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

    std::weak_ptr<secondaryVertex>  matchedSV;

    secondaryVertex();
    secondaryVertex(UInt_t, btaggingData*); 

    ~secondaryVertex(); 

    //void dump();
  };

  typedef std::shared_ptr<secondaryVertex> svPtr;


  class trkTagVar {

  public:

    float pt;
    float trackEta	   ;
    float trackPhi	   ;
    float m;
    float e;
    TLorentzVector p;

    float trackMomentum	   ;

    float trackPtRel	   ;
    float trackPPar	   ;
    float trackEtaRel	   ;
    float trackDeltaR	   ;
    float trackPtRatio	   ;
    float trackPParRatio   ;	
    float trackSip2dVal	   ;
    float trackSip2dSig	   ;
    float trackSip3dVal	   ;
    float trackSip3dSig	   ;
    float trackDecayLenVal ;
    float trackDecayLenSig ;
    float trackJetDistVal  ;
    float trackJetDistSig  ;
    float trackChi2	   ;
    float trackNTotalHits  ;
    float trackNPixelHits  ;
    bool  hasTrackMatch = false;
    int   matchIsFromV0 = -99;

    std::weak_ptr<trkTagVar>  matchedTrkTagVar;


    trkTagVar();
    trkTagVar(UInt_t, btaggingData*); 

    ~trkTagVar(); 

    //void dump();
  };

  typedef std::shared_ptr<trkTagVar> trkTagVarPtr;

  class tagVar {

  public:


    int   jetNTracks            ;
    int   jetNSecondaryVertices ;

    int   chargedMultiplicity         ;
    float chargedHadronEnergyFraction ;
    int   chargedHadronMultiplicity   ;
    float chargedEmEnergyFraction     ;
    int   neutralMultiplicity         ;
    float neutralHadronEnergyFraction ;
    int   neutralHadronMultiplicity   ;
    float neutralEmEnergyFraction     ;
    float photonEnergyFraction        ;   
    int   photonMultiplicity          ;   
    float muonEnergyFraction          ;   
    int   muonMultiplicity            ;   
    float electronEnergyFraction      ;   
    int   electronMultiplicity        ;   
    int   numberOfDaughters           ;   


    tagVar();
    tagVar(UInt_t, btaggingData*); 

    ~tagVar(); 

    //void dump();
  };

  typedef std::shared_ptr<tagVar> tagVarPtr;




  //class for tree access
  class btaggingData {

  public:

    int   nSV;
    bool  haveSVs = false;
    float sv_x                 [100];
    float sv_y                 [100];
    float sv_z                 [100];
    float sv_ex                [100];
    float sv_ey                [100];
    float sv_ez                [100];
    float sv_chi2              [100];
    float sv_ndf               [100];
    float sv_flight            [100];
    float sv_flightErr         [100];
    float sv_deltaR_jet        [100];
    float sv_deltaR_sum_jet    [100];
    float sv_deltaR_sum_dir    [100];
    float sv_vtx_pt            [100];
    float sv_flight2D          [100];
    float sv_flight2DErr       [100];
    float sv_totCharge         [100];
    float sv_vtxDistJetAxis    [100];
    int   sv_nTrk              [100];
    float sv_mass              [100];
    float sv_vtx_eta           [100];
    float sv_vtx_phi           [100];
    float sv_EnergyRatio       [100];
    float sv_dir_x             [100];
    float sv_dir_y             [100];
    float sv_dir_z             [100];

    bool  haveTrkTagVars = false;
    float trackMomentum	    [100];
    float trackEta	    [100];
    float trackPhi	    [100];
    float trackPtRel	    [100];
    float trackPPar	    [100];
    float trackEtaRel	    [100];
    float trackDeltaR	    [100];
    float trackPtRatio	    [100];
    float trackPParRatio    [100];	
    float trackSip2dVal	    [100];
    float trackSip2dSig	    [100];
    float trackSip3dVal	    [100];
    float trackSip3dSig	    [100];
    float trackDecayLenVal  [100];
    float trackDecayLenSig  [100];
    float trackJetDistVal   [100];
    float trackJetDistSig   [100];
    float trackChi2	    [100];
    float trackNTotalHits   [100];
    float trackNPixelHits   [100];

    bool  haveTagVars = false;
    int   jetNTracks            [100];
    int   jetNSecondaryVertices [100];
    int   chargedMultiplicity         [100];
    float chargedHadronEnergyFraction [100];
    int   chargedHadronMultiplicity   [100];
    float chargedEmEnergyFraction     [100];
    int   neutralMultiplicity         [100];
    float neutralHadronEnergyFraction [100];
    int   neutralHadronMultiplicity   [100];
    float neutralEmEnergyFraction     [100];
    float photonEnergyFraction        [100];   
    int   photonMultiplicity          [100];   
    float muonEnergyFraction          [100];   
    int   muonMultiplicity            [100];   
    float electronEnergyFraction      [100];   
    int   electronMultiplicity        [100];   
    int   numberOfDaughters           [100];   


    btaggingData(); 

    void initSecondaryVerticies(std::string name, TTree* tree);
    std::vector<svPtr> getSecondaryVertices(int nFirstSV, int nLastSV, bool debug);

    void initTrkTagVar(std::string name, TTree* tree);
    std::vector<trkTagVarPtr> getTrkTagVars(int nFirstTrkTagVar, int nLastTrkTagVar);

    void initTagVar(std::string name, TTree* tree);
    tagVarPtr getTagVars(int jetIdx);

    ~btaggingData(); 

    //void dump();
  };



}
#endif // btaggingData_H

