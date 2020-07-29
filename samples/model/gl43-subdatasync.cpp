/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file subdatasync.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for subdatasync related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

void renderFrame(void) {
	bool     pass         = true;
	uint32_t dummy_data_1[4], dummy_data_2[4];
	uint32_t good_data[4] = {0, 1, 2, 3};
	void *tmp;
	uint32_t result_data[4];
	bool     subtest_pass;
	size_t   size         = sizeof(good_data);
	GLuint   buffer_handles[2];

	memset(dummy_data_1, 0xaa, size);
	memset(dummy_data_2, 0xbb, size);

	GL_CHECK(glGenBuffers(2, buffer_handles));
	GL_CHECK(glBindBuffer(GL_COPY_READ_BUFFER, buffer_handles[0]));
	GL_CHECK(glBindBuffer(GL_COPY_WRITE_BUFFER, buffer_handles[1]));
	GL_CHECK(glBufferData(GL_COPY_READ_BUFFER, 4096, NULL, GL_STREAM_COPY));
	GL_CHECK(glBufferData(GL_COPY_WRITE_BUFFER, 4096, NULL, GL_STREAM_COPY));
	GL_CHECK(glBufferSubData(GL_COPY_READ_BUFFER, 0, size, good_data));
	GL_CHECK(glBufferSubData(GL_COPY_WRITE_BUFFER, 0, size, dummy_data_1));
	GL_CHECK(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size));
	GL_CHECK(glBufferSubData(GL_COPY_READ_BUFFER, 0, size, dummy_data_2));
	memset(result_data, 0xd0, size);
	GL_CHECK(tmp = glMapBufferRange(GL_COPY_WRITE_BUFFER, 0, size, GL_MAP_READ_BIT));
	memcpy(result_data, tmp, size);
	subtest_pass = memcmp(good_data, result_data, size) == 0;
	LOGI("found 0x%08x 0x%08x 0x%08x 0x%08x\n",
		 result_data[0], result_data[1],
		 result_data[2], result_data[3]);
	LOGI("expected 0x%08x 0x%08x 0x%08x 0x%08x\n",
		 good_data[0], good_data[1],
		 good_data[2], good_data[3]);
	if (!subtest_pass) {
		pass = false;
	}
	GL_CHECK(glUnmapBuffer(GL_COPY_WRITE_BUFFER));
	GL_CHECK(glBufferData(GL_COPY_READ_BUFFER, 4096, NULL, GL_STREAM_COPY));
	GL_CHECK(glBufferData(GL_COPY_WRITE_BUFFER, 4096, NULL, GL_STREAM_COPY));
	GL_CHECK(glBufferSubData(GL_COPY_READ_BUFFER, 0, size, dummy_data_1));
	GL_CHECK(glBufferSubData(GL_COPY_WRITE_BUFFER, 0, size, dummy_data_2));
	GL_CHECK(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size));
	GL_CHECK(glBufferSubData(GL_COPY_WRITE_BUFFER, 0, size, good_data));
	memset(result_data, 0xd0, size);
	GL_CHECK(tmp = glMapBufferRange(GL_COPY_WRITE_BUFFER, 0, size, GL_MAP_WRITE_BIT |
														  GL_MAP_FLUSH_EXPLICIT_BIT));
	memcpy(result_data, tmp, size);
	subtest_pass = memcmp(good_data, result_data, size) == 0;
	GL_CHECK(glFlushMappedBufferRange(GL_COPY_WRITE_BUFFER, 0, size));
	LOGI("found 0x%08x 0x%08x 0x%08x 0x%08x\n",
		 result_data[0], result_data[1], result_data[2], result_data[3]);
	LOGI("expected 0x%08x 0x%08x 0x%08x 0x%08x\n",
		 good_data[0], good_data[1],
		 good_data[2], good_data[3]);
	if (!subtest_pass) {
		pass = false;
	}
	GL_CHECK(glUnmapBuffer(GL_COPY_WRITE_BUFFER));
	LOGI("test result:%d\n", pass);
}

void Sample::test() {
	renderFrame();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

	sample.test();

	return 0;
}
