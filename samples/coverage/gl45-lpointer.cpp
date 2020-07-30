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
#define BUFFER_OFFSET(x)  ((const void*) (x))

using std::string;
using namespace BotsonSDK;

GLuint programID;
GLuint vao;
GLuint vbo;

GLfloat triangleVertices[] =
                    {
                            -0.8, -0.8, 0.0, 1.0,
                            0.0, 0.8, 0.0, 1.0,
                            0.8, -0.8, 0.0, 1.0
                    };



GLdouble triangleColors[] =
                    {
                            1.0, 0.0,
                            0.0, 1.0,
                            1.0, 1.0
                    };

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "lpointer.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "lpointer.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glGenBuffers(1, &vbo));

    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices) + sizeof(triangleColors),
                          NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices), triangleVertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices), sizeof(triangleColors),
                             triangleColors));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribLPointer(1, 4, GL_DOUBLE,  0,
                                   BUFFER_OFFSET(sizeof(triangleVertices))));
    GL_CHECK(glEnableVertexAttribArray(1));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    return true;
}

void renderFrame(void) {

    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
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
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
