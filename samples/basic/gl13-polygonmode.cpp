/**
 * @file gl13-polygonmode.cpp
 * @testpoint glPolygonMode
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLenum faces[] = {
	GL_FRONT,
        GL_BACK,
        GL_FRONT_AND_BACK
};

GLenum modes[] = {
	GL_POINT,
        GL_LINE,
        GL_FILL
};

float rotate=0.0;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0,4.0,-4.0,4.0,-4.0,4.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0,0,0,0.0);
	glColorMask(1,1,1,1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);//¿ªÆôÉî¶È²âÊÔ
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
        return true;
}

static void drawPyramid(void)
{
	glPointSize(5);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.0f,  1.0f,  0.0f);
	glColor3f(0.0,1.0,0.0);
	glVertex3f(1.0f, -1.0f, 1.0f);  
	glColor3f(0.0,0.0,1.0);
	glVertex3f(1.0f, -1.0f, -1.0f);	  
	glColor3f(0.4,0.7,0.5);
	glVertex3f(-1.0f, -1.0f, -1.0);	  
	glColor3f(0.3,0.2,0.6);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glColor3f(0.2,0.0,0.5);
	glVertex3f(1.0f,  -1.0f,   1.0f);
	glEnd();
}

void display(GLenum face, GLenum mode)
{
	glPolygonMode(face, mode);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.2,- 3.0);
	drawPyramid();
	glFlush();
}

int main(int argc, char** argv)
{
    string file = "gl13-polygonmode";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(faces); i++) {
        for(int j=0; j<ARRAY_NUM(modes); j++) {
            display(faces[i], modes[j]);
            string mode_name = get_enum_name(modes[j]);
            string face_name = get_enum_name(faces[i]);
            string filename = file + "-" + face_name + "-" + mode_name + ".bmp";
            LOGIF("[%d_%d]: filename=%s\n", i, j, filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
        }
    }
    GBtest_deinit();

    return 0;
}
