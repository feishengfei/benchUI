/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

/*  Initialize lighting.
 */
void init(void)
{
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}

/* Draw a few lines and two points, one of which will 
 * be clipped.  If in feedback mode, a passthrough token 
 * is issued between the each primitive.
 */
void drawGeometry (GLenum mode)
{
   glBegin (GL_LINE_STRIP);
   glNormal3f (0.0, 0.0, 1.0);
   glVertex3f (30.0, 30.0, 0.0);
   glVertex3f (50.0, 60.0, 0.0);
   glVertex3f (70.0, 40.0, 0.0);
   glEnd ();
   if (mode == GL_FEEDBACK)
      glPassThrough (1.0);
   glBegin (GL_POINTS);
   glVertex3f (-100.0, -100.0, -100.0);  /*  will be clipped  */
   glEnd ();
   if (mode == GL_FEEDBACK)
      glPassThrough (2.0);
   glBegin (GL_POINTS);
   glNormal3f (0.0, 0.0, 1.0);
   glVertex3f (50.0, 50.0, 0.0);
   glEnd ();
}

/* Write contents of one vertex to stdout.	*/
void print3DcolorVertex (GLint size, GLint *count, 
                         GLfloat *buffer)
{
   int i;

   LOGIF ("  ");
   for (i = 0; i < 7; i++) {
      LOGIF ("%4.2f ", buffer[size-(*count)]);
      *count = *count - 1;
   }
   LOGIF ("\n");
}

/*  Write contents of entire buffer.  (Parse tokens!)	*/
void printBuffer(GLint size, GLfloat *buffer)
{
   GLint count;
   GLfloat token;

   count = size;
   while (count) {
      token = buffer[size-count]; count--;
      if (token == GL_PASS_THROUGH_TOKEN) {
         LOGIF ("GL_PASS_THROUGH_TOKEN\n");
         LOGIF ("  %4.2f\n", buffer[size-count]);
         count--;
      }
      else if (token == GL_POINT_TOKEN) {
         LOGIF ("GL_POINT_TOKEN\n");
         print3DcolorVertex (size, &count, buffer);
      }
      else if (token == GL_LINE_TOKEN) {
         LOGIF ("GL_LINE_TOKEN\n");
         print3DcolorVertex (size, &count, buffer);
         print3DcolorVertex (size, &count, buffer);
      }
      else if (token == GL_LINE_RESET_TOKEN) {
         LOGIF ("GL_LINE_RESET_TOKEN\n");
         print3DcolorVertex (size, &count, buffer);
         print3DcolorVertex (size, &count, buffer);
      }
   }
}

void display(void)
{
   GLfloat feedBuffer[1024];
   GLint size;

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho (0.0, 100.0, 0.0, 100.0, 0.0, 1.0);

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   drawGeometry (GL_RENDER);

   glFeedbackBuffer (1024, GL_3D_COLOR, feedBuffer);
   (void) glRenderMode (GL_FEEDBACK);
   drawGeometry (GL_FEEDBACK);

   size = glRenderMode (GL_RENDER);
   printBuffer (size, feedBuffer);
}


int main(int argc, char** argv)
{
    string file = "gl13-passthough";
    GBtest_init(&argc,argv,file,DisplayMode);
    init();
        display();
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
