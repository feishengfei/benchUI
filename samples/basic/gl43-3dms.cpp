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
#define BUFFER_OFFSET(x)  ((const void*) (x))

using std::string;
using namespace BotsonSDK;

static const float Vertices[] = {
     0.7f,  0.5f,  0.0f, 1.0f,
     0.5f, -0.7f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.0f, 1.0f,
    -0.8f, -0.3f,  0.0f, 1.0f
};

GLuint programID;

GLuint  vao, vbo, tex, fbo;

bool setupGraphics(int width, int height) {

    string vertexShaderPath = ((string)GLSL_PATH) + "3dms.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "3dms.frag";
    programID = Shader::CreateProgram (vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glGenTextures(1, &tex));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, tex));
    GL_CHECK(glTexImage3DMultisample(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 4,
                                     GL_RGBA8, 16, 32, 5, 0));
    GL_CHECK(glGenFramebuffers(1, &fbo));
    GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo));

    return true;
}

void renderFrame(void) {
    GLubyte color[5][4]= {
            {102, 127, 204, 255},
            {140, 32, 48, 223},
            {74, 189, 232, 239},
            {214, 72, 239, 87},
            {144, 223, 142, 223}
    };
    for(int i=0; i<5; i++){
        GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo));
        GL_CHECK(glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER,
                                           GL_COLOR_ATTACHMENT0, tex, 0, i));
        GL_CHECK(glClearColor(float(color[i][0])/255.0f,
                              float(color[i][1])/255.0f,
                              float(color[i][2])/255.0f,
                              float(color[i][3])/255.0f));
    }

    GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(vao));
    for(int i=0; i<5; i++){
        GL_CHECK(glUniform1i(0, i));
        GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
        GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    }
}

void Sample::test() {
    glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    GL_CHECK(glEnable(GL_MULTISAMPLE));
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
