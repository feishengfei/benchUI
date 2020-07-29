/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texstorage2d-cubemap.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texstorage2d-cubemap related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "cubemap.vert";
string fragmentShaderFilename = "cubemap.frag";

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocNormal = -1;
const int texUnit=0;
GLuint samplerUniform;
GLuint texBufferObject;

struct {
	GLenum interfmt;
	GLenum format;
	GLenum type;
} factors[] = {
	{GL_R8, GL_RED , GL_UNSIGNED_BYTE},
	{GL_R8_SNORM, GL_RED , GL_BYTE},
	{GL_R8UI, GL_RED_INTEGER , GL_UNSIGNED_BYTE},
	{GL_R8I, GL_RED_INTEGER , GL_BYTE},
	{GL_RG8, GL_RG , GL_UNSIGNED_BYTE},
	{GL_RG8_SNORM, GL_RG , GL_BYTE},
	{GL_RG8UI, GL_RG_INTEGER , GL_UNSIGNED_BYTE},
	{GL_RG8I, GL_RG_INTEGER , GL_BYTE},
	{GL_RGB8, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_SRGB8, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_RGB565, GL_RGB , GL_UNSIGNED_BYTE},
	{GL_RGB8_SNORM, GL_RGB , GL_BYTE},
	{GL_RGB8UI, GL_RGB_INTEGER , GL_UNSIGNED_BYTE},
	{GL_RGB8I, GL_RGB_INTEGER , GL_BYTE},
	{GL_RGBA8, GL_RGBA , GL_UNSIGNED_BYTE},
	{GL_SRGB8_ALPHA8, GL_RGBA , GL_UNSIGNED_BYTE},
	{GL_RGBA8_SNORM, GL_RGBA , GL_BYTE},
	{GL_RGB5_A1, GL_RGBA , GL_UNSIGNED_BYTE},
	{GL_RGBA4, GL_RGBA , GL_UNSIGNED_BYTE},
	{GL_RGBA8UI, GL_RGBA_INTEGER , GL_UNSIGNED_BYTE},
	{GL_RGBA8I, GL_RGBA_INTEGER , GL_BYTE},
	{GL_R16F, GL_RED , GL_FLOAT},
	{GL_R32F, GL_RED , GL_FLOAT},
	{GL_RG16F, GL_RG , GL_FLOAT},
	{GL_RG32F, GL_RG , GL_FLOAT},
	{GL_R11F_G11F_B10F, GL_RGB , GL_FLOAT},
	{GL_RGB16F, GL_RGB , GL_FLOAT},
	{GL_RGB32F, GL_RGB , GL_FLOAT},
	{GL_RGBA16F, GL_RGBA , GL_FLOAT},
	{GL_RGBA32F, GL_RGBA , GL_FLOAT},
	{GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT , GL_FLOAT},
	{GL_R16UI, GL_RED_INTEGER , GL_UNSIGNED_SHORT},
	{GL_R16I, GL_RED_INTEGER , GL_SHORT},
	{GL_RG16UI, GL_RG_INTEGER , GL_UNSIGNED_SHORT},
	{GL_RG16I, GL_RG_INTEGER , GL_SHORT},
	{GL_RGB16UI, GL_RGB_INTEGER , GL_UNSIGNED_SHORT},
	{GL_RGB16I, GL_RGB_INTEGER , GL_SHORT},
	{GL_RGBA16UI, GL_RGBA_INTEGER , GL_UNSIGNED_SHORT},
	{GL_RGBA16I, GL_RGBA_INTEGER , GL_SHORT},
	{GL_R32UI, GL_RED_INTEGER , GL_UNSIGNED_INT},
	{GL_R32I, GL_RED_INTEGER , GL_INT},
	{GL_RG32UI, GL_RG_INTEGER , GL_UNSIGNED_INT},
	{GL_RG32I, GL_RG_INTEGER , GL_INT},
	{GL_RGB32UI, GL_RGB_INTEGER , GL_UNSIGNED_INT},
	{GL_RGB32I, GL_RGB_INTEGER , GL_INT},
	{GL_RGB10_A2, GL_RGBA , GL_UNSIGNED_INT_2_10_10_10_REV},
	{GL_RGB10_A2UI, GL_RGBA_INTEGER , GL_UNSIGNED_INT_2_10_10_10_REV},
	{GL_RGBA32I, GL_RGBA_INTEGER , GL_INT},
	{GL_RGBA32UI, GL_RGBA_INTEGER , GL_UNSIGNED_INT},
	{GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT , GL_UNSIGNED_INT},
	{GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT , GL_UNSIGNED_INT},
	{GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL , GL_UNSIGNED_INT_24_8},
	{GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL , GL_FLOAT_32_UNSIGNED_INT_24_8_REV},
};

GLfloat *vertices;
GLuint *indices;
GLfloat *normals;
int numIndices;

static GLfloat ztrans = 0.0;
#define	imageSize 4
static GLubyte image1b[imageSize][imageSize][4];
static GLubyte image2b[imageSize][imageSize][4];
static GLubyte image3b[imageSize][imageSize][4];
static GLubyte image4b[imageSize][imageSize][4];
static GLubyte image5b[imageSize][imageSize][4];
static GLubyte image6b[imageSize][imageSize][4];

