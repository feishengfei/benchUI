
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, VAOs, abo, ebo;

GLfloat vertices[] = {-0.3, 0.3,
                      -0.3,-0.3,
                       0.3, 0.3,
                       0.3,-0.3,
                       0.1, 0.1};

GLfloat vertColor[] = {1.0, 0, 0, 1.0,
                       0, 1.0, 0, 1.0,
                       0, 0, 1.0, 1.0,
                       0.0, 1.0, 0, 1.0,
                       0.0, 0, 1.0, 1.0};

GLuint indices[]={0, 1, 2, 0, 2, 3, 4, 3, 2};

bool setupGraphics() {
    string vertexShaderPath   = ((string)GLSL_PATH) + "drawbase.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "drawbase.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (!programID) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glUniform2f(0, 0.8, 0.2));
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &abo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, abo));


    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertColor) + sizeof(vertices), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertColor), vertColor));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
    GL_CHECK(glEnableVertexAttribArray(1));

    GLint params;
    GL_CHECK(glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &params));
    LOGI("GL_ARRAY_BUFFER, GL_BUFFER_SIZE: %d\n", params);


    return true;
}

void render(int i, int w, int h) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
    static const GLuint black[] = { 0, 0, 0, 0};
    GL_CHECK(glClearBufferuiv(GL_COLOR, 0, black));
    GL_CHECK(glViewport(0, 0, w, h));

    switch (i) {
    case 0:
    GL_CHECK(glDrawElementsBaseVertex(GL_LINES, 2, GL_UNSIGNED_INT, 0, 2));
        break;
    case 1:
    GL_CHECK(glDrawRangeElementsBaseVertex(GL_LINES, 0, 3, 4, GL_UNSIGNED_INT, 0, 1));
        break;
    case 2:
    GL_CHECK(glDrawRangeElements(GL_LINES, 0, 3, 4, GL_UNSIGNED_INT, 0));
        break;
    default:
        break;
    }
    GL_CHECK(glBindVertexArray(0));
    int status = glGetGraphicsResetStatus();
    LOGI("glGetGraphicsResetStatus is =%d", status);
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &abo));
    GL_CHECK(glDeleteBuffers(1, &ebo));
}

void Sample::test() {
    setupGraphics();
    for (int i = 0; i < 3; i++) {
        char ss[5];
        sprintf(ss, "%d", i);
        render(i, WINDOW_W, WINDOW_H);
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