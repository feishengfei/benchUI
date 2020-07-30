/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file depthmask.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for depthmask related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

void failZ(GLfloat expected, GLfloat actual) {
        GLboolean mask;
        glGetBooleanv(GL_DEPTH_WRITEMASK, &mask);
        LOGI("masked-clear: depth buffer value is %f, expected %f\n", actual, expected);
        LOGI("\tGL_DEPTH_WRITEMASK = %s\n", mask ? "GL_TRUE" : "GL_FALSE");
}

bool setupGraphics(int width, int height) {
    GL_CHECK(glViewport(0, 0, width, height));
    return true;
}

GLboolean renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLfloat depth;
    bool passed = true;
    glDepthMask(GL_TRUE);
    glClearDepthf(0.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glClearDepthf(1.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    glReadPixels(4, 4, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    if (depth != 0.0) {
         passed = false;
         failZ(0.0, depth);
    }
    return passed;
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    if(renderFrame()) {
        LOGI("depth mask test PASS !\n");
    } else
        LOGE("depth mask test FAIL !\n");
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
