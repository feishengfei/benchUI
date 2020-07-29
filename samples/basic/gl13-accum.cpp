/**
 * @file gl13-accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

GLenum factors[] = {
	GL_ACCUM,
	GL_LOAD,
	GL_ADD,
	GL_MULT,
	GL_RETURN
};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

void glDrawRec1(){
	glBegin(GL_TRIANGLES);
	glColor4f(0.1,0.1,0.4,0.0);
	glVertex3f(-0.6,-0.6,0.0);

	glColor4f(0.4,0.1,0.1,0.0);
	glVertex3f(0.4,-0.6,0.0);

	glColor4f(0.1,0.4,0.4,0.0);
	glVertex3f(0.4,0.4,0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.1,0.1,0.4,0.0);
	glVertex3f(-0.6,-0.6,0.0);
	
	glColor4f(0.1,0.4,0.4,0.0);
	glVertex3f(0.4,0.4,0.0);

	glColor4f(0.4,0.4,0.4,0.0);
	glVertex3f(-0.6,0.4,0.0);

	glEnd();
}

void glDrawRec2(){
	glBegin(GL_TRIANGLES);
	glColor4f(0.6,0.0,0.0,0.0);
	glVertex3f(-0.4,-0.4,0.0);

	glColor4f(0.0,0.6,0.0,0.0);
	glVertex3f(0.6,-0.4,0.0);

	glColor4f(0.0,0.0,0.6,0.0);
	glVertex3f(0.6,0.6,0.0);

	glColor4f(0.0,0.0,0.0,0.0);
	glVertex3f(-0.4,0.6,0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(0.6,0.0,0.0,0.0);
	glVertex3f(-0.4,-0.4,0.0);
	
	glColor4f(0.0,0.0,0.6,0.0);
	glVertex3f(0.6,0.6,0.0);

	glColor4f(0.0,0.0,0.0,0.0);
	glVertex3f(-0.4,0.6,0.0);

	glEnd();
}
bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho (-1.0f, 1.0f, -1.0f*h/w, 1.0f*h/w, -1.0f, 1.0f);
	}
	else {
		glOrtho (-1.0f*w/h, 1.0f*w/h, -1.0f, 1.0f, -1.0f, 1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void renderFrame(GLenum factor)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClearAccum(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_ACCUM_BUFFER_BIT);
	glDrawRec1();
	glAccum(factor, 1.0);
	glDrawRec2();
	glAccum(factor, 1.0);
	glAccum(factor, 1.0f);
	glFlush();
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-accum";
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
