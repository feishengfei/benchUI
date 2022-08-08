/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file copybuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for copybuffer related API
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

const float triangleVerticesLittle[] = {
    -0.45f, -0.45f, 0.0f,
     0.45f, -0.45f, 0.0f,
     0.0f,  0.45f, 0.0f,
     0.0f, -0.45f, 0.0f
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

const int triangleColorsI[] = {
    1, 0, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1
};

GLushort indices[] = {0,1,2};
const GLubyte subdata[] = {1,3};

static const GLint vertices [] = {
		0, -2,
		-52, 32,
		0, 2,
		2, 0,
		15, 153,
		-2, 0
};
static const GLfloat color[] = {
		0.0, 1.0, 0.0,
		10.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 110.0, 0.0,
		0.0, 0.0, 1.0
};

const float triangleVertices2[] = {
     0.0f,-0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
};

const float triangleColors2[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
};

GLboolean test_copy(void) {
#define BUF_SIZE 600

	GLuint    bufs[2];
	char      data[BUF_SIZE], *p;
	int       i;
	int       chunk = 100;
	GLboolean pass  = GL_TRUE;

	glGenBuffers(2, bufs);

	for (i = 0; i < BUF_SIZE; i++)
		data[i] = rand() % 256;

	glBindBuffer(GL_COPY_READ_BUFFER, bufs[0]);
	glBufferData(GL_COPY_READ_BUFFER, BUF_SIZE, data, GL_STATIC_DRAW);
	glBindBuffer(GL_COPY_WRITE_BUFFER, bufs[1]);
	glBufferData(GL_COPY_WRITE_BUFFER, BUF_SIZE, NULL, GL_DYNAMIC_COPY);

	for (i = 0; i < BUF_SIZE / chunk; i++) {
		int srcOffset = i * chunk;
		int dstOffset = i * chunk;
		glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER,
							srcOffset, dstOffset, chunk);
	}

	p = (char *)glMapBufferRange(GL_COPY_WRITE_BUFFER, 0,
								 sizeof(char) * BUF_SIZE, GL_MAP_READ_BIT);

	for (i = 0; i < BUF_SIZE; i++) {
		if (p[i] != data[i]) {
			LOGI("expected %d, found %d at location %d\n",
				 data[i], p[i], i);
			pass = GL_FALSE;
			break;
		}
	}

	GLint   getdata;
	GLint64 getdata64;
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_ACCESS_FLAGS, &getdata);
	LOGI("GetBufferParameteriv(GL_COPY_READ_BUFFER,GL_BUFFER_ACCESS_FLAGS):%d\n", getdata);
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_MAPPED, &getdata);
	LOGI("GetBufferParameteriv(GL_COPY_READ_BUFFER,GL_BUFFER_MAPPED):%d\n", getdata);
	glGetBufferParameteri64v(GL_COPY_READ_BUFFER, GL_BUFFER_MAP_LENGTH, &getdata64);
	LOGI("glGetBufferParameteri64v(GL_COPY_READ_BUFFER,GL_BUFFER_MAP_LENGTH):%d\n", getdata64);
	glGetBufferParameteri64v(GL_COPY_READ_BUFFER, GL_BUFFER_MAP_OFFSET, &getdata64);
	LOGI("glGetBufferParameteri64v(GL_COPY_READ_BUFFER,GL_BUFFER_MAP_OFFSET):%d\n", getdata64);
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &getdata);
	LOGI("GetBufferParameteriv(GL_COPY_READ_BUFFER,GL_BUFFER_SIZE):%d\n", getdata);
	glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_USAGE, &getdata);
	LOGI("GetBufferParameteriv(GL_COPY_READ_BUFFER,GL_BUFFER_USAGE):%d\n", getdata);
	GLvoid *params;
	glGetBufferPointerv(GL_COPY_READ_BUFFER, GL_BUFFER_MAP_POINTER, &params);
	LOGI("GetBufferPointerv(GL_COPY_READ_BUFFER):%x\n", params);

	glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_ACCESS_FLAGS, &getdata);
	LOGI("GetBufferParameteriv(GL_COPY_WRITE_BUFFER,GL_BUFFER_ACCESS_FLAGS):%d\n", getdata);
	glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_MAPPED, &getdata);
	LOGI("GetBufferParameteriv(GL_COPY_WRITE_BUFFER,GL_BUFFER_MAPPED):%d\n", getdata);
	glGetBufferParameteri64v(GL_COPY_WRITE_BUFFER, GL_BUFFER_MAP_LENGTH, &getdata64);
	LOGI("glGetBufferParameteri64v(GL_COPY_WRITE_BUFFER,GL_BUFFER_MAP_LENGTH):%d\n", getdata64);
	glGetBufferParameteri64v(GL_COPY_WRITE_BUFFER, GL_BUFFER_MAP_OFFSET, &getdata64);
	LOGI("glGetBufferParameteri64v(GL_COPY_WRITE_BUFFER,GL_BUFFER_MAP_OFFSET):%d\n", getdata64);
	glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_SIZE, &getdata);
	LOGI("GetBufferParameteriv(GL_COPY_WRITE_BUFFER,GL_BUFFER_SIZE):%d\n", getdata);
	glGetBufferParameteriv(GL_COPY_WRITE_BUFFER, GL_BUFFER_USAGE, &getdata);
	LOGI("GetBufferParameteriv(GL_COPY_WRITE_BUFFER,GL_BUFFER_USAGE):%d\n", getdata);
	glGetBufferPointerv(GL_COPY_WRITE_BUFFER, GL_BUFFER_MAP_POINTER, &params);
	LOGI("GetBufferPointerv(GL_COPY_WRITE_BUFFER):%x\n", params);

	glUnmapBuffer(GL_COPY_WRITE_BUFFER);

	glDeleteBuffers(2, bufs);

	return pass;
}

void Sample::test() {
	LOGI("test result:%d\n",test_copy());
	Sample::SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}