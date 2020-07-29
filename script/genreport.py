import os
import shutil
import re
import sys
from PIL import Image, ImageChops
#import numpy as np
import operator
import filecmp

#list bmp files into filelist
def searchFile(start_dir, filetype, filelist):
    os.chdir(start_dir);
    for each_file in os.listdir(os.curdir):
        ext = os.path.splitext(each_file)[1]
        if ext in filetype:
            filelist.append(os.getcwd()+os.sep+each_file)
        if os.path.isdir(each_file):
            searchFile(each_file, filetype, filelist);
            os.chdir(os.pardir)

def comparePIC(goldendir, targetdir):
    filetype = ['.bmp']
    goldenlist = [];
    targetlist = [];
    searchFile(goldendir, filetype, goldenlist)
    searchFile(targetdir, filetype, targetlist)
    if len(goldenlist)==0 and len(targetlist)==0:
        return True,"no bmp file"
    if len(goldenlist) != len(targetlist):
        return False,"FAIL,bmp file num not eq"
    for i in range(len(goldenlist)):
        find = False
        for ref in targetlist:
            filename = os.path.basename(ref)
            if filename in goldenlist[i]:
#                print ref
#                print goldenlist[i]
                pic1 = Image.open(goldenlist[i])
                pic2 = Image.open(ref)
                diff = ImageChops.difference(pic1,pic2)
                c = diff.convert('L')
                extrema = c.convert("L").getextrema()
                if extrema == (0,0):
                    find = True
                    break
                else:
                    c.save(program_dir+"/diffpic/"+filename)
                    return False,"FAIL,bmp diff"
        if find == False:
            return False,"FAIL,bmp not find"
    return True,"bmps same"

def compareLog(goldendir, targetdir):
    filetype = ['.log']
    goldenlist = [];
    targetlist = [];
    searchFile(goldendir, filetype, goldenlist)
    searchFile(targetdir, filetype, targetlist)
    if len(goldenlist)==0 and len(targetlist)==0:
        return True,"no log file"
    if len(goldenlist) != len(targetlist):
        return False,"FAIL,log file num not eq"
    for i in range(len(goldenlist)):
        find = False
        for ref in targetlist:
            filename = os.path.basename(ref)
            f = open(filename, 'r')
            lines = f.readlines()
            for line in lines:
                if "error" in line or "ERROR" in line:
                    msg = "FAIL,"+line.strip()
                    return False,msg
            if filename in goldenlist[i]:
                if filecmp.cmp(goldenlist[i], ref) == True:
                    find = True
                    break
                else:
                    return False,"FAIL,log diff"
        if find == False:
            return False,"FAIL,log not find"
    return True,"logs same"

#main
if __name__ == "__main__":
    goldenPiclist = [];
    targetPiclist = [];
    result_list = [];
    status = True

    program_dir = os.getcwd();
    
    if os.path.isdir("golden"):
        golden_dir = os.path.join(program_dir, 'golden')
    if os.path.isdir("target"):
        target_dir = os.path.join(program_dir, 'target')

    if os.path.isdir("diffpic"):
        shutil.rmtree("diffpic")
    os.makedirs("diffpic")

    os.chdir(program_dir);
#    read result caselist.txt
    casefile = open('caselist.txt', 'r+')

    report_file = open('report.csv', 'w+')
    report_file.write("testcase,path,result,detail\n")

    while True:
        line = casefile.readline()
        if not line:
            break
        line1 = line.strip()
        linelist = line1.split(',')
        casename = linelist[0]
        pathname = linelist[1]
        goldencasedir = os.path.join(golden_dir, pathname)
        targetcasedir = os.path.join(target_dir, pathname)
#        print "--------",casename
        if not os.path.isdir(goldencasedir):
            #print "golden dir lack"
            report_file.write(line.replace(b'\n',b',Lack,golden folder not exist\n'))
            status = False
            continue

        if not os.path.isdir(targetcasedir):
            #print "target dir lack"
            report_file.write(line.replace(b'\n',b',Lack,target folder not exist\n'))
            status = False
            continue

#    compare: 1.search log, 2.list bmp, 3.cmop
        status_log, info_log = compareLog(goldencasedir, targetcasedir)
        if status_log == True:
            status_pic, info_pic = comparePIC(goldencasedir, targetcasedir)
            if status_pic == True:
                report_file.write(line.replace(b'\n',b',PASS\n'))
            else:
                str = ","+info_pic+"\n"
                report_file.write(line.replace(b'\n',str))
                status = False
        else:
            str = ","+info_log+"\n"
            report_file.write(line.replace(b'\n',str))
            status = False

    report_file.close()
    casefile.close()
    if status == False:
        sys.exit(0)
    else:
        sys.exit(1)
