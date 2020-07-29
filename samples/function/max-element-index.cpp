/**
 ** @file max-element-index.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2020-05-15, create file
 ** @par TestPoints:
 **    max-element-index
 **/

#include "Sample.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

float pointVertices[] = { -0.5, -0.5, 0.5, -0.5, 0.0, 0.5};
GLuint *indices;

/* Shader variables. */
GLuint programID;
unsigned int VBO[2], VAO, EBO;
GLint my_element_index;

bool setupGraphics(int width, int height)
{
    string vertexShaderPath =(string)GLSL_PATH + "max-element-index.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "max-element-index.frag";

    LOGI("vertexShaderPath = %s\n", vertexShaderPath.c_str());

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

    if (programID == 0)
    {
        LOGI("Could not create program.");
        return false;
    }

    GL_CHECK(glGetIntegerv(GL_MAX_ELEMENT_INDEX , &my_element_index));
    LOGI("GL_MAX_ELEMENT_INDEX = %d\n", my_element_index);

    indices = (GLuint *)malloc(my_element_index);
    if(indices == NULL)
    {
        LOGI("malloc fail to apply!!!\n");
    }
    
    for(int i = 0 ; i < my_element_index; i++)
    {   
        indices[i] = i%3 ;
    }

    GL_CHECK(glUseProgram(programID));

    glGenVertexArrays(1 , &VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertices), pointVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertices), pointVertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float) , (void*)0 );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float) , (void*)0 );
    glEnableVertexAttribArray(2);

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.7f, 0.8f, 0.7f, 1.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    GL_CHECK(glEnable(GL_DEBUG_OUTPUT));
    string bmp_file = filename + ".bmp";
    save2bmp(bmp_file.c_str());
    LOGI("bmp_file=%s", bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}
