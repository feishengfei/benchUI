/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file getuniform.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for getuniform related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

#define LOG_MAX 255

GLuint mVS, pVS;
GLuint mFS, pFS;
GLuint pipeline;
int colorId, posId;
GLfloat values[4];
float vertices[] =
{
    -0.5,  0.5, -0.5,
    0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5
};

float colors[] =
{
    1.0, 0.0, 0.0,
    0.0, 0.0, 1.0,
    0.0, 1.0, 0.0,
};

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + "uniformtest.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "uniformtest.frag";

    pVS = glCreateProgram();
    Shader::processShader(&mVS, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    glAttachShader(pVS, mVS);
    glProgramParameteri(pVS, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glLinkProgram(pVS);

    pFS = glCreateProgram();
    Shader::processShader(&mFS, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    glAttachShader(pFS, mFS);
    glProgramParameteri(pFS, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glLinkProgram(pFS);

    glGenProgramPipelines(1, &pipeline);
    GLint colorLoc = glGetUniformLocation(pFS, "v_vFillColor");
    GLint tu1fLoc  = glGetUniformLocation(pFS, "v_vuf1f");
    GLint tu2fLoc  = glGetUniformLocation(pFS, "v_vuf2f");
    GLint tu3fLoc  = glGetUniformLocation(pFS, "v_vuf3f");

    glProgramUniform3f(pFS, tu3fLoc, 0.0, 1.0, 0.0);
    glProgramUniform2f(pFS, tu2fLoc, 0.0, 1.0);
    glProgramUniform1f(pFS, tu1fLoc, 1.0);

    GLint tu1iLoc = glGetUniformLocation(pFS, "v_iFillColor");
    GLint tu2iLoc = glGetUniformLocation(pFS, "v_iuf1f");
    GLint tu3iLoc = glGetUniformLocation(pFS, "v_iuf2f");
    GLint tu4iLoc = glGetUniformLocation(pFS, "v_iuf3f");
    glProgramUniform4i(pFS, tu1iLoc, 1, 1, 0, 1);
    glProgramUniform3i(pFS, tu2iLoc, 0, 1, 0);
    glProgramUniform2i(pFS, tu3iLoc, 0, 1);
    glProgramUniform1i(pFS, tu4iLoc, 1);

    GLint tu1uiLoc = glGetUniformLocation(pFS, "v_uiFillColor");
    GLint tu2uiLoc = glGetUniformLocation(pFS, "v_uiuf1f");
    GLint tu3uiLoc = glGetUniformLocation(pFS, "v_uiuf2f");
    GLint tu4uiLoc = glGetUniformLocation(pFS, "v_uiuf3f");
    glProgramUniform4ui(pFS, tu1uiLoc, 1, 1, 0, 1);
    glProgramUniform3ui(pFS, tu2uiLoc, 0, 1, 0);
    glProgramUniform2ui(pFS, tu3uiLoc, 0, 1);
    glProgramUniform1ui(pFS, tu4uiLoc, 1);

    float arry_f4[4] = {1.0, 1.0, 0.0, 1.0};
    float arry_f3[3] = {0.0, 1.0, 0.0};
    float arry_f2[2] = {1.0, 0.0};
    float arry_f     = 0.0;

    glProgramUniform4fv(pFS, colorLoc, 1, arry_f4);
    glGetnUniformfv(pFS, colorLoc, 4 * sizeof(float), values);
    LOGI("values!!!!!!! = %f\n%f/n%f/n%f/n", values[0], values[1], values[2], values[3]);

    glBindProgramPipeline(pipeline);
    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, pVS);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, pFS);
    posId = glGetAttribLocation(pVS, "a_vPosition");
    glViewport(0, 0, width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    return true;
}

void renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindProgramPipeline(pipeline);
    glEnableVertexAttribArray (posId);
    glVertexAttribPointer(posId, 3, GL_FLOAT, GL_FALSE, 0, vertices);

    glDrawArrays(GL_TRIANGLES, 0, 3);
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
