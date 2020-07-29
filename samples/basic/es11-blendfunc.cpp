/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file blendfunc.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-20, Add commit
 * @brief basic test for blendfunc related API
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

static const GLenum srcfactors[] = {
	GL_ZERO,
	GL_ONE,
	GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
	GL_SRC_ALPHA_SATURATE,
};

static const GLenum dstfactors[] = {
	GL_ZERO,
	GL_ONE,
	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA
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

void renderFrame(GLenum src, GLenum dst)
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(src, dst));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(1.0, 0.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices1));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.8));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glDisable(GL_BLEND));
}

void Sample::test()
{
	setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(srcfactors); i++) {
        for(int j=0; j<ARRAY_NUM(dstfactors); j++) {
			renderFrame(srcfactors[i],dstfactors[j]);
			string src_name = get_blending_name(srcfactors[i]);
			string dst_name = get_blending_name(dstfactors[j]);
			string bmp_file = filename + "_" + src_name  + "_" + dst_name + ".bmp";
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
