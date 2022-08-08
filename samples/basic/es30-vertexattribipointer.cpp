/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file vertexattribipointer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for vertexattribipointer related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "VertexAttribIPointer.vert";
string fragmentShaderFilename = "VertexAttribIPointer.frag";

const float Vertices[] = {
    -0.4f,  0.0f, 0.0f,
    -0.2f,  0.0f, 0.0f,
     0.0f,  0.0f, 0.0f,
     0.2f,  0.0f, 0.0f,
     0.4f,  0.0f, 0.0f
};

float Vertices0[] = {
    -0.8f,  0.4f, 0.0f,
    -0.8f, -0.4f, 0.0f
};

float Vertices1[] = {
    -0.4f,  0.4f, 0.0f,
    -0.4f, -0.4f, 0.0f
};

float Vertices2[] = {
     0.0f,  0.4f, 0.0f,
     0.0f, -0.4f, 0.0f
};

float Vertices3[] = {
     0.4f,  0.4f, 0.0f,
     0.4f, -0.4f, 0.0f
};

float Vertices4[] = {
     0.8f,  0.4f, 0.0f,
     0.8f, -0.4f, 0.0f
};

const float Colors[] = {
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0
};

const float Sizes[] = { 1.0, 5.0, 10.0, 15.0, 20.0};

GLfloat Sizes0[] = { 1.0, 10.0 };
GLbyte Sizes1[] = { 2, 9 };
GLubyte Sizes2[] = { 4, 7 };
GLshort Sizes3[] = { 6, 5 };
GLushort Sizes4[] = { 8, 3 };

const GLubyte indices[] = {0,1,2,3,4};

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLint iLocPointSize = -1;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

static const GLubyte ubyte4_data[] = { 100, 0, 200, 255 };
static const GLbyte byte4_data[] = { 50, 0, -25, -50 };
static const GLushort ushort4_data[] = { 16000, 0, 32000, 65535 };
static const GLshort short4_data[] = { 2000, 0, -4000, -32010 };
static const GLuint uint4_data[] = { 10000000, 0, 20000000, 80000020 };
static const GLint int4_data[] = { 10000000, 0, -20000000, -40000020 };
static GLint ExpectedUniform_i, ExpectedUniform_u;
static GLint Attr_i, Attr_u;

static const GLenum types[] = {
	GL_BYTE,
	GL_UNSIGNED_BYTE,
	GL_SHORT,
	GL_UNSIGNED_SHORT,
	GL_INT,
	GL_UNSIGNED_INT
};
char filename[20];

void test_array(GLenum type, GLint size) {
	static const GLfloat verts[4][2] = {
			{-0.5, -0.5},
			{0.5,  -0.5},
			{0.5,  0.5},
			{-0.5, 0.5}
	};
	static const GLfloat green[4]    = {0.0, 1.0, 0.0, 0.0};
	GLubyte              attr_buffer[4 * 4 * sizeof(GLuint)];
	int                  typeSize;
	const void           *data;
	GLint                expected[4];
	int                  i;

	switch (type) {
	case GL_BYTE:
		typeSize = sizeof(GLbyte);
		data     = byte4_data;
		for (i   = 0; i < 4; i++)
			expected[i] = byte4_data[i];
		break;
	case GL_UNSIGNED_BYTE:
		typeSize = sizeof(GLubyte);
		data     = ubyte4_data;
		for (i   = 0; i < 4; i++)
			expected[i] = ubyte4_data[i];
		break;
	case GL_SHORT:
		typeSize = sizeof(GLshort);
		data     = short4_data;
		for (i   = 0; i < 4; i++)
			expected[i] = short4_data[i];
		break;
	case GL_UNSIGNED_SHORT:
		typeSize = sizeof(GLushort);
		data     = ushort4_data;
		for (i   = 0; i < 4; i++)
			expected[i] = ushort4_data[i];
		break;
	case GL_INT:
		typeSize = sizeof(GLint);
		data     = int4_data;
		for (i   = 0; i < 4; i++)
			expected[i] = int4_data[i];
		break;
	case GL_UNSIGNED_INT:
		typeSize = sizeof(GLuint);
		data     = uint4_data;
		for (i   = 0; i < 4; i++)
			expected[i] = uint4_data[i];
		break;
	default:
		typeSize = sizeof(GLint);
		data     = NULL;
	}

	switch (size) {
	case 1:
		expected[1] = 0;
	case 2:
		expected[2] = 0;
	case 3:
		expected[3] = 1;
	}

	{
		int i, sz = typeSize * size;
		for (i = 0; i < 4; i++) {
			memcpy(attr_buffer + i * sz, data, sz);
		}
	}

	glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, verts);
	glEnableVertexAttribArray(iLocPosition);
	glVertexAttribIPointer(Attr_i, size, type, 0, attr_buffer);
	glEnableVertexAttribArray(Attr_i);
	glVertexAttribIPointer(Attr_u, size, type, 0, attr_buffer);
	glEnableVertexAttribArray(Attr_u);

	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	glUniform4iv(ExpectedUniform_i, 1, expected);
	glUniform4uiv(ExpectedUniform_u, 1, (const GLuint *)expected);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(Attr_i);
	glDisableVertexAttribArray(Attr_u);
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(),
						  GL_FRAGMENT_SHADER);
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

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    Attr_i = glGetAttribLocation(programID, "attr_i");
    Attr_u = glGetAttribLocation(programID, "attr_u");
    ExpectedUniform_i = glGetUniformLocation(programID, "expected_i");
    ExpectedUniform_u = glGetUniformLocation(programID, "expected_u");

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));
    return true;
}

void Sample::test() {
	for(int i=0; i<ARRAY_NUM(types); i++) {
		for (int size = 1; size <= 4; size++) {
			setupGraphics(WINDOW_W, WINDOW_H);
			test_array(types[i], size);
			string mode_name = get_enum_name(types[i]);
			char ss[2];
			sprintf(ss, "_d%", size);
			string bmp_file  = filename + "-" + mode_name + "-" + ss + ".bmp";
			LOGI("bmp_file=%s", bmp_file.c_str());
			save2bmp(bmp_file.c_str());
			Sample::SwapBuffers();
		}
	}
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
