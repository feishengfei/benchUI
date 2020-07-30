cmake_minimum_required (VERSION 2.8.0)

## Config
# List and print config file, cmake target
set(BUILD_TARGET "default" CACHE STRING "build type in ${PROJECT_SOURCE_DIR}/target")
if(NOT DEFINED BUILD_TARGET)
  file(GLOB BUILD_TARGETS ./target/*.cmake)
  if (BUILD_TARGETS)
    message(NOTICE "Avaliable build target:")
    foreach(FILENAME ${BUILD_TARGETS})
      string(REGEX REPLACE ".+/(.+)\\..*" "\\1" BUILD_TARGET ${FILENAME})
      message("                      ${BUILD_TARGET}")
    endforeach()
  else()
    message(FATAL_ERROR "NO avaliable build target!")
  endif (BUILD_TARGETS)
endif()
message("Select build type: ${BUILD_TARGET}")

include(target/${BUILD_TARGET}.cmake)

# Arch: x86 / arm / aarch64
if (ARCH)
    if ((${ARCH} STREQUAL "x86") OR (${ARCH} STREQUAL "arm") OR (${ARCH} STREQUAL "aarch64"))
        message("Build for Arch: ${ARCH}")
    else ()
        message("Arch: ${ARCH} is not valid, Choose are \"x86\" or \"arm\" or \"aarch64\"")
    endif ()
else (ARCH)
    message("ARCH was not set, Now using \"x86\" as default")
    set(ARCH x86)
endif (ARCH)

# Type: coverage / function / model / perform / shader / all
if (TYPE)
    if ((${TYPE} STREQUAL "coverage") OR (${TYPE} STREQUAL "function") OR (${TYPE} STREQUAL "shader")
      OR (${TYPE} STREQUAL "model") OR (${TYPE} STREQUAL "performance") OR (${TYPE} STREQUAL "simulate")
      OR (${TYPE} STREQUAL "all"))
        message("Build for Type: ${TYPE}")
    else ()
        message("Type: ${TYPE} is not valid. Choices are \"coverage\" and \"function\" and \"model\" and \"performance\" and \"simulate\" and \"all\"")
    endif ()
else (TYPE)
    message("TYPE was not set, Now using \"coverage\" as default")
    set(TYPE "coverage")
endif (TYPE)

#gdb: on / off
if (DEBUG)
    if ((${DEBUG} STREQUAL "on") OR (${DEBUG} STREQUAL "off"))
        message("Build witch Debug: ${DEBUG}")
    else()
        message("DEBUG is not valid. Choices are \"on\" and \"off\"")
    endif()
else()
    message("DEBUG was not set, Now using \"off\" as default")
    set(DEBUG "off")
endif()

# gl/es version: gl13 ~ gl45 or es11 ~ es32
if (VER)
    if ((${VER} STREQUAL "gl13") OR (${VER} STREQUAL "gl14") OR (${VER} STREQUAL "gl15") 
      OR (${VER} STREQUAL "gl20") OR (${VER} STREQUAL "gl21") OR (${VER} STREQUAL "gl30") 
      OR (${VER} STREQUAL "gl31") OR (${VER} STREQUAL "gl32") OR (${VER} STREQUAL "gl33") 
      OR (${VER} STREQUAL "gl40") OR (${VER} STREQUAL "gl41") OR (${VER} STREQUAL "gl42") 
      OR (${VER} STREQUAL "gl43") OR (${VER} STREQUAL "gl44") OR (${VER} STREQUAL "gl45"))
        add_definitions(-DAPI_GL) 
        message("Build for version: ${VER}")
    elseif ((${VER} STREQUAL "es11") OR (${VER} STREQUAL "es20") OR (${VER} STREQUAL "es30") 
      OR (${VER} STREQUAL "es31") OR (${VER} STREQUAL "es32"))
        add_definitions(-DAPI_ES) 
        message("Build for version: ${VER}")
    else ()
        message("Target: ${VER} is not valid. Choices are from \"gl13\" to \"gl45\" or \"es11\" to \"es32\"")
    endif ()
else (VER)
    message("VER was not set, Now using \"es20\" as default")
    set(VER "es20")
    add_definitions(-DAPI_ES) 
endif (VER)

string(SUBSTRING ${VER} 0 2 apitype)
string(SUBSTRING ${VER} 2 2 apiversion)

#DEBUG
if (${DEBUG} STREQUAL "on")
    set(CMAKE_CXX_FLAGS "-O0 -g -ggdb ${CMAKE_CXX_FLAGS}")
endif ()

#ARCH
add_definitions(-g)
add_definitions(-std=c++11)
if (${ARCH} STREQUAL "arm")
    message("set arm platform toolschain")
    set (TOOLCHAIN_ROOT arm-xilinx-linux-gnueabi-)
    set (CMAKE_TOOLCHAIN_FILE arm-linux.cmake)
    add_definitions(-D__arm__)
elseif (${ARCH} STREQUAL "aarch64")
    message("set arm64 platform toolchain")
    set (TOOLCHAIN_ROOT aarch64-linux-gnu-)
    set (CMAKE_TOOLCHAIN_FILE arm-linux.cmake)
    add_definitions(-D__arm__)
else ()
    message("set x86 platform toolchain")
endif ()

#project
project(gb_opengles_sdk)

# Don't build an RPATH into the libraries
set(CMAKE_SKIP_RPATH TRUE)

# Use relative paths in the generated projects
set(CMAKE_USE_RELATIVE_PATHS TRUE)

# Add the DEBUG definition if not building in release mode
if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-DDEBUG)
endif()

include_directories(inc)
include_directories(framework/inc)
include_directories(framework/inc/models)

#set MESA env
set(PLATFORM_LIBRARIES X11 m png jpeg)
if((${VER} STREQUAL "es32") OR (${VER} STREQUAL "es31") OR (${VER} STREQUAL "es30") OR (${VER} STREQUAL "es20"))
    set(OPENGL_LIBRARIES GLESv2 EGL)
elseif(${VER} STREQUAL "es11")
    set(OPENGL_LIBRARIES GLESv1_CM EGL)
else()
    set(OPENGL_LIBRARIES GL glut)
endif()

# Set the install prefix per target.
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin/)

add_definitions(-DPROJECT_PATH="${PROJECT_SOURCE_DIR}/")
add_definitions(-DAPI_VERSION=${apiversion})
add_definitions(-DRES_PATH="${PROJECT_SOURCE_DIR}/res")
add_definitions(-DPICTURE_PATH="${PROJECT_SOURCE_DIR}/res/picture/")
add_definitions(-DGLSL_PATH="${PROJECT_SOURCE_DIR}/samples/${TYPE}/shader/${VER}/")
add_definitions(-DTYPE="${TYPE}")

set(FRAMEWORK_NAME framework)
add_subdirectory(framework)
add_subdirectory(samples)
