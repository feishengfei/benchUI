/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file patchparameteri.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for patchparameteri related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

#define BUFFER_OFFSET(offset) ((GLvoid *) NULL + offset)
GLuint  PLoc;

const GLfloat  zNear = 1.0;
const GLfloat  zFar  = 3.0;

const int  NumVertices = 4;

GLuint programID;

bool setupGraphics(int width, int height)
{
    enum { Patch, NumVAOs };
    GLuint VAOs[NumVAOs];
    glGenVertexArrays( NumVAOs, VAOs );
    glBindVertexArray( VAOs[Patch] );

    enum { Array, NumBuffers };
    GLuint buffers[NumBuffers];
    glGenBuffers( NumBuffers, buffers );
    glBindBuffer( GL_ARRAY_BUFFER, buffers[Array] );
    
    GLfloat vertices[NumVertices][2] = {
	{ -0.5, -0.5 },
	{  0.5, -0.5 },
	{  0.5,  0.5 },
	{ -0.5,  0.5 }
    };
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    ShaderInfo  shaders[] = {
	{ GL_VERTEX_SHADER,          "simple.vert" },
	{ GL_TESS_CONTROL_SHADER,    "simple.cont" },
 	{ GL_TESS_EVALUATION_SHADER, "simple.eval" },
 	{ GL_FRAGMENT_SHADER,        "simple.frag" },
	{ GL_NONE, NULL }
    };

    GLuint program = Shader::LoadShaders( shaders );
    glUseProgram( program );

    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );
    
    glPatchParameteri( GL_PATCH_VERTICES, 4 );

    glEnable( GL_DEPTH_TEST );

    glClearColor( 0.0, 1.0, 0.0, 1.0 );
    glViewport( 0, 0, width, height );

    return true;
}

void renderFrame(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDrawArrays( GL_PATCHES, 0, NumVertices );
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
