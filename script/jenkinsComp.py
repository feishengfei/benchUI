#! /usr/bin/env python

import os
import sys
import linecache

compile_ver = sys.argv[1]
strlist = '../samples/basic_test/' + compile_ver + '/FileList.cmake'
strpath = '../bin/mesa/basic_test/' + compile_ver + '/'
#file = open(strlist, 'r')
#linecount = len(file.readlines())
total_line = 0
comment_line = 0
blank_line = 0
with open(strlist)as f:
    lines = f.readlines()
    total_line = len(lines)
    line_index = 0

    while line_index < total_line:
        line = lines[line_index]
        
        if line.startswith("//"):
            comment_line += 1
        elif line == "\n":
            blank_line += 1
        line_index += 1

fact_line = total_line - comment_line - blank_line
dir_count = len([name for name in os.listdir(strpath) if os.path.isfile(os.path.join(strpath, name))])
if dir_count != fact_line:
    print('error')
