/**
 * @file accum2.c
 * @testpoint glColorMask
 *
 */
#include "gl-util.h"

GLboolean flag[] = {GL_TRUE,GL_FALSE,GL_TRUE};
GLfloat vertex[] = {-10.0f, 0.0f,  -15.0f,-10.0f,  10.0f, 0.0f};

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

void getdata() 
{
GLvoid **param;

    GL_CHECK(glGetPointerv(GL_EDGE_FLAG_ARRAY, param));
    LOGIF("GetPointerv(GL_EDGE_FLAG_ARRAY): %x\n", *param);
}

void renderFrame()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	glColor3f(0.0,1.0,0.0);
	glPointSize(8);
	//glBegin(GL_POLYGON);
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_EDGE_FLAG_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertex));
    GL_CHECK(glEdgeFlagPointer(0, flag));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 3));
	glFlush();
getdata();
    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glDisableClientState(GL_EDGE_FLAG_ARRAY));
}

int main(int argc, char** argv)
{
    string file = "gl13-edgeflagpointer";
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
