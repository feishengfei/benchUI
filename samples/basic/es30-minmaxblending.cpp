/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file minmaxblending.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for minmaxblending related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"
#include <sstream>

using std::string;
using namespace BotsonSDK;

string imagesFilename = "MRbrain";
const int imagesCount = 109;
const int window_Width  = 600;
const int window_Height = 600;
const GLint textureWidth  = 256;
const GLint textureHeight = 256;
const GLint textureDepth  = 128;
const GLfloat minBlendingThreshold = 0.37f;
const short fillerLuminance = 4;
GLuint textureID = 0;
GLuint programID = 0;
GLuint verticesBufferID = 0;
GLuint uvwBufferID = 0;
GLuint vaoID = 0;
GLint isMinBlendingLocation  = -1;
GLint rotationVectorLocation = -1;
GLint textureZOffset = 0;

GLboolean isMinBlendings[]= {0, 1};

const float resetTimeInterval = 5.0f;

const float squareVertices[] = {
    -1.0f,  1.0f, -1.0f, 1.0f,
     1.0f,  1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, 1.0f,
     1.0f,  1.0f, -1.0f, 1.0f,
     1.0f, -1.0f, -1.0f, 1.0f,
};

const float uvwCoordinates[] = {
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
};

void setNextTextureImage(GLvoid* textureData) {
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, textureZOffset, textureWidth,
                             textureHeight, 1, GL_RED_INTEGER, GL_SHORT, textureData));
    textureZOffset++;
}

void loadUniformTextures(int count) {
    GLvoid* textureData = 0;
    Texture::createTexture(textureWidth, textureHeight, fillerLuminance,
                           (short**) &textureData);

    for (int i = 0; i < count; ++i) {
        setNextTextureImage(textureData);
    }
    delete [] (unsigned char *)textureData;
}

void loadImages(void) {
    for (int currentImageIndex = 1; currentImageIndex <= imagesCount;
            ++currentImageIndex) {
        GLvoid* textureData = 0;
        const int digitsCount = 3;

        std::stringstream stringStream;
        stringStream << currentImageIndex;
        string numericExtension = stringStream.str();
        const string filePath = (string)PICTURE_PATH + imagesFilename + "." +
                numericExtension;

        Texture::loadData(filePath.c_str(), (unsigned char**) &textureData);
        setNextTextureImage(textureData);
        free(textureData);
    }
}

bool initializeTextureData(void) {
    const int frontLayersCount = (textureDepth - imagesCount) / 2;
    const int backLayersCount = textureDepth - frontLayersCount - imagesCount;

    loadUniformTextures(frontLayersCount);
    loadImages();
    loadUniformTextures(backLayersCount);

    if(textureZOffset != textureDepth) {
        LOGE("3D texture not completely loaded.");
        return false;
    }
    return true;
}

bool initialize3DTexture(void) {
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, textureID));
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 0, GL_R16I, textureWidth, textureHeight,
                          textureDepth, 0, GL_RED_INTEGER, GL_SHORT, NULL));

    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    if (!initializeTextureData()) {
        LOGE("There occured errors while initializing texture data.");
        return false;
    }
    return true;
}

void initializeProgram(void) {
    const string vertexShaderPath = (string)GLSL_PATH + "Min_Max_Blending_shader.vert";
    const string fragmentShaderPath = (string)GLSL_PATH + "Min_Max_Blending_shader.frag";

    GLuint vertexShaderID   = 0;
    GLuint fragmentShaderID = 0;

    Shader::processShader(&vertexShaderID,   vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programID = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));
}

bool initializeAttribArrays(void) {
    GLint positionLocation = GL_CHECK(glGetAttribLocation(programID, "inputPosition"));
    GLint inputUVWCoordinatesLocation = GL_CHECK(glGetAttribLocation(programID, "inputUVWCoordinates"));

    GL_CHECK(glGenVertexArrays(1, &vaoID));
    GL_CHECK(glBindVertexArray(vaoID));

    if (positionLocation != -1) {
        GL_CHECK(glGenBuffers(1, &verticesBufferID));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, verticesBufferID));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices),
                              squareVertices, GL_STATIC_DRAW));
        GL_CHECK(glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(positionLocation));
    } else {
        LOGE("Could not locate \"inputPosition\" attribute in program [%d].", programID);
        return false;
    }

    if (inputUVWCoordinatesLocation != -1) {
        GL_CHECK(glGenBuffers(1, &uvwBufferID));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, uvwBufferID));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(uvwCoordinates), uvwCoordinates, GL_STATIC_DRAW));
        GL_CHECK(glVertexAttribPointer(inputUVWCoordinatesLocation, 3, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(inputUVWCoordinatesLocation));
    } else {
        LOGE("Could not locate \"inputUVWCoordinates\" attribute in program [%d].", programID);
        return false;
    }
    return true;
}

