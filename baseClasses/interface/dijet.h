// -*- C++ -*-

#if !defined(dijet_H)
#define dijet_H
#include <iostream>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/jetData.h"

namespace nTupleAnalysis {
  const float mW =  80.4;
  const float mZ =  91.0;
  const float mH = 125.0;

  //dijet object
  class dijet {

  public:
    TLorentzVector p1;
    TLorentzVector p2;

    std::shared_ptr<jet> lead;
    std::shared_ptr<jet> subl;

    TLorentzVector p;
    float dR;
    float st;
    float pt;
    float eta;
    float phi;
    float m;
    float e;

    TLorentzVector pW;
    TLorentzVector pZ;
    TLorentzVector pH;

    float xW;
    float xZ;
    float xH;

    //dijet();
    dijet(std::shared_ptr<jet>&, std::shared_ptr<jet>&, bool undo_bJES=false); 
    ~dijet(); 

    //void dump();
  };

}
#endif // dijet_H

