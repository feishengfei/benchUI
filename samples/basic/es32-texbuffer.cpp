/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texbuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texbuffer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
//#include "GLES3/gl32.h"

using std::string;
using namespace BotsonSDK;

/* Shader variables. */
GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

GLint iLocPosition = -1;
GLuint UniformDisplacement;

float vertices[] =
{
    /* 256 x 128 */
    -1.0f,  1.0f, 0.0f, /* 0 */
    -1.0f, -1.0f, 0.0f, /* 1 */
     0.0f,  1.0f, 0.0f, /* 2 */
     0.0f, -1.0f, 0.0f, /* 3 */
};
float vertices1[] =
{
    /* 256 x 128 */
     0.0f,  1.0f, 0.0f, /* 0 */
     0.0f, -1.0f, 0.0f, /* 1 */
     1.0f,  1.0f, 0.0f, /* 2 */
     1.0f, -1.0f, 0.0f, /* 3 */
};


GLuint tex, bo;
uint8_t g_rgba8[] = {0x00, 0xff, 0x00, 0x00};
uint8_t b_rgba8[] = {0x00, 0x00, 0xff, 0x00};

bool setupGraphics(int width, int height)
{
    string vertexShaderPath = (string)GLSL_PATH + "samplerBuffer.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "samplerBuffer.frag";
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

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "pos"));

    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glGenBuffers(1, &bo));
    GL_CHECK(glBindBuffer(GL_TEXTURE_BUFFER, bo));
    GL_CHECK(glBufferData(GL_TEXTURE_BUFFER, sizeof(g_rgba8), g_rgba8, GL_STREAM_DRAW));

    GL_CHECK(glGenTextures(1, &tex));
    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, tex));
    GL_CHECK(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8, bo));
    GL_CHECK(UniformDisplacement = glGetUniformLocation(programID, "s"));
    GL_CHECK(glUniform1i(UniformDisplacement, 0));

    glViewport(0, 0, width, height);
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    GL_CHECK(glBufferData(GL_TEXTURE_BUFFER, sizeof(b_rgba8), b_rgba8, GL_STREAM_DRAW));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices1));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
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
//    string file = "es32-texbuffer";
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