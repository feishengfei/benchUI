/**
 * @file accum2.c
 * @testpoint glColorMask
 *
 */
#include "gl-util.h"

GLfloat vertices[] = {
	-2.0, 2.0,
	0.0, -2.0,
	2.0, 2.0
};

GLfloat colors[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0
};

GLboolean mask[2] = {GL_TRUE,GL_FALSE};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho (-3.0f, 3.0f, -3.0f*h/w, 3.0f*h/w, -3.0f, 3.0f);
	}
	else {
		glOrtho (-3.0f*w/h, 3.0f*w/h, -3.0f, 3.0f, -3.0f, 3.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getdata()
{
GLfloat paramf4[4];

glGetFloatv(GL_COLOR_WRITEMASK, paramf4); 
LOGIF("get(GL_COLOR_WRITEMASK):\n");
for(int i=0; i<4; i++)
	LOGIF("%f ",paramf4[i]);
}

void renderFrame(GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glColorMask(r,g,b,a));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
getdata();
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-colormask";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
        for(int m=0; m<2; m++) {
        for(int n=0; n<2; n++) {
	    char ss[10];
	    sprintf(ss, "_%d_%d_%d_%d", i, j, m, n);
	    string filename = file + ss + ".bmp";
	    LOGIF("[%d_%d_%d_%d]: filename=%s\n", i, j, m, n, filename.c_str());
            renderFrame(mask[i],mask[j],mask[m],mask[n]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }}}}
    GBtest_deinit();

    return 0;
}
