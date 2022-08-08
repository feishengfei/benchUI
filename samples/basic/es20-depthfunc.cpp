/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file depthfunc.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for depthfunc related API
 * @par TestPoints:
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

const float triangleVertices1[] = {
    -0.5f, -0.5f, 0.4f,
     0.5f, -0.5f, 0.4f,
     0.0f,  0.5f, 0.4f
};

const float triangleVertices2[] = {
    -0.5f,  0.5f, 0.6f,
     0.5f,  0.5f, 0.6f,
     0.0f, -0.5f, 0.6f
};

const float triangleColors1[] = {
    1.0, 1.0, 1.0, 0.1,
    1.0, 1.0, 1.0, 0.1,
    1.0, 1.0, 1.0, 0.1
};

const float triangleColors2[] = {
    1.0, 0.0, 0.0, 0.1,
    0.0, 1.0, 0.0, 0.1,
    0.0, 0.0, 1.0, 0.1
};

GLenum funcs[] = {
	GL_NEVER,
	GL_LESS,
	GL_EQUAL,
	GL_LEQUAL,
	GL_GREATER,
	GL_NOTEQUAL,
	GL_GEQUAL,
	GL_ALWAYS,
};


bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

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

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));
  // GLint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
  // if(iLocProjection == -1) {
  //     LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
  // } else {
  //     GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
  // }

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    glClearDepthf(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);

    return true;
}

void renderFrame(GLenum func) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices1));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    if(iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors1));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    glDepthFunc(func);

    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices2));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    if(iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors2));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    for(int i=0; i<ARRAY_NUM(funcs); i++) {
        setupGraphics(WINDOW_W, WINDOW_H);
        renderFrame(funcs[i]);
        string funcs_name = get_enum_name(funcs[i]);
        string bmp_file   = filename + "-" + funcs_name + ".bmp";
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
