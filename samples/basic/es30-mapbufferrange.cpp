/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file mapbufferrange.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for mapbufferrange related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFilename = "MapBufferRange.vert";
string fragmentShaderFilename = "MapBufferRange.frag";

const float triangleVertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     0.0f, -0.5f, 0.0f
};

const float triangleVerticesLittle[] = {
    -0.45f, -0.45f, 0.0f,
     0.45f, -0.45f, 0.0f,
     0.0f,  0.45f, 0.0f,
     0.0f, -0.45f, 0.0f
};

const float triangleColors[] = {
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

const int triangleColorsI[] = {
    1, 0, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1,
    0, 1, 0, 1
};

GLushort indices[] = {0,1,2};
const GLubyte subdata[] = {1,3};

static const GLint vertices [] = {
        0, -2,
        -52, 32,
        0, 2,
        2, 0,
        15, 153,
        -2, 0
};

static const GLfloat color[] = {
        0.0, 1.0, 0.0,
        10.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 110.0, 0.0,
        0.0, 0.0, 1.0
};

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
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLint iLocPosition = -1;
GLint iLocFillColor = -1;
GLuint buffers[2];
GLuint vao;

void print_get(GLenum pname) {
	GLint tmp;
	glGetIntegerv(pname, &tmp);
	LOGI("%d\n",tmp);
}

bool setupGraphics(int width, int height) {
    GLfloat  *vtxMappedBuf;
    GLushort *idxMappedBuf;

    string vertexShaderPath   = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    programID = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }

    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));

    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), NULL, GL_STATIC_DRAW);
    vtxMappedBuf = (GLfloat *)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(triangleVertices),
                                               GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    if (vtxMappedBuf == NULL) {
        LOGE("Error mapping vertex buffer object.");
        return false;
    }

    memcpy(vtxMappedBuf, triangleVertices, sizeof(triangleVertices));
    GLvoid *pointer;
    glGetBufferPointerv(GL_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, &pointer);
    GLint64 data;
    glGetBufferParameteri64v(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &data);
    LOGI("element buffer size:%d\n", data);
    GLenum err = glGetError();
    if (err == GL_NO_ERROR) {
        LOGI("get pointer:%x,%p,  vtxMappedBuf=%x,%p\n", pointer, pointer, vtxMappedBuf, vtxMappedBuf);
    } else {
        LOGE("error:0x%.8x\n", err);
    }

    if (glUnmapBuffer(GL_ARRAY_BUFFER) == GL_FALSE) {
        LOGE("Error unmapping array buffer object.");
        return false;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3,
                 NULL, GL_STATIC_DRAW);
    idxMappedBuf = (GLushort *)
            glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLushort) * 3,
                             GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    if (idxMappedBuf == NULL) {
        LOGE("Error mapping vertex buffer object.");
        return false;
    }

    memcpy(idxMappedBuf, indices, sizeof(GLushort) * 3);
    glGetBufferPointerv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_MAP_POINTER, &pointer);
    glGetBufferParameteri64v(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &data);
    LOGI("element buffer size:%d\n", data);
    err = glGetError();
    if (err == GL_NO_ERROR) {
        LOGI("get pointer:%x,%p,  idxMappedBuf=%x,%p\n", pointer, pointer, idxMappedBuf, idxMappedBuf);
    } else {
        LOGE("error:0x%.8x\n", err);
    }

    if (glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER) == GL_FALSE) {
        LOGE("Error unmapping array buffer object.");
        return false;
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(iLocPosition);

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    glDisableVertexAttribArray ( iLocPosition );
    glBindBuffer ( GL_ARRAY_BUFFER, 0 );
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glDeleteBuffers(2,buffers);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
