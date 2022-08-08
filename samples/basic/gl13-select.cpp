/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

/* draw a triangle with vertices at (x1, y1), (x2, y2) 
 * and (x3, y3) at z units away from the origin.
 */
void drawTriangle (GLfloat x1, GLfloat y1, GLfloat x2, 
    GLfloat y2, GLfloat x3, GLfloat y3, GLfloat z)
{
   glBegin (GL_TRIANGLES);
   glVertex3f (x1, y1, z);
   glVertex3f (x2, y2, z);
   glVertex3f (x3, y3, z);
   glEnd ();
}

/* draw a rectangular box with these outer x, y, and z values */
void drawViewVolume (GLfloat x1, GLfloat x2, GLfloat y1, 
                     GLfloat y2, GLfloat z1, GLfloat z2)
{
   glColor3f (1.0, 1.0, 1.0);
   glBegin (GL_LINE_LOOP);
   glVertex3f (x1, y1, -z1);
   glVertex3f (x2, y1, -z1);
   glVertex3f (x2, y2, -z1);
   glVertex3f (x1, y2, -z1);
   glEnd ();

   glBegin (GL_LINE_LOOP);
   glVertex3f (x1, y1, -z2);
   glVertex3f (x2, y1, -z2);
   glVertex3f (x2, y2, -z2);
   glVertex3f (x1, y2, -z2);
   glEnd ();

   glBegin (GL_LINES);	/*  4 lines	*/
   glVertex3f (x1, y1, -z1);
   glVertex3f (x1, y1, -z2);
   glVertex3f (x1, y2, -z1);
   glVertex3f (x1, y2, -z2);
   glVertex3f (x2, y1, -z1);
   glVertex3f (x2, y1, -z2);
   glVertex3f (x2, y2, -z1);
   glVertex3f (x2, y2, -z2);
   glEnd ();
}

/* drawScene draws 4 triangles and a wire frame
 * which represents the viewing volume.
 */
void drawScene (void)
{
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective (40.0, 4.0/3.0, 1.0, 100.0);

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
   gluLookAt (7.5, 7.5, 12.5, 2.5, 2.5, -5.0, 0.0, 1.0, 0.0);
   glColor3f (0.0, 1.0, 0.0);	/*  green triangle	*/
   drawTriangle (2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -5.0);
   glColor3f (1.0, 0.0, 0.0);	/*  red triangle	*/
   drawTriangle (2.0, 7.0, 3.0, 7.0, 2.5, 8.0, -5.0);
   glColor3f (1.0, 1.0, 0.0);	/*  yellow triangles	*/
   drawTriangle (2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -1.0);
   drawTriangle (2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -9.0);
   drawViewVolume (0.0, 5.0, 0.0, 5.0, 0.0, 10.0);
}

/* processHits prints out the contents of the selection array
 */
void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint names, *ptr;

   printf ("hits = %d\n", hits);
   ptr = (GLuint *) buffer;
   for (i = 0; i < hits; i++) {	/*  for each hit  */
      names = *ptr;
      printf (" number of names for hit = %d\n", names); ptr++;
      printf("  z1 is %g;", (float) *ptr/0x7fffffff); ptr++;
      printf(" z2 is %g\n", (float) *ptr/0x7fffffff); ptr++;
      printf ("   the name is ");
      for (j = 0; j < names; j++) {	/*  for each name */
         printf ("%d ", *ptr); ptr++;
      }
      printf ("\n");
   }
}

/* selectObjects "draws" the triangles in selection mode, 
 * assigning names for the triangles.  Note that the third
 * and fourth triangles share one name, so that if either 
 * or both triangles intersects the viewing/clipping volume, 
 * only one hit will be registered.
 */
#define BUFSIZE 512

void getdata()
{
	void * params;
	glGetPointerv(GL_SELECTION_BUFFER_POINTER, &params);
	LOGIF("GetPointerv(GL_SELECTION_BUFFER_POINTER)=0x%x\n", params);
}

void selectObjects(void)
{
   GLuint selectBuf[BUFSIZE];
   GLint hits;

   glSelectBuffer (BUFSIZE, selectBuf);
   (void) glRenderMode (GL_SELECT);

   glInitNames();
   glPushName(0);

   glPushMatrix ();
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho (0.0, 5.0, 0.0, 5.0, 0.0, 10.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
   glLoadName(1);
   drawTriangle (2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -5.0);
   glLoadName(2);
   drawTriangle (2.0, 7.0, 3.0, 7.0, 2.5, 8.0, -5.0);
   glLoadName(3);
   drawTriangle (2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -1.0);
   drawTriangle (2.0, 2.0, 3.0, 2.0, 2.5, 3.0, -9.0);
   glPopMatrix ();
   glFlush ();

   hits = glRenderMode (GL_RENDER);
   processHits (hits, selectBuf);
} 

void init (void) 
{
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
}

void display(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   drawScene ();
   selectObjects ();
   getdata();
   glFlush();
}

int main(int argc, char** argv)
{
    string file = "transform";
    GBtest_init(&argc,argv,file,DisplayMode);
    init();
    display();
    string filename = file + ".bmp";
    LOGIF("filename=%s\n", filename.c_str());
    save2bmp(filename.c_str());
    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
