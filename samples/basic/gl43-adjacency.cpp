/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texsub.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for texsub related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;



#define BUFFER_OFFSET(i) ((char *)NULL + (i))

GLuint programID;

bool setupGraphics(int w, int h) {

    ShaderInfo  shaders[] = {
            { GL_VERTEX_SHADER,  "adjacency.vert" },
            { GL_GEOMETRY_SHADER, "adjacency.gemo" },
            { GL_FRAGMENT_SHADER, "adjacency.frag" },
            { GL_NONE, NULL }
    };

    programID = Shader::LoadShaders( shaders );

    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(0.1f, 0.3f, 0.0f, 1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDrawArrays(GL_LINES_ADJACENCY, 0, 4));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

