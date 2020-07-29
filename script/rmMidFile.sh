#! /usr/bin/env bash
cd samples
rm -rf Makefile CMakeFiles cmake_install.cmake
for dir in `ls samples/`
do 
  if [ -d $dir ]
  then
    echo $dir
    cd $dir
    echo `pwd`
    cd ..
  fi
done
