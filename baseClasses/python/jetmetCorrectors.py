from PhysicsTools.NanoAODTools.postprocessing.modules.jme.jetmetHelperRun2       import * 

#for MC
jetmetCorrector2016 = createJMECorrector(isMC=True,  dataYear=2016, jesUncert="All", redojec=True) 
jetmetCorrector2017 = createJMECorrector(isMC=True,  dataYear=2017, jesUncert="All", redojec=True) 
jetmetCorrector2018 = createJMECorrector(isMC=True,  dataYear=2018, jesUncert="All", redojec=True) 

#for Data
jetmetCorrector2018A = createJMECorrector(isMC=False, dataYear=2018, runPeriod="A", jesUncert="All", redojec=True) 
