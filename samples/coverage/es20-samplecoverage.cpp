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

using std::string;
using namespace BotsonSDK;

const float Vertices[] = {
    0.25, 0.05,
    0.9, 0.2,
    0.25, 0.0,
    0.9, 0.0,
    0.875, 0.10
};

const float lineColors[] = {
    1.0, 1.0, 1.0,1.0
};

const float triColors[] = {
    0.0, 1.0, 1.0,1.0
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

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";
    glEnable(GL_DEPTH_TEST);
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition = glGetAttribLocation(programID, "a_v4Position");
    iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor");
    GLint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
	glSampleCoverage(1.0,GL_TRUE);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    glEnable (GL_SAMPLE_COVERAGE);
    GLint buf[1], sbuf[1];
    glGetIntegerv (GL_SAMPLE_BUFFERS, buf);
    LOGI ("number of sample buffers is %d\n", buf[0]);
    glGetIntegerv (GL_SAMPLES, sbuf);
    LOGI ("number of samples is %d\n", sbuf[0]);

    return true;
}

void renderFrame(void) {
    GLfloat polyfactor = -1.0;
    GLfloat polyunits = -1.0;
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(polyfactor, polyunits);
    GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, Vertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if(iLocFillColor != -1) {
	glVertexAttrib4f(iLocFillColor, 1.0, 1.0, 1.0,1.0);
    }

    GL_CHECK(glDrawArrays(GL_LINES, 0, 2));
    glDisable(GL_POLYGON_OFFSET_FILL);
    GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, Vertices+4));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if(iLocFillColor != -1) {
	glVertexAttrib4f(iLocFillColor, 0.0, 1.0, 1.0,1.0);
    }
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	GLint parami;
	GLboolean paramb;
	for(int i=0; i<ARRAY_NUM(getfactorsI); i++) {
		string parami_name=get_enum_name(getfactorsI[i]);
		glGetIntegerv(getfactorsI[i], &parami);
		LOGI("Get(%s): %d",parami_name.c_str(), parami);
	}
	for(int i=0; i<ARRAY_NUM(getfactorsB); i++) {
		string paramb_name=get_enum_name(getfactorsB[i]);
		glGetBooleanv(getfactorsB[i], &paramb);
		LOGI("Get(%s): %d",paramb_name.c_str(), paramb);
	}
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
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
