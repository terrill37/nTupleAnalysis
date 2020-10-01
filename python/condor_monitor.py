import os
import subprocess
import time
import re
from commandLineHelpers import *

ROWS, COLUMNS = os.popen('stty size', 'r').read().split()
ROWS, COLUMNS = int(ROWS), int(COLUMNS)

class condor_job:
    def __init__(self, schedd, ID):
        self.schedd = schedd
        self.ID = ID
        self.done = False
        self.line = ''
        self.maxLines = 1
    
    def check(self):
        if self.done: return self.line
        args = ['condor_tail -maxbytes 1024 -name %s %s'%(self.schedd, self.ID)]
        res = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, executable='/bin/bash', universal_newlines=True)
        res.wait()

        if res.returncode:
            self.done = True
            #self.line = '%s %10s >> %s %d'%(self.schedd, self.ID, 'FINISHED: return code', res.returncode)
            self.line += ' | FINISHED'#: return code %d'%(res.returncode)
        else:
            tail = res.stdout.read()
            split = [line for line in tail.split('\n') if line]
            try:
                line = split[-1]
            except IndexError:
                line = ''
            self.line = '%s %10s >> %s'%(self.schedd, self.ID, line)
            time.sleep(0.1)

        nLines = 1 + int(len(self.line)/COLUMNS)
        self.maxLines = max(nLines, self.maxLines)
        self.line += ('\n'+' '*COLUMNS)*(self.maxLines-nLines)

        return self.line

    def watch(self, timeout=1):
        start = time.time()
        while time.time()-start < timeout:
            line = self.check()
            if self.done:
                break
            sys.stdout.write('\r'+line)
            sys.stdout.flush()
            #print split[-1]
            
        
def get_jobs():
    USER = getUSER()
    q = os.popen('condor_q').read()
    lines = q.split('\n')
    jobs = []
    for line in lines:
        print line
        split = line.split()
        if not split: continue
        if "-- Schedd:" in line:
            schedd = split[2]
        if "dagman" in line: continue
        if USER == split[1]:
            ID = split[0]
            #print schedd, ID
            jobs.append( condor_job(schedd, ID) )

    print '-'*20
    if not jobs:
        print "No Jobs"
    # else:
    #     print '-'*20
    return jobs

    

jobs = get_jobs()
while jobs:

    nDone=0
    nJobs=len(jobs)
    while nDone < nJobs:
        nDone = 0
        nLines = 0
        for job in jobs:
            if job.done: 
                nDone += 1
            line = job.check()
            nLines += job.maxLines
            print "\033[K"+line
        moveCursorUp(nLines)
    moveCursorDown(ROWS)

    print '-'*20
    time.sleep(10)
    jobs = get_jobs()

