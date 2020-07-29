/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file bindbufferrange.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for bindbufferrange related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
};

const float triangleVerticesLittle[] = {
    -0.45f, -0.45f, 0.0f,
     0.45f, -0.45f, 0.0f,
     0.0f,  0.45f, 0.0f,
     0.0f, -0.45f, 0.0f
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

const int triangleColorsI[] = {
    1, 0, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1
};

const GLubyte indices[] = {0,1,2};
const GLubyte subdata[] = {1,3};
static const GLint vertices [] = {
		0, -2,
		-52, 32,
		0, 2,
		2, 0,
		15, 153,
		-2, 0
};

static const GLfloat color[] = {
		0.0, 1.0, 0.0,
		10.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 110.0, 0.0,
		0.0, 0.0, 1.0
};

const float triangleVertices2[] = {
     0.0f,-0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
};

const float triangleColors2[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
};

string vertexShaderFilename = "es30-ClearBufferColorFormat.vert";
string fragmentShaderFilename = "es30-ClearBufferColorFormat.frag";

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;

static const float fcolor[4][4] = {
		{0.5, 0.3, 0.7,  0.0},
		{0.5, 2.5, -5.2, 1.0}
};


static const unsigned int  uicolor[3][4] = {
		{10,  90,  100, 150},
		{100, 190, 200, 15},
		{15,  25,  20,  15}
};


static const int  icolor[3][4] = {
		{-10, -90, 100, 15},
		{100, 190, 200, -15},
		{-50, -50, -50, 50}
};

static const struct {
	GLenum rb_format;
	GLenum type;
	const GLvoid *clear_color; 
} test_vectors[] = {{GL_RGBA8,    GL_FLOAT,        (const GLvoid *)fcolor[0]},
					{GL_RGBA8UI,  GL_UNSIGNED_INT, (const GLvoid *)uicolor[0]},
					{GL_RGBA32UI, GL_UNSIGNED_INT, (const GLvoid *)uicolor[2]},
					{GL_RGBA16I,  GL_INT,          (const GLvoid *)icolor[1]},
					{GL_RGBA32I,  GL_INT,          (const GLvoid *)icolor[2]},
};

#define COUNT ARRAY_NUM(test_vectors)
GLuint generate_fbo(void) {
	GLuint fb;
	GLuint rb[COUNT];
	GLuint i;
	GLenum status;
	GLenum drawbuffers[COUNT];

	glGenFramebuffers(1, &fb);
	glBindFramebuffer(GL_FRAMEBUFFER, fb);
	glGenRenderbuffers(COUNT, rb);

	for (i = 0; i < COUNT; i++) {
		drawbuffers[i] = GL_COLOR_ATTACHMENT0 + i;
		glBindRenderbuffer(GL_RENDERBUFFER, rb[i]);
		glRenderbufferStorage(GL_RENDERBUFFER, test_vectors[i].rb_format,
							  WINDOW_W, WINDOW_H);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
								  GL_RENDERBUFFER, rb[i]);

		if (!check_gl_error(GL_NO_ERROR))
		LOGE("Failed!\n");
	}

	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		LOGI("Framebuffer with color"
			 "attachment was not complete: 0x%04x\n",
			 status);
		LOGE("Failed!\n");
	}

	if (status == GL_FRAMEBUFFER_UNSUPPORTED) {
		glDeleteRenderbuffers(COUNT, rb);
		glDeleteFramebuffers(1, &fb);
		return 0;
	}

	glDrawBuffers(COUNT, drawbuffers);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!check_gl_error(GL_NO_ERROR))
		LOGI("Failed!\n");
	return fb;
}

int piglit_probe_rect_rgba_int(int x, int y, int w, int h, const int *expected) {
	int   i, j, p;
	GLint *probe;
	GLint *pixels = (GLint *)malloc(w * h * 4 * sizeof(int));

	glReadPixels(x, y, w, h, GL_RGBA_INTEGER, GL_INT, pixels);

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			probe  = &pixels[(j * w + i) * 4];
			for (p = 0; p < 4; ++p) {
				LOGI("Probe color at (%d,%d)\n", x + i, y + j);
				LOGI("  Expected: %d %d %d %d\n",
					 expected[0], expected[1], expected[2], expected[3]);
				LOGI("  Observed: %d %d %d %d\n",
					 probe[0], probe[1], probe[2], probe[3]);
				if (probe[p] != expected[p]) {
					free(pixels);
					return 0;
				}
			}
		}
	}
	free(pixels);
	return 1;
}

