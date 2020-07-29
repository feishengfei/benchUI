#! /usr/bin/env python

import os,re

strMain="main(";
strFor="for(";
strWhile="while(";
t3='simple_framework3';
t="framework_lib";

def alter(file):
    numFor=0;
    hasMain=0;
    f2 = open('tmp.txt', 'a+')
    with open(file, "r") as f1:
#    with open(file, "r") as f1,open("%s.bak" % file, "w") as f2:
        for line in f1:
            if strMain in line:
                hasMain = 1;
            if ((strFor in line) and (hasMain == 1)):
                numFor = numFor + 1;
            if ((strWhile in line) and (hasMain == 1)):
                numFor = numFor + 1;
#            f2.write(re.sub(old, new, line))
        if ((numFor == 0) and (file.endswith('.cpp'))):
#             f2.write(file+'\n');
            print file;
    f1.close()
    numFor=0;
    hasMain=0;
#    f2.close()
#    os.remove(file)
#    os.rename("%s.bak" % file, file)

fileDir=os.getcwd();
fileList=[]
for root,dirs,files in os.walk(fileDir):
    for fileObj in files:
#        if os.path.basename(fileObj) == 'CMakeLists.txt':
#            print(os.path.abspath(fileObj));
            fileList.append(os.path.join(root,fileObj))

for fileObj in fileList:
#    print(os.path.abspath(fileObj));
    alter(fileObj)

    
