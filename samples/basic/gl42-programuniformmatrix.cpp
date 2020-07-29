
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, vao, vbo, vs, fs, pipe;

GLfloat rp1_pos[] = {0.0, 0.5,
                     -0.5, -0.5,
                     0.5, -0.5};

GLfloat pos[] = {
        0.3, 0.3,
        -0.3, -0.3};
GLfloat pos1[] = {
        0.3, 0.3, 0.0,
        -0.3, 0.0, 0.0,
        0.3, 0.3, -0.2};
GLfloat pos2[] = {
        0.3, 0.3, 0.0, 0.0,
        -0.3, -0.9, 0.0, 1.0,
        0.3, 0.3, -0.3,  1.0,
        0.3, -0.3, 0.0, 1.0};
GLfloat pos3[] = {
        0.3, 0.3, 0.0,
        -0.3, 0.0, -0.2};
GLfloat pos4[] = {
        -0.3, 0.3, 0.0,
        -0.3, 0.0, 0.2};
GLfloat pos5[] = {
        0.3, 0.3, 0.0, 0.0,
        -0.3, -0.9, 0.0, -0.4};
GLfloat pos6[] = {
        0.3, 0.3, 0.0, 0.0,
        -0.3, -0.9, 0.0, -0.3};
GLfloat pos7[] = {
        0.3, 0.3, 0.0, 0.0,
        -0.3, -0.9, 0.0, 1.0,
        0.3, 0.3, -0.3, -0.4};
GLfloat pos8[] = {
        0.7, 0.3, 0.0, 0.0,
        -0.3, -0.9, 0.0, 1.0,
        0.3, 0.3, -0.3, -0.7};
bool setupGraphics(int w, int h) {
    const char *strings[1] = { NULL };
    string vertexShaderPath   = ((string)GLSL_PATH) + "matrixf.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "matrix2f.frag";

    strings[0] = Shader::loadShader(vertexShaderPath.c_str());
    vs = GL_CHECK(glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings));
    strings[0] = Shader::loadShader(fragmentShaderPath.c_str());
    fs = GL_CHECK(glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings));
    LOGI("VS=%d, FS=%d\n", vs, fs);
    GL_CHECK(glGenProgramPipelines(1, &pipe));
    GL_CHECK(glBindProgramPipeline(pipe));

    GLuint k = GL_CHECK(glIsProgramPipeline(pipe));
    LOGI("PIPELINE IS %d\n", k);
    GL_CHECK(glActiveShaderProgram(pipe, vs));
    GL_CHECK(glActiveShaderProgram(pipe, fs));
    GL_CHECK(glUseProgramStages(pipe, GL_FRAGMENT_SHADER_BIT, fs));
    GL_CHECK(glUseProgramStages(pipe, GL_VERTEX_SHADER_BIT, vs));

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(rp1_pos), rp1_pos, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glViewport(0, 0, w, h));
}

void render(){
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(vao));

    GL_CHECK(glProgramUniformMatrix2fv(vs, 0, 1, GL_FALSE, pos));
    GL_CHECK(glProgramUniformMatrix3fv(vs, 1, 1, GL_FALSE, pos1));
    GL_CHECK(glProgramUniformMatrix4fv(vs, 4, 1, GL_FALSE, pos2));
    GL_CHECK(glProgramUniformMatrix2x3fv(vs, 8, 1, GL_FALSE, pos3));
    GL_CHECK(glProgramUniformMatrix3x2fv(vs, 10, 1, GL_FALSE, pos4));
    GL_CHECK(glProgramUniformMatrix2x4fv(vs, 12, 1, GL_FALSE, pos5));
    GL_CHECK(glProgramUniformMatrix4x2fv(vs, 14, 1, GL_FALSE, pos6));
    GL_CHECK(glProgramUniformMatrix3x4fv(vs, 16, 1, GL_FALSE, pos7));
    GL_CHECK(glProgramUniformMatrix4x3fv(vs, 19, 1, GL_FALSE, pos8));

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &vao));
    GL_CHECK(glDeleteBuffers(1, &vbo));
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