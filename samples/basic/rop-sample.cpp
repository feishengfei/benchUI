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
#include <sstream>
#include <iostream>
#include "VectorTypes.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

/*shaderID & pogramID*/
GLuint vertexShaderID = -1;
GLuint fragmentShaderID = -1;
GLuint programID = -1;

/* Asset directory. */

string vertexShaderFileName = "Samplers.vert";
string fragmentShaderFileName = "Samplers.frag";
GLuint iLocPosition = -1;
GLuint UniformDisplacement = -1;
GLuint SamplerName = 0;
float vertices[] =
        {
            -1.0f, -1.0f, 0.0f,         1.0f, 0.0f, 0.0f,        1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f,          0.0f, 1.0f, 0.0f,        1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,           0.0f, 0.0f, 1.0f,        0.0f, 0.0f,
            1.0f, -1.0f, 0.0f,          1.0f, 1.0f, 0.0f,        0.0f, 1.0f
        };

unsigned int indices[] = 
{
    0, 1, 3,
    1, 2, 3
};

float fcolor[] = {0.0, 0.0, 0.0};
int icolor[] = {0, 0, 0 };

   TexData image_png;
   tBMP    image_bmp;

unsigned int VBO, VAO, EBO;
unsigned int texture1, texture2;
GLuint samplerUniform;
const int texUnit=0;
GLint params;
GLboolean initProgram(void)
{
    string vertexShaderPath = (string)GLSL_PATH + "Samplers.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "Samplers.frag";

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0)
    {
        LOGI("Could not create program.");
        return GL_FALSE;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "pos"));
    return GL_TRUE;
}

bool setupGraphics()
{
    if(!initProgram())
    {
        LOGI("init program failed!\n");
        return GL_FALSE;
    }

    glViewport(0, 0, WINDOW_W, WINDOW_H);
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}


bool initSampler()
{
/*                GL_CHECK(glEnable(GL_MULTISAMPLE));
                GL_CHECK(glEnable(GL_POINT_SMOOTH));
*/  
    GL_CHECK(glGenSamplers(1, &SamplerName));
                
//                GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));

//    GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
//    GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
//  GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
//    GL_CHECK(glSamplerParameterfv(SamplerName, GL_TEXTURE_BORDER_COLOR, fcolor));
//    GL_CHECK(glSamplerParameterIiv(SamplerName, GL_TEXTURE_BORDER_COLOR, icolor));
    GL_CHECK(glSamplerParameterf(SamplerName, GL_TEXTURE_MIN_LOD, -1000.f));
    GL_CHECK(glSamplerParameterf(SamplerName, GL_TEXTURE_MAX_LOD, 1000.f));
//    GL_CHECK(glSamplerParameterIuiv(SamplerName, GL_TEXTURE_LOD_BIAS, 0));
    GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_COMPARE_MODE, GL_NONE));
    GL_CHECK(glSamplerParameteri(SamplerName, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));

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

    string PictureName = (string)PICTURE_PATH + "glsl/gl33/landscape.jpg";
    image_png.file_name = (char *)PictureName.c_str();   

    LOGI("loadTexturePNG: %s\n",image_png.file_name);
    read_jpeg(&image_png);
  
    LOGI("mage_png.height  = %d\n",image_png.height);
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_png.width, image_png.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_png.data));
    
//    GL_CHECK(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, SamplerName, GL_RGB, image_png.width, image_png.height, GL_TRUE ));

    free(image_png.data);

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
}

void renderFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

//    glClearBufferfv(GL_COLOR, 0, icolor);

    GL_CHECK(samplerUniform = glGetUniformLocation  (programID, "ourTexture"));
    GL_CHECK(glUniform1i(samplerUniform, texUnit));

    GL_CHECK(glEnable(GL_SAMPLE_MASK));
    GL_CHECK(glSampleMaski(0, 0x8));
    
    GL_CHECK(glEnable(GL_DITHER));

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));
    GL_CHECK(glBindSampler(texUnit, SamplerName));
    GL_CHECK(glBindVertexArray(VAO));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

void Sample::test() {
    string bmp_file = filename + ".bmp";
    LOGI("[]: fileName=%s\n", bmp_file.c_str());
    setupGraphics();
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