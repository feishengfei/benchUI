/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file colorpointer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for colorpointer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLenum types_color[]={
	GL_UNSIGNED_BYTE,
	GL_FLOAT
};

GLfloat vertices[] = {
	-2.0, 2.0,
	0.0, -2.0,
	2.0, 2.0
};

GLubyte colors_ub[] = {
	255, 0, 0, 0,
	0, 255, 0, 0,
	0, 0, 255, 0
};

GLfloat colors[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0
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

void renderFrame(GLenum type)
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));

    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    if(type == GL_UNSIGNED_BYTE)
	    GL_CHECK(glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors_ub));
    if(type == GL_FLOAT)
	    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
//    GL_CHECK(glFlush());
    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glDisableClientState(GL_COLOR_ARRAY));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(types_color); i++) {
        renderFrame(types_color[i]);
        string type_name = get_enum_name(types_color[i]);
        string bmp_file = filename + "-" + type_name + ".bmp";
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
