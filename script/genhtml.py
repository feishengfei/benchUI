#! /usr/bin/env python
# =================================================================
# Copyright (c) 2019 Botson Corp 
# Botson Confidential and Proprietary 
#
# Revision: 
# Date: 2019-02-11
# Author: 
# Descriptions: 
# 
# =================================================================
import os
import sys
import re

def replaceName(rootdir, new, old):
  path = os.path.join(rootdir, old)
  filelist = os.listdir(path)
  wild = '.'
  for temp in filelist:
    dirname = os.path.join(path, temp)
    if os.path.isfile(dirname):
      f = open(dirname, 'r+')
      allLine = f.readlines()
      f.seek(0)
      f.truncate()
      for line in allLine:
        f.write(line.replace(old, new))
      f.close()
      oldname = temp
      string = temp.split(wild)
      if string[0] == old:
        name = dirstr + '-' + oldname
        os.rename(os.path.join(path,oldname), os.path.join(path,name))

def renameDir(rootDir, fpout):
  dirlist = os.listdir(rootDir)
  for temp in dirlist:
     path = os.path.join(rootDir, temp)
     if os.path.isdir(path):
       if (dirstr in temp) == False:
         newname = dirstr + '-' + temp
         replaceName(rootDir, newname, temp)
         os.rename(os.path.join(rootDir,temp), os.path.join(rootDir,newname))
         fpout.write("add_subdirectory(" + newname + ")\n")

def writeCMake(rootDir, fpout):
  wildcard = "samples/"
  string = rootDir.split(wildcard)
  fpout.write("set(EXEC_DIR " + string[1] + ")\n")

def changName(rootdir):
  filename = 'CMakeLists.txt'
  outfile = os.path.join(rootdir, filename)
  fp = open(outfile, "w")
  if not fp:
    print("can not open file %s." %fp)
  writeCMake(rootdir, fp)
  renameDir(rootdir, fp)
  fp.close()

def DirNameCH(subdir, newdir):
      print "new name: %s" %dirstr
      print "sub dir: %s" %subdir
      os.rename(subdir, newdir)
      changName(newdir)

def GetName(rootDir):
  dirlist = os.listdir(rootDir)
  for temp in dirlist:
    subdir = os.path.join(rootDir, temp)
    if os.path.isdir(subdir) :
      global dirstr
      if temp == 'gles11':
        dirstr = 'es11'
        newdir = os.path.join(rootDir, dirstr)
        DirNameCH(subdir, newdir)
      elif temp == 'gles20':
        dirstr = 'es20'
        newdir = os.path.join(rootDir, dirstr)
        DirNameCH(subdir, newdir)
      elif temp == 'gles30':
        dirstr = 'es30'
        newdir = os.path.join(rootDir, dirstr)
        DirNameCH(subdir, newdir)
      elif temp == 'gles31':
        dirstr = 'es31'
        newdir = os.path.join(rootDir, dirstr)
        DirNameCH(subdir, newdir)
      elif temp == 'ogl13':
        dirstr = 'gl13'
        newdir = os.path.join(rootDir, dirstr)
        DirNameCH(subdir, newdir)
      elif temp == 'ogl14':
        dirstr = 'gl14'
        newdir = os.path.join(rootDir, dirstr)
        DirNameCH(subdir, newdir)
      elif temp == 'ogl15':
        dirstr = 'gl15'
        newdir = os.path.join(rootDir, dirstr)
        DirNameCH(subdir, newdir)
      elif temp == 'ogl20':
        dirstr = 'gl20'
        newdir = os.path.join(rootDir, dirstr)
        DirNameCH(subdir, newdir)
      else:
        GetName(subdir)

if __name__ == '__main__':
  dirstr = ''
  rootdir = sys.path[0]
  GetName(rootdir)
