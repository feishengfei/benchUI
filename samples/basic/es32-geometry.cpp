/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file draw.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for draw related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

GLint iLocPosition = 0, colorLocation = 0;
GLuint programID = 0;

bool setupGraphics(int width, int height)
{
    glEnable( GL_DEPTH_TEST );

    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glViewport( 0, 0, width, height );

    ShaderInfo  shaders[] = {
        {GL_VERTEX_SHADER, "geometry.vert", },
        {GL_GEOMETRY_SHADER, "geometry.geom", },
        {GL_FRAGMENT_SHADER, "geometry.frag", },
        {GL_NONE,NULL},
    };

    programID = Shader::LoadShaders( shaders );
    return true;
}

void renderFrame(void)
{
    float points[] = {
        -0.5f,  0.5f, // 左上
         0.5f,  0.5f, // 右上
         0.5f, -0.5f, // 右下
        -0.5f, -0.5f  // 左下
    };

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glUseProgram( programID );

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "aPos"));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, points));

    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    glDrawArrays( GL_POINTS, 0, 4 );
    //glDrawArrays( GL_PATCHES, 0, 4 );
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
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
