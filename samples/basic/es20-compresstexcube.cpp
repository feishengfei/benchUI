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
    -1.000000f,  1.0000f, 0.0f,
    -1.000000f,  0.4666f, 0.0f,
    -0.200000f,  1.0000f, 0.0f,
    -0.200000f,  0.4666f, 0.0f,

    -0.200000f,  1.0000f, 0.0f,
    -0.200000f,  0.7333f, 0.0f,
     0.200000f,  1.0000f, 0.0f,
     0.200000f,  0.7333f, 0.0f,

     0.200000f,  1.0000f, 0.0f,
     0.200000f,  0.8666f, 0.0f,
     0.400000f,  1.0000f, 0.0f,
     0.400000f,  0.8666f, 0.0f,

     0.400000f,  1.0000f, 0.0f,
     0.400000f,  0.9333f, 0.0f,
     0.500000f,  1.0000f, 0.0f,
     0.500000f,  0.9333f, 0.0f,

     0.500000f,  1.0000f, 0.0f,
     0.500000f,  0.9666f, 0.0f,
     0.550000f,  1.0000f, 0.0f,
     0.550000f,  0.9666f, 0.0f,

     0.550000f,  1.0000f, 0.0f,
     0.550000f,  0.9833f, 0.0f,
     0.575000f,  1.0000f, 0.0f,
     0.575000f,  0.9833f, 0.0f,

     0.575000f,  1.0000f, 0.0f,
     0.575000f,  0.9916f, 0.0f,
     0.587500f,  1.0000f, 0.0f,
     0.587500f,  0.9916f, 0.0f,

     0.587500f,  1.0000f, 0.0f,
     0.587500f,  0.9958f, 0.0f,
     0.593750f,  1.0000f, 0.0f,
     0.593750f,  0.9958f, 0.0f,

     0.593750f,  1.0000f, 0.0f,
     0.593750f,  0.9958f, 0.0f,
     0.596875f,  1.0000f, 0.0f,
     0.596875f,  0.9958f, 0.0f,
};

static const GLfloat textureCoordinates[] = {
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

GLuint textureID = 0;

GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocTexCoord = -1;
GLint iLocSampler = -1;

bool setupGraphics(int w, int h) {
    string texturePath = ((string)PICTURE_PATH) + textureFilename;
    string vertexShaderPath = ((string)GLSL_PATH) + "texture2d.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "texture2d.frag";

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glCullFace(GL_BACK));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLint params, i;
    glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &params);
    LOGI("GL_NUM_COMPRESSED_TEXTURE_FORMATS: %d\n", params);
    GLenum type[params];
    glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, (GLint *)type);
    for(i=0; i<params; i++)
    LOGI("%d: %x\n", i, type[i]);

    GL_CHECK(glGenTextures(1, &textureID));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    string mainTexturePath = texturePath + "0" + imageExtension;
    unsigned char *textureData;
    Texture::loadData(mainTexturePath.c_str(), &textureData);
    ETCHeader loadedETCHeader = ETCHeader(textureData);
    GL_CHECK(glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_ETC1_RGB8_OES, loadedETCHeader.getWidth(),loadedETCHeader.getHeight(), 0, loadedETCHeader.getPaddedWidth() * loadedETCHeader.getPaddedHeight() >> 1, textureData + 16));
    free(textureData);

    GLenum glError = glGetError();
    LOGI("glGetError() = %i (0x%.8x) at %s:%i\n", glError, glError, __FILE__, __LINE__);

    unsigned char textureDataSub[64*64];
    memset(textureDataSub,255,sizeof(textureDataSub));
    glCompressedTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 64, 64, GL_ETC1_RGB8_OES, 64*32, textureDataSub);

    glError = glGetError();
    LOGI("glGetError() = %i (0x%.8x) at %s:%i\n", glError, glError, __FILE__, __LINE__);
    
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);
    programID = GL_CHECK(glCreateProgram());
    if (!programID) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    if(iLocPosition == -1) {
        LOGE("Attribute not found: \"a_v4Position\"");
        exit(1);
    }
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    iLocTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_v2TexCoord"));
    if(iLocTexCoord == -1) {
        LOGW("Warning: Attribute not found: \"a_v2TexCoord\"");
    } else {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }

    iLocSampler = GL_CHECK(glGetUniformLocation(programID, "u_s2dTexture"));
    if(iLocSampler == -1) {
        LOGW("Warning: Uniform not found: \"u_s2dTexture\"");
    } else {
        GL_CHECK(glUniform1i(iLocSampler, 0));
    }

    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));

    if(iLocTexCoord != -1) {
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates));
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));

    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);

    GL_CHECK(glDeleteTextures(1, &textureID));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
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
