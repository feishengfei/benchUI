/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"
#include <assert.h>

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLenum dithering = GL_FALSE;

static void Init(void)
{

    glDisable(GL_DITHER);
    glShadeModel(GL_FLAT);
}

static void Reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 400, 0, 400);
    glMatrixMode(GL_MODELVIEW);
}

static void Display(void)
{
    float xscale, yscale;
    GLfloat x, y;
    int i;

    glDisable(GL_BLEND);

    (dithering) ? glEnable(GL_DITHER) : glDisable(GL_DITHER);

    glClearColor(0.5, 0.6, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Draw background prims */
    glColor3f(0.1, 0.1, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2i(5, 5);
        glVertex2i(130, 50);
        glVertex2i(100,  300);
    glEnd();
    glColor3f(0.5, 0.2, 0.9);
    glBegin(GL_TRIANGLES);
        glVertex2i(200, 100);
        glVertex2i(330, 50);
        glVertex2i(340,  400);
    glEnd();

    glEnable(GL_BLEND);
    glBlendEquation(GL_LOGIC_OP);
    glLogicOp(GL_XOR);

    /* Draw a set of rectangles across the window */
    glColor3f(0.9, 0.2, 0.8);
    for(i = 0; i < 400; i+=60) {
        glBegin(GL_POLYGON);
            glVertex2i(i, 100);
            glVertex2i(i+50, 100);
            glVertex2i(i+50, 200);
            glVertex2i(i, 200);
        glEnd();
    }
	glutSwapBuffers();
	glDrawBuffer(GL_FRONT);

    /* Redraw  the rectangles, which should erase them */
    for(i = 0; i < 400; i+=60) {
        glBegin(GL_POLYGON);
            glVertex2i(i, 100);
            glVertex2i(i+50, 100);
            glVertex2i(i+50, 200);
            glVertex2i(i, 200);
        glEnd();
    }

    glFlush();
        glDrawBuffer(GL_BACK);	
    assert(glGetError() == GL_NO_ERROR);
}

int main(int argc, char** argv)
{
    string file = "gl13-drawbuffer";
    GBtest_init(&argc,argv,file,DisplayMode);
    Reshape(WINDOW_W, WINDOW_H);
/*    for(int i=0; i<ARRAY_NUM(funcs); i++) {
        for(int j=0; j<ARRAY_NUM(factors); j++) {
            string func_name = get_enum_name(funcs[i]);
            string sfail_name = get_enum_name(factors[j]);*/
	    string filename = file + ".bmp";
	    LOGIF("[]: filename=%s\n", filename.c_str());
	    Init();
            Display();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
//    }}
    GBtest_deinit();

    return 0;
}
