/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"
#include <cstring>

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

void renderFrame()
{
	GLuint obj;
	void * ptr;

	glVertexPointer(4, GL_FLOAT, sizeof(GLfloat) * 4, (void *) 0xDEADBEEF);
	glEnableClientState(GL_VERTEX_ARRAY);

	glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);

	glVertexPointer(4, GL_FLOAT, sizeof(GLfloat) * 4, (void *) 0xBADDC0DE);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopClientAttrib();

	if (! glIsEnabled(GL_VERTEX_ARRAY)) {
		LOGIF("Array state is incorrectly disabled.\n");
	}

	glGetPointerv(GL_VERTEX_ARRAY_POINTER, & ptr);
	if (ptr != (void *) 0xDEADBEEF) {
		LOGIF("Array pointer is incorrectly set to 0x%p.\n", ptr);
	} else
		LOGIF("test Client Pass\n");
}

int main(int argc, char** argv)
{
    string file = "gl13-clientattrib";
    GBtest_init(&argc,argv,file,DisplayMode);
	    renderFrame();
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
