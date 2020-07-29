/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file sync.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for sync related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

struct GeometryProperties {
    float* coordinates;                        
    float* position;                           
    int    numberOfElementsInCoordinatesArray; 
    int    numberOfElementsInPositionArray;    
    float  scalingFactor;                      
} cube;

struct WindowProperties {
    int height;
    int width; 
} window;

struct CubesAndPlaneProgramProperties {
    GLuint programId;       
    GLuint positionAttributeLocation;
} cubesAndPlaneProgram;

GLuint cubeCoordinatesBufferObjectId = 0; 
GLuint uniformBlockDataBufferObjectId = 0; 

Matrix cameraProjectionMatrix;
GLuint uboHandle;
GLuint cameraPosBlockIndex;
float cameraPosition[3] = {0.0f, 0.0f, 20.0f}; 
GLubyte *blockBuffer;

GLsync emitSync;

bool initializeStructureData(void) {
    window.height = 480;
    window.width  = 600;

    cube.coordinates = NULL;
    cube.numberOfElementsInCoordinatesArray = 0;
    cube.numberOfElementsInPositionArray = 4;
    cube.scalingFactor = 1.0f;

    cube.position = (float*) malloc (cube.numberOfElementsInPositionArray * sizeof(float));
    cube.position[0] =  1.0f; 
    cube.position[1] =  1.0f; 
    cube.position[2] =  1.0f; 
    cube.position[3] =  1.0f; 

    cameraProjectionMatrix = Matrix::matrixPerspective(degreesToRadians(60.0f), 
            float(window.width) / float(window.height), 1.0f, 50.0f);

    return true;
}

void createObjects(void) {   
    GLuint bufferObjectIds [3] = {0};
    GL_CHECK(glGenBuffers(3, bufferObjectIds));
    cubeCoordinatesBufferObjectId = bufferObjectIds[0];
    uniformBlockDataBufferObjectId = bufferObjectIds[1];
    uboHandle = bufferObjectIds[2];
}

void deleteObjects(void) {
    glDeleteBuffers(1,&uboHandle);
    GL_CHECK(glDeleteBuffers(1, &cubeCoordinatesBufferObjectId));
    GL_CHECK(glDeleteBuffers(1, &uniformBlockDataBufferObjectId));
}

void deallocateMemory(void) {
    if (cube.coordinates != NULL) {
        free (cube.coordinates);
        cube.coordinates = NULL;
    }

    if (cube.position != NULL) {
        free (cube.position);
        cube.position = NULL;
    }
}

void getTriangleRep(float   scalingFactor, int*    numberOfCoordinatesPtr, 
                    float** coordinatesPtrPtr) {
    int currentIndex = 0;
    const int numberOfCubeTriangleCoordinates = 1 * 2 * 3 * 3;
    *coordinatesPtrPtr = (float*) malloc(numberOfCubeTriangleCoordinates * sizeof(float));

    const Vec3f pointA = {-1.0f,  1.0f,  1.0f};
    const Vec3f pointB = {-1.0f,  1.0f, -1.0f};
    const Vec3f pointC = { 1.0f,  1.0f, -1.0f};
    const Vec3f pointD = { 1.0f,  1.0f,  1.0f};
    const Vec3f pointE = {-1.0f, -1.0f,  1.0f};
    const Vec3f pointF = {-1.0f, -1.0f, -1.0f};
    const Vec3f pointG = { 1.0f, -1.0f, -1.0f};
    const Vec3f pointH = { 1.0f, -1.0f,  1.0f};

    (*coordinatesPtrPtr)[currentIndex++] = pointG.x;
    (*coordinatesPtrPtr)[currentIndex++] = pointG.y;
    (*coordinatesPtrPtr)[currentIndex++] = pointG.z;
    (*coordinatesPtrPtr)[currentIndex++] = pointC.x;
    (*coordinatesPtrPtr)[currentIndex++] = pointC.y;
    (*coordinatesPtrPtr)[currentIndex++] = pointC.z;
    (*coordinatesPtrPtr)[currentIndex++] = pointB.x;
    (*coordinatesPtrPtr)[currentIndex++] = pointB.y;
    (*coordinatesPtrPtr)[currentIndex++] = pointB.z;
    (*coordinatesPtrPtr)[currentIndex++] = pointG.x;
    (*coordinatesPtrPtr)[currentIndex++] = pointG.y;
    (*coordinatesPtrPtr)[currentIndex++] = pointG.z;
    (*coordinatesPtrPtr)[currentIndex++] = pointB.x;
    (*coordinatesPtrPtr)[currentIndex++] = pointB.y;
    (*coordinatesPtrPtr)[currentIndex++] = pointB.z;
    (*coordinatesPtrPtr)[currentIndex++] = pointF.x;
    (*coordinatesPtrPtr)[currentIndex++] = pointF.y;
    (*coordinatesPtrPtr)[currentIndex++] = pointF.z;

    if (scalingFactor != 1.0f) {
        for (int i = 0; i < numberOfCubeTriangleCoordinates; i++) {
            (*coordinatesPtrPtr)[i] *= scalingFactor;
        }
    }

    if (numberOfCoordinatesPtr != NULL) {
        *numberOfCoordinatesPtr = numberOfCubeTriangleCoordinates;
    }
}

