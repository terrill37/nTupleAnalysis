
#include "TChain.h"

#include "nTupleAnalysis/baseClasses/interface/jetData.h"
#include "DataFormats/BTauReco/interface/ParticleMasses.h"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"

using namespace nTupleAnalysis;



//jet object
jet::jet(){}
jet::jet(UInt_t i, jetData* data){

  cleanmask = data->cleanmask[i];

  pt  = data->pt [i];
  eta = data->eta[i];
  phi = data->phi[i];
  m   = data->m  [i];
  p = TLorentzVector();
  p.SetPtEtaPhiM(pt, eta, phi, m);
  e = p.E();

  bRegCorr = data->bRegCorr[i];
  appliedBRegression = false;

  deepB     = data->deepB[i];
  CSVv2     = data->CSVv2[i];
  deepFlavB = data->deepFlavB[i];

  // Normalizize the underflow
  if(CSVv2 < 0) 
    CSVv2 = -0.1; 
  
  puId = data->puId[i];
  jetId = data->jetId[i];

  deepFlavB = data->deepFlavB[i];

  ntracks        = data->ntracks        [i];
  nseltracks     = data->nseltracks     [i];

  //CombIVF_N      = data->CombIVF_N      [i];
  SoftMu         = data->SoftMu         [i];
  if(SoftMu < 0) 
    SoftMu = -0.1; 

  SoftEl         = data->SoftEl         [i];
  if(SoftEl < 0) 
    SoftEl = -0.1; 


  nSM            = data->nSM            [i];
  nSE            = data->nSE            [i];
  looseID        = data->looseID        [i];
  tightID        = data->tightID        [i];
  DeepCSVb       = data->DeepCSVb       [i];
  DeepCSVc       = data->DeepCSVc       [i];
  DeepCSVl       = data->DeepCSVl       [i];
  DeepCSVbb      = data->DeepCSVbb      [i];

  DeepCSV = DeepCSVb+DeepCSVbb;
  if(DeepCSV < 0)
    DeepCSV = -0.1;

  if(DeepCSVb < 0)
    DeepCSVb = -0.1;

  if(DeepCSVbb < 0)
    DeepCSVbb = -0.1;


  flavour        = data->flavour        [i];
  flavourCleaned = data->flavourCleaned [i];
  partonFlavour  = data->partonFlavour  [i];
  hadronFlavour  = data->hadronFlavour  [i];
  nbHadrons      = data->nbHadrons      [i];
  ncHadrons      = data->ncHadrons      [i];

  if(data->trkData){
    nFirstTrack = data->nFirstTrack[i];
    nLastTrack = data->nLastTrack[i];

    std::vector<trackPtr> tracksTmp = data->trkData->getTracks(nFirstTrack,nLastTrack);
    for(const trackPtr& track: tracksTmp){
      track->dR = track->p.DeltaR(p);
      track->ptRel = track->p.Vect().Perp(p.Vect().Unit());
      track->pPar  = track->p.Vect().Dot(p.Vect().Unit());
      if(track->dR < 0.3)
	tracks.push_back(track);
    }
  }

  //
  //  Set the isV0 bits
  //
  unsigned int nTracks = tracks.size();
  for(unsigned int iTrk1 = 0; iTrk1 < nTracks; ++iTrk1){
    for(unsigned int iTrk2 = iTrk1; iTrk2 < nTracks; ++iTrk2){
      if(iTrk1 == iTrk2 ) continue;

      if (tracks[iTrk1]->charge * tracks[iTrk2]->charge > 0)
	continue;


      float invariantMass = (tracks[iTrk1]->p + tracks[iTrk2]->p).M();
      if (std::abs(invariantMass - reco::ParticleMasses::k0) < 0.05){
	tracks[iTrk1]->isfromV0 = true;
	tracks[iTrk2]->isfromV0 = true;
      }

    }
  }

  if(data->debug){
    std::cout << "i is " << i << std::endl;;

    std::cout << "nFirst is ";
    for(unsigned int iT =0; iT < 100; ++iT){
      std::cout << data->nFirstSV[iT] << " ";
    }
    std::cout << std::endl;

    std::cout << "nLast is ";
    for(unsigned int iT =0; iT < 100; ++iT){
      std::cout << data->nLastSV[iT] << " ";
    }
    std::cout << std::endl;
  }

  if(data->btagData){
    if(data->btagData->haveSVs){
      if(data->debug)  std::cout << data->m_name << " Getting SVs " << data->nFirstSV[i] << " " << data->nLastSV[i] << std::endl;
      svs = data->btagData->getSecondaryVertices(data->nFirstSV[i],data->nLastSV[i], data->debug);
    }
    
    if(data->btagData->haveTrkTagVars){
      trkTagVars = data->btagData->getTrkTagVars(data->nFirstTrkTagVar[i],data->nLastTrkTagVar[i]);
    }
    
    if(data->btagData->haveTagVars){
      tagVars = data->btagData->getTagVars(i);
    }
  }

  //
  // Hack to fix trkTagVas phi which is not filled in cmssw
  //
  for(const trkTagVarPtr& trkTagVar: trkTagVars){
    //std::cout << "Matching " << trkTagVar->trackEta << " " << trkTagVar->pt << std::endl;
    for(const trackPtr& track: tracks){
      //std::cout << "\t " << track->eta << " " << track->pt << std::endl;
      if(fabs(track->eta - trkTagVar->trackEta) < 0.001 && fabs(track->pt - trkTagVar->pt) < 0.001){
  	trkTagVar->trackPhi = track->phi;
  	trkTagVar->p.SetPtEtaPhiM(trkTagVar->pt, trkTagVar->trackEta, trkTagVar->trackPhi, trkTagVar->m);
  	trkTagVar->e = p.E();
  	break;
      }
      
    }
  }


  for(const trkTagVarPtr& trkTagVar: trkTagVars){
    //std::cout << "Matching " << trkTagVar->trackEta << " " << trkTagVar->pt << std::endl;
    for(const trackPtr& track: tracks){
      
      if(track->p.DeltaR(trkTagVar->p) < 0.01){
	trkTagVar->hasTrackMatch = true;
	trkTagVar->matchIsFromV0 = track->isfromV0;
	track->hasTrkTagVarMatch = true;
      }
    }
  }



  if(data->m_isMC && data->m_btagCalibrationTool){
    SF = data->getSF(eta, pt, DeepCSV, hadronFlavour);
  }else{
    SF = 1.0;
  }

}


