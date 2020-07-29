/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file clipplane.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-20, Add commit
 * @brief basic test for clipplane related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat vertices[] = {
	-2.8, 2.8,
	-2.8, -2.8,
	2.8, -2.8,
	2.8, 2.8
};

   int max_clip=0;

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
   glGetIntegerv(GL_MAX_CLIP_PLANES, &max_clip);
//   printf("max num: %d\n",max_clip);
}

bool setupGraphics(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof (-4.0, 4.0,-4.0, 4.0, -3.0, 3.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return true;
}

void renderFrame(GLenum n)
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    for(int i=0; i<n; i++) {
        GLfloat eqn2[4] = {1.0, 0.0, 0.0, i*0.1};
        glClipPlanef(GL_CLIP_PLANE0+i, eqn2);
        glEnable(GL_CLIP_PLANE0+i);
        GLfloat params[4];
        glGetClipPlanef(GL_CLIP_PLANE0+i, params);
        LOGI("glGetClipPlane(%d): %f %f %f %f\n", i, params[0], params[1], params[2], params[3]);
    }

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.0));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
//    GL_CHECK(glFlush());

    for(int i=0; i<n; i++) 
        glDisable(GL_CLIP_PLANE0+i);
}

void Sample::test()
{
    init();
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<max_clip; i++) {
        renderFrame(i);
        char ss[2];
	    sprintf(ss, "%d", i);
        string bmp_file = filename + ss + ".bmp";
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
