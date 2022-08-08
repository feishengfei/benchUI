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
    string vertexShaderPath   = ((string)GLSL_PATH) + "stencil.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "stencil.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
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
    GLuint ste[1] = {0};
    GL_CHECK(glClearBufferuiv(GL_STENCIL, 0, ste));
    glEnable(GL_STENCIL_TEST);

    return true;
}

void renderFrame(GLenum func, GLenum sfail1, GLenum dpfail1,
                 GLenum dppass1) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glStencilMask(0x00));
    GL_CHECK(glStencilFunc(func, 0x90, 0xff));
    GL_CHECK(glStencilOp(sfail1, dpfail1, dppass1));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices));
    GL_CHECK(glVertexAttrib3f(iLocFillColor, 0.3, 0.3, 0.3));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame(funcs[3], factors[0], factors[0],
                factors[1]);
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

