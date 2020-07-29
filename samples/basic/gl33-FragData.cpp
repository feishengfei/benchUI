/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl33-Samplers.cpp
 * @author Cary.Zhang
 * @par History:
 *    A001: Cary.Zhang, 2019-07-10, create file
 * @par TestPoints:
 *
 * glGenSamplers
 * glDeleteSamplers
 * glIsSampler
 * glBindSampler
 * glSamplerParameteri
 * glSamplerParameteriv
 * glTexImage2DMultisample
 * glTexImage3DMultisample
 * glGetMultisamplefv
 * glSampleMaski
 *
 */
#include "Sample.h"
#include "Shader.h"
#include "bmp.h"
#include <iostream>
#include <sstream>
using std::string;

unsigned int DisplayMode = GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE;// | GLUT_MULTISAMPLE;
/*shaderID & pogramID*/
GLuint vertexShaderID = -1;
GLuint fragmentShaderID = -1;
GLuint programID = -1;

/* Asset directory. */
GLuint iLocPosition = -1;
GLuint UniformDisplacement = -1;
GLuint SamplerAName = 0;
GLuint SamplerBName = 0;
GLint iLocFragData = 0;
float vertices[] =
        {
            1.0f, 1.0f, 0.0f,        1.0f, 0.0f, 0.0f,        1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,       0.0f, 1.0f, 0.0f,        1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,      0.0f, 0.0f, 1.0f,        0.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f,        0.0f, 1.0f
        };

unsigned int indices[] = 
{
    0, 1, 3,
    1, 2, 3
};

float fragColor[] = {0.6, 0.0, 0.0};
float fcolor[] = {0.0, 0.0, 0.0};
int icolor[] = {0, 0, 0 };

   TexData image_png;
   tBMP    image_bmp;

unsigned int VBO, VAO, EBO;
unsigned int texture1, texture2;
GLuint samplerUniform;
const int texUnit=0;
GLint params;

bool setupGraphics(int width, int height)
{
    ShaderInfo shaders[] = {
        {GL_VERTEX_SHADER, "Samplers.vert", },
        {GL_FRAGMENT_SHADER, "Samplers.frag", },
        {GL_NONE,NULL},
    };
    programID = Shader::LoadShaders(shaders);

      glViewport(0, 0, width, height);
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}


bool initSampler()
{
    GL_CHECK(glGenSamplers(1, &SamplerAName));
                
    GL_CHECK(glSamplerParameteri(SamplerAName, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CHECK(glSamplerParameteri(SamplerAName, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glSamplerParameteri(SamplerAName, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glSamplerParameteri(SamplerAName, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glSamplerParameterfv(SamplerAName, GL_TEXTURE_BORDER_COLOR, fcolor));
    GL_CHECK(glSamplerParameterIiv(SamplerAName, GL_TEXTURE_BORDER_COLOR, icolor));
    GL_CHECK(glSamplerParameterf(SamplerAName, GL_TEXTURE_MIN_LOD, -1000.f));
    GL_CHECK(glSamplerParameterf(SamplerAName, GL_TEXTURE_MAX_LOD, 1000.f));
    GL_CHECK(glSamplerParameteri(SamplerAName, GL_TEXTURE_COMPARE_MODE, GL_NONE));
    GL_CHECK(glSamplerParameteri(SamplerAName, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
    return true;
}

void initTexture()
{
    GL_CHECK(glGenVertexArrays(1, &VAO));
    GL_CHECK(glGenBuffers(1, &VBO));
    GL_CHECK(glGenBuffers(1, &EBO));
    GL_CHECK(glBindVertexArray(VAO));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float))));
    GL_CHECK(glEnableVertexAttribArray(2));

    GL_CHECK(glGenTextures(1, &texture1));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));

    string PictureName = (string)PICTURE_PATH + "cat.jpg";
    image_png.file_name = (char *)PictureName.c_str();   

    LOGI("loadTexturePNG: %s\n",image_png.file_name);
    read_jpeg(&image_png);
  
    LOGI("mage_png.height  = %d\n",image_png.height);
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_png.width, image_png.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_png.data));
    
    GL_CHECK(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, SamplerAName, GL_RGB8, image_png.width, image_png.height, GL_TRUE ));

    free(image_png.data);

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
}

void renderFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    glEnable(GL_SAMPLE_MASK);
    glSampleMaski(0, 0x3);

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));
    GL_CHECK(glBindSampler(texUnit, SamplerAName));

    GL_CHECK(glBindVertexArray(VAO));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

void Sample::test() {
    string bmp_file = filename + ".bmp";
    LOGI("[]: filename=%s\n", bmp_file.c_str());
    glViewport(0, 0, WINDOW_W, WINDOW_H);
    
    setupGraphics(WINDOW_W, WINDOW_H);
    initSampler();
    initTexture();
    renderFrame();
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}