// -*- C++ -*-

#if !defined(trigData_H)
#define trigData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"

namespace nTupleAnalysis {
  //forward declaration for use in trig constructor from tree
  class trigData;
  //trig object
  class trig {

  public:
    float pt;
    float eta;
    float phi;
    float m;
    float e;
    TLorentzVector p;

    float l1pt;
    float l1pt_2;
    float l2pt;
    int id;
    int filterBits;


    trig();
    trig(UInt_t, trigData*); 
    ~trig(); 

    //void dump();
  };

  typedef std::shared_ptr<trig> trigPtr;

  //class for tree access
  class trigData {

  public:
    UInt_t nTrigObjs;

    static const unsigned int MAXTRIGS = 1000;


    float pt [MAXTRIGS];
    float eta[MAXTRIGS];
    float phi[MAXTRIGS];

    float l1pt[MAXTRIGS];
    float l1pt_2[MAXTRIGS];
    float l2pt[MAXTRIGS];
    int id[MAXTRIGS];
    int filterBits[MAXTRIGS];

    trigData(std::string, TChain*); 
    std::vector<std::shared_ptr<trig>> getTrigs(float ptMin = -1e6, float etaMax = 1e6, int objId = 0);
    std::vector<trigPtr> getTrigs(std::vector<trigPtr> inputTrigs, float ptMin = -1e6, float etaMax = 1e6, int objId = 0);
    ~trigData(); 

    //void dump();
  };

}
#endif // trigData_H

