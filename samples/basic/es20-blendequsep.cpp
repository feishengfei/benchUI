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

using std::string;
using namespace BotsonSDK;

GLuint programID;
GLuint iLocPosition;
GLuint iLocFillColor;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
};

const float triangleColors[] = {
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

void getdata() {
    GLboolean param;
    GLint parami;

    glGetBooleanv(GL_BLEND, &param);
    LOGI("get(GL_BLEND): %d", param);
    glGetIntegerv(GL_BLEND_EQUATION_RGB, &parami);
    LOGI("get(GL_BLEND_EQUATION_RGB): %d", parami);
    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &parami);
    LOGI("get(GL_BLEND_EQUATION_ALPHA): %d", parami);
}

bool setupGraphics(int width, int height, GLenum mode_rgb, GLenum mode_a) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    if(glIsEnabled(GL_DEPTH_TEST))
	LOGI("IsEnable(GL_DEPTH_TEST)=true\n");

    GL_CHECK(glEnable(GL_BLEND));
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquationSeparate(mode_rgb, mode_a);
    getdata();

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);

    programID = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));
    GLint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glViewport(0, 0, width, height));

    GL_CHECK(glClearColor(0.3f, 0.3f, 0.3f, 0.7f));

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
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
