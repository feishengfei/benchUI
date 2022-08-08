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

static const GLenum srcfactors[] = {
	GL_ZERO,
	GL_ONE,
	GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
	GL_SRC_ALPHA_SATURATE
};

static const GLenum dstfactors[] = {
	GL_ZERO,
	GL_ONE,
	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA
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

void renderFrame(GLenum src, GLenum dst)
{
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(src, dst));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glColor4f(1.0, 0.0, 0.0, 0.2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices1));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.8));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glFlush());

    GL_CHECK(glDisable(GL_BLEND));
}

int main(int argc, char** argv)
{
    string file = "gl13-blendfunc";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(srcfactors); i++) {
    for(int j=0; j<ARRAY_NUM(dstfactors); j++) {
            string src_name = get_blending_name(srcfactors[i]);
            string dst_name = get_blending_name(dstfactors[j]);
	    string filename = file + "-src-" + src_name + "-dst-" + dst_name + ".bmp";
	    LOGIF("[%d_%d]: rsc=%s dst=%s, filename=%s\n", i, j, src_name.c_str(), dst_name.c_str(), filename.c_str());
            renderFrame(srcfactors[i],dstfactors[j]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }}
    GBtest_deinit();

    return 0;
}
