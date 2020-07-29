/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texstorage2d.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texstorage2d related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;
GLuint programID, VAOs, Buffers;

GLuint tex[2];

float vertices[] = {
        -1,-1,0,  1,-1,0,  -1,1,0,
        1,-1,0,  -1,1,0,  1,1,0,
};

#define	iWidth 4
#define	iHeight 4

static GLfloat imagef[iHeight][iWidth][4];

void makeImage(void) {
    int s, t, r;

    for (s = 0; s < iHeight; s++)
        for (t = 0; t < iWidth; t++) {
            imagef[t][s][0] = (GLfloat)(s*2);
            imagef[t][s][1] = (GLfloat)(t*10);
            imagef[t][s][2] = (GLfloat)(s*17);
            imagef[t][s][3] = (GLfloat)(t*17);
        }
}


bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + "texstorage2d.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "texstorage2d.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

    glUseProgram(programID);
    makeImage();
    GL_CHECK(glGenTextures(2, &tex[0]));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, tex[0]));

    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1,  GL_RGBA16F, iWidth, iHeight));
    GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, iWidth, iHeight,
                             GL_RGBA, GL_FLOAT, imagef));
   GLfloat res[4][4][4];
   GL_CHECK(glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, res));
   for(int i=0; i<4; i++){
       for(int j=0; j<4; j++){
           for(int k=0; k<4; k++){
               printf("%f-", res[i][j][k]);
           }
           printf("    ");
       }
       printf("\n");
   }

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor (0.5, 0.2, 1.0, 1.0));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D,tex[0]));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file  = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
