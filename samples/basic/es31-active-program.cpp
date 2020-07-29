/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file active-program.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for active-program related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

#define LOG_MAX 255

GLuint pipeline;
GLuint mVS, pVS;
GLuint mFS, pFS;
int colorId, posId;
GLuint mVS1, pVS1;
GLuint mFS1, pFS1;
int colorId1, posId1;

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

void setupProgram()
{
    const char *strings[1] = { NULL };

    string vertexShaderPath = (string)GLSL_PATH + "compute.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "compute.frag";
    string fragmentShaderPath1 = (string)GLSL_PATH  + "compute1.frag";

    strings[0] = Shader::loadShader(vertexShaderPath.c_str());
    pVS = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings);
    strings[0] = Shader::loadShader(fragmentShaderPath.c_str());
    pFS = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings);

    strings[0] = Shader::loadShader(fragmentShaderPath1.c_str());
    pFS1 = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings);

    glGenProgramPipelines(1, &pipeline);
    glBindProgramPipeline(pipeline);
    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, pVS);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, pFS);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, pFS1);
    posId = glGetAttribLocation(pVS, "a_vPosition");

    GLint colorLoc = glGetUniformLocation(pFS, "v_vFillColor");
    glProgramUniform4f(pFS, colorLoc, 1.0, 1.0, 0.0, 1.0);

    glActiveShaderProgram(pipeline, pVS);
    glActiveShaderProgram(pipeline, pFS);
}

bool setupGraphics(int width, int height)
{
    setupProgram();
    glViewport(0, 0, width, height);
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
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
