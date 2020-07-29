#!/bin/bash

#Setup Mesa Version
setMesaGLversion() {
  case $1 in
    es32 )
      export MESA_GLES_VERSION_OVERRIDE=3.2
      export MESA_GLSL_VERSION_OVERRIDE=320
      shift ;;
    es31 )
      export MESA_GLES_VERSION_OVERRIDE=3.1
      export MESA_GLSL_VERSION_OVERRIDE=310
      shift ;;
    es30 )
      export MESA_GLES_VERSION_OVERRIDE=3.0
      export MESA_GLSL_VERSION_OVERRIDE=300
      shift ;;
    es20 )
      export MESA_GLES_VERSION_OVERRIDE=2.0
      export MESA_GLSL_VERSION_OVERRIDE=200
      shift ;;
    es11 )
      export MESA_GLES_VERSION_OVERRIDE=1.1
      shift ;;
    gl13 | gl14 )
      export MESA_GLES_VERSION_OVERRIDE=1.4
      shift ;;
    gl15 )
      export MESA_GLES_VERSION_OVERRIDE=1.5
      shift ;;
    gl20 )
      export MESA_GL_VERSION_OVERRIDE=2.0
      export MESA_GLSL_VERSION_OVERRIDE=110
      shift ;;
    gl21 )
      export MESA_GL_VERSION_OVERRIDE=2.1
      export MESA_GLSL_VERSION_OVERRIDE=120
      shift ;;
    gl30 )
      export MESA_GL_VERSION_OVERRIDE=3.0
      export MESA_GLSL_VERSION_OVERRIDE=130
      shift ;;
    gl31 )
      export MESA_GL_VERSION_OVERRIDE=3.1
      export MESA_GLSL_VERSION_OVERRIDE=140
      shift ;;
    gl32 )
      export MESA_GL_VERSION_OVERRIDE=3.2
      export MESA_GLSL_VERSION_OVERRIDE=150
      shift ;;
    gl33 )
      export MESA_GL_VERSION_OVERRIDE=3.3
      export MESA_GLSL_VERSION_OVERRIDE=330
      shift ;;
    gl40 )
      export MESA_GL_VERSION_OVERRIDE=4.0
      export MESA_GLSL_VERSION_OVERRIDE=400
      shift ;;
    gl41 )
      export MESA_GL_VERSION_OVERRIDE=4.1
      export MESA_GLSL_VERSION_OVERRIDE=410
      shift ;;
    gl42 )
      export MESA_GL_VERSION_OVERRIDE=4.2
      export MESA_GLSL_VERSION_OVERRIDE=420
      shift ;;
    gl43 )
      export MESA_GL_VERSION_OVERRIDE=4.3
      export MESA_GLSL_VERSION_OVERRIDE=430
      shift ;;
    gl44 )
      export MESA_GL_VERSION_OVERRIDE=4.4
      export MESA_GLSL_VERSION_OVERRIDE=440
      shift ;;
    * )
      export MESA_GL_VERSION_OVERRIDE=4.5
      export MESA_GLES_VERSION_OVERRIDE=3.2
      export MESA_GLSL_VERSION_OVERRIDE=450
      shift ;;
    esac
}

