/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file uniformmatrix2x3fv.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-11-12, Add commit
 * @brief basic test for uniformmatrix* related API
 * @par TestPoints:
        glUniform1d
        glUniform2d
        glUniform3d
        glUniform4d
        glUniform1dv
        glUniform2dv
        glUniform3dv
        glUniform4dv
        glUniformMatrix2dv
        glUniformMatrix3dv
        glUniformMatrix4dv
        glUniformMatrix2x3dv
        glUniformMatrix2x4dv
        glUniformMatrix3x2dv
        glUniformMatrix3x4dv
        glUniformMatrix4x2dv
        glUniformMatrix4x3dv
    demo design: use 8 points drawinstance,
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "UniformMatrix.vert";
string fragmentShaderFilename = "fix_green.frag";

GLuint programID, VAOs, Buffers;
GLfloat vertices[2] = {-1.9, -1.9};

bool setupGraphics(int width, int height) 
{
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;
    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    return true;
}

void fillData()
{

    GLuint iLocd1= GL_CHECK(glGetUniformLocation(programID, "d1"));
    GL_CHECK(glUniform1d(iLocd1, 0.1));
    GLuint iLocd2= GL_CHECK(glGetUniformLocation(programID, "d2"));
    GL_CHECK(glUniform2d(iLocd2, 0.1, 0.1));
    GLuint iLocd3= GL_CHECK(glGetUniformLocation(programID, "d3"));
    GL_CHECK(glUniform3d(iLocd3, 0.1, 0.1, 0.1));
    GLuint iLocd4= GL_CHECK(glGetUniformLocation(programID, "d4"));
    GL_CHECK(glUniform4d(iLocd4, 0.1, 0.1, 0.1, 0.1));

    GLdouble getdv[4];
    GL_CHECK(glGetUniformdv(programID, iLocd1, getdv));
    printf("GetUniformdv(iLocdv1): %f\n", getdv[0]);
    GL_CHECK(glGetUniformdv(programID, iLocd4, getdv));
    printf("GetUniformdv(iLocdv4): %f,%f,%f,%f\n", getdv[0], getdv[1], getdv[2],getdv[3]);

    GLdouble d1v[1] = {0.1};
    GLdouble d2v[2] = {0.1, 0.1};
    GLdouble d3v[3] = {0.1, 0.1, 0.1};
    GLdouble d4v[4] = {0.1, 0.1, 0.1, 0.1};

    GLuint iLocd1v= GL_CHECK(glGetUniformLocation(programID, "d1v"));
    GL_CHECK(glUniform1dv(iLocd1v, 1, d1v));
    GLuint iLocd2v= GL_CHECK(glGetUniformLocation(programID, "d2v"));
    GL_CHECK(glUniform2dv(iLocd2v, 1, d2v));
    GLuint iLocd3v= GL_CHECK(glGetUniformLocation(programID, "d3v"));
    GL_CHECK(glUniform3dv(iLocd3v, 1, d3v));
    GLuint iLocd4v= GL_CHECK(glGetUniformLocation(programID, "d4v"));
    GL_CHECK(glUniform4dv(iLocd4v, 1, d4v));

    GLdouble dm2[4] = {0.1, 0.1, 0.1, 0.1};
    GLdouble dm3[9] = {0.1, 0.1, 0.1,  0.1, 0.1, 0.1,  0.1, 0.1, 0.1};
    GLdouble dm4[16] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};

    GLuint iLocdm2= GL_CHECK(glGetUniformLocation(programID, "dm2"));
    GL_CHECK(glUniformMatrix2dv(iLocdm2, 1, GL_FALSE, dm2));
    GLuint iLocdm3= GL_CHECK(glGetUniformLocation(programID, "dm3"));
    GL_CHECK(glUniformMatrix3dv(iLocdm3, 1, GL_FALSE, dm3));
    GLuint iLocdm4= GL_CHECK(glGetUniformLocation(programID, "dm4"));
    GL_CHECK(glUniformMatrix4dv(iLocdm4, 1, GL_FALSE, dm4));

    GLdouble dm23[6] = {0.1, 0.1, 0.1,  0.1, 0.1, 0.1};
    GLdouble dm24[8] = {0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1};
    GLdouble dm32[6] = {0.1, 0.1, 0.1,  0.1, 0.1, 0.1};
    GLdouble dm34[12] = {0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1};
    GLdouble dm42[8] = {0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1};
    GLdouble dm43[12] = {0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1};

    GLuint iLocdm23= GL_CHECK(glGetUniformLocation(programID, "dm23"));
    GL_CHECK(glUniformMatrix2x3dv(iLocdm23, 1, GL_FALSE, dm23));
    GLuint iLocdm24= GL_CHECK(glGetUniformLocation(programID, "dm24"));
    GL_CHECK(glUniformMatrix2x4dv(iLocdm24, 1, GL_FALSE, dm24));
    GLuint iLocdm32= GL_CHECK(glGetUniformLocation(programID, "dm32"));
    GL_CHECK(glUniformMatrix3x2dv(iLocdm32, 1, GL_FALSE, dm32));
    GLuint iLocdm34= GL_CHECK(glGetUniformLocation(programID, "dm34"));
    GL_CHECK(glUniformMatrix3x4dv(iLocdm34, 1, GL_FALSE, dm34));
    GLuint iLocdm42= GL_CHECK(glGetUniformLocation(programID, "dm42"));
    GL_CHECK(glUniformMatrix4x2dv(iLocdm42, 1, GL_FALSE, dm42));
    GLuint iLocdm43= GL_CHECK(glGetUniformLocation(programID, "dm43"));
    GL_CHECK(glUniformMatrix4x3dv(iLocdm43, 1, GL_FALSE, dm43));
}

void renderFrame(void) 
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    fillData();
    GL_CHECK(glPointSize(2.0));
    GL_CHECK(glDrawArraysInstanced(GL_POINTS, 0, 1, 8));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}
