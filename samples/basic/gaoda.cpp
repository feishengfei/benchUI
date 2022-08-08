/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file aishe.cpp
 * @author Cary.Zhang
 * @par History:
 *    A001: Cary.Zhang, 2020-01-11, create file
 * @par TestPoints:
 *      
 *
 */

#include "gaoda.h"
#include "Sample.h"
#include "Timer.h"

#define WINDOW_W_ 512
#define WINDOW_H_ 512

using std::string;
using namespace BotsonSDK;

GLuint programID;
GLuint VAOs;
GLuint Buffers;

bool setupGraphics()
{
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

      ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "gaoda.vert"},
            {GL_FRAGMENT_SHADER, "gaoda.frag"},
            {GL_NONE, NULL}
    };

    programID = Shader::LoadShaders(shaders);

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    //GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    //GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertices), vertices));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glUseProgram(programID));
    
    static float angleX = 0, angleY = 0, angleZ = 0;
    
    Matrix scale = Matrix::createScaling(0.03f, 0.03f, 0.03f);  
    Matrix modelView = Matrix::createRotationX(angleX);
    Matrix rotation = Matrix::createRotationY(angleY);
    modelView=modelView * scale;
    modelView = rotation * modelView;
    rotation = Matrix::createRotationZ(angleZ);
    modelView = rotation * modelView;
    modelView[14] -= 1.8;

    Matrix perspective = Matrix::matrixPerspective(45.0f, WINDOW_W_/(float)WINDOW_H_, 0.5f, 100.0f);
    Matrix modelViewPerspective = perspective * modelView;

    GL_CHECK(glUniformMatrix4fv(0, 1, GL_FALSE, modelViewPerspective.getAsArray()));

   
    angleX += 0;
    angleY += 1;
    angleZ += 0;

    if(angleX >= 360) angleX -= 360;
    if(angleX < 0) angleX += 360;
    if(angleY >= 360) angleY -= 360;
    if(angleY < 0) angleY += 360;
    if(angleZ >= 360) angleZ -= 360;
    if(angleZ < 0) angleZ += 360;

    //GL_CHECK(glDepthFunc(GL_LESS));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 244737));
}

void Sample::test() {
    setupGraphics();

    Timer fpsTimer;
    fpsTimer.reset();
    int i = 1000;
    float start = fpsTimer.getTime();
    while(i > 0)
    {
        float fFPS = fpsTimer.getFPS();
        if(fpsTimer.isTimePassed(1.0f))
        {
            printf("FPS:\t%.1f\n", fFPS);
        }
        renderFrame();
       Sample::SwapBuffers();
       i--;
    }
    float end = fpsTimer.getTime();
    LOGI("i = %d, time is %f s\n", i, (end -start));
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

