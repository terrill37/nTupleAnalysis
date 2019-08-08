
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

  isTag          = data->isTag      [i];
  isSel          = data->isSel      [i];

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

//
//access tree
//
jetData::jetData(std::string name, TTree* tree, bool readIn, std::string jetDetailLevel, std::string prefix, bool isMC, std::string SFName){

  m_name = name;
  m_prefix = prefix;
  m_isMC = isMC;
  m_jetDetailLevel = jetDetailLevel;

  connectBranches(readIn, tree);

  //
  // Load the BTagging SFs
  //
  if(readIn && m_isMC){

    if(SFName != "2017" && SFName != "2018"){
      std::cout << "jetData::Warning no scale factors for " << m_name << std::endl;
    }else{

      std::string sfFileName =  "nTupleAnalysis/baseClasses/data/BTagSF2017/DeepCSV_94XSF_V4_B_F.csv";
      if(SFName == "2018")
	std::string sfFileName = "nTupleAnalysis/baseClasses/data/BTagSF2018/DeepCSV_102XSF_V1.csv";
      
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


float jetData::getSF(float jetEta,  float jetPt,  float jetDeepCSV, int jetHadronFlavour){ 
  if(fabs(jetHadronFlavour) == 5){
    return m_btagCalibrationTool->eval_auto_bounds("central", BTagEntry::FLAV_B, fabs(jetEta), jetPt, jetDeepCSV);
  }else if(fabs(jetHadronFlavour) == 4){
    return m_btagCalibrationTool->eval_auto_bounds("central", BTagEntry::FLAV_C, fabs(jetEta), jetPt, jetDeepCSV);
  }

  return m_btagCalibrationTool->eval_auto_bounds("central", BTagEntry::FLAV_UDSG, fabs(jetEta), jetPt, jetDeepCSV);
}


void jetData::writeJets(std::vector< std::shared_ptr<jet> > outputJets){
  
  int nOutputJets = outputJets.size();
  this->nJets = outputJets.size();

  for(Int_t i = 0; i < int(this->nJets); ++i){
    if(i > int(MAXJETS-1)) {
      std::cout  << m_name << "::Warning too many jets! " << nOutputJets << " jets. Skipping. "<< std::endl;
      break;
    }

    const jetPtr& thisJet = outputJets.at(i);
    this->cleanmask[i] = thisJet->cleanmask;

    this->pt [i] = thisJet->pt  ;
    this->eta[i] = thisJet->eta ;
    this->phi[i] = thisJet->phi ;
    this->m  [i] = thisJet->m   ;


    this->bRegCorr[i] =  thisJet-> bRegCorr;

    this->deepB[i]	      = thisJet->deepB   ; 
    this->CSVv2[i]	      = thisJet->CSVv2   ; 
    this->deepFlavB[i]   = thisJet->deepFlavB; 
  
    this->puId[i] = thisJet->puId;
    this->jetId[i] = thisJet->jetId;
    
    this->deepFlavB[i] = thisJet->deepFlavB ;
    
    this->ntracks        [i] = thisJet->ntracks        ;
    this->nseltracks     [i] = thisJet->nseltracks     ; 
    
      //CombIVF_N      = this->CombIVF_N      [i];
    this->SoftMu         [i] =     thisJet->SoftMu          ;
    this->SoftEl         [i] =     thisJet->SoftEl          ;
    
    this->nSM            [i] =      thisJet->nSM            ;
    this->nSE            [i] =      thisJet->nSE            ;
    this->looseID        [i] =      thisJet->looseID        ;
    this->tightID        [i] =      thisJet->tightID        ;
    this->DeepCSVb       [i] =      thisJet->DeepCSVb       ;
    this->DeepCSVc       [i] =      thisJet->DeepCSVc       ;
    this->DeepCSVl       [i] =      thisJet->DeepCSVl       ;
    this->DeepCSVbb      [i] =      thisJet->DeepCSVbb      ;
    
    this->flavour        [i] =     thisJet->flavour        ;
    this->flavourCleaned [i] =     thisJet->flavourCleaned ;
    this->partonFlavour  [i] =     thisJet->partonFlavour  ;
    this->hadronFlavour  [i] =     thisJet->hadronFlavour  ;
    this->nbHadrons      [i] =     thisJet->nbHadrons      ;
    this->ncHadrons      [i] =     thisJet->ncHadrons      ;

    this->isTag      [i] =   thisJet->isTag          ;
    this->isSel      [i] =   thisJet->isSel          ;

  }

  return ;
}


void jetData::connectBranches(bool readIn, TTree* tree){
  
  std::string jetName =  m_prefix+m_name;
  std::string NjetName = m_prefix+"n"+m_name;


  connectBranch(readIn, tree, NjetName, nJets, "i");

  connectBranchArr(readIn, tree, jetName+"_pt",   pt,  NjetName,  "F");
  connectBranchArr(readIn, tree, jetName+"_eta",  eta, NjetName,  "F");
  connectBranchArr(readIn, tree, jetName+"_phi",  phi, NjetName,  "F");
  connectBranchArr(readIn, tree, jetName+"_mass", m,   NjetName,  "F");  

  connectBranchArr(readIn, tree, jetName+"_cleanmask", m,   NjetName,  "B");  

  connectBranchArr(readIn, tree, jetName+"_bRegCorr", bRegCorr,   NjetName,  "F");  
  connectBranchArr(readIn, tree, jetName+"_btagDeepB", deepB,   NjetName,  "F");  

  int CSVRes = connectBranchArr(readIn, tree, jetName+"_btagCSVV2", CSVv2,   NjetName,  "F");  
  if(readIn && CSVRes == -1){
    std::cout << "\tUsing " << (m_prefix+m_name+"_CombIVF"        ) << " for CSVc2 " << std::endl;
    connectBranchArr(readIn, tree, jetName+"_CombIVF", CSVv2,   NjetName,  "F");  
  }

  connectBranchArr(readIn, tree, jetName+"_btagDeepFlavB", deepFlavB,   NjetName,  "F");  

  connectBranchArr(readIn, tree, jetName+"_puId",  puId,   NjetName,  "i");  
  connectBranchArr(readIn, tree, jetName+"_jetId", puId,   NjetName,  "i");  

  if(m_isMC){
    connectBranchArr(readIn, tree, jetName+"_flavour", flavour,   NjetName,  "i");  
    connectBranchArr(readIn, tree, jetName+"_flavourCleaned", flavourCleaned,   NjetName,  "i");  
    connectBranchArr(readIn, tree, jetName+"_partonFlavour", partonFlavour,   NjetName,  "i");  
    connectBranchArr(readIn, tree, jetName+"_hadronFlavour", hadronFlavour,   NjetName,  "i");  
    connectBranchArr(readIn, tree, jetName+"_nbHadrons", nbHadrons,   NjetName,  "i");  
    connectBranchArr(readIn, tree, jetName+"_ncHadrons", ncHadrons,   NjetName,  "i");  
  }

  connectBranchArr(readIn, tree, jetName+"_looseID", looseID,   NjetName,  "i");  
  connectBranchArr(readIn, tree, jetName+"_tightID", tightID,   NjetName,  "i");  

  connectBranchArr(readIn, tree, jetName+"_DeepCSVb", DeepCSVb,   NjetName,  "F");  
  connectBranchArr(readIn, tree, jetName+"_DeepCSVc", DeepCSVc,   NjetName,  "F");  
  connectBranchArr(readIn, tree, jetName+"_DeepCSVl", DeepCSVl,   NjetName,  "F");  
  connectBranchArr(readIn, tree, jetName+"_DeepCSVbb", DeepCSVbb,   NjetName,  "F");  

  connectBranchArr(readIn, tree, jetName+"_isTag", isTag,   NjetName,  "i");  
  connectBranchArr(readIn, tree, jetName+"_isSel", isSel,   NjetName,  "i");  

  //
  //  Following only supported for reading In
  //
  if(readIn){

    //
    //  only load the track if the variables are availible
    //
    if(m_jetDetailLevel.find("Tracks") != std::string::npos){
      std::cout << "jetData::" << m_name << " loading Tracks" << std::endl;
      inputBranch(tree, (m_prefix+m_name+"_ntracks"        ).c_str(),         ntracks        );
      inputBranch(tree, (m_prefix+m_name+"_nseltracks"     ).c_str(),         nseltracks     );
      int nFirstTrackCode = inputBranch(tree, (m_prefix+m_name+"_nFirstTrack").c_str(),  nFirstTrack);
      int nLastTrackCode  = inputBranch(tree, (m_prefix+m_name+"_nLastTrack" ).c_str(),  nLastTrack );
      if(nFirstTrackCode != -1 && nLastTrackCode != -1){
	trkData = new trackData(m_prefix, tree);
      }
    }

    //
    //  Load the btagging data
    //
    if(m_jetDetailLevel.find("btagInputs") != std::string::npos){
      std::cout << "jetData::" << m_name << " loading btagInputs" << std::endl;
      btagData = new btaggingData();
      btagData->initTagVar(m_prefix, tree);  

      inputBranch(tree, (m_prefix+m_name+"_SoftMu"         ).c_str(),         SoftMu         ); 
      inputBranch(tree, (m_prefix+m_name+"_SoftEl"         ).c_str(),         SoftEl         ); 
      inputBranch(tree, (m_prefix+m_name+"_nSM"            ).c_str(),         nSM            ); 
      inputBranch(tree, (m_prefix+m_name+"_nSE"            ).c_str(),         nSE            ); 
  
      int nFirstSVCode = inputBranch(tree, (m_prefix+m_name+"_nFirstSV").c_str(),  nFirstSV);
      int nLastSVCode  = inputBranch(tree, (m_prefix+m_name+"_nLastSV" ).c_str(),  nLastSV );
      if(nFirstSVCode != -1 && nLastSVCode != -1){
	btagData->initSecondaryVerticies(m_prefix, tree);
      }

      int nFirstTrkTagVarCode = inputBranch(tree, (m_prefix+m_name+"_nFirstTrkTagVar").c_str(),  nFirstTrkTagVar);
      int nLastTrkTagVarCode  = inputBranch(tree, (m_prefix+m_name+"_nLastTrkTagVar" ).c_str(),  nLastTrkTagVar );
      if(nFirstTrkTagVarCode != -1 && nLastTrkTagVarCode != -1){
	btagData->initTrkTagVar(m_prefix, tree);
      }
    }
  }


  return ;
}
