#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/btaggingData.h"
#include <math.h>
using namespace nTupleAnalysis;



//secondaryVertex object
secondaryVertex::secondaryVertex(){}
secondaryVertex::secondaryVertex(UInt_t i, btaggingData* data){


  x                    = data->sv_x                 [i];
  y                    = data->sv_y                 [i];
  z                    = data->sv_z                 [i];
  ex                   = data->sv_ex                [i];
  ey                   = data->sv_ey                [i];
  ez                   = data->sv_ez                [i];
  chi2                 = data->sv_chi2              [i];
  ndf                  = data->sv_ndf               [i];
  flight               = data->sv_flight            [i];
  flightErr            = data->sv_flightErr         [i];
  deltaR_jet           = data->sv_deltaR_jet        [i];
  deltaR_sum_jet       = data->sv_deltaR_sum_jet    [i];
  deltaR_sum_dir       = data->sv_deltaR_sum_dir    [i];
  vtx_pt               = data->sv_vtx_pt            [i];
  flight2D             = data->sv_flight2D          [i];
  flight2DErr          = data->sv_flight2DErr       [i];
  totCharge            = data->sv_totCharge         [i];
  vtxDistJetAxis       = data->sv_vtxDistJetAxis    [i];
  nTrk                 = data->sv_nTrk              [i];
  mass                 = data->sv_mass              [i];
  vtx_eta              = data->sv_vtx_eta           [i];
  vtx_phi              = data->sv_vtx_phi           [i];
  EnergyRatio          = data->sv_EnergyRatio       [i];
  dir_x                = data->sv_dir_x             [i];
  dir_y                = data->sv_dir_y             [i];
  dir_z                = data->sv_dir_z             [i];

  p = TLorentzVector();
  p.SetPtEtaPhiM(vtx_pt, vtx_eta, vtx_phi, mass);
  e = p.E();


}


secondaryVertex::~secondaryVertex(){}



//trkTag object
trkTagVar::trkTagVar(){}
trkTagVar::trkTagVar(UInt_t i, btaggingData* data){

  trackEta	        = data->trackEta	 [i];
  trackMomentum	        = data->trackMomentum	 [i];
  pt                    = trackMomentum/cosh(trackEta);
  trackPhi	        = data->trackPhi	 [i];
  m   = 0.140;
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, trackEta, trackPhi, m);
  e = p.E();

  trackPtRel	        = data->trackPtRel	 [i];
  trackPPar	        = data->trackPPar	 [i];
  trackEtaRel	        = data->trackEtaRel	 [i];
  trackDeltaR	        = data->trackDeltaR	 [i];
  trackPtRatio	        = data->trackPtRatio	 [i];
  trackPParRatio        = data->trackPParRatio   [i];	
  trackSip2dVal	        = data->trackSip2dVal	 [i];
  trackSip2dSig	        = data->trackSip2dSig	 [i];
  trackSip3dVal	        = data->trackSip3dVal	 [i];
  trackSip3dSig	        = data->trackSip3dSig	 [i];
  trackDecayLenVal      = data->trackDecayLenVal [i];
  trackDecayLenSig      = data->trackDecayLenSig [i];
  trackJetDistVal       = data->trackJetDistVal  [i];
  trackJetDistSig       = data->trackJetDistSig  [i];
  trackChi2	        = data->trackChi2	 [i];
  trackNTotalHits       = data->trackNTotalHits  [i];
  trackNPixelHits       = data->trackNPixelHits  [i];


}


trkTagVar::~trkTagVar(){}


//tagVar object
tagVar::tagVar(){}
tagVar::tagVar(UInt_t i, btaggingData* data){

  jetNTracks            = data-> jetNTracks               [i];
  jetNSecondaryVertices = data-> jetNSecondaryVertices    [i];

  chargedMultiplicity         = data-> chargedMultiplicity      [i];
  chargedHadronEnergyFraction = data-> chargedHadronEnergyFraction      [i];
  chargedHadronMultiplicity   = data-> chargedHadronMultiplicity      [i];
  chargedEmEnergyFraction     = data-> chargedEmEnergyFraction      [i];

  neutralMultiplicity   = data-> neutralMultiplicity      [i];
  neutralHadronEnergyFraction = data-> neutralHadronEnergyFraction      [i];
  neutralHadronMultiplicity = data-> neutralHadronMultiplicity      [i];
  neutralEmEnergyFraction = data->neutralEmEnergyFraction [i];

  photonEnergyFraction  = data-> photonEnergyFraction     [i];
  photonMultiplicity    = data-> photonMultiplicity       [i];

  muonEnergyFraction    = data-> muonEnergyFraction       [i];
  muonMultiplicity      = data-> muonMultiplicity         [i];

  electronEnergyFraction  = data-> electronEnergyFraction     [i];
  electronMultiplicity  = data-> electronMultiplicity     [i];

  numberOfDaughters     = data-> numberOfDaughters        [i];

}


tagVar::~tagVar(){}



btaggingData::btaggingData(){ 
}

