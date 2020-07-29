/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file stencil.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for stencil related API
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

GLfloat vertices1[] = {
	-2.0, -2.0,
	0.0, 2.0,
	2.0, -2.0
};

static const GLenum funcs[] = {
	GL_NEVER,
	GL_LESS,
	GL_LEQUAL,
	GL_GREATER,
	GL_GEQUAL,
	GL_EQUAL,
	GL_NOTEQUAL,
	GL_ALWAYS
};

static const GLenum factors[] = {
	GL_KEEP,
	GL_ZERO,
	GL_REPLACE,
	GL_INCR,
	GL_DECR,
	GL_INVERT
};

void init(void)
{
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearStencil(0x00));
    GL_CHECK(glEnable(GL_STENCIL_TEST));
    GL_CHECK(glDisable(GL_DEPTH_TEST));
    GL_CHECK(glStencilMask(0x00));
}

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

void renderFrame(GLenum func, GLenum sfail, GLenum dpfail, GLenum dppass)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glStencilFunc(func,0x90,0xff));
    GL_CHECK(glStencilOp(sfail, dpfail, dppass));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(1.0, 0.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices1));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.8));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    init();
    for(int i=0; i<ARRAY_NUM(funcs); i++) {
        for (int j = 0; j < ARRAY_NUM(factors); j++) {
            for (int m = 0; m < ARRAY_NUM(factors); m++) {
                for (int n = 0; n < ARRAY_NUM(factors); n++) {
                    char ss[10];
                    sprintf(ss, "_%d_%d_%d_%d", i, j, m, n);
                    string func_name = get_enum_name(funcs[i]);
                    string sfail_name = get_enum_name(factors[j]);
                    string dpfail_name = get_enum_name(factors[m]);
                    string dppass_name = get_enum_name(factors[n]);
                    string bmp_file = filename + ss + "-" + func_name + "-" + sfail_name +
                                      "-" + dpfail_name + "-" + dppass_name + ".bmp";
                    LOGI("filename=%s",bmp_file.c_str());
                    renderFrame(funcs[i], factors[j], factors[m], factors[n]);
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
