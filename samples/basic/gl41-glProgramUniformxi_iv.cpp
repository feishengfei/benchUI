
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */
/**
 ** @file program-pipeline.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2019-12-11, Add commit
 ** @brief basic test for program-pipeline related API
 ** @par TestPoints:

 ** glProgramUniform1i
 ** glProgramUniform2i
 ** glProgramUniform3i
 ** glProgramUniform4i
 **
 ** glProgramUniform1iv
 ** glProgramUniform2iv
 ** glProgramUniform3iv
 ** glProgramUniform4iv
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, vao[2], vbo[2], vs, fs, pipe;

GLfloat rp1_pos[] = {0.0, 1.0,
                     -1.0, -1.0,
                     1.0, -1.0};

void fillData()
{
    GL_CHECK(glProgramUniform1i(fs, glGetUniformLocation(fs, "f1"), 1));
    GL_CHECK(glProgramUniform2i(fs, glGetUniformLocation(fs, "f2"), 1, 1));
    GL_CHECK(glProgramUniform3i(fs, glGetUniformLocation(fs, "f3"), 1, 1, 1));
    GL_CHECK(glProgramUniform4i(fs, glGetUniformLocation(fs, "f4"), 1, 1, 1, 1));

    const int fv1[1] = {1};
    const int fv2[2] = {1, 1};
    const int fv3[3] = {1, 1, 1};
    const int fv4[4] = {1, 1, 1, 1};

    GL_CHECK(glProgramUniform1iv(fs, glGetUniformLocation(fs, "fv1"), 1, fv1));
    GL_CHECK(glProgramUniform2iv(fs, glGetUniformLocation(fs, "fv2"), 1, fv2));
    GL_CHECK(glProgramUniform3iv(fs, glGetUniformLocation(fs, "fv3"), 1, fv3));
    GL_CHECK(glProgramUniform4iv(fs, glGetUniformLocation(fs, "fv4"), 1, fv4));
/*
    GLuint iLocd1fv= GL_CHECK(glGetUniformLocation(fs, "fv1"));
    GL_CHECK(glProgramUniform1iv(fs, iLocd1fv, 1, fv1));
    GLuint iLocd2fv= GL_CHECK(glGetUniformLocation(fs, "fv2"));
    GL_CHECK(glProgramUniform2iv(fs, iLocd2fv, 1, fv2));
    GLuint iLocd3fv= GL_CHECK(glGetUniformLocation(fs, "fv3"));
    GL_CHECK(glProgramUniform3iv(fs, iLocd3fv, 1, fv3));
    GLuint iLocd4fv= GL_CHECK(glGetUniformLocation(fs, "fv4"));
    GL_CHECK(glProgramUniform4iv(fs, iLocd4fv, 1, fv4));
*/
}

bool setupGraphics(int w, int h) {
    const char *strings[1] = { NULL };
    string vertexShaderPath   = ((string)GLSL_PATH) + "glProgramUniformxi_iv.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "glProgramUniformxi_iv.frag";

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

    GL_CHECK(glGenVertexArrays(2, &vao[0]));
    GL_CHECK(glGenBuffers(2, &vbo[0]));

    GL_CHECK(glBindVertexArray(vao[0]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(rp1_pos), rp1_pos, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));

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
    GL_CHECK(glClearStencil(0x0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(vao[0]));
    GL_CHECK(glStencilFunc(GL_ALWAYS, 0x1, 0xff));
    GL_CHECK(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
    GL_CHECK(glStencilMask(0xff));

    fillData();

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(2, &vao[0]));
    GL_CHECK(glDeleteBuffers(2, &vbo[0]));
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
