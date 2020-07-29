/**
 ** @file max-elements-vertex.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2020-05-15, create file
 ** @par TestPoints:
 **    max-elements-vertex
 **/

#include "Sample.h"
#include <vector>

using std::string;
using namespace BotsonSDK;
using namespace std;

GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

GLint my_element_indices;
GLint my_element_vertices;

float pointVertices[12000];

vector<float> myvec;
int indices[3];
GLuint programID;
unsigned int VBO[2], VAO, EBO;

bool setupGraphics(int width, int height)
{
    string vertexShaderPath =(string)GLSL_PATH + "max-elements-vertex.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "max-elements-vertex.frag";

    LOGI("vertexShaderPath = %s\n", vertexShaderPath.c_str());

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

    if (programID == 0)
    {
        LOGI("Could not create program.");
        return false;
    }

    GL_CHECK(glGetIntegerv(GL_MAX_ELEMENTS_INDICES , &my_element_indices));
    LOGI("GL_MAX_ELEMENTS_INDICES = %d\n", my_element_indices);
    GL_CHECK(glGetIntegerv(GL_MAX_ELEMENTS_VERTICES , &my_element_vertices));
    LOGI("GL_MAX_ELEMENTS_VERTICES = %d\n", my_element_vertices);

    myvec.reserve(5000);
    for(int i = 0; i < my_element_vertices*2 ; i++)
    {
        myvec.push_back(((float)(rand()%100))/50 - 1);
    }

    GL_CHECK(glUseProgram(programID));
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = my_element_indices;

    glGenVertexArrays(1 , &VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * myvec.size(), &myvec[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * myvec.size(), &myvec[0], GL_STATIC_DRAW);
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
    GL_CHECK(glDrawArrays(GL_POINTS, 0, my_element_vertices));
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
