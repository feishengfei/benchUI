/**
 ** @file max-vertex_attrib.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2019-05-15, create file
 ** @par TestPoints:
 **    
 */

#include "Sample.h"
#include <vector>
#include <stdio.h>
using namespace std;

#define BUFFER_OFFSET(x)  ((const void*) (x))

const float vertices[] = {
    -0.4f, -0.4f, 0.0f, 1.0,
    -0.4f,  0.0f, 0.0f, 1.0,
    -0.4f,  0.4f, 0.0f, 1.0,
     0.0f, -0.4f, 0.0f, 1.0,
     0.0f,  0.0f, 0.0f, 1.0,
     0.0f,  0.4f, 0.0f, 1.0,
     0.4f, -0.4f, 0.0f, 1.0,
     0.4f,  0.0f, 0.0f, 1.0,
     0.4f,  0.4f, 0.0f, 1.0,
};

GLuint programID, VAOs, Buffers;
GLint my_vertex_attrib;

void loadShader(void)
{
    GLint success; 
    GLchar infoLog[512];

    std::string SvertexShaderSource =
        "#version 430 core\n"
        "layout(location = 0) in vec4 a_v4Position;\n";
    std::string SvertexShaderSource1 =
        "out vec4 vcolor;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = a_v4Position;\n";

    std::string vertex_const = "   vcolor = ";
    std::string vertex_n1 = "";
    std::string vertex_temp1 ;

    for(int i = 1 ; i < my_vertex_attrib ; i++)
    {
        vertex_n1.append("layout(location = " + std::to_string(i) + ") in vec4 color" + std::to_string(i) + ";\n");

        std::string temp;
        if(i < ( my_vertex_attrib - 1))
        {
            temp = " + ";
        }
        else
        {
            temp = " ;\n\0 ";

        }
        vertex_temp1.append("color" + std::to_string(i) + temp);
    }   

    SvertexShaderSource.append(vertex_n1);
    SvertexShaderSource.append(SvertexShaderSource1 + vertex_const + vertex_temp1 + "}\n" );
    LOGI("vertexShaderSource = \n %s\n", SvertexShaderSource.c_str());
    const GLchar* vertexShaderSource = SvertexShaderSource.c_str();

    std::string SfragmentShaderSource =
         "#version 430 core\n"
         "precision mediump float;\n"
         "in vec4 vcolor;\n"
         "out vec4 FragColor;\n"
         "void main()\n"
         "{\n"
         "    FragColor = vcolor;\n"
         "}\n";


    LOGI("SfragmentShaderSource = \n %s\n", SfragmentShaderSource.c_str());
    const GLchar* fragmentShaderSource = SfragmentShaderSource.c_str();

    programID = Shader::createProgramFromString(vertexShaderSource, fragmentShaderSource);
    printf("PROGRAM = %d\n", programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
            glGetProgramInfoLog(programID, 512, NULL, infoLog);
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
    }
}



bool setupGraphics(int w, int h) {
    GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &my_vertex_attrib));
    LOGI("GL_MAX_VERTEX_ATTRIBS = %d\n", my_vertex_attrib);

    loadShader();

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));

    GL_CHECK(glClearColor(1.0, 1.0, 1.0, 1.0));
    GL_CHECK(glViewport(0, 0, w, h));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
    GL_CHECK(glPointSize(10.0))
    GL_CHECK(glBindVertexArray(VAOs));


    for(int i = 1 ; i < my_vertex_attrib ; i++)
    {
        GL_CHECK(glVertexAttrib4d(i, 0.05, 0.0, 0.0, 1.0));
    }

    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 1, 1));

    for(int i = 1 ; i < my_vertex_attrib ; i++)
    {
        GL_CHECK(glVertexAttrib4f(i, 0.0, 0.05, 0.0, 1.0));
    }

    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 2, 1));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
