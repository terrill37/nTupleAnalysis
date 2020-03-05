#include "nTupleAnalysis/baseClasses/interface/btaggingDeltaHists.h"

using namespace nTupleAnalysis;
using std::cout; using std::endl; 

btaggingDeltaHists::btaggingDeltaHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}

btaggingDeltaHists::btaggingDeltaHists(std::string name, TFileDirectory& dir, std::string title) {
  TFileDirectory matchedDir = dir.mkdir(name);
  this->makeHists(name, matchedDir, title);
}


void btaggingDeltaHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {

  sv_d_NTracks                    = dir.make<TH1F>("sv_d_NTracks"                ,"vertexNTracks;#Delta nVertex Tracks;Entries"                 ,11, -5.5, 5.5);
  sv_d_Mass                       = dir.make<TH1F>("sv_d_Mass"                   ,"vertexMass;#Delta Vertex Mass [GeV]"                    ,100, -1, 1);
  sv_d_JetDeltaR                  = dir.make<TH1F>("sv_d_JetDeltaR"              ,"vertexJetDeltaR;#Delta Vertex-Jet #Delta R"               ,100, -0.04, 0.04);
  //FitProb                    = dir.make<TH1F>("sv_d_FitProb"                ,"vertexFitProb;Vertex Fit Prob"                 ,100, -50, 50);
  sv_d_EnergyRatio                = dir.make<TH1F>("sv_d_EnergyRatio"            ,"vertexEnergyRatio;#Delta Vertex Energy Fraction "             ,100, -0.3, 0.3);
  sv_d_R              = dir.make<TH1F>("sv_d_R          "            ,"R          ;#Delta Vertex R           "             ,100, -0.02, 0.02);
  sv_d_Z              = dir.make<TH1F>("sv_d_Z          "            ,"Z          ;#Delta Vertex Z           "             ,100, -0.02, 0.02);
  sv_d_Chi2           = dir.make<TH1F>("sv_d_Chi2       "            ,"Chi2       ;#Delta Vertex Chi2        "             ,100, -0.1, 0.1);
  sv_d_Chi2_l         = dir.make<TH1F>("sv_d_Chi2_l     "            ,"Chi2       ;#Delta Vertex Chi2        "           ,100, -5, 5);
  sv_d_NDF            = dir.make<TH1F>("sv_d_NDF        "            ,"NDF        ;#Delta Vertex NDF         "             ,19, -9.5, 9.5);
  sv_d_Flight         = dir.make<TH1F>("sv_d_Flight     "            ,"Flight     ;#Delta Vertex Flight      "             ,100, -0.02, 0.02);
  sv_d_FlightSig      = dir.make<TH1F>("sv_d_FlightSig  "            ,"FlightSig  ;#Delta Vertex FlightSig   "             ,100, -5, 5);
  sv_d_Flight2D       = dir.make<TH1F>("sv_d_Flight2D   "            ,"Flight2D   ;#Delta Vertex Flight2D    "             ,100, -0.02, 0.02);
  sv_d_FlightSig2D    = dir.make<TH1F>("sv_d_FlightSig2D"            ,"FlightSig2D;#Delta Vertex FlightSig2D "             ,100, -5, 5);
  sv_d_Pt             = dir.make<TH1F>("sv_d_Pt         "            ,"Pt         ;#Delta Vertex Pt          "             ,100, -20, 20);
  sv_d_Eta            = dir.make<TH1F>("sv_d_Eta        "            ,"Eta        ;#Delta Vertex Eta         "             ,100, -0.1, 0.1);
  sv_d_Phi            = dir.make<TH1F>("sv_d_Phi        "            ,"Phi        ;#Delta Vertex Phi         "             ,100, -0.1, 0.1);
  sv_d_DistJetAxis    = dir.make<TH1F>("sv_d_DistJetAxis"            ,"DistJetAxis;#Delta Vertex DistJetAxis "             ,100, -5e-5, 5e-5);
  sv_d_nSVs           = dir.make<TH1F>("sv_d_nSVs",     ("nSVs;  #Delta " +title+" Number of Sec. Verticies; Entries").c_str(),  10,-0.5,9.5);
  sv_d_boostOverSqrtJetPt         = dir.make<TH1F>("sv_d_BoostOverSqrtJetPt"     ,"vertexBoostOverSqrtJetPt;#Delta Vertex Boost/#sqrt{jet P_{T}}"      ,100, -0.05, 0.05);
  sv_d_massVertexEnergyFraction   = dir.make<TH1F>("sv_d_massVertexEnergyFraction"     ,"massVertexEnergyFraction;#Delta massVertexEnergyFraction"      ,100, -0.2,0.2);
  sv_d_totCharge   = dir.make<TH1F>("sv_d_totCharge"     ,"totCharge;totCharge"      ,11, -5.5,5.5);


  trkTag_d_ip3d_l = dir.make<TH1F>("d_ip3d_l","ip3d;#Delta IP3D [cm]",100,-0.05,0.05);
  trkTag_d_ip3d   = dir.make<TH1F>("d_ip3d",  "ip3d;#Delta IP3D [cm]",100,-0.02,0.02);

  trkTag_d_ip3d_sig_l = dir.make<TH1F>("d_ip3d_sig_l","ip3d sig;#Delta IP3D significance",100,-10,10);
  trkTag_d_ip3d_sig   = dir.make<TH1F>("d_ip3d_sig",  "ip3d sig;#Delta IP3D significance",100,-1,1);
  trkTag_d_ip3d_err_l = dir.make<TH1F>("d_ip3d_err_l","ip3d err;#Delta IP3D uncertianty [cm]",100,-0.01,0.01);
  trkTag_d_ip3d_err   = dir.make<TH1F>("d_ip3d_err",  "ip3d err;#Delta IP3D uncertianty [cm]",100,-0.001,0.001);
  
  trkTag_d_ip2d_l = dir.make<TH1F>("d_ip2d_l","ip2d;IP2D [cm]",100,-0.05,0.05);
  trkTag_d_ip2d   = dir.make<TH1F>("d_ip2d",  "ip2d;IP2D [cm]",100,-0.02,0.02);
  trkTag_d_ip2d_sig_l = dir.make<TH1F>("d_ip2d_sig_l","ip2d sig;#Delta IP2D significance",100,-10,10);
  trkTag_d_ip2d_sig   = dir.make<TH1F>("d_ip2d_sig",  "ip2d sig;#Delta IP2D significance",100,-1,1);
  trkTag_d_ip2d_err_l = dir.make<TH1F>("d_ip2d_err_l","ip2d err;#Delta IP2D uncertianty [cm]",100,-0.01,0.01);
  trkTag_d_ip2d_err   = dir.make<TH1F>("d_ip2d_err",  "ip2d err;#Delta IP2D uncertianty [cm]",100,-0.001,0.001);
    
  trkTag_d_trackDecayLenVal_l         = dir.make<TH1F>("d_trackDecayLenVal_l"  ,    "trackDecayLenVal;#Delta trackDecayLenVal [cm];Entries", 100, -0.5,  0.5);
  trkTag_d_trackDecayLenVal           = dir.make<TH1F>("d_trackDecayLenVal"    ,    "trackDecayLenVal;#Delta trackDecayLenVal [cm];Entries", 100, -0.1,  0.1);
  trkTag_d_trackJetDistVal            = dir.make<TH1F>("d_trackJetDistVal"     ,    "trackJetDistVal;#Delta trackJetDistVal [cm];Entries",  100, -0.01,  0.01);      
  trkTag_d_trackPtRel                 = dir.make<TH1F>("d_trackPtRel"          ,    "trackPtRel;#Delta track p_{T} Rel [GeV];Entries", 100, -1, 1);          
  trkTag_d_trackPt                    = dir.make<TH1F>("d_trackPt"             ,    "trackPt;#Delta track pt [GeV];Entries", 100, -5, 5);       
  trkTag_d_trackMomentum              = dir.make<TH1F>("d_trackMomentum"       ,    "trackMomentum;#Delta track momentum [GeV];Entries", 100, -5, 5);       

  trkTag_d_trackEta                   = dir.make<TH1F>("d_trackEta"            ,    "trackEta;#Delta track #eta;Entries", 100, -0.05, 0.05);            
  trkTag_d_trackPhi                   = dir.make<TH1F>("d_trackPhi"            ,    "trackPhi;#Delta track #phi;Entries", 100, -0.05, 0.05);            
  trkTag_d_trackPPar                  = dir.make<TH1F>("d_trackPPar"           ,    "trackPPar;#Delta track PPar [GeV];Entries",100, -5, 5);           
  trkTag_d_trackDeltaR                = dir.make<TH1F>("d_trackDeltaR"         ,    "trackDeltaR;#Delta track #DeltaR;Entries", 100, -0.05, 0.05);         
  trkTag_d_trackDeltaR_l              = dir.make<TH1F>("d_trackDeltaR_l"       ,    "trackDeltaR;#Delta track #DeltaR;Entries", 100, -0.05, 0.05);         
  trkTag_d_trackEtaRel                = dir.make<TH1F>("d_trackEtaRel"         ,    "trackEtaRel;#Delta track Eta Rel;Entries", 100, -1, 1);         
  trkTag_d_trackPtRatio               = dir.make<TH1F>("d_trackPtRatio"        ,    "trackPtRatio;#Delta track p_{T} Ratio;Entries", 100, -0.02, 0.02); 
  trkTag_d_trackPParRatio             = dir.make<TH1F>("d_trackPParRatio"      ,    "trackPParRatio;#Delta track P Par Ratio;Entries", 100, -0.02, 0.02);  

  trkTag_d_trackChi2                  = dir.make<TH1F>("d_trackChi2"            ,    "trackChi2;#Delta track Chi2;Entries", 100, -1, 1);            
  trkTag_d_trackNTotalHits            = dir.make<TH1F>("d_trackNTotalHits"      ,    "trackNTotalHits;#Delta trackNTotalHits;Entries", 10, -4.5, 4.5);
  trkTag_d_trackNPixelHits            = dir.make<TH1F>("d_trackNPixelHits"      ,    "trackNPixelHits;#Delta trackNPixelHits;Entries", 10, -4.5, 4.5);  
  //trkTag_d_nTracks                    = dir.make<TH1F>("d_nTracks",     ("nTrkTags;    " +title+" Number of Tracks; Entries").c_str(),  20,-0.5,19.5);
  trkTag_d_isFromV0                    = dir.make<TH1F>("d_trackIsFromV0"  ,  "IsFromV0;#Delta Is from V0;Entries", 3, -1.5,  1.5);  



  tag_d_jetNTracks                       = dir.make<TH1F>("d_jetNTracks"                   ,"jetNTracks;#Delta Number Tracks"                    ,19, -9.5, 9.5);
  tag_d_jetNSecondaryVertices               = dir.make<TH1F>("d_jetNSecondaryVertices"           ,"jetNSelectedTracks;#Delta Number Secondary Verticies"            ,11, -4.5, 4.5);

  tag_d_chargedMultiplicity               = dir.make<TH1F>("d_chargedMultiplicity"           ,"chargedMultiplicity;#Delta charged multiplicity"            ,41, -20.5, 20.5);
  tag_d_chargedHadronEnergyFraction       = dir.make<TH1F>("d_chargedHadronEnergyFraction"         ,"chargedHadronEnergyFraction;#Delta charged Hadron energy fraction"          ,100, -1,1.);
  tag_d_chargedHadronMultiplicity         = dir.make<TH1F>("d_chargedHadronMultiplicity"           ,"chargedHadronMultiplicity;#Delta charged hadron multiplicity"            ,41, -20.5, 20.5);
  tag_d_chargedEmEnergyFraction           = dir.make<TH1F>("d_chargedEmEnergyFraction"         ,"chargedEmEnergyFraction;#Delta charged Em energy fraction"          ,100, -1,1.);

  tag_d_neutralMultiplicity               = dir.make<TH1F>("d_neutralMultiplicity"           ,"neutralMultiplicity;#Delta neutral multiplicity"            ,41, -20.5, 20.5);
  tag_d_neutralHadronEnergyFraction       = dir.make<TH1F>("d_neutralHadronEnergyFraction"         ,"neutralHadronEnergyFraction;#Delta neutral Hadron energy fraction"          ,100, -1,1.);
  tag_d_neutralHadronMultiplicity         = dir.make<TH1F>("d_neutralHadronMultiplicity"           ,"neutralHadronMultiplicity;#Delta neutral hadron multiplicity"           ,41, -20.5, 20.5);
  tag_d_neutralEmEnergyFraction           = dir.make<TH1F>("d_neutralEmEnergyFraction"         ,"neutralEmEnergyFraction;#Delta neutral Em energy fraction"          ,100, -1,1);

  tag_d_photonMultiplicity               = dir.make<TH1F>("d_photonMultiplicity"           ,"photonMultiplicity;#Delta photon multiplicity"             ,41, -20.5, 20.5);
  tag_d_photonEnergyFraction             = dir.make<TH1F>("d_photonEnergyFraction"         ,"photonEnergyFraction;#Delta photon energy fraction"          ,100, -1,1.);

  tag_d_muonMultiplicity                 = dir.make<TH1F>("d_muonMultiplicity"             ,"muonMultiplicity;#Delta muonMultiplicity"              ,11, -4.5, 4.5);
  tag_d_muonEnergyFraction               = dir.make<TH1F>("d_muonEnergyFraction"           ,"muonEnergyFraction;#Delta muonEnergyFraction"            ,100, -1,1.);

  tag_d_elecMultiplicity                 = dir.make<TH1F>("d_elecMultiplicity"             ,"elecMultiplicity;#Delta elecMultiplicity"              ,11, -4.5, 4.5);
  tag_d_elecEnergyFraction               = dir.make<TH1F>("d_elecEnergyFraction"           ,"elecEnergyFraction;#Delta elecEnergyFraction"            ,100, -1,1.);

  tag_d_totalMultiplicity                = dir.make<TH1F>("d_totalMultiplicity"            ,"totalMultiplicity;#Delta total multiplicity"             ,41, -20.5, 20.5);


} 

