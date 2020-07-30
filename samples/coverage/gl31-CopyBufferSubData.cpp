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
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;

const float vertices1[] = {
        -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.0f, 1.0f
};

const float vertices2[] = {
        0.0f,-0.5f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f
};

GLuint programID, VAOs, buffers, cpbuffer;

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + "gl31CopyBufferSubData.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "gl31CopyBufferSubData.frag";

    programID                 = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (!programID) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glGenBuffers(1, &buffers));
    GL_CHECK(glGenBuffers(1, &cpbuffer));

    GL_CHECK(glBindBuffer(GL_COPY_READ_BUFFER, cpbuffer));
    GL_CHECK(glBufferData(GL_COPY_READ_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW));

    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW));
    GL_CHECK(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, 0, 0, sizeof(vertices1)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s\n", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    char name[50];
    glGetFragDataLocation(programID, name);
    LOGI("glGetFragDataLocation:%s\n",name);

}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
