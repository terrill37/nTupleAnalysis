// -*- C++ -*-

#if !defined(elecData_H)
#define elecData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"

namespace nTupleAnalysis {
  //forward declaration for use in elec constructor from tree
  class elecData;
  //elec object
  class elec {

  public:
    float pt;
    float eta;
    float superClusterEta;
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
    float dR = 1e6;

    float sumChargedHadronPt;
    float sumNeutralHadronEt;
    float sumPhotonEt       ;
    float sumPUPt           ;


    elec(UInt_t, elecData*); 
    ~elec(); 

    //void dump();
  };

  typedef std::shared_ptr<elec> elecPtr;

  //class for tree access
  class elecData {

  public:
    std::string m_name;
    static const unsigned int MAXELECS = 10;

    UInt_t n;

    float pt [MAXELECS];
    float eta[MAXELECS];
    float superClusterEta[MAXELECS];
    float phi[MAXELECS];
    float m  [MAXELECS] = {0};

    Bool_t  softId[MAXELECS];
    UChar_t highPtId[MAXELECS];

    Bool_t mediumId[MAXELECS];
    Bool_t tightId[MAXELECS];

    int jetIdx[MAXELECS];
    float pfRelIso04_all[MAXELECS];

    float sumChargedHadronPt [MAXELECS];
    float sumNeutralHadronEt [MAXELECS];
    float sumPhotonEt        [MAXELECS];
    float sumPUPt            [MAXELECS];
    
    elecData(std::string, TChain*); 
    std::vector<std::shared_ptr<elec>> getElecs(float ptMin = -1e6, float etaMax = 1e6, int tag = -1, bool isolation = false);
    ~elecData(); 

    //void dump();
  };

}
#endif // elecData_H

