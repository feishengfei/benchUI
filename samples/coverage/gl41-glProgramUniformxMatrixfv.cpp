/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 ** @file program-pipeline.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2019-12-11, Add commit
 ** @brief basic test for program-pipeline related API
 ** @par TestPoints:
 **
    glProgramUniformMatrix2fv
    glProgramUniformMatrix3fv
    glProgramUniformMatrix4fv
    glProgramUniformMatrix2x3fv
    glProgramUniformMatrix2x4fv
    glProgramUniformMatrix3x2fv
    glProgramUniformMatrix3x4fv
    glProgramUniformMatrix4x2fv
    glProgramUniformMatrix4x3fv
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, vao[2], vbo[2], vs, fs, pipe;
GLint iLocPosition = -1;

void fillData()
{
    GLuint iLocd1= GL_CHECK(glGetUniformLocation(vs, "f1"));
    GL_CHECK(glProgramUniform1f(vs, iLocd1, 0.1));
    GLuint iLocd2= GL_CHECK(glGetUniformLocation(vs, "f2"));
    GL_CHECK(glProgramUniform2f(vs, iLocd2, 0.1, 0.1));
    GLuint iLocd3= GL_CHECK(glGetUniformLocation(vs, "f3"));
    GL_CHECK(glProgramUniform3f(vs, iLocd3, 0.1, 0.1, 0.1));
    GLuint iLocd4= GL_CHECK(glGetUniformLocation(vs, "f4"));
    GL_CHECK(glProgramUniform4f(vs, iLocd4, 0.1, 0.1, 0.1, 0.1));

    GLfloat d1v[1] = {0.1};
    GLfloat d2v[2] = {0.1, 0.1};
    GLfloat d3v[3] = {0.1, 0.1, 0.1};
    GLfloat d4v[4] = {0.1, 0.1, 0.1, 0.1};

    GLuint iLocd1v= GL_CHECK(glGetUniformLocation(vs, "f1v"));
    GL_CHECK(glProgramUniform1fv(vs, iLocd1v, 1, d1v));
    GLuint iLocd2v= GL_CHECK(glGetUniformLocation(vs, "f2v"));
    GL_CHECK(glProgramUniform2fv(vs, iLocd2v, 1, d2v));
    GLuint iLocd3v= GL_CHECK(glGetUniformLocation(vs, "f3v"));
    GL_CHECK(glProgramUniform3fv(vs, iLocd3v, 1, d3v));
    GLuint iLocd4v= GL_CHECK(glGetUniformLocation(vs, "f4v"));
    GL_CHECK(glProgramUniform4fv(vs, iLocd4v, 1, d4v));

    GLfloat fm2[4] = {0.1, 0.1, 0.1, 0.1};
    GLfloat fm3[9] = {0.1, 0.1, 0.1,  0.1, 0.1, 0.1,  0.1, 0.1, 0.1};
    GLfloat fm4[16] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};

    GLuint iLocdm2= GL_CHECK(glGetUniformLocation(vs, "dm2"));
    GL_CHECK(glProgramUniformMatrix2fv(vs, iLocdm2, 1, GL_FALSE, fm2));
    GLuint iLocdm3= GL_CHECK(glGetUniformLocation(vs, "dm3"));
    GL_CHECK(glProgramUniformMatrix3fv(vs, iLocdm3, 1, GL_FALSE, fm3));
    GLuint iLocdm4= GL_CHECK(glGetUniformLocation(vs, "dm4"));
    GL_CHECK(glProgramUniformMatrix4fv(vs, iLocdm4, 1, GL_FALSE, fm4));

    GLfloat fm23[6] = {0.1, 0.1, 0.1,  0.1, 0.1, 0.1};
    GLfloat fm24[8] = {0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1};
    GLfloat fm32[6] = {0.1, 0.1, 0.1,  0.1, 0.1, 0.1};
    GLfloat fm34[12] = {0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1};
    GLfloat fm42[8] = {0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1};
    GLfloat fm43[12] = {0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1,  0.1, 0.1, 0.1, 0.1};

    GLuint iLocdm23= GL_CHECK(glGetUniformLocation(vs, "dm23"));
    GL_CHECK(glProgramUniformMatrix2x3fv(vs, iLocdm23, 1, GL_FALSE, fm23));
    GLuint iLocdm24= GL_CHECK(glGetUniformLocation(vs, "dm24"));
    GL_CHECK(glProgramUniformMatrix2x4fv(vs, iLocdm24, 1, GL_FALSE, fm24));
    GLuint iLocdm32= GL_CHECK(glGetUniformLocation(vs, "dm32"));
    GL_CHECK(glProgramUniformMatrix3x2fv(vs, iLocdm32, 1, GL_FALSE, fm32));
    GLuint iLocdm34= GL_CHECK(glGetUniformLocation(vs, "dm34"));
    GL_CHECK(glProgramUniformMatrix3x4fv(vs, iLocdm34, 1, GL_FALSE, fm34));
    GLuint iLocdm42= GL_CHECK(glGetUniformLocation(vs, "dm42"));
    GL_CHECK(glProgramUniformMatrix4x2fv(vs, iLocdm42, 1, GL_FALSE, fm42));
    GLuint iLocdm43= GL_CHECK(glGetUniformLocation(vs, "dm43"));
    GL_CHECK(glProgramUniformMatrix4x3fv(vs, iLocdm43, 1, GL_FALSE, fm43));
}

