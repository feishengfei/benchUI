/**
 * @file accum2.c
 * @testpoint glArrayElement glVertexPointer
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

GLenum culls[] = {GL_FRONT, GL_BACK, GL_FRONT_AND_BACK};
GLenum fronts[] = {GL_CW, GL_CCW};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-3.0f, 3.0f, -3.0f*h/w, 3.0f*h/w, -3.0f, 3.0f);
	}
	else {
		glOrtho(-3.0f*w/h, 3.0f*w/h, -3.0f, 3.0f, -3.0f, 3.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getdata()
{
GLint parami;
GLboolean paramb;

glGetBooleanv(GL_CULL_FACE, &paramb); 
LOGIF("get(GL_CULL_FACE)=%s\n",paramb==GL_TRUE?"GL_TRUE":"GL_FALSE");

glGetIntegerv(GL_CULL_FACE_MODE, &parami);
LOGIF("get(GL_CULL_FACE_MODE)=%d\n",parami);
glGetIntegerv(GL_FRONT_FACE, &parami);
LOGIF("get(GL_FRONT_FACE)=%d\n",parami);
}

void renderFrame(GLenum front, GLenum cull)
{
    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glFrontFace(front));
    GL_CHECK(glCullFace(cull));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));

    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glFlush());
getdata();
    glDisable(GL_CULL_FACE);
}

int main(int argc, char** argv)
{
    string file = "gl13-cullface";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(fronts); i++) {
    for(int j=0; j<ARRAY_NUM(culls); j++) {
	    string cull_name=get_enum_name(culls[j]);
	    string front_name=get_enum_name(fronts[i]);
	    string filename = file + "-" + front_name + "-" + cull_name + ".bmp";
	    LOGIF("[%d_%d]:frontface=%s gl13-cullface=%s, filename=%s\n", i, j, front_name.c_str(), cull_name.c_str(), filename.c_str());
            renderFrame(fronts[i],culls[j]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }}
    GBtest_deinit();

    return 0;
}
