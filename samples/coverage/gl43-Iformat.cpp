/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file bindvertexbuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for bindvertexbuffer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const GLint Vertices[] =
{
    -300, -300, 0,
     0, 300, 0,
     300, -300, 0
};


GLuint programID;
GLuint VertexArrayName;
GLuint vbo;

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + "Iformat.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "Iformat.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (programID == 0) {
            LOGE("Could not create program.");
            return false;
        }
    GL_CHECK(glUseProgram(programID));


    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices),
                          Vertices, GL_STATIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glGenVertexArrays(1, &VertexArrayName));
    GL_CHECK(glBindVertexArray(VertexArrayName));
    GL_CHECK(glVertexAttribBinding(0, 0));
    GL_CHECK(glVertexAttribIFormat(0, 3, GL_INT, 0));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glBindVertexBuffer(0, vbo, 0, 3*sizeof(int)));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VertexArrayName));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
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
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
