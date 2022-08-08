/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file depthrange.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for depthrange related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
const float triangleVertices1[] =
{
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};
const float triangleVertices2[] =
{
    -0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f
};

const float triangleColors1[] =
{
    0.0, 1.0, 0.0, 0.5,
    0.0, 1.0, 0.0, 0.5,
    0.0, 1.0, 0.0, 0.5
};
const float triangleColors2[] =
{
    0.0, 0.0, 1.0, 0.5,
    0.0, 0.0, 1.0, 0.5,
    0.0, 0.0, 1.0, 0.5
};

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

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
    GLint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glViewport(0, 0, width, height));

    glClearColor(0.7, 0.3, 0.3, 0.1);
    glClearDepthf(0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    GL_CHECK(glUseProgram(programID));

    glDepthRangef(0, 1);
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices1));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    if(iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors1));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    glDepthRangef(1, 0);

    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices2));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    if(iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors2));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
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
