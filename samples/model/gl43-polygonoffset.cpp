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

GLfloat vertices1[]={
        -0.8, -0.8, 0.0, 1.0,
         0.0,  0.8, 0.2, 1.0,
         0.8, -0.8, 0.0, 1.0
};

GLfloat color1[]={
        1.0, 1.0, 0.0, 1.0,
        1.0, 1.0, 0.0, 1.0,
        1.0, 1.0, 0.0, 1.0
};

GLfloat vertices2[]={
        -0.8,  0.8, 0.2, 1.0,
         0.8,  0.8, 0.2, 1.0,
         0.0, -0.8, 0.0, 1.0
};

GLfloat color2[]={
        0.0, 1.0, 1.0, 1.0,
        0.0, 1.0, 1.0, 1.0,
        0.0, 1.0, 1.0, 1.0
};

GLuint programID;
GLuint vao[2];
GLuint vbo[2];

Timer this_one;

bool setupGraphics(int width, int height) {

    ShaderInfo  shaders[] = {
            {GL_VERTEX_SHADER, "polygonoffset.vert", },
            {GL_FRAGMENT_SHADER, "polygonoffset.frag", },
            {GL_NONE,NULL},
    };

    programID = Shader::LoadShaders( shaders );

    GL_CHECK(glGenVertexArrays(2, &vao[0]));
    GL_CHECK(glGenBuffers(2, &vbo[0]));

    GL_CHECK(glBindVertexArray(vao[0]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, 2*sizeof(vertices1), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices1), vertices1));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(color1), color1));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices1))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(glBindVertexArray(vao[1]));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo[1]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, 2*sizeof(vertices2), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices2), vertices2));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices2), sizeof(color2), color2));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices1))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(glClearColor(0.1, 0.1, 0.1, 1.0));
    GL_CHECK(glViewport(0, 0, width, height));

    return true;
}

void renderFrame(void) {
    float Time = this_one.getTime();
    GL_CHECK(glUseProgram(programID));
    static float angleX = 0;

    Matrix scale     = Matrix::createScaling(0.5f, 0.5f, 1.0f);
    Matrix rotation  = Matrix::createRotationX(angleX);
    Matrix modelView = rotation * scale;//add scale by cgj
    GL_CHECK(glUniformMatrix4fv(0, 1, GL_FALSE, modelView.getAsArray()));

    angleX += 0.1;

    if (angleX >= 360)
        angleX -= 360;
    if (angleX < 0)
        angleX += 360;

    GL_CHECK(glClearDepthf(1.0f));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

//    glEnable(GL_POLYGON_OFFSET_FILL);
//    glPolygonOffset(1.0, 1.0);


    GL_CHECK(glBindVertexArray(vao[0]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CHECK(glBindVertexArray(0));

//    glPolygonOffset(-1.0, -1.0);
    GL_CHECK(glBindVertexArray(vao[1]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    GL_CHECK(glBindVertexArray(0));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    bool end = false;
    while(!end) {
        renderFrame();
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
