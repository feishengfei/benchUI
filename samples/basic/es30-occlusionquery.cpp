/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file occlusionquery.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for occlusionquery related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Model.h"

using std::string;
using namespace BotsonSDK;

const int window_Width  = 800;
const int window_Height = 600;
const float intervalInSeconds = 10.0f;
GLuint programId = 0;
const int numberOfCubes = 50;
const int numberOfSamples = 256;
const float squareness1	= 0.3f;
const float squareness2	= 0.3f;
const float roundedCubeScaleFactor = 2.5f;
const float normalCubeScaleFactor = 2.49f;
float* roundedCubeCoordinates = NULL; 
float* roundedCubeNormalVectors = NULL;
int numberOfRoundedCubesVertices = 0;
int numberOfRoundedCubeCoordinates = 0;
int numberOfRoundedCubeNormalVectors = 0;
Vec2f randomCubesPositions[numberOfCubes];
bool previouslyVisible[numberOfCubes] = { false };
const float minimumDistance = 4.0f;
GLuint cubeQuery[numberOfCubes] = { 0 };
bool occlusionQueriesOn = false;
float angleY = 0.0f;
const float cameraRadius = 22.0f;
const float yCameraTranslation = 1.25f;
Matrix viewMatrix;
Matrix rotatedViewMatrix;
GLint renderPlaneUniformLocation = 0;
GLint cubesLocationsUniformLocation = 0;
GLuint viewMatrixUniformLocation = 0;
float sortedCubesPositions[2 * numberOfCubes] = { 0.0f };
const float planeScalingFactor = 40.0f;
const float planeDividend = 3.0f;
GLuint planeVertexArrayObjectId		  = 0;
GLuint normalCubeVertexArrayObjectId  = 0;
GLuint roundedCubeVertexArrayObjectId = 0;
GLuint planeVerticesBufferId = 0;
GLuint planeNormalVectorsBufferId = 0;
GLuint normalCubeBufferId = 0;
GLuint roundedCubeVerticesBufferId = 0;
GLuint roundedCubeNormalVectorsBufferId = 0;
float* normalCubeVertices = NULL;
int sizeOfNormalCubeVerticesArray = 0;
float* planeVertices = NULL;
int sizeOfPlaneVerticesArray = 0;
float* planeNormalVectors = NULL;
int sizeOfPlaneNormalsArray = 0;
bool modeChanged = false;
int numberOfRoundedCubesDrawn = 0;

inline bool inNeighbourhood(const Vec2f& point, float minDistance, int j) {
	for (int i = 0; i < j; i++) {
		if (distanceBetweenPoints(point, randomCubesPositions[i]) < minDistance) {
			return true;
		}
	}
	return false;
}

void generateCubesLocations(float planeWidth, float planeHeight, float minDistance) {
	float xRange = planeWidth / planeDividend;
	float zRange = planeHeight / planeDividend;
	float loopsCounter = 0;

	Vec2f firstRandomPoint = {(xRange + xRange) * uniformRandomNumber() - xRange,
							  (zRange + zRange) * uniformRandomNumber() - zRange};
	randomCubesPositions[0] = firstRandomPoint;
	
	for (int i = 1; i < numberOfCubes; i++) {
		if (loopsCounter > numberOfCubes * numberOfCubes) {
			return;
		}

		Vec2f randomPoint = {(xRange + xRange) * BotsonSDK::uniformRandomNumber() - xRange,
							 (zRange + zRange) * BotsonSDK::uniformRandomNumber() - zRange};

		if (!inNeighbourhood(randomPoint, minDistance, i)) {
            randomCubesPositions[i] = randomPoint;
		} else {
			i -= 1;
		}
		loopsCounter++;
	}
}

void sortCubePositions(float* arrayToSort) {
    int  max     = (numberOfCubes * 2) - 4;
    bool swapped = true;
    while (swapped) {
        swapped    = false;
        for (int i = 0; i <= max; i += 2) {
            Vec2f firstCubeLocation, secondCubeLocation;
            firstCubeLocation.x  = arrayToSort[i];
            firstCubeLocation.y  = arrayToSort[i + 1];
            secondCubeLocation.x = arrayToSort[i + 2];
            secondCubeLocation.y = arrayToSort[i + 3];
            Vec3f first_cube_location              = {firstCubeLocation.x, 1, firstCubeLocation.y};
            Vec3f second_cube_location             = {secondCubeLocation.x, 1, secondCubeLocation.y};
            Vec3f transformed_first_cube_location  = Matrix::vertexTransform(
                    &first_cube_location, &rotatedViewMatrix);
            Vec3f transformed_second_cube_location = Matrix::vertexTransform(
                    &second_cube_location, &rotatedViewMatrix);

            if (transformed_first_cube_location.z < transformed_second_cube_location.z) {
                arrayToSort[i]     = secondCubeLocation.x;
                arrayToSort[i + 1] = secondCubeLocation.y;
                arrayToSort[i + 2] = firstCubeLocation.x;
                arrayToSort[i + 3] = firstCubeLocation.y;

                bool temp = previouslyVisible[i / 2];
                previouslyVisible[i / 2]     = previouslyVisible[i / 2 + 1];
                previouslyVisible[i / 2 + 1] = temp;
                swapped = true;
            }
        }
    }
}

