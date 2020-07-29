/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file glDepthRangef.cpp
 * @author cary.Zhang
 * @par History:
 *    A001: cary.Zhang, 2019-08-26, Add commit
 * @brief basic test for depthrangef related API
 * @par TestPoints:
 *  
 *  glDepthRangef
 *  glDepthRangeIndexed
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
const float triangleVertices1[] =
{
    -0.5f,  0.6f, 0.2f,
    -0.5f, -0.4f, 0.2f,
     0.5f, -0.4f, 0.2f
};
const float triangleVertices2[] =
{
    -0.4f,  0.7f, 0.3f,
    -0.4f, -0.3f, 0.3f,
     0.6f, -0.3f, 0.3f
};

const float triangleColors1[] =
{
    0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.5,
    0.0, 1.0, 0.0, 0.5
};
const float triangleColors2[] =
{
    0.0, 0.0, 1.0, 0.5,
    0.0, 0.0, 1.0, 0.5,
    0.0, 0.0, 1.0, 0.5
};

bool setupGraphics(){
    string vertexShaderPath = ((string)GLSL_PATH) + "glDepthRangef.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "glDepthRangef.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    iLocPosition = glGetAttribLocation(programID, "a_v4Position");
    iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor");
}

void renderFrame1() {
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices1));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    if(iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors1));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }   

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void renderFrame2() {
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices2));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    if(iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors2));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    string bmp_file = filename + ".bmp";

    setupGraphics();
    GL_CHECK(glViewport(0, 0, WINDOW_W/2, WINDOW_H/2));    
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDepthRangef( 0, 1));
    renderFrame1();
    renderFrame2();

    setupGraphics();
    GL_CHECK(glViewport(0, WINDOW_H/2, WINDOW_W/2, WINDOW_H/2));    
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDepthRangef(1, 0));
    renderFrame1();
    renderFrame2();

    setupGraphics();
    GL_CHECK(glViewport(WINDOW_W/2, 0, WINDOW_W/2, WINDOW_H/2));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDepthRangeIndexed(0, 0, 1));
    renderFrame1();
    renderFrame2();

    setupGraphics();
    GL_CHECK(glViewport(WINDOW_W/2, WINDOW_H/2, WINDOW_W/2, WINDOW_H/2));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDepthRangeIndexed(0, 1, 0));
    renderFrame1();
    renderFrame2();

    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__,  GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();

    return 0;
}
