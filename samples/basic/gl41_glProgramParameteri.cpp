
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
 **
 ** glProgramUniform1f
 ** glProgramUniform2f
 ** glProgramUniform3f
 ** glProgramUniform4f
 **
 ** glProgramUniform1fv
 ** glProgramUniform2fv
 ** glProgramUniform3fv
 ** glProgramUniform4fv
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, vao[2], vbo[2], vs, fs, pipe;
GLuint vs_program, fs_program;

GLfloat rp1_pos[] = {0.0, 1.0,
                     -1.0, -1.0,
                     1.0, -1.0};

void fillData()
{
    GL_CHECK(glProgramUniform1f(fs_program, glGetUniformLocation(fs_program, "f1"), 0.1));
    GL_CHECK(glProgramUniform2f(fs_program, glGetUniformLocation(fs_program, "f2"), 0.1, 0.1));
    GL_CHECK(glProgramUniform3f(fs_program, glGetUniformLocation(fs_program, "f3"), 0.1, 0.1, 0.1));
    GL_CHECK(glProgramUniform4f(fs_program, glGetUniformLocation(fs_program, "f4"), 0.1, 0.1, 0.1, 0.1));

    const GLfloat fv1[1] = {0.1};
    const GLfloat fv2[2] = {0.1, 0.1};
    const GLfloat fv3[3] = {0.1, 0.1, 0.1};
    const GLfloat fv4[4] = {0.1, 0.1, 0.1, 0.1};

    GLuint iLocd1fv= GL_CHECK(glGetUniformLocation(fs_program, "fv1"));
    GL_CHECK(glProgramUniform1fv(fs_program, iLocd1fv, 1, fv1));
    GLuint iLocd2fv= GL_CHECK(glGetUniformLocation(fs_program, "fv2"));
    GL_CHECK(glProgramUniform2fv(fs_program, iLocd2fv, 1, fv2));
    GLuint iLocd3fv= GL_CHECK(glGetUniformLocation(fs_program, "fv3"));
    GL_CHECK(glProgramUniform3fv(fs_program, iLocd3fv, 1, fv3));
    GLuint iLocd4fv= GL_CHECK(glGetUniformLocation(fs_program, "fv4"));
    GL_CHECK(glProgramUniform4fv(fs_program, iLocd4fv, 1, fv4));

}

bool setupGraphics(int w, int h) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "glProgramUniformxf_fv.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "glProgramUniformxf_fv.frag";

    char* strings1 = Shader::loadShader(vertexShaderPath.c_str());
    char* strings2 = Shader::loadShader(fragmentShaderPath.c_str());

    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &strings1, NULL);
    glCompileShader(vs);
    vs_program = glCreateProgram();
    glAttachShader(vs_program, vs);
    glProgramParameteri(vs_program,/*GL_PROGRAM_BINARY_RETRIEVABLE_HINT,*/ GL_PROGRAM_SEPARABLE, GL_TRUE);
    glLinkProgram(vs_program);

    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &strings2, NULL);
    glCompileShader(fs);
    fs_program = glCreateProgram();
    glAttachShader(fs_program, fs);
    glProgramParameteri(fs_program, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glLinkProgram(fs_program);
 
    GL_CHECK(glGenProgramPipelines(1, &pipe));
    GL_CHECK(glBindProgramPipeline(pipe));

    GLuint k = GL_CHECK(glIsProgramPipeline(pipe));
    LOGI("PIPELINE IS %d\n", k);
    GL_CHECK(glUseProgramStages(pipe, GL_VERTEX_SHADER_BIT, vs_program));
    GL_CHECK(glUseProgramStages(pipe, GL_FRAGMENT_SHADER_BIT, fs_program));

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
