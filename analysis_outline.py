import sys
#https://github.com/patrickbryant/nTupleAnalysis
sys.path.insert(0, 'nTupleAnalysis/python/')  
#nTupleAnalysis/python/commandLineHelpers.py has helper functions to interact with the command line and classes for condor jobs  
from commandLineHelpers import * 

# Get the name of your CMSSW area and your USER name
CMSSW = getCMSSW()
USER  = getUSER()
# Specify the desired location of your local tarball which will be made/copied to EOS
NFSBASE    = "/uscms/home/"+USER+"/nobackup/"
NFSTARBALL = NFSBASE+CMSSW+".tgz"
# Specify your default EOS output directory and location of CMSSW tarball for condor jobs that need it
EOSOUTDIR  = "root://cmseos.fnal.gov//store/user/"+USER+"/condor/"
EOSTARBALL = EOSOUTDIR+CMSSW+".tgz"

import optparse
parser = optparse.OptionParser()
parser.add_option('-e', '--execute', action="store_true", default=False, help="Execute commands. Default is to just print them")
parser.add_option('-c', '--condor',  action="store_true", default=False, help="Run on condor")
parser.add_option(      '--step1',   action="store_true", default=False, help="Run step 1")
o, a = parser.parse_args()


# To run your CMSSW on condor, you will need a tarball of your CMSSW area stored on EOS which condor.sh can download, unpack and setup.
def makeTARBALL():
    # If the tarball already exists, do nothing
    # If you want to remake the tarball because you have new scripts or have recompiled code, just remove the existing local tarball
    if os.path.exists(NFSTARBALL): 
        print "TARBALL already exists, skip making it"
        return

    # Make the basic tarball command
    cmd  = 'tar -C '+NFSBASE+' -zcvf '+NFSTARBALL+' '+CMSSW
    # To make the tarball as small as possible, exclude unnecessary files
    cmd += ' --exclude="*.pdf" --exclude="*.jdl" --exclude="*.stdout" --exclude="*.stderr" --exclude="*.log"'
    cmd += ' --exclude=".git"'                                                                
    cmd += ' --exclude="tmp" --exclude-vcs --exclude-caches-all'
    # Execute the command to make the tarball
    execute(cmd, o.execute)

    # Check how big the tarball is (should be less than ~100MB)
    cmd  = 'ls '+NFSBASE+' -alh'
    execute(cmd, o.execute)

    # Make sure the EOS location for the tarball exists
    mkpath(EOSOUTDIR, o.execute)

    # Copy the tarball to EOS using -f to overwrite the existing tarball if it exists
    cmd = "xrdcp -f "+NFSTARBALL+" "+EOSTARBALL
    execute(cmd, o.execute)


# To manage a chain of condor jobs we will use the dag (directed acyclic graph) class from commandLineHelpers
DAG = dag(fileName="analysis.dag")

# Often the first step of an analysis is to make skims of the signal sample AODs
# Here we define an example function which makes and runs/submits the commands for this step
def analysisStep1():
    signals = ['yourAnalysis/fileLists/signalA.txt',
               'yourAnalysis/fileLists/signalB.txt']
    cmds = []
    for signal in signals:
        cmd = "yourAnalysis/scripts/yourConfigScript.py -i "+signal
        if o.condor:
            JDL = jdl(TARBALL=EOSTARBALL, cmd=cmd)
            DAG.addJob(JDL)
        else:
            cmds.append(cmd)

    if cmds: # run commands locally, up to 3 at a time
        babySit(cmds, o.execute, maxJobs=3)
    else:
        DAG.addGeneration()

    # An example post-processing step you might want to do is add together the output histogram files
    cmd = "hadd -f "+EOSOUTDIR+"signal/hists.root "+EOSOUTDIR+"signalA/hists.root "+EOSOUTDIR+"signalB/hists.root"
    if o.condor:
        JDL = jdl(TARBALL=EOSTARBALL, cmd=cmd)
        DAG.addJob(JDL)
    else:
        execute(cmd, o.execute)

    # At the end of the analysis step, add a generation to the DAG so that the next step starts when this one completes
    if o.condor: 
        DAG.addGeneration()

# Define additional analysis steps like running background samples, fitting parameters, plotting, moving around files etc.
# def analysisStep2():
#     ...    


#
# Run your analysis steps
#
if o.condor:
    makeTARBALL()

if o.step1:
    analysisStep1()

# if o.step2:
#     analysisStep2()

if o.condor:
    DAG.submit(o.execute)
