/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file drawrangeelements.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for drawrangeelements related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "DrawRangeElements.vert";
string fragmentShaderFilename = "DrawRangeElements.frag";

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

const GLubyte indices[] = {0,1,2};

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;

void print_get(GLenum pname) {
	GLint tmp;

	glGetIntegerv(pname, &tmp);
	LOGI("%d\n",tmp);
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

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

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    LOGE("glGetAttribLocation(\"a_v4Position\") = %d\n", iLocPosition);

    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));
    LOGE("glGetAttribLocation(\"a_v4FillColor\") = %d\n", iLocFillColor);

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0,
                                   triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if (iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0,
                                       triangleColors));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }
    GL_CHECK(glDrawRangeElements(GL_TRIANGLES, 0, 2, 3, GL_UNSIGNED_BYTE, indices));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    LOGI("GL_MAX_ELEMENTS_VERTICES:");
    print_get(GL_MAX_ELEMENTS_VERTICES);
    LOGI("GL_MAX_ELEMENTS_INDICES:");
    print_get(GL_MAX_ELEMENTS_INDICES);
    LOGI("GL_MAX_ELEMENT_INDEX:");
    print_get(GL_MAX_ELEMENT_INDEX);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
