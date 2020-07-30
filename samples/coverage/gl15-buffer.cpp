/**
 * @file buffer.cpp
 * @testpoint glBindBuffer glBufferData glGenBuffers
 *
 */

#include "gl-util.h"
#include <cstring>

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

GLuint buffers[2];
GLuint vao;

float triangleVertices[] =
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
const float triangleVertices1[] =
{
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
     0.0f,-0.5f, 0.0f,
};

GLubyte indices[] = {1,2,4, 0,3,5};
GLubyte indices1[] = {5,4,1};

void getdata(GLenum target)
{
	GLubyte getIndice;
	GLfloat getVertice;
	GLint data;
	GLvoid * params;

	if(target == GL_ARRAY_BUFFER) {
		glGetBufferSubData(target, 0, sizeof(GLfloat), &getVertice); //getError
		LOGIF("glGetBufferSubData(GL_ARRAY_BUFFER, 0, 1)=%f\n", getVertice);
	}
	if(target == GL_ELEMENT_ARRAY_BUFFER) {
		glGetBufferSubData(target, 0, sizeof(GLubyte), &getIndice);
		LOGIF("glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 1)=%d\n", getIndice);
	}
	glGetBufferParameteriv(target, GL_BUFFER_ACCESS, &data); 
	LOGIF("glGetBufferParameteriv(GL_BUFFER_ACCESS)=%d\n", data);
	glGetBufferParameteriv(target, GL_BUFFER_MAPPED, &data);
	LOGIF("glGetBufferParameteriv(GL_BUFFER_MAPPED)=%d\n", data);
	glGetBufferParameteriv(target, GL_BUFFER_SIZE, &data); 
	LOGIF("glGetBufferParameteriv(GL_BUFFER_SIZE)=%d\n", data);
	glGetBufferParameteriv(target, GL_BUFFER_USAGE, &data); 
	LOGIF("glGetBufferParameteriv(GL_BUFFER_USAGE)=%d\n", data);
	glGetBufferPointerv(target, GL_BUFFER_MAP_POINTER, &params);
	LOGIF("glGetBufferPointerv(GL_BUFFER_MAP_POINTER)=%x\n", params);
}

bool setupGraphics(int width, int height)
{
	GLfloat *mapArray;
	GLubyte *mapElement;

	glGenBuffers(2, buffers);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices1), triangleVertices1);
	mapArray = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
	LOGIF("glMapBuffer(GL_ARRAY_BUFFER)=%f\n", *mapArray);
	getdata(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices1), indices1);
	mapElement = (GLubyte *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	*mapElement = 2;
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

        getdata(GL_ELEMENT_ARRAY_BUFFER);
	GLboolean isBuffer = glIsBuffer(buffers[0]);
	LOGIF("glIsBuffer(buffers[0])=%s\n", GET_BOOL(isBuffer));
	isBuffer = glIsBuffer(buffers[1]);
	LOGIF("glIsBuffer(buffers[1])=%s\n", GET_BOOL(isBuffer));

	glViewport(0, 0, width, height);

	/* Set clear screen color. */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepthf(1.0f);

	return true;
}

void renderFrame(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor4f(0.0, 1.0, 0.0, 0.0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    glFlush();
    glDeleteBuffers(2, buffers);
}

int main(int argc, char** argv)
{
    string file = "gl15-buffer";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
	    string filename = file + ".bmp";
	    LOGIF("[]: filename=%s\n", filename.c_str());
            renderFrame();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
