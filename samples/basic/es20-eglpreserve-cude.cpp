/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file eglpreserve-cude.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for eglpreserve-cude related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

static const GLubyte cubeIndices[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 0, 1,   1, 1,   1, 7, 3, 5,   5, 6,   6, 0, 4, 2,
};

static const float cubeVertices[] = {
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
};

static const float cubeColors[] = {
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
};

string scissorOff = "Scissor:  off";
string scissorOn = "Scissor:  on ";
string preserveOff = "Preserve: off";
string preserveOn = "Preserve: on ";

GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLint iLocProjection = -1;
GLint iLocModelview = -1;

Matrix perspective;
Matrix translation;

unsigned int window_Width = 0;
unsigned int window_Height = 0;

static float angleX = 0.0f;
static float angleY = 0.0f;
static float angleZ = 0.0f;

bool setupGraphics(int width, int height) {
    window_Width = width;
    window_Height = height;

    string vertexShaderPath = ((string)GLSL_PATH) + "eglpreserve.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "eglpreserve.frag";

    perspective = Matrix::matrixPerspective(45.0f, window_Width /(float)window_Height, 0.01f, 100.0f);

    translation = Matrix::createTranslation(0.0f, 0.0f, -2.0f);

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glCullFace(GL_BACK));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLuint vertexShaderID = 0;
    GLuint fragmentShaderID = 0;
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    if(iLocPosition == -1) {
        LOGE("Attribute not found at %s:%i\n", __FILE__, __LINE__);
        return false;
    }
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    iLocFillColor = GL_CHECK(glGetAttribLocation(programID, "a_v4FillColor"));
    if(iLocFillColor == -1) {
        LOGW("Warning: Attribute not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }

    iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, perspective.getAsArray()));
    }

    iLocModelview = GL_CHECK(glGetUniformLocation(programID, "u_m4Modelview"));
    if(iLocModelview == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    }

    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0));

    EGLint swapBehaviour;
    if(eglQuerySurface(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW),
                       EGL_SWAP_BEHAVIOR, &swapBehaviour) != EGL_TRUE) {
        LOGW("Warning: eglQuerySurface() failed at %s:%i\n", __FILE__, __LINE__);
    }

    LOGI("Default values:");
    LOGI("EGL_SWAP_BEHAVIOR = 0x%.4x", (int)swapBehaviour);
    switch(swapBehaviour) {
        case (EGL_BUFFER_PRESERVED):
            LOGI("                  = EGL_BUFFER_PRESERVED");
            break;
        case (EGL_BUFFER_DESTROYED):
            LOGI("                  = EGL_BUFFER_DESTROYED");
            break;
        default:
            LOGI("                  = UNKNOWN");
            break;
    }

    if(eglSurfaceAttrib(eglGetCurrentDisplay(), eglGetCurrentSurface(EGL_DRAW),
                        EGL_SWAP_BEHAVIOR, EGL_BUFFER_PRESERVED) != EGL_TRUE) {
        LOGW("Warning: eglSurfaceAttrib() failed at %s:%i\n", __FILE__, __LINE__);
    }

    return true;
}

void renderFrame(void) {
    static bool fullScreen = false;
    static bool preserve = false;

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    Matrix rotationX = Matrix::createRotationX(angleX);
    Matrix rotationY = Matrix::createRotationY(angleY);
    Matrix rotationZ = Matrix::createRotationZ(angleZ);

    angleX += 3;
    angleY += 2;
    angleZ += 1;
    if(angleY >= 360) angleY -= 360;
    if(angleZ >= 360) angleZ -= 360;

    Matrix modelView = translation * rotationX;
    modelView = modelView * rotationY;
    modelView = modelView * rotationZ;

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glUniformMatrix4fv(iLocModelview, 1, GL_FALSE, modelView.getAsArray()));
    GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, perspective.getAsArray()));

    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, cubeVertices));

    if(iLocFillColor != -1) {
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, cubeColors));
    }

    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, 22, GL_UNSIGNED_BYTE, cubeIndices));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    while(angleX <= 360) {
        renderFrame();
        char ss[3];
        sprintf(ss, "_%d", (int)angleX);
        string bmp_file = filename + ss + ".bmp";
        LOGI("bmp_file=%s", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
