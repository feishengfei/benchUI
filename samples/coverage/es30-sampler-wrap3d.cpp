/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file sampler-wrap3d.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for sampler-wrap3d related API
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
GLuint sampler=0;
GLuint samplerUniform;
GLuint texBufferObject;

float vertices1[] = {
	-2.25/2.5, 1.0/2.5, 0.0,
	-2.25/2.5, -1.0/2.5, 0.0,
	-0.25/2.5, 1.0/2.5, 0.0,
	-0.25/2.5, -1.0/2.5, 0.0,
};

float vertices2[] = {
	0.25/2.5, 1.0/2.5, 0.0,
	0.25/2.5, -1.0/2.5, 0.0,
	2.25/2.5, 1.0/2.5, 0.0,
	2.25/2.5, -1.0/2.5, 0.0,
};

float texcoords1[] = {
	-0.4, 1.4, -0.4,
	-0.4, -0.4, -0.4,
	1.4, 1.4, 1.4,
	1.4, -0.4, 1.4,
};

float texcoords2[] = {
	-0.4, 1.4, 1.4,
	-0.4, -0.4, 1.4,
	1.4, 1.4, -0.4,
	1.4, -0.4, -0.4
};

GLenum factors[] = {
	GL_CLAMP_TO_EDGE, 
	GL_MIRRORED_REPEAT,
	GL_REPEAT
};

#define	iWidth 16
#define	iHeight 16
#define iDepth 16

static GLubyte image[iDepth][iHeight][iWidth][3];

void makeImage(void) {
   int s, t, r;
   for (s = 0; s < 16; s++)
      for (t = 0; t < 16; t++)
         for (r = 0; r < iDepth; r++) {
            image[r][t][s][0] = (GLubyte) (s * 17);
            image[r][t][s][1] = (GLubyte) (t * 17);
            image[r][t][s][2] = (GLubyte) (r * 17);
         }
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

    iLocPosition   = glGetAttribLocation(programID, "pos");
    iTexPosition   = glGetAttribLocation(programID, "tex");
    samplerUniform = glGetUniformLocation(programID, "texSampler");

    glUseProgram(programID);
    makeImage();
    glGenTextures(1, &texBufferObject);
    glBindTexture(GL_TEXTURE_3D, texBufferObject);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, iWidth, iHeight, iDepth, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);

    GL_CHECK(glViewport(0, 0, width, height));
    glClearColor(0.7, 0.2, 0.8, 0.6);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void renderFrame(GLenum factor) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    GL_CHECK(glGenSamplers(1,&sampler));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER,GL_NEAREST));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER,GL_NEAREST));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S,factor));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T,factor));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R,factor));

    GL_CHECK(glUniform1i(samplerUniform, texUnit));
    GL_CHECK(GL_CHECK(glUseProgram(programID)));
    GL_CHECK(glActiveTexture(GL_TEXTURE0+texUnit));
    GL_CHECK(glBindTexture(GL_TEXTURE_3D,texBufferObject));
    GL_CHECK(glBindSampler(texUnit,sampler));

    GLint param;
    GL_CHECK(glGetSamplerParameteriv(sampler, GL_TEXTURE_WRAP_S,&param));
    GL_CHECK(LOGI("glGetSamplerParameteriv(GL_TEXTURE_WRAP_S)=%x",get_enum_name(param)));
    GL_CHECK(glGetSamplerParameteriv(sampler, GL_TEXTURE_WRAP_T,&param));
    GL_CHECK(LOGI("glGetSamplerParameteriv(GL_TEXTURE_WRAP_T)=%x",get_enum_name(param)));
    GL_CHECK(glGetSamplerParameteriv(sampler, GL_TEXTURE_WRAP_R,&param));
    GL_CHECK(LOGI("glGetSamplerParameteriv(GL_TEXTURE_WRAP_R)=%x",get_enum_name(param)));

    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glEnableVertexAttribArray(iTexPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices1));
    GL_CHECK(glVertexAttribPointer(iTexPosition, 3, GL_FLOAT, GL_FALSE, 0, texcoords1));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));

    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glEnableVertexAttribArray(iTexPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices2));
    GL_CHECK(glVertexAttribPointer(iTexPosition, 3, GL_FLOAT, GL_FALSE, 0, texcoords2));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        renderFrame(factors[i]);
        string mode_name = get_enum_name(factors[i]);
        string bmp_file  = filename + "-" + mode_name + ".bmp";
        LOGI("bmp_file=%s", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
    glDeleteSamplers(1,&sampler);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
