/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file instancing.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for instancing related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Model.h"

using namespace BotsonSDK;
using std::string;

GLuint programID = 0;
const int numberOfCubesToGenerate = 10;
int numberOfCubeTriangleCoordinates = 0;
float* cubeTrianglesCoordinates = NULL;
int numberOfValuesInVertexColorsArray = 0;
float* vertexColors = NULL;
const int numberOfValuesInCubeColorsArray = 4 * numberOfCubesToGenerate;
float cubeColors[numberOfValuesInCubeColorsArray] = {0};
const float cubeSize = 2.5f;
const int window_Height = 600;
const int window_Width = 800;
GLint cameraPositionLocation = 0;
GLuint uniformBlockIndex = 0;
GLint perspectiveMatrixLocation = 0;
GLint positionLocation = 0;
GLint cubeVertexColorLocation = 0;
GLint timeLocation = 0;
const GLuint numberOfBufferObjectIds = 3;
GLuint bufferObjectIds[numberOfBufferObjectIds] = {0};
GLuint cubeColorsBufferObjectId = 0;
GLuint cubeCoordinatesBufferObjectId = 0;
GLuint uniformBlockDataBufferObjectId = 0;    
float startPosition[numberOfCubesToGenerate] = {0};

const float perspectiveVector[] = {45.0f, (float)window_Width / (float)window_Height,
                                   0.1f, 1000.0f};
const float cameraVector[] = {0.0f, 0.0f, -60.0f};

void generateStartPosition(void) {
    float spaceBetweenCubes = (2 * M_PI) / (numberOfCubesToGenerate);
    for (int allCubes = 0; allCubes < numberOfCubesToGenerate; allCubes++) {
        startPosition[allCubes] = allCubes * spaceBetweenCubes;
    }
}

void fillCubeColorsArray(void) {
    for (int allComponents = 0; allComponents < numberOfValuesInCubeColorsArray;
            allComponents++) {
        cubeColors[allComponents] = (float)rand() / (float)RAND_MAX;
    }
}

bool fillVertexColorsArray(void) {
    numberOfValuesInVertexColorsArray = int (numberOfCubeTriangleCoordinates * 4 / 3);
    vertexColors = (float*) malloc (numberOfValuesInVertexColorsArray * sizeof(float));

    if (vertexColors != NULL) {
        for (int allComponents = 0; allComponents < numberOfValuesInVertexColorsArray;
                allComponents++) {
            vertexColors[allComponents] = (float)rand() / (float)RAND_MAX;
        }
    } else {
        LOGE ("Could not allocate memory for vertexColors array.");
        return false;
    }
    return true;
}

bool createCubesData(void) {
    Model::getCubeTriangleRepresentation(cubeSize, &numberOfCubeTriangleCoordinates,
                                         &cubeTrianglesCoordinates);
    if (cubeTrianglesCoordinates == NULL) {
        return false;
    }

    generateStartPosition();
    fillCubeColorsArray();
    if (!fillVertexColorsArray()) {
        free(cubeTrianglesCoordinates);
        cubeTrianglesCoordinates = NULL;
        return false;
    }
    return true;
}

bool initializeData(void) {
    if(createCubesData()) {
        GL_CHECK(glDisable(GL_CULL_FACE));
        GL_CHECK(glEnable(GL_DEPTH_TEST));
        GL_CHECK(glDepthFunc(GL_LEQUAL));
        GL_CHECK(glGenBuffers(numberOfBufferObjectIds, bufferObjectIds));

        cubeCoordinatesBufferObjectId  = bufferObjectIds[0];
        cubeColorsBufferObjectId       = bufferObjectIds[1];
        uniformBlockDataBufferObjectId = bufferObjectIds[2];

        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, cubeCoordinatesBufferObjectId));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, numberOfCubeTriangleCoordinates * sizeof(float),
                              cubeTrianglesCoordinates, GL_STATIC_DRAW));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, cubeColorsBufferObjectId));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, numberOfValuesInVertexColorsArray * sizeof(float),
                              vertexColors, GL_STATIC_DRAW));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, uniformBlockDataBufferObjectId));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(startPosition) +
                                               sizeof(cubeColors), NULL, GL_STATIC_DRAW));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(startPosition),
                                 startPosition));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(startPosition),
                                 sizeof(cubeColors), cubeColors));
        free(vertexColors);
        vertexColors = NULL;

        free(cubeTrianglesCoordinates);
        cubeTrianglesCoordinates = NULL;
    } else {
        LOGE("Could not initialize data used for rendering.");
        return false;
    }
    return true;
}

bool setupProgram() {
    bool functionCallResult = true;

    string vertexShaderPath = ((string)GLSL_PATH) + "instancing.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "instancing.frag";
    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
            fragmentShaderPath.c_str());
    GL_CHECK(glUseProgram(programID));

    positionLocation = GL_CHECK(glGetAttribLocation(programID, "attributePosition"));
    cubeVertexColorLocation = GL_CHECK(glGetAttribLocation(programID, "attributeColor"));
    perspectiveMatrixLocation = GL_CHECK(glGetUniformLocation(programID, "perspectiveVector"));
    cameraPositionLocation = GL_CHECK(glGetUniformLocation(programID, "cameraVector"));
    uniformBlockIndex = GL_CHECK(glGetUniformBlockIndex(programID, "CubesUniformBlock"));

    if (positionLocation == -1) {
        LOGE("Could not retrieve attribute location: positionLocation");
        functionCallResult = false;
    }

    if (cubeVertexColorLocation == -1) {
        LOGE("Could not retrieve attribute location: cubeVertexColorLocation");
        functionCallResult = false;
    }

    if (perspectiveMatrixLocation == -1) {
        LOGE("Could not retrieve uniform location: perspectiveMatrixLocation");
        functionCallResult = false;
    }

    if (cameraPositionLocation == -1) {
        LOGE("Could not retrieve uniform location: cameraPositionLocation");
        functionCallResult = false;
    }

    if (timeLocation == -1) {
        LOGE("Could not retrieve uniform location: timeLocation");
        functionCallResult = false;
    }

    if (uniformBlockIndex == GL_INVALID_INDEX) {
        LOGE("Could not retrieve uniform block index: uniformBlockIndex");
        functionCallResult = false;
    }
    return functionCallResult;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
   // GL_CHECK(glViewport(0, 0, window_Width, window_Height));
    GL_CHECK(glUniform4fv(perspectiveMatrixLocation, 1, perspectiveVector));
    GL_CHECK(glUniform3fv(cameraPositionLocation,    1, cameraVector));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, cubeCoordinatesBufferObjectId));
    GL_CHECK(glEnableVertexAttribArray(positionLocation));
    GL_CHECK(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, cubeColorsBufferObjectId));
    GL_CHECK(glEnableVertexAttribArray(cubeVertexColorLocation));
    GL_CHECK(glVertexAttribPointer(cubeVertexColorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glUniformBlockBinding(programID, uniformBlockIndex, 0));
    GL_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBlockDataBufferObjectId));
    GL_CHECK(glDrawArraysInstanced(GL_TRIANGLES, 0, numberOfCubeTriangleCoordinates,
                                   numberOfCubesToGenerate));
}

void Sample::test() {
    initializeData();
    setupProgram();
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
    GL_CHECK(glDeleteBuffers(numberOfBufferObjectIds, bufferObjectIds));
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}