/**
 * @file accum2.c
 * @testpoint glColor glVertex
 *
 */
#include "gl-util.h"
#include "limits.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

#define NUMCOLORS 32
#define RAMPSTART 16

static void init(void)
{
   int i;

   glEnable(GL_DEPTH_TEST);

   for (i = 0; i < NUMCOLORS; i++) {
      GLfloat shade;
      shade = (GLfloat) (NUMCOLORS-i)/(GLfloat) NUMCOLORS;
      glutSetColor (RAMPSTART + i, shade, shade, shade);
   }
   glEnable(GL_FOG);

   glFogi (GL_FOG_MODE, GL_LINEAR);
   glFogi (GL_FOG_INDEX, NUMCOLORS);
   glFogf (GL_FOG_START, 1.0);
   glFogf (GL_FOG_END, 6.0);
   glHint (GL_FOG_HINT, GL_NICEST);
   glClearIndex((GLfloat) (NUMCOLORS+RAMPSTART-1));
}

static void renderSphere (GLfloat x, GLfloat y, GLfloat z)
{
   glPushMatrix();
   glTranslatef (x, y, z);
   glutWireSphere(0.4, 16, 16);
   glPopMatrix();
}

/*  display() draws 5 spheres at different z positions.
 */
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glIndexi (RAMPSTART);

   renderSphere (-2., -0.5, -1.0);
   renderSphere (-1., -0.5, -2.0);
   renderSphere (0., -0.5, -3.0);
   renderSphere (1., -0.5, -4.0);
   renderSphere (2., -0.5, -5.0);

   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-2.5, 2.5, -2.5*(GLfloat)h/(GLfloat)w,
         2.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-2.5*(GLfloat)w/(GLfloat)h,
         2.5*(GLfloat)w/(GLfloat)h, -2.5, 2.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity ();
}

int main(int argc, char** argv)
{
    string file = "gl13-index";
    GBtest_init(&argc,argv,file,DisplayMode);
    init();
    reshape(WINDOW_W, WINDOW_H);
    display();
    string filename = file + ".bmp";
    LOGIF("filename=%s\n", filename.c_str());
    save2bmp(filename.c_str());
    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