bool setupGraphics(int w, int h) {
    const char *strings[1] = { NULL };
    string vertexShaderPath   = ((string)GLSL_PATH) + "glProgramUniformxMatrixfv.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "glProgramUniformxMatrixfv.frag";

    strings[0] = Shader::loadShader(vertexShaderPath.c_str());
    vs = GL_CHECK(glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings));
    strings[0] = Shader::loadShader(fragmentShaderPath.c_str());
    fs = GL_CHECK(glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings));

    GL_CHECK(glGenProgramPipelines(1, &pipe));
    GL_CHECK(glBindProgramPipeline(pipe));

    GLuint k = GL_CHECK(glIsProgramPipeline(pipe));
    LOGI("PIPELINE IS %d\n", k);
    GL_CHECK(glUseProgramStages(pipe, GL_VERTEX_SHADER_BIT, vs));
    GL_CHECK(glUseProgramStages(pipe, GL_FRAGMENT_SHADER_BIT, fs));

    GLfloat vertices[2] = {-1.9, -1.9};
    GL_CHECK(iLocPosition = glGetAttribLocation(vs, "a_v2Position"));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, vertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    GLint p;
    GL_CHECK(glGetProgramPipelineiv(pipe, GL_ACTIVE_PROGRAM, &p));
    LOGI("GL_ACTIVE_PROGRAM = %d\n", p);
    GL_CHECK(glGetProgramPipelineiv(pipe, GL_VERTEX_SHADER, &p));
    LOGI("GL_VERTEX_SHADER = %d\n", p);
    GL_CHECK(glGetProgramPipelineiv(pipe, GL_GEOMETRY_SHADER, &p));
    LOGI("GL_GEOMETRY_SHADER = %d\n", p);
    GL_CHECK(glGetProgramPipelineiv(pipe, GL_FRAGMENT_SHADER, &p));
    LOGI("GL_FRAGMENT_SHADER = %d\n", p);

    GLint length;
    GL_CHECK(glGetProgramPipelineiv(pipe, GL_INFO_LOG_LENGTH, &length));
    LOGI("GL_INFO_LOG_LENGTH = %d\n", length);

    char* buf = (char*)malloc(length);
    GL_CHECK(glGetProgramPipelineInfoLog(pipe, length, NULL, buf));
    LOGI("GL_ACTIVE_PROGRAM = %c\n", buf);
}

void render(){
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgramStages(pipe, GL_VERTEX_SHADER_BIT, vs));
    GL_CHECK(glUseProgramStages(pipe, GL_FRAGMENT_SHADER_BIT, fs));
    fillData();
    GL_CHECK(glPointSize(2.0));
    GL_CHECK(glDrawArraysInstanced(GL_POINTS, 0, 1, 8));
}

void de_init(){
    GL_CHECK(glDeleteProgramPipelines(1, &pipe));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    render();
    string bmp_file1 = filename + ".bmp";
    save2bmp(bmp_file1.c_str());
    SwapBuffers();
    de_init();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}
