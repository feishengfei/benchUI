/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texstoragemultisample.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texstoragemultisample related API
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
GLint iTexPosition = -1;
GLuint vao;
GLuint positionBufferObject;
const int texUnit=0;
GLuint samplerUniform;
GLuint texBufferObject;
float vertices[] =
{
    -1.0f,  1.0f, 0.0f, /* 0 */
    -1.0f, -1.0f, 0.0f, /* 1 */
     1.0f,  1.0f, 0.0f, /* 2 */
     1.0f, -1.0f, 0.0f, /* 3 */
};

float vertices1[] =
{
	-0.5,-0.5,-0.5,  0.5,-0.5,-0.5,  -0.5,0.5,-0.5,
	0.5,-0.5,-0.5,  -0.5,0.5,-0.5,  0.5,0.5,-0.5,

	-0.5,-0.5,-0.5,  -0.5,0.5,-0.5,  -0.5,-0.5,0.5,
	-0.5,0.5,-0.5,  -0.5,-0.5,0.5,  -0.5,0.5,0.5,

	-0.5,-0.5,-0.5,  -0.5,-0.5,0.5,  0.5,-0.5,-0.5,
	-0.5,-0.5,0.5,  0.5,-0.5,-0.5,  0.5,-0.5,0.5,  

	-0.5,-0.5,0.5,  -0.5,0.5,0.5,  0.5,-0.5,0.5,
	-0.5,0.5,0.5,  0.5,-0.5,0.5,  0.5,0.5,0.5,

	-0.5,0.5,-0.5,  -0.5,0.5,0.5,  0.5,0.5,-0.5,
	-0.5,0.5,0.5,  0.5,0.5,-0.5,  0.5,0.5,0.5,

	0.5,-0.5,-0.5,  0.5,-0.5,0.5,  0.5,0.5,-0.5,
	0.5,-0.5,0.5,  0.5,0.5,-0.5,  0.5,0.5,0.5,
};
float texcoords1[] =
{
	0,0,0,  1,0,0,  0,1,0,
	1,0,0,  0,1,0,  1,1,0,

	0,0,0,  0,1,0,  0,0,1,
	0,1,0,  0,0,1,  0,1,1,

	0,0,0,  0,0,1,  1,0,0,
	0,0,1,  1,0,0,  1,0,1,  

	0,0,1,  0,1,1,  1,0,1,
	0,1,1,  1,0,1,  1,1,1,

	0,1,0,  0,1,1,  1,1,0,
	0,1,1,  1,1,0,  1,1,1,

	1,0,0,  1,0,1,  1,1,0,
	1,0,1,  1,1,0,  1,1,1,
};

float texcoords[] =
{
    0.0f, 0.0f, /* 0 */
    0.0f, 1.0f, /* 1 */
    1.0f, 0.0f, /* 2 */
    1.0f, 1.0f, /* 3 */
};

#define iWidth 16
#define iHeight 16
#define iDepth 16
static GLubyte image[iDepth][iHeight][iWidth][4];
GLuint TextureName, MultisampleTextureName;
GLuint FramebufferRenderName, FramebufferResolveName;
GLuint ColorTextureName;
void makeImage(void)
{
   int s, t, r;
    
   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            image[r][t][s][0] = (GLubyte) (s * 17);
            image[r][t][s][1] = (GLubyte) (t * 17);
            image[r][t][s][2] = (GLubyte) (r * 17);
            image[r][t][s][3] = (GLubyte) (r * 17);
         }
}

void initProgram()
{
    string vertexShaderPath = (string)GLSL_PATH + "multisample.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "multisample.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    samplerUniform = glGetUniformLocation(programID, "texSampler"); 

    GL_CHECK(glUniform1i(samplerUniform, 0));

}

bool initTexture()
{
    GL_CHECK(glGenTextures(1, &TextureName));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, TextureName));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1,GL_RGBA8,iWidth, iHeight, iDepth));

    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, iWidth, iHeight, iDepth, GL_RGBA, GL_UNSIGNED_BYTE, image));

    return true;
}

