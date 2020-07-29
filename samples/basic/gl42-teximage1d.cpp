/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */


#include "Sample.h"

using std::string;
using namespace BotsonSDK;


GLuint programID, VAOs, Buffers;
#define DATA_TRANS(x)  ((const void*) (x))
GLuint texBufferObject;

float vertices[] = {
        -1,-1,0,  1,-1,0,  -1,1,0,
        1,-1,0,  -1,1,0,  1,1,0
};


#define	iWidth 400

static GLubyte imageb[iWidth][4];

void makeImage(void) {
    int t;
    for (t = 0; t < iWidth; t++) {
        imageb[t][0] = (GLubyte)(t * 0);
        imageb[t][1] = (GLubyte)(t * 8);
        imageb[t][2] = (GLubyte)(t * 8);
        imageb[t][3] = (GLubyte)(t * 16);
    }
}

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + "texstorage1d.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "texstorage1d.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

    glUseProgram(programID);
    makeImage();
    GL_CHECK(glGenTextures(1, &texBufferObject));
    GL_CHECK(glBindTexture(GL_TEXTURE_1D, texBufferObject));
    GL_CHECK(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER,GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER,GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA8_SNORM, iWidth, 0, GL_RGBA, GL_BYTE, DATA_TRANS(imageb)))
    GL_CHECK(glCopyTexSubImage1D(GL_TEXTURE_1D, 0, 100, 100, 100, 100));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor (0.0, 0.0, 0.0, 0.0));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_1D,texBufferObject));
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