//access tree
void btaggingData::initSecondaryVerticies(std::string name, TTree* tree){

  haveSVs = true;

  inputBranch(tree, (name+"nSV"                 ).c_str(),   nSV);
  inputBranch(tree, (name+"SV_x"                ).c_str(),   sv_x                 );
  inputBranch(tree, (name+"SV_y"                ).c_str(),   sv_y                 );
  inputBranch(tree, (name+"SV_z"                ).c_str(),   sv_z                 );
  inputBranch(tree, (name+"SV_ex"               ).c_str(),   sv_ex                );
  inputBranch(tree, (name+"SV_ey"               ).c_str(),   sv_ey                );
  inputBranch(tree, (name+"SV_ez"               ).c_str(),   sv_ez                );
  inputBranch(tree, (name+"SV_chi2"             ).c_str(),   sv_chi2              );
  inputBranch(tree, (name+"SV_ndf"              ).c_str(),   sv_ndf               );
  inputBranch(tree, (name+"SV_flight"           ).c_str(),   sv_flight            );
  inputBranch(tree, (name+"SV_flightErr"        ).c_str(),   sv_flightErr         );
  inputBranch(tree, (name+"SV_deltaR_jet"       ).c_str(),   sv_deltaR_jet        );
  inputBranch(tree, (name+"SV_deltaR_sum_jet"   ).c_str(),   sv_deltaR_sum_jet    );
  inputBranch(tree, (name+"SV_deltaR_sum_dir"   ).c_str(),   sv_deltaR_sum_dir    );
  inputBranch(tree, (name+"SV_vtx_pt"           ).c_str(),   sv_vtx_pt            );
  inputBranch(tree, (name+"SV_flight2D"         ).c_str(),   sv_flight2D          );
  inputBranch(tree, (name+"SV_flight2DErr"      ).c_str(),   sv_flight2DErr       );
  inputBranch(tree, (name+"SV_totCharge"        ).c_str(),   sv_totCharge         );
  inputBranch(tree, (name+"SV_vtxDistJetAxis"   ).c_str(),   sv_vtxDistJetAxis    );
  inputBranch(tree, (name+"SV_nTrk"             ).c_str(),   sv_nTrk              );
  inputBranch(tree, (name+"SV_mass"             ).c_str(),   sv_mass              );
  inputBranch(tree, (name+"SV_vtx_eta"          ).c_str(),   sv_vtx_eta           );
  inputBranch(tree, (name+"SV_vtx_phi"          ).c_str(),   sv_vtx_phi           );
  inputBranch(tree, (name+"SV_EnergyRatio"      ).c_str(),   sv_EnergyRatio       );
  inputBranch(tree, (name+"SV_dir_x"            ).c_str(),   sv_dir_x             );
  inputBranch(tree, (name+"SV_dir_y"            ).c_str(),   sv_dir_y             );
  inputBranch(tree, (name+"SV_dir_z"            ).c_str(),   sv_dir_z             );

}


//access tree
void btaggingData::initTrkTagVar(std::string name, TTree* tree){

  haveTrkTagVars = true;

  //nTrkTagVar : nTrkTagVar/I                                          *
  inputBranch(tree, (name+"TagVar_trackMomentum"        ).c_str(),      trackMomentum    );
  inputBranch(tree, (name+"TagVar_trackEta"             ).c_str(),      trackEta         );
  inputBranch(tree, (name+"TagVar_trackPhi"             ).c_str(),      trackPhi         );
  inputBranch(tree, (name+"TagVar_trackPtRel"           ).c_str(),      trackPtRel       );
  inputBranch(tree, (name+"TagVar_trackPPar"            ).c_str(),      trackPPar        );
  inputBranch(tree, (name+"TagVar_trackEtaRel"          ).c_str(),      trackEtaRel      );
  inputBranch(tree, (name+"TagVar_trackDeltaR"          ).c_str(),      trackDeltaR      );
  inputBranch(tree, (name+"TagVar_trackPtRatio"         ).c_str(),      trackPtRatio     );
  inputBranch(tree, (name+"TagVar_trackPParRatio"       ).c_str(),      trackPParRatio   ); 
  inputBranch(tree, (name+"TagVar_trackSip2dVal"        ).c_str(),      trackSip2dVal    ); 
  inputBranch(tree, (name+"TagVar_trackSip2dSig"        ).c_str(),      trackSip2dSig    ); 
  inputBranch(tree, (name+"TagVar_trackSip3dVal"        ).c_str(),      trackSip3dVal    ); 
  inputBranch(tree, (name+"TagVar_trackSip3dSig"        ).c_str(),      trackSip3dSig    ); 
  inputBranch(tree, (name+"TagVar_trackDecayLenVal"     ).c_str(),      trackDecayLenVal );
  inputBranch(tree, (name+"TagVar_trackDecayLenSig"     ).c_str(),      trackDecayLenSig );
  inputBranch(tree, (name+"TagVar_trackJetDistVal"      ).c_str(),      trackJetDistVal  );
  inputBranch(tree, (name+"TagVar_trackJetDistSig"      ).c_str(),      trackJetDistSig  );
  inputBranch(tree, (name+"TagVar_trackChi2"            ).c_str(),      trackChi2        );
  inputBranch(tree, (name+"TagVar_trackNTotalHits"      ).c_str(),      trackNTotalHits  );
  inputBranch(tree, (name+"TagVar_trackNPixelHits"      ).c_str(),      trackNPixelHits  );
    
  

}

