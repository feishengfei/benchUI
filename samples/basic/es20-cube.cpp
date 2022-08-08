/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file cube.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for cube related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const float vertices[] = {
    -0.5,  0.5, -0.5,
    0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5,  0.5, -0.5,
    0.5,  0.5, -0.5,
    0.5, -0.5, -0.5,

    -0.5,  0.5,  0.5,
    -0.5, -0.5, -0.5,
    -0.5, -0.5,  0.5,
    -0.5,  0.5,  0.5,
    -0.5,  0.5, -0.5,
    -0.5, -0.5, -0.5,

    -0.5,  0.5,  0.5,
    0.5,  0.5, -0.5,
    -0.5,  0.5, -0.5,
    -0.5,  0.5,  0.5,
    0.5,  0.5,  0.5,
    0.5,  0.5, -0.5,

    0.5,  0.5, -0.5,
    0.5, -0.5,  0.5,
    0.5, -0.5, -0.5,
    0.5,  0.5, -0.5,
    0.5,  0.5,  0.5,
    0.5, -0.5,  0.5,

    0.5,  0.5,  0.5,
    -0.5, -0.5,  0.5,
    0.5, -0.5,  0.5,
    0.5,  0.5,  0.5,
    -0.5,  0.5,  0.5,
    -0.5, -0.5,  0.5,

    -0.5, -0.5, -0.5,
    0.5, -0.5,  0.5,
    -0.5, -0.5,  0.5,
    -0.5, -0.5, -0.5,
    0.5, -0.5, -0.5,
    0.5, -0.5,  0.5,
};

const float colors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,

    1.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,

    1.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 1.0, 1.0,

    1.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,

    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,

    1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,

    1.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,

    1.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 1.0, 1.0,

    0.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,

    0.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,

    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,

    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
};

GLuint programID;
GLint iLocPosition;
GLint iLocColor; 
GLint iLocMVP;
GLfloat GetUnf[16];

int window_Width = -1;
int window_Height = -1;

bool setupGraphics(int width, int height) {
    window_Width = width;
    window_Height = height;

    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLuint fragmentShaderID, vertexShaderID;
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    iLocColor = GL_CHECK(glGetAttribLocation(programID, "a_v4FillColor"));

    LOGD("iLocPosition = %i\n", iLocPosition);
    LOGD("iLocColor   = %i\n", iLocColor);

    GLint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glGetUniformfv(programID, iLocProjection, GetUnf));
    printf("glGetUniformfv = %f, %f, %f, %f\n", GetUnf[0],GetUnf[1],GetUnf[2],GetUnf[3]);

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glEnableVertexAttribArray(iLocColor));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));
    GL_CHECK(glVertexAttribPointer(iLocColor, 4, GL_FLOAT, GL_FALSE, 0, colors));

    static float angleX = 0, angleY = 0, angleZ = 0;

    Matrix modelView = Matrix::createRotationX(angleX);
    Matrix rotation = Matrix::createRotationY(angleY);
    modelView = rotation * modelView;
    rotation = Matrix::createRotationZ(angleZ);
    modelView = rotation * modelView;
    modelView[14] -= 2.5;
    Matrix perspective = Matrix::matrixPerspective(45.0f, window_Width/(float)window_Height, 0.01f, 100.0f);
    Matrix modelViewPerspective = perspective * modelView;
    GL_CHECK(glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, modelViewPerspective.getAsArray()));

    angleX += 3;
    angleY += 2;
    angleZ += 1;

    if(angleX >= 360) angleX -= 360;
    if(angleX < 0) angleX += 360;
    if(angleY >= 360) angleY -= 360;
    if(angleY < 0) angleY += 360;
    if(angleZ >= 360) angleZ -= 360;
    if(angleZ < 0) angleZ += 360;

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 36));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
