/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file bufferusage.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for bufferusage related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

float verts[4][4] = {
		{-1.000000, -1.000000, 0.000000, 1.000000},
		{-0.500000, -1.000000, 0.000000, 1.000000},
		{-1.000000, -0.500000, 0.000000, 1.000000},
		{-0.500000, -0.500000, 0.000000, 1.000000}
};

float color_wheel[4][4] = {
	{1, 0, 0, 1},
	{0, 1, 0, 1},
	{0, 0, 1, 1},
	{1, 1, 1, 1},
};

const GLubyte indices[] = {0,1,2};

string vertexShaderFilename = "BufferUsage.vert";
string fragmentShaderFilename = "BufferUsage.frag";

GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint prog;

#define NUM_POINTS 10002
#define SHIFT_COUNT 64

bool setupGraphics(int width, int height) {
	const char *varying = "tf";

    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    prog = GL_CHECK(glCreateProgram());
    if (prog == 0) {
        LOGE("Could not create tf program.");
        return false;
    }

    GL_CHECK(glAttachShader(prog, vertexShaderID));
    GL_CHECK(glAttachShader(prog, fragmentShaderID));
	glTransformFeedbackVaryings(prog, 1, &varying, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(prog);
	glUseProgram(prog);

	glViewport(0, 0, width, height);
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

    return true;
}

void renderFrame(void) {
	static const GLenum bo_modes[] = {
		GL_STREAM_DRAW,
		GL_STREAM_READ,
		GL_STREAM_COPY,
		GL_STATIC_DRAW,
		GL_STATIC_READ,
		GL_STATIC_COPY,
		GL_DYNAMIC_DRAW,
		GL_DYNAMIC_READ,
		GL_DYNAMIC_COPY,
	};
	int i;
	bool pass = true;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (i = 0; i < ARRAY_NUM(bo_modes); i++) {
		static GLuint xfb_buf;
		float *readback;

		glGenBuffers(1, &xfb_buf);
		glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, xfb_buf);
		glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float), NULL, bo_modes[i]);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, xfb_buf);

		glBeginTransformFeedback(GL_POINTS);
		glDrawArrays(GL_POINTS, 0, 1);
		glEndTransformFeedback();

		readback = (float *)glMapBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0,
				sizeof(float), GL_MAP_READ_BIT);

		if (readback[0] != 1.0) {
			pass = false;
		}
		LOGI("Readback found %f, expected 1.0\n", readback[0]);
		glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER);

		glDeleteBuffers(1, &xfb_buf);
	}
	LOGI("test result: %d\n",pass);
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	renderFrame();
	string bmp_file = filename + ".bmp";
	LOGI("bmp_file=%s",bmp_file.c_str());
	save2bmp(bmp_file.c_str());
	Sample::SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}