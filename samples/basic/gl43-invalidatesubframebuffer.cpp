/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file invalidateframebuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for invalidateframebuffer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID, VAOs, Buffers;
GLuint fbo, crb, drb, fbog;
GLuint colorTexId[4];
GLsizei textureWidth;
GLsizei textureHeight;

int InitFBO ( ) {
    int i;
    GLint defaultFramebuffer = 0;
    const GLenum attachments[4] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3
    };

    GL_CHECK(glGenFramebuffers(1, &fbo));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
    LOGI("FRAMEBUFFER = %d\n", glIsFramebuffer(fbo));
    GL_CHECK(glGenRenderbuffers(1, &crb));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, crb));
    LOGI("RENDERBUFFER = %d\n", glIsRenderbuffer(crb));
    GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, WINDOW_W, WINDOW_H));
    GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, crb));
    GL_CHECK(glGenRenderbuffers(1, &drb));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, drb));
    GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WINDOW_W, WINDOW_H));
    GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, drb));

    textureHeight = textureWidth = 400;
    glGenTextures ( 4, &colorTexId[0] );
    for (i = 0; i < 4; ++i) {
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, colorTexId[i]));
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight,
                       0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GL_CHECK(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachments[i],
                                 GL_TEXTURE_2D, colorTexId[i], 0));
    }

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        LOGE("FAIL  %s is incomplete\n", status);
        return false;
    }

    return true;
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "basic.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
                                               fragmentShaderPath.c_str()));
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GLint tmp;
    glGetProgramiv(programID, GL_LINK_STATUS, &tmp);
    LOGI("glGetProgramiv(GL_LINK_STATUS) status=%d\n", tmp);

    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glViewport(0, 0, width, height));
    InitFBO ( );
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    return true;
}


void DrawGeometry ( ) {
    GLfloat vertices[] = {
            -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
    };

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));

    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    GL_CHECK(glViewport( 0, 0, WINDOW_W, WINDOW_H ));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices));
}

void BlitTextures (  ) {
    GL_CHECK(glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo));
    GL_CHECK(glReadBuffer(GL_COLOR_ATTACHMENT0));
    GL_CHECK(glBlitFramebuffer(0, 0, textureWidth, textureHeight, 0, 0, WINDOW_W / 2,
                               WINDOW_H / 2, GL_COLOR_BUFFER_BIT, GL_LINEAR));
    GL_CHECK(glReadBuffer(GL_COLOR_ATTACHMENT1));
    GL_CHECK(glBlitFramebuffer(0, 0, textureWidth, textureHeight, WINDOW_W / 2, 0, WINDOW_W,
                               WINDOW_H / 2, GL_COLOR_BUFFER_BIT, GL_LINEAR));
    GL_CHECK(glReadBuffer(GL_COLOR_ATTACHMENT2));
    GL_CHECK(glBlitFramebuffer(0, 0, textureWidth, textureHeight, 0, WINDOW_H / 2, WINDOW_W / 2,
                               WINDOW_H, GL_COLOR_BUFFER_BIT, GL_LINEAR));
}

void renderFrame(void) {
    GLint        defaultFramebuffer = 0;
    const GLenum attachments[4]     = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3
    };

    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    const GLenum attachmentsinvalide[1] = {GL_DEPTH_ATTACHMENT};
    GL_CHECK(glInvalidateSubFramebuffer(GL_READ_FRAMEBUFFER, 1, attachmentsinvalide, 50, 50,
                               WINDOW_W/2, WINDOW_H/2));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, crb));
    GL_CHECK(glDrawBuffers(4, attachments));
    DrawGeometry();
    GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFramebuffer));
    BlitTextures();

}

void ShutDown () {
    glDeleteTextures ( 4, colorTexId );
    glDeleteFramebuffers ( 1, &fbo );
    glDeleteFramebuffers ( 1, &crb );
    glDeleteFramebuffers ( 1, &drb );
    glDeleteProgram ( programID );
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s\n", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();

    ShutDown();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

