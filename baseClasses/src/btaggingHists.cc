#include "nTupleAnalysis/baseClasses/interface/btaggingHists.h"

using namespace nTupleAnalysis;

btaggingHists::btaggingHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}

btaggingHists::btaggingHists(std::string name, TFileDirectory& dir, std::string title) {
  this->makeHists(name, dir, title);
}


void btaggingHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {

  sv_NTracks                    = dir.make<TH1F>("sv_NTracks"                ,"vertexNTracks;nVertex Tracks;Entries"                 ,22, -2.5, 19.5);
  sv_Mass                       = dir.make<TH1F>("sv_Mass"                   ,"vertexMass;Vertex Mass [GeV]"                    ,100, -0.5, 10);
  sv_JetDeltaR                  = dir.make<TH1F>("sv_JetDeltaR"              ,"vertexJetDeltaR;Vertex-Jet #Delta R"               ,100, -0.01, 0.4);
  //FitProb                    = dir.make<TH1F>("sv_FitProb"                ,"vertexFitProb;Vertex Fit Prob"                 ,100, -50, 50);
  sv_EnergyRatio                = dir.make<TH1F>("sv_EnergyRatio"            ,"vertexEnergyRatio;Vertex Energy Fraction "             ,100, -0.1, 3);
  sv_R              = dir.make<TH1F>("sv_R          "            ,"R          ;Vertex R           "             ,100, -0.1, 5);
  sv_Z              = dir.make<TH1F>("sv_Z          "            ,"Z          ;Vertex Z           "             ,100, -20, 20);
  sv_Chi2           = dir.make<TH1F>("sv_Chi2       "            ,"Chi2       ;Vertex Chi2        "             ,100, -0.1, 10);
  sv_NDF            = dir.make<TH1F>("sv_NDF        "            ,"NDF        ;Vertex NDF         "             ,20, -0.5, 19.5);
  sv_Flight         = dir.make<TH1F>("sv_Flight     "            ,"Flight     ;Vertex Flight      "             ,100, -0.1, 5);
  sv_FlightSig      = dir.make<TH1F>("sv_FlightSig  "            ,"FlightSig  ;Vertex FlightSig   "             ,100, -0.1, 30);
  sv_Flight2D       = dir.make<TH1F>("sv_Flight2D   "            ,"Flight2D   ;Vertex Flight2D    "             ,100, -0.1, 5);
  sv_FlightSig2D    = dir.make<TH1F>("sv_FlightSig2D"            ,"FlightSig2D;Vertex FlightSig2D "             ,100, -0.1, 30);
  sv_Pt             = dir.make<TH1F>("sv_Pt         "            ,"Pt         ;Vertex Pt          "             ,100, -0.1, 100);
  sv_Eta            = dir.make<TH1F>("sv_Eta        "            ,"Eta        ;Vertex Eta         "             ,100, -2.5, 2.5);
  sv_Phi            = dir.make<TH1F>("sv_Phi        "            ,"Phi        ;Vertex Phi         "             ,100, -3.2, 3.2);
  sv_DistJetAxis    = dir.make<TH1F>("sv_DistJetAxis"            ,"DistJetAxis;Vertex DistJetAxis "             ,100, -0.1, 10);
  sv_nSVs           = dir.make<TH1F>("sv_nSVs",     ("nSVs;    " +title+" Number of Sec. Verticies; Entries").c_str(),  10,-0.5,9.5);



  trkTag_ip3d_l = dir.make<TH1F>("ip3d_l","ip3d;IP3D [cm]",100,-0.2,0.2);
  trkTag_ip3d   = dir.make<TH1F>("ip3d",  "ip3d;IP3D [cm]",100,-0.05,0.05);
  trkTag_ip3d_sig_l = dir.make<TH1F>("ip3d_sig_l","ip3d sig;IP3D significance",100,-100,100);
  trkTag_ip3d_sig   = dir.make<TH1F>("ip3d_sig",  "ip3d sig;IP3D significance",100,-10,10);
  trkTag_ip3d_err_l = dir.make<TH1F>("ip3d_err_l","ip3d err;IP3D uncertianty [cm]",100,-0.01,0.1);
  trkTag_ip3d_err   = dir.make<TH1F>("ip3d_err",  "ip3d err;IP3D uncertianty [cm]",100,-0.001,0.01);
  
  trkTag_ip2d_l = dir.make<TH1F>("ip2d_l","ip2d;IP2D [cm]",100,-0.2,0.2);
  trkTag_ip2d   = dir.make<TH1F>("ip2d",  "ip2d;IP2D [cm]",100,-0.05,0.05);
  trkTag_ip2d_sig_l = dir.make<TH1F>("ip2d_sig_l","ip2d sig;IP2D significance",100,-100,100);
  trkTag_ip2d_sig   = dir.make<TH1F>("ip2d_sig",  "ip2d sig;IP2D significance",100,-10,10);
  trkTag_ip2d_err_l = dir.make<TH1F>("ip2d_err_l","ip2d err;IP2D uncertianty [cm]",100,-0.01,0.1);
  trkTag_ip2d_err   = dir.make<TH1F>("ip2d_err",  "ip2d err;IP2D uncertianty [cm]",100,-0.001,0.01);
    
  trkTag_trackDecayLenVal_l         = dir.make<TH1F>("trackDecayLenVal_l"  ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  6);
  trkTag_trackDecayLenVal           = dir.make<TH1F>("trackDecayLenVal"    ,    "trackDecayLenVal;trackDecayLenVal [cm];Entries", 100, -0.1,  0.5);
  trkTag_trackJetDistVal            = dir.make<TH1F>("trackJetDistVal"     ,    "trackJetDistVal;trackJetDistVal [cm];Entries",  100, -0.1,0.01);      
  trkTag_trackPtRel                 = dir.make<TH1F>("trackPtRel"          ,    "trackPtRel;track p_{T} Rel [GeV];Entries", 100, -0.1, 7);          
  trkTag_trackPt                    = dir.make<TH1F>("trackPt"             ,    "trackPt;track pt [GeV];Entries", 20, 0, 20);       
  trkTag_trackMomentum              = dir.make<TH1F>("trackMomentum"       ,    "trackMomentum;track momentum [GeV];Entries", 60, 0, 60);       

  Double_t binsPt[28] = {0.9, 1.116, 1.3838, 1.716, 2.1278, 2.6385, 3.2717, 4.0569, 5.0306, 6.2379, 7.735, 9.5914, 11.8933, 14.7477, 18.2872, 22.6761, 28.1183, 34.8667, 43.2347, 53.6111, 66.4777, 82.4324, 102.2162, 126.748, 157.1676, 194.8878, 241.6609, 299.6595};
  trkTag_trackPt_logx               = dir.make<TH1F>("trackPt_logx", "trackPt;track p_{T} [GeV];Entries", 27, binsPt);
  trkTag_trackEta                   = dir.make<TH1F>("trackEta"            ,    "trackEta;track #eta;Entries", 100, -2.6, 2.6);            
  trkTag_trackPhi                   = dir.make<TH1F>("trackPhi"            ,    "trackPhi;track #phi;Entries", 100, -3.2, 3.2);            
  trkTag_trackPPar                  = dir.make<TH1F>("trackPPar"           ,    "trackPPar;track PPar [GeV];Entries",60, 0, 60);           
  trkTag_trackDeltaR                = dir.make<TH1F>("trackDeltaR"         ,    "trackDeltaR;track #DeltaR;Entries", 160, -0.05, 0.35);         
  trkTag_trackDeltaR_l              = dir.make<TH1F>("trackDeltaR_l"       ,    "trackDeltaR;track #DeltaR;Entries", 160, -0.05, 0.6);         
  trkTag_trackEtaRel                = dir.make<TH1F>("trackEtaRel"         ,    "trackEtaRel;track Eta Rel;Entries", 100, 0, 7);         
  trkTag_trackPtRatio               = dir.make<TH1F>("trackPtRatio"        ,    "trackPtRatio;track p_{T} Ratio;Entries", 100, -0.01, 0.3); 
  trkTag_trackPParRatio             = dir.make<TH1F>("trackPParRatio"      ,    "trackPParRatio;track P Par Ratio;Entries", 100, 0.95, 1.02);  
  
  trkTag_trackChi2                  = dir.make<TH1F>("trackChi2"            ,    "trackChi2;track Chi2;Entries", 100, -0.1, 6);            
  trkTag_trackNTotalHits            = dir.make<TH1F>("trackNTotalHits"      ,    "trackNTotalHits;trackNTotalHits;Entries", 30, -0.5, 29.5);
  trkTag_trackNPixelHits            = dir.make<TH1F>("trackNPixelHits"      ,    "trackNPixelHits;trackNPixelHits;Entries", 10, -0.5,  9.5);  
  trkTag_nTracks                    = dir.make<TH1F>("nTracks",     ("nTrkTags;    " +title+" Number of Tracks; Entries").c_str(),  20,-0.5,19.5);
} 

