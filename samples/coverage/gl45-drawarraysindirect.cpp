
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, VAOs, Buffers, in_buffer;

GLfloat vertices[] = {-0.3, 0.3,
                      -0.3,-0.3,
                      0.3, 0.3};

GLfloat vertColor[] = {1.0, 0, 0, 1.0,
                       0, 1.0, 0, 1.0,
                       0, 0, 1.0, 1.0,
                       1.0, 1.0, 0, 1.0};



GLfloat vertPosOffsets[] = {-0.5, 0.5,
                            -0.5,-0.5,
                            0.5, 0.5,
                            0.5,-0.5,
                            0.5, 0.2};

typedef  struct {
    GLuint  count;
    GLuint  primCount;
    GLuint  first;
    GLuint  baseInstance;
} DrawArraysIndirectCommand;

DrawArraysIndirectCommand cmd1 = { 3, 2, 0, 2 };
DrawArraysIndirectCommand cmd2 = { 3, 2, 0, 2 };
bool setupGraphics() {
    string vertexShaderPath   = ((string)GLSL_PATH) + "drawarraysindirect.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "drawarraysindirect.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (!programID) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertColor) + sizeof(vertices)+ 1 * sizeof(vertPosOffsets),
                          NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertColor), vertColor));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(vertColor), sizeof(vertPosOffsets),
                             vertPosOffsets));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribDivisor(1, 1));

    GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,
                                   BUFFER_OFFSET(sizeof(vertices)+sizeof(vertColor))));
    GL_CHECK(glEnableVertexAttribArray(2));
    GL_CHECK(glVertexAttribDivisor(2, 1));



}

void render(){
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &in_buffer));
    GL_CHECK(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, in_buffer));
    GL_CHECK(glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(cmd1) + sizeof(cmd2), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_DRAW_INDIRECT_BUFFER, 0, sizeof(cmd1), &cmd1));
    GL_CHECK(glBufferSubData(GL_DRAW_INDIRECT_BUFFER, sizeof(cmd1), sizeof(cmd2), &cmd2));
    GL_CHECK(glViewport(0, 0, WINDOW_W, WINDOW_H));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 3));
  //  GL_CHECK(glDrawArraysIndirect(GL_TRIANGLE_STRIP, BUFFER_OFFSET(sizeof(cmd1))));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
    GL_CHECK(glDeleteBuffers(1, &in_buffer));
}

void Sample::test() {
    setupGraphics();
    render();
    string bmp_file1 = filename + ".bmp";
    save2bmp(bmp_file1.c_str());
    SwapBuffers();
    de_init();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}