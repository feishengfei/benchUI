/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file depthfunc.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for depthfunc related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Timer.h"
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;

GLuint programID[4];
GLuint VAOs[2], Buffers[2];
const float vertices1[] = {
    -0.8f, -0.8f, 0.4f,
    0.0f,  0.8f, 0.4f,
     0.8f, -0.8, 0.4f
};

const float vertices2[] = {
     -0.8f,  0.8f, 0.6f,
      0.8f,  0.8f, 0.6f,
      0.0f, -0.8f, 0.6f
};

const float color1[] = {
    0.9, 0.9, 0.0, 0.1,
    0.0, 0.9, 0.9, 0.1,
    0.9, 0.0, 0.9, 0.1
};

const float color2[] = {
    0.9, 0.0, 0.0, 0.1,
    0.0, 0.9, 0.0, 0.1,
    0.0, 0.0, 0.9, 0.1,
};

bool setupGraphics(int width, int height, int i) {
    string fragmentShaderPath[4];
    string vertexShaderPath = ((string)GLSL_PATH) + "fragdepth.vert";
    fragmentShaderPath[0] = ((string)GLSL_PATH) + "fragdepth.frag";
    fragmentShaderPath[1] = ((string)GLSL_PATH) + "fragdepth1.frag";
    fragmentShaderPath[2] = ((string)GLSL_PATH) + "fragdepth2.frag";
    fragmentShaderPath[3] = ((string)GLSL_PATH) + "fragdepth3.frag";
 
    programID[i]  = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
            fragmentShaderPath[i].c_str()));

    GL_CHECK(glGenVertexArrays(2, &VAOs[0]));
    GL_CHECK(glGenBuffers(2, &Buffers[0]));

    GL_CHECK(glBindVertexArray(VAOs[0]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1) + sizeof(color1), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices1), vertices1));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(color1), color1));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices1))));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(glBindVertexArray(VAOs[1]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2) + sizeof(color2), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices2), vertices2));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices2), sizeof(color2), color2));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices2))));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_ALWAYS));

    return true;
}

void renderFrame(int i) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID[i]));

    GL_CHECK(glBindVertexArray(VAOs[0]));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 3));

    GL_CHECK(glDepthFunc(GL_GREATER));

    GL_CHECK(glBindVertexArray(VAOs[1]));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 3));
}

void Sample::test() {
    for(int i=0; i<4; i++) {
        setupGraphics(WINDOW_W, WINDOW_H, i);
        renderFrame(i);
        char ss[3];
        sprintf(ss, "%d", i);
        string bmp_file = filename + "-" + ss + ".bmp";
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    Timer fpsTimer;
    float start = fpsTimer.getTime();
    sample.test();
    float end = fpsTimer.getTime();
    LOGI("time is %f s\n", (end - start));

    return 0;
}
