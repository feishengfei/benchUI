/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file fbotexture2d.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for fbotexture2d related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

bool check_attachment(GLenum attach, GLint expect_name) {
	GLint actual_type;
	GLint actual_name;

	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attach,
				              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &actual_type);

	if (actual_type != GL_RENDERBUFFER) {
		LOGE("error: expected GL_RENDERBUFFER for %x attachment type, but found %x\n",
			attach, actual_type);
		return false;
	}

	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, attach,
				              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &actual_name);

	if (actual_name != expect_name) {
		LOGE("error: expected %d for %x attachment name, but found %d\n",
			expect_name, attach, actual_name);
		return false;
	}
	return true;
}

int Init ( ) {
	bool pass = true;

	GLuint fb;
	GLuint rb;

	glGenRenderbuffers(1, &rb);
	glGenFramebuffers(1, &fb);
	glBindRenderbuffer(GL_RENDERBUFFER, rb);
	glBindFramebuffer(GL_FRAMEBUFFER, fb);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, 200, 200);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER,
			         GL_DEPTH_STENCIL_ATTACHMENT,
			         GL_RENDERBUFFER,
			         rb);

	pass = check_attachment(GL_DEPTH_ATTACHMENT, rb) && pass;
	pass = check_attachment(GL_STENCIL_ATTACHMENT, rb) && pass;
	pass = check_attachment(GL_DEPTH_STENCIL_ATTACHMENT, rb) && pass;

	return pass;
}

void Sample::test() {
	Init();
	LOGI("test result: %s !\n", Init() == GL_TRUE ? "PASS" : "FAIL");
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