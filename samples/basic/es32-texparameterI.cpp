/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texparameterI.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texparameterI related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iTexPosition = -1;
GLuint vao;
GLuint positionBufferObject;
const int texUnit=0;
GLuint samplerUniform;
GLuint TextureName;
GLuint VertexArrayName;
GLuint SamplerName;

#define VertexCount 6

typedef struct {
        float x;
        float b;
} vec2;

typedef struct {
        vec2 vertex;
        vec2 texcoord;
} vertex_v2fv2f;

vertex_v2fv2f VertexData[VertexCount] =
{
	{{-0.4f,-0.4f}, {0.0f, 1.0f}},
	{{ 0.4f,-0.4f}, {1.0f, 1.0f}},
	{{ 0.4f, 0.4f}, {1.0f, 0.0f}},
	{{ 0.4f, 0.4f}, {1.0f, 0.0f}},
	{{-0.4f, 0.4f}, {0.0f, 0.0f}},
	{{-0.4f,-0.4f}, {0.0f, 1.0f}}
};

namespace buffer
{
	enum type
	{
		VERTEX,
		ELEMENT,
		MAX
	};
}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

GLuint BufferName[buffer::MAX] = {0, 0};

float vertices[] =
{
	0,0,0,  1,0,0,  0,1,0,
	1,0,0,  0,1,0,  1,1,0,

	0,0,0,  0,1,0,  0,0,1,
	0,1,0,  0,0,1,  0,1,1,

	0,0,0,  0,0,1,  1,0,0,
	0,0,1,  1,0,0,  1,0,1,  

	0,0,1,  0,1,1,  1,0,1,
	0,1,1,  1,0,1,  1,1,1,

	0,1,0,  0,1,1,  1,1,0,
	0,1,1,  1,1,0,  1,1,1,

	1,0,0,  1,0,1,  1,1,0,
	1,0,1,  1,1,0,  1,1,1,
};

#define	iWidth 16
#define	iHeight 16
#define iDepth 16
static GLubyte image[iDepth][iHeight][iWidth][4];

void makeImage(void)
{
   int s, t, r;
    
   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            image[r][t][s][0] = (GLubyte) (s * 17);
            image[r][t][s][1] = (GLubyte) (t * 17);
            image[r][t][s][2] = (GLubyte) (r * 17);
            image[r][t][s][3] = (GLubyte) (r * 17);
         }
}

bool initTexture()
{
    GLint MaxTextureArrayLayers = 0;
    GL_CHECK(glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &MaxTextureArrayLayers));
    LOGI("GetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS): %d\n", MaxTextureArrayLayers);
    GL_CHECK(glGenTextures(1, &TextureName));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, TextureName));
    makeImage();
    GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, iWidth, iHeight, iDepth));
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, iWidth, iHeight, iDepth,
                             GL_RGBA, GL_UNSIGNED_BYTE, image));
    GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 4));
}

void initVertexArray()
{
    GL_CHECK(glGenVertexArrays(1, &VertexArrayName));
    GL_CHECK(glBindVertexArray(VertexArrayName));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]));
	GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_v2fv2f),
                                   BUFFER_OFFSET(0)));
	GL_CHECK(glVertexAttribPointer(iTexPosition, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_v2fv2f),
                                   BUFFER_OFFSET(sizeof(vec2))));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	GL_CHECK(glEnableVertexAttribArray(iLocPosition));
	GL_CHECK(glEnableVertexAttribArray(iTexPosition));
    GL_CHECK(glBindVertexArray(0));
}

bool initSampler() {
    GLint get[4], tmp[4] = {1, 1, 1, 1};

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameterIiv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, tmp));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_LOD, -1000.f));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_NONE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
    GL_CHECK(glGetTexParameterIiv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, get));
    LOGI("GetTexParameterIiv:%d, %d, %d, %d\n", get[0], get[1], get[2], get[3]);
}

bool initBuffer()
{
	GL_CHECK(glGenBuffers(buffer::MAX, &BufferName[0]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(vertex_v2fv2f), VertexData, GL_STATIC_DRAW));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

	return true;
}
void initProgram()
{
    string vertexShaderPath = (string)GLSL_PATH + "sampler2DArray.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "sampler2DArray.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "Position"));
    GL_CHECK(iTexPosition = glGetAttribLocation(programID, "Texcoord"));
    GL_CHECK(samplerUniform = glGetUniformLocation  (programID, "Diffuse"));
    LOGI("S = %d", samplerUniform);
}

bool setupGraphics(int w, int h) {
    makeImage();

    glViewport(0, 0, w, h);
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    initProgram();
    initTexture();
    initBuffer();
    initVertexArray();
    initSampler();
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, TextureName));
    GL_CHECK(glBindSampler(0, SamplerName));
    GL_CHECK(glBindVertexArray(VertexArrayName));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, VertexCount));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file  = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

