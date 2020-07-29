/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file transfeedbackubo.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for transfeedbackubo related API
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

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

float verts[4][4] = {
	{-1.000000, -1.000000, 0.000000, 1.000000},
	{-0.500000, -1.000000, 0.000000, 1.000000},
	{-1.000000, -0.500000, 0.000000, 1.000000},
	{-0.500000, -0.500000, 0.000000, 1.000000}
	};

float color_wheel[4][4] = {
	{1, 0, 0, 1},
	{0, 1, 0, 1},
	{0, 0, 1, 1},
	{1, 1, 1, 1},
};
const GLubyte indices[] = {0,1,2};

string TFvertexShaderFilename = "TransFeedback.vert";
string TFfragmentShaderFilename = "TransFeedback.frag";
string UBvertexShaderFilename = "UniformBlock.vert";
string UBfragmentShaderFilename = "UniformBlock.frag";

GLuint TFvertexShaderID = 0;
GLuint TFfragmentShaderID = 0;
GLuint UBvertexShaderID = 0;
GLuint UBfragmentShaderID = 0;
static int tf_prog, ubo_prog;
static unsigned buffer_object;
GLint tf_pass_loc = -1;
GLint tile_loc = -1;
GLint ubo_pass_loc = -1;
GLint ubo_idx = -1;
GLint TFiLocPosition = -1;
GLint TFiLocFillColor = -1;
GLint UBiLocPosition = -1;
GLint UBiLocFillColor = -1;

#define TILESIZE 32
#define X_TILES 8
#define Y_TILES 8
#define BO_SIZE (X_TILES * Y_TILES * 6 * 4 * sizeof(float))

bool setupGraphics(int width, int height) {
    string TFvertexShaderPath = (string)GLSL_PATH + TFvertexShaderFilename; 
    string TFfragmentShaderPath = (string)GLSL_PATH + TFfragmentShaderFilename;
    Shader::processShader(&TFvertexShaderID, TFvertexShaderPath.c_str(),
						  GL_VERTEX_SHADER);
    Shader::processShader(&TFfragmentShaderID, TFfragmentShaderPath.c_str(),
						  GL_FRAGMENT_SHADER);
    tf_prog = GL_CHECK(glCreateProgram());
    if (tf_prog == 0) {
        LOGE("Could not create tf program.");
        return false;
    }
    GL_CHECK(glAttachShader(tf_prog, TFvertexShaderID));
    GL_CHECK(glAttachShader(tf_prog, TFfragmentShaderID));
    GL_CHECK(glLinkProgram(tf_prog));

    string UBvertexShaderPath = (string)GLSL_PATH + UBvertexShaderFilename; 
    string UBfragmentShaderPath = (string)GLSL_PATH + UBfragmentShaderFilename;
    Shader::processShader(&UBvertexShaderID, UBvertexShaderPath.c_str(),
						  GL_VERTEX_SHADER);
    Shader::processShader(&UBfragmentShaderID, UBfragmentShaderPath.c_str(),
						  GL_FRAGMENT_SHADER);
    ubo_prog = GL_CHECK(glCreateProgram());
    if (ubo_prog == 0) {
        LOGE("Could not create ub program.");
        return false;
    }
    GL_CHECK(glAttachShader(ubo_prog, UBvertexShaderID));
    GL_CHECK(glAttachShader(ubo_prog, UBfragmentShaderID));
    GL_CHECK(glLinkProgram(ubo_prog));

	const char *name = "out_pass";
	glTransformFeedbackVaryings(tf_prog, 1, &name, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(tf_prog);

	glGenBuffers(1, &buffer_object);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, buffer_object);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, BO_SIZE, NULL, GL_STREAM_COPY);

    GL_CHECK(TFiLocPosition = glGetAttribLocation(tf_prog, "piglit_vertex"));
    GL_CHECK(UBiLocPosition = glGetAttribLocation(ubo_prog, "piglit_vertex"));

	tf_pass_loc = glGetUniformLocation(tf_prog, "tf_pass");
	tile_loc = glGetUniformLocation(ubo_prog, "tile");
	ubo_pass_loc = glGetUniformLocation(ubo_prog, "ubo_pass");
	ubo_idx = glGetUniformBlockIndex(ubo_prog, "ubo");

	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_BLEND);
	glViewport(0, 0, width, height);
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

    return true;
}

GLvoid piglit_draw_rect(int iLocPosition, float x, float y, float w, float h) {
	float verts[4][4];
	float color_wheel[4][4] = {
		{1, 0, 0, 1}, 
		{0, 1, 0, 1}, 
		{0, 0, 1, 1}, 
		{1, 1, 1, 1}, 
	};

	verts[0][0] = x;
	verts[0][1] = y;
	verts[0][2] = 0.0;
	verts[0][3] = 1.0;
	verts[1][0] = x + w;
	verts[1][1] = y;
	verts[1][2] = 0.0;
	verts[1][3] = 1.0;
	verts[2][0] = x;
	verts[2][1] = y + h;
	verts[2][2] = 0.0;
	verts[2][3] = 1.0;
	verts[3][0] = x + w;
	verts[3][1] = y + h;
	verts[3][2] = 0.0;
	verts[3][3] = 1.0;

	glVertexAttribPointer(iLocPosition, 4, GL_FLOAT, GL_FALSE, 0, verts);
	glEnableVertexAttribArray(iLocPosition);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void renderFrame(void) {
	bool pass = true;
	const int num_passes = 3;
	const float black[] = {0, 0, 0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < num_passes; ++i) {
		glUseProgram(tf_prog);
		glUniform1i(tf_pass_loc, i);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, buffer_object);
		glBeginTransformFeedback(GL_TRIANGLES);

		for (int y = 1; y < Y_TILES-1; ++y) {
			for (int x = 1; x < X_TILES-1; ++x) {
				const float w = 1.0 / X_TILES;
				const float h = 1.0 / Y_TILES;
				piglit_draw_rect(TFiLocPosition, -1 + 2*x * w, -1 + 2*y * h, 2*w, 2*h);
			}
		}

		glEndTransformFeedback();

		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);

		glUseProgram(ubo_prog);
		glUniform1i(ubo_pass_loc, i);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, buffer_object);
		glUniformBlockBinding(ubo_prog, ubo_idx, 0);

		for (int y = 1; y < Y_TILES-1; ++y) {
			for (int x = 1; x < X_TILES-1; ++x) {
				const float w = 1.0 / X_TILES;
				const float h = 1.0 / Y_TILES;
				glUniform1i(tile_loc, y * X_TILES + x);
				piglit_draw_rect(UBiLocPosition, -1 + 2*x * w, -1 + 2*y * h, 2*w, 2*h);
			}
		}
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, 0);
	}
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
