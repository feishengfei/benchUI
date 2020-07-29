/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file test.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-11-18, Add commit
 * @brief basic test for related API
 * @par TestPoints:
        glBlendEquationSeparatei
        glBlendFuncSeparatei
 *
 */

#include "Sample.h"

using namespace BotsonSDK;

GLfloat vertices[] = { 
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
}; 
GLfloat colors[] = { 
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f
};
GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;
GLint posLocation=2, colorLocation;

void setupGraphics(int w, int h)
{
    ShaderInfo shaders[3] = {
        {GL_VERTEX_SHADER, "basic.vert", },
        {GL_FRAGMENT_SHADER, "basic.frag", },
        {GL_NONE,NULL},
    };
    shaderProgram = Shader::LoadShaders(shaders);
	posLocation = glGetAttribLocation(shaderProgram, "position");
	colorLocation = glGetAttribLocation(shaderProgram, "acolor");

    GL_CHECK(glShadeModel(GL_FLAT));
	glUseProgram(shaderProgram); 
	glViewport(0, 0, w, h);
} 


void renderFrame()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glUseProgram(shaderProgram); 

	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)vertices); 
	glEnableVertexAttribArray(posLocation); 
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), colors); 

	glDrawArrays(GL_TRIANGLES, 0, 3); 
	glDisableVertexAttribArray(posLocation);
	glDisableVertexAttribArray(colorLocation);
	glDeleteProgram(shaderProgram);
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("%s\n", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}