void btaggingHists::FillSVHists(const svPtr &sv, float weight){

  
  sv_NTracks                ->Fill(sv->nTrk, weight);
  sv_Mass                   ->Fill(sv->mass, weight);
  sv_JetDeltaR              ->Fill(sv->deltaR_jet, weight);
  //svFitProb                ->Fill(sv->, weight);
  sv_EnergyRatio            ->Fill(sv->EnergyRatio, weight);

  float svR = sqrt(sv->x*sv->x + sv->y*sv->y);
  sv_R                ->Fill(svR, weight);
  sv_Z                ->Fill(sv->z, weight);
  sv_Chi2             ->Fill(sv->chi2, weight);
  sv_NDF              ->Fill(sv->ndf, weight);
  
  sv_Flight           ->Fill(sv->flight, weight);
  float flightSig = sv->flightErr ? sv->flight/sv->flightErr : -1;
  sv_FlightSig        ->Fill(flightSig, weight);
  
  sv_Flight2D           ->Fill(sv->flight2D, weight);
  float flightSig2D = sv->flight2DErr ? sv->flight2D/sv->flight2DErr : -1;
  sv_FlightSig2D        ->Fill(flightSig2D, weight);
  
  sv_Pt                ->Fill(sv->vtx_pt, weight);
  sv_Eta               ->Fill(sv->vtx_eta, weight);
  sv_Phi               ->Fill(sv->vtx_phi, weight);
  sv_DistJetAxis       ->Fill(sv->vtxDistJetAxis, weight);


  return;
}


