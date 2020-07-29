/**
 * @file accum2.c
 * @testpoint glColorMask
 *
 */
#include "gl-util.h"

GLboolean mask[2] = {GL_TRUE,GL_FALSE};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

bool setupGraphics(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20,20,-20,20,-20,20);
	glMatrixMode(GL_MODELVIEW);
	glScalef(0.5,0.5,0.5);
	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
    return true;
}

void renderFrame(GLboolean mask)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glColor3f(0.0,1.0,0.0);
	glPointSize(8);
	//glBegin(GL_POLYGON);
	glBegin(GL_TRIANGLE_FAN);
	glEdgeFlag(GL_TRUE);
	glVertex2f(-10.0f, 0.0f);
	glEdgeFlag(mask);
	glVertex2f(-15.0f,-10.0f);
	glEdgeFlag(GL_TRUE);
	glVertex2f(10.0f, 0.0f);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
    string file = "gl13-edgeflag";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<2; i++) {
	char ss[2];
	    sprintf(ss, "-%d", mask[i]);
	    string filename = file + ss + ".bmp";
	    LOGIF("[%d]: filename=%s\n", i, filename.c_str());
            renderFrame(mask[i]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
