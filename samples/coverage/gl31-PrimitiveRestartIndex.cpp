/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gl31-PrimitiveRestartIndex.cpp
 * @author Alan.Liu
 * @par History:
 *    A001: Alan.Liu, 2019-04-15, create file
 * @par TestPoints:
 *
 *      glPrimitiveRestartIndex
 */
#include "Sample.h"

//
using std::string;
using namespace BotsonSDK;

GLuint programID = -1;

/* Asset directory. */

string vertexShaderFileName = "DrawArraysInstanced.vert";
string fragmentShaderFileName = "DrawArraysInstanced.frag";

/*Vertex Data*/
static const GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f, 1.0f,
         1.0f, -1.0f, -1.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 1.0f,
         1.0f,  1.0f, -1.0f, 1.0f,
         1.0f,  1.0f,  1.0f, 1.0f
};

/*Vertex Color*/
static const GLfloat color[] = {
        1.0f,1.0f,1.0f,1.0f,
        1.0f,1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,1.0f,
        1.0f,0.0f,0.0f,1.0f,
        0.0f,1.0f,1.0f,1.0f,
        0.0f,1.0f,0.0f,1.0f,
        0.0f,0.0f,1.0f,1.0f,
        0.5f,0.5f,0.5f,1.0f
};

/*element indices*/
        static const GLushort cube_indices[]=
        {
                0,1,2,3,6,7,4,5,
                0xFFFF,/*restare indices*/
                2,6,0,4,1,5,3,7
        };

/*vbo project*/
GLuint VBO;
GLuint EBO;
GLuint VAO;

bool setupGraphics()
{
         /*load shader*/
    string vertexShaderPath = (string)GLSL_PATH + "PrimitiveRestatIndex.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "PrimitiveRestatIndex.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
                                               fragmentShaderPath.c_str()));

    GL_CHECK(glClearColor(1.0,1.0,1.0,1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    return true;
}

void renderFrame() {
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glGenBuffers(1, &EBO));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW));

    GL_CHECK(glGenVertexArrays(1, &VAO));
    GL_CHECK(glBindVertexArray(VAO));

    GL_CHECK(glGenBuffers(1, &VBO));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(color), 0, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color), color));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void *)sizeof(vertices)));
    GL_CHECK(glBindVertexArray(VAO));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GL_CHECK(glEnable(GL_PRIMITIVE_RESTART));
    GL_CHECK(glPrimitiveRestartIndex(0xFFFF));
    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, NULL));

}

void Sample::test() {
    string bmp_file = filename + ".bmp";
    LOGI("[]: filename=%s\n", bmp_file.c_str());
    glViewport(0, 0, WINDOW_W, WINDOW_H);
    
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
