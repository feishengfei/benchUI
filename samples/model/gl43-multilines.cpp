
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;
float pointVertices[3000];
GLuint indices[1500];
bool setupGraphics(int w, int h) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "multilines.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "fixedcolor.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (!programID) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glViewport(0, 0, w, h));
}

void render(){
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    for(int i = 0; i < sizeof(pointVertices)/sizeof(pointVertices[0]) ; i++) {
        pointVertices[i] = ((float)(rand() % 100)) / 50 - 1;
    }
    for(int i = 0; i < sizeof(indices)/sizeof(indices[0]) ; i++ )
    {
        indices[i] = i;
    }

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertices), pointVertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawElements(GL_LINE_LOOP, 1500, GL_UNSIGNED_INT, indices));
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