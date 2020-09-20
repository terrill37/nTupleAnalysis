import time
import textwrap
from copy import copy
import os, re
import sys
import subprocess
import shlex
import optparse
import numpy as np
from threading import Thread
try:
    from queue import Queue, Empty
except ImportError:
    from Queue import Queue, Empty  # python 2.x

ON_POSIX = 'posix' in sys.builtin_module_names

def getCMSSW():
    return os.getenv('CMSSW_VERSION')

def getUSER():
    return os.getenv('USER')


def enqueue_output(out, queue, logFile):
    for line in iter(out.readline, b''):
        if logFile: logFile.write(line)
        queue.put(line)
        if queue.qsize()>1: queue.get_nowait()

        
    out.close()


def execute(command, doExecute=True): # use to run command like a normal line of bash
    print command
    if doExecute: os.system(command)


def watch(command, doExecute=True, stdout=None, doPrint=True, logFile=None): # use to run a command and keep track of the thread, ie to run something when it is done
    if doPrint: print command
    if doExecute:
        p = subprocess.Popen(shlex.split(command), stdout=stdout, universal_newlines=(True if stdout else False), bufsize=1, close_fds=ON_POSIX)
        if stdout:
            q = Queue()
            t = Thread(target=enqueue_output, args=(p.stdout, q, logFile))
            t.daemon = True
            t.start()
            return (command, p, q)
        return (command, p)


# \033[<L>;<C>H # Move the cursor to line L, column C
# \033[<N>A     # Move the cursor up N lines
# \033[<N>B     # Move the cursor down N lines
# \033[<N>C     # Move the cursor forward N columns
# \033[<N>D     # Move the cursor backward N columns
# \033[2J       # Clear the screen, move to (0,0)
# \033[K        # Erase to end of line
def placeCursor(L,C):
    print '\033['+str(L)+';'+str(C)+'H',
def moveCursorUp(N=''):
    print '\r\033['+str(N)+'A',
def moveCursorDown(N=''):
    print '\r\033['+str(N)+'B',


def babySit(commands, doExecute, maxAttempts=1, maxJobs=3, logFiles=None):
    attempts={}
    nCommands = len(commands)
    jobs=[]
    logs=[]
    outs=[]
    waiting=[]
    waitinglogs=[]
    done=[]
    for c in range(nCommands):
        command = commands[c]
        attempts[command] = 1
        done.append(0)
        print "# ",c
        if len(jobs)<maxJobs:
            logs.append(open(logFiles[c],"w") if (logFiles and doExecute) else None)
            jobs.append(watch(command, doExecute, stdout=subprocess.PIPE,logFile=logs[-1]))
                
            outs.append("LAUNCHING")
        else:
            print command
            waiting.append(command)
            waitinglogs.append(open(logFiles[c],"w") if (logFiles and doExecute) else None)
            outs.append("IN QUEUE")

    if not doExecute: return
    
    nDone = 0
    while nDone < nCommands:
        time.sleep(0.2)
        failure=False
        nJobs = len(jobs)
        nDone = sum(done)
        nToLaunch = 0
        for j in range(nJobs):
            code = jobs[j][1].poll()
            #if code == None: # job is still running
            #    done=False
            if code==0: # job finished
                if done[j]==0: nToLaunch += 1
                done[j] = 1
            elif code: # job crashed, try resubmitting
                moveCursorDown(1000)
                outs[j] = "CRASHED AT <"+outs[j]+">"
                crash = ["",
                         "# "+"-"*200,
                         "# "+jobs[j][0],
                         "# "+outs[j],
                         "# Exited with: "+str(code),
                         "# Attempt: "+str(attempts[jobs[j][0]]),
                         "# "+"-"*200,
                         ""]
                time.sleep(1)
                for line in crash: print line
                if attempts[jobs[j][0]] > maxAttempts: 
                    if done[j]==0: nToLaunch += 1
                    done[j] = 1
                    continue # don't resubmit, already tried maxAttempts times
                attempts[jobs[j][0]] += 1
                time.sleep(10)
                #done=False
                jobs[j] = watch(jobs[j][0], doExecute, stdout=subprocess.PIPE, logFile=logs[j])

        nWaiting = len(waiting)
        for w in range(nJobs, nJobs+min(nToLaunch, nWaiting)):
            jobs.append(watch(waiting.pop(0), doExecute, stdout=subprocess.PIPE, doPrint=False,logFile=waitinglogs.pop(0)))
            outs[w] = "LAUNCHING"

        nJobs = len(jobs)
        nLines = 1+nCommands#3
        print "\033[K"
        for c in range(nCommands):
            if c < nJobs:
                try:          
                    outs[c]=jobs[c][2].get_nowait().replace('\n','').replace('\r','')
                except Empty: 
                    outs[c]=outs[c]
            print "\033[K# "+str(c).rjust(2)+" >>",outs[c]

        moveCursorUp(nLines)
    moveCursorDown(1000)
            

def waitForJobs(jobs,failedJobs):
    for job in jobs:
        code = job[1].wait()
        if code: failedJobs.append(job)
    return failedJobs

def relaunchJobs(jobs, doExecute=True):
    print "# "+"-"*200
    print "# RELAUNCHING JOBS"
    newJobs = []
    for job in jobs: newJobs.append(watch(job[0], doExecute))
    return newJobs


def mkdir(directory, doExecute=True, xrd=False, url="root://cmseos.fnal.gov/"):
    if "root://" in directory or xrd:
        url, path = parseXRD(directory)
        cmd = "xrdfs "+url+" mkdir "+path
        execute(cmd, doExecute)
    else:
        if not os.path.isdir(directory):
            print "mkdir",directory
            if doExecute: os.mkdir(directory)
        else:
            print "#",directory,"already exists"
        

