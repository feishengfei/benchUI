/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file blendbarrier.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for blendbarrier related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const float triangleVertices1[] =
{
    -0.8f, -0.5f, 0.0f,
    -0.6f,  0.5f, 0.0f,
    -0.4f, -0.5f, 0.0f
};

const float triangleVertices2[] =
{
    -0.2f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.2f, -0.5f, 0.0f
};

const float triangleVertices3[] =
{
    0.8f, -0.5f, 0.0f,
    0.6f,  0.5f, 0.0f,
    0.4f, -0.5f, 0.0f
};

const float triangleColors1[] =
{
    1.0, 0.0, 0.0, 0.2,
    1.0, 0.0, 0.0, 0.2,
    1.0, 0.0, 0.0, 0.2
};

const float triangleColors2[] =
{
    0.0, 1.0, 0.0, 0.2,
    0.0, 1.0, 0.0, 0.2,
    0.0, 1.0, 0.0, 0.2
};

const float triangleColors3[] =
{
    0.0, 0.0, 1.0, 0.2,
    0.0, 0.0, 1.0, 0.2,
    0.0, 0.0, 1.0, 0.2
};

GLuint programID;

bool setupGraphics(int width, int height)
{
    string vertexShaderPath = (string)GLSL_PATH + "blend.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "blend.frag";

    GLuint vertexShaderID = 0;
    GLuint fragmentShaderID = 0;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glEnableVertexAttribArray(1));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 0.8f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    glEnablei(GL_BLEND, 0);
    glBlendEquationi(0, GL_FUNC_ADD);
    glBlendFunci(0, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    LOGI("IsEnablei(GL_BLEND, 0): %d\n", glIsEnabledi(GL_BLEND, 0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, triangleColors1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    glDisablei(GL_BLEND, 0);
    glBlendEquationSeparatei(0, GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparatei(0, GL_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                         GL_ONE_MINUS_SRC_ALPHA);
    LOGI("IsEnablei(GL_BLEND, 0): %d\n", glIsEnabledi(GL_BLEND, 0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices2));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, triangleColors2));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    glEnablei(GL_BLEND, 1);
    glBlendEquationi(0, GL_FUNC_ADD);
    glBlendFunci(0, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices3));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, triangleColors3));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    glBlendBarrier();
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
