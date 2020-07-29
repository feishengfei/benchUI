/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file multidrawarraysindirect.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for multidrawarraysindirect related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include <GL/glcorearb.h>

using std::string;
using namespace BotsonSDK;
using namespace std;

float vertices_data[] = {
		-0.8, 0.0,
		-0.6, 0.6,
		0.0, 0.8,
		0.6, 0.6,
		0.8, 0.0,
        	0.6, -0.6,
		0.0, -0.8,
		-0.6, -0.6
};

GLenum factor[]={
GL_POINTS,
GL_LINES,
GL_LINE_STRIP,
GL_LINE_LOOP,
GL_TRIANGLES,
GL_TRIANGLE_STRIP,
GL_TRIANGLE_FAN
};

GLuint programID;
GLint iLocPosition = -1;
GLuint vao;
GLuint vertices_bo[2];
GLuint indirect_bo;


bool setupGraphics(int width, int height)
{
	string vertexShaderPath = (string)GLSL_PATH + "base-green.vert";
	string fragmentShaderPath = (string)GLSL_PATH + "base-green.frag";

	programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
	GL_CHECK(glViewport(0, 0, width, height));

	GL_CHECK(glGenVertexArrays(1, &vao));
	GL_CHECK(glBindVertexArray(vao));
	GL_CHECK(glGenBuffers(2, &vertices_bo[0]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertices_bo[0]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_data), vertices_data, GL_STATIC_DRAW));
	GL_CHECK(glEnableVertexAttribArray(iLocPosition));
	GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glBindVertexArray(0));

	return true;
}

void renderFrame(GLenum factor, int i) {
	GLsizei  cout[]           = {4, 4};
	GLushort indicesUp_us[]   = {0, 1, 2, 3};
	GLushort indicesDown_us[] = {2, 3, 4, 5};
	GLvoid *indices_us[2] = {indicesUp_us, indicesDown_us};
	const GLint base[] = {1, 2};
	GL_CHECK(glClearColor(0.0, 0.0, 1.0, 1.0));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));
	GL_CHECK(glBindVertexArray(vao));
	switch (i) {
	case 0:
	GL_CHECK(glMultiDrawElements(factor, cout, GL_UNSIGNED_SHORT, indices_us, 2));
		break;
	case 1:
	GL_CHECK(glMultiDrawElementsBaseVertex(factor, cout, GL_UNSIGNED_SHORT, indices_us, 2, base));
		break;
	default:
		break;
	}
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	for (int i = 0; i < ARRAY_NUM(factor); i++) {
		for (int j = 0; j < 2; j++) {
			char ss[3];
			sprintf(ss, "%d", j);
			string bmp_file = filename + "-" + get_primitives_name(factor[i]) + ss + ".bmp";
			renderFrame(factor[i], j);
			LOGI("bmp_file=%s\n", bmp_file.c_str());
			save2bmp(bmp_file.c_str());
			SwapBuffers();
		}
	}
}

int main(int argc, char **argv) {
	Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

	sample.test();

	return 0;
}
