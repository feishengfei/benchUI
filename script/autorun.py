# =================================================================
# Copyright (c) 2019 Botson Corp 
# Botson Confidential and Proprietary 
#
# Revision: 
# Date: 2019-08-19
# Author: 
# Descriptions: 
# 
# =================================================================
import os
import sys
import shutil

#copy run.py file & call run.py
def run4ver(path, version):
  global scriptpath
  global rundump
  runfile = scriptpath + "/run.py"
  if(os.path.exists(runfile)):
    shutil.copy(runfile, path)
  else:
    print ("[Error] ==== " + runfile + " not exist!")
  if(rundump == 'on'):
    dumpfile = scriptpath + "/dump.py"
    if(os.path.exists(dumpfile)):
      shutil.copy(dumpfile, path)
    else:
      print ("[Error] ==== " + dumpfile + " not exist!")
  os.chdir(path)
  print(os.getcwd()) 
  os.system("python run.py " + version + " " + rundump)
  print(path+"/run.py")
  os.remove(path+"/run.py")
#  if(rundump == 'on'):
#    os.remove(dumpfile)

def searchver(path):
  global runversion
  if(runversion == 'all'):
    for childverpath in os.listdir(path):
      print ("[Debug] ==== Run for version: " + childverpath)
      run4ver(path, childverpath)
  else:
    verpath = path + "/" + runversion
    if(os.path.exists(verpath)):
      print ("[Debug] ==== Run for version: " + runversion)
      run4ver(path, runversion)
    else:
      print ("[Error] ==== " + path + "/" + runversion + " not exist!")

if __name__ == '__main__':
  #Init input params
  runtype = 'all'
  runversion = 'all'
  rundump = 'off'
  
  #Get input params
  varnum = len(sys.argv) - 1
  scriptname = sys.argv[0]

  if(varnum >= 1):
    if(sys.argv[1] == 'dump'):
      runtype = 'all'
      runversion = 'all'
      rundump = 'on'
    else:
      runtype = sys.argv[1]
      if(varnum >= 2):
        runversion = sys.argv[2]
      if(varnum >= 3):
        rundump = sys.argv[3]
  
  #check params
  typenormal = 0
  typenists=['basic', 'function', 'model', 'shader', 'all']
  for typelist in typenists:
    if(runtype == typelist):
      typenormal = 1
  #if input param is a exefile check if file exsit
  
  #Debug print param
  print ("[Debug] Input params number: " + str(varnum))
  if(typenormal == 0):
    print ("[Debug]             name   :" + sys.argv[1])
  else:
    print ("[Debug]             type   :" + runtype)
    print ("[Debug]             version:" + runversion)
    print ("[Debug]             dump   :" + rundump)
  
  #search file & get file full name to runlist
  #Get project root path
  rootpath = os.getcwd()
  patharray=(rootpath.split("/"))
  curdir = patharray[len(patharray) - 1]
  if (curdir == 'bin') or (curdir == 'build') or (curdir == 'script'):
    rootpath = curdir + "../"
  os.chdir(rootpath)
  patharray=(rootpath.split("/"))
  curdir = patharray[len(patharray) - 1]
  if(curdir != 'btx_bench'):
    print ("[Error] Run Path not exist!")
    sys.exit(1)
  print ("[Debug] Root Path :" + rootpath)
  
  #Get project run path script path
  runpath = rootpath + "/bin/mesa/samples"
  scriptpath = rootpath + "/script"
  if(os.path.exists(runpath)):
    os.chdir(runpath)
    print ("[Debug] Run Path :" + os.getcwd())
  
  # change dir to type
  if(runtype == 'all'):
    for childtypepath in os.listdir(runpath):
      typepath = runpath + "/" + childtypepath
      print ("[Debug] == Run for type: " + typepath)
      searchver(typepath)
  else:
    typepath = runpath + "/" + runtype
    if(os.path.exists(typepath)):
      print ("[Debug] == Run for type: " + typepath)
      searchver(typepath)
    else:
      print ("[Error] ==== " + typepath + " not exist!")
  
  #if in bin path
  
    #list exefiles in run path
  
    #write into runlist
  
  #open thread: 1-run exe; 2-check timeout; 
  
  #get log & check error
  
  #check run number & success percent
  
  #make run report
  
  #submit the result file
  
  #if dump, config dump file
  
  #pull the golden bmp/md5
  
  #gen md5 for result picture
  #os.system(md5sum gl20/gl20-shader.bmp > runfile.md5);
  
  #search & compare the result picture
  
  #make compare result
