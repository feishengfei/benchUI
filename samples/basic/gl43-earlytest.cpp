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

using std::string;
using namespace BotsonSDK;

GLuint programID;
GLuint qu_dep;
Timer this_one;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "earlytest.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "earlytest.frag";
 
    programID  = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
            fragmentShaderPath.c_str()));   

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(0.5));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_GREATER));

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    float t = this_one.getTime();

    float vertices[] = {
            -0.8f, -0.8f, (sin(t)+1.0)/2.0, 1.0,
             0.0f,  0.8f, (cos(t)+1.0)/2.0, 1.0,
             0.8f, -0.8f, (sin(t)+1.0)/(cos(t)+1.0), 1.0
    };


    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, vertices));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 3));
}

void Sample::test() {
    for(int i=0; i<20; i++) {
        setupGraphics(1600, 1200);
        float fFPS = this_one.getFPS();
        if(this_one.isTimePassed(1.0f))
        {
            printf("FPS:\t%.1f\n", fFPS);
        }
        renderFrame();
        string bmp_file   = filename + ".bmp";
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    this_one.reset();
    sample.test();
    return 0;
}
