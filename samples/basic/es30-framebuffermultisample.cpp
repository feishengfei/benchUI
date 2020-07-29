/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file framebuffermultisample.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for framebuffermultisample related API
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
	GLint max_samples, samples, prev_rb_samples = 0;
	GLuint rb;
	bool pass = true;

	glGetIntegerv(GL_MAX_SAMPLES, &max_samples);
	check_gl_error(GL_NO_ERROR);
	LOGI("GL_MAX_SAMPLES = %10d\n", max_samples);
	glGenRenderbuffers(1, &rb);
	glBindRenderbuffer(GL_RENDERBUFFER, rb);
	LOGI("%10s %10s\n", "requested", "result");
	for (samples = 0; samples <= max_samples; samples++) {
		GLint rb_samples;
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_RGBA, 1, 1);
		glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &rb_samples);

		if ((rb_samples < prev_rb_samples) ||
		    (samples == 0 && rb_samples != 0) ||
		    (samples > 0 && rb_samples < samples)) {
			LOGE("%10d %10d (ERROR)\n", samples, rb_samples);
			pass = false;
		} else {
			LOGI("%10d %10d\n", samples, rb_samples);
		}
		prev_rb_samples = rb_samples;
	}
	glDeleteRenderbuffers(1, &rb);
    return true;
}

void renderFrame(void)
{
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	LOGI("test result: %s\n", setupGraphics(WINDOW_W, WINDOW_H)==true ? "PASS" : "FAIL");
	renderFrame();
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
