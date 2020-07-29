/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texbufferrange.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texbufferrange related API
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

float data[] = {
	-1, -1,		0, 1,
	0, -1,		0, 1,
	0, 0,		0, 1,
	-1, -1,		0, 1,
	0, 0,		0, 1,
	-1, 0,		0, 1,

	-1, 0,		0, 0.5,
	0, 0,		0, 0.5,
	0, 1,		0, 0.5,
	-1, 0,		0, 0.5,
	0, 1,		0, 0.5,
	-1, 1,		0, 0.5,

	0, 0,		1, 0,
	1, 0,		1, 0,
	1, 1,		1, 0,
	0, 0,		1, 0,
	1, 1,		1, 0,
	0, 1,		1, 0,

	0, -1,		0.5, 0,
	1, -1,		0.5, 0,
	1, 0,		0.5, 0,
	0, -1,		0.5, 0,
	1, 0,		0.5, 0,
	0, 0,		0.5, 0,
};

GLuint prog;
GLuint vao;
GLuint tbo;
GLuint tex;


void initProgram()
{
    string vertexShaderPath = (string)GLSL_PATH + "texelFetch.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "texelFetch.frag";
    /* Process shaders. */
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    programID = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "pos"));

    GL_CHECK(glUseProgram(programID));
}

bool initBuffer()
{
	GL_CHECK(glGenVertexArrays(1, &vao));
	GL_CHECK(glBindVertexArray(vao));

	GL_CHECK(glGenBuffers(1, &tbo));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, tbo));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));

	GL_CHECK(glGenTextures(1, &tex));
	GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, tex));
    return true;
}

bool setupGraphics(int width, int height)
{
    initProgram();
    initBuffer();

    GL_CHECK(UniformDisplacement = glGetUniformLocation(programID, "s"));
    GL_CHECK(glUniform1i(UniformDisplacement, 0));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.2, 0.2, 0.2, 0.2));

    return true;
}

void renderFrame() {
	int i;
	int chunk_size = 24 * sizeof(float);
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

	GL_CHECK(glUseProgram(programID));
	for (i = 0; i < sizeof(data) / chunk_size; i++) {
		GL_CHECK(glTexBufferRange(GL_TEXTURE_BUFFER, GL_RGBA32F, tbo, i * chunk_size, chunk_size));
		GL_CHECK(glBindVertexArray(vao));
		GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
	}
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
//    string file = "es32-texbufferrange";
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