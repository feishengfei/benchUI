/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file copybuffersubdata.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for copybuffersubdata related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLfloat triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
};

GLfloat triangleColors1[] = {
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0
};

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint buffers[2];
GLuint vao;


bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + "CopyBufferSubData.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "CopyBufferSubData.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
                                               fragmentShaderPath.c_str()));
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glUseProgram(programID));

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));
    LOGI("iLoc: pos=%d, color=%d\n", iLocPosition, iLocFillColor);

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(2, buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffers[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices),
                          triangleVertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffers[1]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleColors1),
                          triangleColors1, GL_STATIC_DRAW));
    LOGI("k=%d\n", sizeof(triangleColors1));
   // GL_CHECK(glClearBufferData(GL_ARRAY_BUFFER, GL_RGBA32F, GL_RGBA,
   //                            GL_FLOAT, triangleColors1));
    GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(iLocFillColor));

    GL_CHECK(glViewport(0, 0, width, height));
    static const GLint black[] = { 0, 0, 0, 0};
    GL_CHECK(glClearBufferiv(GL_COLOR, 0, black));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();

}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