jet::jet(TLorentzVector& vec, float tag){

  p = TLorentzVector(vec);
  pt  = p.Pt();
  eta = p.Eta();
  phi = p.Phi();
  m   = p.M();
  e   = p.E();

  bRegCorr = 1.0;
  appliedBRegression = false;

  deepB = tag;
  CSVv2 = tag;
  deepFlavB = tag;
}

void jet::bRegression(){
  scaleFourVector(bRegCorr);
  appliedBRegression = true;
}


void jet::scaleFourVector(float scale){
  p  *= scale;
  pt  = p.Pt();
  eta = p.Eta();
  phi = p.Phi();
  m   = p.M();
  e   = p.E();
}



void jet::RotateZ(float dPhi){
  p.RotateZ(dPhi);
  phi = p.Phi();
}



jet::~jet(){
}


//access tree
jetData::jetData(std::string name, TChain* tree, bool isMC, std::string jetDetailLevel, std::string prefix, std::string SFName){

  m_name = name;
  m_prefix = prefix;
  m_isMC = isMC;

  initBranch(tree, (prefix+"n"+name).c_str(), nJets );

  initBranch(tree, (prefix+name+"_cleanmask").c_str(), cleanmask );

  initBranch(tree, (prefix+name+"_pt"  ).c_str(), pt  );  
  initBranch(tree, (prefix+name+"_eta" ).c_str(), eta );  
  initBranch(tree, (prefix+name+"_phi" ).c_str(), phi );  
  initBranch(tree, (prefix+name+"_mass").c_str(), m   );  

  initBranch(tree, (prefix+name+"_bRegCorr").c_str(), bRegCorr );  

  initBranch(tree, (prefix+name+"_btagDeepB"    ).c_str(), deepB     );

  if(initBranch(tree, (prefix+name+"_btagCSVV2"    ).c_str(), CSVv2     ) == -1){
    std::cout << "\tUsing " << (prefix+name+"_CombIVF"        ) << " for CSVc2 " << std::endl;
    initBranch(tree, (prefix+name+"_CombIVF"        ).c_str(),         CSVv2        ); 
  }
  
  initBranch(tree, (prefix+name+"_btagDeepFlavB").c_str(), deepFlavB );

  initBranch(tree, (prefix+name+"_puId" ).c_str(), puId  );
  initBranch(tree, (prefix+name+"_jetId").c_str(), jetId );
  
  initBranch(tree, (prefix+name+"_ntracks"        ).c_str(),         ntracks        );
  initBranch(tree, (prefix+name+"_nseltracks"     ).c_str(),         nseltracks     );
  initBranch(tree, (prefix+name+"_flavour"        ).c_str(),         flavour        ); 
  initBranch(tree, (prefix+name+"_flavourCleaned" ).c_str(),         flavourCleaned );
  initBranch(tree, (prefix+name+"_partonFlavour"  ).c_str(),         partonFlavour  );
  initBranch(tree, (prefix+name+"_hadronFlavour"  ).c_str(),         hadronFlavour  );
  initBranch(tree, (prefix+name+"_nbHadrons"      ).c_str(),         nbHadrons      );
  initBranch(tree, (prefix+name+"_ncHadrons"      ).c_str(),         ncHadrons      );

  initBranch(tree, (prefix+name+"_SoftMu"         ).c_str(),         SoftMu         ); 
  initBranch(tree, (prefix+name+"_SoftEl"         ).c_str(),         SoftEl         ); 
  initBranch(tree, (prefix+name+"_nSM"            ).c_str(),         nSM            ); 
  initBranch(tree, (prefix+name+"_nSE"            ).c_str(),         nSE            ); 
  initBranch(tree, (prefix+name+"_looseID"        ).c_str(),         looseID        ); 
  initBranch(tree, (prefix+name+"_tightID"        ).c_str(),         tightID        ); 
  initBranch(tree, (prefix+name+"_DeepCSVb"       ).c_str(),         DeepCSVb       );
  initBranch(tree, (prefix+name+"_DeepCSVc"       ).c_str(),         DeepCSVc       );
  initBranch(tree, (prefix+name+"_DeepCSVl"       ).c_str(),         DeepCSVl       );
  initBranch(tree, (prefix+name+"_DeepCSVbb"      ).c_str(),         DeepCSVbb      );


  //
  //  only load the track if the variables are availible
  //
  if(jetDetailLevel.find("Tracks") != std::string::npos){
    std::cout << "jetData::" << m_name << " loading Tracks" << std::endl;
    int nFirstTrackCode = initBranch(tree, (prefix+name+"_nFirstTrack").c_str(),  nFirstTrack);
    int nLastTrackCode  = initBranch(tree, (prefix+name+"_nLastTrack" ).c_str(),  nLastTrack );
    if(nFirstTrackCode != -1 && nLastTrackCode != -1){
      trkData = new trackData(prefix, tree);
    }
  }

  //
  //  Load the btagging data
  //
  if(jetDetailLevel.find("btagInputs") != std::string::npos){
    std::cout << "jetData::" << m_name << " loading btagInputs" << std::endl;
    btagData = new btaggingData();
    btagData->initTagVar(prefix, tree);  
  
    int nFirstSVCode = initBranch(tree, (prefix+name+"_nFirstSV").c_str(),  nFirstSV);
    int nLastSVCode  = initBranch(tree, (prefix+name+"_nLastSV" ).c_str(),  nLastSV );
    if(nFirstSVCode != -1 && nLastSVCode != -1){
      btagData->initSecondaryVerticies(prefix, tree);
    }

    int nFirstTrkTagVarCode = initBranch(tree, (prefix+name+"_nFirstTrkTagVar").c_str(),  nFirstTrkTagVar);
    int nLastTrkTagVarCode  = initBranch(tree, (prefix+name+"_nLastTrkTagVar" ).c_str(),  nLastTrkTagVar );
    if(nFirstTrkTagVarCode != -1 && nLastTrkTagVarCode != -1){
      btagData->initTrkTagVar(prefix, tree);
    }
  }

  //
  // Load the BTagging SFs
  //
  if(m_isMC){

    if(SFName != "2017" && SFName != "deepcsv2018" && SFName != "deepjet2018"){
      std::cout << "jetData::Warning no scale factors for " << m_name << std::endl;
    }else{

      std::string sfFileName =  "nTupleAnalysis/baseClasses/data/BTagSF2017/DeepCSV_94XSF_V4_B_F.csv";
      if(SFName == "deepcsv2018")
	sfFileName = "nTupleAnalysis/baseClasses/data/BTagSF2018/DeepCSV_102XSF_V1.csv";
      if(SFName == "deepjet2018")
	sfFileName = "nTupleAnalysis/baseClasses/data/BTagSF2018/DeepJet_102XSF_V1.csv";
      
      std::cout << "jetData::Loading SF from " << sfFileName << " For jets " << m_name << std::endl;
      BTagCalibration calib = BTagCalibration("deepcsv", sfFileName);
      
      m_btagCalibrationTool = new BTagCalibrationReader(BTagEntry::OP_RESHAPING,              // 0 is for loose op, 1: medium, 2: tight, 3: discr. reshaping
							"central"      // central systematic type
							);

      m_btagCalibrationTool->load(calib, 
				  BTagEntry::FLAV_B,   // 0 is for b flavour, 1: FLAV_C, 2: FLAV_UDSG
				  "iterativefit"      // measurement type
				  );

      m_btagCalibrationTool->load(calib, 
				  BTagEntry::FLAV_C,   // 0 is for b flavour, 1: FLAV_C, 2: FLAV_UDSG
				  "iterativefit"      // measurement type
				  );


      m_btagCalibrationTool->load(calib, 
				  BTagEntry::FLAV_UDSG,   // 0 is for b flavour, 1: FLAV_C, 2: FLAV_UDSG
				  "iterativefit"      // measurement type
				  );

    }

  }

}


