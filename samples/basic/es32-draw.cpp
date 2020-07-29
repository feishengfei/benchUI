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

GLuint vaoID;
GLuint EBO;
GLuint VBO;

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

GLint iLocPosition = -1;
GLint iLocFillColor = -1;

static const GLfloat vertex_positions[] = 
{
	0.5f,0.5f,0.0f,1.0f,
	0.5f,-0.5f,0.0f,1.0f,
	-0.5f,-0.5f,0.0f,1.0f,
	-0.5f,0.5f,0.0f,1.0f,
};

static const GLfloat vertex_colors[] =
{
	1.0f,0.0f,1.0f,1.0f,
	0.0f,1.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,
	1.0f,0.0f,1.0f,1.0f
};

static const GLushort vertex_indices[] =
{
	0,1,2,
	0,2,3
};


void ebo_renderFrame()
{
	GLuint vaoId;
	glGenVertexArrays(1,&vaoId);	
	glBindVertexArray(vaoId);

	GLuint vboId;
	glGenVertexArrays(1,&vboId);
	glBindBuffer(GL_ARRAY_BUFFER,vboId);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_positions),vertex_positions,GL_STATIC_DRAW);

	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertex_indices),vertex_indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));
	glBindVertexArray(vaoId);
	glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_SHORT,NULL);
	glBindVertexArray(0);

}

void vbo_renderFrame()
{
	GLuint vboID[2];
	glGenBuffers(2,vboID);
	GLuint positionID = vboID[0];
	GLuint colorID = vboID[1];

	glBindBuffer(GL_ARRAY_BUFFER,positionID);
	glBufferData(GL_ARRAY_BUFFER,9*sizeof(float),vertex_positions,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,colorID);
	glBufferData(GL_ARRAY_BUFFER,9*sizeof(float),vertex_colors,GL_STATIC_DRAW);

	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	glEnableVertexAttribArray(0);//
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER,positionID);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(GLubyte*)NULL);

	glBindBuffer(GL_ARRAY_BUFFER,colorID);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(GLubyte*)NULL);
	
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));
	glBindVertexArray(vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

}

void ebo_DEBV_renderFrame()
{
	GLuint vaoId;
	glGenVertexArrays(1,&vaoId);	
	glBindVertexArray(vaoId);

	GLuint vboId;
	glGenVertexArrays(1,&vboId);
	glBindBuffer(GL_ARRAY_BUFFER,vboId);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_positions),vertex_positions,GL_STATIC_DRAW);

	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertex_indices),vertex_indices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));
	glBindVertexArray(vaoId);
	glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_SHORT,NULL);
	glBindVertexArray(0);

}

void ebo_creat(GLuint ebo)
{
	glGenBuffers(1,&ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertex_indices),vertex_indices,GL_STATIC_DRAW);

}



char* loadS(const char *filename)
{
        FILE *file = fopen(filename, "rb");
        if(file == NULL)
        {
            LOGI("Cannot read file '%s'\n", filename);
            exit(1);
        }

        fseek(file, 0, SEEK_END);

        long length = ftell(file);

        fseek(file, 0, SEEK_SET); 
        char *shader = (char *)calloc(length + 1, sizeof(char));
        if(shader == NULL)
        {
            LOGI("Out of memory at %s:%i\n", __FILE__, __LINE__);
            exit(1);
        }

        size_t numberOfBytesRead = fread(shader, sizeof(char), length, file);
        if (numberOfBytesRead != length) 
        {
            LOGI("Error reading %s (read %d of %d)", filename, numberOfBytesRead, length);
            exit(1);
        }
        shader[length] = '\0';
        fclose(file);

        return shader;
}

void procShader(GLuint *shader, const char *filename, GLint shaderType)
{  
        const char *strings[1] = { NULL };

        *shader = GL_CHECK(glCreateShader(shaderType));
        strings[0] = loadS(filename);
        GL_CHECK(glShaderSource(*shader, 1, strings, NULL));

        free((void *)(strings[0]));
        strings[0] = NULL;

        GL_CHECK(glCompileShader(*shader));
        GLint status;
        GL_CHECK(glGetShaderiv(*shader, GL_COMPILE_STATUS, &status));

        if(status != GL_TRUE) 
        {
            GLint length;
            char *debugSource = NULL;
            char *errorLog = NULL;

            GL_CHECK(glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length));
            debugSource = (char *)malloc(length);
            GL_CHECK(glGetShaderSource(*shader, length, NULL, debugSource));
            LOGI("Debug source START:\n%s\nDebug source END\n\n", debugSource);
            free(debugSource);

            GL_CHECK(glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &length));
            errorLog = (char *)malloc(length);
            GL_CHECK(glGetShaderInfoLog(*shader, length, NULL, errorLog));
            LOGI("Log START:\n%s\nLog END\n\n", errorLog);
            free(errorLog);

            LOGE("Compilation FAILED!\n\n");
            exit(1);
        }
}


void renderFrame(void)
{
	ebo_renderFrame();
}


bool setupGraphics(int width, int height) {
	string vertexShaderPath   = (string)GLSL_PATH + "basic.vert";
	string fragmentShaderPath = (string)GLSL_PATH + "basic.frag";

	procShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
	procShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
	programID                 = GL_CHECK(glCreateProgram());
	if (programID == 0) {
		LOGE("Could not create program.");
		return false;
	}

	GL_CHECK(glAttachShader(programID, vertexShaderID));
	GL_CHECK(glAttachShader(programID, fragmentShaderID));
	glBindAttribLocation(programID, 0, "position");
	glBindAttribLocation(programID, 1, "color");
	GL_CHECK(glLinkProgram(programID));

	glViewport(0, 0, width, height);
	GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
	GL_CHECK(glClearDepthf(1.0f));

	return true;
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

