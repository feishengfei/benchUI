/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file perspectivecorrect.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for perspectivecorrect related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat triverts[] = {
	0.0f, 1.0f, 0.0f,
	-1.0f,-1.0f, 0.0f,
	1.0f,-1.0f, 0.0f
};

GLfloat quadverts[] = {
	 1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,
	 1.0f,-1.0f, 0.0f,
	-1.0f,-1.0f, 0.0f
};

GLenum factors[] = {
	GL_FASTEST,
	GL_NICEST,
	GL_DONT_CARE
};
static GLint fogMode;

bool setupGraphics(int width, int height)
{
    GL_CHECK(glViewport(0, 0, width, height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        glOrthof(-3.0f, 3.0f, -3.0f, 3.0f, -3.0f, 3.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void renderFrame(GLenum factor)
{
        glShadeModel(GL_SMOOTH);
        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
        glClearDepthf(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, factor); 

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	glLoadIdentity();
	glTranslatef(-3.0f,0.0f, 0.0f);	

    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, triverts));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glColor4f(1.0, 0.0, 0.0, 0.0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	glTranslatef(6.0f,0.0f,0.0f);	
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, quadverts));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.0));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<3; i++) {
        renderFrame(factors[i]);
        string factor_name = get_enum_name(factors[i]);
        string bmp_file = filename + "-" + factor_name + ".bmp";
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
