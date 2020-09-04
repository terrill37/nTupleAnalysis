#!/bin/bash
echo "Starting job on " `date` #Date/time of start of job
echo "Running on: `uname -a`" #Condor job is running on this node
echo "System software: `cat /etc/redhat-release`" #Operating System on that node
CMSSW=$1
EOSOUTDIR=$2
TARBALL=$3
CMD=(${@})
unset CMD[0]
unset CMD[1]
unset CMD[2]

# bring in the tarball you created before with caches and large files excluded:
echo "xrdcp -s ${TARBALL} ."
xrdcp -s ${TARBALL} .
echo "source /cvmfs/cms.cern.ch/cmsset_default.sh"
source /cvmfs/cms.cern.ch/cmsset_default.sh 
echo "tar -xf ${CMSSW}.tgz"
tar -xf ${CMSSW}.tgz
rm ${CMSSW}.tgz
echo "cd ${CMSSW}/src/"
cd ${CMSSW}/src/
scramv1 b ProjectRename # this handles linking the already compiled code - do NOT recompile
eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers
echo $CMSSW_BASE "is the CMSSW we have on the local worker node"
#cd ${_CONDOR_SCRATCH_DIR}
pwd
echo "${CMD[*]}"
eval "${CMD[*]}"


### Now that the cmsRun is over, there is one or more root files created
#pwd
#echo "cd $FILELIST"
#cd $FILELIST
pwd
echo "List all root files:"
ls *.root
echo "List all files:"
ls -alh
echo "*******************************************"
echo "xrdcp output for condor to:"
echo $EOSOUTDIR
for FILE in *.root
do
  echo "xrdcp -f ${FILE} ${EOSOUTDIR}/${FILE}"
  xrdcp -f ${FILE} ${EOSOUTDIR}/${FILE} 2>&1
  XRDEXIT=$?
  if [[ $XRDEXIT -ne 0 ]]; then
    rm *.root
    echo "exit code $XRDEXIT, failure in xrdcp"
    exit $XRDEXIT
  fi
  rm ${FILE}
done
