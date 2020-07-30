/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texsub.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for texsub related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;



#define BUFFER_OFFSET(i) ((char *)NULL + (i))

const float vertices[] = {-0.5,-0.5, 0.0, 1.0,
                          0.5,-0.5, 0.0, 1.0,
                          0.5, 0.5, 0.0, 1.0,
                         -0.5, 0.5, 0.0, 1.0,
                          0.0, 0.0, 0.0, 1.0};

const float colors[] = {0.0, 0.0, 0.0, 1.0,
                      0.0, 0.0, 0.0, 1.0,
                      0.0, 0.0, 0.0, 1.0,
                      1.0, 1.0, 1.0, 1.0,
                      0.25, 0.25, 0.25, 1.0};

GLuint programID;
GLuint vao;
GLuint vbo;
GLuint ebo;

GLuint indices[]={0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};
bool setupGraphics(int w, int h) {

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "noadjacency.vert"},
            {GL_FRAGMENT_SHADER, "noadjacency.frag"},
            {GL_NONE, NULL}
    };

    programID = Shader::LoadShaders(shaders);

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors),
                          NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,
                                   BUFFER_OFFSET(0)));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,
                                   BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glEnableVertexAttribArray(1));

    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(0.1f, 0.3f, 0.0f, 1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL));
    //GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

