/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

GLfloat triVertex[] = {
	0.0,0.0,0.0,
	-2.0,-2.0,-1.0,
	1.0,0.5,2.0,
};

GLfloat lineColor[] = {
	1.0,0.0,0.0,
	1.0,0.0,0.0,
	1.0,1.0,1.0,
	1.0,1.0,1.0,
	0.0,1.0,0.0,
	0.0,1.0,0.0
};

GLfloat lineVertex[] = {
	-5.0,0.0,0.0,
	5.0,0.0,0.0,
	0.0,-5.0,0.0,
	0.0,5.0,0.0,
	0.0,0.0,-5.0,
	0.0,0.0,5.0,
};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

bool setupGraphicsO(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0,-5.0, 5.0, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

bool setupGraphicsF(int w, int h)
{
    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glMatrixMode(GL_PROJECTION));
    GL_CHECK(glLoadIdentity());
    GL_CHECK(glFrustum(-1.0,1.0,-1.0,1.0,1.0,5.0));
    GL_CHECK(glMatrixMode(GL_MODELVIEW));
    GL_CHECK(glLoadIdentity());
    return true;
}

void renderFrame()
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0,0.0,-5.0);
	glLineWidth(5.0);
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, lineVertex));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, lineColor));
    GL_CHECK(glDrawArrays(GL_LINES, 0, 2));


    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, triVertex));
    GL_CHECK(glColor4f(0.0,1.0,0.0,0.0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	glPopMatrix();
    GL_CHECK(glFinish());

    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glDisableClientState(GL_COLOR_ARRAY));
}

int main(int argc, char** argv)
{
    string file = "gl13-frustumortho";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphicsO(WINDOW_W, WINDOW_H);
    string filename = file + "_Ortho.bmp";
    LOGIF("filename=%s\n", filename.c_str());
    renderFrame();
    save2bmp(filename.c_str());

    setupGraphicsF(WINDOW_W, WINDOW_H);
    filename = file + "_Frustum.bmp";
    LOGIF("filename=%s\n", filename.c_str());
    renderFrame();
    save2bmp(filename.c_str());
    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
