/**
 * @file gl20-vertexattrib.cpp
 * @testpoint glsl related API
 *
 */

#include "Sample.h"

const float Vertices[] =
{
	-0.4, 0.7, 0.0,  0.4, 0.7, 0.0,
	-0.4, 0.5, 0.0,  0.4, 0.5, 0.0,
	-0.4, 0.3, 0.0,  0.4, 0.3, 0.0,
	-0.4, 0.1, 0.0,  0.4, 0.1, 0.0,
	-0.4,-0.1, 0.0,  0.4,-0.1, 0.0,
	-0.4,-0.3, 0.0,  0.4,-0.3, 0.0,
	-0.4,-0.5, 0.0,  0.4,-0.5, 0.0,
	-0.4,-0.7, 0.0,  0.4,-0.7, 0.0
};
/* Per corner colors for the triangle (Red, Green, Green). */
const float triangleColors[] =
{
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};
const GLubyte indices1[] = {0,1};
const GLushort indices2[] = {2,3};
const GLuint indices3[] = {4,5};
const GLubyte indices4[] = {6,7};
const GLubyte indices5[] = {8,9};
const GLubyte indices6[] = {10,11};
const GLubyte indices7[] = {12,13};
const GLubyte indices8[] = {14,15};

/* Simple triangle. */
const float triangleVertices2[] =
{
     0.0f,-0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
};

/* Per corner colors for the triangle (Red, Green, Green). */
const float triangleColors2[] =
{
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
};

GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;
GLint iLocPosition, iLocFillColor;

const GLchar* vertexShaderSource = "#version 430 core\n"
"in vec4 a_v4Position;\n" 
"in vec4 a_v4FillColor;\n"
"out vec4 v_v4FillColor;\n"
"void main()\n" 
"{\n" 
"    v_v4FillColor = a_v4FillColor;\n"
"    gl_Position = a_v4Position;\n"
"}\0"; 
const GLchar* fragmentShaderSource = "#version 430 core\n"
"in vec4 v_v4FillColor;\n"
"out vec4 color;\n" 
"void main()\n" 
"{\n" 
"color = v_v4FillColor;\n" 
"}\n\0"; 

void loadShader(void)
{
	GLint success; 
	GLchar infoLog[512];
    shaderProgram = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
    LOGI("PROGRAM = %d\n", shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) { 
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); 
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"); 
	} 
	glDeleteShader(vertexShader); 
	glDeleteShader(fragmentShader); 

    iLocPosition = glGetAttribLocation(shaderProgram, "a_v4Position");
    iLocFillColor = glGetAttribLocation(shaderProgram, "a_v4FillColor");
}

void setupGraphics(int w, int h)
{
	loadShader();
	glUseProgram(shaderProgram); 
	glViewport(0, 0, w, h);
} 

void getdata()
{
GLint buf_size[2], buf_use[2];
GLint size;
GLfloat tmp[4];
char name[14];
GLint length;
GLenum type;
glGetVertexAttribiv(iLocPosition, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &size);
LOGI("glGetVertexAttribiv(iLocPosition,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING):%d\n",size);
glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_SIZE):%d\n",size);
glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &size);
LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_STRIDE):%d\n",size);
glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_TYPE, &size);
LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_TYPE):0x%x\n",size);
glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &size);
LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_NORMALIZED):%d\n",size);
glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &size);
LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_ENABLED):%d\n",size);
glGetVertexAttribfv(iLocFillColor, GL_CURRENT_VERTEX_ATTRIB, tmp);
LOGI("glGetVertexAttribiv(GL_CURRENT_VERTEX_ATTRIB):%f,%f,%f,%f\n",tmp[0],tmp[1],tmp[2],tmp[3]);
glGetActiveAttrib(shaderProgram,iLocFillColor,13,&length,&size,&type,name);
LOGI("glGetActiveAttrib(iLocFillColor):length=%d,size=%d,type=%x,name=%s\n",length,size,type,name);
GLfloat tmp_p[9];
GLvoid *data;
glGetVertexAttribPointerv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_POINTER, &data);
LOGI("glGetVertexAttribPointerv(GL_CURRENT_VERTEX_ATTRIB): %x\n",data);
}

void renderFrame() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);

	glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, Vertices);
	glVertexAttrib1f(iLocFillColor, 1.0);
	glEnableVertexAttribArray(iLocFillColor);
	glEnableVertexAttribArray(iLocPosition);
	glDisableVertexAttribArray(iLocFillColor);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices1);

	glVertexAttrib2f(iLocFillColor, 1.0, 1.0);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, indices2);

	glVertexAttrib3f(iLocFillColor, 0.0, 1.0, 1.0);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indices3);

	glVertexAttrib4f(iLocFillColor, 1.0, 1.0, 1.0, 0.0);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices4);

	GLfloat color1[] = {1.0};
	glVertexAttrib1fv(iLocFillColor, color1);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices5);

	GLfloat color2[] = {0.0, 1.0};
	glVertexAttrib2fv(iLocFillColor, color2);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices6);

	GLfloat color3[] = {1.0, 0.0, 1.0};
	glVertexAttrib3fv(iLocFillColor, color3);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices7);

	GLfloat color4[] = {1.0, 1.0, 1.0, 0.0};
	glVertexAttrib4fv(iLocFillColor, color4);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices8);

	glFlush();
	getdata();
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
//    string file = "gl20-vertexattrib";
//    GBtest_init(&argc,argv,file,DisplayMode);
//    setupGraphics(WINDOW_W, WINDOW_H);
//	    string filename = file + ".bmp";
//	    LOGI("[]: filename=%s\n", filename.c_str());
//            renderFrame();
//	    save2bmp(filename.c_str());
//	    glutSwapBuffers();
//    GBtest_deinit();
//
//    return 0;
//}