int piglit_probe_rect_rgba_uint(int x, int y, int w, int h, 
								const unsigned int *expected) {
	int    i, j, p;
	GLuint *probe;
	GLuint *pixels = (GLuint *)malloc(w * h * 4 * sizeof(unsigned int));

	glReadPixels(x, y, w, h, GL_RGBA_INTEGER, GL_UNSIGNED_INT, pixels);

	for (j = 0; j < h; j++) {
		for (i = 0; i < w; i++) {
			probe  = &pixels[(j * w + i) * 4];
			for (p = 0; p < 4; ++p) {
				LOGI("Probe color at (%d,%d)\n", x + i, y + j);
				LOGI("  Expected: %u %u %u %u\n", expected[0], expected[1],
					 expected[2], expected[3]);
				LOGI("  Observed: %u %u %u %u\n", probe[0], probe[1], probe[2],
					 probe[3]);
				if (probe[p] != expected[p]) {
					free(pixels);
					return 0;
				}
			}
		}
	}
	free(pixels);
	return 1;
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

static void print_pixel_ubyte(int x, int y, int num_components,
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

static void print_pixel_float(int x, int y, int num_components,
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

	glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, read, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, &r);
	glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, read, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &g);
	glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, read, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, &b);
	glGetFramebufferAttachmentParameteriv(GL_READ_FRAMEBUFFER, read, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, &a);

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
				print_pixel_ubyte(x + i, y + j, 4, expected, probe);
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
				print_pixel_float(x + i, y + j, 4, fexpected, probe);
			}
		}
		free(pixels);
		LOGI("test float\n");
	}
	return true;
}

bool probe_rect_color(int x, int y, int w, int h, GLenum type, const GLvoid *refcolor) {
	if (type == GL_FLOAT)
		return piglit_probe_rect_rgba(x, y, w, h, (const float*)refcolor);
	else if (type == GL_UNSIGNED_INT) {
		LOGI("GL_UNSIGNED_INT\n");
		return piglit_probe_rect_rgba_uint(x, y, w, h, (const unsigned int*)refcolor);
	}
	else if (type == GL_INT)
		return piglit_probe_rect_rgba_int(x, y, w, h, (const int*)refcolor);
	else
		type == GL_INT || type == GL_UNSIGNED_INT || type == GL_FLOAT;
	return true;
}

bool setupGraphics(int width, int height) {
	GLuint fb;
	bool   pass = true;
	int    i, j, k;
	LOGI("COUNT:%d\n", COUNT);
	fb = generate_fbo();

	for (i = 0; i < COUNT; i++) {
		switch (test_vectors[i].type) {
		case GL_FLOAT:
			glClearBufferfv(GL_COLOR, i, (GLfloat *)test_vectors[i].clear_color);
			LOGI("GL_FLOAT\n");
			break;
		case GL_INT:
			glClearBufferiv(GL_COLOR, i, (GLint *)test_vectors[i].clear_color);
			LOGI("GL_INT\n");
			break;
		case GL_UNSIGNED_INT:
			glClearBufferuiv(GL_COLOR, i, (GLuint *)test_vectors[i].clear_color);
			LOGI("GL_UNSIGNED_INT\n");
			break;
		}
	}

	for (i = 0; i < COUNT; i++) {
		glReadBuffer(GL_COLOR_ATTACHMENT0 + i);
		if (!probe_rect_color(0, 0, width, height, test_vectors[i].type,
							  test_vectors[i].clear_color)) {
			LOGI("  from color attachment %i.\n", i);
			pass = GL_FALSE;
		}
	}

	glDeleteFramebuffers(1, &fb);
	pass = check_gl_error(GL_NO_ERROR) && pass;
	return pass;
}

void Sample::test() {
	LOGI("test result:%d\n",setupGraphics(WINDOW_W, WINDOW_H));
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
