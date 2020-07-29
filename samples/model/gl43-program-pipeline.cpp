
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, vao[2], vbo[2], vs, fs, pipe[2], vs1, fs1;

GLfloat rp1_pos[] = {0.0, 1.0,
                     -1.0, -1.0,
                     1.0, -1.0};

GLfloat rp2_pos[] = {
        0.0, 0.5,
        -0.5, -0.5,
        0.5, -0.5};

bool setupGraphics(int w, int h) {
    const char *strings[1] = { NULL };
    GL_CHECK(glGenProgramPipelines(2, &pipe[0]));
    GL_CHECK(glGenVertexArrays(2, &vao[0]));
    GL_CHECK(glGenBuffers(2, &vbo[0]));
    GL_CHECK(glBindVertexArray(vao[1]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[1]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(rp2_pos), rp2_pos, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glBindVertexArray(vao[0]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(rp1_pos), rp1_pos, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(GLfloat), BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));

    string vertexShaderPath0   = ((string)GLSL_PATH) + "pipe.vert";
    string fragmentShaderPath0 = ((string)GLSL_PATH) + "pipe0.frag";

    strings[0] = Shader::loadShader(vertexShaderPath0.c_str());
    vs = GL_CHECK(glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings));
    strings[0] = Shader::loadShader(fragmentShaderPath0.c_str());
    fs = GL_CHECK(glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings));

    GL_CHECK(glBindProgramPipeline(pipe[0]));
    GL_CHECK(glUseProgramStages(pipe[0], GL_VERTEX_SHADER_BIT, vs));
    GL_CHECK(glUseProgramStages(pipe[0], GL_FRAGMENT_SHADER_BIT, fs));
    GL_CHECK(glBindProgramPipeline(0));

    string vertexShaderPath1   = ((string)GLSL_PATH) + "pipe.vert";
    string fragmentShaderPath1 = ((string)GLSL_PATH) + "pipe1.frag";

    strings[0] = Shader::loadShader(vertexShaderPath1.c_str());
    vs1 = GL_CHECK(glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings));
    strings[0] = Shader::loadShader(fragmentShaderPath1.c_str());
    fs1 = GL_CHECK(glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings));

    GL_CHECK(glBindProgramPipeline(pipe[1]));
    GL_CHECK(glUseProgramStages(pipe[1], GL_VERTEX_SHADER_BIT, vs1));
    GL_CHECK(glUseProgramStages(pipe[1], GL_FRAGMENT_SHADER_BIT, fs1));
    GL_CHECK(glBindProgramPipeline(0));
    GL_CHECK(glViewport(0, 0, w, h));
}

void render(){
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glValidateProgramPipeline(pipe[1]));
    GL_CHECK(glBindProgramPipeline(pipe[1]));
    GL_CHECK(glBindVertexArray(vao[1]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(2, &vao[0]));
    GL_CHECK(glDeleteBuffers(2, &vbo[0]));
    GL_CHECK(glDeleteProgramPipelines(2, &pipe[0]));
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