void rewriteVec2fArrayToFloatArray() {
	for (int i = 0; i < numberOfCubes; i++) {
	    sortedCubesPositions[i * 2]     = randomCubesPositions[i].x;
	    sortedCubesPositions[i * 2 + 1] = randomCubesPositions[i].y;
	}
}

inline void sendCubeLocationVectorToUniform(int whichCube) {
    float tempArray[3];
    tempArray[0] = sortedCubesPositions[2 * whichCube];
    tempArray[1] = roundedCubeScaleFactor;
    tempArray[2] = sortedCubesPositions[2 * whichCube + 1];
    GL_CHECK(glUniform3fv(cubesLocationsUniformLocation, 1, tempArray));
}

bool setupGraphics(int width, int height) {

    GL_CHECK(glClearColor(0.3f, 0.6f, 0.70f, 1.0f));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glDepthFunc(GL_LEQUAL));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLuint vertexShaderId   = 0;
    string vertexShaderPath = (string)GLSL_PATH + "vertex.vert";
    Shader::processShader(&vertexShaderId, vertexShaderPath.c_str(),
                          GL_VERTEX_SHADER);
    GLuint fragmentShaderId   = 0;
    string fragmentShaderPath = (string)GLSL_PATH + "fragment.frag";
    Shader::processShader(&fragmentShaderId, fragmentShaderPath.c_str(),
                          GL_FRAGMENT_SHADER);
    programId                       = GL_CHECK(glCreateProgram());
    GL_CHECK(glAttachShader(programId, vertexShaderId));
    GL_CHECK(glAttachShader(programId, fragmentShaderId));
    GL_CHECK(glLinkProgram(programId));
    GL_CHECK(glUseProgram(programId));

    Matrix projectionMatrix = Matrix::matrixPerspective(degreesToRadians(45.0f),
                                                        float(window_Width) / float(window_Height), 0.1f, 50.0f);
    GLuint projectionMatrixLocation = GL_CHECK(glGetUniformLocation(programId,
                                                                    "projectionMatrix"));

    if (projectionMatrixLocation == -1) {
        LOGE("Could not retrieve uniform location: projectionMatrixLocation");
        return false;
    } else {
        GL_CHECK(glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, projectionMatrix.getAsArray()));
    }

    GLuint verticesAttributeLocation = GL_CHECK(glGetAttribLocation(programId, "vertex"));
    GLuint normalAttributeLocation = GL_CHECK(glGetAttribLocation(programId, "normal"));
    renderPlaneUniformLocation = GL_CHECK(glGetUniformLocation(programId, "renderPlane"));
    cubesLocationsUniformLocation = GL_CHECK(glGetUniformLocation(programId, "cubesLocations"));
    viewMatrixUniformLocation = GL_CHECK(glGetUniformLocation(programId, "viewMatrix"));

    if (verticesAttributeLocation == -1) {
        LOGE("Could not retrieve attribute location: verticesAttributeLocation");
        return false;
    }

    if (normalAttributeLocation == -1) {
        LOGE("Could not retrieve attribute location: normalAttributeLocation");
        return false;
    }

    if (renderPlaneUniformLocation == -1) {
        LOGE("Could not retrieve uniform location: renderPlaneUniformLocation");
        return false;
    }

    if (viewMatrixUniformLocation == -1) {
        LOGE("Could not retrieve uniform location: viewMatrixUniformLocation");
        return false;
    } else {
        Vec3f eyeVector   = {0.0f, yCameraTranslation, cameraRadius};
        Vec3f lookAtPoint = {0.0f, 0.0f, 0.0f};
        Vec3f upVector    = {0.0f, 1.0f, 0.0f};
        viewMatrix = Matrix::matrixCameraLookAt(eyeVector, lookAtPoint, upVector);
    }

    if (cubesLocationsUniformLocation == -1) {
        LOGE("Could not retrieve uniform location: cubesLocationsUniformLocation");
        return false;
    }

    Model::createSuper(numberOfSamples,
                       squareness1,
                       squareness2,
                       roundedCubeScaleFactor,
                       &roundedCubeCoordinates,
                       &roundedCubeNormalVectors,
                       &numberOfRoundedCubesVertices,
                       &numberOfRoundedCubeCoordinates,
                       &numberOfRoundedCubeNormalVectors);

    if (roundedCubeCoordinates == NULL) {
        LOGE("Could not create super ellipsoid's coordinates.");
        return false;
    }

    if (roundedCubeNormalVectors == NULL) {
        LOGE("Could not create super ellipsoid's normal vectors.");
        return false;
    }

    generateCubesLocations(planeScalingFactor, planeScalingFactor, minimumDistance);
    rewriteVec2fArrayToFloatArray();
    Model::getCubeTriangleRepresentation(normalCubeScaleFactor, &sizeOfNormalCubeVerticesArray, &normalCubeVertices);

    if (normalCubeVertices == NULL) {
        LOGE("Could not create triangular representation of a cube.");
        return false;
    }

    Model::getPlaneTriangleRepresentation(&sizeOfPlaneVerticesArray, &planeVertices);
    Matrix scaling = Matrix::createScaling(planeScalingFactor, planeScalingFactor, planeScalingFactor);
    Model::transformPlane(scaling, sizeOfPlaneVerticesArray, &planeVertices);
    if (planeVertices == NULL) {
        LOGE("Could not create triangular representation of a plane.");
        return false;
    }

    Model::getPlaneNormals(&sizeOfPlaneNormalsArray, &planeNormalVectors);
    if (planeVertices == NULL) {
        LOGE("Could not create plane's normal vectors.");
        return false;
    }

    GL_CHECK(glGenBuffers(1, &planeVerticesBufferId));
    GL_CHECK(glGenBuffers(1, &planeNormalVectorsBufferId));
    GL_CHECK(glGenBuffers(1, &normalCubeBufferId));
    GL_CHECK(glGenBuffers(1, &roundedCubeVerticesBufferId));
    GL_CHECK(glGenBuffers(1, &roundedCubeNormalVectorsBufferId));
    GL_CHECK(glGenVertexArrays(1, &planeVertexArrayObjectId));
    GL_CHECK(glGenVertexArrays(1, &normalCubeVertexArrayObjectId));
    GL_CHECK(glGenVertexArrays(1, &roundedCubeVertexArrayObjectId));
    GL_CHECK(glBindVertexArray(planeVertexArrayObjectId));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, planeVerticesBufferId));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeOfPlaneVerticesArray * sizeof(float),
                          planeVertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(verticesAttributeLocation, 4, GL_FLOAT,
                                   GL_FALSE, 0, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, planeNormalVectorsBufferId));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeOfPlaneNormalsArray * sizeof(float),
                          planeNormalVectors, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(normalAttributeLocation, 3, GL_FLOAT,
                                   GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(verticesAttributeLocation));
    GL_CHECK(glEnableVertexAttribArray(normalAttributeLocation));
    GL_CHECK(glBindVertexArray(normalCubeVertexArrayObjectId));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, normalCubeBufferId));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeOfNormalCubeVerticesArray * sizeof(float),
                          normalCubeVertices, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(verticesAttributeLocation, 3, GL_FLOAT,
                                   GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(verticesAttributeLocation));
    GL_CHECK(glBindVertexArray(roundedCubeVertexArrayObjectId));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, roundedCubeVerticesBufferId));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, numberOfRoundedCubeCoordinates * sizeof(float),
                          roundedCubeCoordinates, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(verticesAttributeLocation, 4, GL_FLOAT,
                                   GL_FALSE, 0, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, roundedCubeNormalVectorsBufferId));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, numberOfRoundedCubeNormalVectors * sizeof(float),
                          roundedCubeNormalVectors, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(normalAttributeLocation, 3, GL_FLOAT,
                                   GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(verticesAttributeLocation));
    GL_CHECK(glEnableVertexAttribArray(normalAttributeLocation));
    GL_CHECK(glGenQueries(numberOfCubes, cubeQuery));

    for (int i = 0; i < numberOfCubes; i++) {
        bool isQ = glIsQuery(cubeQuery[i]);
        LOGI("%d: %d\n", i, isQ);
    }

    if (normalCubeVertices != NULL) {
        free(normalCubeVertices);
        normalCubeVertices = NULL;
    }

    if (planeVertices != NULL) {
        free(planeVertices);
        planeVertices = NULL;
    }

    if (planeNormalVectors != NULL) {
        free(planeNormalVectors);
        planeNormalVectors = NULL;
    }

    if (roundedCubeCoordinates != NULL) {
        delete[] roundedCubeCoordinates;
        roundedCubeCoordinates = NULL;
    }

    if (roundedCubeNormalVectors != NULL) {
        delete[] roundedCubeNormalVectors;
        roundedCubeNormalVectors = NULL;
    }
    free(planeVertices);
    free(planeNormalVectors);
    return true;
}

