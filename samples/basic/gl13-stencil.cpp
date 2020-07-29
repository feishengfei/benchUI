/**
 * @file accum2.c
 * @testpoint glAccum
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

static const GLenum funcs[] = {
	GL_NEVER,
	GL_LESS,
	GL_LEQUAL,
	GL_GREATER,//
	GL_GEQUAL,//
	GL_EQUAL,
	GL_NOTEQUAL,//
	GL_ALWAYS//
};

static const GLenum factors[] = {
	GL_KEEP,
	GL_ZERO,
	GL_REPLACE,
	GL_INCR,
	GL_DECR,
	GL_INVERT
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
    GL_CHECK(glClearStencil(0x00));
    GL_CHECK(glEnable(GL_STENCIL_TEST));
    GL_CHECK(glDisable(GL_DEPTH_TEST));
    GL_CHECK(glStencilMask(0x00));
    return true;
}

void getdata()
{
GLint parami;
GLboolean paramb;

glGetBooleanv(GL_STENCIL_TEST, &paramb); 
LOGIF("get(GL_STENCIL_TEST)=%s\n",GET_BOOL(paramb));

glGetIntegerv(GL_STENCIL_BITS, &parami);
LOGIF("get(GL_STENCIL_BITS)=%d\n",parami);
glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &parami);
LOGIF("get(GL_STENCIL_CLEAR_VALUE)=%d\n",parami);
glGetIntegerv(GL_STENCIL_FAIL, &parami);
LOGIF("get(GL_STENCIL_FAIL)=%d\n",parami);
glGetIntegerv(GL_STENCIL_FUNC, &parami);
LOGIF("get(GL_STENCIL_FUNC)=%d\n",parami);
glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &parami);
LOGIF("get(GL_STENCIL_PASS_DEPTH_FAIL)=%d\n",parami);
glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &parami);
LOGIF("get(GL_STENCIL_PASS_DEPTH_PASS)=%d\n",parami);
glGetIntegerv(GL_STENCIL_REF, &parami);
LOGIF("get(GL_STENCIL_REF)=%d\n",parami);
glGetIntegerv(GL_STENCIL_VALUE_MASK, &parami);
LOGIF("get(GL_STENCIL_VALUE_MASK)=%d\n",parami);
glGetIntegerv(GL_STENCIL_WRITEMASK, &parami);
LOGIF("get(GL_STENCIL_WRITEMASK)=%d\n",parami);
}

void renderFrame(GLenum func, GLenum sfail, GLenum dpfail, GLenum dppass)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glStencilFunc(func,0x90,0xff));
    GL_CHECK(glStencilOp(sfail, dpfail, dppass));
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
    string file = "gl13-stencil";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(funcs); i++) {
        for(int j=0; j<ARRAY_NUM(factors); j++) {
        for(int m=0; m<ARRAY_NUM(factors); m++) {
        for(int n=0; n<ARRAY_NUM(factors); n++) { //sfail, , 
            string func_name = get_enum_name(funcs[i]);
            string sfail_name = get_enum_name(factors[j]);
            string dpfail_name = get_enum_name(factors[m]);
            string dppass_name = get_enum_name(factors[n]);
	    string filename = file + "-func-" + func_name + "-sfail-" + sfail_name + 
			"_dpfail_" + dpfail_name + "_dppass_" + dppass_name + ".bmp";
	    LOGIF("[%d_%d_%d_%d]: filename=%s\n", i, j, m, n, filename.c_str());
            renderFrame(funcs[i],factors[j],factors[m],factors[n]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }}}}
    GBtest_deinit();

    return 0;
}
