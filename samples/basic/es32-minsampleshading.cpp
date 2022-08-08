/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file minsampleshading.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for minsampleshading related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
//#include "GLES3/gl32.h"

using std::string;
using namespace BotsonSDK;

string resourceDirectory = "assets/";
/* Shader variables. */
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLuint fbo = -1;
/* Texture variables. */
GLuint textureID = 0;

float vertices1[] =
{
    -0.8f, -0.8f, 0.0f, /* 1 */
     0.8f, 0.8f, 0.0f, /* 3 */
};

bool setupGraphics(int w, int h)
{
    string vertexShaderPath = (string)GLSL_PATH + "base-red.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "base-red.frag";
    /* Process shaders. */
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    programID = GL_CHECK(glCreateProgram());
    if (programID == 0)
    {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "pos"));
    
    glGenTextures(1, &textureID);
    glGenFramebuffers(1, &fbo);

//    GL_CHECK(glEnable(GL_DEPTH_TEST));
    glViewport(0,0,w,h);
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
}

void renderToFB()
{
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureID);
    GL_CHECK(glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 1, GL_RGBA8, WINDOW_W, WINDOW_H, GL_FALSE));
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureID, 0);

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
//render to fb
    GL_CHECK(glEnable(GL_SAMPLE_SHADING));
    GL_CHECK(glMinSampleShading(1.0));
    GL_CHECK(glUseProgram(programID));
    glLineWidth(10.0);
    glEnableVertexAttribArray(iLocPosition);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices1);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableVertexAttribArray(iLocPosition);
}

void renderFrame()
{
    renderToFB();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    GLenum const BuffersRender = GL_COLOR_ATTACHMENT0;
    glBlitFramebuffer(0, 0, WINDOW_W, WINDOW_H, 0, 0, WINDOW_W, WINDOW_H, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file  = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

//int main(int argc, char **argv)
//{
//    string file = "es32-minsampleshading";
//
//    GBtest_init(&argc,argv,file);
//    Platform * platform = Platform::getInstance();
//    platform->createWindow(WINDOW_W, WINDOW_H);
//    EGLRuntime::initializeEGL(EGLRuntime::OPENGLES32);
//    EGL_CHECK(eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context));
//    setupGraphics(WINDOW_W, WINDOW_H);
//#ifndef DUMP
//    while(1) {
//#endif
//        renderFrame();
//        string filename = file + ".bmp";
//        EGLRuntime::pixelsToPicture(filename.c_str());
//	eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
//#ifndef DUMP
//    }
//#endif
//    EGLRuntime::terminateEGL();
//    platform->destroyWindow();
//    delete platform;
//    GBtest_deinit();
//
//    return 0;
//}
//