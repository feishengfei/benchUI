/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file depth.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for depth related API
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

static const GLenum masks[] = {
	GL_TRUE,
	GL_FALSE
};

static const GLenum funcs[] = {
	GL_NEVER,
	GL_LESS,
	GL_EQUAL,
	GL_LEQUAL,
	GL_GREATER,
	GL_NOTEQUAL,
	GL_GEQUAL,
	GL_ALWAYS
};

void init(void)
{
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthRangef(0.1, 0.7);
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

void renderFrame(GLenum func, GLboolean mask)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    glDepthMask(mask);

    GL_CHECK(glDepthFunc(func));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(1.0, 0.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices1));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.8));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

//    GL_CHECK(glFlush());
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(funcs); i++) {
        for(int j=0; j<2; j++) {
            renderFrame(funcs[i], masks[j]);
            string func_name = get_enum_name(funcs[i]);
            string mask_name = GET_BOOL(masks[j]);
            string bmp_file = filename + "-" + func_name + "-" + mask_name + ".bmp";
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