runBuild() {
  if [ -e ${rootDir}/samples/$2/$1 ];then
    rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake  framework  Makefile  samples build.log
    cmake ../ -DVER="$1" -DTYPE="$2" -DWINSYS="$winsys" -DARCH="$arch" -DDEBUG="$debug" -DTARGET="$target" -DLIB="$lib" 2>&1 | tee -a build.log
    if [ ${PIPESTATUS[0]} -ne 0 ]; then
      echo "[Build Script]:  cmake error"
      exit 2
    else
      echo "[Build Script]:  cmake success"
    fi
    make -j8 2>&1 | tee -a build.log
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
    echo "[Build Script]:  ${rootDir}/sample/$2/$1 dir not exists, skip!"
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
echo "[Build Script]:  root Dir:"${rootDir}

#Init parameters
type="all"
version="all"
target="mesa"
winsys="x11"
arch="x86"
debug="off"
#Library Path
libpath_mesa="/home/bts/$USER/local/lib/"
libpath_gb="/home/loongson/project/gb/gbumd-loongson-release/lib64"
libpath_tc="/home/bts/zac/local/botson_lib/tclib"
libpath_hikey="/home/shunya/eric/dump_gbsdk/install_dump/libs"
#input parameters list
type_list="basic function model performance simulate shader"
version_list="gl13 gl14 gl15 gl20 gl21 gl30 gl31 gl32 gl33 gl40 gl41 gl42 gl43 gl44 gl45 es11 es20 es21 es30 es31 es32"
target_list="gb mesa tc hikey"
winsys_list="x11 fbdev offscreen"
arch_list="x86 arm aarch64"
number=0 #Error Code:   1:No input parameters;   2:cmake error;   3:make error;
index=1

#Chech if there is input parameters. 
#If not, print usage of this script
if [ -z "$1" ];then
  echo "[Build Script]:  Usage: $0 + canshu"
  echo "[Build Script]:         version: $version_list"
  echo "[Build Script]:         tye    : $type_list"
  echo "[Build Script]:         target : $target_list"
  echo "[Build Script]:         arch   : $arch_list"
  echo "[Build Script]:         winsys : $winsys_list"
  exit 1
fi
#If has, list the parameters
#echo "[Build Script]:  listing args with:"
#for arg in $*
#do
#  echo "[Build Script]:  arg: $index=$arg"
#  let index+=1
#done
#Parser the input parameters
for arg in $*
do
  if [[ $type_list =~ $arg ]]
  then
    type=$arg
  fi
  if [[ $version_list =~ $arg ]]
  then
    version=$arg
  fi
  if [[ $target_list =~ $arg ]]
  then
    target=$arg
  fi
  if [[ $winsys_list =~ $arg ]]
  then
    winsys=$arg
  fi
  if [[ $arch_list =~ $arg ]]
  then
    arch=$arg
  fi
done
if [[ $* =~ "debug" ]]
then
  debug="on"
fi
if [[ $* =~ "release" ]]
then
  debug="off"
fi
echo "[Build Script]:  Use: ${type} ${version} ${target} ${winsys} ${arch} ${debug}"

#Clean up the old build information
rm -rf CMakeCache.txt  CMakeFiles  cmake_install.cmake  framework  Makefile  samples build.log
rm -rf ../bin/* 

#Setup envirment parameters
if [ "$target" == "gb" ]; then
  export LD_LIBRARY_PATH=$libpath_gb
  arch="x86"
  winsys="x11" 
  lib=$libpath_gb
elif [ "$target" == "tc" ]; then
  export LD_LIBRARY_PATH=$libpath_tc
  arch="arm"
  winsys="fbdev" 
  lib=$libpath_tc
elif [ "$target" == "hikey" ]; then
  export LD_LIBRARY_PATH=$libpath_hikey
  arch="aarch64"
  winsys="offscreen" 
  lib=$libpath_hikey
else
  export LIBGL_DRIVERS_PATH="$libpath_mesa/dri/"
  export LD_LIBRARY_PATH=$libpath_mesa
  export PATH=$PATH:$libpath_mesa
  export MESA_DEBUG=1
  setMesaGLversion $version
fi

if [[ $type == "all" ]]; then
  arrtype=$(echo $type_list | tr " " "\n")
  for argtype in ${arrtype}
  do
    type=${argtype}
    echo "[Build Script]:  ${argtype}"
    if [[ $version == "all" ]]; then
      arrver=$(echo $version_list | tr " " "\n")
      for argver in ${arrver}
      do
        version=${argver}
        echo "[Build Script]:  ${argver}"
        if [ "$target" == "mesa" ]; then
          setMesaGLversion $argver
        fi
        runBuild $argver $argtype
      done
    else
      runBuild $version $argtype
    fi
  done
else
  if [[ $version == "all" ]]; then
    arrver=$(echo $version_list | tr " " "\n")
    for argver in ${arrver}
    do
      version=${argver}
      echo "[Build Script]:  ${argver}"
      if [ "$target" == "mesa" ]; then
        setMesaGLversion $argver
      fi
      runBuild $argver $type
    done
  else
    runBuild $version $type
  fi
fi