void btaggingDeltaHists::FillSVHists(const svPtr &sv1, const jetPtr& jet1, 
				     const svPtr &sv2, const jetPtr& jet2, 
				     float weight){

  
  sv_d_NTracks                ->Fill(sv1->nTrk        - sv2->nTrk,        weight);
  sv_d_Mass                   ->Fill(sv1->mass        - sv2->mass,        weight);
  sv_d_JetDeltaR              ->Fill(sv1->deltaR_jet  - sv2->deltaR_jet,  weight);
  sv_d_EnergyRatio            ->Fill(sv1->EnergyRatio - sv2->EnergyRatio, weight);
  sv_d_totCharge              ->Fill(sv1->totCharge   - sv2->totCharge,   weight);

  float svR_1 = sqrt(sv1->x*sv1->x + sv1->y*sv1->y);
  float svR_2 = sqrt(sv2->x*sv2->x + sv2->y*sv2->y);
  sv_d_R                ->Fill(svR_1 - svR_2, weight);
  sv_d_Z                ->Fill(sv1->z    - sv2->z   , weight);
  sv_d_Chi2             ->Fill(sv1->chi2 - sv2->chi2, weight);
  sv_d_Chi2_l             ->Fill(sv1->chi2 - sv2->chi2, weight);
  sv_d_NDF              ->Fill(sv1->ndf  - sv2->ndf , weight);
  
  sv_d_Flight           ->Fill(sv1->flight - sv2->flight, weight);
  float flightSig_1 = sv1->flightErr ? sv1->flight/sv1->flightErr : -1;
  float flightSig_2 = sv2->flightErr ? sv2->flight/sv2->flightErr : -1;
  sv_d_FlightSig        ->Fill(flightSig_1 - flightSig_2, weight);
  
  sv_d_Flight2D           ->Fill(sv1->flight2D - sv2->flight2D, weight);
  float flightSig2D_1 = sv1->flight2DErr ? sv1->flight2D/sv1->flight2DErr : -1;
  float flightSig2D_2 = sv2->flight2DErr ? sv2->flight2D/sv2->flight2DErr : -1;
  sv_d_FlightSig2D        ->Fill(flightSig2D_1 - flightSig2D_2, weight);
  
  sv_d_Pt                ->Fill(sv1->vtx_pt         - sv2->vtx_pt        , weight);
  sv_d_Eta               ->Fill(sv1->vtx_eta        - sv2->vtx_eta       , weight);
  sv_d_Phi               ->Fill(sv1->vtx_phi        - sv2->vtx_phi       , weight);
  sv_d_DistJetAxis       ->Fill(sv1->vtxDistJetAxis - sv2->vtxDistJetAxis, weight);

  sv_d_boostOverSqrtJetPt ->Fill(sv1->p.BoostVector().Mag()/ sqrt(jet1->p.Pt()) - sv2->p.BoostVector().Mag()/ sqrt(jet2->p.Pt()), weight);
  sv_d_massVertexEnergyFraction -> Fill(sv1->p.M() / sv1->p.E() - sv2->p.M() / sv2->p.E(), weight);

  return;
}


