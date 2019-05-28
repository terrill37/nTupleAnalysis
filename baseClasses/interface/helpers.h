// -*- C++ -*-

#if !defined(Helpers_H)
#define Helpers_H


#include "nTupleAnalysis/baseClasses/interface/muonData.h"
#include "nTupleAnalysis/baseClasses/interface/elecData.h"
#include <TLorentzVector.h>

namespace nTupleAnalysis {

  bool failOverlap(const TLorentzVector& jet,const std::vector<muonPtr>& muons, float dRCut = 0.4) {
    
    for( muonPtr m : muons){
      if(jet.DeltaR(m->p) < dRCut)
	return true;
    }
    return false;
  }


  bool failOverlap(const TLorentzVector& jet,const std::vector<elecPtr>& elecs, float dRCut = 0.4) {
    
    for( elecPtr e : elecs){
      if(jet.DeltaR(e->p) < dRCut)
	return true;
    }
    return false;
  }


}
#endif // Helpers_H
