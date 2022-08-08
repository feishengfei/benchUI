/**
 * @file accum2.c
 * @testpoint glColorMask
 *
 */
#include "gl-util.h"

GLboolean flag[] = {GL_TRUE,GL_FALSE,GL_TRUE};
GLfloat vertex[] = {-10.0f, 0.0f,  -15.0f,-10.0f,  10.0f, 0.0f};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

void listC(int w, int h)
{
	if(h == 0)	h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2,2,-2,2,-2,2);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	glClearColor(0.0,0.0,0.0,0.0);
	glNewList(1,GL_COMPILE);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(0.0,0.0);
	glColor3f(0.0,1.0,0.0);
	glVertex2f(1.0,0.0);
	glColor3f(0.0,0.0,1.0);
	glVertex2f(1.0,1.0);
	glEndList(); 
	glShadeModel (GL_SMOOTH);

	glClear (GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glCallList(1);
	glEnd();

	glFlush();
}

void listCE(int w, int h)
{
	glClear (GL_COLOR_BUFFER_BIT);

	glClearColor(0.0,0.0,0.0,0.0);
	glNewList(1,GL_COMPILE_AND_EXECUTE);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(0.0,0.0);
	glColor3f(0.0,1.0,0.0);
	glVertex2f(1.0,0.0);
	glColor3f(0.0,0.0,1.0);
	glVertex2f(1.0,1.0);
	glEndList(); 
	glShadeModel (GL_SMOOTH);

	glTranslatef(-1.0,0.0,0.0);
	glBegin(GL_TRIANGLES);
	glCallList(1);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
    string file = "gl13-calllist";
    GBtest_init(&argc,argv,file,DisplayMode);
    listC(WINDOW_W, WINDOW_H);
    string filename = file + "-GL_COMPILE.bmp";
    LOGIF("filename=%s\n", filename.c_str());
    save2bmp(filename.c_str());
    glutSwapBuffers();

    listCE(WINDOW_W, WINDOW_H);
    filename = file + "-GL_COMPILE_AND_EXECUTE.bmp";
    LOGIF("filename=%s\n", filename.c_str());
    save2bmp(filename.c_str());
    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