void btaggingHists::FillTrkTagVarHists(const trkTagVarPtr &trkTag, float weight){

  trkTag_ip3d  ->Fill(trkTag->trackSip3dVal);
  trkTag_ip3d_l->Fill(trkTag->trackSip3dVal);
  trkTag_ip3d_sig  ->Fill(trkTag->trackSip3dSig);
  trkTag_ip3d_sig_l->Fill(trkTag->trackSip3dSig);

  float ip3d_err = trkTag->trackSip3dSig ? trkTag->trackSip3dVal/trkTag->trackSip3dSig : 0;
  trkTag_ip3d_err  ->Fill(ip3d_err);
  trkTag_ip3d_err_l->Fill(ip3d_err);

  trkTag_ip2d  ->Fill(trkTag->trackSip2dVal);
  trkTag_ip2d_l->Fill(trkTag->trackSip2dVal);
  trkTag_ip2d_sig  ->Fill(trkTag->trackSip2dSig);
  trkTag_ip2d_sig_l->Fill(trkTag->trackSip2dSig);

  float ip2d_err = trkTag->trackSip2dSig ? trkTag->trackSip2dVal/trkTag->trackSip2dSig : 0;
  trkTag_ip2d_err  ->Fill(ip2d_err);
  trkTag_ip2d_err_l->Fill(ip2d_err);
        

  trkTag_trackDecayLenVal_l   ->Fill(trkTag->trackDecayLenVal,weight );
  trkTag_trackDecayLenVal     ->Fill(trkTag->trackDecayLenVal,weight );
  trkTag_trackJetDistVal      ->Fill(trkTag->trackJetDistVal ,weight );
  trkTag_trackPtRel           ->Fill(trkTag->trackPtRel      ,weight );
  trkTag_trackMomentum        ->Fill(trkTag->trackMomentum   ,weight ); 
  trkTag_trackPt              ->Fill(trkTag->pt   ,weight ); 
  trkTag_trackPt_logx         ->Fill(trkTag->pt   ,weight ); 
  trkTag_trackEta             ->Fill(trkTag->trackEta        ,weight );
  trkTag_trackPhi             ->Fill(trkTag->trackPhi        ,weight );
  trkTag_trackPPar            ->Fill(trkTag->trackPPar       ,weight );
  trkTag_trackDeltaR          ->Fill(trkTag->trackDeltaR         ,weight );
  trkTag_trackDeltaR_l        ->Fill(trkTag->trackDeltaR         ,weight );
  trkTag_trackEtaRel          ->Fill(trkTag->trackEtaRel     ,weight );
  trkTag_trackPtRatio         ->Fill(trkTag->trackPtRatio    ,weight );
  trkTag_trackPParRatio       ->Fill(trkTag->trackPParRatio  ,weight );

  trkTag_trackChi2                  ->Fill(trkTag->trackChi2      ,weight );
  trkTag_trackNTotalHits            ->Fill(trkTag->trackNTotalHits,weight ); 
  trkTag_trackNPixelHits            ->Fill(trkTag->trackNPixelHits,weight );


//  trackDecayLenSi       = data->trackDecayLenSi  [i];

//  trackJetDistSig       = data->trackJetDistSig  [i];



  return;
}



btaggingHists::~btaggingHists(){} 
