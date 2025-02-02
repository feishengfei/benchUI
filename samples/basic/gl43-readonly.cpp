/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file compute-texload.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for compute-texload related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"

using std::string;
using namespace BotsonSDK;

GLuint  input_image, output_image, dst_image;
GLuint  render_vao;
GLuint  render_vbo;

GLuint program, ComputeProgramID;

bool setupGraphics(int width, int height)
{
    string computeShaderPath = (string)GLSL_PATH + "readonly.comp";
    ComputeProgramID = glCreateProgram();
    GLuint ComputeShaderID;

    Shader::processShader(&ComputeShaderID, computeShaderPath.c_str(), GL_COMPUTE_SHADER);
    LOGI("ComputeShaderID = %d\n", ComputeShaderID);
    GL_CHECK(glAttachShader(ComputeProgramID, ComputeShaderID));
    GL_CHECK(glLinkProgram(ComputeProgramID));

    string texturePath = ((string)PICTURE_PATH) + "RotoZoom.raw";
    unsigned char *textureData = NULL;
    Texture::loadData(texturePath.c_str(), &textureData);
    GL_CHECK(glGenTextures(1, &input_image));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, input_image));
    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 256, 256));
    GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGBA,
                             GL_UNSIGNED_BYTE, textureData))

    string vertexShaderPath = (string)GLSL_PATH + "imageStore.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "imageStore.frag";
    program = Shader::CreateProgram (vertexShaderPath.c_str(), fragmentShaderPath.c_str());
   GL_CHECK(glViewport(0, 0, width, height));
   GL_CHECK(glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f ));
   GL_CHECK(glGenVertexArrays(1, &render_vao));
   GL_CHECK(glBindVertexArray(render_vao));
   GL_CHECK(glEnableVertexAttribArray(0));
   GL_CHECK(glGenBuffers(1, &render_vbo));
   GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, render_vbo));
   static const float verts[] =
    {
        -1.0f, -1.0f, 0.5f, 1.0f,
         1.0f, -1.0f, 0.5f, 1.0f,
         1.0f,  1.0f, 0.5f, 1.0f,
        -1.0f,  1.0f, 0.5f, 1.0f,
    };
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL));

    return true;
}

void renderFrame()
{
    GL_CHECK(glGenTextures(1, &output_image));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, output_image));
    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 256, 256));
    GL_CHECK(glBindImageTexture(0, input_image, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F));
    GL_CHECK(glBindImageTexture(1, output_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));
    GL_CHECK(glUseProgram(ComputeProgramID));
    GL_CHECK(glDispatchCompute(8, 16, 1));
    GL_CHECK(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT));

    GL_CHECK(glGenTextures(1, &dst_image));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, dst_image));
    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 256, 256));
    GL_CHECK(glBindImageTexture(0, output_image, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F));
    GL_CHECK(glBindImageTexture(1, dst_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));
    GL_CHECK(glDispatchCompute(8, 16, 1));
    GL_CHECK(glMemoryBarrierByRegion(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT));
 //  GLfloat res[256*256][4];
 //  GL_CHECK(glGetTexImage(GL_TEXTURE_2D, 1, GL_RGBA, GL_FLOAT, &res));
 //  for(int i=0; i<256; i++){
 //      for(int j=0; j<256; j++){
 //          printf("%f-%f-%f-%f  ", res[256*i + j][0], res[256*i + j][1], res[256*i + j][2], res[256*i + j][3]);
 //      }
 //      printf("\n");
 //  }
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(program));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file  = filename + ".bmp";
    LOGI("bmp_file=%s\n", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
