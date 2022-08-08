/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

GLfloat vertices[] = {
	-2.8, 2.8,
	-2.8, -2.8,
	2.8, -2.8,
	2.8, 2.8
};

int max_clip=0;

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
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
   glGetIntegerv(GL_MAX_CLIP_PLANES, &max_clip);
   printf("max num: %d\n",max_clip);
    return true;
}

void getdata()
{
GLboolean paramb;

    for(int i=0; i<max_clip; i++) {
glGetBooleanv(GL_CLIP_PLANE0+i, &paramb); 
LOGIF("get(GL_CLIP_PLANE%d)=%s\n",i,GET_BOOL(paramb));
}
}

void renderFrame(GLenum n)
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    for(int i=0; i<max_clip; i++) {
        GLdouble eqn2[4] = {1.0, 0.0, 0.0, i*0.1};
        glClipPlane(GL_CLIP_PLANE0+i, eqn2);
        glEnable(GL_CLIP_PLANE0+i);
        GLdouble params[4];
        glGetClipPlane(GL_CLIP_PLANE0+i, params);
        LOGIF("glGetClipPlane(%d): %f %f %f %f\n", i, params[0], params[1], params[2], params[3]);
    }

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.0));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    GL_CHECK(glFlush());
getdata();
    for(int i=0; i<n; i++) 
        glDisable(GL_CLIP_PLANE0+i);
}
int main(int argc, char** argv)
{
    string file = "gl13-clipplane";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<max_clip; i++) {
            renderFrame(i);
	    char ss[2];
	    sprintf(ss, "%d", i);
	    string filename = file + "_planeNum_" + ss + ".bmp";
	    LOGIF("[%d] filename=%s\n", i, filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
