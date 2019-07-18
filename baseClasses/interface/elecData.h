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
    float dR = 1e6;

    elec(UInt_t, elecData*); 
    ~elec(); 

    //void dump();
  };

  typedef std::shared_ptr<elec> elecPtr;

  //class for tree access
  class elecData {

  public:
    UInt_t n;

    float pt [10];
    float eta[10];
    float phi[10];
    float m  [10] = {0};

    Bool_t  softId[10];
    UChar_t highPtId[10];

    Bool_t mediumId[10];
    Bool_t tightId[10];

    int jetIdx[10];
    float pfRelIso04_all[10];
    
    elecData(std::string, TChain*); 
    std::vector<std::shared_ptr<elec>> getElecs(float ptMin = -1e6, float etaMax = 1e6, int tag = -1, bool isolation = false);
    ~elecData(); 

    //void dump();
  };

}
#endif // elecData_H

