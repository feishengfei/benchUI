/**
 * @file accum2.c
 * @testpoint glArrayElement glVertexPointer
 *
 */
#include "gl-util.h"
#include "limits.h"

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

static GLubyte texels0[32][32][4];
static GLubyte texels1[16][16][4];

void makeCheckImages(void)
{
   int i, j;
    
   for (i = 0; i < 32; i++) {
      for (j = 0; j < 32; j++) {
         texels0[i][j][0] = (GLubyte) i;
         texels0[i][j][1] = (GLubyte) j;
         texels0[i][j][2] = (GLubyte) (i*j)/255;
         texels0[i][j][3] = (GLubyte) 255;
      }
   }

   for (i = 0; i < 16; i++) {
      for (j = 0; j < 16; j++) {
         texels1[i][j][0] = (GLubyte) 255;
         texels1[i][j][1] = (GLubyte) i;
         texels1[i][j][2] = (GLubyte) j;
         texels1[i][j][3] = (GLubyte) 255;
      }
   }
}

void init(void)
{    
   GLuint texNames[2];

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeCheckImages();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(2, texNames);
   glBindTexture(GL_TEXTURE_2D, texNames[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, texels0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glBindTexture(GL_TEXTURE_2D, texNames[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, texels1);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   /*  Use the two texture objects to define two texture units
    *  for use in gl13-multitexturing  */
   glActiveTextureARB (GL_TEXTURE0_ARB);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texNames[0]);
   glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glMatrixMode (GL_TEXTURE);
      glLoadIdentity();
      glTranslatef(0.5f, 0.5f, 0.0f);
      glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
      glTranslatef(-0.5f, -0.5f, 0.0f);
   glMatrixMode (GL_MODELVIEW);
   glActiveTextureARB (GL_TEXTURE1_ARB);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texNames[1]);
   glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glBegin(GL_TRIANGLES);
   glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 0.0, 0.0);
   glMultiTexCoord2fARB (GL_TEXTURE1_ARB, 1.0, 0.0);
   glVertex2f(0.0, 0.0);
   glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 0.5, 1.0);
   glMultiTexCoord2fARB (GL_TEXTURE1_ARB, 0.5, 0.0);
   glVertex2f(50.0, 100.0);
   glMultiTexCoord2fARB (GL_TEXTURE0_ARB, 1.0, 0.0);
   glMultiTexCoord2fARB (GL_TEXTURE1_ARB, 1.0, 1.0);
   glVertex2f(100.0, 0.0);
   glEnd();
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      gluOrtho2D(0.0, 100.0, 0.0, 100.0 * (GLdouble)h/(GLdouble)w);
   else
      gluOrtho2D(0.0, 100.0 * (GLdouble)w/(GLdouble)h, 0.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
    string file = "gl13-multitex";
    GBtest_init(&argc,argv,file,DisplayMode);
    init ();
    reshape(WINDOW_W, WINDOW_H);
	    string filename = file + ".bmp";
	    LOGIF(" filename=%s\n", filename.c_str());
            display();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
