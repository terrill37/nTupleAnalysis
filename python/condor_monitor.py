import os
import time
import re
from commandLineHelpers import *

class condor_job:
    def __init__(self, schedd, ID):
        self.schedd = schedd
        self.ID = ID
        self.done = False
    
    def check(self):
        tail = os.popen('condor_tail -name %s %s'%(self.schedd, self.ID)).read()
        #split = re.split('\n\r',tail)
        line = tail.encode('string-escape')
        line = line.split(r'\n')[-1]
        line = line.split(r'\r')[-1]
        line = str(line)
        line = '%s %10s >> %s'%(self.schedd, self.ID, line)
        return line

    def watch(self, timeout=1):
        start = time.time()
        while time.time()-start < timeout:
            line = self.check()
            if not line:
                self.done = True
                break
            sys.stdout.write('\r'+line)
            sys.stdout.flush()
            #print split[-1]
            time.sleep(0.1)
            
        
def get_jobs():
    USER = getUSER()
    q = os.popen('condor_q').read()
    lines = q.split('\n')
    jobs = []
    for line in lines:
        split = line.split()
        if not split: continue
        if "-- Schedd:" in line:
            schedd = split[2]
        if USER == split[1]:
            ID = split[0]
            print schedd, ID
            jobs.append( condor_job(schedd, ID) )
    print '-'*20
    return jobs

    

jobs = get_jobs()

nDone=0
nJobs=len(jobs)
while nDone < jobs:
    nDone = 0
    print "\033[K"
    for job in jobs:
        if job.done: 
            nDone += 1
        print "\033[K"+job.check()
    moveCursorUp(nJobs+1)
moveCursorDown(1000)
    


