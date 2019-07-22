
#include "nTupleAnalysis/baseClasses/interface/jetHists.h"

using namespace nTupleAnalysis;

jetHists::jetHists(std::string name, fwlite::TFileService& fs, std::string title, std::string jetDetailLevel) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir, title);

    cleanmask = dir.make<TH1F>("cleanmask", (name+"/cleanmask; "+title+" Clean Mask; Entries").c_str(), 2,-0.5,1.5);

    deepB     = dir.make<TH1F>("deepB",     (name+"/deepB; "    +title+" Deep B; Entries").c_str(), 100,0,1);
    CSVv2     = dir.make<TH1F>("CSVv2",     (name+"/CSVv2; "    +title+" CSV v2; Entries").c_str(), 100,0,1);
    deepFlavB = dir.make<TH1F>("deepFlavB", (name+"/deepFlavB; "+title+" Deep (Jet) Flavour B; Entries").c_str(), 100,0,1);
    nJets     = dir.make<TH1F>("nJets",     (name+"/nJets;    " +title+" Number of Jets; Entries").c_str(),  10,-0.5,9.5);

    CSVv2_l     = dir.make<TH1F>("CSVv2_l",     (name+"/CSVv2_l; "   +title+" CSV v2; Entries").c_str(), 120,-0.2,1.2);
    deepCSV_l   = dir.make<TH1F>("DeepCSV_l",   (name+"/DeepCSV_l; "   +title+" DeepCSV; Entries").c_str(), 120,-0.2,1.2);
    deepCSVb_l  = dir.make<TH1F>("DeepCSVb_l",   (name+"/DeepCSVb_l; "   +title+" DeepCSVb; Entries").c_str(), 120,-0.2,1.2);
    deepCSVbb_l = dir.make<TH1F>("DeepCSVbb_l",   (name+"/DeepCSVbb_l; "   +title+" DeepCSVbb; Entries").c_str(), 120,-0.2,1.2);
    SoftMu      = dir.make<TH1F>("SoftMu",      (name+"/SoftMu; "    +title+" SoftMu; Entries").c_str(), 120,-0.2,1.2);
    nSoftMu     = dir.make<TH1F>("nSoftEl",     (name+"/nSoftEl;    " +title+" Number of Soft El.; Entries").c_str(),  11,-0.5,10.5);
    SoftEl      = dir.make<TH1F>("SoftEl",      (name+"/SoftEl; "    +title+" SoftEl; Entries").c_str(), 120,-0.2,1.2);
    nSoftMu     = dir.make<TH1F>("nSoftMu",     (name+"/nSoftMu;    " +title+" Number of Soft Mu; Entries").c_str(),  11,-0.5,10.5);

    if(jetDetailLevel.find("matched") != std::string::npos){
      matched_dPt      = dir.make<TH1F>("matched_dPt",     (name+"/matched_dPt     ;P_{T}-P_{T}^{matched} [GeV];Entries").c_str()  ,100,-50, 50);
      matched_dEta     = dir.make<TH1F>("matched_dEta",    (name+"/matched_dEta    ;#eta-#eta^{matched};Entries"        ).c_str()  ,100,-0.5,0.5);
      matched_dPhi     = dir.make<TH1F>("matched_dPhi",    (name+"/matched_dPhi    ;#phi-#phi^{matched};Entries"        ).c_str()  ,100,-0.5,0.5);
      matched_dR       = dir.make<TH1F>("matched_dR",      (name+"/matched_dR      ;#DeltaR(Online,Offline);;Entries"   ).c_str()  ,100, 0,0.45);
      matched_dcsv     = dir.make<TH1F>("matched_dcsv",    (name+"/matched_dcsv;CSV-CSV^{matched};Entries"              ).c_str()  ,100,-1,1);
      matched_dDeepcsv = dir.make<TH1F>("matched_dDeepcsv",(name+"/matched_dDeepcsv;DeepCSV-DeepCSV^{matched};Entries"  ).c_str()  ,100,-1,1);
    }

    if(jetDetailLevel.find("Tracks") != std::string::npos){
      nTrksExpected  = dir.make<TH1F>("nTrksExpected",     (name+"/nTrksExpected;    " +title+" Number of Expected Tracks; Entries").c_str(),  20,-0.5,19.5);
      ntracks     = dir.make<TH1F>("nTracks",     (name+"/nTracks;    " +title+" Number of Tracks; Entries").c_str(),  20,-0.5,19.5);
      nseltracks  = dir.make<TH1F>("nSelTracks",  (name+"/nSelTracks;    " +title+" Number of Selected Tracks; Entries").c_str(),  20,-0.5,19.5);

      tracks      = new trackHists(name+"/tracks",      fs, title);
      tracks_noV0 = new trackHists(name+"/tracks_noV0", fs, title);
    }
    if(jetDetailLevel.find("btagInputs") != std::string::npos){
      flavour          = dir.make<TH1F>("flavour",     (name+"/flavour;    " +title+" Flavour; Entries").c_str(),  31,-5.5,25.5);
      flavourCleaned     = dir.make<TH1F>("flavourCleaned",     (name+"/flavourCleaned;    " +title+" Flavour (cleaned); Entries").c_str(),  31,-5.5,25.5);
      partonFlavour     = dir.make<TH1F>("partonFlavour",     (name+"/partonFlavour;    " +title+" Parton Flavour; Entries").c_str(),  31,-5.5,25.5);
      hadronFlavour     = dir.make<TH1F>("hadronFlavour",     (name+"/hadronFlavour;    " +title+" Hadron Flavour; Entries").c_str(),  31,-5.5,25.5);
      nbHadrons     = dir.make<TH1F>("nbHadrons",     (name+"/nbHadrons;    " +title+" Number of B Hadrons; Entries").c_str(),  5,-0.5,4.5);
      ncHadrons     = dir.make<TH1F>("ncHadrons",     (name+"/ncHadrons;    " +title+" Number of C Hadrons; Entries").c_str(),  5,-0.5,4.5);

      SF      = dir.make<TH1F>("SF",     (name+"/SF;SF;Entries").c_str(),50,-0.1,2);

      btags      = new btaggingHists(name+"/btags",      fs, title);
      btags_noV0 = new btaggingHists(name+"/btags_noV0", fs, title);
    }
} 

