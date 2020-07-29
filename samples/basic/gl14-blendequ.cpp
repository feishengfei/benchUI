/**
 * @file gl14-blendequ.cpp
 * @testpoint glBlendEquation
 *
 */
#include "gl-util.h"
unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;
#define NUM 3

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
GLenum factors[] = {
	GL_FUNC_ADD, 
	GL_FUNC_SUBTRACT,
        GL_FUNC_REVERSE_SUBTRACT, 
	GL_MIN, 
	GL_MAX
};

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho (-3.0f, 3.0f, -3.0f*h/w, 3.0f*h/w, -3.0f, 3.0f);
	}
	else {
		glOrtho (-3.0f*w/h, 3.0f*w/h, -3.0f, 3.0f, -3.0f, 3.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    return true;
}

void renderFrame(GLenum mode)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));    
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_COLOR,GL_SRC_ALPHA));
    GL_CHECK(glBlendEquation(mode));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(1.0, 0.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices1));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.8));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glFlush());
    GL_CHECK(glDisable(GL_BLEND));
}

int main(int argc, char** argv)
{
    string file = "gl14-blendequ";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++)
    {
        string src_name = get_enum_name(factors[i]);
	string filename = file + "-" + src_name + ".bmp";
	LOGIF("[%d]: filename=%s\n", i, filename.c_str());
        renderFrame(factors[i]);
	save2bmp(filename.c_str());
	glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
