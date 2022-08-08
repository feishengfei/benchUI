/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file blitdepth.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for blitdepth related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;
GLuint mask;

const GLenum attachments[2] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};

GLuint programObject;
GLuint fbo;
GLuint colorTexId[4];
GLsizei textureWidth;
GLsizei textureHeight;

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
       "out vec4 fragColor;                                 \n"
       "void main()                                         \n"
       "{                                                   \n"
       "  fragColor = vec4 ( 1, 0, 0, 1 );                  \n"
       "}                                                   \n";
   
   programObject = Shader::createProgramFromString ( vShaderStr, fShaderStr );
   glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
   
   
   return true;
}

void draw_rect(float z, float x, float y, float w, float h) {
   GLfloat verts[4][4];

   verts[0][0] = x;
   verts[0][1] = y;
   verts[0][2] = z;
   verts[0][3] = 1.0;
   verts[1][0] = x + w;
   verts[1][1] = y;
   verts[1][2] = z;
   verts[1][3] = 1.0;
   verts[2][0] = x;
   verts[2][1] = y + h;
   verts[2][2] = z;
   verts[2][3] = 1.0;
   verts[3][0] = x + w;
   verts[3][1] = y + h;
   verts[3][2] = z;
   verts[3][3] = 1.0;

   GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

   glUseProgram ( programObject );
   glVertexAttribPointer ( 0, 4, GL_FLOAT, false, 4 * sizeof ( GLfloat ), verts );
   glEnableVertexAttribArray ( 0 );
   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
}

void compare_stencil(void) {
	int x, y, failures = 0;
	GLfloat depth[WINDOW_W*WINDOW_H];
	GLfloat expected_depth;

	glReadPixels(0, 0, WINDOW_W, WINDOW_H, GL_DEPTH_COMPONENT, GL_FLOAT, depth);

	for (y = 0; y < WINDOW_W; y++) {
		for (x = 0; x < WINDOW_H; x++) {
			if (x == WINDOW_H / 2 || y == WINDOW_W / 2)
				continue;

			if (y < WINDOW_W/2) {
				expected_depth = x < WINDOW_H/2 ? 0.25 : 0.375;
			} else {
				expected_depth = x < WINDOW_H/2 ? 0.625 : 0.75;
			}

			if (fabs(depth[y*WINDOW_H+x] - expected_depth) > 0.001) {
				failures++;
				if (failures < 20) {
					LOGI("Depth at %i,%i   Expected: %f   Observed: %f\n",
						x, y, expected_depth, depth[y*WINDOW_H+x]);
				} else if (failures == 20) {
					LOGI("...\n");
				}
			}
		}
	}
	if (failures)
		LOGE("Total failures: %i\n", failures);
}
void test_copy(void) {
	glClearStencil(0);
	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	draw_rect(-0.5, 0, 0, 1, 1);
	glBlitFramebuffer(WINDOW_W/2+1, WINDOW_H/2+1, WINDOW_W, WINDOW_H,
				     0, 0, WINDOW_W/2, WINDOW_H/2,
				     GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	
	draw_rect(-0.25, 0, -1, 1, 1);
	draw_rect(0.25, -1, 0, 1, 1);
	draw_rect(0.5, 0, 0, 1, 1);
	glDisable(GL_DEPTH_TEST);

	compare_stencil();
}

void renderFrame(void) {
    GLuint fb, rb;
    GLint  stencil_size;
    GLenum status;

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);

    glGenRenderbuffers(1, &rb);
    glBindRenderbuffer(GL_RENDERBUFFER, rb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, WINDOW_W, WINDOW_H);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    GLint param;
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_BACK,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &param);
    LOGI("GL_BACK=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH,
                                          GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, &param);
    LOGI("GL_DEPTH=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_STENCIL,
                                          GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, &param);
    LOGI("GL_STENCIL=%d\n", param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                          GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, &param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER=%d\n", param);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb);
    glViewport(0, 0, WINDOW_W, WINDOW_H);
    GLenum buf[] = {GL_NONE};
    glDrawBuffers(1, buf);
    glReadBuffer(GL_NONE);
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        LOGI("FBO incomplete status 0x%X\n", status);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    test_copy();

    glDeleteFramebuffers(1, &fb);
    glDeleteRenderbuffers(1, &rb);
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
