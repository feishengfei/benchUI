/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file points.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for points related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const float Vertices[] = {
    -0.4f,  0.0f, 0.0f,
    -0.2f,  0.0f, 0.0f,
     0.0f,  0.0f, 0.0f,
     0.2f,  0.0f, 0.0f,
     0.4f,  0.0f, 0.0f
};

float Vertices0[] = {
    -0.8f,  0.4f, 0.0f,
    -0.8f, -0.4f, 0.0f
};

float Vertices1[] = {
    -0.4f,  0.4f, 0.0f,
    -0.4f, -0.4f, 0.0f
};

float Vertices2[] = {
     0.0f,  0.4f, 0.0f,
     0.0f, -0.4f, 0.0f
};

float Vertices3[] = {
     0.4f,  0.4f, 0.0f,
     0.4f, -0.4f, 0.0f
};

float Vertices4[] = {
     0.8f,  0.4f, 0.0f,
     0.8f, -0.4f, 0.0f
};

const float Colors[] = {
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0
};

const float Sizes[] = { 1.0, 5.0, 10.0, 15.0, 20.0};
GLint Sizes0[] = { 1, 10 };
GLuint Sizes1[] = { 2, 9 };
float Sizes2[] = { 4.2, 7.3 };
GLshort Sizes3[] = { 6, 5 };
GLushort Sizes4[] = { 8, 3 };

const GLubyte indices[] = {0,1,2,3,4};
string vertexShaderFilename = "Points3.vert";
string fragmentShaderFilename = "Points3.frag";

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLint iLocPointSize = -1;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
int size=6;
GLhalf Sizes5[2];

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGD("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGD("fragmentShaderID = %d", fragmentShaderID);

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
    iLocPointSize = glGetAttribLocation(programID, "a_PointSize");

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));
    return true;
}

GLhalf Float2Half(float value) {
	GLhalf fltInt16;
	int fltInt32;
	memcpy(&fltInt32, &value, sizeof(float));
	fltInt16 = ((fltInt32 & 0x7fffffff) >> 13) - (0x38000000 >> 13);
	fltInt16 |= ((fltInt32 & 0x80000000) >> 16);
	return fltInt16;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPointSize));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Vertices0));
    GL_CHECK(glVertexAttribPointer(iLocPointSize, 1, GL_INT, GL_FALSE, 0, Sizes0));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 2));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Vertices1));
    GL_CHECK(glVertexAttribPointer(iLocPointSize, 1, GL_UNSIGNED_INT, GL_FALSE,
                                   0, Sizes1));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 2));

    for (int i = 0; i < 2; i++) {
        Sizes5[i] = Float2Half(Sizes2[i]);
    }

    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Vertices2));
    GL_CHECK(glVertexAttribPointer(iLocPointSize, 1, GL_HALF_FLOAT, GL_FALSE, 0, Sizes2));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 2));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Vertices3));
    GL_CHECK(glVertexAttribPointer(iLocPointSize, 1, GL_SHORT, GL_FALSE, 0, Sizes3));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 2));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Vertices4));
    GL_CHECK(glVertexAttribPointer(iLocPointSize, 1, GL_UNSIGNED_SHORT, GL_FALSE,
                                   0, Sizes4));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 2));
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
