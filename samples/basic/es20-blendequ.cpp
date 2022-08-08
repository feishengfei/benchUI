/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file blendequ.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for blendequ related API
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
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 0.3,
    0.0, 1.0, 0.0, 0.3,
    0.0, 0.0, 1.0, 0.3,
};

static const GLenum factors[] = {
	GL_FUNC_ADD,
	GL_FUNC_SUBTRACT,
	GL_FUNC_REVERSE_SUBTRACT
};

GLuint programID;
GLuint iLocPosition;
GLuint iLocFillColor ;
GLint iLocProjection;

bool setupGraphics(int width, int height, GLenum mode) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    if(glIsEnabled(GL_DEPTH_TEST))
	  LOGI("IsEnable(GL_DEPTH_TEST)=true\n");

    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_COLOR,GL_SRC_ALPHA));
    GL_CHECK(glBlendEquation(mode));

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    if(iLocPosition == -1) {
        LOGE("Attribute not found at %s:%i\n", __FILE__, __LINE__);
        return false;
    }
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    iLocFillColor = GL_CHECK(glGetAttribLocation(programID, "a_v4FillColor"));
    if(iLocFillColor == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
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

    GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors));

    GL_CHECK(glEnableVertexAttribArray(iLocFillColor));

    iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
      GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        setupGraphics(WINDOW_W, WINDOW_H,factors[i]);
        renderFrame();
        string mode_name=get_enum_name(factors[i]);
        string bmp_file=filename+"-"+mode_name+".bmp";
        LOGI("bmp_file=%s",bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
