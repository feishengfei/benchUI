/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file bind-image-tex2D.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for bind-image-tex2D related API
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
	GL_CLAMP_TO_EDGE, 
	GL_MIRRORED_REPEAT,
	GL_REPEAT,
};

bool setupGraphics(int width, int height)
{
    string vertexShaderPath = (string)GLSL_PATH + "imageLoad.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "imageLoad.frag";
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
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texBufferObject);
    glBindTexture(GL_TEXTURE_2D, texBufferObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_jpg.width, image_jpg.height, 0, GL_RGBA,GL_UNSIGNED_BYTE, image_jpg.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
   free(image_jpg.data);

    glViewport(0, 0, width, height);
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));

    return true;
}

void renderFrame(GLenum factor)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    
    GL_CHECK(glUseProgram(programID));
   glBindImageTexture(0, texBufferObject, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);

    glEnableVertexAttribArray(iLocPosition);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for (int i = 0; i < ARRAY_NUM(factors); i++) {
        renderFrame(factors[i]);
        string factor_name = get_enum_name(factors[i]);
        string bmp_file  = filename + "-" + factor_name + ".bmp";
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
