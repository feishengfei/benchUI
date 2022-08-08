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
GLuint  indirect_bo;
GLuint program, ComputeProgramID;

typedef struct {
    uint num_groups_x;
    uint num_groups_y;
    uint num_groups_z;
}DispatchIndirectCommand;

DispatchIndirectCommand indirect_com[]={4, 8, 1};

bool setupGraphics(int width, int height)
{
    string computeShaderPath = (string)GLSL_PATH + "imageStore.comp";
    ComputeProgramID = glCreateProgram();
    GLuint ComputeShaderID;

    Shader::processShader(&ComputeShaderID, computeShaderPath.c_str(), GL_COMPUTE_SHADER);
    LOGI("ComputeShaderID = %d\n", ComputeShaderID);
    GL_CHECK(glAttachShader(ComputeProgramID, ComputeShaderID));
    GL_CHECK(glLinkProgram(ComputeProgramID));
 
    GL_CHECK(glGenTextures(1, &output_image));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, output_image));
    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, 256, 256));

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
   GL_CHECK(glGenBuffers(1, &indirect_bo));
   GL_CHECK(glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, indirect_bo));
   GL_CHECK(glBufferData(GL_DISPATCH_INDIRECT_BUFFER,2*sizeof(indirect_com),
                         indirect_com, GL_STATIC_DRAW));

    return true;
}

void renderFrame()
{
    GL_CHECK(glUseProgram(ComputeProgramID));
    GL_CHECK(glBindImageTexture(0, output_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));
    GL_CHECK(glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, indirect_bo));
    GL_CHECK(glDispatchComputeIndirect(4));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, output_image));
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
