/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file stencil.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for stencil related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

struct format_info {
   GLenum IntFormat, BaseFormat;
   GLboolean IsInteger;
   GLboolean IsFloat;
   GLboolean IsCompressed;
};

struct Sop_t {
	GLenum sfail;
	GLenum dpfail;
	GLenum dppass;
};

struct Sfunc_t {
	GLenum func;
	GLint ref;
	GLuint mask;
};

struct stencil_param_t {
	GLint Sclear;
	struct Sfunc_t func_s11;   
	struct Sop_t op_s11;
	struct Sfunc_t func_s12;
	struct Sop_t op_s12;

	GLenum DepthF21;
	struct Sfunc_t func_s21;   
	struct Sop_t op_s21;
	GLenum DepthF22;
	struct Sfunc_t func_s22;
	struct Sop_t op_s22;

	struct Sfunc_t func_s31;   
	struct Sop_t op_s31;
	struct Sfunc_t func_s32;
	struct Sop_t op_s32;
};

const struct stencil_param_t stencil_param[]={{
	0xff, { GL_NEVER,0x1,0xff }, { GL_INCR,GL_INCR_WRAP,GL_DECR },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0xff,0xff }, { GL_INCR,GL_INCR_WRAP,GL_DECR },
	GL_ALWAYS, {GL_EQUAL,0x00,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_ALWAYS,0x70,0xff }, { GL_INCR,GL_INCR_WRAP,GL_DECR },
	{ GL_EQUAL,0xfe,0xfe }, { GL_KEEP,GL_KEEP,GL_KEEP }
},
{ 
	0x71, { GL_NEVER,0x90,0xff }, { GL_DECR_WRAP,GL_INVERT,GL_KEEP },
	{ GL_EQUAL,0x70,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x71,0xff }, { GL_DECR_WRAP,GL_INVERT,GL_KEEP },
	GL_ALWAYS, {GL_EQUAL,0x8e,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR_WRAP,GL_INVERT,GL_KEEP },
	{ GL_EQUAL,0x71,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}, {
	0x71, { GL_NEVER,0x90,0xff }, { GL_INVERT,GL_KEEP,GL_ZERO },
	{ GL_EQUAL,0x8e,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_INVERT,GL_KEEP,GL_ZERO },
	GL_ALWAYS, {GL_EQUAL,0x71,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_INVERT,GL_KEEP,GL_ZERO },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}, {
	0xff, { GL_NEVER,0x90,0xff }, { GL_INCR_WRAP,GL_DECR,GL_DECR_WRAP },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0xfe,0xff }, { GL_INCR_WRAP,GL_DECR,GL_DECR_WRAP },
	GL_ALWAYS, {GL_EQUAL,0xfe,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_INCR_WRAP,GL_DECR,GL_DECR_WRAP },
	{ GL_EQUAL,0xfe,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}, {
	0xff, { GL_NEVER,0x90,0xff }, { GL_KEEP,GL_ZERO,GL_REPLACE },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_KEEP,GL_ZERO,GL_REPLACE },
	GL_ALWAYS, {GL_EQUAL,0x00,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_KEEP,GL_ZERO,GL_REPLACE },
	{ GL_EQUAL,0x90,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}, {
	0x00, { GL_LESS, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_LESS, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_LESS, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_LESS, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_LESS, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_LESS, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}, {
	0x00, { GL_LEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_LEQUAL, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_LEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_LEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_LEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_LEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}, {
	0x00, { GL_GREATER, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_GREATER, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_GREATER, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_GREATER, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_GREATER, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_GREATER, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}, {
	0x00, { GL_NOTEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_NOTEQUAL, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_NOTEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_NOTEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_NOTEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_NOTEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}, {
	0x00, { GL_GEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_GEQUAL, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_GEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_GEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_GEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_GEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}, { 	0x00, { GL_NEVER,0x90,0xff }, { GL_ZERO, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_ZERO, GL_KEEP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_ZERO, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_ZERO, GL_KEEP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_ZERO, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_ZERO, GL_KEEP, GL_KEEP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_INCR_WRAP, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_INCR_WRAP, GL_KEEP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_INCR_WRAP, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_INCR_WRAP, GL_KEEP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_INCR_WRAP, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_INCR_WRAP, GL_KEEP, GL_KEEP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR_WRAP, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_DECR_WRAP, GL_KEEP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR_WRAP, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_DECR_WRAP, GL_KEEP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR_WRAP, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_DECR_WRAP, GL_KEEP, GL_KEEP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_INCR, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_INCR, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INCR, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INCR, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INCR, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INCR, GL_KEEP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_INCR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_INCR_WRAP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INCR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INCR_WRAP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INCR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INCR_WRAP, GL_KEEP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_DECR, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_DECR, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_DECR, GL_KEEP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_DECR_WRAP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_DECR_WRAP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_DECR_WRAP, GL_KEEP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_INVERT, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_INVERT, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INVERT, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INVERT, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INVERT, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INVERT, GL_KEEP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INCR_WRAP },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_KEEP, GL_INCR_WRAP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INCR_WRAP },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_INCR_WRAP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INCR_WRAP },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_INCR_WRAP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_KEEP, GL_DECR },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_DECR }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_DECR }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR_WRAP },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_KEEP, GL_DECR_WRAP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR_WRAP },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_DECR_WRAP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR_WRAP },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_DECR_WRAP }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_KEEP, GL_INVERT },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_INVERT }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_INVERT }
}, {
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}
};

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
GLint iLocFillColor = -1;
GLuint buffers[2];

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    GLuint vertexShaderID = 0;
    GLuint fragmentShaderID = 0;

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition = glGetAttribLocation(programID, "a_v4Position");
    iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor");
    GLint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glViewport(0, 0, width, height));

    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));
    glClearStencil(0x00);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0x00);

    return true;
}

void renderFrame(void) {
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	GL_CHECK(glUseProgram(programID));
	glStencilFunc(GL_GREATER, 0x90, 0xff);
	glStencilOp(GL_DECR, GL_DECR_WRAP, GL_INVERT);

	GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0,
								   triangleVertices));
	GL_CHECK(glEnableVertexAttribArray(iLocPosition));

	if (iLocFillColor != -1) {
		GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0,
									   triangleColors));
		GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
	}

	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
	glStencilFuncSeparate(GL_FRONT, GL_GREATER, 0x00, 0xff);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilMaskSeparate(GL_FRONT, 0x00);
	GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0,
								   triangleVertices2));
	GL_CHECK(glEnableVertexAttribArray(iLocPosition));

	if (iLocFillColor != -1) {
		GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0,
									   triangleColors2));
		GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
	}

	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
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
