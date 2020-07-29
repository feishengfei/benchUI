/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file max-3d-texture-size.cpp
 * @author Cary.Zhang
 * @par History:
 *    A001: Cary.Zhang, 2019-09-02, Add commit
 * @brief basic test for sampler-wrap3d related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

using std::string;
using namespace BotsonSDK;

GLuint programID;
const int texUnit=0;
GLuint sampler=0;
GLuint samplerUniform;
GLuint texBufferObject;

GLuint VAOs, Buffers;


float vertices1[] = {
	-2.25/2.5, 1.0/2.5, 0.0,
	-2.25/2.5, -1.0/2.5, 0.0,
	-0.25/2.5, 1.0/2.5, 0.0,
	-0.25/2.5, -1.0/2.5, 0.0,
};

float texcoords1[] = {
	-0.4, 1.4, -0.4,
	-0.4, -0.4, -0.4,
	1.4, 1.4, 1.4,
	1.4, -0.4, 1.4,
};

#define	iWidth 64
#define	iHeight 64
#define iDepth 64

static GLubyte image[iDepth][iHeight][iWidth][3];

void makeImage(void) {
   int s, t, r;
   for (s = 0; s < iWidth; s++)
      for (t = 0; t < iHeight; t++)
         for (r = 0; r < iDepth; r++) {
            image[r][t][s][0] = (GLubyte) (s * 17);
            image[r][t][s][1] = (GLubyte) (t * 17);
            image[r][t][s][2] = (GLubyte) (r * 17);
         }
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + "max-3d-texture-size.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "max-3d-texture-size.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1) + sizeof(texcoords1), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices1), vertices1));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(texcoords1), texcoords1));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices1))));

    GL_CHECK(glUseProgram(programID));
    makeImage();
    GL_CHECK(glGenTextures(1, &texBufferObject));
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texBufferObject));

    GLint my_3d_texture_size;
    GL_CHECK(glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE , &my_3d_texture_size));
    LOGI("GL_MAX_3D_TEXTURE_SIZE = %d\n", my_3d_texture_size);

    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, my_3d_texture_size, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, image));

    GL_CHECK(glViewport(0, 0, width, height));
    glClearColor(0.7, 0.2, 0.8, 0.6);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    GL_CHECK(glGenSamplers(1,&sampler));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER,GL_NEAREST));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER,GL_NEAREST));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE));

    GL_CHECK(glUniform1i(samplerUniform, texUnit));
    GL_CHECK(GL_CHECK(glUseProgram(programID)));
    GL_CHECK(glActiveTexture(GL_TEXTURE0+texUnit));
    GL_CHECK(glBindTexture(GL_TEXTURE_3D,texBufferObject));
    GL_CHECK(glBindSampler(texUnit,sampler));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
        renderFrame();
        string bmp_file  = filename + ".bmp";
        LOGI("bmp_file=%s \n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
    glDeleteSamplers(1,&sampler);
}
int main(int argc, char **argv) {
#ifdef API_ES
    Sample sample(__FILE__);
#else
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
#endif
    sample.test();

    return 0;
}

