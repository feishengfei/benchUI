/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texcopysub3d-2darray.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texcopysub3d-2darray related API
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

static GLubyte image[iDepth][iHeight][iWidth][4];
static GLubyte imagesub[iDepth/2][iHeight/2][iWidth/2][4];

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
}

bool setupGraphics(int width, int height) {
    GL_CHECK(glViewport(0, 0, width, height));
    glClearColor (1.0, 1.0, 1.0, 1.0);
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
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
    GL_CHECK(glGenTextures(1, &texBufferObject));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texBufferObject));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER,GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER,GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, iWidth, iHeight, iDepth, 0,  GL_RGBA, GL_UNSIGNED_BYTE, image));
    GL_CHECK(glCopyTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, iWidth/2,0,0,  0,0,
                                 iHeight/2,iWidth/2));

    Matrix rotationX = Matrix::createRotationX(angleX);
    Matrix rotationY = Matrix::createRotationY(angleY);
    Matrix rotationZ = Matrix::createRotationY(angleY);
    Matrix rotation = rotationX * rotationY;
    rotation = rotation * rotationZ;

    Matrix MVP = rotation * trans;
    GL_CHECK(glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, MVP.getAsArray()));
    GL_CHECK(glUniform1i(samplerUniform, 0));

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
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
