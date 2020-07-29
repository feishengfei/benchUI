/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file uniformbuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for uniformbuffer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

bool setupGraphics(int width, int height) {
	bool    pass        = true;
	GLuint  bo;
	uint8_t in_data[1]  = {0xaa};
	uint8_t out_data[1] = {0xd0};
	uint8_t *ptr1, *ptr2;

	glGenBuffers(1, &bo);

	glBindBuffer(GL_UNIFORM_BUFFER, bo);
	pass = pass && check_gl_error(0);

	glBufferData(GL_UNIFORM_BUFFER, 1, NULL, GL_STATIC_READ);
	pass = pass && check_gl_error(0);

	glBufferSubData(GL_UNIFORM_BUFFER, 0, 1, in_data);
	pass = pass && check_gl_error(0);

	ptr1 = (uint8_t *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(uint8_t),
									   GL_MAP_READ_BIT);
	pass = pass && check_gl_error(0);

	glGetBufferPointerv(GL_UNIFORM_BUFFER, GL_BUFFER_MAP_POINTER, (void **)(&ptr2));
	pass = pass && check_gl_error(0);
	LOGI("ptr1=%x(%x), ptr2=%x(%x)\n", ptr1, *ptr1, ptr2, *ptr2);

	glUnmapBuffer(GL_UNIFORM_BUFFER);
	pass = pass && check_gl_error(0);
	LOGI("test result: %d\n", pass);

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
