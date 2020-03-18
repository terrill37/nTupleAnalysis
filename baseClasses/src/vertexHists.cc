#include "nTupleAnalysis/baseClasses/interface/vertexHists.h"

using namespace nTupleAnalysis;

vertexHists::vertexHists(std::string name, fwlite::TFileService& fs, std::string title) {

  dir = fs.mkdir(name);

  n           = dir.make<TH1F>("n",   (name+"/n;   "+title+" N Verties ;   Entries").c_str(), 100,-0.5,299.5);
  nGood       = dir.make<TH1F>("nGood",   (name+"/nGood;   "+title+" N Good Verties ;   Entries").c_str(), 100,-0.5,299.5);
  nReal       = dir.make<TH1F>("nReal",   (name+"/nReal;   "+title+" N Real Verties ;   Entries").c_str(), 100,-0.5,299.5);
  nRealGood   = dir.make<TH1F>("nRealGood",   (name+"/nRealGood;   "+title+" N Real Good Verties ;   Entries").c_str(), 100,-0.5,299.5);

  x   = dir.make<TH1F>("x",   (name+"/x;   "+title+" Vertex X;   Entries").c_str(), 100,-0.01,0.01);
  y   = dir.make<TH1F>("y",   (name+"/y;   "+title+" Vertex Y;   Entries").c_str(), 100,-0.01,0.01);
  z   = dir.make<TH1F>("z",   (name+"/z;   "+title+" Vertex Z;   Entries").c_str(), 100,-20,20);
  ex  = dir.make<TH1F>("ex",  (name+"/ex;  "+title+" Vertex X;   Entries").c_str(), 100,-1e-5,0.001);
  ey  = dir.make<TH1F>("ey",  (name+"/ey;  "+title+" Vertex Y;   Entries").c_str(), 100,-1e-5,0.001);
  ez  = dir.make<TH1F>("ez",  (name+"/ez;  "+title+" Vertex Z;   Entries").c_str(), 100,-1e-5,0.005);
  chi2 = dir.make<TH1F>("chi2",  (name+"/chi2;  "+title+" Vertex chi2;   Entries").c_str(), 100,0,5);
  ndf  = dir.make<TH1F>("ndf",  (name+"/ndf;  "+title+" Vertex ndf;   Entries").c_str(), 100,0,500);
  ndf_l  = dir.make<TH1F>("ndf_l",  (name+"/ndf_l;  "+title+" Vertex ndf;   Entries").c_str(), 100,0,1000);
  isgood  = dir.make<TH1F>("isgood",  (name+"/isgood;  "+title+" Vertex isgood;   Entries").c_str(), 2,-0.5,1.5);
  isfake  = dir.make<TH1F>("isfake",  (name+"/isfake;  "+title+" Vertex isfake;   Entries").c_str(), 2,-0.5,1.5);
} 

void vertexHists::makeDiffHists(std::string name, fwlite::TFileService& fs, std::string title) {
  dx   = dir.make<TH1F>("dx",   (name+"/dx;   "+title+" Vertex #Delta X;   Entries").c_str(), 100,-0.005,0.005);
  dy   = dir.make<TH1F>("dy",   (name+"/dy;   "+title+" Vertex #Delta Y;   Entries").c_str(), 100,-0.005,0.005);
  dz_s = dir.make<TH1F>("dz_s", (name+"/dz_s; "+title+" Vertex #Delta Z;   Entries").c_str(), 100,-0.5,0.5);
  dz   = dir.make<TH1F>("dz",   (name+"/dz;   "+title+" Vertex #Delta Z;   Entries").c_str(), 100,-2,2);
  dz_l = dir.make<TH1F>("dz_l", (name+"/dz_l; "+title+" Vertex #Delta Z;   Entries").c_str(), 100,-20,20);

  dex   = dir.make<TH1F>("dex",   (name+"/dex;   "+title+" Vertex #Delta #sigma X;   Entries").c_str(), 100,-0.005,0.005);
  dey   = dir.make<TH1F>("dey",   (name+"/dey;   "+title+" Vertex #Delta #sigma Y;   Entries").c_str(), 100,-0.005,0.005);
  dez   = dir.make<TH1F>("dez",   (name+"/dez;   "+title+" Vertex #Delta #sigma Z;   Entries").c_str(), 100,-0.02,0.02);

  dchi2 = dir.make<TH1F>("dchi2",  (name+"/dchi2;  "+title+" Vertex #Delta chi2;   Entries").c_str(), 100,-4,4);
  dndf  = dir.make<TH1F>("dndf",  (name+"/dndf;  "+title+" Vertex #Delta ndf;   Entries").c_str(), 100,-500,500);

  nVsN   = dir.make<TH2F>("nVsN",   (name+"/nVsN;   "+title+" N Verties ;   Entries").c_str(), 50,-0.5,299.5, 50, -0.5, 299.5);

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
    ndf_l   -> Fill(vtx->ndf   , weight);
    isgood  -> Fill(vtx->isgood, weight);
    isfake  -> Fill(vtx->isfake, weight);
  }


  n -> Fill(vtxs.size(),weight);
  unsigned int numGood = 0;
  unsigned int numReal = 0;
  unsigned int numRealGood = 0;

  for(const vertexPtr& v : vtxs){
    if(v->isgood){
      ++numGood;
    }

    if(!v->isfake){
      ++numReal;
      if(v->isgood){
	++numRealGood;
      }
    }

  }
  nGood       -> Fill(numGood,     weight);
  nReal       -> Fill(numReal,     weight);
  nRealGood   -> Fill(numRealGood, weight);



  return;
}

void vertexHists::FillDiffHists(const std::vector<vertexPtr> &vtxs1, const std::vector<vertexPtr> &vtxs2, float weight){

  if(vtxs1.size() > 0 && vtxs2.size() > 0){
    const vertexPtr& vtx1 = vtxs1.at(0);
    const vertexPtr& vtx2 = vtxs2.at(0);

    dx       -> Fill(vtx1->x - vtx2->x   , weight);
    dy       -> Fill(vtx1->y - vtx2->y   , weight);
    dz_s     -> Fill(vtx1->z - vtx2->z   , weight);
    dz       -> Fill(vtx1->z - vtx2->z   , weight);
    dz_l     -> Fill(vtx1->z - vtx2->z   , weight);

    dex       -> Fill(vtx1->ex - vtx2->ex   , weight);
    dey       -> Fill(vtx1->ey - vtx2->ey   , weight);
    dez       -> Fill(vtx1->ez - vtx2->ez   , weight);

    dchi2    -> Fill(vtx1->chi2 - vtx2->chi2  , weight);
    dndf     -> Fill(vtx1->ndf  - vtx2->ndf   , weight);

  }

  nVsN   ->Fill(vtxs1.size(), vtxs2.size(), weight);

}


vertexHists::~vertexHists(){} 
