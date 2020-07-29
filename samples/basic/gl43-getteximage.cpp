/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl43-getteximage.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2020-04-08, create file
 * @par TestPoints:
 *      glGetTexImage
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

GLuint textureID = 0;
GLuint programID;
GLuint buf;

bool setupGraphics()
{
    char vShaderStr[] =
      "#version 430 core                            \n"
      "in vec4 a_position;   \n"
      "in vec2 a_texcoord;   \n"
      "out vec2 texcoord;   \n"
      "void main()                                \n"
      "{                                          \n"
      "   gl_Position = a_position;               \n"
      "   texcoord = a_texcoord;               \n"
      "}                                          \n";

    char fShaderStr[] =
       "#version 430 core                                     \n"
       "precision mediump float;                            \n"
       "out vec4 fragColor;                                 \n"
       "in vec2 texcoord;   \n"
       "uniform sampler2D u_s2dTexture;   \n"
       "void main()                                         \n"
       "{                                                   \n"
       "  fragColor = texture2D(u_s2dTexture, texcoord);    \n"
       "}                                                   \n";
   
    programID = Shader::createProgramFromString ( vShaderStr, fShaderStr );
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );

    GLubyte textureData[4][3] = {
        {255, 0, 0},
        {0, 255, 0},
        {255, 0, 0},
        {0, 255, 0}
    };

    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData));

    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

    return true;
}

void renderFrame(void) {
    float vertices[] = {
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
    };

    float texcoords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
    };
    
    GL_CHECK(glUseProgram(programID));
    GLuint locTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_texcoord"));
    GLuint locPosition = GL_CHECK(glGetAttribLocation(programID, "a_position"));
    GLuint locTexture = GL_CHECK(glGetAttribLocation(programID, "u_s2dTexture"));
    GL_CHECK(glUniform1i(locTexture, 0));
    GL_CHECK(glVertexAttribPointer(locPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));
    GL_CHECK(glVertexAttribPointer(locTexCoord, 2, GL_FLOAT, GL_FALSE, 0, texcoords));
    GL_CHECK(glEnableVertexAttribArray(locPosition));
    GL_CHECK(glEnableVertexAttribArray(locTexCoord));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
}

void Sample::test() {
    setupGraphics();
    renderFrame();
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

