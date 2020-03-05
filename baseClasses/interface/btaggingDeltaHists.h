// -*- C++ -*-
#if !defined(btaggingDeltaHists_H)
#define btaggingDeltaHists_H

#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include "PhysicsTools/FWLite/interface/TFileService.h"
#include "nTupleAnalysis/baseClasses/interface/btaggingData.h"
#include "nTupleAnalysis/baseClasses/interface/jetData.h"

namespace nTupleAnalysis {

  class btaggingDeltaHists {
  public:
    
    //SV Hists
    TH1F*   sv_d_NTracks                    ;
    TH1F*   sv_d_Mass                       ;
    TH1F*   sv_d_JetDeltaR                  ;
    TH1F*   sv_d_FitProb                    ;
    TH1F*   sv_d_EnergyRatio                ;
    TH1F*   sv_d_R          ;
    TH1F*   sv_d_Z          ;
    TH1F*   sv_d_Chi2       ;
    TH1F*   sv_d_Chi2_l       ;
    TH1F*   sv_d_NDF        ;
    TH1F*   sv_d_Flight     ;
    TH1F*   sv_d_FlightSig  ;
    TH1F*   sv_d_Flight2D   ;
    TH1F*   sv_d_FlightSig2D;
    TH1F*   sv_d_Pt         ;
    TH1F*   sv_d_Eta        ;
    TH1F*   sv_d_Phi        ;
    TH1F*   sv_d_DistJetAxis;
    TH1F*   sv_d_nSVs;
    TH1F*   sv_d_boostOverSqrtJetPt;
    TH1F*   sv_d_massVertexEnergyFraction;
    TH1F*   sv_d_totCharge;

    //TrkTagVar Hists
    TH1F* trkTag_d_ip3d_l ;
    TH1F* trkTag_d_ip3d   ;
    TH1F* trkTag_d_ip3d_sig_l;
    TH1F* trkTag_d_ip3d_sig  ;
    TH1F* trkTag_d_ip3d_err_l;
    TH1F* trkTag_d_ip3d_err  ;

    TH1F* trkTag_d_ip2d_l ;
    TH1F* trkTag_d_ip2d   ;
    TH1F* trkTag_d_ip2d_sig_l;
    TH1F* trkTag_d_ip2d_sig;
    TH1F* trkTag_d_ip2d_err_l;
    TH1F* trkTag_d_ip2d_err;
    
    TH1F* trkTag_d_trackDecayLenVal_l ;
    TH1F* trkTag_d_trackDecayLenVal;
    TH1F* trkTag_d_trackJetDistVal ;    
    TH1F* trkTag_d_trackJetDistSig ;    
    TH1F* trkTag_d_trackPt_logx           ;
    TH1F* trkTag_d_trackMomentum   ;
    TH1F* trkTag_d_trackPt   ;
    TH1F* trkTag_d_trackEta           ;       
    TH1F* trkTag_d_trackPhi           ;       
    TH1F* trkTag_d_trackPtRel      ; 
    TH1F* trkTag_d_trackDeltaR        ;       
    TH1F* trkTag_d_trackDeltaR_l        ;       
    TH1F* trkTag_d_trackPtRatio       ;       
    TH1F* trkTag_d_trackPPar          ;       
    TH1F* trkTag_d_trackEtaRel        ;       
    TH1F* trkTag_d_trackPParRatio     ;       
    TH1F* trkTag_d_trackChi2          ;       
    TH1F* trkTag_d_trackNTotalHits    ;       
    TH1F* trkTag_d_trackNPixelHits    ;       
    //TH1F* trkTag_d_nTracks;
    TH1F* trkTag_d_isFromV0  ;

    TH1F*   tag_d_jetNTracks                      ;
    TH1F*   tag_d_jetNSecondaryVertices              ;
    TH1F*   tag_d_chargedMultiplicity             ;
    TH1F*   tag_d_chargedHadronEnergyFraction     ;
    TH1F*   tag_d_chargedHadronMultiplicity       ;
    TH1F*   tag_d_chargedEmEnergyFraction         ;
    TH1F*   tag_d_neutralMultiplicity             ;
    TH1F*   tag_d_neutralHadronEnergyFraction     ;
    TH1F*   tag_d_neutralHadronMultiplicity       ;
    TH1F*   tag_d_neutralEmEnergyFraction         ;
    TH1F*   tag_d_photonMultiplicity              ;
    TH1F*   tag_d_photonEnergyFraction            ;
    TH1F*   tag_d_muonMultiplicity                ;
    TH1F*   tag_d_muonEnergyFraction              ;
    TH1F*   tag_d_elecMultiplicity                ;
    TH1F*   tag_d_elecEnergyFraction              ;
    TH1F*   tag_d_totalMultiplicity               ;

    btaggingDeltaHists(std::string,       TFileDirectory&, std::string title = "");
    btaggingDeltaHists(std::string, fwlite::TFileService&, std::string title = "");

    void makeHists(std::string, TFileDirectory&, std::string title);
    void FillSVHists(const svPtr& sv1, const jetPtr& jet1, 
		     const svPtr& sv2, const jetPtr& jet2, 
		     float weight);

    void FillTrkTagVarHists(const trkTagVarPtr& trkTag1, 
			    const trkTagVarPtr& trkTag2, 
			    float weight);

    void FillTagVarHists(const tagVarPtr& tag1, 
			 const tagVarPtr& tag2, 
			 float weight );

    ~btaggingDeltaHists(); 

  };

}
#endif // btaggingDeltaHists_H
