/**
 * @file gl33-VertexAttribDivisor.cpp
 * @testpoint
 *
 *   glVertexAttribDivisor
 *
 */

#include "Sample.h"

unsigned int DisplayMode = GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE;

/* Simple triangle. */
const float triangleVertices[] =
{
     0.5f,-0.5f, 0.0f,
    -0.5f,-0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
};

/* Per corner colors for the triangle (Red, Green, Green). */
const float triangleColors[] =
{
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
};

GLuint vertexShader;
GLuint fragmentShader;
GLuint programID;
GLint iLocPosition, iLocFillColor;
GLuint vertexShaderID = -1;
GLuint fragmentShaderID = -1;

void setupGraphics(int w, int h)
{
    string vertexShaderPath = (string)GLSL_PATH + "VertexAttribDivisor.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "VertexAttribDivisor.frag";
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0)
    {
        return ;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));

//    loadShader();
    glUseProgram(programID); 
    glViewport(0, 0, w, h);
} 

void renderFrame()
{
    GL_CHECK(glClearColor(0.2f, 0.3f, 0.3f, 1.0f)); 
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT)); 
    GL_CHECK(glUseProgram(programID)); 

    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, triangleVertices));
    GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, triangleColors));

    glVertexAttribDivisor(iLocFillColor, 1);

    glEnableVertexAttribArray(iLocFillColor);
    glEnableVertexAttribArray(iLocPosition);
    GL_CHECK(glDrawArraysInstanced(GL_QUADS, 0, 4, 4));
    glFlush();
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    string bmp_file = filename + ".bmp";
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