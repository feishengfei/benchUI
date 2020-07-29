#!/bin/bash

runBuild() {
  if [ -e ${rootDir}/target/${1}.cmake ];then
    rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake  framework  Makefile  samples
    cmake ../ -DBUILD_TARGET="$1" 2>&1 | tee -a ../result/build_$1.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
      echo "[Build Script]:  cmake error"
      exit 2
    else
      echo "[Build Script]:  cmake success"
    fi
    make -j8 2>&1 | tee -a ../result/build_$1.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
      echo "[Build Script]:  make error"
      exit 3
    else
      echo "[Build Script]:  make success"
    fi
    make install
    if [ $? -ne 0 ]; then
      echo "[Build Script]:  make install"
      exit 4
    else
      echo "[Build Script]:  make install success"
    fi
  else
    echo "[Build Script]:  ${rootDir}/target/${1}.cmake dir not exists, skip!"
  fi
}

#Step into build dir
workdir=$(cd $(dirname $0); pwd)
#echo "[Build Script]:  script work path:"${workdir}
workname="${workdir##*/}"
#echo "[Build Script]:  script work name:"${workname}
if [ "${workname}" != "build" ]; then
  mkdir -p build
  rm -rf build/*
  rootDir=`pwd`
  cd build/
else
  rootDir="${workdir}/../"
fi

if [ ! -d "./result" ]; then
    rm -rf result
    echo "[RUN]: File not exists, exit!"
    mkdir result
fi

echo "[Build Script]:  root Dir:"${rootDir}

#Init parameters
type="all"
version="gl43"

#Library Path
libpath_mesa="/home/bts/$USER/local/lib/"
alternative_libpath_gb=$(find /home/$(whoami) -type d -print | grep -E '/gbumd/gbumd-x86_64-debug/lib64$')
umd_libpath_gb=${alternative_libpath_gb:-$(find /home/$(whoami) -type d -print | grep -E '/gbumd-x86_64-debug-v.*/lib64$')}
libpath_gb=${umd_libpath_gb:-"/usr/local/botson/lib64"}
#input parameters list
build_target_list=("basic" "shader" "function" "model" "performance")
target_list="gb mesa"

#Clean up the old build information
rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake  framework  Makefile  samples *.log
rm -rf ../result/*
rm -rf ../bin/*

export MESA_DEBUG=1
export MESA_GL_VERSION_OVERRIDE=4.5
export MESA_GLES_VERSION_OVERRIDE=3.2
export MESA_GLSL_VERSION_OVERRIDE=450

if [ -z "$1" ];then
  if [ ! -n "$build_target_list" ]; then
    echo "Not define build_target_list"
    dir=$(ls -l ../target/ | awk '{print $9}')
    for li in $dir
    do
      extension="${li##*.}"
      if [[ $extension == "cmake" ]]
      then
        build_target="${li%.cmake}"
        echo $build_target
        runBuild $build_target
      fi
    done
  else
    for build_target in ${build_target_list[@]}
    do
      echo $build_target
      runBuild $build_target
    done
  fi
else
  echo "Build target:"
  echo $1
  runBuild $1
fi

cd $workdir
