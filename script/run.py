import os
import re
import sys
import time
import threading
import shutil

def runExe():
    global flag
    global ver
    global dump
    global verpath
    global varExe
    print(flag, ver, dump, verpath)

#    workpath = os.getcwd()
    os.chdir(verpath)
    workpathLog = verpath + "/" + verLog
    if os.path.exists(workpathLog):
        os.remove(workpathLog)
    fname = os.popen('ls -F | grep "*"').readlines();

    for var in fname:
        varExe = var[:-2]
        print("----------------" + varExe + "-----------------")
        varExeFile = "mk-" + varExe
        exepath = verpath + "/" + varExeFile
        os.mkdir(varExeFile)
        shutil.move(varExe, exepath)
        os.chdir(exepath)
        print(os.getcwd())    
        if(dump == 'on'):
            os.system("python ../../dump.py " + varExe + " " + dump + " >> ../" + verLog + " 2>&1 ") 
        else:
            os.environ['DUMP_ALL']='0'
            os.system("./" + varExe + " " + " >> ../" + verLog + " 2>&1 ")

        os.chdir(verpath)
        if flag == False:
            print("dump has abnormal end!!!")
            break

    print("[Debug] ====== Run over!!")
    flag = False


def checkOut():
    global flag
    global verpath
    global verLof
    time.sleep(1)
    keyword = "error"
    count = 0

    while(flag):
        time.sleep(5)
        f = open(verpath + "/" + verLog, "rb")
        lines = f.readlines()

        if len(lines) == 0:
            flag == False
            print("=======================dump.log is NULL")
            f.close()
        tempCount = -1
        for line in lines:
            tempCount += 1
            if tempCount < count :
                continue
            else:
                count += 1
                rs = re.search(keyword, line)
                if rs:
                    print("number: %d  [error] -----------> %s" %(count, line))
            f.close()

def timeOut():
    global flag
    global verpath
    global varExe
    global verLog
    time.sleep(1)
    number = 0
    while(flag):
        time.sleep(20)
        info = os.stat(verpath + "/" + verLog)
        if time.time() - info.st_mtime < 600:
            print "doing"
            number = number + 1
            if number == 30:
                number = 0
                print "timeout 10 minute , dump has abnormal !!!"
                os.system("killall " + varExe)
                continue
        else:
            print "timeout 10 minute , dump has abnormal !!!"
            os.system("killall " + varExe)
            continue

if __name__ == '__main__':
    flag = True
    ver = sys.argv[1]
    dump = sys.argv[2]
    workpath = os.getcwd()
    verpath = workpath + "/" + ver
    varExe = "es11"
    verLog = ver + ".log"
    if(os.path.exists(verpath)):
        startTime = time.time()
        t1 = threading.Thread(target = runExe, name = "threadA")
        t2 = threading.Thread(target = checkOut, name = "threadB")
        t3 = threading.Thread(target = timeOut, name = "threadC")
        t1.start()
        t2.start()
        t3.start()
        t1.join()
        t2.join()
        t3.join()
        endTime = time.time()
        print("[Debug] ==== EXE time is : %s" %(endTime - startTime))
    else:
        print ("[Error] ==== " + verpath + " is not dir!")

