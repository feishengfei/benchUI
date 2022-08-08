/**
 * @file gl20-stencilsep.cpp
 * @testpoint glBlendEquationSeparate
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
unsigned int DisplayMode = GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE;

struct format_info
{
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

const struct stencil_param_t stencil_param[]={
{
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
},
{ 
	0x71, { GL_NEVER,0x90,0xff }, { GL_INVERT,GL_KEEP,GL_ZERO },
	{ GL_EQUAL,0x8e,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_INVERT,GL_KEEP,GL_ZERO },
	GL_ALWAYS, {GL_EQUAL,0x71,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_INVERT,GL_KEEP,GL_ZERO },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
},
{ 
	0xff, { GL_NEVER,0x90,0xff }, { GL_INCR_WRAP,GL_DECR,GL_DECR_WRAP },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0xfe,0xff }, { GL_INCR_WRAP,GL_DECR,GL_DECR_WRAP },
	GL_ALWAYS, {GL_EQUAL,0xfe,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_INCR_WRAP,GL_DECR,GL_DECR_WRAP },
	{ GL_EQUAL,0xfe,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
},
{ 
	0xff, { GL_NEVER,0x90,0xff }, { GL_KEEP,GL_ZERO,GL_REPLACE },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_KEEP,GL_ZERO,GL_REPLACE },
	GL_ALWAYS, {GL_EQUAL,0x00,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_KEEP,GL_ZERO,GL_REPLACE },
	{ GL_EQUAL,0x90,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
},
{ 
	0x00, { GL_LESS, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_LESS, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_LESS, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_LESS, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_LESS, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_LESS, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
},
{ 
	0x00, { GL_LEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_LEQUAL, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_LEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_LEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_LEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_LEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
},
{ 
	0x00, { GL_GREATER, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_GREATER, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_GREATER, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_GREATER, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_GREATER, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_GREATER, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
},
{ 
	0x00, { GL_NOTEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_NOTEQUAL, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_NOTEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_NOTEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_NOTEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_NOTEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
},
{ 
	0x00, { GL_GEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_GEQUAL, 0x00, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_GEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_GEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_GEQUAL, 0x90, 0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_GEQUAL, 0xff, 0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
},
{ 	0x00, { GL_NEVER,0x90,0xff }, { GL_ZERO, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_ZERO, GL_KEEP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_ZERO, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_ZERO, GL_KEEP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_ZERO, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_ZERO, GL_KEEP, GL_KEEP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_INCR_WRAP, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_INCR_WRAP, GL_KEEP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_INCR_WRAP, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_INCR_WRAP, GL_KEEP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_INCR_WRAP, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_INCR_WRAP, GL_KEEP, GL_KEEP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR_WRAP, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_DECR_WRAP, GL_KEEP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR_WRAP, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_DECR_WRAP, GL_KEEP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR_WRAP, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_DECR_WRAP, GL_KEEP, GL_KEEP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_INCR, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_INCR, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INCR, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INCR, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INCR, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INCR, GL_KEEP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_INCR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_INCR_WRAP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INCR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INCR_WRAP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INCR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INCR_WRAP, GL_KEEP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_DECR, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_DECR, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_DECR, GL_KEEP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_DECR_WRAP, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_DECR_WRAP, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_DECR_WRAP, GL_KEEP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_INVERT, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_INVERT, GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INVERT, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INVERT, GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_INVERT, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_INVERT, GL_KEEP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INCR_WRAP },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_KEEP, GL_INCR_WRAP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INCR_WRAP },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_INCR_WRAP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INCR_WRAP },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_INCR_WRAP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_KEEP, GL_DECR },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_DECR }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_DECR }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR_WRAP },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_KEEP, GL_DECR_WRAP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR_WRAP },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_DECR_WRAP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_DECR_WRAP },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_DECR_WRAP }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP, GL_KEEP, GL_INVERT },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_INVERT }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR, GL_DECR_WRAP, GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP, GL_KEEP, GL_INVERT }
},
{ 
	0x00, { GL_NEVER,0x90,0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_EQUAL,0x00,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP },
	GL_NEVER, {GL_ALWAYS,0x90,0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	GL_ALWAYS, {GL_EQUAL,0xff,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }, 
	{ GL_ALWAYS,0x90,0xff }, { GL_DECR,GL_DECR_WRAP,GL_INVERT },
	{ GL_EQUAL,0xff,0xff }, { GL_KEEP,GL_KEEP,GL_KEEP }
}
};

/* Simple triangle. */
const float triangleVertices1[] =
{
    -0.8f, -0.5f, 0.0f,
    -0.6f,  0.6f, 0.0f,
    -0.4f, -0.5f, 0.0f
};
const float triangleVertices2[] =
{
    -0.2f, -0.5f, 0.0f,
     0.0f,  0.6f, 0.0f,
     0.2f, -0.5f, 0.0f
};
const float triangleVertices3[] =
{
     0.6f,  0.6f, 0.0f,
     0.4f, -0.5f, 0.0f,
     0.8f, -0.5f, 0.0f
};

