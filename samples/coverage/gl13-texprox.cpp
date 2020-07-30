/**
 * @file accum2.c
 * @testpoint glArrayElement glVertexPointer
 *
 */
#include "gl-util.h"
#include "limits.h"

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

void init(void) 
{
   GLint proxyComponents;

   glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA8,
                64, 64, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, NULL);
   glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, 
                            GL_TEXTURE_COMPONENTS, &proxyComponents);
   printf ("proxyComponents are %d\n", proxyComponents);
   if (proxyComponents == GL_RGBA8)
      printf ("proxy allocation succeeded\n");
   else
      printf ("proxy allocation failed\n");

   glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA16,
                2048, 2048, 0,
                GL_RGBA, GL_UNSIGNED_SHORT, NULL);
   glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, 
                            GL_TEXTURE_COMPONENTS, &proxyComponents);
   printf ("proxyComponents are %d\n", proxyComponents);
   if (proxyComponents == GL_RGBA16)
      printf ("proxy allocation succeeded\n");
   else
      printf ("proxy allocation failed\n");
}

void display(void)
{
   exit(0);
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
}

int main(int argc, char** argv)
{
    string file = "gl13-texprox";
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
