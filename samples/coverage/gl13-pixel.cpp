/**
 * @file accum2.c
 * @testpoint glColorMask
 *
 */
#include "gl-util.h"

GLenum factors[] = {
	GL_COLOR,
	GL_DEPTH,
	GL_STENCIL
};
GLenum types[] = {
	GL_COLOR_INDEX,
	GL_STENCIL_INDEX,
	GL_DEPTH_COMPONENT,
	GL_RGB,
	GL_BGR,
	GL_RGBA,
	GL_BGRA,
	GL_RED,
	GL_GREEN,
	GL_BLUE,
	GL_ALPHA,
	GL_LUMINANCE,
	GL_LUMINANCE_ALPHA 
};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

/*	Create checkerboard image	*/
#define	checkImageWidth 64
#define	checkImageHeight 64
GLubyte checkImage[checkImageHeight][checkImageWidth][3];

static GLdouble zoomFactor = 1.0;
static GLint height;

void makeCheckImage(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
      }
   }
}

void init(void)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   makeCheckImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   height = (GLint) h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void motion(int x, int y, GLenum factor)
{
   static GLint screeny;
   
   screeny = height - (GLint) y;
   glRasterPos2i (x, screeny);
   glPixelZoom (zoomFactor, zoomFactor);
   glCopyPixels (0, 0, checkImageWidth, checkImageHeight, factor);
   glPixelZoom (1.0, 1.0);
   glFlush ();
}

bool setupGraphics(int w, int h)
{
    init();
    reshape(w,h);
    return true;
}

void renderFrame(GLenum type, GLenum factor)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(0, 0);
   glDrawPixels(checkImageWidth, checkImageHeight, type, 
                GL_UNSIGNED_BYTE, checkImage);
   motion(64,64,factor);
   glFlush();
}

int main(int argc, char** argv)
{
    string file = "gl13-pixel";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(types); i++) {
    for(int j=0; j<ARRAY_NUM(factors); j++) {
	    string factor_name = get_enum_name(factors[j]);
	    string type_name = get_enum_name(types[i]);
	    string filename = file + "-" + factor_name.c_str() + "-" + type_name.c_str() + ".bmp";
	    LOGIF("[%d]: filename=%s\n", i, filename.c_str());
            renderFrame(types[i],factors[i]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }}
    GBtest_deinit();

    return 0;
}
