/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file scissor.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-20, Add commit
 * @brief basic test for scissor related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat vertices[] = {
	-0.8, -0.5,
	-0.5, 0.5,
	-0.2, -0.5,
	0.8, -0.5,
	0.5, 0.5,
	0.2, -0.5
};

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrthof (-1.0f, 1.0f, -1.0f*h/w, 1.0f*h/w, -1.0f, 1.0f);
	}
	else {
		glOrthof (-1.0f*w/h, 1.0f*w/h, -1.0f, 1.0f, -1.0f, 1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void renderFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnable(GL_SCISSOR_TEST));
    GL_CHECK(glScissor(0,0,160,320));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.0));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
    GL_CHECK(glDisable(GL_SCISSOR_TEST));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

	renderFrame();
	string bmp_file = filename + ".bmp";
	LOGI("filename=%s",bmp_file.c_str());
	save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
