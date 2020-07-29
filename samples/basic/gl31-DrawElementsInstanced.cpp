/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl31-DrawElementsInstanced.cpp
 * @author Cary.Zhang
 * @par History:
 *    A001: Cary.Zhang, 2019-04-20, create file
 * @par TestPoints:
 *
 *      glDrawElementsInstanced
 */
#include "Sample.h"
#include <iostream>
#include <sstream>
using std::string;
using namespace BotsonSDK;

unsigned int DisplayMode = GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE;
/*shaderID & pogramID*/
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

string vertexShaderFileName = "DrawElementsInstanced.vert";
string fragmentShaderFileName = "DrawElementsInstanced.frag";
float offset = 0.1f;
/*Vertex Data*/
GLfloat vertices[] = {
        -0.05f,0.05f,
        0.05f,-0.05f,
        -0.05f,-0.05f,
        0.05f,0.05f
};

/*Vertex Color*/
GLfloat color[] = {
        1.0f,0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f
};
/*elements*/
        GLubyte array[] = {0,1,2,0,3,1};

/*vbo project*/
GLuint VBO;
GLuint VAO;
GLuint EBO;
GLint locationID;
GLint location_colorID;

/*VEC DATA*/
struct vec2
{
    float x;
    float y;
};

bool setupGraphics(int w, int h)
{
    /*load shader*/
    string vertexShaderPath =(string)GLSL_PATH + "DrawElementsInstanced.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "DrawElementsInstanced.frag";
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0)
    {
        LOGI("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    glViewport(0, 0, w, h);
    
}

void renderFrame(int drawType)
{
        glGenVertexArrays(1,&VAO);
        glGenBuffers(1,&VBO);
        glGenBuffers(1,&EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(array),array,GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),&vertices,GL_STATIC_DRAW);
        locationID = glGetAttribLocation(programID,"position");
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(locationID,2,GL_FLOAT,GL_FALSE,2* sizeof(float),(void*)0);
        glBindVertexArray(0);

        struct vec2 vec21[100];
        int index = 0;

        for(int y = -10;y < 10;y +=2)
        {
            for(int x = -10;x < 10;x +=2)
            {
                struct vec2 vec22;
                vec22.x = (float)x/10.0f+offset;
                vec22.y = (float)y/10.0f+offset;
                vec21[index++] = vec22;
            }
        }
        glUseProgram(programID);

        for (unsigned int i = 0; i < 100;i++){
            std::stringstream ss;
            std::string index;
            ss << i;
            index = ss.str();
            glUniform2f((glGetUniformLocation(programID,("offsets["+index+"]").c_str())),vec21[i].x,vec21[i].y);
        }

        glClearColor(0.0,0.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        glBindVertexArray(VAO);
        glDrawElementsInstanced(drawType, 600, GL_UNSIGNED_BYTE, array, 100);

}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H); 
    for(int typeNum=0; typeNum < ARRAY_NUM(factors); typeNum++) {
        string src_name = get_primitives_name(factors[typeNum]);
        string bmp_file = filename + "-" + src_name + ".bmp";
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