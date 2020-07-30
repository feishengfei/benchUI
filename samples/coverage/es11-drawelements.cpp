/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file drawleements.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for drawelements related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat colors[] = {
	1.0,1.0,0.0,0.0,
	1.0,0.0,0.0,0.0,
	0.0,1.0,0.0,0.0,
	0.0,0.0,1.0,0.0
};
GLfloat vertices[] = {
	2.0, 0.0,
	0.0, 0.0,
	2.0, 2.0,
	0.0, 2.0
};
GLubyte indices_ub[] = {0,1,2,3};
unsigned short indices_us[] = {0,1,2,3};
static const GLenum modes[] = {
	GL_POINTS,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_LINES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_TRIANGLES
};
static const GLenum types[] = {
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_SHORT
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

void renderFrame(GLenum mode, GLenum type)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
//GL_CHECK(glDrawArrays(GL_POINTS, 0, 4));
    if(type == GL_UNSIGNED_BYTE)
        GL_CHECK(glDrawElements(mode, 4, type, indices_ub));
    if(type == GL_UNSIGNED_SHORT)
        GL_CHECK(glDrawElements(mode, 4, type, indices_us));
//    GL_CHECK(glFlush());
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(modes); i++) {
        for(int j=0; j<ARRAY_NUM(types); j++) {
            renderFrame(modes[i], types[j]);
            string mode_name = get_primitives_name(modes[i]);
            string type_name = get_enum_name(types[j]);
            string bmp_file = filename + "-" + mode_name + "-" + type_name + ".bmp";
            LOGI("filename=%s",bmp_file.c_str());
            save2bmp(bmp_file.c_str());
            SwapBuffers();
        }
    }
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
