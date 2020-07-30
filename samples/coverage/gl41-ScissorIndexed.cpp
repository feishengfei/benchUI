/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file depthrange.cpp
 * @author cary.Zhang
 * @par History:
 *    A001: cary.Zhang, 2019-12-24
 * @par TestPoints:
 *
 * glViewportArrayv
 * glViewportIndexedf
 * glViewportIndexedfv
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID, VAOs, Buffers;

const float vertices[] =
{
    -0.5f,  0.6f, -0.2f,
    -0.5f, -0.4f, -0.2f,
     0.5f, -0.4f, -0.2f
};

bool setupGraphics(){
    string vertexShaderPath = "ScissorArrayv.vert";
    string geometryShaderPath = "ViewportArrayv.gemo";
    string fragmentShaderPath = "ViewportArrayv.frag";

    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER,   vertexShaderPath.c_str() },
        { GL_GEOMETRY_SHADER, geometryShaderPath.c_str() },
        { GL_FRAGMENT_SHADER, fragmentShaderPath.c_str() },
        { GL_NONE, NULL }
    };
    programID = Shader::LoadShaders( shaders );

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
}

void renderFrame() {
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnable(GL_SCISSOR_TEST));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glViewportIndexedf( 0, 0,          0,          WINDOW_W/2, WINDOW_H/2));
    GL_CHECK(glViewportIndexedf( 1, 0,          WINDOW_H/2, WINDOW_W/2, WINDOW_H/2));
    GL_CHECK(glViewportIndexedf( 2, WINDOW_W/2, 0,          WINDOW_W/2, WINDOW_H/2));
    GL_CHECK(glViewportIndexedf( 3, WINDOW_W/2, WINDOW_H/2, WINDOW_W/2, WINDOW_H/2));

    GL_CHECK(glScissorIndexed( 0, 0,          0,          WINDOW_W/4, WINDOW_H/4));
    GL_CHECK(glScissorIndexed( 1, 0,          WINDOW_H/2, WINDOW_W/4, WINDOW_H/4));
    GL_CHECK(glScissorIndexed( 2, WINDOW_W/2, 0,          WINDOW_W/4, WINDOW_H/4));
    GL_CHECK(glScissorIndexed( 3, WINDOW_W/2, WINDOW_H/2, WINDOW_W/4, WINDOW_H/4));

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    string bmp_file = filename + ".bmp";
    setupGraphics();
    renderFrame();
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__,  GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();

    return 0;
}
