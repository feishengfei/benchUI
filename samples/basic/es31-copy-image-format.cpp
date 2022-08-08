/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file copy-image-format.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for copy-image-format related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

#define WIDTH 16
#define HEIGHT 16

enum piglit_result {
PIGLIT_FAIL,
PIGLIT_PASS,
};

const struct image_format {
	const char *name;
	GLenum format;
	GLenum pixel_format;
	GLenum pixel_type;
} image_formats[] = {
	{ "rgba32f", GL_RGBA32F, GL_RGBA, GL_FLOAT },
	{ "rgba16f", GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT },
	{ "rgba32ui", GL_RGBA32UI, GL_RGBA, GL_UNSIGNED_INT },
	{ "rgba16ui", GL_RGBA16UI, GL_RGBA, GL_UNSIGNED_SHORT },
	{ "rgba8ui", GL_RGBA8UI, GL_RGBA, GL_UNSIGNED_BYTE },
	{ "rgba32i", GL_RGBA32I, GL_RGBA, GL_INT },
	{ "rgba16i", GL_RGBA16I, GL_RGBA, GL_SHORT },
	{ "rgba8i", GL_RGBA8I, GL_RGBA, GL_BYTE },
	{ "rgba8", GL_RGBA8, GL_RGBA, GL_BYTE },
	{ "rgba8_snorm", GL_RGBA8_SNORM, GL_RGBA, GL_BYTE },
};

static const char *
glsl_image_type_name(GLenum format)
{
	switch (format) {
	case GL_RGBA32F:
	case GL_RGBA16F:
	case GL_R32F:
	case GL_RGBA8:
	case GL_RGBA8_SNORM:
		return "image";
	case GL_RGBA32UI:
	case GL_RGBA16UI:
	case GL_RGBA8UI:
	case GL_R32UI:
		return "uimage";
	case GL_RGBA32I:
	case GL_RGBA16I:
	case GL_RGBA8I:
	case GL_R32I:
		return "iimage";
	default:
		LOGD("Unsupported format\n");
		return "";
	}
}

static const char *glsl_type_name(GLenum format)
{
	switch (format) {
	case GL_RGBA32F:
	case GL_RGBA16F:
	case GL_R32F:
	case GL_RGBA8:
	case GL_RGBA8_SNORM:
		return "highp vec4";
	case GL_RGBA32UI:
	case GL_RGBA16UI:
	case GL_RGBA8UI:
	case GL_R32UI:
		return "highp uvec4";
	case GL_RGBA32I:
	case GL_RGBA16I:
	case GL_RGBA8I:
	case GL_R32I:
		return "highp ivec4";
	default:
		LOGD("Unsupported format\n");
		return "";
	}
}

