/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texturecube1.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for texturecube1 related API
 * @par TestPoints:
 *
 */

#include "Sample.h"


using std::string;
using namespace BotsonSDK;
#define WIN_W 300
#define WIN_H 300
#define	imageSize 4

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocNormal = -1;
const int texUnit=0;
GLuint samplerUniform;
GLuint texBufferObject;

struct {
    GLenum format;
    GLenum type;
}factors[] = {
        {GL_RGB, GL_UNSIGNED_BYTE},
        {GL_RGB, GL_UNSIGNED_SHORT_5_6_5},
        {GL_RGBA, GL_UNSIGNED_BYTE},
        {GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4},
        {GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1},
        {GL_ALPHA, GL_UNSIGNED_BYTE},
        {GL_LUMINANCE, GL_UNSIGNED_BYTE},
        {GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE},
};

static GLubyte image_1[imageSize][imageSize][4];
static GLubyte image_2[imageSize][imageSize][4];
static GLubyte image_3[imageSize][imageSize][4];
static GLubyte image_4[imageSize][imageSize][4];
static GLubyte image_5[imageSize][imageSize][4];
static GLubyte image_6[imageSize][imageSize][4];

GLenum target[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

GLfloat *vertices;
GLuint *indices;
GLfloat *normals;
int numIndices;

static GLfloat ztrans = 0.0;

void makeImages(void) {
   int i, j, c;
    
   for (i = 0; i < imageSize; i++) {
      for (j = 0; j < imageSize; j++) {
         c = ((((i&0x1)==0)^((j&0x1))==0))*255;
         image_1[i][j][0] = (GLubyte) c;
         image_1[i][j][1] = (GLubyte) c;
         image_1[i][j][2] = (GLubyte) c;
         image_1[i][j][3] = (GLubyte) 255;

         image_2[i][j][0] = (GLubyte) c;
         image_2[i][j][1] = (GLubyte) c;
         image_2[i][j][2] = (GLubyte) 0;
         image_2[i][j][3] = (GLubyte) 255;

         image_3[i][j][0] = (GLubyte) c;
         image_3[i][j][1] = (GLubyte) 0;
         image_3[i][j][2] = (GLubyte) c;
         image_3[i][j][3] = (GLubyte) 255;

         image_4[i][j][0] = (GLubyte) 0;
         image_4[i][j][1] = (GLubyte) c;
         image_4[i][j][2] = (GLubyte) c;
         image_4[i][j][3] = (GLubyte) 255;

         image_5[i][j][0] = (GLubyte) 255;
         image_5[i][j][1] = (GLubyte) c;
         image_5[i][j][2] = (GLubyte) c;
         image_5[i][j][3] = (GLubyte) 255;

         image_6[i][j][0] = (GLubyte) c;
         image_6[i][j][1] = (GLubyte) c;
         image_6[i][j][2] = (GLubyte) 255;
         image_6[i][j][3] = (GLubyte) 255;
      }
   }
}

void teximage(GLenum format, GLenum type) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, imageSize,
                 imageSize, 0, format, type, image_1);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, imageSize,
                 imageSize, 0, format, type, image_4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, imageSize,
                 imageSize, 0, format, type, image_2);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, imageSize,
                 imageSize, 0, format, type, image_5);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, imageSize,
                 imageSize, 0, format, type, image_3);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, imageSize,
                 imageSize, 0, format, type, image_6);
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texBufferObject);

    glEnableVertexAttribArray(iLocPosition);
    glEnableVertexAttribArray(iLocNormal);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(iLocNormal, 3, GL_FLOAT, GL_FALSE, 0, normals);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, indices);

    free(vertices);
    free(normals);
    free(indices);
}

void setupContext() {
    string vertexShaderPath   = ((string)GLSL_PATH) + "texturecube.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "texturecube.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    iLocPosition   = glGetAttribLocation(programID, "pos");
    iLocNormal     = glGetAttribLocation(programID, "normal");
    samplerUniform = glGetUniformLocation(programID, "texSampler");

    glUseProgram(programID);
    makeImages();
    numIndices = genSphere(20, 0.75f, &vertices, &normals, NULL, &indices);
    glGenTextures(1, &texBufferObject);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texBufferObject);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R_OES, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void endofContext() {
    GL_CHECK(glUniform1i(samplerUniform, 0));

    GL_CHECK(glViewport(0, 0, WIN_W, WIN_H));
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void Sample::test() {

    for (int i = 0; i < 8; i++) {
        setupContext();
        teximage(factors[i].format, factors[i].type);
        endofContext();
        renderFrame();

        char ss[5];
        sprintf(ss, "%d", i);
        string bmp_file = filename + "-" + ss + ".bmp";
        LOGI("bmp_file=%s", bmp_file.c_str());

        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}


int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
