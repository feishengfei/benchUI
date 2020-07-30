/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texstorage2d.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texstorage2d related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;
GLuint programID;

GLint samplerUniform;
GLuint tex;
GLuint Buffers;
GLuint vao;
GLfloat vertices[] = {
        -1,-1,0,  1,-1,0,  -1,1,0,
        1,-1,0,  -1,1,0,  1,1,0
};

#define	iWidth 32
static GLfloat imagef[iWidth][4];

void makeImage(void) {
    int s;

    for (s = 0; s < iWidth; s++) {
            imagef[s][0] = (GLfloat)(0);
            imagef[s][1] = (GLfloat)(8);
            imagef[s][2] = (GLfloat)(17);
            imagef[s][3] = (GLfloat)(0);
        }
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + "texstorage1d.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "texstorage1d.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

    glUseProgram(programID);
    makeImage();

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, + sizeof(vertices),
                          NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));

    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glGenTextures(1, &tex));
    GL_CHECK(glBindTexture(GL_TEXTURE_1D, tex));

    GL_CHECK(glTexStorage1D(GL_TEXTURE_1D, 1,  GL_RG16F, iWidth));
    GL_CHECK(glTexSubImage1D(GL_TEXTURE_1D, 0, 0, iWidth,
                             GL_RGB, GL_FLOAT, imagef));
    GL_CHECK(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    samplerUniform = glGetUniformLocation(programID, "texSampler");

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor (0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_1D,tex));

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file  = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
