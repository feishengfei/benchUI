/**
 * @file accum2.c
 * @testgl13-point glAccum
 *
 */
#include "gl-util.h"
#include <cstring>

float sizes[]={2.0, 4.0, 6.0, 8.0};
float vertices[]={
	-1.5,0.5,  
	-0.5,0.5,
	0.5,0.5,
	1.5,0.5
};
float colors[]={
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	1.0, 1.0, 1.0, 0.0
};

GLenum factors[] = {
	GL_FASTEST,
	GL_NICEST,
	GL_DONT_CARE
};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho (-2.0f, 2.0f, -2.0f*h/w, 2.0f*h/w, -2.0f, 2.0f);
	}
	else {
		glOrtho (-2.0f, 2.0f, -2.0f*h/w, 2.0f*h/w, -2.0f, 2.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void renderFrame(GLenum factor)
{
    GL_CHECK(glClearColor (0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT ));
    glHint(GL_POINT_SMOOTH_HINT, factor);
    for(int i=0; i<4; i++) {
        GL_CHECK(glPointSize(sizes[i]));
        GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.0));
        GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
        GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices+i*2));
        GL_CHECK(glDrawArrays(GL_POINTS, 0, 1));
    }

    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-point";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<3; i++) {
        renderFrame(factors[i]);
	string factor_name = get_enum_name(factors[i]);
        string filename = file + "_" + factor_name + ".bmp";
        LOGIF("filename=%s\n", filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
