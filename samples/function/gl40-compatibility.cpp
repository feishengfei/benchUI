/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file test.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-11-18, Add commit
 * @brief basic test for related API
 * @par TestPoints:
        glBlendEquationSeparatei
        glBlendFuncSeparatei
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID;

GLfloat vertices[] = {
/*	-2.0, -2.0,
	-2.0, 2.0,
	2.0, -2.0,
	2.0, 2.0*/
	-0.8, -0.8,
	-0.8, 0.8,
	0.8, -0.8,
	0.8, 0.8
};

GLfloat colors[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.5, 1.0, 0.5, 0.0
};
/*
bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho (-3.0f, 3.0f, -3.0f*h/w, 3.0f*h/w, -3.0f, 3.0f);
	}
	else {
		glOrtho (-3.0f*w/h, 3.0f*w/h, -3.0f, 3.0f, -3.0f, 3.0f);
	}

	if (w <= h) {
		glOrtho (-1.0f, 1.0f, -1.0f*h/w, 1.0f*h/w, -1.0f, 1.0f);
	}
	else {
		glOrtho (-1.0f*w/h, 1.0f*w/h, -1.0f, 1.0f, -1.0f, 1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void renderFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glShadeModel(GL_FLAT));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
}
*/
//new gl4.0
bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "vert2color4_passby.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "color_passby.frag";
    //static dfk=2;
    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }
GL_CHECK(glShadeModel(GL_FLAT));
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.3f, 0.3f, 0.3f, 0.7f));
glOrtho (-3.0f, 3.0f, -3.0f, 3.0f, -3.0f, 3.0f);
    return true;
}

void fileData() {
    GLint iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v2Position"));
    GLint iLocFillColor = GL_CHECK(glGetAttribLocation(programID, "a_v4Color"));
    
    GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, vertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, colors));
    GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    fileData();
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("%s\n", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}

