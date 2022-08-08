/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file mapbufferrangeerrorcheck.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for mapbufferrangeerrorcheck related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

bool setupGraphics(int width, int height) {
	GLenum     target = GL_ARRAY_BUFFER;
	GLbitfield access = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
	GLuint     buffer;
	bool       pass   = true;

	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, 100, NULL, GL_STATIC_DRAW);
	glGetError();

	glMapBufferRange(target, -1, 1, access);
	if (!check_gl_error(GL_INVALID_VALUE)) {
		LOGE("Failed!\n");
		pass = false;
	}

	glMapBufferRange(target, 0, -1, access);
	if (!check_gl_error(GL_INVALID_VALUE)) {
		LOGE("Failed!\n");
		pass = false;
	}

	glMapBufferRange(target, 1, GL_BUFFER_SIZE, access);
	if (!check_gl_error(GL_INVALID_VALUE)) {
		LOGE("Failed!\n");
		pass = false;
	}

	glMapBufferRange(target, 0, 10, 0xffffffff);
	if (!check_gl_error(GL_INVALID_VALUE)) {
		LOGE("Failed!\n");
		pass = false;
	}

	glMapBufferRange(target, 0, 10, access);
	if (!check_gl_error(GL_NO_ERROR)) {
		LOGE("Failed!\n");
		pass = false;
	}

	glMapBufferRange(target, 0, 10, access);
	if (!check_gl_error(GL_INVALID_OPERATION)) {
		LOGE("Failed!\n");
		pass = false;
	}
	glUnmapBuffer(target);

	glMapBufferRange(target, 0, 10, 0);
	if (!check_gl_error(GL_INVALID_OPERATION)) {
		LOGE("Failed!\n");
		pass = false;
	}

	glMapBufferRange(target, 0, 10, GL_MAP_READ_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
	if (!check_gl_error(GL_INVALID_OPERATION)) {
		LOGE("Failed!\n");
		pass = false;
	}

	glMapBufferRange(target, 0, 10, GL_MAP_READ_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	if (!check_gl_error(GL_INVALID_OPERATION)) {
		LOGE("Failed!\n");
		pass = false;
	}

	glMapBufferRange(target, 0, 10, GL_MAP_READ_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
	if (!check_gl_error(GL_INVALID_OPERATION)) {
		LOGE("Failed!\n");
		pass = false;
	}

	glMapBufferRange(target, 0, 10, GL_MAP_FLUSH_EXPLICIT_BIT | GL_MAP_READ_BIT);
	if (!check_gl_error(GL_INVALID_OPERATION)) {
		LOGE("Failed!\n");
		pass = false;
	}
	LOGI("test result:%d\n", pass);
	return true;
}


void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	string bmp_file = filename + ".bmp";
	LOGI("bmp_file=%s", bmp_file.c_str());
	save2bmp(bmp_file.c_str());
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
