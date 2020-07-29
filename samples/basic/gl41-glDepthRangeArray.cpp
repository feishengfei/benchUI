/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file glDepthRangeArrayv.cpp
 * @author cary.Zhang
 * @par History:
 *    A001: cary.Zhang, 2019-12-24
 * @par TestPoints:
 *
 * glDepthRangeArrayv
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
const float triangleVertices[] =
{
    -0.5f,  0.6f, 0.2f,
    -0.5f, -0.4f, 0.2f,
     0.5f, -0.4f, 0.2f
};
const float viewportArrayV[] = {0.0, 0.0, WINDOW_W/2, WINDOW_H/2,
                                0, WINDOW_H/2, WINDOW_W/2, WINDOW_H/2,
                                WINDOW_W/2, 0, WINDOW_W/2, WINDOW_H/2,
                                WINDOW_W/2, WINDOW_H/2, WINDOW_W/2, WINDOW_H/2
};

const double depthrangeArrayV_1[] = {0, 1};
const double depthrangeArrayV_2[] = {1, 0};

const double depthrangeArrayV[] = {0, 1, 1, 0};

bool setupGraphics(){
    string vertexShaderPath = "ViewportArrayv.vert";
    string geometryShaderPath = "ViewportArrayv.gemo";
    string fragmentShaderPath = "ViewportArrayv.frag";

    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER,   vertexShaderPath.c_str() },
        { GL_GEOMETRY_SHADER, geometryShaderPath.c_str() },
        { GL_FRAGMENT_SHADER, fragmentShaderPath.c_str() },
        { GL_NONE, NULL }
    };

    programID = Shader::LoadShaders( shaders );
    iLocPosition = glGetAttribLocation(programID, "a_v4Position");
    iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor");
}

void renderFrame() {
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    string bmp_file = filename + ".bmp";

    GL_CHECK(glDepthRangeArrayv(0, 2, depthrangeArrayV)); 
    GL_CHECK(glDepthRangeArrayv(2, 1, depthrangeArrayV_1)); 
    GL_CHECK(glDepthRangeArrayv(3, 1, depthrangeArrayV_2)); 
    GL_CHECK(glViewportArrayv(0, 4, viewportArrayV));   

    setupGraphics();
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    GL_CHECK(glUseProgram(programID));
    renderFrame();

    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__,  GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();

    return 0;
}
