/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file fboscissorblit.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for fboscissorblit related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programObject;

static GLuint src_fbo;
static GLuint ref_fbo;
static GLuint dst_fbo;
unsigned piglit_winsys_fbo = 0;
static const int width = 128, height = 128;

float piglit_tolerance[4] = { 0.01, 0.01, 0.01, 0.01 };

static GLuint setup_framebuffer() {
	GLuint fbo, rb;

	glGenRenderbuffers(1, &rb);
	glBindRenderbuffer(GL_RENDERBUFFER, rb);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
							  GL_RENDERBUFFER, rb);
	if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER)
	    != GL_FRAMEBUFFER_COMPLETE) {
		LOGI("Framebuffer incomplete\n");
	}
	return fbo;
}

int Init ( ) {
	src_fbo = setup_framebuffer();
	ref_fbo = setup_framebuffer();
	dst_fbo = setup_framebuffer();
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

void piglit_compute_probe_tolerance(GLenum format, float *tolerance) {
	int num_components, component;
	switch (format) {
	case GL_LUMINANCE_ALPHA:
		tolerance[0] = piglit_tolerance[0];
		tolerance[1] = piglit_tolerance[3];
		break;
	case GL_ALPHA:
		tolerance[0] = piglit_tolerance[3];
		break;
	default:
		num_components = piglit_num_components(format);
		for (component = 0; component < num_components; ++component)
			tolerance[component] = piglit_tolerance[component];
		break;
	}
}

static GLfloat* read_pixels_float(GLint x, GLint y, GLsizei width, GLsizei height,
		  GLenum format, GLfloat *pixels) {
	GLubyte *pixels_b;
	unsigned i, j, k;
	int comps = piglit_num_components(format);

	if (!pixels)
		pixels = (GLfloat *)malloc(width * height * comps * sizeof(GLfloat));

	pixels_b = (GLubyte *)malloc(width * height * 4 * sizeof(GLubyte));
	glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels_b);
	k = 0;
	for (i = 0; i < width * height; i++) {
		for (j = 0; j < comps; j++) {
			pixels[k++] = pixels_b[i*4+j] / 255.0f;
		}
	}
	free(pixels_b);
	return pixels;
}

static bool
compare_pixels_float(const float *color1, const float *color2,
		     const float *tolerance, int components) {
	for (int p = 0; p < components; ++p)
		if (fabsf(color1[p] - color2[p]) > tolerance[p])
			return false;
	return true;
}

static void print_components_float(const float *pixel, unsigned components) {
	int p;
	for (p = 0; p < components; ++p)
		LOGI(" %f", pixel[p]);
}

int piglit_compare_images_color(int x, int y, int w, int h, int num_components,
			    const float *tolerance, const float *expected_image,
			    const float *observed_image) {
	int i, j;
	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			const float *expected =
				&expected_image[((j + y) * w + i + x) *
						num_components];
			const float *probe =
				&observed_image[((j + y) * w + i + x) *
						num_components];

			if (compare_pixels_float(probe, expected, tolerance,
						 num_components))
				continue;

			LOGI("Probe at (%i,%i)\n", x+i, y+j);
			LOGI("  Expected:");
			print_components_float(expected, num_components);
			LOGI("\n  Observed:");
			print_components_float(probe, num_components);
			LOGI("\n");

			return 0;
		}
	}
	return 1;
}
int piglit_probe_image_color(int x, int y, int w, int h, GLenum format,
							 const float *image) {
	int c = piglit_num_components(format);
	GLfloat *pixels;
	float tolerance[4];
	int result;

	piglit_compute_probe_tolerance(format, tolerance);
	pixels = read_pixels_float(x, y, w, h, format, NULL);
	result = piglit_compare_images_color(0, 0, w, h, c, tolerance, image, pixels);

	free(pixels);
	return result;
}

GLboolean renderFrame(void) {
	float red[4]   = {1.0, 0.0, 0.0, 0.0};
	float green[4] = {0.0, 1.0, 0.0, 0.25};
	float blue[4]  = {0.0, 0.0, 1.0, 0.5};
	float white[4] = {1.0, 1.0, 1.0, 1.0};
	float grey[4]  = {0.5, 0.5, 0.5, 0.5};
	bool  pass;
	float *ref_image;

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, src_fbo);
	glEnable(GL_SCISSOR_TEST);

	glScissor(0, 0, width / 2, height / 2);
	glClearColor(red[0], red[1], red[2], red[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	glScissor(width / 2, 0, width / 2, height / 2);
	glClearColor(green[0], green[1], green[2], green[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	glScissor(0, height / 2, width / 2, height / 2);
	glClearColor(blue[0], blue[1], blue[2], blue[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	glScissor(width / 2, height / 2, width / 2, height / 2);
	glClearColor(white[0], white[1], white[2], white[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_SCISSOR_TEST);

	glClearColor(grey[0], grey[1], grey[2], grey[3]);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, src_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dst_fbo);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_SCISSOR_TEST);
	glScissor(10, 20, width - 40, height - 60);
	glBlitFramebuffer(0, 0, width, height,
					  0, 0, width, height,
					  GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glDisable(GL_SCISSOR_TEST);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, src_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ref_fbo);
	glClear(GL_COLOR_BUFFER_BIT);
	glBlitFramebuffer(10, 20, width - 30, height - 40,
					  10, 20, width - 30, height - 40,
					  GL_COLOR_BUFFER_BIT, GL_NEAREST);

	ref_image = (float *)malloc(sizeof(float) * 4 * width * height);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, ref_fbo);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_FLOAT, ref_image);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, dst_fbo);
	pass = piglit_probe_image_color(0, 0, width, height, GL_RGBA, ref_image);

	if (dst_fbo != 0) {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, dst_fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, piglit_winsys_fbo);
		glBlitFramebuffer(0, 0, width, height,
						  0, 0, width, height,
						  GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}
	return pass;
}


void Sample::test() {
	Init();
	renderFrame();
	string bmp_file = filename + ".bmp";
	LOGI("bmp_file=%s",bmp_file.c_str());
	LOGI("test result: %s !\n", renderFrame()==GL_TRUE? "PASS" : "FAIL");
	save2bmp(bmp_file.c_str());
	Sample::SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
