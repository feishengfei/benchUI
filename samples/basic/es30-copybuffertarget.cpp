/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file copybuffertarget.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for copybuffertarget related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

static void test_copy(GLenum from, GLenum to) {
	GLuint bufs[2];
	uint8_t data[8];
	uint8_t bad_data[8];
	void *ptr;
	int i;

	glGenBuffers(2, bufs);

	for (i = 0; i < ARRAY_NUM(data); i++)
		data[i] = i;

	memset(bad_data, 0xd0, sizeof(bad_data));

	glBindBuffer(from, bufs[0]);
	glBufferData(from, sizeof(data), data, GL_DYNAMIC_DRAW);
	glBindBuffer(to, bufs[1]);
	glBufferData(to, sizeof(bad_data), bad_data, GL_DYNAMIC_DRAW);

	glCopyBufferSubData(from, to, 0, 0, sizeof(data));
	ptr = glMapBufferRange(to, 0, sizeof(data), GL_MAP_READ_BIT);
	if (memcmp(ptr, data, sizeof(data))) {
		LOGI("[from %s to %s]Failed:data not copied\n",get_enum_name(from),
			   get_enum_name(to));
	} else {
		LOGI("[from %s to %s]Sucessed\n",get_enum_name(from),get_enum_name(to));
	}
	glUnmapBuffer(to);

	glDeleteBuffers(2, bufs);
}

void setupGraphics() {
	int    i, j;
	GLenum targets[] = {
			GL_ARRAY_BUFFER,
			GL_COPY_READ_BUFFER,
			GL_COPY_WRITE_BUFFER,
			GL_ELEMENT_ARRAY_BUFFER,
			GL_PIXEL_PACK_BUFFER,
			GL_PIXEL_UNPACK_BUFFER,
			GL_TRANSFORM_FEEDBACK_BUFFER,
			GL_UNIFORM_BUFFER,
	};

	for (i = 0; i < ARRAY_NUM(targets); i++) {
		GLenum from = targets[i];

		for (j = 0; j < ARRAY_NUM(targets); j++) {
			GLenum to = targets[j];
			if (from == to)
				continue;
			test_copy(from, to);
		}
	}
}

void Sample::test() {
	setupGraphics();
	Sample::SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
