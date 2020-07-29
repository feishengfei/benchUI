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
GLuint vertices_bo;
GLuint indirect_bo;

typedef struct {
	GLuint count;
	GLuint primCount;
	GLuint first;
	GLuint baseInstance;
} DrawArraysIndirectCommand;

DrawArraysIndirectCommand draw_arrays_indirect[]={
{3,1,0,0},
{4,1,2,0}
};

bool setupGraphics(int width, int height)
{
	string vertexShaderPath = (string)GLSL_PATH + "base-green.vert";
	string fragmentShaderPath = (string)GLSL_PATH + "base-green.frag";

	programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
	GL_CHECK(glViewport(0, 0, width, height));

	GL_CHECK(glGenVertexArrays(1, &vao));
	GL_CHECK(glBindVertexArray(vao));
	GL_CHECK(glGenBuffers(1, &vertices_bo));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertices_bo));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_data), vertices_data, GL_STATIC_DRAW));
	GL_CHECK(glEnableVertexAttribArray(iLocPosition));
	GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glGenBuffers(1, &indirect_bo));
	GL_CHECK(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_bo));
	GL_CHECK(glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(draw_arrays_indirect), draw_arrays_indirect, GL_STATIC_DRAW));
      
	GL_CHECK(glBindVertexArray(0));

	return true;
}

void renderFrame(GLenum factor) {
	GL_CHECK(glClearColor(0, 0, 1, 1));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));

	GL_CHECK(glBindVertexArray(vao));
	GL_CHECK(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_bo));

	GL_CHECK(glMultiDrawArraysIndirect(factor, (GLvoid *)0,
									   sizeof(draw_arrays_indirect) / sizeof(draw_arrays_indirect[0]), 0));
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
        for(int i=0; i<ARRAY_NUM(factor); i++) {
                string bmp_file = filename + "-" + get_primitives_name(factor[i]) + ".bmp";
		renderFrame(factor[i]);
		LOGI("bmp_file=%s\n", bmp_file.c_str());
		save2bmp(bmp_file.c_str());
		SwapBuffers();
        }
}

int main(int argc, char **argv) {
	Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

	sample.test();

	return 0;
}
