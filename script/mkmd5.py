import os
import shutil
import re
import sys
from PIL import Image, ImageChops
import numpy as np

#list bmp files into filelist
def searchFile(start_dir, target, filelist):
    os.chdir(start_dir);
    for each_file in os.listdir(os.curdir):
        ext = os.path.splitext(each_file)[1]
        if ext in target:
            filelist.append(os.getcwd()+os.sep+each_file)
        if os.path.isdir(each_file):
            searchFile(each_file, target);
            os.chdir(os.pardir)

#generate golden and refer bmp list file
def generatelists():
    target = ['.bmp']
    searchFile(golden_dir, target, golden_list)
    searchFile(ref_dir, target, ref_list)
    os.chdir(program_dir)

    fg=open('golden.list', 'w+')
    fg.writelines(golden_list)
    fg.close()

    fr=open('ref.list', 'w+')
    fr.writelines(ref_list)
    fr.close()

#compare file
def compareBMP(a, b, filename):
    pic1 = Image.open(a)
    pic2 = Image.open(b)
    diff = ImageChops.difference(pic1,pic2)
    c = diff.convert('L')
    extrema = c.convert("L").getextrema()
    if extrema == (0,0):
        return True
    else:
        c.save("result/"+filename)
        return False

#search couple bmp file
def listCompare():
    for i in range(len(golden_list)):
        print(i)
        result_list.append('N')
        for ref in ref_list:
            filename = os.path.basename(ref)
            if filename in golden_list[i]:
                print(filename)
                print(golden_list[i])
                r = compareBMP(golden_list[i], ref, filename)
                if r == True :
                    result_list[i] = 'P'
                else:
                    result_list[i] = 'D'
                print(result_list[i])

#compare result compute
def compute():
    cnt = 0
    for rs in result_list:
        if rs == 'P' :
            cnt = cnt + 1
    PassPer = cnt / len(result_list)
    return PassPer

#write result to csv file
#Error code: P--Pass N--NoPic D--Diff
def write_report():
    f=open('report.csv', 'w+')
    f.write("Result picture, Pass or not\n")
    for i in range(len(golden_list)):
        f.write(str(i+1))
        f.write(', ')
        f.write(golden_list[i])
        f.write(', ')
        f.write(result_list[i])
        f.write('\n')
    f.write('Pass percent, ')
    f.write(str(compute()))
    f.close()

#main
if __name__ == "__main__":

    golden_list = [];
    ref_list = [];
    result_list = [];

    golden_dir = "/home/bts/eric/work/project/test-pic-diff/es20-mesa/";
    ref_dir = "/home/bts/eric/work/project/test-pic-diff/es20-nvidia/";
    program_dir = os.getcwd();
    
    if os.path.isdir("result"):
        shutil.rmtree("result")
    os.makedirs("result")

    generatelists();
    listCompare();
    write_report();
