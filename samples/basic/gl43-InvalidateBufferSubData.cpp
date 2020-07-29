
/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file triangle-buffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for triangle-buffer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"


using std::string;
using namespace BotsonSDK;

static float triangleVertices[] = {
        -0.5f, 0.2f, 0.0f,
        -0.5f, 0.8f, 0.0f,
        0.9f,  0.6f, 0.0f,

        0.6f,0.2f, 0.0f,
        0.7f, 0.4f, 0.0f,
        0.9f, 0.2f, 0.0f
};

static float triangleVertices1[] = {
        -0.2f, -0.8f, 0.0f,
        -0.2f, -0.3f, 0.0f,
        0.5f, -0.5f, 0.0f
};


GLuint programID, vao;
GLint iLocPosition = -1;
GLuint buffers[2];

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "base-green.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "base-green.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    programID  = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
            fragmentShaderPath.c_str()));
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    glGenBuffers(2, buffers);

    return true;
}

void renderFrame(void) {
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffers[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices,
                 GL_STATIC_DRAW));

    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices)/2, triangleVertices1));
    GL_CHECK(glInvalidateBufferSubData(buffers[0], 0, sizeof(triangleVertices)/2));
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(iLocPosition);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDeleteBuffers(2, buffers);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename+".bmp";

    save2bmp(bmp_file.c_str());
    SwapBuffers();
}



int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
