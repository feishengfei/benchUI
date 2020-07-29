cmake_minimum_required (VERSION 2.8)

project (framework)

file(GLOB SOURCES
    src/Platform.cpp
    src/Enum.cpp
    src/EGLRuntime.cpp
    src/Util.cpp
    src/bmp.cpp
    src/Shader.cpp
    src/Sample.cpp
    src/Matrix.cpp
    src/ETCHeader.cpp
    src/Texture.cpp
    src/LinuxX11Platform.cpp
    src/rgb.c
    src/Model.cpp
    src/Text.cpp
    src/Timer.cpp
)

file(GLOB PLATFORM_SOURCES src/LinuxX11Platform.cpp)
add_definitions(-DGBSDK_WINSYS_X11)

add_library(${FRAMEWORK_NAME} ${SOURCES} ${PLATFORM_SOURCES})
#add_library(${FRAMEWORK_NAME} SHARED ${SOURCES} ${PLATFORM_SOURCES})

#install(TARGETS ${FRAMEWORK_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
#install(DIRECTORY inc DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
