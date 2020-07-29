/**
 * @file gl15-buffersubdata.cpp
 * @testpoint glBufferSubData
 *
 */

#include "gl-util.h"
#include <cstring>

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

GLuint bufferID;
GLuint textureID;
GLuint vao;
float triangleVertices[] =
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
};

GLfloat texcoord[]={
	0.0, 1.0, 
	0.0, 0.0,
	1.0, 1.0, 
	1.0, 0.0
};

GLfloat vertice[]={
	-0.5, 0.5, 0.0,
	 0.5, 0.5, 0.0,
	-0.5,-0.5, 0.0,
	 0.5,-0.5, 0.0
};

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
    GLubyte image[width*height*3];
	GLubyte *mapArray;

	glViewport(0, 0, width, height);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor4f(0.0, 1.0, 0.0, 0.0);
    glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);

    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_PIXEL_PACK_BUFFER, bufferID);
    glBufferData(GL_PIXEL_PACK_BUFFER, sizeof(image), image, GL_STATIC_DRAW);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mapArray = (GLubyte *)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
	LOGIF("glMapBuffer(GL_ARRAY_BUFFER)=%d\n", *mapArray);
	getdata(GL_PIXEL_PACK_BUFFER);
	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);

   // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, bufferID);
   // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, NULL);
   // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	return true;
}

void renderFrame(void)
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoord);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertice);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glFlush();

    glDeleteBuffers(1, &bufferID);
}

int main(int argc, char** argv)
{
    string file = "gl15-buffersubdata";
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
