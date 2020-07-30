/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file fbomipmapcopypix.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for fbomipmapcopypix related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint test_framebuffer;
GLuint aux_framebuffer;
GLuint test_texture;
GLuint aux_texture;
GLenum texture_internal_format;
GLenum texture_format;
GLenum readback_format;
GLenum texture_type;

GLbitfield blit_mask;
GLenum framebuffer_attachment;

float piglit_tolerance[4] = { 0.01, 0.01, 0.01, 0.01 };

#define LOG2_SIZE 7
#define SIZE (1 << LOG2_SIZE)
#define NUM_LEVELS (LOG2_SIZE + 1)

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

static void create_test_data_rgba(GLfloat *data, unsigned level,
		      unsigned width, unsigned height) {
	unsigned pixel;
	unsigned num_pixels = width * height;
	for (pixel = 0; pixel < num_pixels; ++pixel) {
		unsigned unique_value = level * (SIZE * SIZE) + pixel;
		data[4*pixel + 0] = (unique_value % 233) / 233.0;
		data[4*pixel + 1] = (unique_value % 239) / 239.0;
		data[4*pixel + 2] = (unique_value % 241) / 241.0;
		data[4*pixel + 3] = (unique_value % 251) / 251.0;
	}
}

static void create_test_data_depth(GLfloat *data, unsigned level,
		       unsigned width, unsigned height) {
	unsigned pixel;
	unsigned num_pixels = width * height;
	double depth_delta = 0.95 / num_pixels;
	double depth_value = 0;

	for (pixel = 0; pixel < num_pixels; ++pixel) {
		data[pixel] = depth_value;
		depth_value += depth_delta;
	}
}

static void create_test_data_stencil(GLbyte *data, unsigned level,
			 unsigned width, unsigned height) {
	unsigned pixel;
	unsigned num_pixels = width * height;
	for (pixel = 0; pixel < num_pixels; ++pixel) {
		unsigned i = (level * (SIZE * SIZE) + pixel) / 2;
		unsigned x = (16451 * (i + 1)) % 65521;
		if (pixel % 2 == 0)
			data[pixel] = x / 256;
		else
			data[pixel] = x % 256;
	}
}

static void create_test_data_depthstencil(GLbyte *data, unsigned level,
			      unsigned width, unsigned height) {
	unsigned i;
	GLbyte *stencil_data = (GLbyte *)malloc(width * height);
	create_test_data_stencil(stencil_data, level, width, height);

	for (i = 0; i < width * height; ++i) {
		data[4 * i] = stencil_data[i];
		data[4 * i + 1] = 0;
		data[4 * i + 2] = 0;
		data[4 * i + 3] = 0;
	}

	free(stencil_data);
}

static void create_test_data(GLfloat *data, GLenum format,
		 unsigned level, unsigned width, unsigned height) {
	switch (format) {
	case GL_RGBA:
		create_test_data_rgba(data, level, width, height);
		break;
	case GL_DEPTH_COMPONENT:
		create_test_data_depth(data, level, width, height);
		break;
	case GL_DEPTH_STENCIL:
		create_test_data_depthstencil((GLbyte *)data, level,
									  width, height);
		break;
	default:
		break;
	}
}

static GLfloat *read_pixels_float(GLint x, GLint y, GLsizei width, GLsizei height,
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

static bool compare_pixels_float(const float *color1, const float *color2,
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
			const float *probe    =
								&observed_image[((j + y) * w + i + x) *
												num_components];

			if (compare_pixels_float(probe, expected, tolerance,
									 num_components))
				continue;

			LOGI("Probe at (%i,%i)\n", x + i, y + j);
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

void Init(void) {
	unsigned level;

		texture_internal_format = GL_RGBA;
		texture_format = GL_RGBA;
		readback_format = GL_RGBA;
		texture_type = GL_FLOAT;
		framebuffer_attachment = GL_COLOR_ATTACHMENT0;
		blit_mask = GL_COLOR_BUFFER_BIT;

	glGenFramebuffers(1, &test_framebuffer);
	glGenTextures(1, &test_texture);
	glBindTexture(GL_TEXTURE_2D, test_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	for (level = 0; level < NUM_LEVELS; ++level) {
		glTexImage2D(GL_TEXTURE_2D, level, texture_internal_format, SIZE >> level,
					 SIZE >> level, 0 , texture_format, texture_type, NULL );
	}

	glGenFramebuffers(1, &aux_framebuffer);
	glGenTextures(1, &aux_texture);
	glBindTexture(GL_TEXTURE_2D, aux_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0 , texture_internal_format, SIZE, SIZE,
		     0 , texture_format, texture_type, NULL);
	glBindFramebuffer(GL_FRAMEBUFFER, aux_framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, framebuffer_attachment,
			       GL_TEXTURE_2D, aux_texture, 0 );
}

static void upload_test_data(GLuint texture, unsigned data_level,
		 unsigned upload_level, unsigned width, unsigned height) {
	GLfloat *data = (GLfloat *)malloc(SIZE * SIZE * 4 * sizeof(GLfloat));

	glBindTexture(GL_TEXTURE_2D, texture);

	create_test_data(data, texture_format, data_level, width, height);

	glTexImage2D(GL_TEXTURE_2D, upload_level, texture_internal_format,
		     width, height, 0, texture_format,
		     texture_type, data);

	free(data);
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

static bool test_image(unsigned width, unsigned height, const GLfloat *expected) {
		return piglit_probe_image_color(0, 0, width, height, readback_format, expected);
}

GLboolean renderFrame(void) {
	bool     pass  = true;
	GLfloat  *data = (GLfloat *)malloc(SIZE * SIZE * 4 * sizeof(GLfloat));
	unsigned level;

	for (level = 0; level < NUM_LEVELS; ++level) {
		unsigned width  = SIZE >> level;
		unsigned height = SIZE >> level;

		upload_test_data(aux_texture, level, 0, width, height);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, aux_framebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, test_framebuffer);
		glBindTexture(GL_TEXTURE_2D, test_texture);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, framebuffer_attachment,
							   GL_TEXTURE_2D, test_texture, level);
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
						  blit_mask, GL_NEAREST);
	}

	for (level = 0; level < NUM_LEVELS; ++level) {
		unsigned width  = SIZE >> level;
		unsigned height = SIZE >> level;
		LOGI("Testing level %d\n", level);
		create_test_data(data, readback_format, level, width, height);

		glBindFramebuffer(GL_READ_FRAMEBUFFER, test_framebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, aux_framebuffer);
		glBindTexture(GL_TEXTURE_2D, test_texture);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, framebuffer_attachment,
							   GL_TEXTURE_2D, test_texture, level);
		glBindTexture(GL_TEXTURE_2D, aux_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, texture_internal_format, width, height,
					 0, texture_format, texture_type, NULL);
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
						  blit_mask, GL_NEAREST);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, aux_framebuffer);
		pass = test_image(width, height, data) && pass;
	}
	free(data);

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
