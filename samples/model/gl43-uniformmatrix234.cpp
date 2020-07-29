/**
 * @file gl20-uniformmatrix.cpp
 * @testpoint glUniformMatrix2/3/4fv
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vertices[] = { 
	0.0f, 0.5f,
	0.5f, 0.0f
	-0.2f, 0.0f
}; 

GLfloat colors[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f
}; 

GLuint shaderProgram, VAOs, Buffers;;

const GLchar* vertexShaderSource = "#version 430 core\n"
	"layout(location=0) in vec2 pos;\n"
	"layout(location=1) in vec4 acolor;\n"
	"layout(location=0) uniform mat2x4 u24m;\n"
	"layout(location=1) uniform mat3x4 u34m;\n"
	"layout(location=4) uniform mat4x2 u42m;\n"
	"layout(location=6) uniform mat4x3 u43m;\n"
	"out vec4 vcolor;\n"
	"void main()\n" 
	"{\n" 
	"vcolor =acolor;\n"
	"float a = u24m[0][0] + u24m[1][1];\n"
	"float b = u34m[0][0] + u34m[1][1] + u34m[2][2];\n"
	"float c = u42m[0][0] + u42m[3][1];\n"
	"float d = u43m[0][0] + u43m[1][1] + u43m[2][2];\n"
	"gl_Position = vec4(pos.x+a+d, pos.y+b-d, c, 1.0);\n"
	"}\0";

const GLchar* fragmentShaderSource = "#version 430 core\n"
	"in vec4 vcolor;\n"
	"out vec4 FragColor;\n"
	"void main()\n" 
	"{\n" 
	"FragColor = vcolor;\n"
	"}\n\0"; 

void loadShader(void) {

	shaderProgram = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

}

void setupGraphics(int w, int h)
{
	loadShader();
    GL_CHECK(glUseProgram(shaderProgram));
    GL_CHECK(glViewport(0, 0, w, h));
} 

void renderFrame(void)
{

	GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUseProgram(shaderProgram));

	float u24m[] = {
	-1.2, 0.0, 0.0, 1.0,
	0.0, 0.5, 0.8, 0.0
	};
    GL_CHECK(glUniformMatrix2x4fv(0, 1, GL_FALSE, u24m));
	float u34m[] = {
	1.0, 0.0, 0.2, 0.5,
	0.0, -2.5, 0.2, 0.6,
	0.0, 0.0, 1.0, 0.7
	};
    GL_CHECK(glUniformMatrix3x4fv(1, 1, GL_FALSE, u34m));
	float u42m[] = {
	0.5, 1.0,
	1.0, 0.0,
	0.0, 0.0,
	0.0, -0.2
	};
	GL_CHECK(glUniformMatrix4x2fv(4, 1, GL_FALSE, u42m));
	float u43m[] = {
			0.5, 1.0, 0.3,
			1.0, -1.0, 0.5,
			0.0, 0.0, 0.7,
			0.0, -0.2, 0.8
	};
	GL_CHECK(glUniformMatrix4x3fv(6, 1, GL_FALSE, u43m));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
	GL_CHECK(glFlush());
}


void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	string bmp_file  = filename + ".bmp";
	LOGI("[]: filename=%s\n", bmp_file.c_str());
	renderFrame();
	save2bmp(bmp_file.c_str());
	SwapBuffers();

}

int main(int argc, char **argv) {
	Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
	sample.test();
	return 0;
}


//int main(int argc, char** argv)
//{
//    string file = "gl20-uniformmatrix";
//    GBtest_init(&argc,argv,file,DisplayMode);
//	string filename = file + ".bmp";
//	LOGIF("[]: filename=%s\n", filename.c_str());
//	setupGraphics(WINDOW_W, WINDOW_H);
//        renderFrame();
//	save2bmp(filename.c_str());
//	glutSwapBuffers();
//    GBtest_deinit();
//
//    return 0;
//}
