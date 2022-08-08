/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file stencilsep.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for stencilsep related API
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
    0.0, 0.0, 1.0, 1.0,
};

GLenum funcs[] = {
	GL_NEVER,
	GL_LESS,
	GL_LEQUAL,
	GL_GREATER,
	GL_GEQUAL,
	GL_EQUAL,
	GL_NOTEQUAL,
	GL_ALWAYS
};

GLenum faces[]={
	GL_FRONT,
	GL_BACK,
	GL_FRONT_AND_BACK
};

GLenum factors[]={
GL_KEEP,
GL_ZERO,
GL_REPLACE,
GL_INCR,
GL_INCR_WRAP,
GL_DECR,
GL_DECR_WRAP,
GL_INVERT
};

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint buffers[2];

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "basic.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    GLuint vertexShaderID   = 0;
    GLuint fragmentShaderID = 0;

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition  = glGetAttribLocation(programID, "a_v4Position");
    iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor");
    GLint  iLocProjection     = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if (iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.5f));
    GL_CHECK(glClearDepthf(1.0f));
    glClearStencil(0x00);
    glEnable(GL_STENCIL_TEST);

    return true;
}

void renderFrame(GLenum func, GLenum sfail1, GLenum dpfail1,
                 GLenum dppass1) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    glStencilMask(0x00);
    glStencilFunc(func, 0x90, 0xff);
    glStencilOp(sfail1, dpfail1, dppass1);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices);
    glVertexAttrib3f(iLocFillColor, 0.3, 0.3, 0.3);
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);

    for (int i = 0; i < ARRAY_NUM(factors); i++) {
        for (int j = 0; j < ARRAY_NUM(factors); j++) {
            for (int k = 0; k < ARRAY_NUM(factors); k++) {
                for (int l = 0; l < ARRAY_NUM(funcs); l++) {
                    renderFrame(funcs[l], factors[i], factors[j],
                                factors[k]);
                    char ss[12];
                    sprintf(ss, "_%d_%d_%d_%d_%d", l, i, j, k);
                    string func_name    = get_enum_name(funcs[l]);
                    string sfail1_name  = get_enum_name(factors[i]);
                    string dpfail1_name = get_enum_name(factors[j]);
                    string dppass1_name = get_enum_name(factors[k]);
                    string bmp_file     = filename + "-" + ss + func_name +
                                          sfail1_name + dpfail1_name + dppass1_name + ".bmp";
                    LOGI("bmp_file=%s", bmp_file.c_str());
                    save2bmp(bmp_file.c_str());
                    Sample::SwapBuffers();
                }
            }
        }
    }
}


int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

