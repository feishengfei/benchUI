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


GLuint programID;;
GLuint fbo, crb, drb;
GLuint colorTexId[4];
GLsizei textureWidth;
GLsizei textureHeight;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

int InitFBO ( ) {
    int i;
    GLint defaultFramebuffer = 0;
    const GLenum attachments[4] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3
    };

    GL_CHECK(glGenFramebuffers ( 1, &fbo ));
    GL_CHECK(glBindFramebuffer ( GL_FRAMEBUFFER, fbo ));
    GL_CHECK(glGenRenderbuffers(1, &crb));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, crb));
    GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, WINDOW_W, WINDOW_H));
    GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, crb));
    GL_CHECK(glGenRenderbuffers(1, &drb));
    GL_CHECK(glBindRenderbuffer(GL_RENDERBUFFER, drb));
    GL_CHECK(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WINDOW_W, WINDOW_H));
    GL_CHECK(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, drb));

    textureHeight = textureWidth = 400;
    GL_CHECK(glGenTextures ( 4, &colorTexId[0] ));
    for (i = 0; i < 4; ++i) {
        glBindTexture ( GL_TEXTURE_2D, colorTexId[i] );
        glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight,
                       0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glFramebufferTexture2D ( GL_DRAW_FRAMEBUFFER, attachments[i],
                                 GL_TEXTURE_2D, colorTexId[i], 0 );
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

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);

    programID  = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glViewport(0, 0, width, height));
    InitFBO ( );
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    return true;
}


void DrawGeometry ( ) {
    GLfloat vVertices[] = {
            -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
    };

    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    GL_CHECK(glViewport ( 0, 0, WINDOW_W, WINDOW_H ));
    GL_CHECK(glClear ( GL_COLOR_BUFFER_BIT ));
    GL_CHECK(glUseProgram ( programID));
    GL_CHECK(glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, vVertices ));
    GL_CHECK(glEnableVertexAttribArray ( 0 ));
    GL_CHECK(glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices ));
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
    GL_CHECK(glInvalidateFramebuffer(GL_DRAW_FRAMEBUFFER, 1, attachmentsinvalide));
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
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    ShutDown();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

