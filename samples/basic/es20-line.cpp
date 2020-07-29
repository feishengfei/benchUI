/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file line.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for line related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const float lineVertices[][6] =
{
    {-0.5f, -0.5f, 0.0f,   -0.5f, 0.5f, 0.0f},
    {-0.2f, -0.5f, 0.0f,   -0.2f, 0.5f, 0.0f},
     {0.2f, -0.5f, 0.0f,    0.2f, 0.5f, 0.0f},
     {0.5f, -0.5f, 0.0f,    0.5f, 0.5f, 0.0f}
};

const float lineColors[] =
{
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

const GLubyte indices[] = {0,1,2,3,4,5,6,7};

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "base-green.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "base-green.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));

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

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    glLineWidth(2.0);
    GLfloat lw[2];
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lw);
    LOGI("glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE):\n");
    LOGI("%f\t %f\n",lw[0],lw[1]);
    GLint parami;
    glGetIntegerv(GL_LINE_WIDTH, &parami);
    LOGI("get(GL_LINE_WIDTH): %d", parami);

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    for(int i=0; i<4; i++) {
        glLineWidth(5.0*i+1.0);
        GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, lineVertices[i]));
        GL_CHECK(glEnableVertexAttribArray(iLocPosition));
        GL_CHECK(glDrawArrays(GL_LINES, 0, 2));
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
