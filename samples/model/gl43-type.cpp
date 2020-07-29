/**
 * @file gl20-vertexattrib.cpp
 * @testpoint glsl related API
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
const float vertices[] =
{
	-0.8, -0.8, 0.0, 1.0,
	-0.2, -0.8, 0.0, 1.0,
	-0.5, -0.2, 0.0, 1.0,

	 0.8, -0.8, 0.0, 1.0,
	 0.2, -0.8, 0.0, 1.0,
	 0.5, -0.2, 0.0, 1.0,

	-0.8,  0.8, 0.0, 1.0,
	-0.2,  0.8, 0.0, 1.0,
	-0.5,  0.2, 0.0, 1.0,

};
/* Per corner colors for the triangle (Red, Green, Green). */
const float color[] =
{
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,

    0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,

	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	0.0, 0.0, 1.0, 1.0
};
const GLubyte indices1[] = {0,1,2};
const GLushort indices2[] = {3,4,5};
const GLuint indices3[] = {6,7,8};
GLuint programID, VAOs, Buffers;
const GLchar* vertexShaderSource = "#version 430 core\n"
"layout(location=0) in vec4 a_v4Position;\n"
"layout(location=1) in vec4 a_v4FillColor;\n"
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

void setupGraphics(int w, int h)
{
	programID = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
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

	GL_CHECK(glUseProgram(programID));
	GL_CHECK(glViewport(0, 0, w, h));
} 

void renderFrame() {
	GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));
	GL_CHECK(glBindVertexArray(VAOs));
	GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices1));
	GL_CHECK(glDrawElements(GL_LINES, 3, GL_UNSIGNED_SHORT, indices2));
	GL_CHECK(glDrawElements(GL_LINES, 3, GL_UNSIGNED_INT, indices3));
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
