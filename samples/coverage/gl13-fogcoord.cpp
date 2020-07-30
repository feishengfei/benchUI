/*
 *  colormatix.c
 *  This program uses the color matrix to exchange the color channels of
 *  an image.
 *
 *    Red   -> Green
 *    Green -> Blue
 *    Blue  -> Red
 *
 */

#include "gl-util.h"
#include <cstring>

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

static GLfloat f1, f2, f3;

/*  Initialize fog
 */
static void init(void)
{
   GLfloat fogColor[4] = {0.0, 0.25, 0.25, 1.0};
   f1 = 1.0f;
   f2 = 5.0f;
   f3 = 10.0f;

   glEnable(GL_FOG);
   glFogi (GL_FOG_MODE, GL_EXP);
   glFogfv (GL_FOG_COLOR, fogColor);
   glFogf (GL_FOG_DENSITY, 0.25);
   glHint (GL_FOG_HINT, GL_DONT_CARE);
   glFogi(GL_FOG_COORDINATE_SOURCE_EXT, GL_FOG_COORDINATE_EXT);
   glClearColor(0.0, 0.25, 0.25, 1.0);  /* fog color */
}

/* display() draws a triangle at an angle.
 */
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f (1.0f, 0.75f, 0.0f);
   glBegin (GL_TRIANGLES);
   glFogCoordf(f1); 
   glVertex3f (2.0f, -2.0f, 0.0f);
   glFogCoordf(f2); 
   glVertex3f (-2.0f, 0.0f, -5.0f);
   glFogCoordf(f3); 
   glVertex3f (0.0f, 2.0f, -10.0f);
   glEnd();

   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective (45.0, 1.0, 0.25, 25.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
   glTranslatef (0.0, 0.0, -5.0);
}

int main(int argc, char** argv)
{
    string file = "gl13-fogcoord";
    GBtest_init(&argc,argv,file,DisplayMode);
    init();
    reshape(WINDOW_W, WINDOW_H);
	    string filename = file + ".bmp";
	    LOGIF("filename=%s\n", filename.c_str());
            display();
        save2bmp(filename.c_str());
	glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