bool initializeData() {
GLvoid *param[3];
    GLuint bufferObjectIds [3] = {0};
    GL_CHECK(glGenBuffers(3, bufferObjectIds));
    cubeCoordinatesBufferObjectId = bufferObjectIds[0];
    uniformBlockDataBufferObjectId = bufferObjectIds[1];
    uboHandle = bufferObjectIds[2];

    getTriangleRep(cube.scalingFactor, &cube.numberOfElementsInCoordinatesArray, 
                   &cube.coordinates);
    return true;
}

void setUpAndUseProgramObject(GLint programId, string fragmentShaderFileName, 
                              string vertexShaderFileName) {
    GLuint vertexShaderId = 0;
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFileName;
    Shader::processShader(&vertexShaderId, vertexShaderPath.c_str(), GL_VERTEX_SHADER);

    GLuint fragmentShaderId = 0;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFileName;
    Shader::processShader(&fragmentShaderId, fragmentShaderPath.c_str(), 
                          GL_FRAGMENT_SHADER);

    GL_CHECK(glAttachShader(programId, vertexShaderId));
    GL_CHECK(glAttachShader(programId, fragmentShaderId));

    GL_CHECK(glLinkProgram(programId));
    GL_CHECK(glUseProgram (programId));
}

bool setupCubesAndPlaneProgram(void) {
    cubesAndPlaneProgram.programId = GL_CHECK(glCreateProgram());
    setUpAndUseProgramObject(cubesAndPlaneProgram.programId, "Sync.frag", "Sync.vert");

    cubesAndPlaneProgram.positionAttributeLocation = GL_CHECK(glGetAttribLocation
                                                                      (cubesAndPlaneProgram.programId,
                                                                       "attributePosition"));
    cameraPosBlockIndex = GL_CHECK(glGetUniformBlockIndex
                                           (cubesAndPlaneProgram.programId, "cameraPosUniformBlock"));

    GLint blockSize;
    glGetActiveUniformBlockiv(cubesAndPlaneProgram.programId, cameraPosBlockIndex,
                              GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
    char    tmpname[22];
    GLsizei length      = 0;
    glGetActiveUniformBlockName(cubesAndPlaneProgram.programId,
                                cameraPosBlockIndex, sizeof(tmpname), &length, tmpname);
    LOGI("length=%d,name=%s\n", length, tmpname);
    blockBuffer = (GLubyte *)malloc(blockSize);
    const GLchar *name[] = {"cameraProjectionMatrix", "cameraPosition"};
    GLuint       indices[2];
    glGetUniformIndices(cubesAndPlaneProgram.programId, 2, name, indices);
    GLint offset[2];
    glGetActiveUniformsiv(cubesAndPlaneProgram.programId, 2, indices, GL_UNIFORM_OFFSET, offset);
    LOGI("offset:%d,%d\n\n", offset[0], offset[1]);
    memcpy(blockBuffer + offset[0], cameraProjectionMatrix.getAsArray(), 4 * 4 * sizeof(float));
    memcpy(blockBuffer + offset[1], cameraPosition, 3 * sizeof(float));
    glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
    glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glViewport(0, 0, window.width, window.height));

    GL_CHECK(glUseProgram(cubesAndPlaneProgram.programId));

    GL_CHECK(glEnableVertexAttribArray(cubesAndPlaneProgram.positionAttributeLocation));
    GL_CHECK(glVertexAttribPointer(cubesAndPlaneProgram.positionAttributeLocation,
                                   3, GL_FLOAT, GL_FALSE, 0, cube.coordinates));
    glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
    glBindBufferBase(GL_UNIFORM_BUFFER, cameraPosBlockIndex, uboHandle);

    emitSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    GL_CHECK(glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 2));
    glClientWaitSync(emitSync, GL_SYNC_FLUSH_COMMANDS_BIT, 10000000000);
}

void Sample::test() {
    initializeStructureData();
    initializeData();
    setupCubesAndPlaneProgram();
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    bool isSync = glIsSync(emitSync);
    LOGI("isSync=%d\n", isSync);
    GLsizei bufSize = 1;
    GLsizei length;
    GLint   value;
    glGetSynciv(emitSync, GL_OBJECT_TYPE, bufSize, &length, &value);
    LOGI("GL_OBJECT_TYPE: length=%d, value=0x%x\n", length, value);
    glGetSynciv(emitSync, GL_SYNC_STATUS, bufSize, &length, &value);
    LOGI("GL_SYNC_STATUS: length=%d, value=0x%x\n", length, value);
    glGetSynciv(emitSync, GL_SYNC_CONDITION, bufSize, &length, &value);
    LOGI("GL_SYNC_CONDITION: length=%d, value=0x%x\n", length, value);
    glGetSynciv(emitSync, GL_SYNC_FLAGS, bufSize, &length, &value);
    LOGI("GL_SYNC_FLAGS: length=%d, value=0x%x\n", length, value);
    glDeleteSync(emitSync);
    free(blockBuffer);
    deleteObjects();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
