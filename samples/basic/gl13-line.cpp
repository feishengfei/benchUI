/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"
#include <cstring>

float sizes[]={2.0, 4.0, 6.0, 8.0};
float vertices[]={
	//-1.5,0.5,  
	-1.5,-0.5,  
	-0.5,0.5,
	-0.5,-0.5,
	0.5,0.5,
	0.5,-0.5,
	1.5,0.5,
	//1.5,-0.5
};
float colors[]={
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 1.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	1.0, 1.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	1.0, 0.0, 1.0, 0.0,
	1.0, 1.0, 1.0, 0.0,
	1.0, 1.0, 1.0, 0.0
};

GLenum factors[] = {
	GL_FASTEST,
	GL_NICEST,
	GL_DONT_CARE
};

static GLint fogMode;

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

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

void getdata()
{
GLfloat paramf2[2];
GLboolean paramb;
GLint parami;
GLfloat paramf;

glGetBooleanv(GL_LINE_SMOOTH, &paramb); 
LOGIF("get(GL_LINE_SMOOTH)=%s\n",GET_BOOL(paramb));

glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, paramf2); 
LOGIF("get(GL_ALIASED_LINE_WIDTH_RANGE):%f %f\n",paramf2[0],paramf2[1]);

glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, paramf2); 
LOGIF("get(GL_SMOOTH_LINE_WIDTH_RANGE):%f %f\n",paramf2[0],paramf2[1]);

glGetIntegerv(GL_LINE_SMOOTH_HINT, &parami);
LOGIF("get(GL_LINE_SMOOTH_HINT)=%d\n",parami);

glGetFloatv(GL_LINE_WIDTH, &paramf); 
LOGIF("get(GL_LINE_WIDTH):%f\n", paramf);
}

void renderFrame(GLenum factor)
{
    GL_CHECK(glClearColor (0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT ));

    glHint(GL_LINE_SMOOTH_HINT, factor);
    for(int i=0; i<3; i++) {
        GL_CHECK(glLineWidth(sizes[i]));
        GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
        GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors+i*4*2));
        GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
        GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices+i*4));
        GL_CHECK(glDrawArrays(GL_LINES, 0, 2));
    }
getdata();
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-line";
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
