/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file uniformuiv.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for uniformuiv related API
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
    GLuint       params[4];
    GLsizei      bufSize  = 10;
    GLsizei      length;
    GLint        size;
    GLenum       type;
    GLchar       name[10];
    GLenum       pname[]  = {
            GL_UNIFORM_TYPE,
            GL_UNIFORM_SIZE,
            GL_UNIFORM_NAME_LENGTH,
            GL_UNIFORM_BLOCK_INDEX,
            GL_UNIFORM_OFFSET,
            GL_UNIFORM_ARRAY_STRIDE,
            GL_UNIFORM_MATRIX_STRIDE,
            GL_UNIFORM_IS_ROW_MAJOR
    };
    GLuint       indices[4];
    GLint        paramsi[4];
    const GLchar *names[] = {"ui1", "ui2", "ui3", "ui4"};

    glGetUniformuiv(programID, ui4Loc, params);
    LOGI("glGetUniformuiv(ui4Loc)=%d\n", params[0], params[1], params[2], params[3]);
    glGetActiveUniform(programID, ui1Loc, bufSize, &length, &size, &type, name);
    LOGI("glGetActiveUniform(ui1Loc): length=%d, size=%d, type=%s, name=%s\n", length, size, get_enum_name(type), name);
    glGetUniformIndices(programID, 4, names, indices);

    for (int i = 0; i < ARRAY_NUM(pname); i++) {
        glGetActiveUniformsiv(programID, 4, indices, pname[i], paramsi);
        LOGI("glGetActiveUniformsiv(%s): %d, %d, %d, %d\n", get_enum_name(pname[i]),
             paramsi[0], paramsi[1], paramsi[2], paramsi[3]);
    }
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GLuint ui1v[] = {1};
    glUniform1uiv(ui1Loc, 1, ui1v);
    GLuint ui2v[] = {1, 1};
    glUniform2uiv(ui2Loc, 1, ui2v);
    GLuint ui3v[] = {1, 1, 1};
    glUniform3uiv(ui3Loc, 1, ui3v);
    GLuint ui4v[] = {1, 1, 1, 1};
    glUniform4uiv(ui4Loc, 1, ui4v);
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
