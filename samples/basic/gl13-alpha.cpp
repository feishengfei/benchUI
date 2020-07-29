/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

GLfloat triVertex1[] = {
	1.0,0.0,0.0,0.8,
	0.0,1.0,0.0,0.4,
	0.0,0.0,1.0,0.1
};
GLfloat triColor1[] = {
	-2.0, 0.0,
	-1.0, 0.0,
	-1.5, 2.0
};

GLfloat triVertex2[] = {
	1.0,0.5,0.0,0.1,
	0.0,1.0,0.0,0.8,
	0.0,0.0,1.0,0.4
};
GLfloat triColor2[] = {
	0.0, 0.0,
	2.0, 0.0,
	2.0, 2.0
};

GLfloat triVertex3[] = {
	1.0,0.5,0.0,0.1,
	0.0,0.0,1.0,0.4,
	1.0,1.0,0.0,0.7
};
GLfloat triColor3[] = {
	0.0, 0.0,
	2.0, 2.0,
	0.0, 2.0
};

static const GLenum factors[] = {
GL_NEVER,
GL_LESS,
GL_EQUAL,
GL_LEQUAL,
GL_GREATER,
GL_NOTEQUAL,
GL_GEQUAL,
GL_ALWAYS
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
	GLboolean paramb;
GLint parami;
glGetBooleanv(GL_ALPHA_TEST,  &paramb);
LOGIF("Get(GL_ALPHA_TEST): %d\n",paramb);
glGetIntegerv(GL_ALPHA_BITS,  &parami);
LOGIF("Get(GL_ALPHA_BITS): %d\n",parami);	
glGetIntegerv(GL_ALPHA_TEST_FUNC,  &parami);
LOGIF("Get(GL_ALPHA_TEST_FUNC): %d\n",parami);	
glGetIntegerv(GL_ALPHA_TEST_REF,  &parami);
LOGIF("Get(GL_ALPHA_TEST_REF): %d\n",parami);	
}
void renderFrame(GLenum factor)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glEnable(GL_ALPHA_TEST));
    GL_CHECK(glAlphaFunc(factor,0.4));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, triColor1));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, triVertex1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, triColor2));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, triVertex2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, triColor3));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, triVertex3));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
//getdata();
    GL_CHECK(glDisable(GL_ALPHA_TEST));
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-alpha";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
            string src_name = get_enum_name(factors[i]);
	    string filename = file + "-" + src_name + ".bmp";
	    LOGIF("[%d]: %s  filename=%s\n", i, src_name.c_str(), filename.c_str());
            renderFrame(factors[i]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
