#! /usr/bin/env python

import os,re

t0="simple_framework0";
t1="simple_framework1";
t2='simple_framework2';
t3='simple_framework3';
t="framework_lib";

def alter(file, old, new):
    with open(file, "r") as f1,open("%s.bak" % file, "w") as f2:
        for line in f1:
            f2.write(re.sub(old, new, line))
    f1.close()
    f2.close()
    os.remove(file)
    os.rename("%s.bak" % file, file)

fileDir=os.getcwd();
fileList=[]
for root,dirs,files in os.walk(fileDir):
    for fileObj in files:
        if os.path.basename(fileObj) == 'CMakeLists.txt':
#            print(os.path.abspath(fileObj));
            fileList.append(os.path.join(root,fileObj))

for fileObj in fileList:
    print(os.path.abspath(fileObj));
    alter(fileObj, t0, t)
    