const float triangleColors1[] =
					{
							0.3f, 0.3f, 0.3f, 1.0f,
							0.3f, 0.3f, 0.3f, 1.0f,
							0.3f, 0.3f, 0.3f, 1.0f
					};
const float triangleColors2[] =
					{
							1.0f, 0.0f, 0.0f, 1.0f,
							1.0f, 0.0f, 0.0f, 1.0f,
							1.0f, 0.0f, 0.0f, 1.0f
					};
const float triangleColors3[] =
					{
							0.0f, 1.0f, 0.0f, 1.0f,
							0.0f, 1.0f, 0.0f, 1.0f,
							0.0f, 1.0f, 0.0f, 1.0f
					};
const float triangleColors4[] =
					{
							0.0f, 0.0f, 1.0f, 1.0f,
							0.0f, 0.0f, 1.0f, 1.0f,
							0.0f, 0.0f, 1.0f, 1.0f
					};

GLenum funcs[] = {
	GL_NEVER,
	GL_LESS,
	GL_LEQUAL,
	GL_GREATER,
	GL_GEQUAL,
	GL_EQUAL,
	GL_NOTEQUAL,
	GL_ALWAYS
};

GLenum faces[]={
	GL_FRONT,
	GL_BACK,
	GL_FRONT_AND_BACK
};

GLenum factors[]={
	GL_KEEP,
	GL_ZERO,
	GL_REPLACE,
	GL_INCR,
	GL_INCR_WRAP,
	GL_DECR,
	GL_DECR_WRAP,
	GL_INVERT
};
GLuint programID, vaos[6], vbos[6];
bool setupGraphics(int width, int height)
{
	string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert";
	string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";
	programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

	GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));
    GL_CHECK(glClearStencil(0x00));
    GL_CHECK(glEnable(GL_STENCIL_TEST));

	GL_CHECK(glGenVertexArrays(6, &vaos[0]));
	GL_CHECK(glGenBuffers(6, &vbos[0]));

	GL_CHECK(glBindVertexArray(vaos[0]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbos[0]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices1) + sizeof(triangleColors1), NULL, GL_STATIC_DRAW));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices1), triangleVertices1));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices1), sizeof(triangleColors1), triangleColors1));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(triangleVertices1))));
	GL_CHECK(glBindVertexArray(0));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GL_CHECK(glBindVertexArray(vaos[1]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbos[1]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices1) + sizeof(triangleColors2), NULL, GL_STATIC_DRAW));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices1), triangleVertices1));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices1), sizeof(triangleColors2), triangleColors2));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(triangleVertices1))));
	GL_CHECK(glBindVertexArray(0));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GL_CHECK(glBindVertexArray(vaos[2]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbos[2]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices2) + sizeof(triangleColors1), NULL, GL_STATIC_DRAW));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices2), triangleVertices2));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices2), sizeof(triangleColors1), triangleColors1));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(triangleVertices2))));
	GL_CHECK(glBindVertexArray(0));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GL_CHECK(glBindVertexArray(vaos[3]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbos[3]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices2) + sizeof(triangleColors3), NULL, GL_STATIC_DRAW));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices2), triangleVertices2));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices2), sizeof(triangleColors3), triangleColors3));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(triangleVertices2))));
	GL_CHECK(glBindVertexArray(0));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GL_CHECK(glBindVertexArray(vaos[4]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbos[4]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices3) + sizeof(triangleColors1), NULL, GL_STATIC_DRAW));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices3), triangleVertices3));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices3), sizeof(triangleColors1), triangleColors1));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(triangleVertices3))));
	GL_CHECK(glBindVertexArray(0));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GL_CHECK(glBindVertexArray(vaos[5]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbos[5]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices3) + sizeof(triangleColors4), NULL, GL_STATIC_DRAW));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices3), triangleVertices3));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangleVertices3), sizeof(triangleColors4), triangleColors4));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(triangleVertices3))));
	GL_CHECK(glBindVertexArray(0));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    return true;
}