void jetHists::Fill(const std::shared_ptr<jet> &jet, float weight){

  v->Fill(jet->p, weight);

  cleanmask->Fill(jet->cleanmask, weight);

  deepB    ->Fill(jet->deepB, weight);
  CSVv2    ->Fill(jet->CSVv2, weight);
  CSVv2_l  ->Fill(jet->CSVv2, weight);
  deepFlavB->Fill(jet->deepFlavB, weight);

  deepCSV_l  ->Fill(jet->DeepCSV    ,weight);
  deepCSVb_l  ->Fill(jet->DeepCSVb    ,weight);
  deepCSVbb_l  ->Fill(jet->DeepCSVbb    ,weight);

  SoftMu     ->Fill(jet->SoftMu     ,weight);
  nSoftMu    ->Fill(jet->nSM        ,weight);
  
  SoftEl     ->Fill(jet->SoftEl     ,weight);
  nSoftMu    ->Fill(jet->nSE        ,weight);

  //
  // track hists
  //
  if(tracks){
    ntracks    ->Fill(jet->ntracks    ,weight);
    nseltracks ->Fill(jet->nseltracks ,weight);
    nTrksExpected->Fill(jet->nLastTrack-jet->nFirstTrack,weight);
    tracks->nTracks->Fill(jet->tracks.size(), weight);
    for(const trackPtr& track: jet->tracks) 
      tracks->Fill(track, weight);

    //
    // No V0s
    //
    unsigned int nTrks_noV0 = 0;
    for(const trackPtr& track: jet->tracks) {
      if(!track->isfromV0){
	++nTrks_noV0;
	tracks_noV0->Fill(track, weight);
      }
    }
    tracks_noV0->nTracks->Fill(nTrks_noV0, weight);  
  }

  //
  // btagging
  //
  if(btags){
    flavour    ->Fill(jet->flavour,   weight);
    flavourCleaned    ->Fill(jet->flavourCleaned,   weight);
    partonFlavour    ->Fill(jet->partonFlavour,   weight);
    hadronFlavour    ->Fill(jet->hadronFlavour,   weight);
    nbHadrons        ->Fill(jet->nbHadrons,   weight);
    ncHadrons        ->Fill(jet->ncHadrons,   weight);

    SF               ->Fill(jet->SF      , weight);

    btags->sv_nSVs->Fill(jet->svs.size(), weight);
    for(const svPtr& sv: jet->svs) 
      btags->FillSVHists(sv, jet, weight);

    btags->trkTag_nTracks->Fill(jet->trkTagVars.size(), weight);
    for(const trkTagVarPtr& trkTag: jet->trkTagVars) 
      btags->FillTrkTagVarHists(trkTag, weight);
  
    if(jet->tagVars)
      btags->FillTagVarHists(jet->tagVars, weight);

    //
    // No V0s
    //
    unsigned int nTrkTags_noV0 = 0;
    for(const trkTagVarPtr& trkTag: jet->trkTagVars) {
      if(!trkTag->matchIsFromV0){
	btags_noV0->FillTrkTagVarHists(trkTag, weight);
	++nTrkTags_noV0;
      }
    }
    btags_noV0->trkTag_nTracks->Fill(nTrkTags_noV0, weight);
  }
  
  if(matched_dPt){
    std::shared_ptr<nTupleAnalysis::jet> matchedJet = jet->matchedJet.lock();
    if(matchedJet){
      matched_dPt      ->Fill(jet->pt  - matchedJet->pt ,weight);
      matched_dEta     ->Fill(jet->eta - matchedJet->eta,weight);
      matched_dPhi     ->Fill(jet->p.DeltaPhi(matchedJet->p),weight);
      matched_dR       ->Fill(jet->p.DeltaR(matchedJet->p),weight);
      matched_dcsv     ->Fill(jet->CSVv2 - matchedJet->CSVv2,weight);
      matched_dDeepcsv ->Fill(jet->DeepCSV - matchedJet->DeepCSV,weight);
    }
  }

  return;
}

jetHists::~jetHists(){} 
