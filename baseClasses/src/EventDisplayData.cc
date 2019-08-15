#include <iostream>
#include <fstream>
#include "TChain.h"


#include "nTupleAnalysis/baseClasses/interface/EventDisplayData.h"

using namespace std;
using namespace nTupleAnalysis;
namespace pt = boost::property_tree;


EventDisplayData::EventDisplayData(string name) : m_name(name) {
  
  for(string varName : m_varNames){
    m_OneEvent_info.insert(make_pair(varName,pt::ptree()));
    m_AllEvent_info.insert(make_pair(varName,pt::ptree()));
  }

  for(string jetName : m_jetNames){
    m_OneEvent_info.insert(make_pair(jetName,pt::ptree()));
    m_AllEvent_info.insert(make_pair(jetName,pt::ptree()));
  }


  for(string trkName : m_trkNames){
    m_OneEvent_info.insert(make_pair(trkName,pt::ptree()));
    m_AllEvent_info.insert(make_pair(trkName,pt::ptree()));
  }

}


void
EventDisplayData::AddJet (string jetName, const jetPtr& jetData, bool doTracks, bool debug ){

  if(debug){
    cout << "In Add Jet " << jetName << endl;
    cout << "\tAdding " << jetData->eta << " " << jetData->phi << " " << jetData->pt << endl; 
  }

  // Create an unnamed node containing the value                                                                                                                                                          
  pt::ptree var_node;
  pt::ptree jet_node;
  var_node.put("", jetData->eta);
  jet_node.push_back(std::make_pair("", var_node));
 
  var_node.put("", jetData->phi);
  jet_node.push_back(std::make_pair("", var_node));
 
  var_node.put("", jetData->pt);
  jet_node.push_back(std::make_pair("", var_node));

  m_OneEvent_info[jetName].push_back(std::make_pair("", jet_node));


  if(doTracks){
    for(const trackPtr& tData : jetData->tracks){
      AddTrk(jetName+"_Trks",tData, debug);
    }
  }
    
  
  return;
}


void
EventDisplayData::AddEventVar (string varName, float var, bool debug ){

  if(debug){
    cout << "In AddEventVar " << varName << endl;
    cout << "\tAdding " << var  << endl; 
  }

  // Create an unnamed node containing the value                                                                                                                                                          
  pt::ptree var_node;
  var_node.put("", var);

  m_OneEvent_info[varName].push_back(std::make_pair("", var_node));
  
  return;
}


void
EventDisplayData::AddTrk (string trkName, const trackPtr& trkData, bool debug){
  if(debug){
    cout << "In Add Trk " << trkName << endl;
    cout << "\tAdding " << trkData->eta << " " << trkData->phi << " " << trkData->pt << endl;
  }

  // Create an unnamed node containing the value                                                                                                                                                          
  pt::ptree var_node;
  pt::ptree trk_node;
  var_node.put("", trkData->eta);
  trk_node.push_back(std::make_pair("", var_node));
 
  var_node.put("", trkData->phi);
  trk_node.push_back(std::make_pair("", var_node));
 
  var_node.put("", trkData->pt);
  trk_node.push_back(std::make_pair("", var_node));

  m_OneEvent_info[trkName].push_back(std::make_pair("", trk_node));

  return;
}


void
EventDisplayData::NewEvent (){

  m_nDisplays += 1;

  for(string varName : m_varNames){
    m_AllEvent_info[varName].push_back(std::make_pair(std::to_string(m_nDisplays), m_OneEvent_info[varName]));    
    m_OneEvent_info[varName].clear();
  }


  for(string jetName : m_jetNames){
    m_AllEvent_info[jetName].push_back(std::make_pair(std::to_string(m_nDisplays), m_OneEvent_info[jetName]));    
    m_OneEvent_info[jetName].clear();
  }

  for(string trkName : m_trkNames){
    m_AllEvent_info[trkName].push_back(std::make_pair(std::to_string(m_nDisplays), m_OneEvent_info[trkName]));    
    m_OneEvent_info[trkName].clear();
  }


  return;
}

void
EventDisplayData::Write (std::string outfileName){

  for(string varName : m_varNames){  
    oroot.add_child(varName, m_AllEvent_info[varName]);
  }

  for(string jetName : m_jetNames){  
    oroot.add_child(jetName, m_AllEvent_info[jetName]);
  }

  for(string trkName : m_trkNames){  
    oroot.add_child(trkName, m_AllEvent_info[trkName]);
  }

  ofstream myfile;
  myfile.open (outfileName);
  
  pt::write_json(myfile, oroot);
  myfile.close();

  return;
}