static bool run_test(const struct image_format *image_format) {
	GLuint src, dst, prog;
	char   *fs_source;

	glGenTextures(1, &src);
	glBindTexture(GL_TEXTURE_2D, src);
	glTexStorage2D(GL_TEXTURE_2D, 1, image_format->format, WIDTH, HEIGHT);
	glBindImageTexture(0, src, 0, GL_FALSE, 0, GL_READ_ONLY, image_format->format);

	glGenTextures(1, &dst);
	glBindTexture(GL_TEXTURE_2D, dst);
	glTexStorage2D(GL_TEXTURE_2D, 1, image_format->format, WIDTH, HEIGHT);
	glBindImageTexture(0, dst, 0, GL_FALSE, 0, GL_WRITE_ONLY, image_format->format);

	fs_source = NULL;
	asprintf(&fs_source,
			 "#version 310 es\n"
			 "\n"
			 "layout(%s) readonly uniform highp %s2D img_src;\n"
			 "layout(%s) writeonly uniform highp %s2D img_dst;\n"
			 "\n"
			 "void main() {\n"
			 "  %s v = imageLoad(img_src, ivec2(gl_FragCoord));\n"
			 "  imageStore(img_dst, ivec2(gl_FragCoord), v);\n"
			 "}",
			 image_format->name,
			 glsl_image_type_name(image_format->format),
			 image_format->name,
			 glsl_image_type_name(image_format->format),
			 glsl_type_name(image_format->format));

	const char *vs_source = {
			"#version 310 es\n"
			"\n"
			"in vec4 piglit_vertex;\n"
			"void main() {\n"
			"  gl_Position = piglit_vertex;\n"
			"}"};

	const char *strings[1] = {NULL};
	strings[0] = vs_source;
	GLuint vs_shader = GL_CHECK(glCreateShader(GL_VERTEX_SHADER));
	GL_CHECK(glShaderSource(vs_shader, 1, strings, NULL));

	GL_CHECK(glCompileShader(vs_shader));
	GLint status;
	GL_CHECK(glGetShaderiv(vs_shader, GL_COMPILE_STATUS, &status));

	if (status != GL_TRUE) {
		GLint length;
		char  *debugSource = NULL;
		char  *errorLog    = NULL;

		GL_CHECK(glGetShaderiv(vs_shader, GL_SHADER_SOURCE_LENGTH, &length));
		debugSource = (char *)malloc(length);
		GL_CHECK(glGetShaderSource(vs_shader, length, NULL, debugSource));
		LOGE("Debug source START:\n%s\nDebug source END\n\n", debugSource);
		free(debugSource);

		GL_CHECK(glGetShaderiv(vs_shader, GL_INFO_LOG_LENGTH, &length));
		errorLog = (char *)malloc(length);
		GL_CHECK(glGetShaderInfoLog(vs_shader, length, NULL, errorLog));
		LOGE("Log START:\n%s\nLog END\n\n", errorLog);
		free(errorLog);

		LOGE("Compilation FAILED!\n\n");
		exit(1);
	}

	strings[0] = NULL;
	strings[0] = fs_source;
	GLuint fs_shader = GL_CHECK(glCreateShader(GL_FRAGMENT_SHADER));
	GL_CHECK(glShaderSource(fs_shader, 1, strings, NULL));

	GL_CHECK(glCompileShader(fs_shader));
	GL_CHECK(glGetShaderiv(fs_shader, GL_COMPILE_STATUS, &status));

	if (status != GL_TRUE) {
		GLint length;
		char  *debugSource = NULL;
		char  *errorLog    = NULL;

		GL_CHECK(glGetShaderiv(fs_shader, GL_SHADER_SOURCE_LENGTH, &length));
		debugSource = (char *)malloc(length);
		GL_CHECK(glGetShaderSource(fs_shader, length, NULL, debugSource));
		LOGE("Debug source START:\n%s\nDebug source END\n\n", debugSource);
		free(debugSource);

		GL_CHECK(glGetShaderiv(fs_shader, GL_INFO_LOG_LENGTH, &length));
		errorLog = (char *)malloc(length);
		GL_CHECK(glGetShaderInfoLog(fs_shader, length, NULL, errorLog));
		LOGE("Log START:\n%s\nLog END\n\n", errorLog);
		free(errorLog);

		LOGE("Compilation FAILED!\n\n");
		exit(1);
	}

	free(fs_source);
	prog = GL_CHECK(glCreateProgram());
	if (prog == 0) {
		LOGE("Could not create program.");
		return false;
	}
	GL_CHECK(glAttachShader(prog, vs_shader));
	GL_CHECK(glAttachShader(prog, fs_shader));
	GL_CHECK(glLinkProgram(prog));

	GLuint iLocPosition = glGetAttribLocation(prog, "piglit_vertex");
	glUseProgram(prog);

	float verts[4][4];
	float x             = -0.8, y = -0.8, w = 1.6, h = 1.6;
	verts[0][0] = x;
	verts[0][1] = y;
	verts[0][2] = 0.0;
	verts[0][3] = 1.0;
	verts[1][0] = x + w;
	verts[1][1] = y;
	verts[1][2] = 0.0;
	verts[1][3] = 1.0;
	verts[2][0] = x;
	verts[2][1] = y + h;
	verts[2][2] = 0.0;
	verts[2][3] = 1.0;
	verts[3][0] = x + w;
	verts[3][1] = y + h;
	verts[3][2] = 0.0;
	verts[3][3] = 1.0;

	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	glEnableVertexAttribArray(iLocPosition);
	glVertexAttribPointer(iLocPosition, 4, GL_FLOAT, GL_FALSE, 0, verts);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	return true;
}

void Sample::test() {
	for (int i = 0; i < sizeof(image_formats) / sizeof(image_formats[0]); ++i) {
		run_test(&image_formats[i]);
		string bmp_file = filename + string(image_formats[i].name) + ".bmp";
		LOGI("bmp_file=%s", bmp_file.c_str());
		save2bmp(bmp_file.c_str());
		Sample::SwapBuffers();
	}
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
