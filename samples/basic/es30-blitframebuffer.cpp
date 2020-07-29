/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file blitframebuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for blitframebuffer related API
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

const GLenum attachments[2] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};

GLuint programObject;
GLuint fbo;
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

   glGetIntegerv ( GL_FRAMEBUFFER_BINDING, &defaultFramebuffer );
   glGenFramebuffers ( 1, &fbo );
   glBindFramebuffer ( GL_FRAMEBUFFER, fbo );
   textureHeight = textureWidth = 400;
   glGenTextures ( 4, &colorTexId[0] );
   
   for (i = 0; i < 4; ++i) {
      glBindTexture ( GL_TEXTURE_2D, colorTexId[i] );
      glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 
                     0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
      glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
      glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
      glFramebufferTexture2D ( GL_DRAW_FRAMEBUFFER, attachments[i], 
                               GL_TEXTURE_2D, colorTexId[i], 0 );
   }

   glDrawBuffers ( 4, attachments );

   if ( GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus ( GL_FRAMEBUFFER ) ) {
      return false;
   }
   glBindFramebuffer ( GL_FRAMEBUFFER, defaultFramebuffer );

   return true;
}

int Init ( ) {
   char vShaderStr[] =
      "#version 300 es                            \n"
      "layout(location = 0) in vec4 a_position;   \n"
      "void main()                                \n"
      "{                                          \n"
      "   gl_Position = a_position;               \n"
      "}                                          \n";

   char fShaderStr[] =
       "#version 300 es                                     \n"
       "precision mediump float;                            \n"
       "layout(location = 0) out vec4 fragData0;            \n"
       "layout(location = 1) out vec4 fragData1;            \n"
       "layout(location = 2) out vec4 fragData2;            \n"
       "layout(location = 3) out vec4 fragData3;            \n"
       "void main()                                         \n"
       "{                                                   \n"
       "  // first buffer will contain red color            \n"
       "  fragData0 = vec4 ( 1, 0, 0, 1 );                  \n"
       "                                                    \n"
       "  // second buffer will contain green color         \n"
       "  fragData1 = vec4 ( 0, 1, 0, 1 );                  \n"
       "                                                    \n"
       "  // third buffer will contain blue color           \n"
       "  fragData2 = vec4 ( 0, 0, 1, 1 );                  \n"
       "                                                    \n"
       "  // fourth buffer will contain gray color          \n"            
       "  fragData3 = vec4 ( 0.5, 0.5, 0.5, 1 );            \n"
       "}                                                   \n";

   programObject = Shader::createProgramFromString ( vShaderStr, fShaderStr );
   InitFBO ( );

   glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
   
   return true;
}
void DrawGeometry ( ) {
    GLfloat vVertices[] = {-1.0f, 1.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,
                           1.0f, -1.0f, 0.0f,
                           1.0f, 1.0f, 0.0f,
    };

    GLushort indices[] = {0, 1, 2, 0, 2, 3};

    glViewport(0, 0, WINDOW_W, WINDOW_H);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(GLfloat), vVertices);
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void BlitTextures (  ) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    GLenum statusRead = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
    LOGI("glCheckFramebufferStatus ( GL_READ_FRAMEBUFFER )=%x\n", statusRead);

    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glBlitFramebuffer(0, 0, textureWidth, textureHeight, 0, 0, WINDOW_W / 2,
                      WINDOW_H / 2, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glReadBuffer(GL_COLOR_ATTACHMENT1);
    glBlitFramebuffer(0, 0, textureWidth, textureHeight, WINDOW_W / 2, 0,
                      WINDOW_W, WINDOW_H / 2, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glReadBuffer(GL_COLOR_ATTACHMENT2);
    glBlitFramebuffer(0, 0, textureWidth, textureHeight, 0, WINDOW_H / 2,
                      WINDOW_W / 2, WINDOW_H, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    glReadBuffer(GL_COLOR_ATTACHMENT3);
    glBlitFramebuffer(0, 0, textureWidth, textureHeight, WINDOW_W / 2, WINDOW_H / 2,
                      WINDOW_W, WINDOW_H, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    GLint param;
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE=%d\n", param);
}

void renderFrame(void) {
    GLint defaultFramebuffer = 0;

    const GLenum attachments[4] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3
    };

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawBuffers(4, attachments);
    DrawGeometry();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, defaultFramebuffer);
    BlitTextures();

    const GLenum attachmentsinvalide[1] = {
            GL_COLOR_ATTACHMENT3
    };

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glDeleteTextures ( 4, colorTexId );
    glDeleteFramebuffers ( 1, &fbo );
    glDeleteProgram ( programObject );
}

void ShutDown () {
   glDeleteTextures ( 4, colorTexId );
   glDeleteFramebuffers ( 1, &fbo );
   glDeleteProgram ( programObject );
}

void Sample::test() {
    Init();
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
    ShutDown ();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

