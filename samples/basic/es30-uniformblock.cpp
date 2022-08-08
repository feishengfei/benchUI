/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file uniformblock.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for uniformblock related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

string vertexShaderFileName = "UniformBlock.vert";
string fragmentShaderFileName = "UniformBlock.frag";

float* coordinates;

GLuint programId;       
GLuint posAttriLoc;
GLuint cubeCoordinatesBufferObjectId = 0;
GLuint uniformBlockDataBufferObjectId = 0;
Matrix cameraProjectionMatrix;
GLuint uboHandle;
GLuint cameraPosBlockIndex;
float cameraPosition[3] = {0.0f, 0.0f, 20.0f};
GLubyte *blockBuffer;

void getTriangleRep(float** coordinatesPtrPtr) {
    int currentIndex  = 0;
    const int numberOfCubeTriangleCoordinates = 1 * 2 * 3 * 3;

    *coordinatesPtrPtr = (float*) malloc(
            numberOfCubeTriangleCoordinates * sizeof(float));

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
}

void deleteObjects(void) {
    free(blockBuffer);
    glDeleteBuffers(1,&uboHandle);
    if (coordinates != NULL) {
        free (coordinates);
        coordinates = NULL;
    }
}

void getUniformBufferData() {
	GLint getdata;
	GLint64 getdata64;
	GLvoid * params;

	glGetBufferParameteriv(GL_UNIFORM_BUFFER,GL_BUFFER_ACCESS_FLAGS,&getdata);
	LOGI("GetBufferParameteriv(GL_UNIFORM_BUFFER,GL_BUFFER_ACCESS_FLAGS):%d\n", getdata);
	glGetBufferParameteriv(GL_UNIFORM_BUFFER,GL_BUFFER_MAPPED,&getdata);
	LOGI("GetBufferParameteriv(GL_UNIFORM_BUFFER,GL_BUFFER_MAPPED):%d\n",getdata);
	glGetBufferParameteri64v(GL_UNIFORM_BUFFER,GL_BUFFER_MAP_LENGTH,&getdata64);
	LOGI("glGetBufferParameteri64v(GL_UNIFORM_BUFFER,GL_BUFFER_MAP_LENGTH):%d	\n",getdata64);
	glGetBufferParameteri64v(GL_UNIFORM_BUFFER,GL_BUFFER_MAP_OFFSET,&getdata64);
	LOGI("glGetBufferParameteri64v(GL_UNIFORM_BUFFER,GL_BUFFER_MAP_OFFSET):%d\n",getdata64);
	glGetBufferParameteriv(GL_UNIFORM_BUFFER,GL_BUFFER_SIZE,&getdata);
	LOGI("GetBufferParameteriv(GL_UNIFORM_BUFFER,GL_BUFFER_SIZE):%d\n",getdata);
	glGetBufferParameteriv(GL_UNIFORM_BUFFER,GL_BUFFER_USAGE,&getdata);
	LOGI("GetBufferParameteriv(GL_UNIFORM_BUFFER,GL_BUFFER_USAGE):%d\n",getdata);
	glGetBufferPointerv(GL_UNIFORM_BUFFER, GL_BUFFER_MAP_POINTER, &params);
	LOGI("GetBufferPointerv(GL_UNIFORM_BUFFER):%x\n",params);
}

