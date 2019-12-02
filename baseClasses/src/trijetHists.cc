#include "nTupleAnalysis/baseClasses/interface/trijetHists.h"

using namespace nTupleAnalysis;

trijetHists::trijetHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    v = new fourVectorHists(name, dir, title);
    W = new dijetHists(name+"/W", fs, "W Candidate");
    dRbW = dir.make<TH1F>("dRbW", (name+"/dRbW; "+title+" #DeltaR(b,W); Entries").c_str(), 50,0,5);
    mbW  = dir.make<TH1F>("mbW",  (name+"/mbW;  "+title+" m_{b,W};      Entries").c_str(),100,0,500);
    xWt  = dir.make<TH1F>("xWt",  (name+"/xWt; "+title+" X_{Wt};   Entries").c_str(), 60, 0, 12);

    mW_vs_mt = dir.make<TH2F>("mW_vs_mt", (name+"/mW_vs_mt; W Candidate Mass [GeV]; Top Candidate Mass [GeV]; Entries").c_str(), 50,0,250, 50,80,280);
    xW_vs_xt = dir.make<TH2F>("xW_vs_xt", (name+"/xW_vs_xt; x_{W}; x_{t}; Entries").c_str(), 50,-10, 10, 50,-10,10);

} 

void trijetHists::Fill(std::shared_ptr<trijet> &trijet, float weight){
  if(!trijet) return;
  
  v->Fill(trijet->p, weight);
  W->Fill(trijet->W, weight);

  dRbW->Fill(trijet->dRbW, weight);
  mbW->Fill(trijet->mbW, weight);
  xWt->Fill(trijet->xWt, weight);

  mW_vs_mt->Fill(trijet->W->m, trijet->m, weight);
  xW_vs_xt->Fill(trijet->W->xW, trijet->xt, weight);

  return;
}

trijetHists::~trijetHists(){} 