static GLushort image1s[imageSize][imageSize][4];
static GLushort image2s[imageSize][imageSize][4];
static GLushort image3s[imageSize][imageSize][4];
static GLushort image4s[imageSize][imageSize][4];
static GLushort image5s[imageSize][imageSize][4];
static GLushort image6s[imageSize][imageSize][4];

static GLfloat image1f[imageSize][imageSize][4];
static GLfloat image2f[imageSize][imageSize][4];
static GLfloat image3f[imageSize][imageSize][4];
static GLfloat image4f[imageSize][imageSize][4];
static GLfloat image5f[imageSize][imageSize][4];
static GLfloat image6f[imageSize][imageSize][4];

static GLuint image1i[imageSize][imageSize][4];
static GLuint image2i[imageSize][imageSize][4];
static GLuint image3i[imageSize][imageSize][4];
static GLuint image4i[imageSize][imageSize][4];
static GLuint image5i[imageSize][imageSize][4];
static GLuint image6i[imageSize][imageSize][4];

void makeImages(void) {
   int i, j, c;
   for (i = 0; i < imageSize; i++) {
      for (j = 0; j < imageSize; j++) {
         c = ((((i&0x1)==0)^((j&0x1))==0))*255;
         image1b[i][j][0] = (GLubyte) c;
         image1b[i][j][1] = (GLubyte) c;
         image1b[i][j][2] = (GLubyte) c;
         image1b[i][j][3] = (GLubyte) 255;

         image2b[i][j][0] = (GLubyte) c;
         image2b[i][j][1] = (GLubyte) c;
         image2b[i][j][2] = (GLubyte) 0;
         image2b[i][j][3] = (GLubyte) 255;

         image3b[i][j][0] = (GLubyte) c;
         image3b[i][j][1] = (GLubyte) 0;
         image3b[i][j][2] = (GLubyte) c;
         image3b[i][j][3] = (GLubyte) 255;

         image4b[i][j][0] = (GLubyte) 0;
         image4b[i][j][1] = (GLubyte) c;
         image4b[i][j][2] = (GLubyte) c;
         image4b[i][j][3] = (GLubyte) 255;

         image5b[i][j][0] = (GLubyte) 255;
         image5b[i][j][1] = (GLubyte) c;
         image5b[i][j][2] = (GLubyte) c;
         image5b[i][j][3] = (GLubyte) 255;

         image6b[i][j][0] = (GLubyte) c;
         image6b[i][j][1] = (GLubyte) c;
         image6b[i][j][2] = (GLubyte) 255;
         image6b[i][j][3] = (GLubyte) 255;
      }
   }

   for (i = 0; i < imageSize; i++) {
      for (j = 0; j < imageSize; j++) {
         c = ((((i&0x1)==0)^((j&0x1))==0))*255;
         image1s[i][j][0] = (GLushort) c;
         image1s[i][j][1] = (GLushort) c;
         image1s[i][j][2] = (GLushort) c;
         image1s[i][j][3] = (GLushort) 255;

         image2s[i][j][0] = (GLushort) c;
         image2s[i][j][1] = (GLushort) c;
         image2s[i][j][2] = (GLushort) 0;
         image2s[i][j][3] = (GLushort) 255;

         image3s[i][j][0] = (GLushort) c;
         image3s[i][j][1] = (GLushort) 0;
         image3s[i][j][2] = (GLushort) c;
         image3s[i][j][3] = (GLushort) 255;

         image4s[i][j][0] = (GLushort) 0;
         image4s[i][j][1] = (GLushort) c;
         image4s[i][j][2] = (GLushort) c;
         image4s[i][j][3] = (GLushort) 255;

         image5s[i][j][0] = (GLushort) 255;
         image5s[i][j][1] = (GLushort) c;
         image5s[i][j][2] = (GLushort) c;
         image5s[i][j][3] = (GLushort) 255;

         image6s[i][j][0] = (GLushort) c;
         image6s[i][j][1] = (GLushort) c;
         image6s[i][j][2] = (GLushort) 255;
         image6s[i][j][3] = (GLushort) 255;
      }
   }
}

bool setupGraphics(int width, int height, int i) {
    string vertexShaderPath   = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

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
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GL_CHECK(glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, factors[i].interfmt,
                            imageSize, imageSize));
    if (i < 21) {
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image1b));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image4b));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image2b));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image5b));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image3b));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image6b));
    } else if (i < 32) {
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image1f));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image4f));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image2f));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image5f));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image3f));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image6f));
    } else if (i < 40) {
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image1s));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image4s));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image2s));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image5s));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image3s));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image6s));
    } else {
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image1i));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image4i));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image2i));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image5i));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image3i));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, 0, 0, imageSize,
                                 imageSize, factors[i].format, factors[i].type, image6i));
    }

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
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        setupGraphics(WINDOW_W, WINDOW_H, i);
        renderFrame();
        char ss[2];
        sprintf(ss, "%d", i);
        string factorname = get_enum_name(factors[i].interfmt);
        string bmp_file  = filename + "-" + ss + "-" + factorname + ".bmp";
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
