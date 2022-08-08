/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file drawarrays.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-20, Add commit
 * @brief basic test for drawarrays related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat vertices[] = {
	2.0, 0.0,
	0.0, 0.0,
	2.0, 2.0,
	0.0, 2.0
};

static const GLenum modes[] = {
	GL_POINTS,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_LINES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_TRIANGLES
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

void renderFrame(GLenum mode)
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.0));
    GL_CHECK(glDrawArrays(mode, 0, 4));
//    GL_CHECK(glFlush());
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(modes); i++) {
        renderFrame(modes[i]);
        string mode_name = get_primitives_name(modes[i]);
        string bmp_file = filename + "-" + mode_name + ".bmp";
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
