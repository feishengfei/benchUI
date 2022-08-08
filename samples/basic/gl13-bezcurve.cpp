/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLfloat ctrlpoints[4][3] = {
	{ -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0}, 
	{2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};
GLfloat ctrlpoints4[4][4] = {
	{ -4.0, 4.0, 0.0, 1.0}, { -2.0, -4.0, 0.0, 1.0}, 
	{2.0, 4.0, 0.0, 1.0}, {4.0, -4.0, 0.0, 1.0}};
GLfloat ctrlcolors[4][4] = {
	{ 1.0, 1.0, 0.0, 0.0}, { 0.0, 1.0, 0.0, 0.0}, 
	{0.0, 1.0, 1.0, 0.0}, { 0.0, 0.0, 1.0, 0.0}};

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glMap1f(GL_MAP1_COLOR_4, 0, 1, 4, 4, &ctrlcolors[0][0]);
   glEnable(GL_MAP1_COLOR_4);
}

void init4(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glMap1f(GL_MAP1_VERTEX_4, 0.0, 1.0, 4, 4, &ctrlpoints4[0][0]);
   glMap1f(GL_MAP1_COLOR_4, 0, 1, 4, 4, &ctrlcolors[0][0]);
   glEnable(GL_MAP1_VERTEX_4);
   glEnable(GL_MAP1_COLOR_4);
}

void display(void)
{
   int i;

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glMap1f(GL_MAP1_COLOR_4, 0, 1, 4, 4, &ctrlcolors[0][0]);
   glEnable(GL_MAP1_COLOR_4);

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++) 
         glEvalCoord1f((GLfloat) i/30.0);
   glEnd();
   /* The following code displays the control points as dots. */
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 4; i++) 
         glVertex3fv(&ctrlpoints[i][0]);
   glEnd();
   glFlush();
   glDisable(GL_MAP1_VERTEX_3);
   glDisable(GL_MAP1_COLOR_4);
}

void display4(void)
{
   int i;

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glMap1f(GL_MAP1_VERTEX_4, 0.0, 1.0, 4, 4, &ctrlpoints4[0][0]);
   glEnable(GL_MAP1_VERTEX_4);

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++) 
         glEvalCoord1f((GLfloat) i/30.0);
   glEnd();
   /* The following code displays the control points as dots. */
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 4; i++) 
         glVertex4fv(&ctrlpoints4[i][0]);
   glEnd();
   glFlush();
   glDisable(GL_MAP1_VERTEX_4);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
               5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
   else
      glOrtho(-5.0*(GLfloat)w/(GLfloat)h, 
               5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
    string file = "gl13-bezcurve";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
	    string filename = file + "3.bmp";
	    LOGIF("[]: filename=%s\n", filename.c_str());
//            init();
            display();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();

	    filename = file + "4.bmp";
	    LOGIF("[]: filename=%s\n", filename.c_str());
//            init4();
            display4();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
