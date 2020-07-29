/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file framebufferobject.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for framebufferobject related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

#define FBO_WIDTH    256
#define FBO_HEIGHT    256

static const GLubyte cubeIndices[] = {
    0, 1, 2, 3,   3, 4,   4, 5, 6, 7,   7, 8,   8, 9, 10, 11,   11, 12,   12, 13, 14, 15,   15, 16,   16, 17, 18, 19,   19, 20,   20, 21, 22, 23,
};

static const float cubeVertices[] = {

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,

     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
};

static const float cubeTextureCoordinates[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
};

static const float cubeColors[] = {
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
};

GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocTextureMix = -1;
GLint iLocTexture = -1;
GLint iLocFillColor = -1;
GLint iLocTexCoord = -1;
GLint iLocProjection = -1;
GLint iLocModelview = -1;

static float angleX = 0;
static float angleY = 0;
static float angleZ = 0;
Matrix rotationX;
Matrix rotationY;
Matrix rotationZ;
Matrix translation;
Matrix modelView;
Matrix projection;
Matrix projectionFBO;

GLuint iFBO = 0;

GLuint iFBOTex = 0;

int window_Width = -1;
int window_Height = -1;

bool setupGraphics(int width, int height) {
    window_Width = width;
    window_Height = height;

    string vertexShaderPath = ((string)GLSL_PATH) + "eglpreserve.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "eglpreserve.frag";

    projection = Matrix::matrixPerspective(45.0f, window_Width/(float)window_Height, 0.01f, 100.0f);
    projectionFBO = Matrix::matrixPerspective(45.0f, (FBO_WIDTH / (float)FBO_HEIGHT), 0.01f, 100.0f);

    translation = Matrix::createTranslation(0.0f, 0.0f, -2.0f);

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glCullFace(GL_BACK));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GL_CHECK(glGenTextures(1, &iFBOTex));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, iFBOTex));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, FBO_WIDTH, FBO_HEIGHT, 0,
                          GL_RGBA, GL_UNSIGNED_BYTE, NULL));
    GL_CHECK(glGenFramebuffers(1, &iFBO));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, iFBO));
    GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, iFBOTex, 0));

    GLenum iResult = GL_CHECK(glCheckFramebufferStatus(GL_FRAMEBUFFER));
    if(iResult != GL_FRAMEBUFFER_COMPLETE) {
        LOGI("Framebuffer incomplete at %s:%i\n", __FILE__, __LINE__);
        return false;
    }

    GLint param;
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,&param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE=%d\n",param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,&param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME=%d\n",param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL,&param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL=%d\n",param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE,&param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE=%d\n",param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,&param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE=%d\n",param);
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,GL_STENCIL_ATTACHMENT,GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,&param);
    LOGI("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE=%d\n",param);

    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    if(iLocPosition == -1) {
        LOGE("Attribute not found at %s:%i\n", __FILE__, __LINE__);
        return false;
    }
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    iLocTextureMix = GL_CHECK(glGetUniformLocation(programID, "u_fTex"));
    if(iLocTextureMix == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniform1f(iLocTextureMix, 0.0));
    }

    iLocTexture = GL_CHECK(glGetUniformLocation(programID, "u_s2dTexture"));
    if(iLocTexture == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniform1i(iLocTexture, 0));
    }

    iLocFillColor = GL_CHECK(glGetAttribLocation(programID, "a_v4FillColor"));
    if(iLocFillColor == -1) {
        LOGW("Warning: Attribute not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
    }

    iLocTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_v2TexCoord"));
    if(iLocTexCoord == -1) {
        LOGW("Warning: Attribute not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }

    iLocProjection = GL_CHECK(glGetUniformLocation(programID, "u_m4Projection"));
    if(iLocProjection == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, projection.getAsArray()));
    }

    iLocModelview = GL_CHECK(glGetUniformLocation(programID, "u_m4Modelview"));
    if(iLocModelview == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    }

    return true;
}

void renderFrame(void) {
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0,
                                   cubeVertices));

    if(iLocFillColor != -1) {
        GL_CHECK(glEnableVertexAttribArray(iLocFillColor));
        GL_CHECK(glVertexAttribPointer(iLocFillColor, 4, GL_FLOAT, GL_FALSE, 0, cubeColors));
    }

    if(iLocTexCoord != -1) {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, cubeTextureCoordinates));
    }

    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, iFBO));
    GL_CHECK(glViewport(0, 0, FBO_WIDTH, FBO_HEIGHT));
    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    rotationX = Matrix::createRotationX(-angleZ);
    rotationY = Matrix::createRotationY(-angleY);
    rotationZ = Matrix::createRotationZ(-angleX);

    modelView = translation * rotationX;
    modelView = modelView * rotationY;
    modelView = modelView * rotationZ;

    GL_CHECK(glUniformMatrix4fv(iLocModelview, 1, GL_FALSE, modelView.getAsArray()));
    GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, projectionFBO.getAsArray()));

    if(iLocTextureMix != -1) {
        GL_CHECK(glUniform1f(iLocTextureMix, 0.0));
    }

    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, sizeof(cubeIndices) / sizeof(GLubyte),
                            GL_UNSIGNED_BYTE, cubeIndices));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER,0));
    GL_CHECK(glViewport(0, 0, window_Width, window_Height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 1.0f, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    rotationX = Matrix::createRotationX(angleX);
    rotationY = Matrix::createRotationY(angleY);
    rotationZ = Matrix::createRotationZ(angleZ);

    modelView = translation * rotationX;
    modelView = modelView * rotationY;
    modelView = modelView * rotationZ;

    GL_CHECK(glUniformMatrix4fv(iLocModelview, 1, GL_FALSE, modelView.getAsArray()));
    GL_CHECK(glUniformMatrix4fv(iLocProjection, 1, GL_FALSE, projection.getAsArray()));

    if(iLocTextureMix != -1) {
        GL_CHECK(glUniform1f(iLocTextureMix, 1.0));
    }

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, iFBOTex));

    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, sizeof(cubeIndices) / sizeof(GLubyte),
                            GL_UNSIGNED_BYTE, cubeIndices));

    angleX += 3;
    angleY += 20;
    angleZ += 1;
    if(angleX >= 360) angleX -= 360;
    if(angleZ >= 360) angleZ -= 360;
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    while(angleY <= 360) {
        renderFrame();
        char ss[3];
        sprintf(ss, "_%d", (int)angleY);
        string bmp_file = filename + ss + ".bmp";
        LOGI("bmp_file=%s", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
