/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file samplecoverage.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for samplecoverage related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;

const float vertices[] = {
    0.25, 0.05, 0.0, 1.0,
    0.9, 0.2, 0.0, 1.0,
    0.25, 0.0, 0.0, 1.0,
    0.9, 0.0, 0.0, 1.0,
    0.875, 0.10, 0.0, 1.0
};

const float color[] = {
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        1.0, 0.0, 1.0, 1.0
};

GLenum getfactorsB[] = {
	GL_SAMPLE_ALPHA_TO_COVERAGE,
	GL_POLYGON_OFFSET_FILL,
	GL_SAMPLE_COVERAGE,
	GL_SAMPLE_COVERAGE_INVERT,
};

GLenum getfactorsI[] = {
	GL_SAMPLE_BUFFERS,
	GL_SAMPLE_COVERAGE_VALUE,
	GL_POLYGON_OFFSET_FACTOR,
	GL_POLYGON_OFFSET_UNITS,
};
GLuint programID, VAOs, Buffers;
bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "shader.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "shader.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(color), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color), color));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glSampleCoverage(1.0,GL_TRUE));
    GL_CHECK(glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE));
    GL_CHECK(glEnable (GL_SAMPLE_COVERAGE));
    GLint buf[1], sbuf[1];
    GL_CHECK(glGetIntegerv (GL_SAMPLE_BUFFERS, buf));
    LOGI ("number of sample buffers is %d\n", buf[0]);
    GL_CHECK(glGetIntegerv (GL_SAMPLES, sbuf));
    LOGI ("number of samples is %d\n", sbuf[0]);

    return true;
}

void renderFrame(void) {
    GLfloat polyfactor = -1.0;
    GLfloat polyunits = -1.0;
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glEnable(GL_POLYGON_OFFSET_FILL));
    GL_CHECK(glPolygonOffset(polyfactor, polyunits));
    GL_CHECK(glDrawArrays(GL_LINES, 0, 2));
    GL_CHECK(glDisable(GL_POLYGON_OFFSET_FILL));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	GLint parami;
	GLboolean paramb;
	for(int i=0; i<ARRAY_NUM(getfactorsI); i++) {
		string parami_name=get_enum_name(getfactorsI[i]);
        GL_CHECK(glGetIntegerv(getfactorsI[i], &parami));
		LOGI("Get(%s): %d\n",parami_name.c_str(), parami);
	}
	for(int i=0; i<ARRAY_NUM(getfactorsB); i++) {
		string paramb_name=get_enum_name(getfactorsB[i]);
        GL_CHECK(glGetBooleanv(getfactorsB[i], &paramb));
		LOGI("Get(%s): %d\n",paramb_name.c_str(), paramb);
	}
}

void getstring(void) {
    const char *renderer = (const char *) GL_CHECK(glGetString(GL_RENDERER));
    const char *version = (const char *) GL_CHECK(glGetString(GL_VERSION));
    const char *vendor = (const char *) GL_CHECK(glGetString(GL_VENDOR));

    LOGI("GL_RENDERER = %s\n", renderer);
    LOGI("GL_VERSION = %s\n", version);
    LOGI("GL_VENDOR = %s\n", vendor);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    getstring();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s\n",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
