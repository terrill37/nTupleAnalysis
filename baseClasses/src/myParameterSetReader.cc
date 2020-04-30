// Uncomment for SLC6
#define NTUPLEANALYSIS_SLC6 1

#if defined NTUPLEANALYSIS_SLC6

#include "nTupleAnalysis/baseClasses/interface/myParameterSetReader.h"
#include "FWCore/PythonParameterSet/interface/PythonProcessDesc.h"
#include "nTupleAnalysis/baseClasses/interface/myMakeParameterSets.h"

std::unique_ptr<edm::ParameterSet> edm::readPSetsFrom(std::string const& fileOrString, int argc, char* argv[]) {
  return edm::boost_python::readPSetsFrom(fileOrString, argc, argv);
}

#endif
