/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLfloat ctrlpoints[4][4][3] = {
   {{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0}, 
    {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}}, 
   {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0}, 
    {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}}, 
   {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0}, 
    {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}}, 
   {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0}, 
    {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
};

GLenum modes[] = {
	GL_POINT,
	GL_LINE,
	GL_FILL
};

void display(GLenum mode)
{
   int i, j;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);
   glPointSize(3.0);
   glPushMatrix ();
   glRotatef(85.0, 1.0, 1.0, 1.0);
   glEvalMesh2(mode, 0, 20, 0, 20);
   glPopMatrix ();
   glFlush();
}

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpoints[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-4.0, 4.0, -4.0*(GLfloat)h/(GLfloat)w, 
              4.0*(GLfloat)h/(GLfloat)w, -4.0, 4.0);
   else
      glOrtho(-4.0*(GLfloat)w/(GLfloat)h, 
              4.0*(GLfloat)w/(GLfloat)h, -4.0, 4.0, -4.0, 4.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
    string file = "gl13-evalmesh2";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(modes); i++) { 
	    printf("11111\n");
            string mode_name = get_enum_name(modes[i]);
	    printf("22222\n");
	    string filename = file + "-" + mode_name + ".bmp";
	    printf("33333\n");
	    printf("[%d]: filename=%s\n", i, filename.c_str());
            init();
            display(modes[i]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
