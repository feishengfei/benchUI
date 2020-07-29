/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file triangle-uniform.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for triangle-uniform related API
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

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "triangleuniform.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "triangleuniform.frag";

    GLuint vertexShaderID   = 0;
    GLuint fragmentShaderID = 0;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);

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
    GLint iLocu1f = glGetUniformLocation(programID, "u1f");
    glUniform1f(iLocu1f, 0.1);
    GLint   iLocu1fv = glGetUniformLocation(programID, "u1fv");
    GLfloat u1fv[1]  = {0.1};
    glUniform1fv(iLocu1fv, 1, u1fv);
    GLint iLocu2f = glGetUniformLocation(programID, "u2f");
    glUniform2f(iLocu2f, 0.1, 0.1);
    GLint   iLocu2fv = glGetUniformLocation(programID, "u2fv");
    GLfloat u2fv[2]  = {0.1, 0.1};
    glUniform2fv(iLocu2fv, 1, u2fv);
    GLint iLocu3f = glGetUniformLocation(programID, "u3f");
    glUniform3f(iLocu3f, 0.1, 0.1, 0.1);
    GLint   iLocu3fv = glGetUniformLocation(programID, "u3fv");
    GLfloat u3fv[3]  = {0.1, 0.1, 0.1};
    glUniform3fv(iLocu3fv, 1, u3fv);
    GLint iLocu4f = glGetUniformLocation(programID, "u4f");
    glUniform4f(iLocu4f, 0.1, 0.1, 0.1, 0.1);
    GLint   iLocu4fv = glGetUniformLocation(programID, "u4fv");
    GLfloat u4fv[4]  = {0.1, 0.1, 0.1, 0.1};
    glUniform4fv(iLocu4fv, 1, u4fv);
    GLint   iLocmat2f = glGetUniformLocation(programID, "mat2f");
    GLfloat mat2f[4]  = {-0.1, -0.2, 0.0, 1.0};
    glUniformMatrix2fv(iLocmat2f, 1, GL_FALSE, mat2f);

    GLint   iLocmat3f = glGetUniformLocation(programID, "mat3f");
    GLfloat mat3f[9]  = {1.0, 0.0, 0.0,
                         0.0, 1.0, 0.0,
                         0.0, 0.0, 1.0};
    glUniformMatrix3fv(iLocmat3f, 1, GL_FALSE, mat3f);

    GLint iLocu1i = glGetUniformLocation(programID, "u1i");
    glUniform1i(iLocu1i, 1);
    GLint iLocu1iv = glGetUniformLocation(programID, "u1iv");
    GLint u1iv[1]  = {1};
    glUniform1iv(iLocu1iv, 1, u1iv);
    GLint iLocu2i = glGetUniformLocation(programID, "u2i");
    glUniform2i(iLocu2i, 1, 1);
    GLint iLocu2iv = glGetUniformLocation(programID, "u2iv");
    GLint u2iv[2]  = {1, 1};
    glUniform2iv(iLocu2iv, 1, u2iv);
    GLint iLocu3i = glGetUniformLocation(programID, "u3i");
    glUniform3i(iLocu3i, 1, 1, 1);
    GLint iLocu3iv = glGetUniformLocation(programID, "u3iv");
    GLint u3iv[3]  = {1, 1, 1};
    glUniform3iv(iLocu3iv, 1, u3iv);
    GLint iLocu4i = glGetUniformLocation(programID, "u4i");
    glUniform4i(iLocu4i, 1, 1, 1, 1);
    GLint iLocu4iv = glGetUniformLocation(programID, "u4iv");
    GLint u4iv[4]  = {1, 1, 1, 1};
    glUniform4iv(iLocu4iv, 1, u4iv);
    GLint params[4];
    glGetUniformiv(programID, iLocu4iv, params);
    LOGI("glGetUniformiv: %d, %d, %d, %d\n", params[0], params[1], params[2], params[3]);
    GL_CHECK(glViewport(0, 0, width, height));

    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));
    GL_CHECK(glClearDepthf(1.0f));
    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0,
                                   triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
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
