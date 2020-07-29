#! /usr/bin/env python

import os,re

#1' replace header
old_str="gles-util";
old_str1="gl-util";
new_str="Util";
#2' delete GLES_VERSION
#3' replace LOGIF __FILE__

def delete(Dir, string):
  for root,dirs,files in os.walk(Dir):
    for fileObj in files:
      if fileObj.endswith('.h') or fileObj.endswith('.cpp') :
        with open(fileObj, "r") as f1,open("%s.bak" % fileObj, "w") as f2:
          for line in f1:
            f2.write(re.sub(old, new, line))
        os.remove(fileObj)
        os.rename("%s.bak" % fileObj, fileObj)

def replace(Dir, old, new):
  for root,dirs,files in os.walk(Dir):
    for fileObj in files:
      if fileObj.endswith('.h') or fileObj.endswith('.cpp') :
        print(fileObj)
        with open(fileObj, "r") as f1,open("%s.bak" % fileObj, "w") as f2:
          for line in f1:
            f2.write(re.sub(old, new, line))
        os.remove(fileObj)
        os.rename("%s.bak" % fileObj, fileObj)

curDir=os.getcwd();
replace(curDir, old_str1, new_str);
replace(curDir, old_str, new_str);