void getUniformBlockData() {
	GLenum pname[] = {
		GL_UNIFORM_BLOCK_BINDING,
		GL_UNIFORM_BLOCK_DATA_SIZE,
		GL_UNIFORM_BLOCK_NAME_LENGTH,
		GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,
		GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,
		GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER,
		GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER,
	};

    GLenum pnames[] = {
	GL_UNIFORM_TYPE,
	GL_UNIFORM_SIZE,
	GL_UNIFORM_NAME_LENGTH,
	GL_UNIFORM_BLOCK_INDEX,
	GL_UNIFORM_OFFSET,
	GL_UNIFORM_ARRAY_STRIDE,
	GL_UNIFORM_MATRIX_STRIDE,
	GL_UNIFORM_IS_ROW_MAJOR
    };

	GLint param;
	char tmpname[22];
	GLsizei length=0;
    GLint paramsi[2];

	for(int i=0; i<ARRAY_NUM(pname); i++) {
		glGetActiveUniformBlockiv(programId, cameraPosBlockIndex,
                                  GL_UNIFORM_BLOCK_DATA_SIZE, &param);
		LOGI("glGetActiveUniformBlockiv(GL_UNIFORM_BLOCK_DATA_SIZE) = %d\n",param);
	}

	glGetProgramiv(programId, GL_ACTIVE_UNIFORM_BLOCKS, &param);
	LOGI("glGetProgramiv(GL_ACTIVE_UNIFORM_BLOCKS) = %d\n",param);
	glGetProgramiv(programId, GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, &param);
	LOGI("glGetProgramiv(GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH) = %d\n",param);
	
	glGetActiveUniformBlockName(programId, cameraPosBlockIndex,sizeof(tmpname),
                                &length,tmpname);
	LOGI("glGetActiveUniformBlockName: length=%d,name=%s\n",length,tmpname);

    const GLchar *name[]={"cameraProjectionMatrix","cameraPosition"};
    GLuint indices[2];
    glGetUniformIndices(programId,2,name,indices);
    for(int i=0; i<ARRAY_NUM(pnames); i++) {
	glGetActiveUniformsiv(programId, 2, indices, pnames[i], paramsi);
        LOGI("glGetActiveUniformsiv(%s): %d, %d\n", get_enum_name(pnames[i]),
             paramsi[0], paramsi[1]);
    }
    GLint paramui;
    glGetIntegeri_v(GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, uboHandle, &paramui);
    LOGI("GetIntegeri_v(GL_TRANSFORM_FEEDBACK_BUFFER_BINDING): %d\n",paramui);
}

bool setupCubesAndPlaneProgram(void) {
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFileName;
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFileName;
    programId = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    posAttriLoc = GL_CHECK(glGetAttribLocation(programId, "attributePosition"));   

    cameraPosBlockIndex = GL_CHECK(glGetUniformBlockIndex(programId,
            "cameraPosUniformBlock"));

    GLint blockSize;
    glGetActiveUniformBlockiv(programId, cameraPosBlockIndex,
                              GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
    blockBuffer=(GLubyte *)malloc(blockSize);
    const GLchar *name[]={"cameraProjectionMatrix","cameraPosition"};
    GLuint indices[2];
    glGetUniformIndices(programId,2,name,indices);
    GLint offset[2];
    glGetActiveUniformsiv(programId,2,indices,GL_UNIFORM_OFFSET,offset);
    LOGI("offset:%d,%d\n\n",offset[0],offset[1]);
    memcpy(blockBuffer+offset[0], cameraProjectionMatrix.getAsArray(),
           4*4*sizeof(float));
    memcpy(blockBuffer+offset[1], cameraPosition, 3*sizeof(float));
    glBindBuffer(GL_UNIFORM_BUFFER,uboHandle);
    glBufferData(GL_UNIFORM_BUFFER,blockSize,blockBuffer,GL_DYNAMIC_DRAW);

    getUniformBufferData();
    getUniformBlockData();

    return true;
}

bool setupGraphics(int width, int height) {
    cameraProjectionMatrix = Matrix::matrixPerspective(degreesToRadians(60.0f), float(width) / float(height), 1.0f, 50.0f);

    GL_CHECK(glGenBuffers(1, &uboHandle));

    getTriangleRep(&coordinates);
    GL_CHECK(glViewport(0, 0, width, height));
    setupCubesAndPlaneProgram();

    return true;
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

    GL_CHECK(glUseProgram(programId));

    GL_CHECK(glEnableVertexAttribArray(posAttriLoc));
    GL_CHECK(glVertexAttribPointer    (posAttriLoc, 3, GL_FLOAT, GL_FALSE, 0, coordinates));
    GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER,uboHandle));
    GL_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER,cameraPosBlockIndex,uboHandle));

    GL_CHECK(glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 2));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
    deleteObjects();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
