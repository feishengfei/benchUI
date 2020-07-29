/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

float rotate=0.0;

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

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
GLboolean paramb;
GLfloat paramf;

glGetBooleanv(GL_POLYGON_OFFSET_FILL, &paramb); 
LOGIF("get(GL_POLYGON_OFFSET_FILL)=%s\n",GET_BOOL(paramb));
glGetFloatv(GL_POLYGON_OFFSET_FACTOR, &paramf); 
LOGIF("get(GL_POLYGON_OFFSET_FACTOR):%f\n", paramf);
glGetFloatv(GL_POLYGON_OFFSET_UNITS, &paramf); 
LOGIF("get(GL_POLYGON_OFFSET_UNITS):%f\n", paramf);
}

void renderFrame()
{
    int i, j;
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    glPushMatrix ();
    glTranslatef(-0.9,0.0,0.0);
    rotate += 1;
    if(rotate > 360.0) rotate = 0.0;
    glRotatef(rotate, 0, 1, 0);
    //GL_CHECK(glDisable (GL_POLYGON_OFFSET_FILL));
    glColor4f (1.0, 0.0, 0.0,1.0);
    glRectf(-1.0, -1.0, 1.0, 1.0);
    //glEnable(GL_POLYGON_OFFSET_FILL);
    //glPolygonOffset(1.0, 0.0);
    glColor4f (0.0, 1.0, 0.0,1.0);
    glRectf(-0.5, -0.5, 1.0, 1.0);
    glPopMatrix ();

    glPushMatrix ();
    glTranslatef(0.9,0.0,0.0);
    rotate += 1;
    if(rotate > 360.0) rotate = 0.0;
    glRotatef(rotate, 0, 1, 0);
    GL_CHECK(glDisable (GL_POLYGON_OFFSET_FILL));
    glColor4f (1.0, 0.0, 0.0,1.0);
    glRectf(-1.0, -1.0, 1.0, 1.0);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 0.0);
    glColor4f (0.0, 1.0, 0.0,1.0);
    glRectf(-0.5, -0.5, 1.0, 1.0);
    glPopMatrix ();
getdata();
    GL_CHECK(glFlush());
    GL_CHECK(glDisable (GL_DEPTH_TEST));
    GL_CHECK(glDisable (GL_POLYGON_OFFSET_FILL));
}

int main(int argc, char** argv)
{
    string file = "gl13-polygonoffset";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    while(rotate < 720.0)
    {
        renderFrame();
        char ss[2];
        sprintf(ss, "_%d", int(rotate));
        string filename = file + ss + ".bmp";
        LOGIF("filename=%s\n", filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
