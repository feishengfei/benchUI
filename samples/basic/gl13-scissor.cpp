/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

GLfloat vertices[] = {
	-0.8, -0.5,
	-0.5, 0.5,
	-0.2, -0.5,
	0.8, -0.5,
	0.5, 0.5,
	0.2, -0.5
};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-1.0f, 1.0f, -1.0f*h/w, 1.0f*h/w, -1.0f, 1.0f);
	}
	else {
		glOrtho(-1.0f*w/h, 1.0f*w/h, -1.0f, 1.0f, -1.0f, 1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getdata()
{
GLboolean paramb;
GLfloat paramf4[4];

glGetBooleanv(GL_SCISSOR_TEST, &paramb); 
LOGIF("get(GL_SCISSOR_TEST)=%s\n",GET_BOOL(paramb));

glGetFloatv(GL_SCISSOR_BOX, paramf4); 
LOGIF("get(GL_SCISSOR_BOX):\n");
for(int i=0; i<4; i++)
	LOGIF("%f ",paramf4[i]);
}

void renderFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnable(GL_SCISSOR_TEST));
    GL_CHECK(glScissor(0,0,160,320));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.0));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
    GL_CHECK(glDisable(GL_SCISSOR_TEST));
//getdata();
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-scissor";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
        renderFrame();
        string filename = file + ".bmp";
        LOGIF("filename=%s\n", filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
