// -*- C++ -*-
#if !defined(mass_H)
#define mass_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"

namespace nTupleAnalysis {

  class mass {
  public:
    TFileDirectory dir;
    
    TH1F* DeepCSV;
    TH1F* invariant_mass;
    TH1F* Ht;
    TH1F* pt_1;
    TH1F* pt_2;
    TH1F* pt_3;
    TH1F* pt_4;
    
    TH1F* pt_1_cut;
    TH1F* pt_2_cut;
    TH1F* pt_3_cut;
    TH1F* pt_4_cut;
   

    mass(std::string, fwlite::TFileService&);
    void Fill(const std::shared_ptr<jet>&, float);
    void FillMass(const float);
    void FillHt(const float);
    void Fillpts(std::vector<float>);
    //void AddCut(std::string cut);
    ~mass(); 

  };

}
#endif // cutflowHists_H
