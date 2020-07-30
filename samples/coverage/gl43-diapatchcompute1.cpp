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

using std::string;
using namespace BotsonSDK;

GLuint  output_image;
GLuint  render_vao;
GLuint  render_vbo;

GLuint program, ComputeProgramID;
static const GLenum interfmt[] = {
        GL_RGBA32F,
        GL_RGBA16F,
        GL_RG32F,
        GL_RG16F,
        GL_R11F_G11F_B10F,
        GL_R16F,
        GL_RGBA16,
        GL_RGB10_A2,
        GL_RG16,
        GL_RG8,
        GL_R16,
        GL_R8,
        GL_RGBA16_SNORM,
        GL_RGBA8_SNORM,
        GL_RG16_SNORM,
        GL_RG8_SNORM,
        GL_R16_SNORM,
        GL_R8_SNORM,
        GL_RGBA32I,
        GL_RGBA16I,
        GL_RGBA8I,
        GL_RG32I,
        GL_RG16I,
        GL_RG8I,
        GL_R16I,
        GL_R8I,
        GL_RGBA32UI,
        GL_RGBA16UI,
        GL_RGB10_A2UI,
        GL_RGBA8UI,
        GL_RG32UI,
        GL_RG16UI,
        GL_RG8UI,
        GL_R16UI,
        GL_R8UI
};

bool setupGraphics(int width, int height, int i)
{
    string computeShaderPath[36];
    computeShaderPath[0]= (string)GLSL_PATH + "imageStore.comp";
    computeShaderPath[1]= (string)GLSL_PATH + "imageStore1.comp";
    computeShaderPath[2]= (string)GLSL_PATH + "imageStore2.comp";
    computeShaderPath[3]= (string)GLSL_PATH + "imageStore3.comp";
    computeShaderPath[4]= (string)GLSL_PATH + "imageStore4.comp";
    computeShaderPath[5]= (string)GLSL_PATH + "imageStore5.comp";
    computeShaderPath[6]= (string)GLSL_PATH + "imageStore6.comp";
    computeShaderPath[7]= (string)GLSL_PATH + "imageStore7.comp";
    computeShaderPath[8]= (string)GLSL_PATH + "imageStore8.comp";
    computeShaderPath[9]= (string)GLSL_PATH + "imageStore9.comp";
    computeShaderPath[10]= (string)GLSL_PATH + "imageStore10.comp";
    computeShaderPath[11]= (string)GLSL_PATH + "imageStore11.comp";
    computeShaderPath[12]= (string)GLSL_PATH + "imageStore12.comp";
    computeShaderPath[13]= (string)GLSL_PATH + "imageStore13.comp";
    computeShaderPath[14]= (string)GLSL_PATH + "imageStore14.comp";
    computeShaderPath[15]= (string)GLSL_PATH + "imageStore15.comp";
    computeShaderPath[16]= (string)GLSL_PATH + "imageStore16.comp";
    computeShaderPath[17]= (string)GLSL_PATH + "imageStore17.comp";
    computeShaderPath[18]= (string)GLSL_PATH + "imageStore18.comp";
    computeShaderPath[19]= (string)GLSL_PATH + "imageStore19.comp";
    computeShaderPath[20]= (string)GLSL_PATH + "imageStore20.comp";
    computeShaderPath[21]= (string)GLSL_PATH + "imageStore21.comp";
    computeShaderPath[22]= (string)GLSL_PATH + "imageStore22.comp";
    computeShaderPath[23]= (string)GLSL_PATH + "imageStore23.comp";
    computeShaderPath[24]= (string)GLSL_PATH + "imageStore24.comp";
    computeShaderPath[25]= (string)GLSL_PATH + "imageStore25.comp";
    computeShaderPath[26]= (string)GLSL_PATH + "imageStore26.comp";
    computeShaderPath[27]= (string)GLSL_PATH + "imageStore27.comp";
    computeShaderPath[28]= (string)GLSL_PATH + "imageStore28.comp";
    computeShaderPath[29]= (string)GLSL_PATH + "imageStore29.comp";
    computeShaderPath[30]= (string)GLSL_PATH + "imageStore30.comp";
    computeShaderPath[31]= (string)GLSL_PATH + "imageStore31.comp";
    computeShaderPath[32]= (string)GLSL_PATH + "imageStore32.comp";
    computeShaderPath[33]= (string)GLSL_PATH + "imageStore33.comp";
    computeShaderPath[34]= (string)GLSL_PATH + "imageStore34.comp";
    computeShaderPath[35]= (string)GLSL_PATH + "imageStore35.comp";

    ComputeProgramID = glCreateProgram();
    GLuint ComputeShaderID;

    Shader::processShader(&ComputeShaderID, computeShaderPath[i].c_str(), GL_COMPUTE_SHADER);
    LOGI("ComputeShaderID = %d\n", ComputeShaderID);
    GL_CHECK(glAttachShader(ComputeProgramID, ComputeShaderID));
    GL_CHECK(glLinkProgram(ComputeProgramID));
 
    GL_CHECK(glGenTextures(1, &output_image));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, output_image));
    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 256, 256));

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
    GL_CHECK(glUseProgram(ComputeProgramID));
    GL_CHECK(glBindImageTexture(0, output_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));
    GL_CHECK(glDispatchCompute(8, 16, 1));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, output_image));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(program));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));
}

void Sample::test() {
    for (int i = 0; i < 36; i++) {
        setupGraphics(WINDOW_W, WINDOW_H, i);
        renderFrame();
        char ss[3];
        sprintf(ss, "%d", i);
        string bmp_file = filename + "-" + ss + ".bmp";
        LOGI("bmp_file=%s\n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
