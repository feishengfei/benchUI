
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */

/**
 * @file gl45-bindvertexbuffer.cpp
 * @author Alan.Liu
 * @par History:
 *    A001: Alan.liu, 2019-05-30, Add commit
 * @brief basic test for VertexAttribLFormat related API
 * @par TestPoints:glVertexAttribLFormat
 *
 */

//
#include "Sample.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

const float triangleVertices[] =
                     {
                             -0.5f, -0.5f, 0.0f,
                             0.5f, -0.5f, 0.0f,
                             0.0f,  0.5f, 0.0f
                     };

GLuint programID;
GLint iLocPosition = -1;
GLuint VertexArrayName;
GLuint vbo;

bool setupGraphics(int width, int height)
{
    string vertexShaderPath =(string)GLSL_PATH + "compute1.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "compute.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
                                               fragmentShaderPath.c_str()));
    if (programID == 0)
    {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glUseProgram(programID));

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));

    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices),
                          triangleVertices, GL_STATIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glGenVertexArrays(1, &VertexArrayName));
    GL_CHECK(glBindVertexArray(VertexArrayName));
    GL_CHECK(glVertexAttribBinding(iLocPosition, 0));
    GL_CHECK(glVertexAttribFormat(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glBindVertexBuffer(0, vbo, 0, 3*sizeof(float)));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VertexArrayName));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}


void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    GL_CHECK(glEnable(GL_DEBUG_OUTPUT));
    string bmp_file = filename + ".bmp";
    save2bmp(bmp_file.c_str());
    LOGI("bmp_file=%s", bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}