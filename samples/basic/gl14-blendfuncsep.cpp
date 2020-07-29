/**
 * @file gl14-blendfuncsep.cpp
 * @testpoint glBlendFuncSeparate
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLenum factors[] = {
	GL_ZERO,
	GL_ONE,
	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
	GL_CONSTANT_COLOR,
	GL_ONE_MINUS_CONSTANT_COLOR,
	GL_CONSTANT_ALPHA,
	GL_ONE_MINUS_CONSTANT_ALPHA,
	GL_SRC_ALPHA_SATURATE
};

static void drawLeftTriangle(void)
{
	GLfloat vertices[] = {0.1, 0.9, 0.0,
			0.1, 0.1, 0.0,
			0.7, 0.5, 0.0};

	//glColor4f(1.0, 1.0, 0.0, 0.75);
	glColor4f(1.0, 1.0, 0.0, 0.75);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

static void drawRightTriangle(void)
{
	GLfloat vertices[] = {0.9, 0.9, 0.0,
			0.3, 0.5, 0.0,
			0.9, 0.1, 0.0};

	//glColor4f(0.0, 1.0, 1.0, 0.75);
	glColor4f(0.0, 1.0, 1.0, 0.25);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void renderFrame(GLenum src_factor_rgb, GLenum dst_factor_rgb, GLenum src_factor_a, GLenum dst_factor_a)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT);

   glEnable (GL_BLEND);
   glBlendColor(0.1,0.5,0.3,0.4);
   glBlendFuncSeparate (src_factor_rgb, dst_factor_rgb, src_factor_a, dst_factor_a);
   glShadeModel (GL_FLAT);

   drawLeftTriangle();
   drawRightTriangle();

   GL_CHECK(glFlush());
   GL_CHECK(glDisable(GL_BLEND));
}

void setupGraphics(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h) 
      gluOrtho2D (0.0, 1.0, 0.0, 1.0*(GLfloat)h/(GLfloat)w);
   else 
      gluOrtho2D (0.0, 1.0*(GLfloat)w/(GLfloat)h, 0.0, 1.0);
}

int main(int argc, char** argv)
{
    string file = "gl14-blendfuncsep";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
    	for(int j=0; j<ARRAY_NUM(factors); j++) {
	    for(int m=0; m<ARRAY_NUM(factors); m++) {
    		for(int n=0; n<ARRAY_NUM(factors); n++) {
		if(n == 10||j==10) 
		printf("Jump");
		else {
	        renderFrame(factors[i], factors[j], factors[m], factors[n]);
		string src_rgb_name=get_blending_name(factors[i]);
		string dst_rgb_name=get_blending_name(factors[j]);
		string src_a_name=get_blending_name(factors[m]);
		string dst_a_name=get_blending_name(factors[n]);
		string filename="demo_srcrgb"+src_rgb_name+"_dstrgb"+dst_rgb_name+"srca"+src_a_name+"_dsta"+dst_a_name+".bmp";
		LOGIF("%d %d %d %d:filename=%s\n",i,j,m,n,filename.c_str());
	save2bmp(filename.c_str());
	glutSwapBuffers();
            }}}
	}
    }
    GBtest_deinit();

    return 0;
}
