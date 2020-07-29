/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl31-DrawArraysInstanced.cpp
 * @author Cary.Zhang
 * @par History:
 *    A001: Cary.Zhang, 2019-04-19, create file
 * @par TestPoints:
 *
 *      glDrawArraysInstanced
 */
#include "Sample.h"
#include <iostream>
#include <sstream>
using std::string;

unsigned int DisplayMode = GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE;
GLuint vertexShaderID = -1;
GLuint fragmentShaderID = -1;
GLuint programID = -1;
GLuint setoffID = -1;

static const GLenum factors[] = { 
        GL_POINTS,
        GL_LINE_STRIP,
        GL_LINE_LOOP,
        GL_LINES,
        GL_TRIANGLE_STRIP,
        GL_TRIANGLE_FAN,
        GL_TRIANGLES,
        GL_LINES_ADJACENCY,
        GL_LINE_STRIP_ADJACENCY,
        GL_TRIANGLES_ADJACENCY,
        GL_TRIANGLE_STRIP_ADJACENCY,
        GL_PATCHES
};

/* Asset directory. */

string vertexShaderFileName = "DrawArraysInstanced.vert";
string fragmentShaderFileName = "DrawArraysInstanced.frag";
float offset = 0.1f;
/*Vertex Data*/
GLfloat vertices[] = {
    -0.5f,0.5f,0.0f,
     0.5f,-0.5f,0.0f,
    -0.5f,-0.5f,0.0f,

    -0.5f,0.5f,0.0f,
     0.5f,-0.5f,0.0f,
     0.5f,0.5f,0.0f
};

/*Vertex Color*/
GLfloat color[] = {
        1.0f,0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,
        1.0f,0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f
};

/*vbo project*/
GLuint VBO;
GLuint VAO;
GLint locationID;
GLint location_colorID;
GLint iLocPosition;
GLint iLocFillColor;

/*VEC DATA*/
struct vec2
{
    float x;
    float y;
};

bool setupGraphics(int w, int h)
{
    /*load shader*/
    string vertexShaderPath = (string)GLSL_PATH + "DrawArraysInstanced.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "DrawArraysInstanced.frag";
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0)
    {
        /*  LOGE("Could not create program.");*/
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(iLocPosition = glGetAttribLocation(programID,"position"));
    GL_CHECK(iLocFillColor = glGetAttribLocation(programID,"a_vColor"));
    glUseProgram(programID);
    glViewport(0, 0, w, h);
    return true;
}

void renderFrame(int drawType)
{
    GL_CHECK(glClearColor(0.0,0.0,1.0,1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));
    GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, color));
    glEnableVertexAttribArray(iLocFillColor);
    glEnableVertexAttribArray(iLocPosition);
    GL_CHECK(glDrawArraysInstanced(drawType, 0, 6, 4));
    glFlush();
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int typeNum=0; typeNum < ARRAY_NUM(factors); typeNum++) {
        string src_name = get_primitives_name(factors[typeNum]);
        string bmp_file = filename + "-" + src_name +".bmp";
        LOGI("[]: filename=%s\n", bmp_file.c_str());
        renderFrame(factors[typeNum]);
        save2bmp(bmp_file.c_str());
        SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
