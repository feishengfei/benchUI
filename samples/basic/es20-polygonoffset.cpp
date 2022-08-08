/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file polygonoffset.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for polygonoffset related API
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
    glEnable(GL_DEPTH_TEST);
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
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

    iLocPosition = glGetAttribLocation(programID, "a_v4Position");
    iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor");
    GLint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    return true;
}

void renderFrame(void) {
    GLfloat polyfactor = -1.0;
    GLfloat polyunits = -1.0;

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(polyfactor, polyunits);
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if(iLocFillColor != -1) {
	glVertexAttrib4f(iLocFillColor, 0.0, 0.0, 1.0, 1.0);
    }

    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
    glDisable(GL_POLYGON_OFFSET_FILL);
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVerticesLittle));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if(iLocFillColor != -1) {
	glVertexAttrib4f(iLocFillColor, 1.0, 0.0, 0.0, 1.0);
    }

    GL_CHECK(glDrawArrays(GL_LINE_LOOP, 0, 3));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
