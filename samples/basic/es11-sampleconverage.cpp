/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file sampleconverage.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for sampleconverage related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;


GLboolean inverts[] {
    GL_TRUE,
    GL_FALSE
};


GLfloat vertices[] = {
	0.25, 0.05,
	0.9, 0.2,
	0.25, 0.0,
	0.9, 0.0,
	0.875, 0.10
};

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrthof (-2.0f, 2.0f, -2.0f*h/w, 2.0f*h/w, -2.0f, 2.0f);
	}
	else {
		glOrthof (-2.0f*w/h, 2.0f*w/h, -2.0f, 2.0f, -2.0f, 2.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void renderFrame(GLboolean invert) {
    int i, j;
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glSampleCoverage(1.0, invert));
    GL_CHECK(glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE));
    GL_CHECK(glEnable(GL_MULTISAMPLE));
    GL_CHECK(glPushMatrix());
    GL_CHECK(glTranslatef(-1.0, 0.0, 0.0));
    for (i = 0; i < 19; i++) {
        glPushMatrix();
        glRotatef(360.0 * (float)i / 19.0, 0.0, 0.0, 1.0);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glLineWidth((i % 3) + 1.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_LINES, 0, 2);
        glColor4f(0.0, 1.0, 1.0, 1.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLES, 2, 3);
        glPopMatrix();
    }
    glPopMatrix();

    glDisable(GL_MULTISAMPLE);
    glPushMatrix();
    glTranslatef(1.0, 0.0, 0.0);
    for (i = 0; i < 19; i++) {
        glPushMatrix();
        glRotatef(360.0 * (float)i / 19.0, 0.0, 0.0, 1.0);
        glColor4f(1.0, 1.0, 1.0, 0.0);
        glLineWidth((i % 3) + 1.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_LINES, 0, 2);
        glColor4f(0.0, 1.0, 1.0, 0.0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices);
        glDrawArrays(GL_TRIANGLES, 2, 3);
        glPopMatrix();
    }
    glPopMatrix();

    GL_CHECK(glFlush());
    GL_CHECK(glDisable(GL_MULTISAMPLE));
    GL_CHECK(glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE));
}


void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for (int i = 0; i < ARRAY_NUM(inverts); i++) {
        renderFrame(inverts[i]);
        char ss[2];
        sprintf(ss, "%d", i);
        string bmp_file = filename + ss + ".bmp";
        LOGI("filename=%s", bmp_file.c_str());
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
