/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file matrix.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for matrix related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat vertices[] = {
	-2.8, 0.0,
	-2.0, 2.0,
	-1.2, 0.0
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

void renderFrame()
{
    GLfloat loadTrans[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	2.0, 0.0, 0.0, 1.0
    };

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(1.0, 0.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    glLoadMatrixf(loadTrans);
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    glMultMatrixf(loadTrans);
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    string bmp_file = filename + ".bmp";
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
