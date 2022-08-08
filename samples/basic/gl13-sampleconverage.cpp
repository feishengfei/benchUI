/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

GLfloat vertices[] = {
	0.25, 0.05,
	0.9, 0.2,
	0.25, 0.0,
	0.9, 0.0,
	0.875, 0.10
};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-2.0f, 2.0f, -2.0f*h/w, 2.0f*h/w, -2.0f, 2.0f);
	}
	else {
		glOrtho(-2.0f*w/h, 2.0f*w/h, -2.0f, 2.0f, -2.0f, 2.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getdata()
{
GLint parami;
GLboolean paramb;
GLfloat paramf;

glGetBooleanv(GL_MULTISAMPLE, &paramb); 
LOGIF("get(GL_MULTISAMPLE)=%s\n",GET_BOOL(paramb));
glGetBooleanv(GL_SAMPLE_ALPHA_TO_COVERAGE, &paramb); 
LOGIF("get(GL_SAMPLE_ALPHA_TO_COVERAGE)=%s\n",GET_BOOL(paramb));
glGetBooleanv(GL_SAMPLE_ALPHA_TO_ONE, &paramb); 
LOGIF("get(GL_SAMPLE_ALPHA_TO_ONE)=%s\n",GET_BOOL(paramb));
glGetBooleanv(GL_SAMPLE_COVERAGE, &paramb); 
LOGIF("get(GL_SAMPLE_COVERAGE)=%s\n",GET_BOOL(paramb));
glGetBooleanv(GL_SAMPLE_COVERAGE_INVERT, &paramb); 
LOGIF("get(GL_SAMPLE_COVERAGE_INVERT)=%s\n",GET_BOOL(paramb));
glGetFloatv(GL_SAMPLE_COVERAGE_VALUE, &paramf); 
LOGIF("get(GL_SAMPLE_COVERAGE_VALUE):%f\n", paramf);
glGetIntegerv(GL_SAMPLES, &parami);
LOGIF("get(GL_SAMPLES)=%d\n",parami);
glGetIntegerv(GL_SAMPLE_BUFFERS, &parami);
LOGIF("get(GL_SAMPLE_BUFFERS)=%d\n",parami);
}

void renderFrame()
{
	int i, j;
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glSampleCoverage(1.0,GL_TRUE));
    GL_CHECK(glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE));
    GL_CHECK(glEnable (GL_MULTISAMPLE));
    GL_CHECK(glPushMatrix());
    GL_CHECK(glTranslatef (-1.0, 0.0, 0.0));
      for (i = 0; i < 19; i++) {
      glPushMatrix();
      glRotatef(360.0*(float)i/19.0, 0.0, 0.0, 1.0);
      glColor4f (1.0, 1.0, 1.0,1.0);
      glLineWidth((i%3)+1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINES, 0, 2);
      glColor4f (0.0, 1.0, 1.0,1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 2, 3);
      glPopMatrix();
   }
   glPopMatrix();

   glDisable (GL_MULTISAMPLE);
   glPushMatrix();
   glTranslatef (1.0, 0.0, 0.0);
      for (i = 0; i < 19; i++) {
      glPushMatrix();
      glRotatef(360.0*(float)i/19.0, 0.0, 0.0, 1.0);
      glColor4f (1.0, 1.0, 1.0, 0.0);
      glLineWidth((i%3)+1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINES, 0, 2);
      glColor4f (0.0, 1.0, 1.0, 0.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 2, 3);
      glPopMatrix();
   }
   glPopMatrix();
//getdata();
    GL_CHECK(glFlush());
    GL_CHECK(glDisable(GL_MULTISAMPLE));
    GL_CHECK(glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE));
}


int main(int argc, char** argv)
{
    string file = "gl13-sampleconverage";
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