std::vector< std::shared_ptr<jet> > jetData::getJets(float ptMin, float ptMax, float etaMax, bool clean, float tagMin, std::string tagger, bool antiTag){
  
  std::vector< std::shared_ptr<jet> > outputJets;
  float *tag = CSVv2;
  if(tagger == "deepB")     tag = deepB;
  if(tagger == "deepFlavB") tag = deepFlavB;
  if(debug) std::cout << "We have " << nJets << " jets"<< std::endl;
  for(Int_t i = 0; i < int(nJets); ++i){
    if(i > int(MAXJETS-1)) {
      std::cout  << m_name << "::Warning too many jets! " << nJets << " jets. Skipping. "<< std::endl;
      break;
    }
      
    if(clean && cleanmask[i] == 0) continue;
    if(          pt[i]  <  ptMin ) continue;
    if(          pt[i]  >= ptMax ) continue;
    if(    fabs(eta[i]) > etaMax ) continue;
    if(antiTag^(tag[i]  < tagMin)) continue; // antiTag XOR (jet fails tagMin). This way antiTag inverts the tag criteria to select untagged jets
    outputJets.push_back(std::make_shared<jet>(jet(i, this)));
  }

  return outputJets;
}

std::vector< std::shared_ptr<jet> > jetData::getJets(std::vector< std::shared_ptr<jet> > inputJets, float ptMin, float ptMax, float etaMax, bool clean, float tagMin, std::string tagger, bool antiTag){
  
  std::vector< std::shared_ptr<jet> > outputJets;

  for(auto &jet: inputJets){
    if(clean && jet->cleanmask == 0) continue;
    if(         jet->pt   <  ptMin ) continue;
    if(         jet->pt   >= ptMax ) continue;
    if(    fabs(jet->eta) > etaMax ) continue;

    if(     tagger == "deepFlavB" && antiTag^(jet->deepFlavB < tagMin)) continue;
    else if(tagger == "deepB"     && antiTag^(jet->deepB     < tagMin)) continue;
    else if(tagger == "CSVv2"     && antiTag^(jet->CSVv2     < tagMin)) continue;
    outputJets.push_back(jet);
  }

  return outputJets;
}


jetData::~jetData(){ 
  std::cout << "jetData::destroyed " << std::endl;
}


float jetData::getSF(float jetEta,  float jetPt,  float jetTagScore, int jetHadronFlavour){ 
  if(!m_btagCalibrationTool) return 1;

  if(fabs(jetHadronFlavour) == 5){
    return m_btagCalibrationTool->eval_auto_bounds("central", BTagEntry::FLAV_B, fabs(jetEta), jetPt, jetTagScore);
  }else if(fabs(jetHadronFlavour) == 4){
    return m_btagCalibrationTool->eval_auto_bounds("central", BTagEntry::FLAV_C, fabs(jetEta), jetPt, jetTagScore);
  }

  return m_btagCalibrationTool->eval_auto_bounds("central", BTagEntry::FLAV_UDSG, fabs(jetEta), jetPt, jetTagScore);
}
