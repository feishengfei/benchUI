/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file compresstex.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for compresstex related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"
#include "ETCHeader.h"

#define DISABLE_MIPMAPS

using std::string;
using namespace BotsonSDK;

static const GLubyte indices[] =
{
     0,  1,  2,  3,    3,  4,    4,  5,  6,  7,    7,  8,
     8,  9, 10, 11,   11, 12,   12, 13, 14, 15,   15, 16,
    16, 17, 18, 19,   19, 20,   20, 21, 22, 23,   23, 24,
    24, 25, 26, 27,   27, 28,   28, 29, 30, 31,   31, 32,
    32, 33, 34, 35,
};


static const GLfloat vertices[] = {
    -1.000000f,  1.0000f, 0.0f, 1.0f,
    -1.000000f,  0.4666f, 0.0f, 1.0f,
    -0.200000f,  1.0000f, 0.0f, 1.0f,
    -0.200000f,  0.4666f, 0.0f, 1.0f,
    -0.200000f,  1.0000f, 0.0f, 1.0f,
    -0.200000f,  0.7333f, 0.0f, 1.0f,
     0.200000f,  1.0000f, 0.0f, 1.0f,
     0.200000f,  0.7333f, 0.0f, 1.0f,
     0.200000f,  1.0000f, 0.0f, 1.0f,
     0.200000f,  0.8666f, 0.0f, 1.0f,
     0.400000f,  1.0000f, 0.0f, 1.0f,
     0.400000f,  0.8666f, 0.0f, 1.0f,
     0.400000f,  1.0000f, 0.0f, 1.0f,
     0.400000f,  0.9333f, 0.0f, 1.0f,
     0.500000f,  1.0000f, 0.0f, 1.0f,
     0.500000f,  0.9333f, 0.0f, 1.0f,
     0.500000f,  1.0000f, 0.0f, 1.0f,
     0.500000f,  0.9666f, 0.0f, 1.0f,
     0.550000f,  1.0000f, 0.0f, 1.0f,
     0.550000f,  0.9666f, 0.0f, 1.0f,
     0.550000f,  1.0000f, 0.0f, 1.0f,
     0.550000f,  0.9833f, 0.0f, 1.0f,
     0.575000f,  1.0000f, 0.0f, 1.0f,
     0.575000f,  0.9833f, 0.0f, 1.0f,
     0.575000f,  1.0000f, 0.0f, 1.0f,
     0.575000f,  0.9916f, 0.0f, 1.0f,
     0.587500f,  1.0000f, 0.0f, 1.0f,
     0.587500f,  0.9916f, 0.0f, 1.0f,
     0.587500f,  1.0000f, 0.0f, 1.0f,
     0.587500f,  0.9958f, 0.0f, 1.0f,
     0.593750f,  1.0000f, 0.0f, 1.0f,
     0.593750f,  0.9958f, 0.0f, 1.0f,
     0.593750f,  1.0000f, 0.0f, 1.0f,
     0.593750f,  0.9958f, 0.0f, 1.0f,
     0.596875f,  1.0000f, 0.0f, 1.0f,
     0.596875f,  0.9958f, 0.0f, 1.0f
};

static const GLfloat coords[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
};
string textureFilename = "good_mip_";
string imageExtension = ".pkm";
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint textureID = 0;
GLuint programID, VAOs, Buffers;


bool setupGraphics(int w, int h) {
    string texturePath = ((string)PICTURE_PATH) + textureFilename;
    string vertexShaderPath = ((string)GLSL_PATH) + "texture2d.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "texture2d.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glCullFace(GL_BACK));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    string mainTexturePath = texturePath + "0" + imageExtension;
    unsigned char *textureData;
    Texture::loadData(mainTexturePath.c_str(), &textureData);
    ETCHeader loadedETCHeader = ETCHeader(textureData);
    GL_CHECK(glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB8_ETC2, loadedETCHeader.getWidth(),loadedETCHeader.getHeight(), 0, loadedETCHeader.getPaddedWidth() * loadedETCHeader.getPaddedHeight() >> 1, textureData + 16));
    free(textureData);

    unsigned char textureDataSub[64*64];
    memset(textureDataSub,255,sizeof(textureDataSub));
    GL_CHECK(glCompressedTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 64, 64, GL_COMPRESSED_RGB8_ETC2, 64*32, textureDataSub));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(coords), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(coords), coords));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));

    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices));

    GL_CHECK(glDeleteTextures(1, &textureID));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file    = filename + ".bmp";
    LOGI("bmp_file=%s\n", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
