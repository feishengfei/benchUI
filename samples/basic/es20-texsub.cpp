/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texsub.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for texsub related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"


#define NUM 4

using std::string;
using namespace BotsonSDK;

static const GLubyte indices[] = {
     0,  1,  2,  3
};

static const GLfloat vertices[] = {
    -0.8f,  0.8f,
    -0.8f, -0.8f,
     0.8f,  0.8f,
     0.8f, -0.8f,
};

static const GLfloat textureCoordinates[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
};

string textureFilename = "RotoZoom.raw";
#define COLOR_TEXTURE_NAME ("mali.bmp")

GLuint textureID[NUM];
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocTexCoord = -1;
GLint iLocSampler = -1;

bool setupGraphics(int w, int h) {
    string texturePath = ((string)PICTURE_PATH) + COLOR_TEXTURE_NAME;
    string vertexShaderPath = ((string)GLSL_PATH) + "texture2d.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "texture2d.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glGenTextures(NUM, textureID));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID[0]));
    string mainTexturePath1 = texturePath;
    GLsizei        imageHeight = 0;
    GLsizei        imageWidth  = 0;
    unsigned char* textureData1 = NULL;

    Texture::loadBmpImageData(texturePath.c_str(), &imageWidth, &imageHeight, &textureData1);
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData1));
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

    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0));
    free(textureData1);

    return true;
}

void renderFrame(void) {
    GL_CHECK(glActiveTexture(GL_TEXTURE1));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, vertices));

    if(iLocTexCoord != -1) {
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates));
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID[0]));
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
    GLint active_texture;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &active_texture);
    LOGI("active_texture=0x%x\n",active_texture);
    GLint parami;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &parami);
    LOGI("get(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS): %d", parami);
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &parami);
    LOGI("get(GL_MAX_CUBE_MAP_TEXTURE_SIZE): %d", parami);
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &parami);
    LOGI("get(GL_MAX_TEXTURE_IMAGE_UNITS): %d", parami);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &parami);
    LOGI("get(GL_MAX_TEXTURE_SIZE): %d", parami);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &parami);
    LOGI("get(GL_TEXTURE_BINDING_2D): %d", parami);
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &parami);
    LOGI("get(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS): %d", parami);
    GL_CHECK(glDeleteTextures(2, textureID));
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

