/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file teximagetype.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for teximagetype related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include <GL/freeglut.h>

using std::string;
using namespace BotsonSDK;

float vertexData[] = {
        -0.8, -0.8,  1.0, 0.0,
        0,    0,  0.0, 1.0,
        0,  0.8,  0.0, 0.0,
        0.8,  0.8,  1.0, 1.0,
        0.8,  0.2,  1.0, 2.0,
        0,  0.5,  2.0, 1.0
};

unsigned int indexData[] = {
        0, 1, 2, 3, 4, 5
};

GLuint m_vao, m_vbo, m_ebo, m_fbo, tex, rb;
GLuint programID = 0;
GLint max_integer_samples;
bool setupGraphics(int w, int h) {
    GL_CHECK(glGetIntegerv(GL_MAX_INTEGER_SAMPLES, &max_integer_samples));
    LOGI("MAX GL_MAX_INTEGER_SAMPLES IS %d\n", max_integer_samples);
    glutSetOption(GLUT_MULTISAMPLE, max_integer_samples);
    string vertexShaderPath = ((string)GLSL_PATH) + "texstorage2dms.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "texstorage2dms.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glGenVertexArrays(1, &m_vao));
    GL_CHECK(glBindVertexArray(m_vao));

    GL_CHECK(glGenBuffers(1, &m_vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*4, vertexData, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glGenBuffers(1, &m_ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*6, indexData, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0));



    GL_CHECK(glGenFramebuffers(1, &m_fbo));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
    GL_CHECK(glGenTextures(1, &tex));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex));
    GL_CHECK(glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, max_integer_samples, GL_RGB8, w, h, GL_TRUE));

    GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                    GL_TEXTURE_2D_MULTISAMPLE, tex, 0));

    GL_CHECK(glGenRenderbuffers(1, &rb));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, rb));
    GL_CHECK(glRenderbufferStorageMultisample(GL_RENDERBUFFER, max_integer_samples,
                                              GL_DEPTH_COMPONENT24, w, h));
    GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb));
    GL_CHECK(glUniform1i(0, max_integer_samples));
    GLenum drawbuffers[] = {GL_COLOR_ATTACHMENT0};
    GL_CHECK(glDrawBuffers(1, drawbuffers));
    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0));
    GL_CHECK(glClearDepthf(1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    return true;
}

void renderFrame(int w, int h) {
    GL_CHECK(glBindVertexArray(m_vao));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, rb));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

    GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo));
    GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
    GL_CHECK(glBlitFramebuffer(0, 0, w, h, 0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_NEAREST));
    GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
}

void clean_test(){
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0));

    GL_CHECK(glDeleteBuffers(1, &m_vbo));
    GL_CHECK(glDeleteBuffers(1, &m_ebo));
    GL_CHECK(glDeleteProgram(programID));
    GL_CHECK(glDeleteFramebuffers(1, &m_fbo));
    GL_CHECK(glDeleteRenderbuffers(1, &rb));
    GL_CHECK(glDeleteTextures(1, &tex));
    GL_CHECK(glDeleteVertexArrays(1, &m_vao));
}
void Sample::test() {
    glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    GL_CHECK(glEnable(GL_MULTISAMPLE));
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame(WINDOW_W, WINDOW_H);
    string bmp_file1 = filename + ".bmp";
    save2bmp(bmp_file1.c_str());
    SwapBuffers();
    clean_test();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
