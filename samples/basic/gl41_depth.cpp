/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl41_depthf.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-12-25, Init file
 * @brief basic test for related API
 * @par TestPoints:
       glClearDepthf
       glDepthRangef
 *
 */
#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, VAOs, Buffers;
using std::string;
using namespace BotsonSDK;
using namespace std;

float vertices[] = {
	0.9, 0.0, 1.5,
	0.6, 0.0, 1.0,
	0.3, 0.0, 0.5,
	0.0, 0.0, 0.0,
	-0.3, 0.0, -0.5,
       	-0.6, 0.0, -1.0,
	-0.9, 0.0, -1.5
};

float color[] = {
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 1.0, 1.0,
	1.0, 0.0, 1.0, 1.0
};

GLint iLocPosition = -1, iLocColor=-1;

bool setupGraphics(int width, int height)
{
    string vertexShaderPath = (string)GLSL_PATH + "vert4color4_passby.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "gl41color_passby.frag";
    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClearDepth(0.1));
    GL_CHECK(glDepthRangef(-1.0, 1.0));
    GL_CHECK(glDepthRange(-0.6, 0.6));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glPointSize(8.0));
    GL_CHECK(glViewport(0, 0, width, height));

    GLfloat range[2];
    GL_CHECK(glGetFloatv(GL_DEPTH_RANGE, range));
    LOGI("Get(GL_DEPTH_RANGE): %f, %f\n", range[0], range[1]);
    GLfloat clear;
    GL_CHECK(glGetFloatv(GL_DEPTH_CLEAR_VALUE, &clear));
    LOGI("Get(GL_DEPTH_CLEAR_VALUE): %f\n", clear);

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(iLocColor = glGetAttribLocation(programID, "a_v4Color"));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(color), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color), color));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(iLocColor));
    GL_CHECK(glVertexAttribPointer(iLocColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    return true;
}

void renderFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_POINTS,0,7));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    string bmp_file = filename + ".bmp";
    renderFrame();
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}
