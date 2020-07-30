/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file rotozoom.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for rotozoom related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"


using std::string;
using namespace BotsonSDK;

string textureFilename = "RotoZoom.raw";

static const GLubyte quadIndices[] = {
    0, 1, 2, 3,
};

static const float quadVertices[] = {
    -1.0f, -1.0f,  0.0f,
     1.0f, -1.0f,  0.0f,
    -1.0f,  1.0f,  0.0f,
     1.0f,  1.0f,  0.0f,
};

static const float quadTextureCoordinates[] = {
    0.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
};

GLuint programID, ComputeProgramID;;

GLuint  input_image, output_image, dst_image;
int window_Width = -1;
int window_Height = -1;

bool setupGraphics(int width, int height) {
    int textureWidth = 256;
    int textureHeight = 256;
    
    window_Width = width;
    window_Height = height;

    string texturePath = ((string)PICTURE_PATH) + textureFilename;   
    string vertexShaderPath = ((string)GLSL_PATH) + "rotozoom.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "rotozoom.frag";
    programID = Shader::CreateProgram (vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    string computeShaderPath = (string)GLSL_PATH + "readonly.comp";
    ComputeProgramID = glCreateProgram();
    GLuint ComputeShaderID;
    Shader::processShader(&ComputeShaderID, computeShaderPath.c_str(), GL_COMPUTE_SHADER);
    LOGI("ComputeShaderID = %d\n", ComputeShaderID);
    GL_CHECK(glAttachShader(ComputeProgramID, ComputeShaderID));
    GL_CHECK(glLinkProgram(ComputeProgramID));

    unsigned char *textureData = NULL;
    Texture::loadData(texturePath.c_str(), &textureData);
    GL_CHECK(glGenTextures(1, &input_image));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, input_image));
    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 256, 256));
    GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, 256, GL_RGBA,
                             GL_UNSIGNED_BYTE, textureData))

    GL_CHECK(glViewport(0, 0, window_Width, window_Height));
    GL_CHECK(glClearColor(1.0f, 1.0f, 0.0f, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    return true;
}

void renderFrame(void) {
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
    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 256, 256));
    GL_CHECK(glBindImageTexture(0, output_image, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA32F));
    GL_CHECK(glBindImageTexture(1, dst_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F));
    GL_CHECK(glDispatchCompute(8, 16, 1));
    GL_CHECK(glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, quadVertices));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, quadTextureCoordinates));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, input_image));
    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, sizeof(quadIndices) / sizeof(GLubyte),
                            GL_UNSIGNED_BYTE, quadIndices));

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
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
