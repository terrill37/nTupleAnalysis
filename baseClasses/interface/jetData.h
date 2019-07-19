// -*- C++ -*-

#if !defined(jetData_H)
#define jetData_H
#include <TChain.h>
#include <TLorentzVector.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"
#include "nTupleAnalysis/baseClasses/interface/trackData.h"
#include "nTupleAnalysis/baseClasses/interface/btaggingData.h"

#include "CondTools/BTau/interface/BTagCalibrationReader.h"


namespace nTupleAnalysis {


  //forward declaration for use in jet constructor from tree
  class jetData;
  //jet object
  class jet {

  public:
    UChar_t cleanmask;

    float pt;
    float eta;
    float phi;
    float m;
    float e;
    TLorentzVector p;

    float bRegCorr;

    float deepB;
    float CSVv2;
    float deepFlavB;
    Int_t puId;
    Int_t jetId;

    int ntracks        ;
    int nseltracks     ;
    float SoftMu       ;
    float SoftEl       ;
    int nSM            ;
    int nSE            ;
    int looseID        ;
    int tightID        ;
    float DeepCSV      ;
    float DeepCSVb     ;
    float DeepCSVc     ;
    float DeepCSVl     ;
    float DeepCSVbb    ;

    // truth Info
    int flavour        ;
    int flavourCleaned ;
    int partonFlavour  ;
    int hadronFlavour  ;
    int nbHadrons      ;
    int ncHadrons      ;


    //
    //  Tracks in Jet
    //
    float nFirstTrack;
    float nLastTrack;
    std::vector<trackPtr> tracks;

    //
    // SVs in Jet
    //
    std::vector<svPtr> svs;

    //
    // trkTag in Jet
    //
    std::vector<trkTagVarPtr> trkTagVars;

    //
    // tag vars in Jet
    //
    tagVarPtr tagVars;


    //
    //  Matched Jets
    //
    float match_dR = -99;
    std::weak_ptr<jet>  matchedJet;

    float SF = 1.0; //btagging scale-factor

    jet();
    jet(UInt_t, jetData*); 
    jet(TLorentzVector&, float tag = -1); 
    void bRegression();
    ~jet(); 

    //void dump();
  };

  typedef std::shared_ptr<jet> jetPtr;


  //class for tree access
  class jetData {

  public:
    std::string m_name ="";
    bool m_isMC = false;
    std::string m_prefix ="";
    bool debug = false;
    static const unsigned int MAXJETS = 100;

    UInt_t nJets;
    //ULong64_t n;

    UChar_t cleanmask[MAXJETS];

    float pt [MAXJETS];
    float eta[MAXJETS];
    float phi[MAXJETS];
    float m  [MAXJETS];

    float bRegCorr[MAXJETS];

    float deepB[MAXJETS];
    float CSVv2[MAXJETS];
    float deepFlavB[MAXJETS];
    Int_t puId[MAXJETS];
    Int_t jetId[MAXJETS];

    int ntracks        [MAXJETS];
    int nseltracks     [MAXJETS];
    float SoftMu       [MAXJETS];
    float SoftEl       [MAXJETS];
    int nSM            [MAXJETS];
    int nSE            [MAXJETS];
    int looseID        [MAXJETS];
    int tightID        [MAXJETS];
    float DeepCSVb     [MAXJETS];
    float DeepCSVc     [MAXJETS];
    float DeepCSVl     [MAXJETS];
    float DeepCSVbb    [MAXJETS] = {0};

    // truth Info
    int flavour        [MAXJETS];
    int flavourCleaned [MAXJETS];
    int partonFlavour  [MAXJETS];
    int hadronFlavour  [MAXJETS];
    int nbHadrons      [MAXJETS];
    int ncHadrons      [MAXJETS];


    int nFirstTrack[MAXJETS];
    int nLastTrack[MAXJETS];
    trackData* trkData = nullptr;


    int nFirstSV[MAXJETS] = {0};
    int nLastSV[MAXJETS] = {0};

    int nFirstTrkTagVar[MAXJETS];
    int nLastTrkTagVar [MAXJETS];

    btaggingData* btagData = nullptr;

    jetData(std::string, TChain*, std::string jetDetailLevel = "Tracks.btagInputs", std::string prefix = "", bool isMC = false, std::string SFName = ""); 

    std::vector< std::shared_ptr<jet> > getJets(float ptMin = -1e6, float ptMax = 1e6, float etaMax = 1e6, bool clean = false, float tagMin = -1e6, std::string tagger = "CSVv2", bool antiTag = false);
    std::vector< std::shared_ptr<jet> > getJets(std::vector< std::shared_ptr<jet> > inputJets, 
						float ptMin = -1e6, float ptMax = 1e6, float etaMax = 1e6, bool clean = false, float tagMin = -1e6, std::string tagger = "CSVv2", bool antiTag = false);
    ~jetData(); 

    BTagCalibrationReader* m_btagCalibrationTool = nullptr;
    float getSF(float jetEta,  float jetPt,  float jetDeepCSV, int jetHadronFlavour);

    //void dump();
  };



}
#endif // jetData_H

