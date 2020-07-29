/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

void renderFrame(void)
{
	const char *renderer = (const char *) glGetString(GL_RENDERER);
	const char *version = (const char *) glGetString(GL_VERSION);
	const char *vendor = (const char *) glGetString(GL_VENDOR);

	LOGIF("GL_RENDERER = %s\n", renderer);
	LOGIF("GL_VERSION = %s\n", version);
	LOGIF("GL_VENDOR = %s\n", vendor);

	LOGIF("Extensions:\n");
	const char *ext = (const char *) glGetString(GL_EXTENSIONS);
	const char *c = ext;
	for (c = ext; *c; c++) {
		if (*c == ' ')
			LOGIF("\n");
		else
			LOGIF("%c",*c);
	}
}

int main(int argc, char** argv)
{
    string file = "gl13-getstring";
    GBtest_init(&argc,argv,file,DisplayMode);
        renderFrame();
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
