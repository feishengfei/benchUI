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

GLuint programID;
GLuint vao;
GLuint vbo;

Timer this_one;

bool setupGraphics(int width, int height) {

    ShaderInfo  shaders[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "equalspace.tcs", },
            {GL_TESS_EVALUATION_SHADER, "equalspace.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };

    programID = Shader::LoadShaders( shaders );

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

void renderFrame(void) {
    float Time = this_one.getTime();

    Matrix perspective = Matrix::matrixPerspective(45.0f, WINDOW_W / (float)WINDOW_H, 1.0f, 100.0f);
    Matrix translate = Matrix::createTranslation(0.0f, 0.0f, -2.0f);
    Matrix rotateX = Matrix::createRotationX(Time * 17.0f);
    Matrix rotateY = Matrix::createRotationY(Time * 10.0f);
    Matrix rotate = rotateY * rotateX;
    Matrix mv_matrix = translate * rotate;
    Matrix mvp_matrix = perspective * mv_matrix;

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glCullFace(GL_BACK));
    GL_CHECK(glFrontFace(GL_CCW));
    GL_CHECK(glPatchParameteri(GL_PATCH_VERTICES, 4));
    GL_CHECK(glPointSize(10));
    GL_CHECK(glUniform1f(0, Time));
    GL_CHECK(glUniformMatrix4fv(1, 1, GL_FALSE, mvp_matrix.getAsArray()));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
    GL_CHECK(glDrawArrays(GL_PATCHES, 0, 4));

}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
   // bool end = false;
   // while(!end)
     for(int i=0; i<20; i++){
        renderFrame();
         string bmp_file = filename + ".bmp";
         LOGI("bmp_file=%s",bmp_file.c_str());
         save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