void initializeUniformData(void) {
    GLint cameraMatrixLocation = GL_CHECK(glGetUniformLocation(programID, "cameraMatrix"));
    GLint projectionMatrixLocation = GL_CHECK(glGetUniformLocation(programID, "projectionMatrix"));
    GLint textureSamplerLocation = GL_CHECK(glGetUniformLocation(programID, "textureSampler"));
    GLint instancesCountLocation = GL_CHECK(glGetUniformLocation(programID, "instancesCount"));
    GLint minBlendingThresholdLocation = GL_CHECK(glGetUniformLocation(programID, "minBlendingThreshold"));
    isMinBlendingLocation  = GL_CHECK(glGetUniformLocation(programID, "isMinBlending"));
    rotationVectorLocation = GL_CHECK(glGetUniformLocation(programID, "rotationVector"));

    if (cameraMatrixLocation != -1) {
        const float cameraTranslation = -2.0f;
        Matrix cameraMatrix = Matrix::createTranslation(0.0f, 0.0f, cameraTranslation);
        GL_CHECK(glUniformMatrix4fv(cameraMatrixLocation, 1, GL_FALSE, cameraMatrix.getAsArray()));
    } else {
        LOGD("Could not locate \"cameraMatrix\" uniform in program [%d].", programID);
    }

    if (projectionMatrixLocation != -1) {
        Matrix projectionMatrix = Matrix::matrixPerspective(45.0f, (float) window_Width / (float) window_Height, 0.01f, 10.0f);
        GL_CHECK(glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix.getAsArray()));
    } else {
        LOGD("Could not locate \"projectionMatrix\" uniform in program [%d].", programID);
    }

    if (textureSamplerLocation != -1) {
        GL_CHECK(glUniform1i(textureSamplerLocation, 0));
    } else {
        LOGD("Could not locate \"textureSampler\" uniform in program [%d].", programID);
    }

    if (instancesCountLocation != -1) {
        GL_CHECK(glUniform1i(instancesCountLocation, textureDepth));
    } else {
        LOGD("Could not locate \"instancesCount\" uniform in program [%d].", programID);
    }

    if (minBlendingThresholdLocation != -1) {
        GL_CHECK(glUniform1f(minBlendingThresholdLocation, minBlendingThreshold));
    } else {
        LOGD("Could not locate \"minBlendingThreshold\" uniform in program [%d].",
             programID);
    }

    if (isMinBlendingLocation == -1) {
        LOGD("Could not locate \"isMinBlending\" uniform in program [%d]. Blending"
             " equation will not change.", programID);
    }

    if (rotationVectorLocation == -1) {
        LOGD("Could not locat \"rotationVector\" uniform in program [%d]. Texture "
             "will not rotate.", programID);
    }
}

bool setupGraphics(void) {
    initializeProgram();
    if (initialize3DTexture()) {
        if (initializeAttribArrays()) {
            initializeUniformData();
            GL_CHECK(glEnable(GL_BLEND));
        } else {
            LOGE("Graphics setup failed at initialization of attribute arrays.");
            return false;
        }
    }
    else {
        LOGE("Graphics setup failed at texture initialization.");
        return false;
    }
    return true;
}

void setBlendEquation(GLboolean isMinBlending) {
    if (isMinBlending) {
        GL_CHECK(glBlendEquation(GL_MIN));
        GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    } else {
        GL_CHECK(glBlendEquation(GL_MAX));
        GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    }
    GL_CHECK(glUniform1i(isMinBlendingLocation, isMinBlending));
}

void renderFrame(void) {
    static float angleX = 0.0f;
    static float angleY = 0.0f;
    static float angleZ = 0.0f;
    const float angleXIncrement = 0.75f;
    const float angleYIncrement = 1.0f;
    const float angleZIncrement = 0.5f;
    float rotationVector[] = {angleX, angleY, angleZ};

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUniform3fv(rotationVectorLocation, 1, rotationVector));
    GL_CHECK(glDrawArraysInstanced(GL_TRIANGLES, 0, 6, textureDepth));

    angleX += angleXIncrement;
    angleY += angleYIncrement;
    angleZ += angleZIncrement;

    if(angleX >= 360.0f) angleX = 0.0f;
    if(angleY >= 360.0f) angleY = 0.0f;
    if(angleZ >= 360.0f) angleZ = 0.0f;
}

void releaseOpenGLObjects(void) {
    GL_CHECK(glDeleteTextures    (1, &textureID       ));
    GL_CHECK(glDeleteBuffers     (1, &verticesBufferID));
    GL_CHECK(glDeleteBuffers     (1, &uvwBufferID     ));
    GL_CHECK(glDeleteVertexArrays(1, &vaoID           ));
    GL_CHECK(glDeleteProgram     (programID           ));
}

void Sample::test() {
    setupGraphics();
    for (int i = 0; i < ARRAY_NUM(isMinBlendings); i++) {
        setBlendEquation(i);
        renderFrame();
        char ss[2];
        sprintf(ss, "%d", i);
        string bmp_file    = filename + "-" + ss + ".bmp";
        LOGI("bmp_file=%s", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
    releaseOpenGLObjects();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
