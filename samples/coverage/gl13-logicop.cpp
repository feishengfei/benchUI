/**
 * @file gl13-logicop.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

GLfloat vertices[] = {
	-2.0, 2.0,
	0.0, -2.0,
	2.0, 2.0
};

static const GLenum factors[] = {
	GL_CLEAR,
	GL_SET,
	GL_COPY,
	GL_COPY_INVERTED,
	GL_NOOP,
	GL_INVERT,
	GL_AND,
	GL_NAND,
	GL_OR,
	GL_NOR,
	GL_XOR,
	GL_EQUIV,
	GL_AND_REVERSE,
	GL_AND_INVERTED,
	GL_OR_REVERSE,
	GL_OR_INVERTED
};

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
    return true;
}

void getdata()
{
GLboolean paramb;
GLint parami;

glGetBooleanv(GL_COLOR_LOGIC_OP, &paramb); 
LOGIF("get(GL_COLOR_LOGIC_OP)=%s\n",GET_BOOL(paramb));

glGetIntegerv(GL_LOGIC_OP_MODE, &parami);
LOGIF("get(GL_LOGIC_OP_MODE)=%d\n",parami);
}

void renderFrame(GLenum factor)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glEnable(GL_COLOR_LOGIC_OP));

    GL_CHECK(glLogicOp(factor));
    GL_CHECK(glColor4f (1.0, 1.0, 0.0, 0.0));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
getdata();
    GL_CHECK(glDisable(GL_COLOR_LOGIC_OP));
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-logicop";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
	    renderFrame(factors[i]);
            string mode_name = get_enum_name(factors[i]);
	    string filename = file + "-" + mode_name + ".bmp";
	    LOGIF("[%d]: %s, filename=%s\n", i, mode_name.c_str(), filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
