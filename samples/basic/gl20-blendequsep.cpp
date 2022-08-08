/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file blendequsep.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for blendequsep related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;

GLuint programID, VAOs, Buffers;

const float Vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
};

const float Colors[] = {
        1.0, 0.0, 0.0, 0.3,
        0.0, 1.0, 0.0, 0.3,
        0.0, 0.0, 1.0, 0.3,
};

const GLubyte indices[] = {0,1,2};

static const GLenum factors[] = {
        GL_FUNC_ADD,
        GL_FUNC_SUBTRACT,
        GL_FUNC_REVERSE_SUBTRACT
};

bool setupGraphics(int width, int height, GLenum mode_rgb, GLenum mode_a) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_GREATER));
    if(glIsEnabled(GL_DEPTH_TEST))
    LOGI("IsEnable(GL_DEPTH_TEST)=true\n");

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Colors), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Colors), Colors));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(Vertices))));

    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));
    GL_CHECK(glBlendEquationSeparate(mode_rgb, mode_a));
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.3f, 0.3f, 0.3f, 0.7f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        for(int j=0; j<ARRAY_NUM(factors); j++) {
            setupGraphics(WINDOW_W, WINDOW_H, factors[i], factors[j]);
            renderFrame();
            string mode_rgb_name = get_enum_name(factors[i]);
            string mode_a_name   = get_enum_name(factors[j]);
            string bmp_file      = filename + "-" + mode_rgb_name + mode_a_name + ".bmp";
            LOGI("bmp_file=%s", bmp_file.c_str());
            save2bmp(bmp_file.c_str());
            Sample::SwapBuffers();
        }
    }
    //setupGraphics(WINDOW_W, WINDOW_H, factors[0], factors[0]);
    //renderFrame();
    //string bmp_file      = filename + ".bmp";
    //LOGI("bmp_file=%s", bmp_file.c_str());
    //save2bmp(bmp_file.c_str());
    //Sample::SwapBuffers();
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
