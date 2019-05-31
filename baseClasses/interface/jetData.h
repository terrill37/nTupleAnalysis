// -*- C++ -*-

#if !defined(jetData_H)
#define jetData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"
#include "nTupleAnalysis/baseClasses/interface/trackData.h"
#include "nTupleAnalysis/baseClasses/interface/btaggingData.h"



namespace nTupleAnalysis {


  //forward declaration for use in jet constructor from tree
  class jetData;
  //jet object
  class jet {

  public:
    UChar_t cleanmask;

    float pt;
    float eta;
    float phi;
    float m;
    float e;
    TLorentzVector p;

    float bRegCorr;

    float deepB;
    float CSVv2;
    float deepFlavB;



    //
    //  Tracks in Jet
    //
    float nFirstTrack;
    float nLastTrack;
    std::vector<trackPtr> tracks;

    //
    // SVs in Jet
    //
    std::vector<svPtr> svs;

    //
    // SVs in Jet
    //
    std::vector<trkTagVarPtr> trkTagVars;


    //
    //  Matched Jets

    //
    float match_dR = -99;
    std::weak_ptr<jet>  matchedJet;



    jet();
    jet(UInt_t, jetData*); 
    jet(TLorentzVector&, float tag = -1); 
    void bRegression();
    ~jet(); 

    //void dump();
  };

  typedef std::shared_ptr<jet> jetPtr;


  //class for tree access
  class jetData {

  public:
    UInt_t n;
    //ULong64_t n;

    UChar_t cleanmask[100];

    float pt [100];
    float eta[100];
    float phi[100];
    float m  [100];

    float bRegCorr[100];

    float deepB[100];
    float CSVv2[100];
    float deepFlavB[100];

    int nFirstTrack[100];
    int nLastTrack[100];
    trackData* trkData = nullptr;


    int nFirstSV[100];
    int nLastSV[100];

    int nFirstTrkTagVar[100];
    int nLastTrkTagVar [100];

    btaggingData* btagData = nullptr;

    jetData(std::string, TChain*, std::string prefix = ""); 
    std::vector< std::shared_ptr<jet> > getJets(float ptMin = -1e6, float ptMax = 1e6, float etaMax = 1e6, bool clean = false, float tagMin = -1e6, std::string tagger = "CSVv2", bool antiTag = false);
    std::vector< std::shared_ptr<jet> > getJets(std::vector< std::shared_ptr<jet> > inputJets, 
						float ptMin = -1e6, float ptMax = 1e6, float etaMax = 1e6, bool clean = false, float tagMin = -1e6, std::string tagger = "CSVv2", bool antiTag = false);
    ~jetData(); 

    //void dump();
  };



}
#endif // jetData_H