void btaggingDeltaHists::FillTrkTagVarHists(const trkTagVarPtr &trkTag1, 
					    const trkTagVarPtr &trkTag2, 
					    float weight){

  trkTag_d_ip3d      ->Fill(trkTag1->trackSip3dVal - trkTag2->trackSip3dVal);
  trkTag_d_ip3d_l    ->Fill(trkTag1->trackSip3dVal - trkTag2->trackSip3dVal);
  trkTag_d_ip3d_sig  ->Fill(trkTag1->trackSip3dSig - trkTag2->trackSip3dSig);
  trkTag_d_ip3d_sig_l->Fill(trkTag1->trackSip3dSig - trkTag2->trackSip3dSig);

  float ip3d_err_1 = trkTag1->trackSip3dSig ? trkTag1->trackSip3dVal/trkTag1->trackSip3dSig : 0;
  float ip3d_err_2 = trkTag2->trackSip3dSig ? trkTag2->trackSip3dVal/trkTag2->trackSip3dSig : 0;
  trkTag_d_ip3d_err  ->Fill(ip3d_err_1 - ip3d_err_2);
  trkTag_d_ip3d_err_l->Fill(ip3d_err_1 - ip3d_err_2);

  trkTag_d_ip2d      ->Fill(trkTag1->trackSip2dVal - trkTag2->trackSip2dVal);
  trkTag_d_ip2d_l    ->Fill(trkTag1->trackSip2dVal - trkTag2->trackSip2dVal);
  trkTag_d_ip2d_sig  ->Fill(trkTag1->trackSip2dSig - trkTag2->trackSip2dSig);
  trkTag_d_ip2d_sig_l->Fill(trkTag1->trackSip2dSig - trkTag2->trackSip2dSig);

  float ip2d_err_1 = trkTag1->trackSip2dSig ? trkTag1->trackSip2dVal/trkTag1->trackSip2dSig : 0;
  float ip2d_err_2 = trkTag2->trackSip2dSig ? trkTag2->trackSip2dVal/trkTag2->trackSip2dSig : 0;
  trkTag_d_ip2d_err  ->Fill(ip2d_err_1 - ip2d_err_2);
  trkTag_d_ip2d_err_l->Fill(ip2d_err_1 - ip2d_err_2);
        

  trkTag_d_trackDecayLenVal_l   ->Fill(trkTag1->trackDecayLenVal - trkTag2->trackDecayLenVal,weight );
  trkTag_d_trackDecayLenVal     ->Fill(trkTag1->trackDecayLenVal - trkTag2->trackDecayLenVal,weight );
  trkTag_d_trackJetDistVal      ->Fill(trkTag1->trackJetDistVal  - trkTag2->trackJetDistVal ,weight );
  trkTag_d_trackPtRel           ->Fill(trkTag1->trackPtRel       - trkTag2->trackPtRel      ,weight );
  trkTag_d_trackMomentum        ->Fill(trkTag1->trackMomentum    - trkTag2->trackMomentum   ,weight ); 
  trkTag_d_trackPt              ->Fill(trkTag1->pt               - trkTag2->pt              ,weight ); 

  trkTag_d_trackEta             ->Fill(trkTag1->trackEta       - trkTag2->trackEta        ,weight );
  trkTag_d_trackPhi             ->Fill(trkTag1->trackPhi       - trkTag2->trackPhi        ,weight );
  trkTag_d_trackPPar            ->Fill(trkTag1->trackPPar      - trkTag2->trackPPar       ,weight );
  trkTag_d_trackDeltaR          ->Fill(trkTag1->trackDeltaR    - trkTag2->trackDeltaR     ,weight );
  trkTag_d_trackDeltaR_l        ->Fill(trkTag1->trackDeltaR    - trkTag2->trackDeltaR     ,weight );
  trkTag_d_trackEtaRel          ->Fill(trkTag1->trackEtaRel    - trkTag2->trackEtaRel     ,weight );
  trkTag_d_trackPtRatio         ->Fill(trkTag1->trackPtRatio   - trkTag2->trackPtRatio    ,weight );
  trkTag_d_trackPParRatio       ->Fill(trkTag1->trackPParRatio - trkTag2->trackPParRatio  ,weight );

  trkTag_d_trackChi2                  ->Fill(trkTag1->trackChi2       - trkTag2->trackChi2      ,weight );
  trkTag_d_trackNTotalHits            ->Fill(trkTag1->trackNTotalHits - trkTag2->trackNTotalHits,weight ); 
  trkTag_d_trackNPixelHits            ->Fill(trkTag1->trackNPixelHits - trkTag2->trackNPixelHits,weight );

  trkTag_d_isFromV0->Fill(trkTag1->matchIsFromV0 - trkTag2->matchIsFromV0, weight);

  return;
}


