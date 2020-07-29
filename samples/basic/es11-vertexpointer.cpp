/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file vertexpointer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for vertexpointer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"


using namespace BotsonSDK;
using std::string;

GLenum types_vertex[]={
GL_BYTE,
GL_SHORT,
GL_FLOAT
};

short vertices_s[] = {
	-2, 2,
	0, -2,
	2, 2
};

GLbyte vertices_b[] = {
	-2, 2,
	0, -2,
	2, 2
};

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

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof (-3.0, 3.0,-3.0, 3.0, -3.0, 3.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return true;
}

int size;

void renderFrame(GLenum type)
{
	GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
	switch(type) {
	case GL_BYTE:
	GL_CHECK(glVertexPointer(size, type, 0, vertices_b));
		break;
	case GL_SHORT:
	GL_CHECK(glVertexPointer(size, type, 0, vertices_s));
		break;
	case GL_FLOAT:
	GL_CHECK(glVertexPointer(size, type, 0, vertices));
		break;
	default:
	LOGI("invalid type\n");
		break;
	}

    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glDisableClientState(GL_COLOR_ARRAY));
}


void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);

	for (size = 2; size < 5; size++) {
		for (int i = 0; i < ARRAY_NUM(types_vertex); i++) {
			char ss[2];
			sprintf(ss, "%d", size);
			string type_name = get_enum_name(types_vertex[i]);
			string bmp_file  = filename + "-" + ss + type_name + ".bmp";
			LOGI("filename=%s", bmp_file.c_str());
			renderFrame(types_vertex[i]);
			save2bmp(bmp_file.c_str());
			SwapBuffers();
		}
	}
}

int main(int argc, char **argv)
{
	Sample sample(__FILE__);

	sample.test();

	return 0;
}

