/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"
#include <cstring>

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

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

bool setupGraphics(int width, int height)
{
    GL_CHECK(glViewport(0, 0, width, height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        glOrtho(-8.0f, 8.0f, -8.0f, 8.0f, -8.0f, 8.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getdata()
{
GLint parami;
glGetIntegerv(GL_PERSPECTIVE_CORRECTION_HINT, &parami);
LOGIF("get(GL_PERSPECTIVE_CORRECTION_HINT)=%d\n",parami);
}

void renderFrame(GLenum factor)
{
        glShadeModel(GL_SMOOTH);
        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
        glClearDepth(1.0f);
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

int main(int argc, char** argv)
{
    string file = "gl13-perspectivecorrect";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<3; i++) {
        renderFrame(factors[i]);
	string factor_name = get_enum_name(factors[i]);
        string filename = file + "-" + factor_name + ".bmp";
        LOGIF("filename=%s\n", filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
