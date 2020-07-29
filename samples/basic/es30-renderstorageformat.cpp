/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file renderstorageformat.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for renderstorageformat related API
 * @par TestPoints:
 *
 */

#include "Sample.h"


using std::string;
using namespace BotsonSDK;

GLenum formats[] = {
		GL_R8,
		GL_R8UI,
		GL_R8I,
		GL_R16UI,
		GL_R16I,
		GL_R32UI,
		GL_R32I,
		GL_RG8,
		GL_RG8UI,
		GL_RG8I,
		GL_RG16UI,
		GL_RG16I,
		GL_RG32UI,
		GL_RG32I,
		GL_RGB8,
		GL_RGBA8,
		GL_SRGB8_ALPHA8,
		GL_RGB10_A2,
		GL_RGBA8UI,
		GL_RGBA8I,
		GL_RGB10_A2UI,
		GL_RGBA16UI,
		GL_RGBA16I,
		GL_RGBA32I,
		GL_RGBA32UI,
		GL_DEPTH_COMPONENT24,
		GL_DEPTH_COMPONENT32F,
		GL_DEPTH24_STENCIL8,
		GL_DEPTH32F_STENCIL8
};

bool setupGraphics(int width, int height) {
	GLuint    fbo, rb, stencilrb, depthrb;
	int       i;
	GLboolean pass = true;

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	if (!check_gl_error(GL_NO_ERROR)) {
		LOGE("FAIL\n");
		return false;
	}

	glGenRenderbuffers(1, &rb);
	glGenRenderbuffers(1, &depthrb);
	glGenRenderbuffers(1, &stencilrb);
	if (!check_gl_error(GL_NO_ERROR)) {
		LOGE("FAIL\n");
		return false;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, rb);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rb);
	if (!check_gl_error(GL_NO_ERROR)) {
		LOGE("FAIL\n");
		return false;
	}

	while (glGetError());
	for (i = 0; i < ARRAY_NUM(formats); i++) {
		const char *name = get_enum_name(formats[i]);
		if (formats[i] == GL_DEPTH_COMPONENT24 || formats[i] == GL_DEPTH_COMPONENT32F) {
			glBindRenderbuffer(GL_RENDERBUFFER, depthrb);
			glRenderbufferStorage(GL_RENDERBUFFER, formats[i], width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
									  depthrb);
		} else if (formats[i] == GL_DEPTH24_STENCIL8 || formats[i] == GL_DEPTH32F_STENCIL8) {
			glDeleteRenderbuffers(1, &depthrb);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glBindRenderbuffer(GL_RENDERBUFFER, stencilrb);
			glRenderbufferStorage(GL_RENDERBUFFER, formats[i], width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
									  GL_RENDERBUFFER, stencilrb);
		} else {
			glRenderbufferStorage(GL_RENDERBUFFER, formats[i], width, height);
		}
		if (!check_gl_error(GL_NO_ERROR)) {
			LOGE("FAIL  %s\n", name);
			return false;
		} else {
			GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (status != GL_FRAMEBUFFER_COMPLETE) {
				LOGE("FAIL  %s is incomplete\n", name);
				return false;
			}
		}
		LOGI(" %d: %s PASS\n", i, name);
	}
	glDeleteRenderbuffers(1, &rb);
	glDeleteFramebuffers(1, &fbo);
	return true;
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	LOGE("test result: %s\n", setupGraphics(WINDOW_W, WINDOW_H)==true ? "PASS" : "FAIL");
	string bmp_file = filename + ".bmp";
	LOGI("bmp_file=%s", bmp_file.c_str());
	save2bmp(bmp_file.c_str());
	Sample::SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
