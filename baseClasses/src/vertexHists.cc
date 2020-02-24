#include "nTupleAnalysis/baseClasses/interface/vertexHists.h"

using namespace nTupleAnalysis;

vertexHists::vertexHists(std::string name, fwlite::TFileService& fs, std::string title) {

    dir = fs.mkdir(name);

    x   = dir.make<TH1F>("x",   (name+"/x;   "+title+" Vertex X;   Entries").c_str(), 100,-0.01,0.01);
    y   = dir.make<TH1F>("y",   (name+"/y;   "+title+" Vertex Y;   Entries").c_str(), 100,-0.01,0.01);
    z   = dir.make<TH1F>("z",   (name+"/z;   "+title+" Vertex Z;   Entries").c_str(), 100,-20,20);
    ex  = dir.make<TH1F>("ex",  (name+"/ex;  "+title+" Vertex X;   Entries").c_str(), 100,-0.001,0.001);
    ey  = dir.make<TH1F>("ey",  (name+"/ey;  "+title+" Vertex Y;   Entries").c_str(), 100,-0.001,0.001);
    ez  = dir.make<TH1F>("ez",  (name+"/ez;  "+title+" Vertex Z;   Entries").c_str(), 100,-0.02,0.02);
    chi2 = dir.make<TH1F>("chi2",  (name+"/chi2;  "+title+" Vertex chi2;   Entries").c_str(), 100,0,5);
    ndf  = dir.make<TH1F>("ndf",  (name+"/ndf;  "+title+" Vertex ndf;   Entries").c_str(), 100,0,50);
    isgood  = dir.make<TH1F>("isgood",  (name+"/isgood;  "+title+" Vertex isgood;   Entries").c_str(), 2,-0.5,1.5);
    isfake  = dir.make<TH1F>("isfake",  (name+"/isfake;  "+title+" Vertex isfake;   Entries").c_str(), 2,-0.5,1.5);


} 

void vertexHists::Fill(const std::vector<vertexPtr> &vtxs, float weight){

  if(vtxs.size() > 0){
    const vertexPtr& vtx = vtxs.at(0);

    x       -> Fill(vtx->x     , weight);
    y       -> Fill(vtx->y     , weight);
    z       -> Fill(vtx->z     , weight);
    ex      -> Fill(vtx->ex    , weight);
    ey      -> Fill(vtx->ey    , weight);
    ez      -> Fill(vtx->ez    , weight);
    chi2    -> Fill(vtx->chi2  , weight);
    ndf     -> Fill(vtx->ndf   , weight);
    isgood  -> Fill(vtx->isgood, weight);
    isfake  -> Fill(vtx->isfake, weight);


  }

  return;
}

vertexHists::~vertexHists(){} 