//access tree
void btaggingData::initTagVar(std::string name, TTree* tree){

  haveTagVars = true;

  inputBranch(tree, (name+"TagVar_jetNTracks"            ).c_str(),    jetNTracks            );
  inputBranch(tree, (name+"TagVar_jetNSecondaryVertices" ).c_str(),    jetNSecondaryVertices );

  inputBranch(tree, (name+"TagVar_chargedMultiplicity"        ).c_str(), chargedMultiplicity            );
  inputBranch(tree, (name+"TagVar_chargedHadronEnergyFraction").c_str(), chargedHadronEnergyFraction    );
  inputBranch(tree, (name+"TagVar_chargedHadronMultiplicity"  ).c_str(), chargedHadronMultiplicity      );
  inputBranch(tree, (name+"TagVar_chargedEmEnergyFraction"    ).c_str(), chargedEmEnergyFraction        );
  inputBranch(tree, (name+"TagVar_neutralMultiplicity"        ).c_str(), neutralMultiplicity            );
  inputBranch(tree, (name+"TagVar_neutralHadronEnergyFraction").c_str(), neutralHadronEnergyFraction    );
  inputBranch(tree, (name+"TagVar_neutralHadronMultiplicity"  ).c_str(), neutralHadronMultiplicity      );
  inputBranch(tree, (name+"TagVar_neutralEmEnergyFraction"    ).c_str(), neutralEmEnergyFraction        );
  inputBranch(tree, (name+"TagVar_photonEnergyFraction"       ).c_str(), photonEnergyFraction           );
  inputBranch(tree, (name+"TagVar_photonMultiplicity"         ).c_str(), photonMultiplicity             );
  inputBranch(tree, (name+"TagVar_muonEnergyFraction"         ).c_str(), muonEnergyFraction             );
  inputBranch(tree, (name+"TagVar_muonMultiplicity"           ).c_str(), muonMultiplicity               );
  inputBranch(tree, (name+"TagVar_electronEnergyFraction"     ).c_str(), electronEnergyFraction         );
  inputBranch(tree, (name+"TagVar_electronMultiplicity"       ).c_str(), electronMultiplicity           );
  inputBranch(tree, (name+"TagVar_numberOfDaughters"          ).c_str(), numberOfDaughters              );
}

std::vector< std::shared_ptr<secondaryVertex> > btaggingData::getSecondaryVertices(int nFirstSV, int nLastSV, bool debug){
  if(debug) std::cout << "btaggingData::getSecondaryVertices " << nFirstSV << " to " << nLastSV << std::endl;  
  std::vector< std::shared_ptr<secondaryVertex> > outputSVs;
  for(int i = nFirstSV; i < nLastSV; ++i){
    if(i > int(MAXSVS-1)) {
      std::cout  << "btaggingData::Warning too many SVs! " << nLastSV  << " SVs. Skipping. "<< std::endl;
      break;
    }

    if(debug) std::cout << "btaggingData::getSecondaryVertices " << i <<  "vs nSVs " << nSV <<  std::endl; 
    outputSVs.push_back(std::make_shared<secondaryVertex>(secondaryVertex(i, this)));
  }
  if(debug) std::cout << "leave btaggingData::getSecondaryVertices " << std::endl;
  return outputSVs;
}


std::vector<trkTagVarPtr> btaggingData::getTrkTagVars(int nFirstTrkTagVar, int nLastTrkTagVar){
  
  std::vector<trkTagVarPtr> outputTrkTagVars;
  for(int i = nFirstTrkTagVar; i < nLastTrkTagVar; ++i){
    if(i > int(MAXNTRK-1)) {
      std::cout  << "btaggingData::Warning too many trkTagVars! " << nLastTrkTagVar  << " trkTagVars. Skipping. "<< std::endl;
      break;
    }
    
    if(this->trackDeltaR[i] < 0.3 && fabs(this->trackJetDistVal[i]) < 0.07 && this->trackDecayLenVal[i] < 5 ){
      outputTrkTagVars.push_back(std::make_shared<trkTagVar>(trkTagVar(i, this)));
    }
  }
  return outputTrkTagVars;
}



tagVarPtr btaggingData::getTagVars(int jetIdx){
  if(jetIdx > int(MAXNJETS-1)) {
    std::cout  << "btaggingData::Warning too many tagVar! " << jetIdx  << std::endl;
  }

  return std::make_shared<tagVar>(tagVar(jetIdx, this));
}



btaggingData::~btaggingData(){}

