#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/secondaryVertexData.h"

using namespace nTupleAnalysis;



//secondaryVertex object
secondaryVertex::secondaryVertex(){}
secondaryVertex::secondaryVertex(UInt_t i, secondaryVertexData* data){

  x                    = data->x                 [i];
  y                    = data->y                 [i];
  z                    = data->z                 [i];
  ex                   = data->ex                [i];
  ey                   = data->ey                [i];
  ez                   = data->ez                [i];
  chi2                 = data->chi2              [i];
  ndf                  = data->ndf               [i];
  flight               = data->flight            [i];
  flightErr            = data->flightErr         [i];
  deltaR_jet           = data->deltaR_jet        [i];
  deltaR_sum_jet       = data->deltaR_sum_jet    [i];
  deltaR_sum_dir       = data->deltaR_sum_dir    [i];
  vtx_pt               = data->vtx_pt            [i];
  flight2D             = data->flight2D          [i];
  flight2DErr          = data->flight2DErr       [i];
  totCharge            = data->totCharge         [i];
  vtxDistJetAxis       = data->vtxDistJetAxis    [i];
  nTrk                 = data->nTrk              [i];
  mass                 = data->mass              [i];
  vtx_eta              = data->vtx_eta           [i];
  vtx_phi              = data->vtx_phi           [i];
  EnergyRatio          = data->EnergyRatio       [i];
  dir_x                = data->dir_x             [i];
  dir_y                = data->dir_y             [i];
  dir_z                = data->dir_z             [i];


}


secondaryVertex::~secondaryVertex(){}


//access tree
secondaryVertexData::secondaryVertexData(std::string name, TChain* tree){

 
  //nSV       : nSV/I                                                  *

  initBranch(tree, (name+"SV_x"                ).c_str(),   x                 );
  initBranch(tree, (name+"SV_y"                ).c_str(),   y                 );
  initBranch(tree, (name+"SV_z"                ).c_str(),   z                 );
  initBranch(tree, (name+"SV_ex"               ).c_str(),   ex                );
  initBranch(tree, (name+"SV_ey"               ).c_str(),   ey                );
  initBranch(tree, (name+"SV_ez"               ).c_str(),   ez                );
  initBranch(tree, (name+"SV_chi2"             ).c_str(),   chi2              );
  initBranch(tree, (name+"SV_ndf"              ).c_str(),   ndf               );
  initBranch(tree, (name+"SV_flight"           ).c_str(),   flight            );
  initBranch(tree, (name+"SV_flightErr"        ).c_str(),   flightErr         );
  initBranch(tree, (name+"SV_deltaR_jet"       ).c_str(),   deltaR_jet        );
  initBranch(tree, (name+"SV_deltaR_sum_jet"   ).c_str(),   deltaR_sum_jet    );
  initBranch(tree, (name+"SV_deltaR_sum_dir"   ).c_str(),   deltaR_sum_dir    );
  initBranch(tree, (name+"SV_vtx_pt"           ).c_str(),   vtx_pt            );
  initBranch(tree, (name+"SV_flight2D"         ).c_str(),   flight2D          );
  initBranch(tree, (name+"SV_flight2DErr"      ).c_str(),   flight2DErr       );
  initBranch(tree, (name+"SV_totCharge"        ).c_str(),   totCharge         );
  initBranch(tree, (name+"SV_vtxDistJetAxis"   ).c_str(),   vtxDistJetAxis    );
  initBranch(tree, (name+"SV_nTrk"             ).c_str(),   nTrk              );
  initBranch(tree, (name+"SV_mass"             ).c_str(),   mass              );
  initBranch(tree, (name+"SV_vtx_eta"          ).c_str(),   vtx_eta           );
  initBranch(tree, (name+"SV_vtx_phi"          ).c_str(),   vtx_phi           );
  initBranch(tree, (name+"SV_EnergyRatio"      ).c_str(),   EnergyRatio       );
  initBranch(tree, (name+"SV_dir_x"            ).c_str(),   dir_x             );
  initBranch(tree, (name+"SV_dir_y"            ).c_str(),   dir_y             );
  initBranch(tree, (name+"SV_dir_z"            ).c_str(),   dir_z             );

}


std::vector< std::shared_ptr<secondaryVertex> > secondaryVertexData::getSecondaryVertices(int nFirstSV, int nLastSV){
  
  std::vector< std::shared_ptr<secondaryVertex> > outputSVs;
  for(int i = nFirstSV; i < nLastSV; ++i){
    outputSVs.push_back(std::make_shared<secondaryVertex>(secondaryVertex(i, this)));
  }
  return outputSVs;
}



secondaryVertexData::~secondaryVertexData(){}

