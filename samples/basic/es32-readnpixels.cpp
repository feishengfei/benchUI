/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file readnpixels.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for readnpixels related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

bool setupGraphics(int w, int h)
{
    glViewport(0,0,w,h);
    GL_CHECK(glClearColor(1.0, 0.0, 0.5, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void render() {
    int     width   = 2, height = 2;
    GLubyte *readPixelBuffer;
    GLubyte *tmp;
    GLsizei bufSize = width * height * sizeof(GLubyte) * 4;
    readPixelBuffer = (GLubyte *)malloc(bufSize);
    tmp             = readPixelBuffer;
    GL_CHECK(glReadnPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, bufSize, readPixelBuffer));
    LOGI("pixel: %d %d\n", width, height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            LOGI("[%d][%d]: %d %d %d %d\n", i, j, *(tmp), *(tmp++), *(tmp++), *(tmp++));
        }
    }
    free(readPixelBuffer);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    render();
    string bmp_file  = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
