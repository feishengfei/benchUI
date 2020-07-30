
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, VAOs, abo, ebo, in_buffer;

GLfloat vertices[] = {-0.3, 0.3,
                      -0.3,-0.3,
                       0.3, 0.3,
                       0.3,-0.3,
                       0.1, 0.1};

GLfloat vertColor[] = {1.0, 0, 0, 1.0,
                       0, 1.0, 0, 1.0,
                       0, 0, 1.0, 1.0,
                       1.0, 1.0, 0, 1.0,
                       1.0, 0, 1.0, 1.0};

GLfloat vertPosOffsets[] = {-0.5, 0.5,
                            -0.5,-0.5,
                            0.5, 0.5,
                            0.5,-0.5,
                            0.0, 0.0};

GLuint indices[]={0, 1, 2, 0, 2, 3, 4};

typedef  struct {
    GLuint  count;
    GLuint  primCount;
    GLuint  firstIndex;
    GLuint  baseVertex;
    GLuint  baseInstance;
} DrawElementsIndirectCommand;

DrawElementsIndirectCommand cmd1 = { 3, 2, 0, 1, 2 };
DrawElementsIndirectCommand cmd2 = { 2, 1, 5, 0, 0 };

bool setupGraphics(int w, int h) {
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

    GL_CHECK(glGenBuffers(1, &abo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, abo));


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

    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CHECK(glGenBuffers(1, &in_buffer));
    GL_CHECK(glBindBuffer(GL_DRAW_INDIRECT_BUFFER, in_buffer));
    GL_CHECK(glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(cmd1) + sizeof(cmd2), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_DRAW_INDIRECT_BUFFER, 0, sizeof(cmd1), &cmd1));
    GL_CHECK(glBufferSubData(GL_DRAW_INDIRECT_BUFFER, sizeof(cmd1), sizeof(cmd2), &cmd2));

    GL_CHECK(glViewport(0, 0, w, h));

    return true;
}

void render(){
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawElementsIndirect(GL_LINES, GL_UNSIGNED_INT, BUFFER_OFFSET(sizeof(cmd1))));
    GL_CHECK(glBindVertexArray(0));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &abo));
    GL_CHECK(glDeleteBuffers(1, &ebo));
    GL_CHECK(glDeleteBuffers(1, &in_buffer));
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
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}