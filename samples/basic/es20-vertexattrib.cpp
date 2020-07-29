/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file vertexattrib.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for vertexattrib related API
 * @par TestPoints:
 *
 */

#include "Sample.h"


using std::string;
using namespace BotsonSDK;

const float Vertices[] = {
	-0.4, 0.7, 0.0,  0.4, 0.7, 0.0,
	-0.4, 0.5, 0.0,  0.4, 0.5, 0.0,
	-0.4, 0.3, 0.0,  0.4, 0.3, 0.0,
	-0.4, 0.1, 0.0,  0.4, 0.1, 0.0,
	-0.4,-0.1, 0.0,  0.4,-0.1, 0.0,
	-0.4,-0.3, 0.0,  0.4,-0.3, 0.0,
	-0.4,-0.5, 0.0,  0.4,-0.5, 0.0,
	-0.4,-0.7, 0.0,  0.4,-0.7, 0.0
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

const GLubyte indices1[] = {0,1};
const GLushort indices2[] = {2,3};
const GLuint indices3[] = {4,5};
const GLubyte indices4[] = {6,7};
const GLubyte indices5[] = {8,9};
const GLubyte indices6[] = {10,11};
const GLubyte indices7[] = {12,13};
const GLubyte indices8[] = {14,15};

const float triangleVertices2[] = {
     0.0f,-0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
};

const float triangleColors2[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
};

GLuint programID;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint buffer[2];
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;

bool setupGraphics(int width, int height) {
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    if(glIsEnabled(GL_DEPTH_TEST))
    LOGI("IsEnable(GL_DEPTH_TEST)=true\n");

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));

    //glBindAttribLocation(programID, 3, "a_v4Position");
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(iLocFillColor = glGetAttribLocation(programID, "a_v4FillColor"));
    LOGI("Attrib location: a_v4Position=%d, a_v4FillColor=%d\n", iLocPosition, iLocFillColor);
    GLint iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, Matrix::identityMatrix.getAsArray()));
    }

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));
    glGenBuffers(2, buffer);

    return true;
}

void renderFrame(void) {
    GLenum  type;
    GLint   buf_size[2], buf_use[2];
    GLint   size;
    GLfloat tmp[4];
    char    name[14];
    GLint   length;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttrib1f(iLocFillColor, 1.0);
    glEnableVertexAttribArray(iLocFillColor);
    glEnableVertexAttribArray(iLocPosition);
    glDisableVertexAttribArray(iLocFillColor);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices1);

    glVertexAttrib2f(iLocFillColor, 1.0, 1.0);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_SHORT, indices2);
    glGetActiveAttrib(programID, iLocFillColor, 13, &length, &size, &type, name);
    LOGI("glGetActiveAttrib(iLocFillColor):length=%d,size=%d,type=%x,name=%s\n", length,
         size, type, name);

    glVertexAttrib3f(iLocFillColor, 0.0, 1.0, 1.0);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, indices3);
    glGetActiveAttrib(programID, iLocFillColor, 13, &length, &size, &type, name);
    LOGI("glGetActiveAttrib(iLocFillColor):length=%d,size=%d,type=%x,name=%s\n", length,
         size, type, name);

    glVertexAttrib4f(iLocFillColor, 1.0, 1.0, 1.0, 0.0);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices4);
    glGetActiveAttrib(programID, iLocFillColor, 13, &length, &size, &type, name);
    LOGI("glGetActiveAttrib(iLocFillColor):length=%d,size=%d,type=%x,name=%s\n", length,
         size, type, name);

    GLfloat color1[] = {1.0};
    glVertexAttrib1fv(iLocFillColor, color1);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices5);
    glGetActiveAttrib(programID, iLocFillColor, 13, &length, &size, &type, name);
    LOGI("glGetActiveAttrib(iLocFillColor):length=%d,size=%d,type=%x,name=%s\n", length,
         size, type, name);

    GLfloat color2[] = {0.0, 1.0};
    glVertexAttrib2fv(iLocFillColor, color2);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices6);
    glGetActiveAttrib(programID, iLocFillColor, 13, &length, &size, &type, name);
    LOGI("glGetActiveAttrib(iLocFillColor):length=%d,size=%d,type=%x,name=%s\n", length,
         size, type, name);

    GLfloat color3[] = {1.0, 0.0, 1.0};
    glVertexAttrib3fv(iLocFillColor, color3);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices7);
    glGetActiveAttrib(programID, iLocFillColor, 13, &length, &size, &type, name);
    LOGI("glGetActiveAttrib(iLocFillColor):length=%d,size=%d,type=%x,name=%s\n", length,
         size, type, name);

    GLfloat color4[] = {1.0, 1.0, 1.0, 0.0};
    glVertexAttrib4fv(iLocFillColor, color4);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices8);
    glGetActiveAttrib(programID, iLocFillColor, 13, &length, &size, &type, name);
    LOGI("glGetActiveAttrib(iLocFillColor):length=%d,size=%d,type=%x,name=%s\n", length,
         size, type, name);



    glGetVertexAttribiv(iLocPosition, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &size);
    LOGI("glGetVertexAttribiv(iLocPosition,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING):%d\n", size);
    glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_SIZE):%d\n", size);
    glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_STRIDE):%d\n", size);
    glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_TYPE, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_TYPE):0x%x\n", size);
    glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_NORMALIZED):%d\n", size);
    glGetVertexAttribiv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &size);
    LOGI("glGetVertexAttribiv(GL_VERTEX_ATTRIB_ARRAY_ENABLED):%d\n", size);
    glGetVertexAttribfv(iLocFillColor, GL_CURRENT_VERTEX_ATTRIB, tmp);
    LOGI("glGetVertexAttribiv(GL_CURRENT_VERTEX_ATTRIB):%f,%f,%f,%f\n", tmp[0], tmp[1],
         tmp[2], tmp[3]);

    GLfloat tmp_p[9];
    GLvoid  *data;
    glGetVertexAttribPointerv(iLocFillColor, GL_VERTEX_ATTRIB_ARRAY_POINTER, &data);
    LOGI("glGetVertexAttribPointerv(GL_CURRENT_VERTEX_ATTRIB): %x\n", data);

    glDeleteBuffers(2, buffer);
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
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
