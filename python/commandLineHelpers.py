import time
import textwrap
import os, re
import sys
import subprocess
import shlex
import optparse
from threading import Thread
try:
    from queue import Queue, Empty
except ImportError:
    from Queue import Queue, Empty  # python 2.x

ON_POSIX = 'posix' in sys.builtin_module_names

def enqueue_output(out, queue):
    for line in iter(out.readline, b''):
        queue.put(line)
        if queue.qsize()>1: queue.get_nowait()
    out.close()


def execute(command, execute=True): # use to run command like a normal line of bash
    print command
    if execute: os.system(command)


def watch(command, execute=True, stdout=None): # use to run a command and keep track of the thread, ie to run something when it is done
    print command
    if execute:
        p = subprocess.Popen(shlex.split(command), stdout=stdout, universal_newlines=(True if stdout else False), bufsize=1, close_fds=ON_POSIX)
        if stdout:
            q = Queue()
            t = Thread(target=enqueue_output, args=(p.stdout, q))
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


def babySit(commands, execute, maxAttempts=3):
    attempts={}
    nJobs = len(commands)
    jobs=[]
    outs=[]
    for command in commands:
        attempts[command] = 1
        jobs.append(watch(command, execute, stdout=subprocess.PIPE))
        outs.append("LAUNCHING")

    if not execute: return
    
    done=False
    while not done:
        done=True
        time.sleep(0.1)
        failure=False
        for j in range(nJobs):
            code = jobs[j][1].poll()
            if code == None: 
                done=False
            elif code:
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
                if attempts[jobs[j][0]] > maxAttempts: continue
                attempts[jobs[j][0]] += 1
                time.sleep(10)
                done=False
                jobs[j] = watch(jobs[j][0], execute, stdout=subprocess.PIPE)

        nLines = 3
        print "\033[K"
        for j in range(nJobs):
            nLines+=4
            lines=textwrap.wrap("Attempt "+str(attempts[jobs[j][0]])+": "+jobs[j][0], 200)
            nLines += len(lines)
            print "\033[K# "+"-"*200
            for line in lines: print "\033[K#", line
            
            try:          outs[j]=jobs[j][2].get_nowait().replace('\n','').replace('\r','')
            except Empty: outs[j]=outs[j]
            print "\033[K# "
            print "\033[K#    >>",outs[j]
            print "\033[K# "
        print "\033[K# "+"-"*200
        print "\033[K"
        moveCursorUp(nLines)
    moveCursorDown(1000)
            

def waitForJobs(jobs,failedJobs):
    for job in jobs:
        code = job[1].wait()
        if code: failedJobs.append(job)
    return failedJobs

def relaunchJobs(jobs, execute=True):
    print "# "+"-"*200
    print "# RELAUNCHING JOBS"
    newJobs = []
    for job in jobs: newJobs.append(watch(job[0], execute))
    return newJobs

def mkdir(directory, execute=True):
    if not os.path.isdir(directory):
        print "mkdir",directory
        if execute: os.mkdir(directory)
    else:
        print "#",directory,"already exists"

def rmdir(directory, execute=True):
    if not execute: 
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

