/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#include "Sample.h"
#include <iostream>

using std::string;
using namespace BotsonSDK;


namespace BotsonSDK {

    Sample::Sample(string file, int argc, char **argv)
    {
        string tmp = getFileName(file);
        filename = tmp.substr(0, tmp.rfind("."));

        btx_init(filename);

#ifdef API_ES
        Platform *platform = Platform::getInstance();

        platform->createWindow(WINDOW_W, WINDOW_H);
#if (GLES_VERSION == 11)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES1);
#elif(GLES_VERSION == 20)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES2);
#elif(GLES_VERSION == 30)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES3);
#elif(GLES_VERSION == 31)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES31);
 #elif(GLES_VERSION == 32)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES32);
#endif
        EGL_CHECK(eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context));
#else
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
        glutInitWindowPosition(10.0,10.0);
        glutInitWindowSize(WINDOW_W,WINDOW_H);
        glutCreateWindow("Botson OpenGL SDK");
#endif
    }

#ifdef API_ES

    Sample::Sample(string file, int window_w, int window_h) {
        string tmp = getFileName(file);
        filename = tmp.substr(0, tmp.rfind("."));

        btx_init(filename);

        Platform *platform = Platform::getInstance();

        platform->createWindow(window_w, window_h);
#if (GLES_VERSION == 11)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES1);
#elif(GLES_VERSION == 20)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES2);
#elif(GLES_VERSION == 30)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES3);
#elif(GLES_VERSION == 31)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES31);
 #elif(GLES_VERSION == 32)
        EGLRuntime::initializeEGL(EGLRuntime::OPENGLES32);
#endif
        EGL_CHECK(eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context));
    }

#else
    Sample::Sample(string file, unsigned int mode, int argc, char **argv)
    {
        string tmp = getFileName(file);
        filename = tmp.substr(0, tmp.rfind("."));

        btx_init(filename);

        glutInit(&argc,argv);
        glutInitDisplayMode(mode);
        glutInitWindowPosition(10.0,10.0);
        glutInitWindowSize(WINDOW_W,WINDOW_H);
        glutCreateWindow("Botson OpenGL SDK");
    }
#endif

    Sample::~Sample() {
#ifdef API_ES
        EGLRuntime::terminateEGL();
        platform->destroyWindow();
        delete platform;
#endif
        btx_deinit();
    }

    void
    Sample::SwapBuffers(void) {

#ifdef API_ES
        eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
#else
        glutSwapBuffers();
#endif
    }
}

