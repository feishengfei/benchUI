/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file blitstencil.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for blitstencil related API
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

const GLenum attachments[2] = {
      GL_COLOR_ATTACHMENT0,
      GL_DEPTH_ATTACHMENT
};

GLuint mask;
GLuint programObject;
GLuint fb, rb, depthrb, stencilrb;
GLuint texture;
GLenum status;
GLsizei textureWidth;
GLsizei textureHeight;

int InitFBO ( ) {
    int   i;
    GLint defaultFramebuffer = 0;

    const GLenum attachments[4] = {
            GL_COLOR_ATTACHMENT0,
            GL_COLOR_ATTACHMENT1,
            GL_COLOR_ATTACHMENT2,
            GL_COLOR_ATTACHMENT3
    };

    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_W, WINDOW_H, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachments[i], GL_TEXTURE_2D,
                           texture, 0);
    glGenRenderbuffers(1, &stencilrb);
    glBindRenderbuffer(GL_RENDERBUFFER, stencilrb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WINDOW_W, WINDOW_H);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, stencilrb);
    glViewport(0, 0, WINDOW_W, WINDOW_H);

    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FBO incomplete status 0x%X\n", status);
    } else {
        printf("frame buffer status OK!\n");
    }
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
       "out vec4 fragColor;            \n"
       "void main()                                         \n"
       "{                                                   \n"
       "  fragColor = vec4 ( 1, 0, 0, 1 );                  \n"
       "}                                                   \n";

   programObject = Shader::createProgramFromString ( vShaderStr, fShaderStr );
   InitFBO ( );
   glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );

   return true;
}

void draw_rect(int x, int y, int h, int w) {
   GLint vVertices[] = { x,  y, 0,
                         x+w, y, 0,
                         x+w, y+h, 0,
                         x, y+h, 0
                         };
   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

   glUseProgram ( programObject );
   glVertexAttribPointer ( 0, 3, GL_FLOAT, false, 3 * sizeof ( GLfloat ), vVertices );
   glEnableVertexAttribArray ( 0 );
   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
}

void compare_stencil(void) {
    int      x, y, failures = 0;
    GLushort stencil[WINDOW_W * WINDOW_H];
    GLushort expected;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, WINDOW_W, WINDOW_H, GL_STENCIL_INDEX8, GL_UNSIGNED_SHORT, stencil);

    for (y = 0; y < WINDOW_W; y++) {
        for (x = 0; x < WINDOW_H; x++) {
            if (x == WINDOW_H / 2 || y == WINDOW_W / 2)
                continue;

            if (y < WINDOW_W / 2)
                expected = (x < WINDOW_H / 2 ? 0x3333 : 0x6666) & mask;
            else
                expected = (x < WINDOW_H / 2 ? 0x9999 : 0xbbbb) & mask;

            if (stencil[y * WINDOW_H + x] != expected) {
                failures++;
                if (failures < 20) {
                    printf("Stencil at %i,%i   Expected: 0x%02x   Observed: 0x%02x\n",
                           x, y, expected, stencil[y * WINDOW_H + x]);
                } else if (failures == 20) {
                    printf("...\n");
                }
            }
        }
    }
    if (failures)
        printf("Total failures: %i\n", failures);
}

void test_copy(void) {
	glClearStencil(0xfefe);
	glClear(GL_STENCIL_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 0x3333 & mask, ~0);
	draw_rect(0, 0, 1, 1);
	glBlitFramebuffer(WINDOW_W/2+1, WINDOW_H/2+1, WINDOW_W, WINDOW_H, 0, 0,
                      WINDOW_W/2, WINDOW_H/2, GL_STENCIL_BUFFER_BIT, GL_NEAREST);
	
	glStencilFunc(GL_ALWAYS, 0x6666 & mask, ~0);
	draw_rect(0, -1, 1, 1);

	glStencilFunc(GL_ALWAYS, 0x9999 & mask, ~0);
	draw_rect(-1, 0, 1, 1);

	glStencilFunc(GL_ALWAYS, 0xbbbb & mask, ~0);
	draw_rect(0, 0, 1, 1);

	glDisable(GL_STENCIL_TEST);

	compare_stencil();
}

void renderFrame(void) {
	GLint stencil_size;
	GLenum status;

	glClearColor(0, 0, 0, 0);
	glClearDepthf (0.0);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mask = (1 << stencil_size) - 1;

	test_copy();

	glDeleteFramebuffers(1, &fb);
	glDeleteRenderbuffers(1, &depthrb);
	glDeleteRenderbuffers(1, &stencilrb);
	glDeleteTextures(1,&texture);
}

void Sample::test() {
    Init();
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
