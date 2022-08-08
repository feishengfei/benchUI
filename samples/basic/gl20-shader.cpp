/**
 * @file gl20-shader.cpp
 * @testpoint shader related API
 *  include:
 *  glBindAttribLocation
 **/

#include "gl-util.h"
#include "Shader.h"
#include <limits.h>

using namespace BotsonSDK;
unsigned int DisplayMode = GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE;

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

int main(int argc, char** argv)
{
    string file = "gl20-shader";
    GBtest_init(&argc,argv,file,DisplayMode);
	string filename = file + ".bmp";
	LOGIF("filename=%s\n", filename.c_str());
	setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
	save2bmp(filename.c_str());
	glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
