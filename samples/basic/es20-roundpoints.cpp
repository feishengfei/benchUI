/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file roundpoints.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for roundpoints related API
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

const float Colors[] = {
    1.0, 1.0, 1.0, 0.6,
    1.0, 1.0, 1.0, 0.6,
    1.0, 1.0, 1.0, 0.6,
    1.0, 1.0, 1.0, 0.6,
    1.0, 1.0, 1.0, 0.6
};

const float Sizes[] = { 1.0, 5.0, 10.0, 15.0, 20.0};

const GLubyte indices[] = {0,1,2,3,4};

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLint iLocPointSize = -1;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "roundpoints.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "roundpoints.frag";

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
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
    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(iLocPointSize = glGetAttribLocation(programID, "a_PointSize"));
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.7f, 0.2f, 0.6f, 1.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Vertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if(iLocPointSize != -1) {
        GL_CHECK(glVertexAttribPointer(iLocPointSize, 1, GL_FLOAT, GL_FALSE, 0, Sizes));
        GL_CHECK(glEnableVertexAttribArray(iLocPointSize));
    }

    GL_CHECK(glUniform1i(0, GL_TRUE));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 5));
    GL_CHECK(glUniform1i(0, GL_FALSE));
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
