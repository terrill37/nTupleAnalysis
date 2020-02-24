// -*- C++ -*-

#if !defined(vertexData_H)
#define vertexData_H
#include <TChain.h>
#include "nTupleAnalysis/baseClasses/interface/initBranch.h"

namespace nTupleAnalysis {
  //forward declaration for use in vertex constructor from tree
  class vertexData;


  //vertex object
  class vertex {

  public:

    float   x      ;
    float   y      ;
    float   z      ;
    float   ex     ;
    float   ey     ;
    float   ez     ;
    float   chi2   ;
    float   ndf    ;
    int     isgood ;
    int     isfake ;

    vertex(UInt_t, vertexData*); 
    ~vertex(); 

    //void dump();
  };

  typedef std::shared_ptr<vertex> vertexPtr;

  //class for tree access
  class vertexData {

  public:
    std::string m_name;

    static const unsigned int MAXPVS = 1024;
    bool m_isMC;
    
    UInt_t nPV;
    
    // Following are redudant with data->z[0] and data->ez[0] 
    //float  PVz;
    //float  PVez;

    float   x      [MAXPVS];
    float   y      [MAXPVS];
    float   z      [MAXPVS];
    float   ex     [MAXPVS];
    float   ey     [MAXPVS];
    float   ez     [MAXPVS];
    float   chi2   [MAXPVS];
    float   ndf    [MAXPVS];
    int     isgood [MAXPVS];
    int     isfake [MAXPVS];


    
    vertexData(std::string, TTree*, bool readIn = true, bool isMC = false); 
    std::vector<std::shared_ptr<vertex>> getVerticies();
    ~vertexData(); 

    void writeVerticies(std::vector< std::shared_ptr<vertex> > outputVtx) ;
    void connectBranches(bool readIn, TTree* tree);


    //void dump();
  };

}
#endif // vertexData_H

