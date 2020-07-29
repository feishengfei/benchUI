/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file clearbuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for clearbuffer related API
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

const int triangleColorsI[] = {
    1, 0, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1
};

const GLubyte indices[] = {0,1,2};
const GLubyte subdata[] = {1,3};

static const GLint vertices [] = {
        0, -2,
        -52, 32,
        0, 2,
        2, 0,
        15, 153,
        -2, 0
};

static const GLfloat color[] = {
        0.0, 1.0, 0.0,
        10.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 110.0, 0.0,
        0.0, 0.0, 1.0
};

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

string vertexShaderFilename = "ClearBuffer.vert";
string fragmentShaderFilename = "ClearBuffer.frag";

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
    string vertexShaderPath   = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    programID                 = GL_CHECK(glCreateProgram());
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

    GL_CHECK(glViewport(0, 0, width, height));
    GLint num = 0;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &num);
    printf("get GL_MAX_DRAW_BUFFERS = %d\n", num);
    return true;
}

void renderFrame(void) {
int tmp;
int tmpColor[4];
float tmpF;

GLint color[4]={0, 0, 1, 0};
glClearBufferiv(GL_COLOR, 0, color);
glGetIntegerv(GL_COLOR_CLEAR_VALUE, tmpColor);
LOGI("color: %d %d %d %d\n",tmpColor[0],tmpColor[1],tmpColor[2],tmpColor[3]);

GLint stencil=0;
glClearBufferiv(GL_STENCIL, 0, &stencil);
glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &tmp);
LOGI("stencil: %d\n",tmp);

float depth[]={1.0f};
glClearBufferfv(GL_DEPTH, 0, depth);
glGetFloatv(GL_DEPTH_CLEAR_VALUE, &tmpF);
LOGI("depth: %f\n",tmpF);

glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0, 0);
glGetFloatv(GL_DEPTH_CLEAR_VALUE, &tmpF);
LOGI("depth: %f  ",tmpF);
glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &tmp);
LOGI("stencil: %d\n",tmp);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0,
                                   triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    if(iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0,
                                       triangleColors));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);

    int ext_num=0;
    glGetIntegerv(GL_NUM_EXTENSIONS,&ext_num);
    LOGI("GL_NUM_EXTENSIONS=%d\n", ext_num);
    const GLubyte *version=(const GLubyte *)malloc(sizeof(GLubyte)*2);
    version = glGetStringi(GL_EXTENSIONS, 0);
    LOGI("GL_EXTENSIONS0:%s\n",(char *)version);

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