bool initFramebuffer() {
    GL_CHECK(glGenTextures(1, &MultisampleTextureName));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, MultisampleTextureName));
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_MAX_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_R, GL_RED);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);

    LOGI("MultisampleTextureName: %d\n", MultisampleTextureName);
    int bufSize = 2;
    int params[2];
    glGetInternalformativ(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_RGBA8, GL_SAMPLES, bufSize, params);
    LOGI("num sample %d, %d\n", params[0], params[1]);

    int pname = 0;
    glGetTexParameteriv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_IMMUTABLE_FORMAT, &pname);
    LOGI("GL_TEXTURE_2D_ARRAY, GL_TEXTURE_IMMUTABLE_FORMAT: %d\n", pname);
    pname = 0;
    glGetTexParameteriv(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_IMMUTABLE_FORMAT, &pname);
    LOGI("GL_TEXTURE_2D_MULTISAMPLE_ARRAY, GL_TEXTURE_IMMUTABLE_FORMAT: %d\n", pname);
    pname = 0;
    glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES, &pname);
    LOGI("GL_MAX_COLOR_TEXTURE_SAMPLES: %d\n", pname);

    GL_CHECK(glTexStorage3DMultisample(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 1, GL_RGBA8, WINDOW_W, WINDOW_H, 1, GL_TRUE));
    GL_CHECK(glGenFramebuffers(1, &FramebufferRenderName));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, FramebufferRenderName));

    LOGI("FramebufferRenderName: %d\n", FramebufferRenderName);
    pname = 0;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &pname);
    LOGI("MAX_COLOR_ATTACHMENTS: %d\n", FramebufferRenderName);

    GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, MultisampleTextureName, 0));

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenTextures(1, &ColorTextureName);
    glBindTexture(GL_TEXTURE_2D_ARRAY, ColorTextureName);
    GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, WINDOW_W, WINDOW_H, 1));

    glGenFramebuffers(1, &FramebufferResolveName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferResolveName);
    GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ColorTextureName, 0));

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return false;
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    return true;
}

bool setupGraphics(int w, int h)
{
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    glViewport(0,0,w,h);
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
bool Validated=true;
    makeImage();
    initProgram();
    if(Validated)
        Validated = initTexture();
    if(Validated)
        Validated = initFramebuffer();
}

bool end()
{
    glDeleteProgram(programID);
    glDeleteTextures(1, &TextureName);
    glDeleteTextures(1, &ColorTextureName);
    glDeleteTextures(1, &MultisampleTextureName);
    glDeleteFramebuffers(1, &FramebufferRenderName);
    glDeleteFramebuffers(1, &FramebufferResolveName);

    return true;
}

void renderFBO() {
    GL_CHECK(glViewport(0, 0, WINDOW_W, WINDOW_H));
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferRenderName);

    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, TextureName));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices1));
    GL_CHECK(glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, texcoords1));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glEnableVertexAttribArray(4));

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 36));
}

void renderFB() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, ColorTextureName);//translate
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices1);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, texcoords1);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(4);

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 36));
}

bool render() {
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));

    // Pass 1, render the scene in a multisampled framebuffer
    renderFBO();

    // Resolved multisampling
    glBindFramebuffer(GL_READ_FRAMEBUFFER, FramebufferRenderName);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FramebufferResolveName);
    glBlitFramebuffer(0, 0, WINDOW_W, WINDOW_H, 0, 0, WINDOW_W, WINDOW_H, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Pass 2, render the colorbuffer from the multisampled framebuffer
    GL_CHECK(glViewport(0, 0, WINDOW_W, WINDOW_H));
    renderFB();

    return true;
}

void renderFrame() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, texBufferObject);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, texBufferObject);
    GL_CHECK(
            glTexStorage3DMultisample(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 1, GL_RGBA8, iWidth, iHeight, iDepth, GL_FALSE));
    glBindTexture(GL_TEXTURE_2D_ARRAY, texBufferObject);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, iWidth, iHeight, iDepth, GL_RGBA, GL_UNSIGNED_BYTE, image);

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texBufferObject);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices1);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, vertices1);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);
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
//    string file = "es32-texstoragemultisample";
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