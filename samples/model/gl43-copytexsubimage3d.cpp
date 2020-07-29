/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texcopysub3d.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texcopysub3d related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "teximage3d.vert";
string fragmentShaderFilename = "teximage3d.frag";

GLuint programID;

GLuint vao, buffers;
GLuint texBufferObject;

float vertices[] = {
        0,0,0,  1,0,0,  0,1,0,
        1,0,0,  0,1,0,  1,1,0,

        0,0,0,  0,1,0,  0,0,1,
        0,1,0,  0,0,1,  0,1,1,

        0,0,0,  0,0,1,  1,0,0,
        0,0,1,  1,0,0,  1,0,1,

        0,0,1,  0,1,1,  1,0,1,
        0,1,1,  1,0,1,  1,1,1,

        0,1,0,  0,1,1,  1,1,0,
        0,1,1,  1,1,0,  1,1,1,

        1,0,0,  1,0,1,  1,1,0,
        1,0,1,  1,1,0,  1,1,1,
};

#define	iWidth 16
#define	iHeight 16
#define iDepth 16

static GLubyte image[iDepth][iHeight][iWidth][4];
static GLubyte imagesub[iDepth/2][iHeight/2][iWidth/2][4];

void makeImage(void) {
    int s, t, r;
    for (s = 0; s < iWidth; s++)
        for (t = 0; t < iHeight; t++)
            for (r = 0; r < iDepth; r++) {
                image[r][t][s][0] = (GLubyte) (s * 17);
                image[r][t][s][1] = (GLubyte) (t * 17);
                image[r][t][s][2] = (GLubyte) (r * 17);
                image[r][t][s][3] = (GLubyte) (r * 17);
            }
    for (s = 0; s < iWidth/2; s++)
        for (t = 0; t < iHeight/2; t++)
            for (r = 0; r < iDepth/2; r++) {
                imagesub[r][t][s][0] = (GLubyte) (s * 8);
                imagesub[r][t][s][1] = (GLubyte) (t * 8);
                imagesub[r][t][s][2] = (GLubyte) (r * 8);
                imagesub[r][t][s][3] = (GLubyte) (r * 8);
            }
}

bool setupGraphics(int width, int height) {
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor (1.0, 1.0, 1.0, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());


    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                          vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(0));

    glUseProgram(programID);
    makeImage();
    GL_CHECK(glGenTextures(1, &texBufferObject));
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texBufferObject));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER,GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER,GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, iWidth, iHeight, iDepth,
                          0,  GL_RGBA, GL_UNSIGNED_BYTE, image));
    GL_CHECK(glCopyTexSubImage3D(GL_TEXTURE_3D, 0, iWidth/2,0,0,  0,0,
                                 iHeight/2,iWidth/2));

    glEnable(GL_DEPTH_TEST);

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_3D,texBufferObject));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 36));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s\n", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
