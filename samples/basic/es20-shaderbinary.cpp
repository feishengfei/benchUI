/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file shaderbinary.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for shaderbinary related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
};

const float triangleVerticesLittle[] = {
    -0.45f, -0.45f, 0.0f,
     0.45f, -0.45f, 0.0f,
     0.0f,  0.45f, 0.0f,
     0.0f, -0.45f, 0.0f
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

const GLubyte indices[] = {0,1,2};
const GLubyte subdata[] = {1,3};

const float triangleVertices2[] = {
     0.0f,-0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
};

const float triangleColors2[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
};

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition =  GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    iLocFillColor =  GL_CHECK(glGetAttribLocation(programID, "a_v4FillColor"));
    //GLuint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
   // if(iLocProjection == -1) {
   //     LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
   // } else {
   //     GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
   // }

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if(iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    GLuint numattrS[6];
    GLsizei maxS=6;
    GLsizei Scount;
    GLint GPnum;
    GLint prange[2];
    GLint preci;
    GLint lengthS;
    GLint tmp;

    setupGraphics(WINDOW_W, WINDOW_H);

    bool end = false;
    while(!end) {
        if (platform->checkWindow() != Platform::WINDOW_IDLE) {
            end = true;
        }

        renderFrame();
        Sample::SwapBuffers();
    }

    glReleaseShaderCompiler();

    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_HIGH_INT, prange, &preci);
    LOGI("glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_HIGHT_FLOAT): range(%d, %d), prec(%d)\n", (int)prange[0], (int)prange[1], (int)preci);
    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_MEDIUM_INT, prange, &preci);
    LOGI("glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_MEDIUM_FLOAT): range(%d, %d), prec(%d)\n", (int)prange[0], (int)prange[1], (int)preci);
    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_LOW_INT, prange, &preci);
    LOGI("glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_LOW_FLOAT): range(%d, %d), prec(%d)\n", (int)prange[0], (int)prange[1], (int)preci);

    glGetShaderiv(vertexShaderID, GL_SHADER_SOURCE_LENGTH, &lengthS);
    LOGI("glGetShaderiv(GL_SHADER_SOURCE_LENGTH): %d\n", lengthS);

    char *source = (char *)calloc(lengthS + 1, sizeof(char));
    glGetShaderSource(vertexShaderID, lengthS+1, &tmp, source);
    LOGI("glGetShaderSource: %s\n\n",source);
    free(source);

    glGetProgramiv(programID, GL_ATTACHED_SHADERS, &GPnum);
    LOGI("glGetProgramiv(GL_ATTACHED_SHADERS): %d\n", GPnum);

    glDetachShader(programID, vertexShaderID);
    glGetAttachedShaders(programID, maxS, &Scount, numattrS);
    LOGI("glGetAttachedShaders: count=%d (%d, %d, %d, %d, %d, %d)\n", Scount,numattrS[0], numattrS[1], numattrS[2],numattrS[3],numattrS[4],numattrS[5]);

    glDeleteShader(vertexShaderID);
    GLboolean isS = glIsShader(vertexShaderID);
    LOGI("glIsShader(vertexShaderID): %d\n", isS);
    isS = glIsShader(fragmentShaderID);
    LOGI("glIsShader(fragmentShaderID): %d\n", isS);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
