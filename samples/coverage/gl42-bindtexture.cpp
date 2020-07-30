/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */


#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint  output_image;

GLuint  render_vao;
GLuint  render_vbo;
static GLfloat imagef[16][16][4];
GLuint program;

void makeImage(void) {
    int s, t;
    for (s = 0; s < 16; s++) {
        for (t = 0; t < 16; t++) {
            imagef[t][s][0] = (GLfloat)(s * 17);
            imagef[t][s][1] = (GLfloat)(t * 17);
            imagef[t][s][2] = (GLfloat)(s * 17);
            imagef[t][s][3] = (GLfloat)(t * 17);
        }
    }
}

bool setupGraphics(int width, int height) {

    string vertexShaderPath   = (string)GLSL_PATH + "bindtexture.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "bindtexture.frag";
    program = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    GL_CHECK(glUseProgram(program));

    makeImage();
    GL_CHECK(glGenTextures(1, &output_image));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, output_image));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RG16F, 16, 16));
    GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 16, 16,
                             GL_RG, GL_FLOAT, imagef));
    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 0.0f));
    GL_CHECK(glGenVertexArrays(1, &render_vao));
    GL_CHECK(glBindVertexArray(render_vao));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glGenBuffers(1, &render_vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, render_vbo));
    static const float verts[] =
                               {
                                       -1.0f, -1.0f, 0.5f, 1.0f,
                                       1.0f, -1.0f, 0.5f, 1.0f,
                                       1.0f, 1.0f, 0.5f, 1.0f,
                                       -1.0f, 1.0f, 0.5f, 1.0f,
                               };
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL));

    return true;
}

void renderFrame()
{
    GL_CHECK(glBindImageTexture(0, output_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RG16F));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, output_image));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(program));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));
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
