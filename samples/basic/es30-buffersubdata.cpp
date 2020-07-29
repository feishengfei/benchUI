/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file buffersubdata.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for buffersubdata related API
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
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

const float triangleVertices1[] = {
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
     0.0f,-0.5f, 0.0f,
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0
};

const int triangleColorsI[] = {
    1, 0, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1
};

const GLubyte indices[] = {1,2,4,0,3,2};
const GLubyte subdata[] = {1,4,5};

static const GLint vertices [] = {
        0, -2,
        -52, 32,
        0, 2,
        2, 0,
        15, 153,
        -2, 0
};
static const GLfloat color[] = {
        0.0, 1.0, 0.0,
        10.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 110.0, 0.0,
        0.0, 0.0, 1.0
};

const float triangleVertices2[] = {
     0.0f,-0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
};

const float triangleColors2[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
};

string vertexShaderFilename = "BufferSubData.vert";
string fragmentShaderFilename = "BufferSubData.frag";

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint buffers[3];
GLuint vao;

void print_get(GLenum pname) {
	GLint tmp;
	glGetIntegerv(pname, &tmp);
	LOGI("%d\n",tmp);
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    programID                 = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(3, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(iLocPosition);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices1), triangleVertices1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(subdata), subdata);

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    glBindVertexArray(vao);
    GL_CHECK(glDrawRangeElements(GL_TRIANGLES, 0, 5, 6, GL_UNSIGNED_BYTE, 0));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    GLint params;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &params);
    printf("GL_ARRAY_BUFFER, GL_BUFFER_SIZE: %d\n", params);
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &params);
    printf("GL_ARRAY_BUFFER, GL_BUFFER_USAGE: %x(GL_STATIC_DRAW=%x)\n", params,
           GL_STATIC_DRAW);
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &params);
    printf("GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE: %d\n", params);
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE, &params);
    printf("GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_USAGE: %x\n", params);
    glDeleteBuffers(3, buffers);
    glDeleteVertexArrays(1, &vao);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