void renderFrame(GLenum face, struct stencil_param_t param)
{
	GL_CHECK(glUseProgram(programID));
	GL_CHECK(glClearStencil(param.Sclear));
	GL_CHECK(glEnable(GL_STENCIL_TEST));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

    GL_CHECK(glStencilMaskSeparate(face, 0x00));
	GL_CHECK(glStencilFuncSeparate(face, param.func_s11.func,param.func_s11.ref,param.func_s11.mask));
	GL_CHECK(glStencilOpSeparate(face, param.op_s11.sfail,param.op_s11.dpfail,param.op_s11.dppass));

	GL_CHECK(glBindVertexArray(vaos[0]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	GL_CHECK(glStencilFuncSeparate(face, param.func_s12.func,param.func_s12.ref,param.func_s12.mask));
	GL_CHECK(glStencilOpSeparate(face, param.op_s12.sfail,param.op_s12.dpfail,param.op_s12.dppass));

	GL_CHECK(glBindVertexArray(vaos[1]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	GL_CHECK(glDepthFunc(param.DepthF21));
	GL_CHECK(glEnable(GL_DEPTH_TEST));
	GL_CHECK(glStencilFuncSeparate(face, param.func_s21.func,param.func_s21.ref,param.func_s21.mask));
	GL_CHECK(glStencilOpSeparate(face, param.op_s21.sfail,param.op_s21.dpfail,param.op_s21.dppass));

	GL_CHECK(glBindVertexArray(vaos[2]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	GL_CHECK(glDepthFunc(param.DepthF22));
	GL_CHECK(glStencilFuncSeparate(face, param.func_s22.func,param.func_s22.ref,param.func_s22.mask));
	GL_CHECK(glStencilOpSeparate(face, param.op_s22.sfail,param.op_s22.dpfail,param.op_s22.dppass));

	GL_CHECK(glBindVertexArray(vaos[3]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	GL_CHECK(glStencilFuncSeparate(face, param.func_s31.func,param.func_s31.ref,param.func_s31.mask));
	GL_CHECK(glStencilOpSeparate(face, param.op_s31.sfail,param.op_s31.dpfail,param.op_s31.dppass));

	GL_CHECK(glBindVertexArray(vaos[4]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

	GL_CHECK(glStencilFuncSeparate(face, param.func_s32.func,param.func_s32.ref,param.func_s32.mask));
	GL_CHECK(glStencilOpSeparate(face, param.op_s32.sfail,param.op_s32.dpfail,param.op_s32.dppass));

	GL_CHECK(glBindVertexArray(vaos[5]));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	//for(int i=0; i<ARRAY_NUM(faces); i++) {
	//	for(int j=0; j<ARRAY_NUM(factors); j++) {
	//		string face_name = get_enum_name(faces[i]);
	//		char ss[2];
	//		sprintf(ss, "-%d", j);
	//		string bmp_file = filename + "-" + face_name + ss + ".bmp";
	//		LOGI("[%d_%d]: filename=%s\n", i, j, bmp_file.c_str());
	//		renderFrame(faces[i], stencil_param[j]);
	//		save2bmp(bmp_file.c_str());
	//		SwapBuffers();
	//	}
	//}
	string bmp_file = filename + ".bmp";
	LOGI("filename=%s\n", bmp_file.c_str());
	renderFrame(faces[0], stencil_param[0]);
	save2bmp(bmp_file.c_str());
	SwapBuffers();
}

int main(int argc, char **argv) {
	Sample sample(__FILE__, argc, argv);
	sample.test();
	return 0;
}


//int main(int argc, char** argv)
//{
//    string file = "gl20-stencilsep";
//    GBtest_init(&argc,argv,file,DisplayMode);
//    setupGraphics(WINDOW_W, WINDOW_H);
//    for(int i=0; i<ARRAY_NUM(faces); i++) {
//	for(int j=0; j<ARRAY_NUM(factors); j++) {
//	    string face_name = get_enum_name(faces[i]);
//	    char ss[2];
//	    sprintf(ss, "-%d", j);
//	    string filename = file + "-" + face_name + ss + ".bmp";
//	    LOGIF("[%d_%d]: filename=%s\n", i, j, filename.c_str());
//            renderFrame(faces[i], stencil_param[j]);
//	    save2bmp(filename.c_str());
//	    glutSwapBuffers();
//	}
//    }
//    GBtest_deinit();
//
//    return 0;
//}
