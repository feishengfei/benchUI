/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file line.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for line related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

float sizes[]={2.0, 4.0, 6.0, 8.0};
float vertices[]={
	-1.5,-0.5,  
	-0.5,0.5,
	-0.5,-0.5,
	0.5,0.5,
	0.5,-0.5,
	1.5,0.5
};
float colors[]={
	0.0, 1.0, 1.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	1.0, 1.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	1.0, 0.0, 1.0, 0.0,
	1.0, 1.0, 1.0, 0.0
};

GLenum factors[] = {
	GL_FASTEST,
	GL_NICEST,
	GL_DONT_CARE
};

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrthof (-2.0f, 2.0f, -2.0f*h/w, 2.0f*h/w, -2.0f, 2.0f);
	}
	else {
		glOrthof (-2.0f*w/h, 2.0f*w/h, -2.0f, 2.0f, -2.0f, 2.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void renderFrame(GLenum factor)
{
    GL_CHECK(glClearColor (0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT ));

    glHint(GL_LINE_SMOOTH_HINT, factor);
    for(int i=0; i<3; i++) {
        GL_CHECK(glLineWidth(sizes[i]));
        GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
        GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors+i*4*2));
        GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
        GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices+i*4));
        GL_CHECK(glDrawArrays(GL_LINES, 0, 2));
    }
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(factors); i++) {
		renderFrame(factors[i]);
		string factor_name = get_enum_name(factors[i]);
		string bmp_file = filename + "-" + factor_name + ".bmp";
		LOGI("filename=%s",bmp_file.c_str());
		save2bmp(bmp_file.c_str());
        SwapBuffers();
    }
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
