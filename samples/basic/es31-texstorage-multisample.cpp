/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texstorage-multisample.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texstorage-multisample related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

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

GLenum factors[] = {
        GL_R8,
	GL_R8_SNORM,
	GL_R16F,
	GL_R32F,
	GL_R8UI,
	GL_R8I,
	GL_R16UI,
	GL_R16I,
	GL_R32UI,
	GL_R32I,
	GL_RG8,
	GL_RG8_SNORM,
	GL_RG16F,
	GL_RG32F,
	GL_RG8UI,
	GL_RG8I,
	GL_RG16UI,
	GL_RG16I,
	GL_RG32UI,
	GL_RG32I,
	GL_RGB8,
	GL_SRGB8,
	GL_RGB565,
	GL_RGB8_SNORM,
	GL_R11F_G11F_B10F,
	GL_RGB9_E5,
	GL_RGB16F,
	GL_RGB32F,
	GL_RGB8UI,
	GL_RGB8I,
	GL_RGB16UI,
	GL_RGB16I,
	GL_RGB32UI,
	GL_RGB32I,
	GL_RGBA8,
	GL_SRGB8_ALPHA8,
	GL_RGBA8_SNORM,
	GL_RGB5_A1,
	GL_RGBA4,
	GL_RGB10_A2,
	GL_RGBA16F,
	GL_RGBA32F,
	GL_RGBA8UI,
	GL_RGBA8I,
	GL_RGB10_A2UI,
	GL_RGBA16UI,
	GL_RGBA16I,
	GL_RGBA32I,
	GL_RGBA32UI,
    GL_DEPTH_COMPONENT16,
	GL_DEPTH_COMPONENT24,
	GL_DEPTH_COMPONENT32F,
	GL_DEPTH24_STENCIL8,
	GL_DEPTH32F_STENCIL8
};

bool setupGraphics(int w, int h)
{
    string vertexShaderPath = (string)GLSL_PATH + "base-green.vert"; 
    string fragmentShaderPath = (string)GLSL_PATH + "base-green.frag";
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

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    
    glGenTextures(1, &textureID);
    glGenFramebuffers(1, &fbo);

//    GL_CHECK(glEnable(GL_DEPTH_TEST));
    glViewport(0,0,w,h);
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
}

void renderToFB(GLenum factor)
{
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureID));
    GL_CHECK(glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 1, factor, WINDOW_W, WINDOW_H, GL_FALSE));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
    GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, textureID, 0));

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
//render to fb
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glLineWidth(10.0));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices1));
    GL_CHECK(glDrawArrays(GL_LINES, 0, 2));
    GL_CHECK(glDisableVertexAttribArray(iLocPosition));
}

void renderFrame(GLenum factor)
{
    renderToFB(factor);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    GLenum const BuffersRender = GL_COLOR_ATTACHMENT0;
    glBlitFramebuffer(0, 0, WINDOW_W, WINDOW_H, 0, 0, WINDOW_W, WINDOW_H, GL_COLOR_BUFFER_BIT,
                      GL_NEAREST);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        renderFrame(factors[i]);
        char ss[3];
        sprintf(ss, "%d", i);
        string factor_name = get_enum_name(factors[i]);
        string bmp_file = filename + "-" +  ss  + factor_name + ".bmp";
        LOGI("bmp_file=%s", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

//int main(int argc, char **argv)
//{
//    string file = "es31-texstorage-multisample";
//
//    GBtest_init(&argc,argv,file);
//    Platform * platform = Platform::getInstance();
//    platform->createWindow(WINDOW_W, WINDOW_H);
//    EGLRuntime::initializeEGL(EGLRuntime::OPENGLES31);
//    EGL_CHECK(eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context));
//    setupGraphics(WINDOW_W, WINDOW_H);
//#ifndef DUMP
//    for(int i=0; i<ARRAY_NUM(factors); i++) {
//        string filename = file + get_enum_name(factors[i]) + ".bmp";
//        renderFrame(factors[i]);
//#else
//        string filename = file + ".bmp";
//        renderFrame(factors[0]);
//#endif
//        EGLRuntime::pixelsToPicture(filename.c_str());
//        eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
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