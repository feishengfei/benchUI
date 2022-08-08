/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file frontbufferdistraction.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for frontbufferdistraction related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

static const GLenum buffers[] = {
		GL_ARRAY_BUFFER, GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 
		GL_ELEMENT_ARRAY_BUFFER, GL_PIXEL_PACK_BUFFER, GL_PIXEL_UNPACK_BUFFER,
		GL_TRANSFORM_FEEDBACK_BUFFER, GL_UNIFORM_BUFFER
};

float piglit_tolerance[4] = { 0.01, 0.01, 0.01, 0.01 };

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
		LOGI("Unknown num_components\n");
		return 0;
	}
}

static bool compare_pixels_float(const float *color1, const float *color2,
		     const float *tolerance, int components) {
	for (int p = 0; p < components; ++p)
		if (fabsf(color1[p] - color2[p]) > tolerance[p])
			return false;
	return true;
}

static void array_float_to_ubyte_roundup(int n, const float *f, GLubyte *b) {
	int i;
	for (i = 0; i < n; i++)
		b[i] = ceil(f[i] * 255);
}

static void array_float_to_ubyte(int n, const float *f, GLubyte *b) {
	int i;
	for (i = 0; i < n; i++)
		b[i] = f[i] * 255;
}

static void print_components_ubyte(const GLubyte *pixel, unsigned components) {
	int p;
	for (p = 0; p < components; ++p)
		LOGI(" %u", pixel[p]);
}

static void print_bad_pixel_ubyte(int x, int y, int num_components,
		      const GLubyte *expected, const GLubyte *observed) {
	LOGI("Probe color at (%i,%i)\n", x, y);
	LOGI("  Expected:");
	print_components_ubyte(expected, num_components);
	LOGI("\n  Observed:");
	print_components_ubyte(observed, num_components);
	LOGI("\n");
}

static void print_components_float(const float *pixel, unsigned components) {
	int p;
	for (p = 0; p < components; ++p)
		LOGI(" %f", pixel[p]);
}

static void print_bad_pixel_float(int x, int y, int num_components,
		      const float *expected, const float *observed) {
	LOGI("Probe color at (%i,%i)\n", x, y);
	LOGI("  Expected:");
	print_components_float(expected, num_components);
	LOGI("\n  Observed:");
	print_components_float(observed, num_components);
	LOGI("\n");
}

bool piglit_probe_rect_rgba(int x, int y, int w, int h, const float *fexpected) {
	int     r    = 0, g = 0, b = 0, a = 0, read;
	int     i, j, k;
	GLubyte expected[4];
	bool    isUB = true;

	glGetIntegerv(GL_READ_BUFFER, &read);
	LOGI("glGetIntegerv(GL_READ_BUFFER):%x (GL_FRONT=%x,GL_BACK=%x)\n", read, GL_FRONT, GL_BACK);
	if (read == GL_BACK) {
		glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, read, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, &r);
		glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, read, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &g);
		glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, read, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, &b);
		glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, read, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, &a);
		LOGI("GetFramebufferAttachmentParameteriv(SIZE rgba): %d %d %d %d\n", r, g, b, a);
	}
	if (!check_gl_error(GL_NO_ERROR))
	LOGE("%d:err\n", __LINE__);

	if (r <= 8 && g <= 8 && b <= 8 && a <= 8)
		isUB = true;
	else
		isUB = false;
	if (!r && !g && !b && !a)
		isUB = false;

	if (isUB) {
		array_float_to_ubyte(4, fexpected, expected);
		GLubyte *pixels = (GLubyte *)malloc(w * h * 4);
		LOGI("begin\n");
		glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		LOGI("end\n");

		for (j = 0; j < h; j++) {
			for (i = 0; i < w; i++) {
				GLubyte *probe = &pixels[(j * w + i) * 4];
				print_bad_pixel_ubyte(x + i, y + j, 4, expected, probe);
			}
		}
		free(pixels);
		LOGI("test ubyte\n");
	} else {
		int     comps     = piglit_num_components(GL_RGBA);
		float   *pixels   = (float *)malloc(w * h * comps * sizeof(GLfloat));
		GLubyte *pixels_b = (GLubyte *)malloc(w * h * 4 * sizeof(GLubyte));
		LOGI("begin\n");
		glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels_b);
		LOGI("end\n");
		k      = 0;
		for (i = 0; i < w * h; i++) {
			for (j = 0; j < comps; j++) {
				pixels[k++] = pixels_b[i * 4 + j] / 255.0f;
			}
		}
		free(pixels_b);

		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				float *probe = &pixels[(j * w + i) * 4];
				print_bad_pixel_float(x + i, y + j, 4, fexpected, probe);
			}
		}
		free(pixels);
		LOGI("test float\n");
	}
	return true;
}

void renderFrame(void) {
	bool                 pass    = true;
	static const GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
	static const GLfloat red[]   = {1.0, 0.0, 0.0, 1.0};

	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	GLenum buffersb[] = {GL_BACK};
	glDrawBuffers(1, buffersb);
	glClearColor(1, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glReadBuffer(GL_BACK);
	LOGI("GL_BACK\n");
	pass = piglit_probe_rect_rgba(0, 0, WINDOW_W, WINDOW_H, green) && pass;

	GLenum buffersf[] = {GL_NONE};
	glDrawBuffers(1, buffersf);
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glReadBuffer(GL_NONE);
	LOGI("GL_NONE\n");
	pass = piglit_probe_rect_rgba(0, 0, WINDOW_W, WINDOW_H, red) && pass;

	if (!check_gl_error(GL_NO_ERROR))
		pass = false;
	LOGE("test result:%d\n", pass);
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
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
