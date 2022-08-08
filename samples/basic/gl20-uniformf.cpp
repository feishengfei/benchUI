/**
 * @file gl20-uniformf.cpp
 * @testpoint glUniform1/2/3/4f
 *
 */

#include "Sample.h"

unsigned int DisplayMode = GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE;

GLfloat vertices[] = { 
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
}; 
GLfloat colors[] = { 
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f
}; 

GLuint vertexShader, vertexShaderi;
GLuint fragmentShader;
GLuint shaderProgram;
GLint posLocation, colorLocation;
GLint iLocu4f;
GLint iLocu1f;
GLint iLocu2f;
GLint iLocu3f;

const GLchar* vertexShaderSource = "#version 430 core\n"
	"in vec3 position;\n" 
	"in vec4 acolor;\n" 
	"uniform float u1f;\n"
	"uniform vec2 u2f;\n"
	"uniform vec3 u3f;\n"
	"uniform vec4 u4f;\n"
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

void loadShader(void)
{
	GLint success; 
	GLchar infoLog[512]; 

	fragmentShader = loadshadersource(GL_FRAGMENT_SHADER, &fragmentShaderSource);
	vertexShader = loadshadersource(GL_VERTEX_SHADER, &vertexShaderSource); 

	shaderProgram = glCreateProgram(); 
	glAttachShader(shaderProgram, vertexShader); 
	glAttachShader(shaderProgram, fragmentShader); 
	glLinkProgram(shaderProgram); 
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); 
	if (!success) { 
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); 
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
	} 
	posLocation = glGetAttribLocation(shaderProgram, "position");
	colorLocation = glGetAttribLocation(shaderProgram, "acolor");
	printf("Atrrib Location: v=%d, c=%d\n", posLocation, colorLocation);
}

void getdata(void)
{
	GLfloat paramf[4];
	GLsizei length;
	GLint size;
	GLenum type;
	GLchar name[5];

	glGetUniformfv(shaderProgram, iLocu4f, paramf);
	LOGIF("glGetUniformfv: %f, %f, %f, %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetActiveUniform(shaderProgram, iLocu4f, 4, &length, &size, &type, name);
	LOGIF("GetActiveUniform(iLocu4f): length=%d, size=%d, type=%s, name=%s\n", length, size, get_enum_name(type), name);
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

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT); 
	glUseProgram(shaderProgram); 

	iLocu4f = glGetUniformLocation(shaderProgram, "u4f");
	glUniform4f(iLocu4f, 0.0, 1.0, 0.0, 0.0);
	iLocu1f = glGetUniformLocation(shaderProgram, "u1f");
	glUniform1f(iLocu1f, 0.1f);
	iLocu2f = glGetUniformLocation(shaderProgram, "u2f");
	glUniform2f(iLocu2f, 0.1, 0.1);
	iLocu3f = glGetUniformLocation(shaderProgram, "u3f");
	glUniform3f(iLocu3f, 0.1, 0.1, 0.1);

	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)vertices); 
	glEnableVertexAttribArray(posLocation); 
	glEnableVertexAttribArray(colorLocation); 
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), colors); 
	glDrawArrays(GL_TRIANGLES, 0, 3); 
	glFlush();
	getdata();
}

int main(int argc, char** argv)
{
    string file = "gl20-uniformf";
    GBtest_init(&argc,argv,file,DisplayMode);
	string filename = file + ".bmp";
	LOGIF("[]: filename=%s\n", filename.c_str());
	setupGraphics(WINDOW_W, WINDOW_H);
        renderFrame();
	save2bmp(filename.c_str());
	glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
