/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"
#include <cstring>

GLfloat vertices[] = {
	-2.0, -2.0,
	-2.0, 2.0,
	2.0, -2.0,
	2.0, 2.0
};

GLfloat colors[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.5, 1.0, 0.5, 0.0
};

static const GLenum factors[] = {
	GL_FLAT,
	GL_SMOOTH
};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

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
    return true;
}

void getdata()
{
GLint parami;
glGetIntegerv(GL_SHADE_MODEL, &parami);
LOGIF("get(GL_SHADE_MODEL)=%d\n",parami);
}

void renderFrame(GLenum factor)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glShadeModel(factor));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
getdata();
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "windowpos";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
	    renderFrame(factors[i]);
            string mode_name = get_enum_name(factors[i]);
	    string filename = file + "_" + mode_name + ".bmp";
	    LOGIF("[%d]: %s, filename=%s\n", i, mode_name.c_str(), filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
