/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texsub3d-2darray.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texsub3d-2darray related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;
string vertexShaderFilename = "teximage3d.vert";
string fragmentShaderFilename = "teximage3d.frag";

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iTexPosition = -1;
GLuint vao;
GLuint positionBufferObject;
const int texUnit=0;
GLuint samplerUniform;
GLuint texBufferObject;
Matrix trans;
GLint MVPLoc;

float vertices[] = {
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

float angleX = 30, angleY = 30, angleZ = 30;

struct {
	GLenum interfmt;
	GLenum format;
	GLenum type;
} factors[] = {
	{GL_R8_SNORM, GL_RED, GL_BYTE},
	{GL_R8I, GL_RED_INTEGER, GL_BYTE},
	{GL_RG8_SNORM, GL_RG, GL_BYTE},
	{GL_RG8I, GL_RG_INTEGER, GL_BYTE},
	{GL_RGBA8_SNORM, GL_RGBA, GL_BYTE},
	{GL_RGB8_SNORM, GL_RGB, GL_BYTE},
	{GL_RGB8I, GL_RGB_INTEGER, GL_BYTE},
	{GL_RGBA8I, GL_RGBA_INTEGER, GL_BYTE},
	{GL_RG8, GL_RG, GL_UNSIGNED_BYTE},
	{GL_R8, GL_RED, GL_UNSIGNED_BYTE},
	{GL_R8UI, GL_RED_INTEGER, GL_UNSIGNED_BYTE},
	{GL_RG8UI, GL_RG_INTEGER, GL_UNSIGNED_BYTE},
	{GL_RGB8UI, GL_RGB_INTEGER, GL_UNSIGNED_BYTE},
	{GL_RGBA8UI, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE},
	{GL_RGB, GL_RGB, GL_UNSIGNED_BYTE},
	{GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE},
	{GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE},
	{GL_LUMINANCE, GL_LUMINANCE, GL_UNSIGNED_BYTE},
	{GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE},
	{GL_R11F_G11F_B10F, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV},
	{GL_RGB32UI, GL_RGB_INTEGER, GL_UNSIGNED_INT},
	{GL_RGB10_A2, GL_RGBA, GL_UNSIGNED_INT_2_10_10_10_REV},
	{GL_RGB10_A2UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT_2_10_10_10_REV},
	{GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT},
	{GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT},
	{GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8},
	{GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV},
	{GL_RGB, GL_RGB, GL_UNSIGNED_SHORT_5_6_5},
	{GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4},
	{GL_RGBA, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1},
	{GL_RGB16UI, GL_RGB_INTEGER, GL_UNSIGNED_SHORT},
	{GL_RGBA16UI, GL_RGBA_INTEGER, GL_UNSIGNED_SHORT},
	{GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT},
	{GL_R16UI, GL_RED_INTEGER, GL_UNSIGNED_SHORT},
	{GL_RG16UI, GL_RG_INTEGER, GL_UNSIGNED_SHORT},
	{GL_R16I, GL_RED_INTEGER, GL_SHORT},
	{GL_RG16I, GL_RG_INTEGER, GL_SHORT},
	{GL_RGB16I, GL_RGB_INTEGER, GL_SHORT},
	{GL_RGBA16I, GL_RGBA_INTEGER, GL_SHORT},
	{GL_RG16F, GL_RG, GL_HALF_FLOAT},
	{GL_R16F, GL_RED, GL_HALF_FLOAT},
	{GL_RGB16F, GL_RGB, GL_HALF_FLOAT},
	{GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT},
	{GL_R11F_G11F_B10F, GL_RGB, GL_FLOAT},
	{GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT},
	{GL_RG32UI, GL_RG_INTEGER, GL_UNSIGNED_INT},
	{GL_RG32I, GL_RG_INTEGER, GL_INT},
	{GL_R32I, GL_RED_INTEGER, GL_INT},
	{GL_RGB32I, GL_RGB_INTEGER, GL_INT},
	{GL_RGBA32I, GL_RGBA_INTEGER, GL_INT},
	{GL_RGBA32F, GL_RGBA, GL_FLOAT},
	{GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT},
	{GL_RGB32F, GL_RGB, GL_FLOAT},
	{GL_RG32F, GL_RG, GL_FLOAT},
	{GL_R32F, GL_RED, GL_FLOAT},
};

static GLubyte image[iDepth][iHeight][iWidth][4];
static GLubyte imagesub[iDepth/2][iHeight/2][iWidth/2][4];
static GLfloat imagef[iDepth][iHeight][iWidth][4];
static GLfloat imagesubf[iDepth/2][iHeight/2][iWidth/2][4];
static GLuint imageui[iDepth][iHeight][iWidth][4];
static GLuint imagesubui[iDepth/2][iHeight/2][iWidth/2][4];

void makeImage(void) {
   int s, t, r;
   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            image[r][t][s][0] = (GLubyte) (s * 17);
            image[r][t][s][1] = (GLubyte) (t * 17);
            image[r][t][s][2] = (GLubyte) (r * 17);
            image[r][t][s][3] = (GLubyte) (r * 17);
         }
   for (s = 0; s < iWidth/2; s++)
      for (t = 0; t < iHeight/2; t++)
         for (r = 0; r < iDepth/2; r++) {
            imagesub[r][t][s][0] = (GLubyte) (s * 8);
            imagesub[r][t][s][1] = (GLubyte) (t * 8);
            imagesub[r][t][s][2] = (GLubyte) (r * 8);
            imagesub[r][t][s][3] = (GLubyte) (r * 8);
         }

   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            imagef[r][t][s][0] = (GLfloat) (s * 17);
            imagef[r][t][s][1] = (GLfloat) (t * 17);
            imagef[r][t][s][2] = (GLfloat) (r * 17);
            imagef[r][t][s][3] = (GLfloat) (r * 17);
         }
   for (s = 0; s < iWidth/2; s++)
      for (t = 0; t < iHeight/2; t++)
         for (r = 0; r < iDepth/2; r++) {
            imagesubf[r][t][s][0] = (GLfloat) (s * 8);
            imagesubf[r][t][s][1] = (GLfloat) (t * 8);
            imagesubf[r][t][s][2] = (GLfloat) (r * 8);
            imagesubf[r][t][s][3] = (GLfloat) (r * 8);
         }

   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            imageui[r][t][s][0] = (GLuint) (s * 17);
            imageui[r][t][s][1] = (GLuint) (t * 17);
            imageui[r][t][s][2] = (GLuint) (r * 17);
            imageui[r][t][s][3] = (GLuint) (r * 17);
         }
   for (s = 0; s < iWidth/2; s++)
      for (t = 0; t < iHeight/2; t++)
         for (r = 0; r < iDepth/2; r++) {
            imagesubui[r][t][s][0] = (GLuint) (s * 8);
            imagesubui[r][t][s][1] = (GLuint) (t * 8);
            imagesubui[r][t][s][2] = (GLuint) (r * 8);
            imagesubui[r][t][s][3] = (GLuint) (r * 8);
         }
}

