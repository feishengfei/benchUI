/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file points.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for points related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;

const float vertices[] = {
     0.0f,  0.0f, 0.0f, 1.0,
     0.8f,  0.8f, 0.0f, 1.0,
    -0.8f, -0.8f, 0.0f, 1.0,
     0.8f, -0.8f, 0.0f, 1.0,
    -0.8f,  0.8f, 0.0f, 1.0,
     -0.3f,  0.3f, 0.0f, 1.0,
     0.3f, -0.3f, 0.0f, 1.0,
     0.3f,  0.3f, 0.0f, 1.0
};


GLfloat color[] = {
    0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 1.0

};


GLuint programID, VAOs, Buffers;

void getdata()
{
    GLint buf_size[2], buf_use[2];
    GLint size;
    GLfloat tmp[4];
    char name[14];
    GLint length;
    GLenum type;
    glGetVertexAttribiv(0, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &size);
    LOGI("glGetVertexAttribiv(iLocPosition,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING):%d\n",size);
    glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_SIZE):%d\n",size);
    glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_STRIDE):%d\n",size);
    glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_TYPE, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_TYPE):0x%x\n",size);
    glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_NORMALIZED):%d\n",size);
    glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_ENABLED):%d\n",size);
    glGetVertexAttribfv(1, GL_CURRENT_VERTEX_ATTRIB, tmp);
    LOGI("glGetVertexAttribiv(GL_CURRENT_VERTEX_ATTRIB):%f,%f,%f,%f\n",tmp[0],tmp[1],tmp[2],tmp[3]);
    glGetActiveAttrib(programID,1,13,&length,&size,&type,name);
    LOGI("glGetActiveAttrib(1):length=%d,size=%d,type=%x,name=%s\n",length,size,type,name);
    GLfloat tmp_p[9];
    GLvoid *data;
    glGetVertexAttribPointerv(1, GL_VERTEX_ATTRIB_ARRAY_POINTER, &data);
    LOGI("glGetVertexAttribPointerv(GL_CURRENT_VERTEX_ATTRIB): %x\n",data);
}

bool setupGraphics(int w, int h) {
    string vertexShaderPath = ((string)GLSL_PATH) + "vertexattrib.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "vertexattrib.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(color), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color), color));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glClearColor(1.0, 1.0, 1.0, 1.0));
    GL_CHECK(glViewport(0, 0, w, h));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glPointSize(30.0));
    GL_CHECK(glBindVertexArray(VAOs));

    const GLfloat col[4] = {1.0, 0.8, 0, 1.0};
    GL_CHECK(glVertexAttrib4fv(1, col));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 1));

    GL_CHECK(glVertexAttrib4f(1, 1.0, 0.0, 1.0, 1.0));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 1, 1));


    GL_CHECK(glVertexAttrib3f(1, 0.0, 0.5, 0.8));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 2, 1));

    const GLfloat col1[2] = {0.2, 0.9};
    GL_CHECK(glVertexAttrib2fv(1, col1));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 3, 1));

    GL_CHECK(glVertexAttrib2f(1, 0.8, 0.2));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 4, 1));

    GL_CHECK(glVertexAttrib1f(1, 1.0));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 5, 1));

    const GLfloat col2[1] = {1.0};
    GL_CHECK(glVertexAttrib1fv(1, col2));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 6, 1));

    const GLfloat col3[3] = {1.0, 0, 1.0};
    GL_CHECK(glVertexAttrib3fv(1, col3));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_POINTS, 7, 1));
    GLint params;
    GL_CHECK(glGetVertexAttribIiv(1, GL_VERTEX_ATTRIB_ARRAY_SIZE, &params));
    LOGI("index 1 attrib array size is %d\n", params);
    getdata();
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
