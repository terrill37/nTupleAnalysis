// -*- C++ -*-

#if !defined(pileUpWeightTool_H)
#define pileUpWeightTool_H

#include <map>
#include <TFile.h>

namespace nTupleAnalysis {

  class pileUpWeightTool {

  public:

    std::string m_inputFileName;
    std::string m_puWeightHistName = "nPV_weight";
    std::map<int, float> m_weights;

  public:
    
    pileUpWeightTool(std::string inputFileName);
    
    ~pileUpWeightTool(); 

    float getWeight(int nPV);

  };

}
#endif // pileUpWeightTool_H
