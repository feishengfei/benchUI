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

#define	checkImageWidth 128
#define	checkImageHeight 128
GLubyte checkImage[checkImageHeight][checkImageWidth][3];

void makeCheckImage()
{
   int i, j, c, k, cnt=0;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) (255 - c);
         checkImage[i][j][2] = (GLubyte) 0;
      }
   }
}

GLubyte  *pixels;
GLsizei   width, height;

void display(void)
{
   makeCheckImage();
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i( 1, 1 );
   glDrawPixels(checkImageWidth, checkImageHeight, GL_RGB, GL_UNSIGNED_BYTE, checkImage );
   glFlush();
}

void reshapef(int w, int h)
{
   GLfloat  m[16] = {
      0.0, 1.0, 0.0, 0.0,
      0.0, 0.0, 1.0, 0.0,
      1.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0
   };

   glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glMatrixMode( GL_COLOR );
   glLoadMatrixf( m );
   glMatrixMode( GL_MODELVIEW );

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, w, 0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void reshaped(int w, int h)
{
   GLdouble  m[16] = {
      0.0, 0.0, 1.0, 0.0,
      0.0, 1.0, 0.0, 0.0,
      1.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 1.0
   };

   glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glMatrixMode( GL_COLOR );
   glLoadMatrixd( m );
   glMatrixMode( GL_MODELVIEW );

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, w, 0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    string file = "gl13-colormatrix";
    GBtest_init(&argc,argv,file,DisplayMode);
        reshapef(WINDOW_W, WINDOW_H);
        string filename = file + "-f.bmp";
        printf("filename=%s\n", filename.c_str());
        display();
        save2bmp(filename.c_str());
	glutSwapBuffers();

        reshaped(WINDOW_W, WINDOW_H);
        filename = file + "-d.bmp";
        printf("filename=%s\n", filename.c_str());
        display();
        save2bmp(filename.c_str());
	glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
