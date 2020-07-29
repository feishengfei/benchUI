import os
import shutil
import re
import sys
import numpy as np

def searchApi(filename, apis):
    if os.path.exists(filename):
        f=open(filename)
        lines = f.readlines()
    else:
        return
    if not apis:
        return
    for line in lines:
        for api in apis:
            api1 = api.strip();
            api2 = api1 + '(';
            if api2 in line:
                print(api1 + ":" + filename)
                apis.remove(api)
                if not apis:
                    return

#list cpp files into filelist
def searchFile(start_dir, target, filelist):
    os.chdir(start_dir);
    for each_file in os.listdir(os.curdir):
        ext = os.path.splitext(each_file)[1]
        if ext in target:
            filelist.append(os.getcwd()+os.sep+each_file)
        if os.path.isdir(each_file):
            searchFile(each_file, target, filelist);
            os.chdir(os.pardir)

#generate testcase list file
def generatelists():
    target = ['.cpp', '.c']
    searchFile(testbench_dir, target, testcaselist)
    os.chdir(program_dir)

    #read api list file into apis
    f=open("ogl43api.list","r")
    apis = f.readlines();
    f.close();

    for testcase in testcaselist:
        searchApi(testcase, apis)

    f=open('new.list', 'w+')
    for api in apis:
        api1 = api.strip();
        f.write(api1 + '\n')
    f.close();

#write result to csv file
#Error code: P--Pass N--NoPic D--Diff
#def write_report():
#    f=open('report.csv', 'w+')
#    f.write("Result picture, Pass or not\n")
#    for i in range(len(testcaselist)):
#        f.write(str(i+1))
#        f.write(', ')
#        f.write(testcaselist[i])
#        f.write(', ')
#        f.write(result_list[i])
#        f.write('\n')
#    f.write('Pass percent, ')
#    f.write(str(compute()))
#    f.close()

#main
if __name__ == "__main__":

    testcaselist = [];
    ref_list = [];
    result_list = [];

#    version=['gl43','gl42','gl41','gl40','gl32','gl32','gl31','gl30','gl30']
    testbench_dir = "/home/bts/otto/btx_bench/samples/basic/api/es20";
    program_dir = os.getcwd();
    
    if os.path.isdir("result"):
        shutil.rmtree("result")
    os.makedirs("result")

    generatelists();
