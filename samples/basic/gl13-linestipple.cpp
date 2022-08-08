/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(4);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex2f(-29,-5.5);
	glVertex2f(-29,-20); 
	glVertex2f(-29,-20);
	glVertex2f(-16,-20);
	glVertex2f(-16,-20);
	glVertex2f(-16,-5.5);
	glVertex2f(-16,-5.5);
	glVertex2f(-29,-5.5);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-29,-5.5);
	glVertex2f(-23,6.5);
	glVertex2f(-23,6.5);
	glVertex2f(-10,6.5);
	glVertex2f(-10,6.5);
	glVertex2f(-16,-5.5);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-10,6.5);
	glVertex2f(-10,-8);
	glVertex2f(-10,-8);
	glVertex2f(-16,-20);
	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xff00);
	glBegin(GL_LINES);
	glVertex2f(-29,-20);
	glVertex2f(-23,-8);
	glVertex2f(-23,-8);
	glVertex2f(-23,6.5);
	glVertex2f(-23,-8);
	glVertex2f(-10,-8);
	glEnd();

	/**********  four  ************/
	glColor3f(0.0,0.8,1.0);
	glBegin(GL_LINES);
	glVertex2f(23,20.5);
	glVertex2f(16,-12.5);
	glVertex2f(16,-12.5);
	glVertex2f(19.5,-27.5);
	glVertex2f(19.5,-27.5);
	glVertex2f(23,20.5);
	glVertex2f(19.5,-27.5);
	glVertex2f(30,-12.5);
	glVertex2f(30,-12.5);
	glVertex2f(23,20.5);
	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xff00);
	glBegin(GL_LINES);
	glVertex2f(16,-12.5);
	glVertex2f(30,-12.5);
	glEnd();

	/**********  six  ************/
	glShadeModel (GL_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xff00);
	glBegin(GL_LINES);
	glColor3f(1.0,0.5,0.5);
	glVertex2f(-1.5,23.5);
	glColor3f(0.0,0.5,0.5);
	glVertex2f(-1.5,-14);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0,0.5,0.5);
	glVertex2f(6,22);
	glColor3f(1.0,0.5,0.5);
	glVertex2f(6,-15.5);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0,0.5,0.5);
	glVertex2f(-6.5,19);
	glVertex2f(-1.5,23.5);
	glVertex2f(6,22);
	glVertex2f(9,16.5);
	glVertex2f(4,12);
	glVertex2f(-3.5,13.5);
	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0xff00);
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0,0.5,0.5);
	glVertex2f(-6.5,-20);
	glColor3f(0.0,0.5,0.5);
	glVertex2f(-1.5,-14);
	glColor3f(1.0,0.5,0.5);
	glVertex2f(6,-15.5);
	glColor3f(0.0,0.5,0.5);
	glVertex2f(9,-23);
	glEnd();


	glBegin(GL_LINE_STRIP);
	glColor3f(1.0,0.5,0.5);
	glVertex2f(-6.5,-20);
	glColor3f(0.0,0.5,0.5);
	glVertex2f(-3.5,-27.5);
	glColor3f(1.0,0.5,0.5);
	glVertex2f(4,-29);
	glColor3f(0.0,0.5,0.5);
	glVertex2f(9,-23);		
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1.0,0.5,0.5);
	glVertex2f(-6.5,19);
	glVertex2f(-6.5,-20);     
	glVertex2f(-3.5,13.5);
	glVertex2f(-3.5,-27.5);
	glVertex2f(4,12);
	glVertex2f(4,-29);
	glVertex2f(9,16.5);
	glVertex2f(9,-23);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glFlush(); 
}

void reshape(int w, int h)
{
	glViewport(0, 0, 480, 320);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-30, 30, -30, 30, 0, 30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
    string file = "gl13-linestipple";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
    init();
        display();
        string filename = file + ".bmp";
        LOGIF("filename=%s\n", filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
