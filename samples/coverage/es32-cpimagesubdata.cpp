/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file cpimagesubdata.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for cpimagesubdata related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

#define NUM 4
#define COLOR_TEXTURE_NAME ("assets/mali.bmp")

GLuint textureID[NUM];
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocTexCoord = -1;
GLint iLocSampler = -1;

static const GLubyte indices[] = {0,  1,  2,  3};

static const GLfloat vertices[] =
{
    -0.800000f,  0.8000f, 0.0f,
    -0.800000f, -0.8000f, 0.0f,
     0.800000f,  0.8000f, 0.0f,
     0.800000f, -0.8000f, 0.0f,
};

static const GLfloat textureCoordinates[] =
{
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
};

#define TEX_WIDTH        32
#define TEX_HEIGHT       32
#define TEX_NUMPIXELS    (TEX_WIDTH * TEX_HEIGHT)

#define RED 0xFF0000FF
#define GRAY 0x7F7F7FFF

	GLenum target = GL_TEXTURE_2D;
	GLuint texData[TEX_NUMPIXELS];
	GLuint texRGBA, texSRGBA, i;

bool setupGraphics(int width, int height) {
    string texturePath        = (string)PICTURE_PATH + "RotoZoom.raw";
    string vertexShaderPath   = (string)GLSL_PATH + "mix.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "mix.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glGenTextures(NUM, textureID));

    for (i = 0; i < TEX_NUMPIXELS; ++i) {
        texData[i] = RED;
    }

    glGenTextures(1, &texSRGBA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(target, texSRGBA);
    glTexStorage2D(target, 1, GL_SRGB8_ALPHA8, TEX_WIDTH, TEX_HEIGHT);
    glTexSubImage2D(target, 0, 0, 0, TEX_WIDTH, TEX_HEIGHT,
                    GL_RGBA, GL_UNSIGNED_BYTE, texData);

    glGenTextures(1, &texRGBA);
    glBindTexture(target, texRGBA);
    glTexStorage2D(target, 1, GL_RGBA8, TEX_WIDTH, TEX_HEIGHT);

    glCopyImageSubData(texSRGBA, target, 0, 0, 0, 0,
                       texRGBA, target, 0, 0, 0, 0,
                       TEX_WIDTH, TEX_HEIGHT, 1);

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    programID = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    iLocTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_v2TexCoord"));
    GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    iLocSampler               = GL_CHECK(glGetUniformLocation(programID, "u_s2dTexture"));
    GL_CHECK(glUniform1i(iLocSampler, 0));

    GL_CHECK(glClearColor(0.2f, 0.7f, 0.6f, 0.5));

    glBindTexture(target, 0);
    glDeleteTextures(1, &texSRGBA);
    return true;
}

void renderFrame(void)
{
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));

    GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates));
    GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));

	glBindTexture(target, texRGBA);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
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

