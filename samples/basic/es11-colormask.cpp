/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file colormask.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for colormask related API
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

GLboolean mask[2] = {GL_TRUE,GL_FALSE};

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

void renderFrame(GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glColorMask(r,g,b,a));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int m = 0; m < 2; m++) {
                for (int n = 0; n < 2; n++) {
                    renderFrame(mask[i],mask[j],mask[m],mask[n]);
                    char ss[10];
             	    sprintf(ss, "_%d_%d_%d_%d", i, j, m, n);
                    string bmp_file = filename + ss + ".bmp";
                    LOGI("filename=%s",bmp_file.c_str());
                    save2bmp(bmp_file.c_str());
                    SwapBuffers();
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