void draw(void) {
    numberOfRoundedCubesDrawn = 0;

    GL_CHECK(glBindVertexArray(planeVertexArrayObjectId));
    GL_CHECK(glUniform1i(renderPlaneUniformLocation, 1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, sizeOfPlaneVerticesArray));
    GL_CHECK(glUniform1i(renderPlaneUniformLocation, 0));
    if (occlusionQueriesOn) {
        for (int i = 0; i < numberOfCubes; i++) {
            sendCubeLocationVectorToUniform(i);
            GL_CHECK(glBeginQuery(GL_ANY_SAMPLES_PASSED, cubeQuery[i]));
            {
                if (previouslyVisible[i]) {
                    GL_CHECK(glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE));
                    GL_CHECK(glBindVertexArray(roundedCubeVertexArrayObjectId));
                    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, numberOfRoundedCubesVertices));
                    numberOfRoundedCubesDrawn++;
                } else {
                    GL_CHECK(glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE));
                    GL_CHECK(glBindVertexArray(normalCubeVertexArrayObjectId));
                    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, sizeOfNormalCubeVerticesArray));
                }
            }
            GLint params;
            GL_CHECK(glGetQueryiv(GL_ANY_SAMPLES_PASSED, GL_CURRENT_QUERY, &params));
            LOGI("glGetQueryiv: %d\n", params);
            GL_CHECK(glEndQuery(GL_ANY_SAMPLES_PASSED));
        }

        GL_CHECK(glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE));

        if (modeChanged) {
            GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
        }

        GL_CHECK(glBindVertexArray(roundedCubeVertexArrayObjectId));
        for (int i = 0; i < numberOfCubes; i++) {
            GLuint queryResult = GL_FALSE;
            GL_CHECK(glGetQueryObjectuiv(cubeQuery[i], GL_QUERY_RESULT, &queryResult));
            bool wasVisible = previouslyVisible[i];

            previouslyVisible[i] = (queryResult == GL_TRUE);
            if ((queryResult == GL_TRUE) && !wasVisible) {
                sendCubeLocationVectorToUniform(i);
                GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, numberOfRoundedCubesVertices));
                numberOfRoundedCubesDrawn++;
            }
        }
    } else {
        GL_CHECK(glBindVertexArray(roundedCubeVertexArrayObjectId));
        for (int i = 0; i < numberOfCubes; i++) {
            sendCubeLocationVectorToUniform(i);
            GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, numberOfRoundedCubesVertices));
        }
        numberOfRoundedCubesDrawn = numberOfCubes;
    }
}

