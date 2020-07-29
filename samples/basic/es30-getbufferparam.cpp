/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file getbufferparam.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for getbufferparam related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "GetInternalformat.vert";
string fragmentShaderFilename = "GetInternalformat.frag";

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint buffers[2];
GLuint vao;

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f,-0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f
};

const float triangleColors[] = {
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0
};

void print_get(GLenum pname) {
	GLint tmp;

	glGetIntegerv(pname, &tmp);
	LOGI("%d\n",tmp);
}

void getInterfmt() {
   GLint param;
   GLenum interfmts[] = {
      GL_RGBA16F,
      GL_R32F,
      GL_RG32F,
      GL_RGBA32F
   };

   for(int i=0; i<ARRAY_NUM(interfmts); i++) {
      glGetInternalformativ(GL_RENDERBUFFER,interfmts[i],GL_NUM_SAMPLE_COUNTS,1,&param);
      LOGI("GetInternalformativ(%s,GL_NUM_SAMPLE_COUNTS):%d\n", get_enum_name(interfmts[i]), param);
   }
   for(int i=0; i<ARRAY_NUM(interfmts); i++) {
      glGetInternalformativ(GL_RENDERBUFFER,interfmts[i],GL_SAMPLES,1,&param);
      LOGI("GetInternalformativ(%s,GL_SAMPLES):%d\n", get_enum_name(interfmts[i]), param);
   }
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;
    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));
    LOGI("iLoc: pos=%d, color=%d\n", iLocPosition, iLocFillColor);

    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(iLocPosition);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleColors), triangleColors, GL_STATIC_DRAW);
    glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(iLocFillColor);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glCopyBufferSubData(GL_ARRAY_BUFFER, GL_ARRAY_BUFFER, 0, sizeof(triangleVertices) / 2,
                        sizeof(triangleVertices) / 2);
    GLenum err = glGetError();
    LOGE("err=0x%x\n", err);

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));
    getInterfmt();
    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    glBindVertexArray(vao);
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
    char name[50];
    glGetFragDataLocation(programID, name);
    LOGI("glGetFragDataLocation:%s\n", name);
    glGenVertexArrays(1, &vao);
    glDeleteBuffers(2, buffers);
    glDeleteVertexArrays(1, &vao);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
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
