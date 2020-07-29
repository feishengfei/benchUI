/**
 * @file accum2.c
 * @testpoint glBegin glEnd
 *
 */
#include "gl-util.h"

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
#define NUM 12
GLfloat colors_f[NUM*3],vertex_f[NUM*2];//

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-3.0f, 3.0f, -3.0f*h/w, 3.0f*h/w, -3.0f, 3.0f);
	}
	else {
		glOrtho(-3.0f*w/h, 3.0f*w/h, -3.0f, 3.0f, -3.0f, 3.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	genvertex2(NUM, vertex_f, colors_f, 2);
    return true;
}

void renderFrame(GLenum mode)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glPointSize(5.0));
    GL_CHECK(glLineWidth(3.0));
    glBegin(mode);
	for(int i=0; i<NUM; i++) {
        glColor3f(colors_f[i*3],colors_f[i*3+1],colors_f[i*3+2]);
        glVertex2f(vertex_f[i*2],vertex_f[i*2+1]);
	}
    glEnd();
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-beginend";
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
