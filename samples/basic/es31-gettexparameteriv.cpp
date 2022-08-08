/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gettexparameteriv.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for gettexparameteriv related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

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

float vertices[] =
{
    -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
};

float texcoords[] =
{
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
};

GLenum factors[] = {
	GL_NEAREST,
	GL_LINEAR,
};

bool setupGraphics(int width, int height)
{
    string vertexShaderPath = (string)GLSL_PATH + "texture2d.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "texture2d.frag";
    string textureShaderPath = (string)PICTURE_PATH + "cat.jpg";

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    programID = GL_CHECK(glCreateProgram());
    if (programID == 0)
    {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));

    iLocPosition = glGetAttribLocation(programID, "pos");
    iTexPosition = glGetAttribLocation(programID, "tex");

    glUseProgram(programID);

    TexData image_jpg;
    image_jpg.file_name = (char *)textureShaderPath.c_str();
    read_jpeg(&image_jpg);
    glGenTextures(1, &texBufferObject);
    glBindTexture(GL_TEXTURE_2D, texBufferObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_jpg.width, image_jpg.height, 0,
                 GL_RGB,GL_UNSIGNED_BYTE, image_jpg.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    free(image_jpg.data);

    glViewport(0, 0, width, height);
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(GLenum factor)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLint iparams;
    GLfloat fparams;
    glGenSamplers(1,&sampler);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER,factor);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T,GL_REPEAT);
    samplerUniform = glGetUniformLocation  (programID, "texSampler"); 
    glUniform1i(samplerUniform, texUnit);
    GLint param;
    glGetSamplerParameteriv(sampler, GL_TEXTURE_MAG_FILTER,&param);
    LOGI("glGetSamplerParameteriv(GL_TEXTURE_MAG_FILTER)=%x\n",get_enum_name(param));

    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_WIDTH = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_WIDTH = %d\n",iparams);

    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_HEIGHT = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_HEIGHT = %d\n",iparams);

    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_DEPTH,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_DEPTH,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_DEPTH = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_DEPTH = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_INTERNAL_FORMAT,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_INTERNAL_FORMAT,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_INTERNAL_FORMAT = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_INTERNAL_FORMAT = %d\n",iparams);

	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_RED_SIZE,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_RED_SIZE,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_RED_SIZE = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_RED_SIZE = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_GREEN_SIZE,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_GREEN_SIZE,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_GREEN_SIZE = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_GREEN_SIZE = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_BLUE_SIZE,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_BLUE_SIZE,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_BLUE_SIZE = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_BLUE_SIZE = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_ALPHA_SIZE,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_ALPHA_SIZE,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_ALPHA_SIZE = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_ALPHA_SIZE = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_DEPTH_SIZE,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_DEPTH_SIZE,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_DEPTH_SIZE = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_DEPTH_SIZE = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_STENCIL_SIZE,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_STENCIL_SIZE,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_STENCIL_SIZE = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_STENCIL_SIZE = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_SHARED_SIZE,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_SHARED_SIZE,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_SHARED_SIZE = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_SHARED_SIZE = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_BLUE_TYPE,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_BLUE_TYPE,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_BLUE_TYPE = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_BLUE_TYPE = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_ALPHA_TYPE,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_ALPHA_TYPE,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_ALPHA_TYPE = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_ALPHA_TYPE = %d\n",iparams);
	
    glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_COMPRESSED,&fparams);
    glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_COMPRESSED,&iparams);	
   
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_COMPRESSED = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_COMPRESSED = %d\n",iparams);

    GL_CHECK(glUseProgram(programID));
    glActiveTexture(GL_TEXTURE0+texUnit);
    glBindTexture(GL_TEXTURE_2D,texBufferObject);
    glBindSampler(texUnit,sampler);

    GLboolean isSampler=glIsSampler(sampler);
    LOGI("glIsSampler:sampler=%d\n",sampler);

    glEnableVertexAttribArray(iLocPosition);
    glEnableVertexAttribArray(iTexPosition);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(iTexPosition, 2, GL_FLOAT, GL_FALSE, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        renderFrame(factors[i]);
        string bmp_file = filename + "-" + get_enum_name(factors[i]) + ".bmp";
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