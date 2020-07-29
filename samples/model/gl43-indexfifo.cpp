
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

float Tstrip0[0];

float Tstrip1[] = {0.2, 0.0, 0.0};

float Tstrip4[] =
			  {
					  0.6,  -0.2, 0.0,
					  0.7,  -0.8, 0.0,
					  0.8,  -0.2, 0.0,
					  0.9,  -0.8, 0.0,
			  };

float Tstrip5[] =
			  {
					  0.6,  0.2, 0.0,
					  0.7,  0.8, 0.0,
					  0.8,  0.2, 0.0,
					  0.9,  0.8, 0.0,
					  1.0,  0.2, 0.0
			  };

float Tstrip[300];
const GLuint indices0[] = {};
const GLuint indices1[] = {0};
const GLuint indices4[] = {0,1,2,3};
const GLuint indices5[] = {0,1,2,3,4};
GLuint indices100[100];
GLuint programID, VAOs[5], Buffers[5];

bool setupGraphics(int w, int h) {
	string vertexShaderPath   = ((string)GLSL_PATH) + "indexfifo.vert";
	string fragmentShaderPath = ((string)GLSL_PATH) + "fixedcolor.frag";

	programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
	if (!programID) {
		LOGE("Could not create program.");
		return false;
	}
	GL_CHECK(glUseProgram(programID));

	GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
	GL_CHECK(glViewport(0, 0, w, h));
}

void render(){
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	for(int i = 0 ; i < sizeof(Tstrip)/sizeof(Tstrip[0]) ; i++)
	{
		if(i % 3 == 0)
		{
			Tstrip[i] = (0.015*i / 3) - 1;
		}
		else if((i % 3 == 1) && (i % 2 == 0 ))
		{
			Tstrip[i] = -1.0f ;
		}
		else if((i % 3 == 1) && (i % 2 == 1 ))
		{
			Tstrip[i] = 1.0f ;
		}
		else
		{
			Tstrip[i] = 0.0f;
		}
	}

	for(int i = 0 ; i < 100 ; i++)
	{
		indices100[i] = i ;
	}

	GL_CHECK(glGenVertexArrays(5, &VAOs[0]));
	GL_CHECK(glGenBuffers(5, &Buffers[0]));

	GL_CHECK(glBindVertexArray(VAOs[0]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Tstrip0), Tstrip0, GL_STATIC_DRAW));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glBindVertexArray(0));

	GL_CHECK(glBindVertexArray(VAOs[1]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Tstrip1), Tstrip1, GL_STATIC_DRAW));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glBindVertexArray(0));

	GL_CHECK(glBindVertexArray(VAOs[2]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Tstrip4), Tstrip4, GL_STATIC_DRAW));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glBindVertexArray(0));

	GL_CHECK(glBindVertexArray(VAOs[3]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers[3]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Tstrip5), Tstrip5, GL_STATIC_DRAW));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glBindVertexArray(0));

	GL_CHECK(glBindVertexArray(VAOs[4]));
	GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers[4]));
	GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Tstrip), Tstrip, GL_STATIC_DRAW));
	GL_CHECK(glEnableVertexAttribArray(0));
	GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GL_CHECK(glBindVertexArray(0));


	GL_CHECK(glBindVertexArray(VAOs[0]));
	GL_CHECK(glDrawElements(GL_LINE_LOOP, 0, GL_UNSIGNED_INT, indices0));

	GL_CHECK(glBindVertexArray(VAOs[1]));
	GL_CHECK(glDrawElements(GL_LINE_LOOP, 1, GL_UNSIGNED_INT, indices1));

	GL_CHECK(glBindVertexArray(VAOs[2]));
	GL_CHECK(glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, indices4));

	GL_CHECK(glBindVertexArray(VAOs[3]));
	GL_CHECK(glDrawElements(GL_LINE_LOOP, 5, GL_UNSIGNED_INT, indices5));

	GL_CHECK(glBindVertexArray(VAOs[4]));
	GL_CHECK(glDrawElements(GL_LINE_LOOP, 100, GL_UNSIGNED_INT, indices100));
}

void de_init(){
	GL_CHECK(glDeleteVertexArrays(5, &VAOs[0]));
	GL_CHECK(glDeleteBuffers(5, &Buffers[0]));
}

void Sample::test() {
	setupGraphics(WINDOW_W, WINDOW_H);
	render();
	string bmp_file1 = filename + ".bmp";
	save2bmp(bmp_file1.c_str());
	SwapBuffers();
	de_init();
}

int main(int argc, char **argv){
	Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
	sample.test();
	return 0;
}