/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file drawelements.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for drawelements related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint buffer[2];

float points[] = {
	-0.7, 0.8, 0.0,
	-0.8, 0.7, 0.0,
	-0.9, 0.5, 0.0,
	-0.5, 0.8, 0.0,
	-0.5, 0.6, 0.0,
	-0.4, 0.8, 0.0
};

float Lstrip[] = {
	0.5, 0.6, 0.0,
	0.6, 0.7, 0.0,
	0.5, 0.3, 0.0,
	0.8, 0.2, 0.0,
	0.9, 0.5, 0.0
};

float Lloop[] = {
	0.0, 0.4, 0.0,
	0.0, 0.5, 0.0,
	0.1, 0.6, 0.0,
	0.1, 0.1, 0.0,
	-0.2, 0.2, 0.0,
	-0.1, 0.4, 0.0
};

float Tfan[] = {
	-0.6, -0.3, 0.0,
	-0.8, -0.2, 0.0,
	-0.7, -0.7, 0.0,
	-0.5, -0.6, 0.0,
	-0.2, -0.3, 0.0
};

float Tstrip[] = {
	0.2, -0.2, 0.0,
	0.3, -0.3, 0.0,
	0.1, -0.5, 0.0,
	0.4, -0.5, 0.0,
	0.3, -0.7, 0.0,
	0.5, -0.8, 0.0
};

const GLubyte indices1[] = {0,1,2,3,4,5};
const GLubyte indices2[] = {0,1,2,3,4};
const GLubyte indices3[] = {0,1,2,3,4,5};
const GLubyte indices4[] = {0,1,2,3,4};
const GLubyte indices5[] = {0,1,2,3,4,5};

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "base-green.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "base-green.frag";

    GLuint vertexShaderID = 0;
    GLuint fragmentShaderID = 0;

    GL_CHECK(glEnable(GL_DEPTH_TEST));

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
    iLocPosition = glGetAttribLocation(programID, "a_v4Position");

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));

    return true;
}

void renderFrame(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    glEnableVertexAttribArray(iLocPosition);

    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, points);
    glDrawElements(GL_POINTS, 6, GL_UNSIGNED_BYTE, indices1);

    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Lstrip);
    glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_BYTE, indices2);

    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Lloop);
    glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_BYTE, indices3);

    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Tfan);
    glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_BYTE, indices4);

    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Tstrip);
    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_BYTE, indices5);
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
