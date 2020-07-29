/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file framebufferparam.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for framebufferparam related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
//#include <GLES3/gl31.h>

using std::string;
using namespace BotsonSDK;
using namespace std;

GLenum target[] = {
	GL_READ_FRAMEBUFFER,
	GL_DRAW_FRAMEBUFFER,
	GL_FRAMEBUFFER
};

GLenum pname[] = {
	GL_FRAMEBUFFER_DEFAULT_WIDTH,
	GL_FRAMEBUFFER_DEFAULT_HEIGHT,
	GL_FRAMEBUFFER_DEFAULT_SAMPLES,
	GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS
};

GLuint prog;

GLint iLocPosition = -1;
GLuint vao;

GLenum factors[] = {
	GL_POINTS,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_LINES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_TRIANGLES
};

typedef struct {
	GLuint count;
	GLuint instanceCount;
	GLuint first;
	GLuint reservedMustBeZero;
} DrawArraysIndirectCommand;

void draw_rect(float z, float x, float y, float w, float h)
{
   GLfloat verts[4][4];

   verts[0][0] = x;
   verts[0][1] = y;
   verts[0][2] = z;
   verts[0][3] = 1.0;
   verts[1][0] = x + w;
   verts[1][1] = y;
   verts[1][2] = z;
   verts[1][3] = 1.0;
   verts[2][0] = x;
   verts[2][1] = y + h;
   verts[2][2] = z;
   verts[2][3] = 1.0;
   verts[3][0] = x + w;
   verts[3][1] = y + h;
   verts[3][2] = z;
   verts[3][3] = 1.0;

   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

   glUseProgram(prog);
   glVertexAttribPointer(iLocPosition, 4, GL_FLOAT, false, 4 * sizeof(GLfloat), verts);
   glEnableVertexAttribArray(iLocPosition);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

static void reset_counter()
{
	uint32_t *ptr =  (uint32_t *) glMapBufferRange(GL_ATOMIC_COUNTER_BUFFER, 0,
			sizeof(uint32_t), GL_MAP_WRITE_BIT);
	*ptr = 0;
	glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);
}

static bool compare_counter(uint32_t value, const char *subtest)
{
	bool result = false;
	uint32_t *ptr = (uint32_t *) glMapBufferRange(GL_ATOMIC_COUNTER_BUFFER, 0,
			sizeof(uint32_t), GL_MAP_READ_BIT);
	result = (*ptr == value);
	if (!result)
		printf("%s (subtest %s): expected %u, got %u\n",			__func__, subtest, value, *ptr);
	glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);
	LOGI("result: %d", result);
	return result;
}

bool setupGraphics(int width, int height)
{
	string vertexShaderPath = (string)GLSL_PATH + "atomicCounterIncrement.vert";
	string fragmentShaderPath = (string)GLSL_PATH + "atomicCounterIncrement.frag";

	prog = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

	GL_CHECK(glUseProgram(prog));
	GL_CHECK(iLocPosition = glGetAttribLocation(prog, "piglit_vertex"));

	GL_CHECK(glViewport(0, 0, width, height));

	return true;
}

void renderFrame()
{
	GLuint buffer, fbo, vao;
	GLint prog;
	bool pass = true;
	uint32_t counter = 0;

	/* Create fbo with no attachments. */
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	/* Setup default width and height. */
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, WINDOW_W);
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, WINDOW_H);

	/* Check that fbo is marked complete. */
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOGE("FAIL!\n");

	/* Check that there are no errors. */
	if (!prog || !check_gl_error(GL_NO_ERROR))
		LOGE("FAIL!\n");

	glUseProgram(prog);

	/* Create atomic counter buffer. */
	glGenBuffers(1, &buffer);
	glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, buffer);
	glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(uint32_t), &counter, GL_DYNAMIC_DRAW);

	if (!check_gl_error(GL_NO_ERROR))
		LOGE("FAIL!\n");

	/* Render rectangle using our program. */
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	draw_rect(0, -0.8, -0.8, 1.6, 1.6);

	pass &= compare_counter(WINDOW_W * WINDOW_H, "Basic");

	/* Reset counter and set 1x1 scissor rectangle. */
	reset_counter();

	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 0, 1, 1);

	draw_rect(0, -0.8, -0.8, 1.6, 1.6);

	glDisable(GL_SCISSOR_TEST);

	pass &= compare_counter(1, "glScissor");

	/* Reset counter and set 2x2 viewport. */
	reset_counter();
	glViewport(0, 0, 2, 2);

	draw_rect(0, -0.8, -0.8, 1.6, 1.6);

	pass &= compare_counter(4, "glViewport");

	/* Reset counter and add samples to the default fb */
	reset_counter();
	glViewport(0, 0, WINDOW_W, WINDOW_H);
	glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 4);

	draw_rect(0, -0.8, -0.8, 1.6, 1.6);

	reset_counter();
	//glEnable(GL_SAMPLE_SHADING);
	//glMinSampleShading(1.0);

	draw_rect(0, -0.8, -0.8, 1.6, 1.6);

	pass &= compare_counter(WINDOW_W * WINDOW_H * 4, "Per-sample");

	glDeleteFramebuffers(1, &fbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &buffer);
	glDeleteProgram(prog);
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	renderFrame();
	string bmp_file  = filename + ".bmp";
	LOGI("bmp_file=%s", bmp_file.c_str());
	save2bmp(bmp_file.c_str());
	Sample::SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}

//int main(int argc, char **argv)
//{
//    string file = "es31-framebufferparam";
//
//    GBtest_init(&argc,argv,file);
//    Platform * platform = Platform::getInstance();
//    platform->createWindow(WINDOW_W, WINDOW_H);
//    EGLRuntime::initializeEGL(EGLRuntime::OPENGLES31);
//    EGL_CHECK(eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context));
//    setupGraphics(WINDOW_W, WINDOW_H);
//#ifndef DUMP
//    while(1) {
//#endif
//        renderFrame();
//        string filename = file + ".bmp";
//        EGLRuntime::pixelsToPicture(filename.c_str());
//	    eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
//#ifndef DUMP
//    }
//#endif
//    EGLRuntime::terminateEGL();
//    platform->destroyWindow();
//    delete platform;
//    GBtest_deinit();
//
//    return 0;
//}
//