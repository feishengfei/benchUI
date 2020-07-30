/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file vertexbinddivisor.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for vertexbinddivisor related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

static const GLfloat square_vertices[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f,
        1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f
};

static const GLfloat instance_colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f
};

static const GLfloat instance_positions[] = {
        -2.0f, -2.0f, 0.0f, 0.0f,
        2.0f, -2.0f, 0.0f, 0.0f,
        2.0f,  2.0f, 0.0f, 0.0f,
        -2.0f,  2.0f, 0.0f, 0.0f
};


GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint VertexArrayName;
GLuint vbo;
GLuint square_buffer;
GLuint square_vao;

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + "instance_position.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "instance_position.frag";

    GLuint vertexShaderID   = 0;
    GLuint fragmentShaderID = 0;

    GL_CHECK(glEnable(GL_DEPTH_TEST));

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);

    programID                 = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    GLuint offset = 0;

    GL_CHECK(glGenVertexArrays(1, &square_vao));
    GL_CHECK(glGenBuffers(1, &square_buffer));
    GL_CHECK(glBindVertexArray(square_vao));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, square_buffer));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices) + sizeof(instance_colors) + sizeof(instance_positions), NULL,
            GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(square_vertices), square_vertices));
    GL_CHECK(offset += sizeof(square_vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(instance_colors), instance_colors));
    GL_CHECK(offset += sizeof(instance_colors));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(instance_positions), instance_positions));
    GL_CHECK(offset += sizeof(instance_positions));

    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
                                   (GLvoid *)sizeof(square_vertices)));
    GL_CHECK(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0,
             (GLvoid *)(sizeof(square_vertices) + sizeof(instance_colors))));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glEnableVertexAttribArray(2));

    GL_CHECK(glVertexAttribBinding(1, 1));
    GL_CHECK(glVertexBindingDivisor(1, 1));
    GL_CHECK(glVertexAttribBinding(2, 2));
    GL_CHECK(glVertexBindingDivisor(2, 1));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
        GL_CHECK(glClearBufferfv(GL_COLOR, 0, black));
        GL_CHECK(glUseProgram(programID));
        GL_CHECK(glBindVertexArray(square_vao));
        GL_CHECK(glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, 4));
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
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

