/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file minsampleshading.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Otto.Liu, 2019-11-29, Init file
 * @brief basic test for glMinSampleShading
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include <GL/freeglut.h>

using std::string;
using namespace BotsonSDK;

GLfloat triangleVertices[] = {
        0.35f, 0.5f, 0.0f, 1.0f,
        -0.5f,-0.25f,0.0f, 1.0f,
        0.5f, -0.25f,0.0f, 1.0f,
        -0.35f,0.5f, 0.0f, 1.0f,
        0.0f, -0.75f,0.0f, 1.0f
};

GLfloat triangleColors[]={
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f
};

GLfloat ratio[] = { 0.0, 0.5, 1.0};

GLuint vpos_obj, vcol_obj, vao, programID;

bool setupGraphics(int w, int h, int sampleNum, float rate) {
    glutSetOption(GLUT_MULTISAMPLE, sampleNum);
    GL_CHECK(glEnable(GL_SAMPLE_SHADING));
    GL_CHECK(glMinSampleShading(rate));
    string vertexShaderPath = ((string)GLSL_PATH) + "vert4_passby_location.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "single_black.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (!programID) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));

    GL_CHECK(glGenBuffers(1, &vpos_obj));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vpos_obj));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL));
    
    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0));
    GL_CHECK(glClearDepthf(1.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    return true;
}

void renderFrame() {
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDrawArrays(GL_LINE_LOOP, 0, 5));
}

void clean_test(){
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glDeleteBuffers(1, &vpos_obj));
    GL_CHECK(glDeleteProgram(programID));
    GL_CHECK(glDeleteVertexArrays(1, &vao));
}
void Sample::test() {
    for(int i=0; i<ARRAY_NUM(ratio); i++) {
        setupGraphics(WINDOW_W, WINDOW_H, 4, ratio[i]);
        renderFrame();
        char ss[3];
        sprintf(ss, "_%d", i);
        string bmp_file = filename + ss + ".bmp";
        save2bmp(bmp_file.c_str());
        SwapBuffers();
        clean_test();
    }
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();

    return 0;
}
