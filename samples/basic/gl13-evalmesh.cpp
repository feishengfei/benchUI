/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLdouble ctrlpoints[4][3] = {
	{ -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0}, 
	{2.0, -4.0, 0.0}, {4.0, 4.0, 0.0}};

GLenum modes[] = {
	GL_POINT,
	GL_LINE
};

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glMap1d(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
}

void display(GLenum mode)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glMapGrid1f(30, 00.f, 1.0f);
   glEvalMesh1(mode, 0, 30);
   glFlush();
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
    string file = "gl13-evalmesh1d";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(modes); i++) { 
            string mode_name = get_enum_name(modes[i]);
	    string filename = file + "-" + mode_name + ".bmp";
	    LOGIF("[%d]: filename=%s\n", i, filename.c_str());
            init();
            display(modes[i]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
