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

GLfloat triangleVertices[] = {
        0.35f, 0.5f, 0.0f, 1.0f,
        -0.5f,-0.25f,0.0f, 1.0f,
        0.5f, -0.25f,0.0f, 1.0f,
        -0.35f,0.5f, 0.0f, 1.0f,
        0.0f, -0.75f,0.0f, 1.0f
};

GLfloat triangleColors[]={
        0.8f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.8f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.8f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,
        0.2f, 0.2f, 0.2f, 1.0f
};

GLuint vpos_obj, vcol_obj, vao, fb, tex, programID, vs, fs, rb;

bool setupGraphics(int w, int h, int sampleNum) {
    glutSetOption(GLUT_MULTISAMPLE, sampleNum);
    string vertexShaderPath = ((string)GLSL_PATH) + "texstorage3dms.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "texstorage3dms.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));

    GL_CHECK(glGenBuffers(1, &vpos_obj));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vpos_obj));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL));

    GL_CHECK(glGenBuffers(1, &vcol_obj));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vcol_obj));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleColors), triangleColors, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL));

    GLint max_samples;
    GL_CHECK(glGetIntegerv(GL_MAX_SAMPLES, &max_samples));
    LOGI("MAX SAMPLES IS %d\n", max_samples);

    GL_CHECK(glGenFramebuffers(1, &fb));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fb));
    GL_CHECK(glGenTextures(1, &tex));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, tex));
    GL_CHECK(glTexStorage3DMultisample(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, sampleNum, GL_RGBA8, w, h, 1, GL_TRUE));
    GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0));

    GL_CHECK(glGenRenderbuffers(1, &rb));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, rb));
    GL_CHECK(glRenderbufferStorageMultisample(GL_RENDERBUFFER, sampleNum, GL_RGBA8, w, h));
    GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rb));

    GLenum status=glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE){
        LOGE("FRAMEBUFFER NOT COMPLETE");
    }

    GLint diffuseLoc = glGetUniformLocation(programID, "diffuse");
    LOGI("diffuse location = %d\n", diffuseLoc);
    GL_CHECK(glUniform1i(diffuseLoc, 1));

    GLint nMsLoc = GL_CHECK(glGetUniformLocation(programID, "nMultiSample"));
    LOGI("nMultiSample location = %d\n", nMsLoc);
    GL_CHECK(glUniform1i(nMsLoc, sampleNum));

    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0));
    GL_CHECK(glClearDepthf(1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    return true;
}

void renderFrame(int w, int h) {

    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, tex));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fb));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, rb));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDrawArrays(GL_LINE_LOOP, 0, 5));

    GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, fb));
    GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
    GL_CHECK(glBlitFramebuffer(0, 0, w, h, 0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_NEAREST));
    GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
}

void clean_test(){
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 0));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, 0));

    GL_CHECK(glDeleteBuffers(1, &vpos_obj));
    GL_CHECK(glDeleteBuffers(1, &vcol_obj));
    GL_CHECK(glDeleteProgram(programID));
    GL_CHECK(glDeleteFramebuffers(1, &fb));
    GL_CHECK(glDeleteRenderbuffers(1, &rb));
    GL_CHECK(glDeleteTextures(1, &tex));
    GL_CHECK(glDeleteVertexArrays(1, &vao));
}
void Sample::test() {
    glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    GL_CHECK(glEnable(GL_MULTISAMPLE));
    setupGraphics(WINDOW_W, WINDOW_H, 4);
    renderFrame(WINDOW_W, WINDOW_H);
    string bmp_file = filename + ".bmp";
    save2bmp(bmp_file.c_str());
    SwapBuffers();
    clean_test();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_ALPHA | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
