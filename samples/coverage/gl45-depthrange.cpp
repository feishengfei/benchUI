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
GLuint vao[4];
GLuint vbo[4];

const float triangleVertices1[] =
               {
                       -0.8f, -0.8f, 0.0f, 1.0f,
                       -0.5f, -0.2f, 0.0f, 1.0f,
                       -0.2f, -0.8f, 0.0f, 1.0f
               };
const float triangleVertices2[] =
               {
                       0.8f, -0.8f, 0.0f, 1.0f,
                       0.5f, -0.2f, 0.0f, 1.0f,
                       0.2f, -0.8f, 0.0f, 1.0f
               };

const float triangleVertices3[] =
                    {
                            0.8f, 0.8f, 0.0f, 1.0f,
                            0.5f, 0.2f, 0.0f, 1.0f,
                            0.2f, 0.8f, 0.0f, 1.0f
                    };

const float triangleVertices4[] =
                    {
                            -0.8f, 0.8f, 0.0f, 1.0f,
                            -0.5f, 0.2f, 0.0f, 1.0f,
                            -0.2f, 0.8f, 0.0f, 1.0f
                    };

const float triangleColors1[] =
                    {
                            1.0, 0.0, 0.0, 1.0,
                            1.0, 0.0, 0.0, 1.0,
                            1.0, 0.0, 0.0, 1.0
                    };

const float triangleColors2[] =
                    {
                            0.0, 1.0, 0.0, 1.0,
                            0.0, 1.0, 0.0, 1.0,
                            0.0, 1.0, 0.0, 1.0
                    };

const float triangleColors3[] =
                    {
                            0.0, 0.0, 1.0, 1.0,
                            0.0, 0.0, 1.0, 1.0,
                            0.0, 0.0, 1.0, 1.0
                    };

const float triangleColors4[] =
                    {
                            1.0, 0.0, 0.0, 1.0,
                            0.0, 1.0, 0.0, 1.0,
                            0.0, 0.0, 1.0, 1.0
                    };

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "depthrange.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "depthrange.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

    GL_CHECK(glGenVertexArrays(4, &vao[0]));
    GL_CHECK(glGenBuffers(4, &vbo[0]));

    GL_CHECK(glBindVertexArray(vao[0]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices1) + sizeof(triangleColors1),
                          NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices1), triangleVertices1));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices1), sizeof(triangleColors1),
                             triangleColors1));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
                                   BUFFER_OFFSET(sizeof(triangleVertices1))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glBindVertexArray(vao[1]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[1]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices2) + sizeof(triangleColors2),
                          NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices2), triangleVertices2));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices2), sizeof(triangleColors2),
                             triangleColors2));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
                                   BUFFER_OFFSET(sizeof(triangleVertices2))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glBindVertexArray(vao[2]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[2]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices3) + sizeof(triangleColors3),
                          NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices3), triangleVertices3));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices3), sizeof(triangleColors3),
                             triangleColors3));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
                                   BUFFER_OFFSET(sizeof(triangleVertices3))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glBindVertexArray(vao[3]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[3]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices4) + sizeof(triangleColors4),
                          NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices4), triangleVertices4));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices4), sizeof(triangleColors4),
                             triangleColors4));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
                                   BUFFER_OFFSET(sizeof(triangleVertices4))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    return true;
}

void renderFrame(void) {
    GL_CHECK(glClearDepthf(0.5));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glDepthRangeIndexed(0, 1.0, 0.0));
    GL_CHECK(glBindVertexArray(vao[0]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

   GL_CHECK(glDepthRangeIndexed(1, 0.0, 1.0));
   GL_CHECK(glBindVertexArray(vao[1]));
   GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[1]));
   GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

   const GLdouble depth[2] = {0.0, 1.0};
   GL_CHECK(glDepthRangeArrayv(0, 1, &depth[0]));
   GL_CHECK(glBindVertexArray(vao[2]));
   GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[2]));
   GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

   const GLdouble depth1[2] = {0.6, 1.0};
   GL_CHECK(glDepthRangeArrayv(1, 1, &depth1[0]));
   GL_CHECK(glBindVertexArray(vao[3]));
   GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[3]));
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