void btaggingDeltaHists::FillTagVarHists(const tagVarPtr &tag1, 
					 const tagVarPtr &tag2, 
					 float weight){
  
  tag_d_jetNTracks                  ->Fill(tag1-> jetNTracks                  - tag2-> jetNTracks                  ,weight);
  tag_d_jetNSecondaryVertices       ->Fill(tag1-> jetNSecondaryVertices       - tag2-> jetNSecondaryVertices       ,weight);
  tag_d_chargedMultiplicity         ->Fill(tag1-> chargedMultiplicity         - tag2-> chargedMultiplicity         ,weight);
  tag_d_chargedHadronEnergyFraction ->Fill(tag1-> chargedHadronEnergyFraction - tag2-> chargedHadronEnergyFraction ,weight);
  tag_d_chargedHadronMultiplicity   ->Fill(tag1-> chargedHadronMultiplicity   - tag2-> chargedHadronMultiplicity   ,weight);
  tag_d_chargedEmEnergyFraction     ->Fill(tag1-> chargedEmEnergyFraction     - tag2-> chargedEmEnergyFraction     ,weight);
  tag_d_neutralMultiplicity         ->Fill(tag1-> neutralMultiplicity         - tag2-> neutralMultiplicity         ,weight);
  tag_d_neutralHadronEnergyFraction ->Fill(tag1-> neutralHadronEnergyFraction - tag2-> neutralHadronEnergyFraction ,weight);
  tag_d_neutralHadronMultiplicity   ->Fill(tag1-> neutralHadronMultiplicity   - tag2-> neutralHadronMultiplicity   ,weight);
  tag_d_neutralEmEnergyFraction     ->Fill(tag1-> neutralEmEnergyFraction     - tag2-> neutralEmEnergyFraction     ,weight);
  tag_d_photonEnergyFraction        ->Fill(tag1-> photonEnergyFraction        - tag2-> photonEnergyFraction        ,weight);
  tag_d_photonMultiplicity          ->Fill(tag1-> photonMultiplicity          - tag2-> photonMultiplicity          ,weight);
  tag_d_muonEnergyFraction          ->Fill(tag1-> muonEnergyFraction          - tag2-> muonEnergyFraction          ,weight);
  tag_d_muonMultiplicity            ->Fill(tag1-> muonMultiplicity            - tag2-> muonMultiplicity            ,weight);
  tag_d_elecEnergyFraction          ->Fill(tag1-> electronEnergyFraction      - tag2-> electronEnergyFraction      ,weight);
  tag_d_elecMultiplicity            ->Fill(tag1-> electronMultiplicity        - tag2-> electronMultiplicity        ,weight);
  tag_d_totalMultiplicity           ->Fill(tag1-> numberOfDaughters           - tag2-> numberOfDaughters           ,weight);



}

btaggingDeltaHists::~btaggingDeltaHists(){} 
