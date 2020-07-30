/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file drawarrayinstance.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for drawarrayinstance related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

const float triangleVertices[] = {
        -0.45f, 0.3f, 0.0f, 1.0f,
        -0.5f, -0.3f, 0.0f, 1.0f,
        -0.4f, -0.3f, 0.0f, 1.0f
};

const float offsets[] = {
        0.0, 0.0, 0.0, 0.0,
        0.4, 0.0, 0.0, 0.0,
        0.8, 0.0, 0.0, 0.0
};

const GLubyte indices[] = {0,1,2};
string vertexShaderFilename = "DrawArrayInstance.vert";
string fragmentShaderFilename = "DrawArrayInstance.frag";

GLuint programID;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, offsets));
    GL_CHECK(glEnableVertexAttribArray(1));

    glVertexAttribDivisor(1, 1);
    GL_CHECK(glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 3));
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
