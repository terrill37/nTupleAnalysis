// -*- C++ -*-

#if !defined(EventDisplayData_H)
#define EventDisplayData_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "nTupleAnalysis/baseClasses/interface/jetData.h"
#include "nTupleAnalysis/baseClasses/interface/trackData.h"

namespace nTupleAnalysis {

  class EventDisplayData {


  public: 
    
    // Create a root
    boost::property_tree::ptree oroot;
     
    std::map<std::string, boost::property_tree::ptree> m_OneEvent_info;
    std::map<std::string, boost::property_tree::ptree> m_AllEvent_info;

    int m_nDisplays = 0;

    std::string m_name;

    std::vector<std::string> m_jetNames;
    std::vector<std::string> m_trkNames;
    std::vector<std::string> m_varNames;

    void addJetCollection(std::string jName) { m_jetNames.push_back(jName); };
    void addTrkCollection(std::string tName) { m_trkNames.push_back(tName); };
    void addEventVar     (std::string vName) { m_varNames.push_back(vName); };
    
  public:

    EventDisplayData(std::string name);
    
    ~EventDisplayData() {}; 

    void AddJet      (std::string jetName, const jetPtr& jetData, bool doTracks=false, bool debug=false);
    void AddTrk      (std::string trkName, const trackPtr& trkData, bool debug=false);
    void AddEventVar (std::string varName, float var , bool debug=false);

    void NewEvent();

    void Write();
  };

}
#endif // EventDisplayData_H
