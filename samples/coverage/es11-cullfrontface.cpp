/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file cullfrontface.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for cullfrontface related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat vertices[] = {
	-2.0, 2.0,
	0.0, -2.0,
	2.0, 2.0
};

GLfloat colors[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0
};

GLenum culls[] = {
	GL_FRONT, 
	GL_BACK, 
	GL_FRONT_AND_BACK
};

GLenum fronts[] = {
	GL_CW, 
	GL_CCW
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

void renderFrame(GLenum front, GLenum cull)
{
    glEnable(GL_CULL_FACE);
    glFrontFace(front);
    glCullFace(cull);
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));

    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    glDisable(GL_CULL_FACE);
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(fronts); i++) {
        for(int j=0; j<ARRAY_NUM(culls); j++) {
            renderFrame(fronts[i],culls[j]);
            string cull_name=get_enum_name(culls[j]);
    	    string front_name=get_enum_name(fronts[i]);
            string bmp_file = filename + "-" + front_name + "-" + cull_name + ".bmp";
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

