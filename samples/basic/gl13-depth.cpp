/**
 * @file gl13-depth.c
 * @testpoint glDepthFunc glClearDepthf glDepthRangef glDepthMask
 *
 */
#include "gl-util.h"

GLfloat vertices[] = {
	-2.0, 2.0,
	0.0, -2.0,
	2.0, 2.0
};

GLfloat vertices1[] = {
	-2.0, -2.0,
	0.0, 2.0,
	2.0, -2.0
};

static const GLenum masks[] = {
	GL_TRUE,
	GL_FALSE
};

static const GLenum funcs[] = {
	GL_NEVER,
	GL_LESS,
	GL_EQUAL,
	GL_LEQUAL,
	GL_GREATER,
	GL_NOTEQUAL,
	GL_GEQUAL,
	GL_ALWAYS
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
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
glDepthRange(0.1, 0.7);
    return true;
}

void getdata()
{
GLint parami;
GLboolean paramb;
GLfloat paramf2[2];
GLfloat paramf4[4];
GLfloat paramf;

glGetBooleanv(GL_DEPTH_TEST, &paramb); 
LOGIF("get(GL_DEPTH_TEST)=%s\n",GET_BOOL(paramb));
glGetBooleanv(GL_DEPTH_WRITEMASK, &paramb); 
LOGIF("get(GL_DEPTH_WRITEMASK)=%s\n",GET_BOOL(paramb));

glGetFloatv(GL_DEPTH_CLEAR_VALUE, &paramf); 
LOGIF("get(GL_DEPTH_CLEAR_VALUE):%f\n", paramf);
glGetFloatv(GL_DEPTH_RANGE, paramf2); 
LOGIF("get(GL_DEPTH_RANGE):%f %f\n", paramf2[0], paramf2[1]);
glGetFloatv(GL_CURRENT_COLOR, paramf4); 
LOGIF("get(GL_CURRENT_COLOR):%f %f %f %f\n", paramf4[0], paramf4[1], paramf4[2], paramf4[3]);

glGetIntegerv(GL_DEPTH_FUNC, &parami);
LOGIF("get(GL_DEPTH_FUNC)=%d\n",parami);
}

void renderFrame(GLenum func, GLboolean mask)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
glDepthMask(mask);
    GL_CHECK(glDepthFunc(func));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(1.0, 0.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices1));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.8));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
getdata();
    GL_CHECK(glFlush());
}


int main(int argc, char** argv)
{
    string file = "gl13-depth";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(funcs); i++) {
        for(int j=0; j<2; j++) {
            string func_name = get_enum_name(funcs[i]);
            string mask_name = get_enum_name(masks[j]);
	    string filename = file + "-func-" + func_name + "_mask_" + mask_name + ".bmp";
	    LOGIF("[%d_%d]: %s  %s,  filename=%s\n", i, j, func_name.c_str(), mask_name.c_str(), filename.c_str());
            renderFrame(funcs[i], masks[j]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }}
    GBtest_deinit();

    return 0;
}
