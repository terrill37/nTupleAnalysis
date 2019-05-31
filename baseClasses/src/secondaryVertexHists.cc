#include "nTupleAnalysis/baseClasses/interface/secondaryVertexHists.h"

using namespace nTupleAnalysis;

secondaryVertexHists::secondaryVertexHists(std::string name, fwlite::TFileService& fs, std::string title) {
  TFileDirectory dir = fs.mkdir(name);
  this->makeHists(name, dir, title);
}

secondaryVertexHists::secondaryVertexHists(std::string name, TFileDirectory& dir, std::string title) {
  this->makeHists(name, dir, title);
}


void secondaryVertexHists::makeHists(std::string name, TFileDirectory& dir, std::string title) {

  NTracks                    = dir.make<TH1F>("NTracks"                ,"vertexNTracks;nVertex Tracks;Entries"                 ,22, -2.5, 19.5);
  Mass                       = dir.make<TH1F>("Mass"                   ,"vertexMass;Vertex Mass [GeV]"                    ,100, -0.5, 10);
  JetDeltaR                  = dir.make<TH1F>("JetDeltaR"              ,"vertexJetDeltaR;Vertex-Jet #Delta R"               ,100, -0.01, 0.4);
  //FitProb                    = dir.make<TH1F>("FitProb"                ,"vertexFitProb;Vertex Fit Prob"                 ,100, -50, 50);
  EnergyRatio                = dir.make<TH1F>("EnergyRatio"            ,"vertexEnergyRatio;Vertex Energy Fraction "             ,100, -0.1, 3);
  R              = dir.make<TH1F>("R          "            ,"R          ;Vertex R           "             ,100, -0.1, 5);
  Z              = dir.make<TH1F>("Z          "            ,"Z          ;Vertex Z           "             ,100, -20, 20);
  Chi2           = dir.make<TH1F>("Chi2       "            ,"Chi2       ;Vertex Chi2        "             ,100, -0.1, 10);
  NDF            = dir.make<TH1F>("NDF        "            ,"NDF        ;Vertex NDF         "             ,20, -0.5, 19.5);
  Flight         = dir.make<TH1F>("Flight     "            ,"Flight     ;Vertex Flight      "             ,100, -0.1, 5);
  FlightSig      = dir.make<TH1F>("FlightSig  "            ,"FlightSig  ;Vertex FlightSig   "             ,100, -0.1, 30);
  Flight2D       = dir.make<TH1F>("Flight2D   "            ,"Flight2D   ;Vertex Flight2D    "             ,100, -0.1, 5);
  FlightSig2D    = dir.make<TH1F>("FlightSig2D"            ,"FlightSig2D;Vertex FlightSig2D "             ,100, -0.1, 30);
  Pt             = dir.make<TH1F>("Pt         "            ,"Pt         ;Vertex Pt          "             ,100, -0.1, 100);
  Eta            = dir.make<TH1F>("Eta        "            ,"Eta        ;Vertex Eta         "             ,100, -2.5, 2.5);
  Phi            = dir.make<TH1F>("Phi        "            ,"Phi        ;Vertex Phi         "             ,100, -3.2, 3.2);
  DistJetAxis    = dir.make<TH1F>("DistJetAxis"            ,"DistJetAxis;Vertex DistJetAxis "             ,100, -0.1, 10);


} 

void secondaryVertexHists::Fill(const svPtr &sv, float weight){

  
  NTracks                ->Fill(sv->nTrk, weight);
  Mass                   ->Fill(sv->mass, weight);
  JetDeltaR              ->Fill(sv->deltaR_jet, weight);
  //svFitProb                ->Fill(sv->, weight);
  EnergyRatio            ->Fill(sv->EnergyRatio, weight);

  float svR = sqrt(sv->x*sv->x + sv->y*sv->y);
  R                ->Fill(svR, weight);
  Z                ->Fill(sv->z, weight);
  Chi2             ->Fill(sv->chi2, weight);
  NDF              ->Fill(sv->ndf, weight);
  
  Flight           ->Fill(sv->flight, weight);
  float flightSig = sv->flightErr ? sv->flight/sv->flightErr : -1;
  FlightSig        ->Fill(flightSig, weight);
  
  Flight2D           ->Fill(sv->flight2D, weight);
  float flightSig2D = sv->flight2DErr ? sv->flight2D/sv->flight2DErr : -1;
  FlightSig2D        ->Fill(flightSig2D, weight);
  
  Pt                ->Fill(sv->vtx_pt, weight);
  Eta               ->Fill(sv->vtx_eta, weight);
  Phi               ->Fill(sv->vtx_phi, weight);
  DistJetAxis       ->Fill(sv->vtxDistJetAxis, weight);


  return;
}



secondaryVertexHists::~secondaryVertexHists(){} 
