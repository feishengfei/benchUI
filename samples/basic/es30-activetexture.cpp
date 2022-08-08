/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file activetexture.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for activetexture related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"


#define NUM 4

using std::string;
using namespace BotsonSDK;

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

string vertexShaderFilename = "ActiveTexture.vert";
string fragmentShaderFilename = "ActiveTexture.frag";
#define COLOR_TEXTURE_NAME ("mali.bmp")
#define COLOR_TEXTURE_Tim ("Tim.bmp")
#define COLOR_TEXTURE_Iamge2 ("image2.bmp")

GLuint textureID[NUM];
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocTexCoord = -1;
GLint iLocSampler = -1;
GLint iLocSampler1 = -1;

GLint baseMapLoc;
GLint lightMapLoc;
GLuint baseMapTexId;
GLuint lightMapTexId;

void print_active_texture() {
    GLint active_texture;

    glGetIntegerv(GL_ACTIVE_TEXTURE, &active_texture);
    LOGI("active_texture=0x%x\n",active_texture);
}

void print_max_texture_unit() {
    GLint max_texture_unit;

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_texture_unit);
    LOGI("max_texture_unit=%d\n",max_texture_unit);
}

GLuint LoadTexture (const char *fileName ) {
   int width,
       height;

   unsigned char *buffer = NULL;
   GLuint texId;

   glGenTextures ( 1, &texId );
   glBindTexture ( GL_TEXTURE_2D, texId );

   Texture::loadBmpImageData(fileName, &width, &height, &buffer);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                buffer);
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

   free ( buffer );

   return texId;
}

bool setupGraphics(int w, int h) {
    string vertexShaderPath   = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

    baseMapLoc = GL_CHECK(glGetUniformLocation(programID, "s_baseMap"));
    lightMapLoc               = GL_CHECK(glGetUniformLocation(programID, "s_lightMap"));

    string texturePath = (string)PICTURE_PATH + COLOR_TEXTURE_Tim;
    baseMapTexId = LoadTexture(texturePath.c_str());
    texturePath = (string)PICTURE_PATH + COLOR_TEXTURE_Iamge2;
    lightMapTexId = LoadTexture(texturePath.c_str());

    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 0.0f));

    return true;
}

void renderFrame(void) {
    GLfloat vVertices[] = {-0.5f, 0.5f, 0.0f,
                           0.0f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                           0.0f, 1.0f,
                           0.5f, -0.5f, 0.0f,
                           1.0f, 1.0f,
                           0.5f, 0.5f, 0.0f,
                           1.0f, 0.0f
    };

    GLushort indices[] = {0, 1, 2, 0, 2, 3};

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), vVertices);

    if (iLocTexCoord != -1) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                              &vVertices[3]);
    }
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, baseMapTexId);
    glUniform1i(baseMapLoc, 0);
    glBindTexture(GL_TEXTURE_2D, lightMapTexId);
    glUniform1i(lightMapLoc, 1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
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
