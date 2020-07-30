/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file mapflushbuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for mapflushbuffer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

uint8_t data[1 << 20];

GLenum targets[] = {
	GL_ARRAY_BUFFER,
	GL_COPY_READ_BUFFER,
	GL_ELEMENT_ARRAY_BUFFER,
	GL_PIXEL_PACK_BUFFER,
	GL_PIXEL_UNPACK_BUFFER,
	GL_TRANSFORM_FEEDBACK_BUFFER,
	GL_UNIFORM_BUFFER
};

static bool verify_buffer(GLenum target, int offset, int length, void const *compare) {
	const void *ptr = glMapBufferRange(target, offset, length, GL_MAP_READ_BIT);
	int ret = memcmp(ptr, compare, length);
	glUnmapBuffer(target);
	return ret == 0;
}

void renderFrame(GLenum target) {
	uint8_t *ptr;
	uint8_t temp_data[100];
	GLenum  verify = GL_COPY_WRITE_BUFFER;
	GLuint  handles[2];
	int     i;
	bool    ret;

	for (i = 0; i < sizeof(data); i++) {
		data[i] = i & 0xff;
	}

	for (i = 0; i < 100; i++) {
		temp_data[i] = i;
	}

	glGenBuffers(2, handles);
	glBindBuffer(target, handles[0]);
	glBindBuffer(verify, handles[1]);
	glBufferData(target, sizeof(data), data, GL_STATIC_DRAW);
	glBufferData(verify, 0x1000, NULL, GL_STREAM_READ);
	ret = verify_buffer(target, 0x201, 100, &data[0x201]);
	if (!ret)
	LOGE("Line %d:FAIL\n", __LINE__);

	ptr = (uint8_t *)glMapBufferRange(target, 0x10004, 100, GL_MAP_WRITE_BIT |
															GL_MAP_INVALIDATE_RANGE_BIT);
	memcpy(ptr, temp_data, 100);
	glUnmapBuffer(target);
	ret = verify_buffer(target, 0x10004, 100, temp_data);
	if (!ret)
	LOGE("Line %d:FAIL\n", __LINE__);

	ptr = (uint8_t *)glMapBufferRange(target, 0x50f, 100, GL_MAP_WRITE_BIT |
														  GL_MAP_UNSYNCHRONIZED_BIT);
	memcpy(ptr, temp_data, 100);
	glUnmapBuffer(target);
	ret = verify_buffer(target, 0x50f, 100, temp_data);
	if (!ret)
	LOGE("Line %d:FAIL\n", __LINE__);

	ptr = (uint8_t *)glMapBufferRange(target, 0xa000, 100, GL_MAP_WRITE_BIT |
														   GL_MAP_FLUSH_EXPLICIT_BIT |
														   GL_MAP_UNSYNCHRONIZED_BIT);
	memcpy(ptr, temp_data, 100);
	glUnmapBuffer(target);
	glCopyBufferSubData(target, verify, 0xa002, 0, 100);
	ret = verify_buffer(verify, 0, 100, temp_data);
	if (ret)
	LOGE("Coherent without flush\n");

	ptr = (uint8_t *)glMapBufferRange(target, 0xa002, 100, GL_MAP_WRITE_BIT |
														   GL_MAP_FLUSH_EXPLICIT_BIT |
														   GL_MAP_UNSYNCHRONIZED_BIT);
	memcpy(ptr, temp_data, 100);
	glFlushMappedBufferRange(target, 0x0, 100);
	glUnmapBuffer(target);
	glCopyBufferSubData(target, verify, 0xa002, 100, 100);
	ret = verify_buffer(verify, 100, 100, temp_data);
	if (!ret)
	LOGE("Line %d:FAIL\n", __LINE__);

	LOGI("PASS\n");
}

void Sample::test() {
	for(int i=0; i<ARRAY_NUM(targets); i++) {
		LOGI("target = %s:\n", get_enum_name(targets[i]));
		renderFrame(targets[i]);
	}
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
