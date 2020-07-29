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
def GetName(rootDir):
  dirlist = os.listdir(rootDir)
  for temp in dirlist:
    subdir = os.path.join(rootDir, temp)
    if os.path.isdir(subdir) :
      GetName(subdir)
    else:
      if (os.path.splitext(subdir)[1] == ".vert") or (os.path.splitext(subdir)[1] == ".frag") or (os.path.splitext(subdir)[1] == ".gemo") or (os.path.splitext(subdir)[1] == ".glsl") or (os.path.splitext(subdir)[1] == ".geom") or (os.path.splitext(subdir)[1] == ".cont") or (os.path.splitext(subdir)[1] == ".eval") or (os.path.splitext(subdir)[1] == ".tes") or (os.path.splitext(subdir)[1] == ".tcs") or (os.path.splitext(subdir)[1] == ".comp"):
#        name = os.path.splitext(subdir)[0]
        namelist = subdir.split('/')
        filename = namelist[2]
        ver = namelist[1]
        fullname = ver + "-" + filename
        newname = os.path.join(rootDir, fullname)
        os.rename(subdir, newname)
        #shutil.move(reaultdir, newname)
      else:
        print(os.path.splitext(subdir)[1])

if __name__ == '__main__':
  rootdir = sys.argv[1]
  GetName(rootdir)
