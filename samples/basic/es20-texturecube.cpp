/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texturecube.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for texturecube related API
 * @par TestPoints:
 *
 */

#include "Sample.h"


using std::string;
using namespace BotsonSDK;
#define WIN_W 300
#define WIN_H 300

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocNormal = -1;
const int texUnit=0;
GLuint samplerUniform;
GLuint texBufferObject;

GLenum formats[] = {
	GL_ALPHA,
	GL_LUMINANCE,
	GL_LUMINANCE_ALPHA,
	GL_RGB,
	GL_RGBA
};

#define	imageSize 4
static GLubyte image1[imageSize][imageSize][4];
static GLubyte image2[imageSize][imageSize][4];
static GLubyte image3[imageSize][imageSize][4];
static GLubyte image4[imageSize][imageSize][4];
static GLubyte image5[imageSize][imageSize][4];
static GLubyte image6[imageSize][imageSize][4];
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
         image1[i][j][0] = (GLubyte) c;
         image1[i][j][1] = (GLubyte) c;
         image1[i][j][2] = (GLubyte) c;
         image1[i][j][3] = (GLubyte) 255;

         image2[i][j][0] = (GLubyte) c;
         image2[i][j][1] = (GLubyte) c;
         image2[i][j][2] = (GLubyte) 0;
         image2[i][j][3] = (GLubyte) 255;

         image3[i][j][0] = (GLubyte) c;
         image3[i][j][1] = (GLubyte) 0;
         image3[i][j][2] = (GLubyte) c;
         image3[i][j][3] = (GLubyte) 255;

         image4[i][j][0] = (GLubyte) 0;
         image4[i][j][1] = (GLubyte) c;
         image4[i][j][2] = (GLubyte) c;
         image4[i][j][3] = (GLubyte) 255;

         image5[i][j][0] = (GLubyte) 255;
         image5[i][j][1] = (GLubyte) c;
         image5[i][j][2] = (GLubyte) c;
         image5[i][j][3] = (GLubyte) 255;

         image6[i][j][0] = (GLubyte) c;
         image6[i][j][1] = (GLubyte) c;
         image6[i][j][2] = (GLubyte) 255;
         image6[i][j][3] = (GLubyte) 255;
      }
   }
}
bool setupGraphics(int width, int height, GLenum factor) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "texturecube.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "texturecube.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    iLocPosition   = glGetAttribLocation(programID, "pos");
    iLocNormal     = glGetAttribLocation(programID, "normal");
    samplerUniform = glGetUniformLocation(programID, "texSampler");

    glUseProgram(programID);

    numIndices = genSphere(20, 0.75f, &vertices, &normals, NULL, &indices);
    glGenTextures(1, &texBufferObject);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texBufferObject);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R_OES, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, imageSize,
                 imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, imageSize,
                 imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, imageSize,
                 imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, imageSize,
                 imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image5);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, imageSize,
                 imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image3);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, imageSize,
                 imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image6);

    GL_CHECK(glUniform1i(samplerUniform, 0));

    GL_CHECK(glViewport(0, 0, width, height));
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    return true;
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

void Sample::test() {
    setupGraphics(WIN_W, WIN_H, GL_RGBA);
    renderFrame();
    string factor_name = get_enum_name(GL_RGBA);
    string bmp_file = filename + factor_name + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
