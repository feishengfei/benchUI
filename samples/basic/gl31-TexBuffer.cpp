/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texbuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-11-24, Add commit
 * @brief basic test for texbufferrange related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;

GLuint programID;
GLuint UniformDisplacement;

float vertices[] =
              {
                      -1.0f,  1.0f, 0.0f,
                      -1.0f, -1.0f, 0.0f,
                      0.0f,  1.0f, 0.0f
              };
GLuint tex, bo, vao, vbo;
uint8_t g_rgba8[] = {0xff, 0xff, 0x00, 0x00};

bool setupGraphics(int width, int height)
{
    string vertexShaderPath = (string)GLSL_PATH + "texbufferrange.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "texbufferrange.frag";
    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glGenBuffers(1, &bo));  /*生成缓存对象*/
    GL_CHECK(glBindBuffer(GL_TEXTURE_BUFFER, bo));/*绑定缓存对象*/
    GL_CHECK(glBufferData(GL_TEXTURE_BUFFER, sizeof(g_rgba8),
                          g_rgba8, GL_STREAM_DRAW));/*初始化缓存对象*/

    GL_CHECK(glGenTextures(1, &tex)); /*生成缓存纹理对象*/
    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, tex));/*绑定缓存纹理对象*/
    GL_CHECK(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8, bo));/*与缓存对象*/

    glViewport(0, 0, width, height);
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
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
