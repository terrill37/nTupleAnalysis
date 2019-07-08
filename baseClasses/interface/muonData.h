// -*- C++ -*-

#if !defined(muonData_H)
#define muonData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"

namespace nTupleAnalysis {
  //forward declaration for use in muon constructor from tree
  class muonData;
  //muon object
  class muon {

  public:
    float pt;
    float eta;
    float phi;
    float m;
    TLorentzVector p;

    bool    softId;
    UChar_t highPtId;

    bool mediumId;
    bool tightId;

    int quality;

    int jetIdx;
    float isolation;
    float isolation_corrected;
    float isolation_trackerOnly;
    float dR = 1e6;

    muon(UInt_t, muonData*); 
    ~muon(); 

    //void dump();
  };

  typedef std::shared_ptr<muon> muonPtr;

  //class for tree access
  class muonData {

  public:
    std::string m_name;
    static const unsigned int MAXMUONS = 20;

    
    Int_t n;

    float pt [MAXMUONS];
    float eta[MAXMUONS];
    float phi[MAXMUONS];
    float m  [MAXMUONS] = {0};

    Bool_t  softId[MAXMUONS];
    UChar_t highPtId[MAXMUONS];

    Bool_t mediumId[MAXMUONS];
    Bool_t tightId[MAXMUONS];

    int jetIdx[MAXMUONS];
    float pfRelIso04_all[MAXMUONS];
    float isolation_corrected[MAXMUONS];
    float isolation_trkIsoOnly[MAXMUONS];
    
    muonData(std::string, TChain*); 
    std::vector<std::shared_ptr<muon>> getMuons(float ptMin = -1e6, float etaMax = 1e6, int tag = -1, bool isolation = false);
    ~muonData(); 

    //void dump();
  };

}
#endif // muonData_H

