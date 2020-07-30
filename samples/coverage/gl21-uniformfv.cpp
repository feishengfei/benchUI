/**
 * @file uniformf.cpp
 * @testpoint glUniform1/2/3/4fv
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vertices[] = { 
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
}; 
GLfloat colors[] = { 
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0
}; 
const float triangleColors2[] =
{
    1.0, 0.0,
    0.0, 1.0,
    0.0, 1.0
};

GLuint shaderProgram, VAOs, Buffers;


const GLchar* vertexShaderSource = "#version 430 core\n"
	"layout(location=0) in vec4 a_v4Position;\n"
	"layout(location=1) in vec4 a_v4FillColor;\n"
	"out vec4 v_v4FillColor;\n"
	"void main()\n" 
	"{\n" 
	"v_v4FillColor = a_v4FillColor;\n"
	"gl_Position = a_v4Position;\n"
	"}\0"; 

const GLchar* fragmentShaderSource = "#version 430 core\n"
	"in vec4 v_v4FillColor;\n"
	"out vec4 FragColor;\n"
	"layout(location=0) uniform mat2x3 cameraProjectionMatrix;\n"
	"void main()\n" 
	"{\n" 
	"vec4 tmpColor = vec4(cameraProjectionMatrix[0][0], cameraProjectionMatrix[0][1], cameraProjectionMatrix[0][2], 0.0);\n" 
	"FragColor = v_v4FillColor + tmpColor;\n"
	"}\n\0"; 

void loadShader(void) {
	GLint  success;
	GLchar infoLog[512];

	shaderProgram = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
	}
}

void setupGraphics(int w, int h)
{
	loadShader();
	GL_CHECK(glGenVertexArrays(1, &VAOs));
	GL_CHECK(glBindVertexArray(VAOs));

	GL_CHECK(glGenBuffers(1, &Buffers));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
	GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glEnableVertexAttribArray(1));
	GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

	glUseProgram(shaderProgram); 
	glViewport(0, 0, w, h);
} 


void renderFrame(void)
{
	GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUseProgram(shaderProgram));
	GL_CHECK(glUniformMatrix2x3fv(0, 1, GL_FALSE, triangleColors2));
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