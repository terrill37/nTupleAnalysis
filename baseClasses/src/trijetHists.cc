#include "nTupleAnalysis/baseClasses/interface/trijetHists.h"

using namespace nTupleAnalysis;

trijetHists::trijetHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);
    t = new fourVectorHists(name, dir, title);
    b = new fourVectorHists(name+"/b", fs, title);
    W = new dijetHists(name+"/W", fs, "W Candidate");
    dRbW = dir.make<TH1F>("dRbW", (name+"/dRbW; "+title+" #DeltaR(b,W); Entries").c_str(), 50, 0,  5);
    mbW  = dir.make<TH1F>("mbW",  (name+"/mbW;  "+title+" m_{b,W};      Entries").c_str(),100, 0,500);
    xWt  = dir.make<TH1F>("xWt",  (name+"/xWt;  "+title+" X_{Wt};       Entries").c_str(), 60, 0, 12);
    xWbW = dir.make<TH1F>("xWbW", (name+"/xWbW; "+title+" X_{W,bW};     Entries").c_str(), 60, 0, 12);
    rWbW = dir.make<TH1F>("rWbW", (name+"/rWbW; "+title+" r_{W,bW};     Entries").c_str(), 60, 0, 12);

    mW_vs_mt = dir.make<TH2F>("mW_vs_mt", (name+"/mW_vs_mt;  W Candidate Mass [GeV]; Top Candidate Mass [GeV]; Entries").c_str(), 50,0,250, 50,80,280);
    mW_vs_mbW= dir.make<TH2F>("mW_vs_mbW",(name+"/mW_vs_mbW; W Candidate Mass [GeV]; m_{b,W} [GeV]; Entries").c_str(), 50,0,250, 50,80,280);
    xW_vs_xt = dir.make<TH2F>("xW_vs_xt", (name+"/xW_vs_xt;  x_{W}; x_{t}; Entries").c_str(), 50,-10, 10, 50,-10,10);
    xW_vs_xbW= dir.make<TH2F>("xW_vs_xbW",(name+"/xW_vs_xbW; x_{W}; x_{bW}; Entries").c_str(), 50,-10, 10, 50,-10,10);

    deepFlavB_b     = dir.make<TH1F>("deepFlavB_b",     (name+"/deepFlavB_b; "    +title+" DeepFlav B (b); Entries").c_str(), 100,0,1);
    deepFlavB_j     = dir.make<TH1F>("deepFlavB_j",     (name+"/deepFlavB_j; "    +title+" DeepFlav B (j); Entries").c_str(), 100,0,1);
    deepFlavB_l     = dir.make<TH1F>("deepFlavB_l",     (name+"/deepFlavB_l; "    +title+" DeepFlav B (l); Entries").c_str(), 100,0,1);
} 

void trijetHists::Fill(std::shared_ptr<trijet> &trijet, float weight){
  if(!trijet) return;
  
  t->Fill(trijet->p, weight);
  b->Fill(trijet->b->p, weight);
  W->Fill(trijet->W, weight);

  dRbW->Fill(trijet->dRbW, weight);
  mbW ->Fill(trijet->mbW,  weight);
  xWt ->Fill(trijet->xWt,  weight);
  xWbW->Fill(trijet->xWbW, weight);
  rWbW->Fill(trijet->rWbW, weight);

  mW_vs_mt ->Fill(trijet->W->m,  trijet->m,   weight);
  mW_vs_mbW->Fill(trijet->W->m,  trijet->mbW, weight);
  xW_vs_xt ->Fill(trijet->W->xW, trijet->xt,  weight);
  xW_vs_xbW->Fill(trijet->W->xW, trijet->xbW, weight);

  deepFlavB_b->Fill(trijet->b    ->deepFlavB, weight);
  deepFlavB_j->Fill(trijet->jet_j->deepFlavB, weight);
  deepFlavB_l->Fill(trijet->jet_l->deepFlavB, weight);

  return;
}

trijetHists::~trijetHists(){} 
