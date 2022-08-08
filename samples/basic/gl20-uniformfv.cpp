/**
 * @file uniformf.cpp
 * @testpoint glUniform1/2/3/4fv
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vertices[] = { 
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
}; 
GLfloat color[] = {
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f
}; 

GLuint shaderProgram, VAOs, Buffers;

const GLchar* vertexShaderSource = "#version 430 core\n"
	"layout(location=0) in vec3 position;\n"
	"layout(location=1) in vec4 acolor;\n"
	"layout(location=0) uniform float u1f;\n"
	"layout(location=1) uniform vec2 u2f;\n"
	"layout(location=2) uniform vec3 u3f;\n"
	"layout(location=3) uniform vec4 u4f;\n"
	"out vec4 vcolor;\n"
	"void main()\n" 
	"{\n" 
	"vcolor = acolor + u4f;\n"
	"float x = position.x + u1f + u2f.x + u3f.x;\n"
	"float y = position.y + u2f.y + u3f.y;\n"
	"float z = position.z + u3f.z;\n"
	"gl_Position = vec4(x, y, z, 1.0);\n" 
	"}\0"; 

const GLchar* fragmentShaderSource = "#version 430 core\n"
	"in vec4 vcolor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
	"{\n" 
	"FragColor = vcolor;\n"
	"}\n\0"; 

void loadShader(void) {
	GLint  success;
	GLchar infoLog[512];
	shaderProgram = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
	LOGI("PROGRAM = %d\n", shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
	}
	GL_CHECK(glGenVertexArrays(1, &VAOs));
	GL_CHECK(glBindVertexArray(VAOs));
	GL_CHECK(glGenBuffers(1, &Buffers));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(color), NULL, GL_STATIC_DRAW));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color), color));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
}

void setupGraphics(int w, int h)
{
	loadShader();
	glUseProgram(shaderProgram); 
	glViewport(0, 0, w, h);
} 


void renderFrame(void)
{
	int i=0;

	GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUseProgram(shaderProgram));

	float u1f[1] = {0.1f};
	float u2f[2] = {0.1, 0.1};
	float u3f[3] = {0.1, 0.1, 0.1};
	float u4f[4] = {0.0, 1.0, 0.0, 0.0};

	GL_CHECK(glUniform1fv(0, 1, u1f));
	GL_CHECK(glUniform2fv(1, 1, u2f));
	GL_CHECK(glUniform3fv(2, 1, u3f));
	GL_CHECK(glUniform4fv(3, 1, u4f));

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
//    string file = "gl20-uniformfv";
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
