/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file polygonoffset.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for polygonoffset related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

float rotate=0.0;

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

void drawRect(float x, float y, float w, float h) {
    float vertexs[] = {
	x, y,
	x+w, y,
	x, y+h,
	x+w, y+h
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertexs);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void renderFrame()
{
    int i, j;
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    glPushMatrix ();
    glTranslatef(-0.9,0.0,0.0);
    rotate += 36;

    glRotatef(rotate, 0, 1, 0);

    glColor4f (1.0, 0.0, 0.0,1.0);
    drawRect(-1.0, -1.0, 1.0, 1.0);

    glColor4f (0.0, 1.0, 0.0,1.0);
    drawRect(-0.5, -0.5, 1.0, 1.0);
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef(0.9,0.0,0.0);
    rotate += 0.1;

    glRotatef(rotate, 0, 1, 0);
    GL_CHECK(glDisable (GL_POLYGON_OFFSET_FILL));
    glColor4f (1.0, 0.0, 0.0,1.0);
    drawRect(-1.0, -1.0, 1.0, 1.0);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 0.0);
    glColor4f (0.0, 1.0, 0.0,1.0);
    drawRect(-0.5, -0.5, 1.0, 1.0);
    glPopMatrix ();

    GL_CHECK(glDisable (GL_DEPTH_TEST));
    GL_CHECK(glDisable (GL_POLYGON_OFFSET_FILL));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    while(rotate < 720.0) {
        renderFrame();
        char ss[2];
        sprintf(ss, "_%d", int(rotate/36.0));
        string bmp_file = filename + ss + ".bmp";
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
