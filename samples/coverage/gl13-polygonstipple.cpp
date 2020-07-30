/**
 * @file gl13-polygonstipple.cpp
 * @testpoint glPolygonStipple
 *
 */
#include "gl-util.h"

GLubyte stipple_factor[] = {
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33, 
	0x33, 0x33, 0x33, 0x33
};

GLuint uistipple_factor[] = {
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333, 
	0x33333333
};

GLenum factors[] = {
	GL_FASTEST,
	GL_NICEST,
	GL_DONT_CARE
};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glOrtho(-240, 240, -160, 160, -2, 2);
	glLoadIdentity();
	glClearColor(0.0, 0.0, 0.0, 0.0);
    return true;
}

void display(GLenum mode)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//Triangles hint testing

	glEnable(GL_POLYGON_STIPPLE);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POLYGON_SMOOTH_HINT, mode);
	glPolygonStipple(stipple_factor);
	glColor3f(1.0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0-240, 0-160);
	glVertex2f(30-240, 0-160);
	glVertex2f(30-240, 140-160);
	glColor3f(0, 1, 0);
	glVertex2f(30-240, 0-160);
	glVertex2f(30-240, 140-160);
	glVertex2f(60-240, 140-160);

	glColor3f(1, 0, 0);
	glVertex2f(40-240, 20-160);
	glVertex2f(60-240, 0-160);
	glVertex2f(90-240, 140-160);
	glColor3f(0, 1, 0);
	glVertex2f(60-240, 0-160);
	glVertex2f(110-240, 120-160);
	glVertex2f(90-240, 140-160);

	glColor3f(0, 1, 0);
	glVertex2f(100-240, 0-160);
	glVertex2f(130-240, 30-160);
	glVertex2f(120-240, 140-160);
	glColor3f(1, 0, 0);
	glVertex2f(130-240, 30-160);
	glVertex2f(120-240, 140-160);
	glVertex2f(150-240, 170-160);

	glColor3f(0, 1, 0);
	glVertex2f(140-240, 0-160);
	glVertex2f(200-240, 170-160);
	glVertex2f(150-240, 105-160);
	glColor3f(1, 0, 0);
	glVertex2f(140-240, 0-160);
	glVertex2f(190-240, 60-160);
	glVertex2f(200-240, 170-160);

	glColor3f(0, 1, 0);
	glVertex2f(220-240, 0-160);
	glVertex2f(250-240, 160-160);
	glVertex2f(210-240, 120-160);
	glColor3f(1, 0, 0);
	glVertex2f(250-240, 160-160);
	glVertex2f(210-240, 120-160);
	glVertex2f(270-240, 0-160);

	glColor3f(0, 1, 0);
	glVertex2f(280-240, 0-160);
	glVertex2f(310-240, 140-160);
	glVertex2f(280-240, 140-160);
	glColor3f(1, 0, 0);
	glVertex2f(280-240, 0-160);
	glVertex2f(310-240, 0-160);
	glVertex2f(310-240, 140-160);

	glColor3f(0, 1, 0);
	glVertex2f(320-240, 20-160);
	glVertex2f(370-240, 140-160);
	glVertex2f(350-240, 160-160);
	glColor3f(1, 0, 0);
	glVertex2f(320-240, 20-160);
	glVertex2f(340-240, 0-160);
	glVertex2f(370-240, 140-160);

	glColor3f(0, 1, 0);
	glVertex2f(370-240, 110-160);
	glVertex2f(380-240, 0-160);
	glVertex2f(400-240, 140-160);
	glColor3f(1, 0, 0);
	glVertex2f(380-240, 0-160);
	glVertex2f(410-240, 30-160);
	glVertex2f(400-240, 140-160);

	glColor3f(0, 1, 0);
	glVertex2f(420-240, 80-160);
	glVertex2f(490-240, 80-160);
	glVertex2f(450-240, 160-160);
	glColor3f(1, 0, 0);
	glVertex2f(420-240, 80-160);
	glVertex2f(460-240, 0-160);
	glVertex2f(490-240, 80-160);
	glEnd();

	//Small Traingle Testbench
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(250-240, 280-160);
	glVertex2f(251-240, 280-160);
	glVertex2f(251-240, 281-160);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(255-240, 280-160);
	glVertex2f(257-240, 280-160);
	glVertex2f(257-240, 282-160);
	glEnd();
	//glDisable(GL_POLYGON_STIPPLE);
GLubyte pattern[4];
glGetPolygonStipple(pattern);
LOGIF("GetPolygonStipple(pattern)=%d\n", pattern[0]);
	glDisable(GL_POLYGON_SMOOTH);
	glDisable(GL_BLEND);	
	glFlush();
}

int main(int argc, char** argv)
{
    string file = "gl13-polygonstipple";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<3; i++) {
	string factor_name = get_enum_name(factors[i]);
        string filename = file + "_" + factor_name + ".bmp";
        display(factors[i]);
        LOGIF("filename=%s\n", filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