void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programId));
    Matrix yRotationMatrix = Matrix::createRotationY(-angleY);
    rotatedViewMatrix = viewMatrix * yRotationMatrix;
    GL_CHECK(glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE,
                                rotatedViewMatrix.getAsArray()));
    sortCubePositions(sortedCubesPositions);
    modeChanged = false;

    occlusionQueriesOn = !occlusionQueriesOn;
    if (occlusionQueriesOn) {
        for (int i = 0; i < numberOfCubes; i++) {
            previouslyVisible[i] = true;
        }
        modeChanged = true;
        LOGI("\nOcclusion query ON\n");
    } else {
        LOGI("\nOcclusion query OFF\n");
    }

    angleY += 0.25f;
    if (angleY >= 360) {
        angleY = 0.0f;
    }

    draw();
    GLint params;
    GL_CHECK(glGetQueryiv(GL_ANY_SAMPLES_PASSED, GL_CURRENT_QUERY, &params));
    LOGI("glGetQueryiv: %d\n", params);
}

void releaseOpenGlObjects() {
	GL_CHECK(glDeleteProgram(programId));
	GL_CHECK(glDeleteBuffers(1, &planeVerticesBufferId));
	GL_CHECK(glDeleteBuffers(1, &planeNormalVectorsBufferId));
	GL_CHECK(glDeleteBuffers(1, &normalCubeBufferId));
	GL_CHECK(glDeleteBuffers(1, &roundedCubeVerticesBufferId));
	GL_CHECK(glDeleteBuffers(1, &roundedCubeNormalVectorsBufferId));
	GL_CHECK(glDeleteVertexArrays(1, &planeVertexArrayObjectId));
	GL_CHECK(glDeleteVertexArrays(1, &normalCubeVertexArrayObjectId));
	GL_CHECK(glDeleteVertexArrays(1, &roundedCubeVertexArrayObjectId));
	GL_CHECK(glDeleteQueries(numberOfCubes, cubeQuery));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
    releaseOpenGlObjects();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
