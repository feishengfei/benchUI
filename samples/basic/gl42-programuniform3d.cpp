
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, vao[2], vbo[2], vs, fs, pipe;

GLfloat rp1_pos[] = {0.0, 1.0,
                     -1.0, -1.0,
                     1.0, -1.0};

GLfloat rp2_pos[] = {
        0.0, 0.5,
        -0.5, -0.5,
        0.5, -0.5};

bool setupGraphics(int w, int h) {
    const char *strings[1] = { NULL };
    string vertexShaderPath   = ((string)GLSL_PATH) + "pipeline1.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "dpipeline2.frag";

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

    GL_CHECK(glBindVertexArray(vao[1]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[1]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(rp2_pos), rp2_pos, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glEnable(GL_STENCIL_TEST))
    GL_CHECK(glViewport(0, 0, w, h));
}

void render(){
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glClearStencil(0x0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(vao[0]));
    GL_CHECK(glStencilFunc(GL_ALWAYS, 0x1, 0xff));
    GL_CHECK(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
    GL_CHECK(glStencilMask(0xff));
    GL_CHECK(glProgramUniform3d(fs, 0, 1.0, 0.0, 0.0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    const GLdouble fv[3] = {1.0, 1.0, 0.0};
    GL_CHECK(glBindVertexArray(vao[1]));
    GL_CHECK(glStencilFunc(GL_NOTEQUAL, 0x1, 0xff));
    GL_CHECK(glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP));
    GL_CHECK(glStencilMask(0x0));
    GL_CHECK(glProgramUniform3dv(fs, 0, 1, fv));
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