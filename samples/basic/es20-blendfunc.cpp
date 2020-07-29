/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file blendfunc.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for blendfunc related API
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

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 0.3,
    0.0, 1.0, 0.0, 0.3,
    0.0, 0.0, 1.0, 0.3,
    0.0, 0.0, 0.0, 0.1
};

const GLubyte indices[] = {0,1,2};
static const GLfloat constant_color[4] = {0.25, 0.0, 1.0, 0.75};

static const GLenum factors[] = {
	GL_ZERO,
	GL_ONE,
	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA,
	GL_CONSTANT_COLOR,
	GL_ONE_MINUS_CONSTANT_COLOR,
	GL_CONSTANT_ALPHA,
	GL_ONE_MINUS_CONSTANT_ALPHA,
    GL_SRC_ALPHA_SATURATE,
};

void getdata() {
    GLboolean param;
    GLfloat paramf[4];
    GLint parami;

    glGetBooleanv(GL_BLEND, &param);
    LOGI("get(GL_BLEND): %d", param);
    glGetFloatv(GL_BLEND_COLOR, paramf);
    LOGI("get(GL_BLEND_COLOR): %f %f %f %f", paramf[0], paramf[1], paramf[2], paramf[3]);
    glGetIntegerv(GL_BLEND_DST_ALPHA, &parami);
    LOGI("get(GL_BLEND_DST_ALPHA): %d", parami);
    glGetIntegerv(GL_BLEND_DST_RGB, &parami);
    LOGI("get(GL_BLEND_DST_RGB): %d", parami);
    glGetIntegerv(GL_BLEND_SRC_ALPHA, &parami);
    LOGI("get(GL_BLEND_SRC_ALPHA): %d", parami);
    glGetIntegerv(GL_BLEND_SRC_RGB, &parami);
    LOGI("get(GL_BLEND_SRC_RGB): %d", parami);
}

bool setupGraphics(int width, int height, GLenum src_factor_rgb, GLenum dst_factor_rgb) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    if(glIsEnabled(GL_DEPTH_TEST))
	LOGI("IsEnable(GL_DEPTH_TEST)=true\n");

    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(src_factor_rgb, dst_factor_rgb));
    if(needs_blend_color(src_factor_rgb) || needs_blend_color(dst_factor_rgb)) {
        glBlendColor( constant_color[0], constant_color[1], constant_color[2], constant_color[3]);
    }
    getdata();

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

void Sample::test()
{
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        for(int j=0; j<ARRAY_NUM(factors); j++) {
            if (factors[j] != GL_SRC_ALPHA_SATURATE) {
                setupGraphics(WINDOW_W, WINDOW_H, factors[i], factors[j]);
                renderFrame();
                char ss[5];
                sprintf(ss, "_%d_%d", i, j);
                string src_name = get_blending_name(factors[i]);
                string dst_name = get_blending_name(factors[j]);
                string bmp_file = filename + "-" + ss + "-" + src_name + "-"
                                 + dst_name + ".bmp";
                LOGI("bmp_file=%s", bmp_file.c_str());
                save2bmp(bmp_file.c_str());
                Sample::SwapBuffers();
            }
        }
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