bool setupGraphics(int width, int height, int i) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
            fragmentShaderPath.c_str());

    iLocPosition = glGetAttribLocation(programID, "pos");
    samplerUniform = glGetUniformLocation  (programID, "texSampler"); 
    MVPLoc = glGetUniformLocation  (programID, "MVP"); 
    trans = Matrix::createTranslation(-0.5, -0.5, -0.5);

    glUseProgram(programID);
    makeImage();
    glGenTextures(1, &texBufferObject);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texBufferObject);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    if(i<28) {
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, factors[i].interfmt, iWidth, iHeight,
                 iDepth, 0, factors[i].format, factors[i].type, image);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, iWidth/2,0,0,  iWidth/2, iHeight/2,
                    iDepth/2, factors[i].format, factors[i].type, (const GLvoid *)imagesub);
    } else if(i>51) {
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, factors[i].interfmt, iWidth, iHeight,
                 iDepth, 0, factors[i].format, factors[i].type, imagef);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, iWidth/2,0,0,  iWidth/2, iHeight/2,
                    iDepth/2, factors[i].format, factors[i].type, (const GLvoid *)imagesubf);
    } else {
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, factors[i].interfmt, iWidth, iHeight,
                 iDepth, 0, factors[i].format, factors[i].type, imageui);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, iWidth/2,0,0,  iWidth/2, iHeight/2,
            iDepth/2, factors[i].format, factors[i].type, (const GLvoid *)imagesubui);
    }

    Matrix rotationX = Matrix::createRotationX(angleX);
    Matrix rotationY = Matrix::createRotationY(angleY);
    Matrix rotationZ = Matrix::createRotationY(angleY);
    Matrix rotation = rotationX * rotationY;
    rotation = rotation * rotationZ;

    Matrix MVP = rotation * trans;
    glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, MVP.getAsArray());
    glUniform1i(samplerUniform, 0);

    GL_CHECK(glViewport(0, 0, width, height));
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    GL_CHECK(glUseProgram(programID));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY,texBufferObject);

    glEnableVertexAttribArray(iLocPosition);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);
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
