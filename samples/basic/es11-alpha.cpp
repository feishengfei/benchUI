/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file alpha.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-20, Add commit
 * @brief basic test for alphafunc related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLfloat triColor1[] = {
	1.0,0.0,0.0,0.8,
	0.0,1.0,0.0,0.4,
	0.0,0.0,1.0,0.1
};
GLfloat triVertex1[] = {
	-2.0, 0.0,
	-1.0, 0.0,
	-1.5, 2.0
};

GLfloat triColor2[] = {
	1.0,0.5,0.0,0.1,
	0.0,1.0,0.0,0.8,
	0.0,0.0,1.0,0.4
};
GLfloat triVertex2[] = {
	0.0, 0.0,
	2.0, 0.0,
	2.0, 2.0
};

GLfloat triColor3[] = {
	1.0,0.5,0.0,0.1,
	0.0,0.0,1.0,0.4,
	1.0,1.0,0.0,0.7
};
GLfloat triVertex3[] = {
	0.0, 0.0,
	2.0, 2.0,
	0.0, 2.0
};

static const GLenum factors[] = {
	GL_NEVER,
	GL_LESS,
	GL_EQUAL,
	GL_LEQUAL,
	GL_GREATER,
	GL_NOTEQUAL,
	GL_GEQUAL,
	GL_ALWAYS
};

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof (-3.0, 3.0,-3.0, 3.0, -3.0, 3.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return true;
}

void renderFrame(GLenum factor)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glEnable(GL_ALPHA_TEST));
    GL_CHECK(glAlphaFunc(factor,0.4));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, triVertex1));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, triColor1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, triVertex2));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, triColor2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, triVertex3));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, triColor3));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
//getdata();
    GL_CHECK(glDisable(GL_ALPHA_TEST));
}

void getdata()
{
	GLboolean paramb;
	GLint parami;

	glGetBooleanv(GL_ALPHA_TEST,  &paramb);
	LOGI("Get(GL_ALPHA_TEST): %d\n",paramb);
	glGetIntegerv(GL_ALPHA_BITS,  &parami);
	LOGI("Get(GL_ALPHA_BITS): %d\n",parami);
	glGetIntegerv(GL_ALPHA_TEST_FUNC,  &parami);
	LOGI("Get(GL_ALPHA_TEST_FUNC): %d\n",parami);
	glGetIntegerv(GL_ALPHA_TEST_REF,  &parami);
	LOGI ("Get(GL_ALPHA_TEST_REF): %d\n",parami);
}

void Sample::test()
{
	setupGraphics(WINDOW_W, WINDOW_H);

	for(int i=0; i<ARRAY_NUM(factors); i++) {
		renderFrame(factors[i]);
		string factor_name = get_enum_name(factors[i]);
		string bmp_file = filename + "_" + factor_name + ".bmp";
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
