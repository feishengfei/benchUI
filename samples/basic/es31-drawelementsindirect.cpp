/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file drawelementsindirect.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for drawelementsindirect related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

float vertices_data[] = {
	-0.8, -0.8,
	 0.8, -0.8,
	-0.8,  0.8,
	 0.8,  0.8,
};

unsigned short indices_data[] = {
	0, 1, 2, 3,
};

GLuint indirect_data[] = {4, 4, 0, 0, 0,};
GLuint programID;
GLint iLocPosition = -1;
GLuint vao;

GLenum factors[] = {
	GL_POINTS,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_LINES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_TRIANGLES
};

typedef struct {
	GLuint count;
	GLuint instanceCount;
	GLuint first;
	GLuint reservedMustBeZero;
} DrawArraysIndirectCommand;

bool setupGraphics(int width, int height)
{
    string vertexShaderPath = (string)GLSL_PATH + "base-green.vert"; 
    string fragmentShaderPath = (string)GLSL_PATH + "base-green.frag";

	programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	GL_CHECK(glUseProgram(programID));
	GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));

	GL_CHECK(glViewport(0, 0, width, height));

	GLuint vertices_bo;
	GLuint indices_bo;
	GLuint indirect_bo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertices_bo);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_bo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_data), vertices_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(iLocPosition);
	glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &indices_bo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_bo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_data), indices_data, GL_STATIC_DRAW);

	glGenBuffers(1, &indirect_bo);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirect_bo);
	glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(indirect_data), indirect_data, GL_STATIC_DRAW);

	glBindVertexArray(0);

	return true;
}

void renderFrame(GLenum factor)
{
	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao);
	GL_CHECK(glUseProgram(programID));

	glDrawElementsIndirect(factor, GL_UNSIGNED_SHORT, (GLvoid const *)0);
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	for(int i=0; i<ARRAY_NUM(factors); i++) {
		string bmp_file = filename + "-" + get_primitives_name(factors[i]) + ".bmp";
		renderFrame(factors[i]);
		LOGI("bmp_file=%s", bmp_file.c_str());
		save2bmp(bmp_file.c_str());
		Sample::SwapBuffers();
	}
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}

