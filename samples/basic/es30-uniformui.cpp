/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file uniformui.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for uniformui related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "uniformui.vert";
string fragmentShaderFilename = "uniformui.frag";

GLfloat Vertices[] = {
	0.0, 0.5, 0.0, 1.0,
	-0.5, -0.5, 0.0, 1.0,
	0.5, -0.5, 0.0, 1.0,
};

GLuint programID;
GLint ui1Loc, ui2Loc, ui3Loc, ui4Loc;
GLint iLocPosition;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
            fragmentShaderPath.c_str());

    ui1Loc = glGetUniformLocation(programID, "ui1");
    ui2Loc = glGetUniformLocation(programID, "ui2");
    ui3Loc = glGetUniformLocation(programID, "ui3");
    ui4Loc = glGetUniformLocation(programID, "ui4");
    iLocPosition = glGetAttribLocation(programID, "a_v4Position");

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    return true;
}

void getdata() {
    GLuint params[4];
    GLsizei bufSize = 10;
    GLsizei length;
    GLint size;
    GLenum type;
    GLchar name[10];

    glGetUniformuiv(programID, ui4Loc, params);
    LOGI("glGetUniformuiv(ui4Loc)=%d\n", params[0], params[1], params[2], params[3]);
    glGetActiveUniform(programID, ui1Loc, bufSize, &length, &size, &type, name);
    LOGI("glGetActiveUniform(ui1Loc): length=%d, size=%d, type=%s, name=%s\n", length, size, get_enum_name(type), name);
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    glUniform1ui(ui1Loc, 1);
    glUniform2ui(ui2Loc, 1, 1);
    glUniform3ui(ui3Loc, 1, 1, 1);
    glUniform4ui(ui4Loc, 1, 1, 1, 1);
    GL_CHECK(glVertexAttribPointer(iLocPosition, 4, GL_FLOAT, GL_FALSE, 0, Vertices));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    getdata();
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
