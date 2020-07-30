/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file feedback-seperate.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for feedback-seperate related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "TransformFeedback.vert";
string fragmentShaderFilename = "TransformFeedback.frag";

GLubyte indices[] = {0,1,2};
GLubyte subdata[] = {1,3};

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
#define NUM 6
const GLchar *feedbackVaryings[]={"outValue", "v3"};
GLuint vao;
GLfloat data[NUM]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
float v3[] = {0.55, 0.66, 0.77};
GLuint readbuffer;
GLuint writebuffer[2];
GLuint query;
GLint inputAttrib=0;
GLuint tansFDid=0;

void initVBO() {
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	glGenBuffers(1,&readbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, readbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	inputAttrib=glGetAttribLocation(programID, "inValue");
	glEnableVertexAttribArray(inputAttrib);
	glVertexAttribPointer(inputAttrib, 1, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(2,writebuffer);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, writebuffer[0]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(data), NULL, GL_STATIC_READ);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, writebuffer[1]);
	glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(v3), NULL, GL_STATIC_READ);

	glGenQueries(1, &query);
}

void getFBdata() {
	GLint bufSize=9;
	int length=0;
	int size=0;
	GLenum type;
	char name[10];
	GLboolean isTFFB;
	GLint parami;

	isTFFB = GL_CHECK(glIsTransformFeedback(tansFDid));
	LOGI("glIsTransformFeedback:%d\n",isTFFB);
	GL_CHECK(glGetIntegerv(GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS,&parami));
	LOGI("GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS: %d\n",parami);
	GL_CHECK(glGetProgramiv(programID,GL_TRANSFORM_FEEDBACK_VARYINGS,&parami));
	LOGI("GL_TRANSFORM_FEEDBACK_VARYINGS: %d\n",parami);
	GL_CHECK(glGetProgramiv(programID,GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,&parami));
	LOGI("GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH: %d\n",parami);
	GL_CHECK(glGetTransformFeedbackVarying(programID,0,bufSize,&length,&size,&type,name));
	LOGI("glGetTransformFeedbackVarying: length=%d, size=%d, type=0x%x, name=%s\n",length,size,type,name);
}

bool setupGraphics(int w, int h) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
	
    programID = glCreateProgram();
    if (programID == 0) {
	LOGE("Could not create program.");
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));

    GL_CHECK(glGenTransformFeedbacks(1,&tansFDid));
    GL_CHECK(glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tansFDid));
	
    GL_CHECK(glTransformFeedbackVaryings(programID,1,feedbackVaryings,GL_INTERLEAVED_ATTRIBS));
    GL_CHECK(glLinkProgram(programID));
    getFBdata(); 
    GLint linkStatus=GL_FALSE;
    GL_CHECK(glGetProgramiv(programID,GL_LINK_STATUS,&linkStatus));
    if(linkStatus==GL_FALSE) {
	LOGE("link error: %x\n",linkStatus);
    }
    
    GL_CHECK(glValidateProgram(programID));
    GL_CHECK(glGetProgramiv(programID,GL_VALIDATE_STATUS,&linkStatus));
    if(linkStatus==0) {
	LOGE("validate error\n");
    }
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    initVBO();

    return true;
}

void getdata() {
	GLint parami;
	GLint64 getdata64;
	GLvoid * params;
	GLuint primitives;

	glGetProgramiv(programID,GL_TRANSFORM_FEEDBACK_BUFFER_MODE,&parami);
	LOGI("GL_TRANSFORM_FEEDBACK_BUFFER_MODE: %x\n",parami);
	glGetQueryObjectuiv(query, GL_QUERY_RESULT, &primitives);
	LOGI("primitives:%d\n",primitives);
	glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_ACCESS_FLAGS,&parami);
	LOGI("GetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_ACCESS_FLAGS):%d\n",parami);
	glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_MAPPED,&parami);
	LOGI("GetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_MAPPED):%d\n",parami);
	glGetBufferParameteri64v(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_MAP_LENGTH,&getdata64);
	LOGI("glGetBufferParameteri64v(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_MAP_LENGTH):%d\n",getdata64);
	glGetBufferParameteri64v(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_MAP_OFFSET,&getdata64);
	LOGI("glGetBufferParameteri64v(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_MAP_OFFSET):%d\n",getdata64);
	glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_SIZE,&parami);
	LOGI("GetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_SIZE):%d\n",parami);
	glGetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_USAGE,&parami);
	LOGI("GetBufferParameteriv(GL_TRANSFORM_FEEDBACK_BUFFER,GL_BUFFER_USAGE):%d\n",parami);
	glGetBufferPointerv(GL_TRANSFORM_FEEDBACK_BUFFER, GL_BUFFER_MAP_POINTER, &params);
	LOGI("GetBufferPointerv(GL_TRANSFORM_FEEDBACK_BUFFER):%x\n",params);
}

void renderFrame(void) {
	glEnable(GL_RASTERIZER_DISCARD);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, writebuffer[0]);
	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query);
	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, NUM);
	glEndTransformFeedback();
	glBeginTransformFeedback(GL_LINES);
	glPauseTransformFeedback();
	glDrawArrays(GL_LINES, 0, NUM);
	glEndTransformFeedback();
	glBeginTransformFeedback(GL_TRIANGLES);
	glResumeTransformFeedback();
	glDrawArrays(GL_TRIANGLES, 0, NUM);
	glEndTransformFeedback();
	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	glDisable(GL_RASTERIZER_DISCARD);
	glFlush();

	GLfloat *feedback;
	glBindBuffer(GL_ARRAY_BUFFER, writebuffer[0]);
	feedback = (GLfloat *)glMapBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(data), GL_MAP_READ_BIT);
	if (!feedback) {
		LOGI("feedback == NULL\n");
	}
	for (int i = 0; i < NUM; i++) {
		LOGI("%f\n", *(feedback + i));
	}
	getdata();
	if (glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER) == GL_FALSE) {
		LOGE("Error unmapping array buffer object.");
	}
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, writebuffer[2]);
	feedback = (GLfloat *)glMapBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(v3), GL_MAP_READ_BIT);
	if (!feedback) {
		LOGI("feedback == NULL\n");
	}
	for (int i = 0; i < NUM; i++) {
		LOGI("%f\n", *(feedback + i));
	}
	getdata();
	if (glUnmapBuffer(GL_TRANSFORM_FEEDBACK_BUFFER) == GL_FALSE) {
		LOGE("Error unmapping array buffer object.");
	}
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	renderFrame();
	string bmp_file    = filename + ".bmp";
	save2bmp(bmp_file.c_str());

	glDeleteQueries(1, &query);
	glDeleteBuffers(2, writebuffer);
	glDeleteBuffers(1, &readbuffer);
	glDeleteVertexArrays(1, &vao);
	glDeleteTransformFeedbacks(1, &tansFDid);
}

int main(int argc, char **argv) {
	Sample sample(__FILE__);

	sample.test();

	return 0;
}
