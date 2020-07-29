/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */


#include "Sample.h"

using std::string;
using namespace BotsonSDK;


GLuint programID, VAOs, Buffers;
GLint iLocPosition = -1;

GLuint texBufferObject;

float vertices[] = {
        0,0,0,  1,0,0,  0,1,0,
        1,0,0,  0,1,0,  1,1,0,
};


#define	iWidth 64
#define	iHeight 64

static GLubyte imageb[iHeight][iWidth][4];

void makeImage(void) {
    int s, t;
    for (s = 0; s < iHeight; s++){
        for (t = 0; t < iWidth; t++) {
            imageb[t][s][0] = (GLubyte)(s * 17);
            imageb[t][s][1] = (GLubyte)(t * 10);
            imageb[t][s][2] = (GLubyte)(s * 17);
            imageb[t][s][3] = (GLubyte)(t * 17);
        }
    }
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath   = (string)GLSL_PATH + "texstorage2d1.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "texstorage2d1.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

    iLocPosition = glGetAttribLocation(programID, "pos");

    glUseProgram(programID);
    makeImage();
    GL_CHECK(glGenTextures(1, &texBufferObject));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texBufferObject));
    GLfloat tmp[4] = {1.0, 1.0, 1.0, 1.0};
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_ZERO));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_ZERO));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA));
    GL_CHECK(glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, tmp));

    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB5_A1, iWidth, iHeight));
    GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, iWidth, iHeight,
                             GL_RGBA, GL_UNSIGNED_BYTE, imageb));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D,texBufferObject));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 6));
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
