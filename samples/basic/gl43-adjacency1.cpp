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
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID, VAOs, Buffers;
GLfloat vertices[]={-0.5,-0.5, 0.0, 1.0,
                    0.5,-0.5, 0.0, 1.0,
                    0.5, 0.5, 0.0, 1.0,
                    -0.5, 0.5, 0.0, 1.0};

GLfloat color[] = {0.0, 0.0, 0.0, 1.0,
                    0.0, 0.0, 0.0, 1.0,
                    0.0, 0.0, 0.0, 1.0,
                    1.0, 1.0, 1.0, 1.0};

bool setupGraphics(int w, int h) {

    ShaderInfo  shaders[] = {
            { GL_VERTEX_SHADER,  "adjacency1.vert" },
            { GL_GEOMETRY_SHADER, "adjacency.gemo" },
            { GL_FRAGMENT_SHADER, "adjacency.frag" },
            { GL_NONE, NULL }
    };

    programID = Shader::LoadShaders( shaders );

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

    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(0.1f, 0.3f, 0.0f, 1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_LINES_ADJACENCY, 0, 4));
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

