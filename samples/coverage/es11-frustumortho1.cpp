/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file frustumortho1.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for frustumortho1 related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat triVertex[] = {
	0.0,0.0,0.0,
	-2.0,-2.0,-1.0,
	1.0,0.5,2.0,
};

GLfloat lineColor[] = {
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0
};

GLfloat lineVertex[] = {
	-5.0,0.0,0.0,
	5.0,0.0,0.0,
	0.0,-5.0,0.0,
	0.0,5.0,0.0,
	0.0,0.0,-5.0,
	0.0,0.0,5.0,
};

bool setupGraphicsO(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof (-5.0, 5.0,-5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

bool setupGraphicsF(int w, int h)
{
    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glMatrixMode(GL_PROJECTION));
    GL_CHECK(glLoadIdentity());
    GL_CHECK(glFrustumf(-1.0,1.0,-1.0,1.0,1.0,5.0));
    GL_CHECK(glMatrixMode(GL_MODELVIEW));
    GL_CHECK(glLoadIdentity());
    return true;
}

void renderFrame()
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0,0.0,-5.0);
	glLineWidth(5.0);
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, lineVertex));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, lineColor));
    GL_CHECK(glDrawArrays(GL_LINES, 0, 2));


    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, triVertex));
    GL_CHECK(glColor4f(0.0,1.0,0.0,0.0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	glPopMatrix();
    GL_CHECK(glFinish());

    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glDisableClientState(GL_COLOR_ARRAY));
}

void Sample::test()
{
    setupGraphicsF(WINDOW_W, WINDOW_H);

    string bmp_file = filename + "_Frustum.bmp";
    LOGI("filename=%s",bmp_file.c_str());
    renderFrame();
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
