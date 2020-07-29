/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file drawarrayinstance.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for drawarrayinstance related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include <GL/glcorearb.h>
#include "Timer.h"

using std::string;
using namespace BotsonSDK;

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vert[]={ -0.9f, -0.9f,    0.9f, -0.9f,     0.9f, 0.9f,    -0.9f, 0.9f,
                 1.0, 0.0, 0.0,    0.0, 1.0, 0.0,  0.0, 0.0, 1.0, 0.0, 1.0, 1.0
};

GLuint programID[3];
GLuint vao;
GLuint vbo;

bool init_shader(){
    ShaderInfo  shaders[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmaxbak0.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[0] = Shader::LoadShaders(shaders);

    ShaderInfo  shaders1[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmaxbak1.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[1] = Shader::LoadShaders(shaders1);

    ShaderInfo  shaders2[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmaxbak2.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[2] = Shader::LoadShaders(shaders2);
}
bool setupGraphics(int width, int height) {
    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float)*2*4)));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glClearColor(0.1, 0.1, 0.1, 1.0));
    GL_CHECK(glViewport(0, 0, width, height));

    return true;
}

void renderFrame(int i) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID[i]));
    GL_CHECK(glPatchParameteri(GL_PATCH_VERTICES, 4));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    GL_CHECK(glDrawArrays(GL_PATCHES, 0, 4));

}

void Sample::test() {
    init_shader();
    setupGraphics(WINDOW_W, WINDOW_H);
    for (int i = 0; i < 3; i++) {
        renderFrame(i);
        char ss[3];
        sprintf(ss, "%d", i);
        string bmp_file = filename + "-" + ss + ".bmp";
        LOGI("bmp_file=%s\n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}


int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
