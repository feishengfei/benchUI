/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file readpixels.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for readpixels related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

const GLubyte indices[] = {0,1,2};

string vertexShaderFilename = "ReadPixels.vert";
string fragmentShaderFilename = "ReadPixels.frag";
GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint pbo;

#define W 2
#define H 2
GLchar pixels[W][H][4];

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    programID = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    LOGI("glGetAttribLocation(\"a_v4Position\") = %d\n", iLocPosition);

    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));
    LOGI("glGetAttribLocation(\"a_v4FillColor\") = %d\n", iLocFillColor);

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    GL_CHECK(glGenBuffers(1, &pbo));
    GL_CHECK(glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo));
    GL_CHECK(glBufferData(GL_PIXEL_PACK_BUFFER, W*H*sizeof(char)*4,NULL, 
                          GL_STREAM_READ));
    GL_CHECK(glPixelStorei(GL_PACK_ALIGNMENT, 1));
    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0,
                                   triangleVertices));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    if (iLocFillColor != -1) {
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0,
                                       triangleColors));
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }
    GL_CHECK(glDrawRangeElements(GL_TRIANGLES, 0, 2, 3, GL_UNSIGNED_BYTE, indices));
    glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
    glReadPixels(WINDOW_W / 2, WINDOW_H / 2, W, H, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    void *map = glMapBufferRange(GL_PIXEL_PACK_BUFFER, 0, W * H * sizeof(char) * 4,
                                 GL_MAP_READ_BIT);
    if (map != NULL) {
        memcpy(pixels, map, W * H * sizeof(char) * 4);
    } else {
        LOGE("Error mapping vertex buffer object.");
    }
    glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    for(int i=0; i<W; i++)
    {
        for(int j=0; j<W; j++)
        {
            LOGI("%d,%d,%d,%d\n",pixels[i][j][0],pixels[i][j][1],pixels[i][j][2],pixels[i][j][3]);
        }
    }

    GLint getdata;
    GLint64 getdata64;
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER,GL_BUFFER_ACCESS_FLAGS,&getdata);
    LOGI("GetBufferParameteriv(GL_PIXEL_PACK_BUFFER,GL_BUFFER_ACCESS_FLAGS):%d\n", getdata);
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER,GL_BUFFER_MAPPED,&getdata);
    LOGI("GetBufferParameteriv(GL_PIXEL_PACK_BUFFER,GL_BUFFER_MAPPED):%d\n",getdata);
    glGetBufferParameteri64v(GL_PIXEL_PACK_BUFFER,GL_BUFFER_MAP_LENGTH,&getdata64);
    LOGI("glGetBufferParameteri64v(GL_PIXEL_PACK_BUFFER,GL_BUFFER_MAP_LENGTH):%d\n",getdata64);
    glGetBufferParameteri64v(GL_PIXEL_PACK_BUFFER,GL_BUFFER_MAP_OFFSET,&getdata64);
    LOGI("glGetBufferParameteri64v(GL_PIXEL_PACK_BUFFER,GL_BUFFER_MAP_OFFSET):%d\n",getdata64);
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER,GL_BUFFER_SIZE,&getdata);
    LOGI("GetBufferParameteriv(GL_PIXEL_PACK_BUFFER,GL_BUFFER_SIZE):%d\n",getdata);
    glGetBufferParameteriv(GL_PIXEL_PACK_BUFFER,GL_BUFFER_USAGE,&getdata);
    LOGI("GetBufferParameteriv(GL_PIXEL_PACK_BUFFER,GL_BUFFER_USAGE):%d\n",getdata);
    GLvoid * params;
    glGetBufferPointerv(GL_PIXEL_PACK_BUFFER, GL_BUFFER_MAP_POINTER, &params);
    LOGI("GetBufferPointerv(GL_PIXEL_PACK_BUFFER):%x\n",params);
    glGenBuffers(1, &pbo);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
