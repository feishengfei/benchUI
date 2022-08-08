/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file blendequ.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for blendequ related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 0.3,
    0.0, 1.0, 0.0, 0.3,
    0.0, 0.0, 1.0, 0.3,
};


GLuint programID;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "test.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "test.frag";
    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.3f, 0.3f, 0.3f, 0.7f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, triangleColors));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
        setupGraphics(WINDOW_W, WINDOW_H);
        renderFrame();
        string bmp_file=filename+".bmp";
        LOGI("bmp_file=%s",bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
