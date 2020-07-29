/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl41-glGet_v.cpp
 * @author cary.Zhang
 * @par History:
 *    A001: cary.Zhang, 2019-12-24
 * @par TestPoints:
 *
 * gl41-glGet_v
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID, VAOs, Buffers;
GLint iLocPosition = -1;

const float vertices[] =
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

bool setupGraphics() {
    string vertexShaderPath   = "ViewportArrayv.vert";
    string geometryShaderPath = "ViewportArrayv.gemo";
    string fragmentShaderPath = "ViewportArrayv.frag";

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   vertexShaderPath.c_str()},
            {GL_GEOMETRY_SHADER, geometryShaderPath.c_str()},
            {GL_FRAGMENT_SHADER, fragmentShaderPath.c_str()},
            {GL_NONE, NULL}
    };

    programID    = Shader::LoadShaders(shaders);
    iLocPosition = glGetAttribLocation(programID, "a_v4Position");
    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
}

void getInformation()
{
    GLfloat viewport1[4];
    GLfloat viewport2[4];
    GLfloat viewport3[4];
    GLfloat viewport4[4];
    GLdouble depthrange1[2];
    GLdouble depthrange2[2];
    GLdouble depthrange3[2];
    GLdouble depthrange4[2];
    LOGI("\n-----------GL_VIEWPORT 0-------------\n");
    GL_CHECK(glGetFloati_v(GL_VIEWPORT,0,viewport1));
    LOGI("glGetFloati_v is %f\n",viewport1[0]);
    LOGI("glGetFloati_v is %f\n",viewport1[1]);
    LOGI("glGetFloati_v is %f\n",viewport1[2]);
    LOGI("glGetFloati_v is %f\n",viewport1[3]);
    LOGI("\n-----------GL_VIEWPORT 1-------------\n");
    GL_CHECK(glGetFloati_v(GL_VIEWPORT,1,viewport2));
    LOGI("glGetFloati_v is %f\n",viewport2[0]);
    LOGI("glGetFloati_v is %f\n",viewport2[1]);
    LOGI("glGetFloati_v is %f\n",viewport2[2]);
    LOGI("glGetFloati_v is %f\n",viewport2[3]);
    LOGI("\n-----------GL_VIEWPORT 2-------------\n");
    GL_CHECK(glGetFloati_v(GL_VIEWPORT,2,viewport3));
    LOGI("glGetFloati_v is %f\n",viewport3[0]);
    LOGI("glGetFloati_v is %f\n",viewport3[1]);
    LOGI("glGetFloati_v is %f\n",viewport3[2]);
    LOGI("glGetFloati_v is %f\n",viewport3[3]);
    LOGI("\n-----------GL_VIEWPORT 3-------------\n");
    GL_CHECK(glGetFloati_v(GL_VIEWPORT,3,viewport4));
    LOGI("glGetFloati_v is %f\n",viewport4[0]);
    LOGI("glGetFloati_v is %f\n",viewport4[1]);
    LOGI("glGetFloati_v is %f\n",viewport4[2]);
    LOGI("glGetFloati_v is %f\n",viewport4[3]);

    LOGI("\n-----------GL_DEPTH_RANGE 0-------------\n");
    GL_CHECK(glGetDoublei_v(GL_DEPTH_RANGE, 0, depthrange1));
    LOGI("glGetDoublei_v is %f\n",depthrange1[0]);
    LOGI("glGetDoublei_v is %f\n",depthrange1[1]);
    LOGI("\n-----------GL_DEPTH_RANGE 1-------------\n");
    GL_CHECK(glGetDoublei_v(GL_DEPTH_RANGE, 1, depthrange2));
    LOGI("glGetDoublei_v is %f\n",depthrange2[0]);
    LOGI("glGetDoublei_v is %f\n",depthrange2[1]);
    LOGI("\n-----------GL_DEPTH_RANGE 2-------------\n");
    GL_CHECK(glGetDoublei_v(GL_DEPTH_RANGE, 2, depthrange3));
    LOGI("glGetDoublei_v is %f\n",depthrange3[0]);
    LOGI("glGetDoublei_v is %f\n",depthrange3[1]);
    LOGI("\n-----------GL_DEPTH_RANGE 3-------------\n");
    GL_CHECK(glGetDoublei_v(GL_DEPTH_RANGE, 3, depthrange4));
    LOGI("glGetDoublei_v is %f\n",depthrange4[0]);
    LOGI("glGetDoublei_v is %f\n",depthrange4[1]);
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
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
    getInformation();
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
