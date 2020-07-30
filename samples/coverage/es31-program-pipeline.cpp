/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file program-pipeline.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for program-pipeline related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

#define LOG_MAX 255

GLuint pipeline[2];
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

    glGenProgramPipelines(2, pipeline);

    string vertexShaderPath = (string)GLSL_PATH + "compute.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "compute.frag";

    strings[0] = Shader::loadShader(vertexShaderPath.c_str());
    pVS = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings);
    LOGI("PVS=%d\n", pVS);
    strings[0] = Shader::loadShader(fragmentShaderPath.c_str());
    pFS = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings);
    LOGI("PFS=%d\n", pFS);
    glBindProgramPipeline(pipeline[0]);
    glUseProgramStages(pipeline[0], GL_VERTEX_SHADER_BIT, pVS);
    glUseProgramStages(pipeline[0], GL_FRAGMENT_SHADER_BIT, pFS);
    posId = glGetAttribLocation(pVS, "a_vPosition");

    GLint colorLoc = glGetUniformLocation(pFS, "v_vFillColor");
    glProgramUniform4f(pFS, colorLoc, 1.0, 1.0, 0.0, 1.0);
    glEnableVertexAttribArray (posId); 
    glVertexAttribPointer(posId, 3, GL_FLOAT, GL_FALSE, 0, vertices);

    glBindProgramPipeline(0);

    string vertexShaderPath1 = (string)GLSL_PATH + "compute1.frag";
    string fragmentShaderPath1 = (string)GLSL_PATH + "compute1.vert";

    strings[0] = Shader::loadShader(vertexShaderPath1.c_str());
    pVS1 = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings);
    strings[0] = Shader::loadShader(fragmentShaderPath1.c_str());
    pFS1 = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings);

    glBindProgramPipeline(pipeline[1]);
    glUseProgramStages(pipeline[1], GL_VERTEX_SHADER_BIT, pVS1);
    glUseProgramStages(pipeline[1], GL_FRAGMENT_SHADER_BIT, pFS1);
    posId1 = glGetAttribLocation(pVS1, "a_vPosition");
    glEnableVertexAttribArray (posId1); 
    glVertexAttribPointer(posId1, 3, GL_FLOAT, GL_FALSE, 0, vertices);

    glBindProgramPipeline(0);
}

void stateCheck() {
    LOGI("pipeline[1] is pipeline after delete:%d\n", glIsProgramPipeline(pipeline[1]));
    GLint valid;
    glGetProgramPipelineiv(pipeline[1], GL_VALIDATE_STATUS, &valid);
    LOGI("pipeline[1] is valid after delete:%d\n", valid);
    glGetProgramPipelineiv(pipeline[0], GL_ACTIVE_PROGRAM, &valid);
    LOGI("pipeline[0] active program:%d\n", valid);
    glGetProgramPipelineiv(pipeline[0], GL_VERTEX_SHADER, &valid);
    LOGI("pipeline[0] GL_VERTEX_SHADER:%d\n", valid);
    glGetProgramPipelineiv(pipeline[0], GL_FRAGMENT_SHADER, &valid);
    LOGI("pipeline[0] GL_FRAGMENT_SHADER:%d\n", valid);
    glGetProgramPipelineiv(pipeline[0], GL_COMPUTE_SHADER, &valid);
    LOGI("pipeline[0] GL_COMPUTE_SHADER:%d\n", valid);
    glGetProgramPipelineiv(pipeline[0], GL_INFO_LOG_LENGTH, &valid);
    LOGI("pipeline[0] GL_INFO_LOG_LENGTH:%d\n", valid);
}

bool setupGraphics(int width, int height) {
    setupProgram();
    stateCheck();
    glViewport(0, 0, width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glDeleteProgramPipelines(1, &pipeline[1]);
    stateCheck();
    return true;
}

void renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT);
    glValidateProgramPipeline(pipeline[0]);
    glBindProgramPipeline(pipeline[0]);
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
