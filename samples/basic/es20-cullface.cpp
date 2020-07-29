/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file cullface.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for cullface related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0
};

const GLubyte indices[] = {0,1,2};

GLenum culls[] = {GL_FRONT, GL_BACK, GL_FRONT_AND_BACK};
GLenum fronts[] = {GL_CW, GL_CCW};

bool setupGraphics(int width, int height, GLenum cull, GLenum front) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    GLuint vertexShaderID = 0;
    GLuint fragmentShaderID = 0;

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
    LOGI("glGetAttribLocation(\"a_v4Position\") = %d\n", iLocPosition);

    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));
    LOGI("glGetAttribLocation(\"a_v4FillColor\") = %d\n", iLocFillColor);

    GLint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else
    {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glViewport(0, 0, width, height));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(front);
    glCullFace(cull);
    GL_CHECK(glClearColor(0.4f, 0.2f, 0.7f, 0.5f));
    GLfloat paramf[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, paramf);
    LOGI("get(GL_COLOR_CLEAR_VALUE): %f %f %f %f", paramf[0], paramf[1], paramf[2],
         paramf[3]);
    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0,
                                   triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if(iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    for(int i=0; i<ARRAY_NUM(culls); i++) {
        for(int j=0; j<ARRAY_NUM(fronts); j++) {
            setupGraphics(WINDOW_W, WINDOW_H, culls[i], fronts[j]);
            renderFrame();
            string cull_name = get_enum_name(culls[i]);
            string front_name = get_enum_name(fronts[j]);
            string bmp_file = filename + "-" + cull_name + "-" + front_name + ".bmp";
            LOGI("bmp_file=%s", bmp_file.c_str());
            save2bmp(bmp_file.c_str());
            Sample::SwapBuffers();
        }
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

