
#include "nTupleAnalysis/baseClasses/interface/jetHists.h"

using namespace nTupleAnalysis;

jetHists::jetHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir, title);

    cleanmask = dir.make<TH1F>("cleanmask", (name+"/cleanmask; "+title+" Clean Mask; Entries").c_str(), 2,-0.5,1.5);

    deepB     = dir.make<TH1F>("deepB",     (name+"/deepB; "    +title+" Deep B; Entries").c_str(), 100,0,1);
    CSVv2     = dir.make<TH1F>("CSVv2",     (name+"/CSVv2; "    +title+" CSV v2; Entries").c_str(), 100,0,1);
    deepFlavB = dir.make<TH1F>("deepFlavB", (name+"/deepFlavB; "+title+" Deep (Jet) Flavour B; Entries").c_str(), 100,0,1);
    nJets     = dir.make<TH1F>("nJets",     (name+"/nJets;    " +title+" Number of Jets; Entries").c_str(),  10,-0.5,9.5);
    nTrksExpected  = dir.make<TH1F>("nTrksExpected",     (name+"/nTrksExpected;    " +title+" Number of Expected Tracks; Entries").c_str(),  20,-0.5,19.5);

    tracks = new trackHists(name+"/tracks", fs, title);
    svs    = new secondaryVertexHists(name+"/svs", fs, title);
} 

void jetHists::Fill(const std::shared_ptr<jet> &jet, float weight){

  v->Fill(jet->p, weight);

  cleanmask->Fill(jet->cleanmask, weight);

  deepB    ->Fill(jet->deepB, weight);
  CSVv2    ->Fill(jet->CSVv2, weight);
  deepFlavB->Fill(jet->deepFlavB, weight);

  nTrksExpected->Fill(jet->nLastTrack-jet->nFirstTrack,weight);
    
  tracks->nTracks->Fill(jet->tracks.size(), weight);
  for(const trackPtr& track: jet->tracks) 
    tracks->Fill(track, weight);

  //svs->nTracks->Fill(jet->tracks.size(), weight);
  for(const svPtr& sv: jet->svs) 
    svs->Fill(sv, weight);

  
  return;
}

jetHists::~jetHists(){} 
