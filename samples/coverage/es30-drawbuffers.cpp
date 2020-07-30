/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file drawbuffers.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for drawbuffers related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

#define TEXTURE_AMOUNT 3

static const GLenum valid_buffer_list[] = {
	GL_COLOR_ATTACHMENT0,
	GL_COLOR_ATTACHMENT1,
	GL_COLOR_ATTACHMENT2,
};

static const GLenum invalid_buffer_list[] = {
	GL_COLOR_ATTACHMENT0,
	GL_BACK,
	GL_COLOR_ATTACHMENT1,
};

bool setupGraphics(int width, int height) {
     return true;
}

unsigned piglit_num_components(GLenum format) {
	switch (format) {
	case GL_ALPHA:
	case GL_DEPTH_COMPONENT:
	case GL_LUMINANCE:
	case GL_RED:
	case GL_GREEN:
	case GL_BLUE:
		return 1;
	case GL_DEPTH_STENCIL:
	case GL_LUMINANCE_ALPHA:
	case GL_RG:
		return 2;
	case GL_RGB:
		return 3;
	case GL_RGBA:
		return 4;
	default:
		LOGD("Unknown num_components\n");
		return 0;
	}
}

static GLuint create_fbo() {
	GLuint fbo;
	GLuint depth;
	GLuint textures[TEXTURE_AMOUNT];
	GLint param;
	unsigned i;

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glGenTextures(TEXTURE_AMOUNT, textures);

	for (i = 0; i < TEXTURE_AMOUNT; i++) {
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, NULL);

		glFramebufferTexture2D(GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0 + i,
			GL_TEXTURE_2D,
			textures[i], 0);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_FALSE, GL_TEXTURE_2D, textures[0], 0);

	if (!check_gl_error(GL_INVALID_ENUM))
		return 0;

	glGenRenderbuffers(1, &depth);
	glBindRenderbuffer(GL_RENDERBUFFER, depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 4, 4);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_FALSE, GL_RENDERBUFFER, depth);

	if (!check_gl_error(GL_INVALID_ENUM))
		return 0;

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
		GL_FRAMEBUFFER_COMPLETE) {
		return 0;
	}

	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_FALSE,
		GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &param);

	if (!check_gl_error(GL_INVALID_ENUM))
		return 0;

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	return fbo;
}

bool renderFrame(void) {
	const GLenum back = GL_BACK;
	const GLenum att0 = GL_COLOR_ATTACHMENT0;
	GLuint fbo;
	GLint max_buffers;

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glDrawBuffers(0, &back);
	if (!check_gl_error(GL_INVALID_OPERATION))
		return false;

	glDrawBuffers(2, &back);
	if (!check_gl_error(GL_INVALID_OPERATION))
		return false;

	glDrawBuffers(3, &att0);
	if (!check_gl_error(GL_INVALID_OPERATION))
		return false;

	glDrawBuffers(1, &back);
	if (!check_gl_error(GL_NO_ERROR))
		return false;

	fbo = create_fbo();
	if (!fbo || !check_gl_error(GL_NO_ERROR))
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glDrawBuffers(3, invalid_buffer_list);
	if (!check_gl_error(GL_INVALID_OPERATION))
		return false;

	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &max_buffers);
	if (!check_gl_error(GL_NO_ERROR))
		return false;

	glDrawBuffers(max_buffers + 1, valid_buffer_list);
	if (!check_gl_error(GL_INVALID_VALUE))
		return false;

	glDrawBuffers(TEXTURE_AMOUNT, valid_buffer_list);
	if (!check_gl_error(GL_NO_ERROR))
		return false;

	return true;
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	renderFrame();
	LOGI("test result: %d\n",renderFrame());
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
