/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file ftransform
 * @author Martin.li
 * @par History:
 *    A001: Martin.li, 20XX-XX-XX, Add commit
 * @
 * @par TestPoints:
 *
 */
///===================================================================================
#include "Sample.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

float vertices_data[] = {
		-0.8, 0.0, 1.0,
		-0.6, 0.6, 0.9, 
		0.0, 0.8,  0.8,
		0.6, 0.6,  0.7,
		0.8, 0.0,  0.6,
        	0.6, -0.6, 0.5,
		0.0, -0.8, 0.4,
		-0.6, -0.6,0.1
};

GLenum factor[]={
GL_POINTS,
};

GLuint programID;
GLint iLocPosition = -1;
GLuint vao;
GLuint vertices_bo;

bool setupGraphics(int w, int h)
{

    string path = "gl43_pointSize";
	string vertexShaderPath = (string)GLSL_PATH + path + "/base-green.vert";
	string fragmentShaderPath = (string)GLSL_PATH + path + "/base-green.frag";

	programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
	GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
	GL_CHECK(glViewport(0, 0, w, h));

	GL_CHECK(glGenVertexArrays(1, &vao));
	GL_CHECK(glBindVertexArray(vao));
	GL_CHECK(glGenBuffers(1, &vertices_bo));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertices_bo));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_data), vertices_data, GL_STATIC_DRAW));
	GL_CHECK(glEnableVertexAttribArray(iLocPosition));
	GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, 0));

	GL_CHECK(glBindVertexArray(0));

	return true;
}
///===========================================================================================

void renderFrame(GLenum factor)
{
	GL_CHECK(glClearColor(0,0,1,1));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
        GL_CHECK(glUseProgram(programID));

	GL_CHECK(glBindVertexArray(vao));

        GL_CHECK(glPointSize(10.0))
	GL_CHECK(glDrawArrays(factor,0,8));
}
///===========================================================================================

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
        for(int i=0; i<ARRAY_NUM(factor); i++) {
                string bmp_file = filename + "-" + get_primitives_name(factor[i]) + ".bmp";
		renderFrame(factor[i]);
		LOGI("bmp_file=%s", bmp_file.c_str());
		save2bmp(bmp_file.c_str());
		SwapBuffers();
        }
}

int main(int argc, char **argv) {

    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE, argc,argv);

    sample.test();

    return 0;
}
