#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/trackData.h"

using namespace nTupleAnalysis;



//track object
track::track(){}
track::track(UInt_t i, trackData* data){

  pt  = data->pt[i];
  eta = data->eta[i];
  phi = data->phi[i];
  m   = 0.140;
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);
  e = p.E();

  dxy                  = data->dxy                  [i];
  dz                   = data->dz                   [i];
  dxyError             = data->dxyError             [i];
  dzError              = data->dzError              [i];
  sign2D               = data->sign2D               [i];
  sign3D               = data->sign3D               [i];
  length               = data->length               [i];
  dist                 = data->dist                 [i];
  IP2D                 = data->IP2D                 [i];
  IP2Dsig              = data->IP2Dsig              [i];
  IP2Derr              = data->IP2Derr              [i];
  IP                   = data->IP                   [i];
  IPsig                = data->IPsig                [i];
  IPerr                = data->IPerr                [i];
  Proba                = data->Proba                [i];
  chi2                 = data->chi2                 [i];
  charge               = data->charge               [i];
  history              = data->history              [i];
  nHitStrip            = data->nHitStrip            [i];
  nHitPixel            = data->nHitPixel            [i];
  nHitAll              = data->nHitAll              [i];
  nHitTIB              = data->nHitTIB              [i];
  nHitTID              = data->nHitTID              [i];
  nHitTOB              = data->nHitTOB              [i];
  nHitTEC              = data->nHitTEC              [i];
  nHitPXB              = data->nHitPXB              [i];
  nHitPXF              = data->nHitPXF              [i];
  isHitL1              = data->isHitL1              [i];
  PV                   = data->PV                   [i];
  SV                   = data->SV                   [i];
  PVweight             = data->PVweight             [i];
  SVweight             = data->SVweight             [i];
  isfromSV             = data->isfromSV             [i];
  isfromV0             = data->isfromV0             [i];
  category             = data->category             [i];
  algo                 = data->algo                 [i];
  originalAlgo         = data->originalAlgo         [i];
  //TPAssociationQuality = data->TPAssociationQuality [i];
  //idxMatchedTP         = data->idxMatchedTP         [i];


}


track::~track(){}


//access tree
trackData::trackData(std::string name, TChain* tree){

  //initBranch(tree, (name+"nTrack").c_str(), nTrack );    
  std::cout << "Creating trackData " << name << std::endl;
  initBranch(tree, (name+"Track_dxy"                  ).c_str(),          dxy                   );
  initBranch(tree, (name+"Track_dz"                   ).c_str(),          dz                    );
  initBranch(tree, (name+"Track_dxyError"             ).c_str(),          dxyError              );
  initBranch(tree, (name+"Track_dzError"              ).c_str(),          dzError               );
  initBranch(tree, (name+"Track_sign2D"               ).c_str(),          sign2D                );
  initBranch(tree, (name+"Track_sign3D"               ).c_str(),          sign3D                );
  initBranch(tree, (name+"Track_length"               ).c_str(),          length                );
  initBranch(tree, (name+"Track_dist"                 ).c_str(),          dist                  );
  initBranch(tree, (name+"Track_IP2D"                 ).c_str(),          IP2D                  );
  initBranch(tree, (name+"Track_IP2Dsig"              ).c_str(),          IP2Dsig               );
  initBranch(tree, (name+"Track_IP2Derr"              ).c_str(),          IP2Derr               );
  initBranch(tree, (name+"Track_IP"                   ).c_str(),          IP                    );
  initBranch(tree, (name+"Track_IPsig"                ).c_str(),          IPsig                 );
  initBranch(tree, (name+"Track_IPerr"                ).c_str(),          IPerr                 );
  initBranch(tree, (name+"Track_Proba"                ).c_str(),          Proba                 );
  initBranch(tree, (name+"Track_p"                    ).c_str(),          p                     );
  initBranch(tree, (name+"Track_pt"                   ).c_str(),          pt                    );
  initBranch(tree, (name+"Track_eta"                  ).c_str(),          eta                   );
  initBranch(tree, (name+"Track_phi"                  ).c_str(),          phi                   );
  initBranch(tree, (name+"Track_chi2"                 ).c_str(),          chi2                  );
  initBranch(tree, (name+"Track_charge"               ).c_str(),          charge                );
  initBranch(tree, (name+"Track_history"              ).c_str(),          history               );
  initBranch(tree, (name+"Track_nHitStrip"            ).c_str(),          nHitStrip             );
  initBranch(tree, (name+"Track_nHitPixel"            ).c_str(),          nHitPixel             );
  initBranch(tree, (name+"Track_nHitAll"              ).c_str(),          nHitAll               );
  initBranch(tree, (name+"Track_nHitTIB"              ).c_str(),          nHitTIB               );
  initBranch(tree, (name+"Track_nHitTID"              ).c_str(),          nHitTID               );
  initBranch(tree, (name+"Track_nHitTOB"              ).c_str(),          nHitTOB               );
  initBranch(tree, (name+"Track_nHitTEC"              ).c_str(),          nHitTEC               );
  initBranch(tree, (name+"Track_nHitPXB"              ).c_str(),          nHitPXB               );
  initBranch(tree, (name+"Track_nHitPXF"              ).c_str(),          nHitPXF               );
  initBranch(tree, (name+"Track_isHitL1"              ).c_str(),          isHitL1               );
  initBranch(tree, (name+"Track_PV"                   ).c_str(),          PV                    );
  initBranch(tree, (name+"Track_SV"                   ).c_str(),          SV                    );
  initBranch(tree, (name+"Track_PVweight"             ).c_str(),          PVweight              );
  initBranch(tree, (name+"Track_SVweight"             ).c_str(),          SVweight              );
  initBranch(tree, (name+"Track_isfromSV"             ).c_str(),          isfromSV              );
  initBranch(tree, (name+"Track_isfromV0"             ).c_str(),          isfromV0              );
  initBranch(tree, (name+"Track_category"             ).c_str(),          category              );
  initBranch(tree, (name+"Track_algo"                 ).c_str(),          algo                  );
  initBranch(tree, (name+"Track_originalAlgo"         ).c_str(),          originalAlgo          );
  initBranch(tree, (name+"Track_TPAssociationQuality" ).c_str(),          TPAssociationQuality  );
  initBranch(tree, (name+"Track_idxMatchedTP"         ).c_str(),          idxMatchedTP          );
    


}


std::vector< std::shared_ptr<track> > trackData::getTracks(int nFirstTrack, int nLastTrack){
  
  std::vector< std::shared_ptr<track> > outputTracks;
  for(int i = nFirstTrack; i < nLastTrack; ++i){
    outputTracks.push_back(std::make_shared<track>(track(i, this)));
  }
  return outputTracks;
}



trackData::~trackData(){
  std::cout << "track::destroyed " << std::endl;
}

