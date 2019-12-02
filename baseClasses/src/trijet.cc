#include "nTupleAnalysis/baseClasses/interface/trijet.h"

using namespace nTupleAnalysis;

//trijet object
//trijet::trijet(){}
trijet::trijet(std::shared_ptr<jet> &jet1, std::shared_ptr<jet> &jet2, std::shared_ptr<jet> &jet3){

  //// sanity checks
  //float dr12 = jet1->p.DeltaR(jet2->p);
  //float dr13 = jet1->p.DeltaR(jet3->p);
  //float dr23 = jet2->p.DeltaR(jet3->p);
  //assert(dr12 >= 0.1);
  //assert(dr13 >= 0.1);
  //assert(dr23 >= 0.1);


  b = jet1;
  jet_j = jet2;
  jet_l = jet3;
  W = std::make_shared<dijet>(dijet(jet2, jet3));
  
  st  = jet1->pt + jet2->pt + jet3->pt;
  p   = jet1->p  + jet2->p  + jet3->p;
  pt  = p.Pt();
  eta = p.Eta();
  phi = p.Phi();
  m   = p.M();
  e   = p.E();

  dRbW = W->p.DeltaR(b->p);
  xt   = (m-mt)/(0.10*m);
  xWt  = sqrt(pow(W->xW, 2) + pow(xt, 2));
  mbW  = (b->p + W->pW).M();
  pbW  = (b->p + W->pW)*(mt/mbW);

}

trijet::~trijet(){}


