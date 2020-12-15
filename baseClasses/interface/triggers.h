// -*- C++ -*-
#if !defined(triggers_H)
#define triggers_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"

namespace nTupleAnalysis {

  class triggers {
  public:
    TFileDirectory dir;
    
    TH1F* full;
    TH1F* trig_count;
    TH1F* trig_count2;
    TH1F* pt_all;
    TH1F* pt_cut;
    TH1F* pt_initial;

    //TH1F* cutL1;

    triggers(std::string, fwlite::TFileService&);
    void Fill(long unsigned int);
    void AddTrig(std::string cut);
    void Fill_trigCount(std::string);
    void Fill_trigCount2(std::string);
    void Fillpt_all(float);
    void Fillpt_cut(float);
    void Fillpt_initial(float);
    ~triggers(); 

  };

}
#endif // triggers_H
