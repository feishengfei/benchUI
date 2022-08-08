/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file copybuffer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for copybuffer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programObject;
GLuint fbo;

const GLenum tests[] = {
	GL_DEPTH_COMPONENT16, GL_UNSIGNED_INT_24_8,
	GL_DEPTH_COMPONENT24, GL_UNSIGNED_INT_24_8,
	GL_DEPTH_COMPONENT32F, GL_FLOAT,
};

int Init ( ) {
   char vShaderStr[] =
        "#version 430\n" 
	"in vec4 vertex;\n"
	"uniform float depth;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(vertex.xy, depth, 1.0);\n"
	"}\n";                                      

   char fShaderStr[] =
	"void main()\n"
	"{\n"
	"}\n";

   programObject = Shader::createProgramFromString ( vShaderStr, fShaderStr );
   glUseProgram(programObject);
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
   glVertexAttribPointer ( 0, 3, GL_FLOAT, false, 3 * sizeof ( GLfloat ), vVertices );
   glEnableVertexAttribArray ( 0 );
   glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
}

static bool equals(float a, float b) {
   return fabs(a - b) < 0.00001;
}

static GLuint create_depth_fbo(GLenum depth_type) {
    GLuint fbo, buffer;
    GLenum status;
    glGenRenderbuffers(1, &buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, depth_type, WINDOW_W, WINDOW_H);
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, buffer);
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        LOGE("error creating framebuffer, status 0x%x\n", status);
        return 0;
    }
    return fbo;
}

static bool read_depth(GLenum type, float expect) {
	GLfloat data;
	GLuint uint_pixel;
	if (type == GL_FLOAT) {
		glReadPixels(0, 0, 1, 1, GL_DEPTH_COMPONENT, type,
			(void *) &data);
	} else {
		glReadPixels(0, 0, 1, 1, GL_DEPTH_COMPONENT, type,
			(void *) &uint_pixel);
		uint_pixel = uint_pixel >> 8;
		data = (1.0 * ((float) uint_pixel)) / 16777215.0;
	}

	if (!equals(data, expect)) {
		LOGI("expected %f, got %f\n", expect, data);
		return false;
	}
	return true;
}

GLboolean renderFrame(void) {
    const float step = 0.1;
    unsigned    j;
    float       i;

    glEnable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    for (j = 0; j < ARRAY_NUM(tests); j += 2) {
        float  expect = 0.0;
        GLuint fbo    = create_depth_fbo(tests[j]);
        if (!fbo)
            return GL_FALSE;

        for (i = -1.0; !equals(i, 1.0 + step); i += step) {
            glClear(GL_DEPTH_BUFFER_BIT);
            glUniform1f(glGetUniformLocation(programObject, "depth"), i);
            draw_rect(-1, -1, 2, 2);
            if (!(read_depth(tests[j + 1], expect))) {
                LOGE("failed !\n");
                return GL_FALSE;
            }
            expect += step / 2.0;
        }
        glDeleteFramebuffers(1, &fbo);
    }
    LOGI("passed !\n");
    return GL_TRUE;
}

void Sample::test() {
    Init();
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    LOGI("test result: %s !\n", renderFrame()==GL_TRUE? "PASS" : "FAIL");
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
