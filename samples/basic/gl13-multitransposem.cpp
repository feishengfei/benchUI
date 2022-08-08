/*
 *  colormatix.c
 *  This program uses the color matrix to exchange the color channels of
 *  an image.
 *
 *    Red   -> Green
 *    Green -> Blue
 *    Blue  -> Red
 *
 */

#include "gl-util.h"
#include <cstring>

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLfloat vertices[] = {
	-2.8, 0.0,
	-2.0, 2.0,
	-1.2, 0.0
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
    return true;
}

void getdata()
{
GLfloat paramf16[16];
GLint parami;

glGetFloatv(GL_MODELVIEW_MATRIX, paramf16); 
LOGIF("get(GL_MODELVIEW_MATRIX):\n");
for(int i=0; i<4; i++)
	LOGIF("%f %f %f %f\n",paramf16[i*4+0],paramf16[i*4+1],paramf16[i*4+2],paramf16[i*4+3]);

glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &parami);
LOGIF("get(GL_MODELVIEW_STACK_DEPTH)=%d\n",parami);

glGetFloatv(GL_PROJECTION_MATRIX, paramf16); 
LOGIF("get(GL_MODELVIEW_MATRIX):\n");
for(int i=0; i<4; i++)
	LOGIF("%f %f %f %f\n",paramf16[i*4+0],paramf16[i*4+1],paramf16[i*4+2],paramf16[i*4+3]);

glGetIntegerv(GL_PROJECTION_STACK_DEPTH, &parami);
LOGIF("get(GL_MODELVIEW_STACK_DEPTH)=%d\n",parami);
glGetIntegerv(GL_MATRIX_MODE, &parami);
LOGIF("get(GL_MATRIX_MODE)=%d\n",parami);
glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &parami);
LOGIF("get(GL_MAX_MODELVIEW_STACK_DEPTH)=%d\n",parami);
glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &parami);
LOGIF("get(GL_MAX_PROJECTION_STACK_DEPTH)=%d\n",parami);
glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &parami);
LOGIF("get(GL_MAX_TEXTURE_STACK_DEPTH)=%d\n",parami);
glGetIntegerv(GL_MAX_TEXTURE_UNITS, &parami);
LOGIF("get(GL_MAX_TEXTURE_UNITS)=%d\n",parami);
}

void renderFrame()
{
    GLfloat loadTrans[] = {
	1.0, 0.0, 0.0, 2.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
    };
    GLdouble loadTransd[] = {
	1.0, 0.0, 0.0, 2.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
    };

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(1.0, 0.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

glMultTransposeMatrixf(loadTrans);
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

glMultTransposeMatrixd(loadTransd);
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
getdata();
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-multitransposem";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
	    string filename = file + ".bmp";
	    LOGIF("filename=%s\n", filename.c_str());
            renderFrame();
        save2bmp(filename.c_str());
	glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
