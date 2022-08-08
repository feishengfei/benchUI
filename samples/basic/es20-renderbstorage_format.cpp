/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file renderbstorage_format.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for renderbstorage_format related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLenum formats[] = {
	GL_RGB565,
	GL_RGBA4,
	GL_RGB5_A1,
	GL_DEPTH_COMPONENT16,
	GL_STENCIL_INDEX8
};

bool setupGraphics(int width, int height) {
	GLuint fbo, rb, stencilrb, depthrb;
	int i;
	GLboolean pass = true;

	glGenFramebuffers(1, &fbo);
	GL_CHECK(glIsRenderbuffer (fbo));
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
        if(formats[i] == GL_DEPTH_COMPONENT16) {
			glBindRenderbuffer(GL_RENDERBUFFER, depthrb);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrb);
		} else if(formats[i] == GL_STENCIL_INDEX8) {
			glDeleteRenderbuffers(1, &depthrb);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glBindRenderbuffer(GL_RENDERBUFFER, stencilrb);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, stencilrb);
		} else {
			glRenderbufferStorage(GL_RENDERBUFFER, formats[i], width, height);
		}

		if (!check_gl_error(GL_NO_ERROR)) {
			LOGE("FAIL  %s\n", name);
			return false;
		} else {
			GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if(status != GL_FRAMEBUFFER_COMPLETE) {
				LOGE("FAIL  %s is incomplete\n", name);
				return false;
			}
		}
	}

    glDeleteRenderbuffers(1, &rb);
    glDeleteFramebuffers(1, &fbo);

    return true;
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	bool ret = setupGraphics(WINDOW_W, WINDOW_H);
    LOGI("test result: %s\n", ret==true ? "PASS" : "FAIL");
	Sample::SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
