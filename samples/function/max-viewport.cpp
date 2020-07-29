/**
 ** @file max-viewport.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2019-05-15, create file
 ** @par TestPoints:
 **    GL_MAX_VIEWPORTS
 **/

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

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

GLuint programID, VAOs, Buffers;

const GLuint uniformIndices = 0;
const GLuint uniformIndices1 = 1;

GLint params;
GLint params1;

GLint length;
GLchar uniformName;
GLuint indices;
const char*names = {"u1f"};

bool setupGraphics()
{
    /*load shader*/
    string vertexShaderPath =(string)GLSL_PATH + "max-viewport.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "max-viewport.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
                                               fragmentShaderPath.c_str()));

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

    return true;
} 

void renderFrame(void)
{
	GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
	GL_CHECK(glUseProgram(programID));
	GL_CHECK(glUniform1f(0, 0.1f));
	GL_CHECK(glUniform2f(1, 0.1, 0.1));
	GL_CHECK(glUniform3f(2, 0.1, 0.1, 0.1));
	GL_CHECK(glUniform4f(3, 0.0, 1.0, 0.0, 0.0));
	GL_CHECK(glBindVertexArray(VAOs));

        GLint max_viewports;
        GL_CHECK(glGetIntegerv(GL_MAX_VIEWPORTS , &max_viewports));
        LOGI("GL_MAX_VIEWPORTS = %d\n", max_viewports);

        for(int i = 2; i < (max_viewports + 4) ; i++)
        {
            GL_CHECK(glViewport(WINDOW_W / i, WINDOW_H / i, WINDOW_W / (i -1), WINDOW_H / (i -1))); 
            GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
        }

	GL_CHECK(glFlush());
}

void Sample::test() {
	string bmp_file = filename + ".bmp";
	LOGI("[]: filename=%s\n", bmp_file.c_str());
	setupGraphics();
        renderFrame();
	save2bmp(bmp_file.c_str());
	SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