def rmdir(directory, doExecute=True):
    if not doExecute: 
        print "rm -r",directory
        return
    if "*" in directory:
        execute("rm -r "+directory)
        return
    if os.path.isdir(directory):
        execute("rm -r "+directory)
    elif os.path.exists(directory):
        execute("rm "+directory)
    else:
        print "#",directory,"does not exist"


def parseXRD(xrdFile):
    xrdFileSplit = xrdFile.split("//")
    url = "//".join(xrdFileSplit[0:2])+"/"
    path = "/".join(xrdFileSplit[2:])
    if path[0] != "/": path = "/"+path
    return url, path


class jdl:
    def __init__(self, CMSSW=None, EOSOUTDIR="None", TARBALL=None, cmd=None, fileName=None, logPath = "./", logName = "condor_$(Cluster)_$(Process)"):
        self.fileName = fileName if fileName else str(np.random.uniform())[2:]+".jdl"

        self.CMSSW = CMSSW
        self.EOSOUTDIR = EOSOUTDIR
        self.TARBALL = TARBALL

        self.universe = "vanilla"
        self.use_x509userproxy = "true"
        self.Executable = "nTupleAnalysis/scripts/condor.sh"
        #self.x509userproxy = "x509up_forCondor"
        self.should_transfer_files = "YES"
        self.when_to_transfer_output = "ON_EXIT"
        self.Output = logPath+logName+".stdout"
        self.Error = logPath+logName+".stderr"
        self.Log = logPath+logName+".log"
        self.Arguments = CMSSW+" "+EOSOUTDIR+" "+TARBALL+" "+cmd
        self.Queue = "1" # no equals sign in .jdl file

    def make(self):
        attributes=["universe",
                    "use_x509userproxy",
                    "Executable",
                    #"x509userproxy",
                    "should_transfer_files",
                    "when_to_transfer_output",
                    "Output",
                    "Error",
                    "Log",
                    "Arguments",
                ]
        f=open(self.fileName,'w')
        for attr in attributes:
            f.write(attr+" = "+str(getattr(self, attr))+"\n")

        f.write('+DesiredOS="SL7"\n')
        f.write("Queue "+str(self.Queue)+"\n")    
        f.close()

    
class dag:
    def __init__(self, parents=[], children=[], fileName=None):
        self.fileName = fileName if fileName else str(np.random.uniform())[2:]+".jdl"
        # self.iP = 0
        # self.iC = 0
        self.iJ = 0
        self.iG = 0
        self.iGMax = 0
        self.jobs = [[]]
        # self.parentJobs = [[]]
        # self.childJobs = [[]]
        self.generations = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' #['A', 'B', 'C', 'D', 'E', 'F']
        
        #self.lines=[]
        self.jobLines=[]
        self.genLines=[]

        self.written = False

    def setGeneration(self, generation):
        self.iG = generation
        while len(self.jobs) <= self.iG:
            self.jobs.append([])

    def addJob(self, JDL):
        self.iJ = len(self.jobs[self.iG])
        self.jobs[self.iG].append( "%s%d"%(self.generations[self.iG], self.iJ) )
        self.jobLines.append( "JOB %s %s\n"%(self.jobs[self.iG][self.iJ], JDL.fileName) )
        if self.iG > self.iGMax: self.iGMax = copy( self.iG ) # keeps track of the latest non-empty generation
    
    def addJobs(self, JDLs):
        for JDL in JDLs: self.addJobs(JDL)

    # def addParent(self, JDL):
    #     self.iP = len(self.parentJobs[self.iG])
    #     self.parentJobs[self.iG].append( "%s%d"%(self.generations[self.iG], self.iP) )
    #     self.jobLines.append( "JOB %s %s\n"%(self.parentJobs[self.iG][-1], JDL.fileName) )
        
    # def addParents(self, JDLs):
    #     for JDL in JDLs: self.addParent(JDL)

    # def addChild(self, JDL):
    #     self.iC = len(self.childJobs[self.iG])
    #     self.childJobs[self.iG].append( "%s%d"%(self.generations[self.iG+1], self.iC) )
    #     self.jobLines.append( "JOB %s %s\n"%(self.childJobs[self.iG][-1], JDL.fileName) )
        
    # def addChildren(self, JDLs):
    #     for JDL in JDLs: self.addChild(JDL)

    def addGeneration(self):
        #self.genLines.append( "PARENT "+" ".join(self.parentJobs[self.iG])+" CHILD "+" ".join(self.childJobs[self.iG])+"\n" )
        # try:
        #     self.parentJobs[self.iG+1] = copy( self.childJobs[self.iG] )
        #     self.childJobs[self.iG+1] = copy( self.childJobs[self.iG+1] )
        # except IndexError:
        #     self.parentJobs.append( copy( self.childJobs[self.iG] ) )
        #     self.childJobs.append([])
        self.iG += 1
        while len(self.jobs) <= self.iG:
            self.jobs.append([])

    def write(self):
        f = open(self.fileName, 'w')

        for line in self.jobLines:
            f.write(line)

        for iG in range(len(self.jobs)-1):
            if not self.jobs[iG]:   continue
            if not self.jobs[iG+1]: continue
            self.genLines.append( "PARENT "+" ".join(self.jobs[iG])+" CHILD "+" ".join(self.jobs[iG+1])+"\n" )

        for line in self.genLines:
            f.write(line)

        self.written = True
        
    def submit(self, doExecute=False):
        if not self.jobLines: return
        if not self.written: self.write()
        cmd = "condor_submit_dag -f "+self.fileName
        execute(cmd, doExecute)
        
        
