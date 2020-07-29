
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, VAOs, Buffers, ebo;

GLfloat vertices[] = {-0.3, 0.3,
                      -0.3,-0.3,
                       0.3, 0.3,
                       0.3,-0.3};

GLfloat vertColor[] = {1.0, 0, 0, 1.0,
                       0, 1.0, 0, 1.0,
                       0, 0, 1.0, 1.0,
                       1.0, 1.0, 0, 1.0,
                       1.0, 0.0, 1.0, 1.0};

GLfloat vertPosOffsets[] = {-0.5, 0.5,
                            -0.5,-0.5,
                             0.5, 0.5,
                             0.5,-0.5,
                             0.0, 0.0};

GLuint indices[]={0, 1, 2, 0, 2, 3};

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

    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CHECK(glViewport(0, 0, w, h));

}

void render(int k){
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    switch(k){
    case 0:
    GL_CHECK(glDrawElementsInstanced(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL, 3));
    break;
    case 1:
    GL_CHECK(glDrawElementsInstancedBaseInstance(GL_TRIANGLES, 3, GL_UNSIGNED_INT,
                                                 NULL, 3, 2));
    break;
    case 2:
    GL_CHECK(glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, 3,
                                                           GL_UNSIGNED_INT, NULL, 3, 1, 2));
    break;
    case 3:
    GL_CHECK(glDrawElementsInstancedBaseVertex(GL_TRIANGLES, 3,
                                                           GL_UNSIGNED_INT, NULL, 3, 1));
        break;
    default:
        break;
    }
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
    GL_CHECK(glDeleteBuffers(1, &ebo));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<4; i++){
        char ss[5];
        sprintf(ss, "%d", i);
        render(i);
        string bmp_file1 = filename + ss + ".bmp";
        save2bmp(bmp_file1.c_str());
        SwapBuffers();
    }
    de_init();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}