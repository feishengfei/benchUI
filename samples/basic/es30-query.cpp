/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file query.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for query related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "Query.vert";
string fragmentShaderFilename = "Query.frag";

float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

float triangleVertices1[] = {
    -0.4f, -0.4f, -0.2f,
     0.4f, -0.4f, -0.2f,
     0.0f,  0.4f, -0.2f,
};

float triangleVertices2[] = {
    -0.3f, -0.3f, 0.2f,
     0.3f, -0.3f, 0.2f,
     0.0f,  0.3f, 0.2f,
};

float triangleVertices3[] = {
    -0.1f, -0.1f, 0.4f,
     0.1f, -0.1f, 0.4f,
     0.0f,  0.1f, 0.4f,
};

float triangleColors[] = {
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
};

float triangleColors1[] = {
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
};

float triangleColors2[] = {
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
};

float triangleColors3[] = {
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
};

GLuint programID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint query[3];

bool setupGraphics(int w, int h) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;
    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
            fragmentShaderPath.c_str());

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));

    glViewport(0, 0, w, h);
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    glGenQueries(3,query);
    LOGI("gen query: %d,%d,%d\n",query[0], query[1], query[2]);

    return true;
}
void getQueryObject(GLuint id) {
    int count=1000;
    GLuint queryReady=GL_FALSE;
    while(!queryReady&&count--) {
        glGetQueryObjectuiv(id, GL_QUERY_RESULT_AVAILABLE, &queryReady);
    }
    GLuint samples;
    glGetQueryObjectuiv(id, GL_QUERY_RESULT, &samples);
    LOGI("GetQueryObject(%d):%d\n",id, samples);
}

void drawTriangle(GLfloat *vertex, GLfloat *color) {
    GL_CHECK(glVertexAttribPointer(iLocPosition,3,GL_FLOAT,GL_FALSE,0,vertex));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocFillColor,3,GL_FLOAT,GL_FALSE,0,color));
    GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void renderFrame() {
    GLint name;

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    drawTriangle(triangleVertices, triangleColors);
    glBeginQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, query[1]);
    drawTriangle(triangleVertices1, triangleColors1);
    glGetQueryiv(GL_ANY_SAMPLES_PASSED_CONSERVATIVE,GL_CURRENT_QUERY,&name);
    LOGI("current query: %d\n",name);
    glEndQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE);
    getQueryObject(query[1]);

    GL_CHECK(glBeginQuery(GL_ANY_SAMPLES_PASSED, query[0]));
    drawTriangle(triangleVertices2, triangleColors2);
    glGetQueryiv(GL_ANY_SAMPLES_PASSED,GL_CURRENT_QUERY,&name);
    LOGI("current query: %d\n",name);
    glEndQuery(GL_ANY_SAMPLES_PASSED);
    getQueryObject(query[0]);

    GL_CHECK(glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, query[2]));
    drawTriangle(triangleVertices3, triangleColors3);
    glGetQueryiv(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,GL_CURRENT_QUERY,&name);
    LOGI("current query: %d\n",name);
    glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
    getQueryObject(query[2]);

    LOGI("is query: %d,%d,%d\n",glIsQuery(query[0]),glIsQuery(query[1]),glIsQuery(query[2]));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
    GL_CHECK(glDeleteQueries(3,query));
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
