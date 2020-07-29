/**
 * @file gl14-multidrawarrays.cpp
 * @testpoint glMultiDrawArrays
 *
 */
#include "gl-util.h"
#include <GL/glut.h>
#include <stdlib.h>

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

static const GLenum factors[] = {
	GL_POINTS,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_LINES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_TRIANGLES,
	GL_QUAD_STRIP,
	GL_QUADS,
	GL_POLYGON 
};

static const GLenum types[] = {
GL_UNSIGNED_BYTE,
GL_UNSIGNED_SHORT,
GL_UNSIGNED_INT
};


static const GLint vertices [] = {-4,-2,  -4,2,
				  0,2,  0,-2,   
				4,-2,  4,2};
static const GLfloat color[] = {0.0, 1.0, 0.0,
				1.0, 0.0, 0.0,
				0.0, 0.0, 1.0,
				0.0, 1.0, 0.0,
				1.0, 0.0, 0.0,
				0.0, 0.0, 1.0};

void setupGraphics(int width, int height)
{
    GL_CHECK(glViewport(0, 0, width, height));
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5,5,-5,5,5,15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0,0,10,0,0,0,0,1,0);
}

void renderFrame(GLenum mode)
{
	GLint first[] = {0,2};
	GLsizei count[] = {4,4};

	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	glPointSize(4.0);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, color);
	glVertexPointer(2, GL_INT, 0, vertices);
	glMultiDrawArrays(mode, first, count, 2);
	glFlush();
}

int main(int argc, char** argv)
{
    string file = "gl14-multidrawarrays";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
            string src_name = get_primitives_name(factors[i]);
	    string filename = file + "-" + src_name + ".bmp";
	    LOGIF("[%d]: filename=%s\n", i, filename.c_str());
            renderFrame(factors[i]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
