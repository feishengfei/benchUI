/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file vertexattribi.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for vertexattribi related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "VertexAttribI.vert";
string fragmentShaderFilename = "VertexAttribI.frag";

const float Vertices[] = {
	-0.4, 0.7, 0.0,  0.4, 0.7, 0.0,
	-0.4, 0.5, 0.0,  0.4, 0.5, 0.0,
	-0.4, 0.3, 0.0,  0.4, 0.3, 0.0,
	-0.4, 0.1, 0.0,  0.4, 0.1, 0.0,
	-0.4,-0.1, 0.0,  0.4,-0.1, 0.0,
	-0.4,-0.3, 0.0,  0.4,-0.3, 0.0,
	-0.4,-0.5, 0.0,  0.4,-0.5, 0.0,
	-0.4,-0.7, 0.0,  0.4,-0.7, 0.0
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

const GLubyte indices1[] = {0,1};
const GLushort indices2[] = {2,3};
const GLuint indices3[] = {4,5};
const GLubyte indices4[] = {6,7};
const GLubyte indices5[] = {8,9};
const GLubyte indices6[] = {10,11};
const GLubyte indices7[] = {12,13};
const GLubyte indices8[] = {14,15};

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
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLint Attr_i, Attr_u;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(),
                          GL_FRAGMENT_SHADER);
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
    Attr_i = glGetAttribLocation(programID, "attr_i");
    Attr_u = glGetAttribLocation(programID, "attr_u");

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Vertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if (iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE,
                                       0, triangleColors));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }

    glVertexAttribI4i(Attr_i, 0, 1, 0, 0);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices4);
    glVertexAttribI4ui(Attr_u, 1, 1, 0, 0);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices5);
    GLint colori[] = {0, 0, 1, 0};
    glVertexAttribI4iv(Attr_i, colori);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices6);
    GLuint colorui[] = {0, 1, 0, 0};
    glVertexAttribI4uiv(Attr_u, colorui);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices7);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    GLint size;
    GLint tmp[4];
    GLuint utmp[4];
    glGetVertexAttribIiv(Attr_i, GL_CURRENT_VERTEX_ATTRIB, tmp);
    LOGI("glGetVertexAttribIiv(GL_CURRENT_VERTEX_ATTRIB):%f,%f,%f,%f\n",
         tmp[0],tmp[1],tmp[2],tmp[3]);
    glGetVertexAttribIuiv(Attr_u, GL_CURRENT_VERTEX_ATTRIB, utmp);
    LOGI("glGetVertexAttribIuiv:%f,%f,%f,%f\n",utmp[0],utmp[1],utmp[2],utmp[3]);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
