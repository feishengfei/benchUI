
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vertices[] = {
       -0.8, -0.8, 0.0, 1.0,
       -0.2,  0.8, 0.0, 1.0,
        0.0,  0.0, 0.0, 1.0,
        0.3,  0.8, 0.0, 1.0,
        0.8, -0.8, 0.0, 1.0,
};

GLfloat color[] = {
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0,
        1.0, 0.0, 0.0, 1.0
};

GLuint programID, VAOs, Buffers;

bool setupGraphics(int w, int h) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "Triangle.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "Triangle.frag";

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
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(color), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color), color));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glViewport(0, 0, w, h));

    GLint k;
    GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &k));
    LOGI("max vertex attribs is %d\n", k);
}

void render(){
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glPointSize(1.0));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 1));

    GL_CHECK(glPointSize(0.4));
    GL_CHECK(glDrawArrays(GL_POINTS, 1, 1));

    GL_CHECK(glPointSize(0.8));
    GL_CHECK(glDrawArrays(GL_POINTS, 2, 1));

    GL_CHECK(glPointSize(5.2));
    GL_CHECK(glDrawArrays(GL_POINTS, 3, 1));

    GL_CHECK(glPointSize(10.8));
    GL_CHECK(glDrawArrays(GL_POINTS, 4, 1));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
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