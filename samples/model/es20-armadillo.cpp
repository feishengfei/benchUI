/**
 * \file ShadowMapping.cpp
 * draw a
 */
#include "armadillo.h"
#include "Sample.h"
#include "Text.h"
#include "Shader.h"
#include "Texture.h"
#include "Matrix.h"
#include "Timer.h"

using std::string;
using namespace BotsonSDK;

#define WINDOW_W_ 512
#define WINDOW_H_ 512

struct WindowProperties
{
    int height;
    int width;
} window;

struct LightProperties
{
    Vec3f position;
    Vec3f direction;
} light;

GLuint programId;
GLuint cubePosLocation;
GLuint colorOfGeometryLocation;
GLuint isCameraPointOfViewLocation;
GLint  lightDirectionLocation;
GLint  lightPositionLocation;
GLuint lightViewMatrixLocation;
GLuint normalsAttributeLocation; 
GLuint positionAttributeLocation;

Timer timer;

Matrix cameraProjectionMatrix;
Matrix lightProjectionMatrix;
GLuint projectionMatrixLocation;
GLuint rotationMatrixLocation;
Matrix Rotation;

struct timeval t1, t2;
struct timezone tz;
const Vec3f cameraPosition   = {0.0f, 0.0f, 20.0f}; 
Vec3f       lookAtPoint      = {0.0f, 0.0f,  0.0f}; 
Matrix      viewMatrixForShadowMapPass;             
float cube_position[4];

bool initializeStructureData(void)
{
    window.height = WINDOW_H_;
    window.width  = WINDOW_W_;

    cube_position[0] =  0.0f;
    cube_position[1] =  -1.0f;
    cube_position[2] =  8.0f;
    cube_position[3] =  1.0f;

    cameraProjectionMatrix = Matrix::matrixPerspective(degreesToRadians(60.0f), float(window.width) / float(window.height), 1.0f, 50.0f);
    lightProjectionMatrix = Matrix::matrixPerspective(degreesToRadians(90.0f),  1.0f, 1.0f, 50.0f);

    return true;
}

void calculateLookAtMatrix(void)
{
    Vec3f upVector = {0.0f, 1.0f, 0.0f};
    Vec3f cameraTranslation = {0.0f, 0.0f, -20.0f};
    viewMatrixForShadowMapPass = Matrix::matrixCameraLookAt(light.position, lookAtPoint, upVector);
    viewMatrixForShadowMapPass = Matrix::createTranslation(cameraTranslation.x, cameraTranslation.y, cameraTranslation.z) * viewMatrixForShadowMapPass;
}

bool getLightAndShadowUniformLocations(void)
{
    lightDirectionLocation = GL_CHECK(glGetUniformLocation(programId, "lightDirection"));
    lightPositionLocation  = GL_CHECK(glGetUniformLocation(programId, "lightPosition"));
    return true;
}

void setUpAndUseProgramObject(GLint programId, string fragmentShaderFileName, string vertexShaderFileName)
{
    GLuint vertexShaderId = 0;
    string vertexShaderPath = ((string)GLSL_PATH) + "model_light.vert";
    Shader::processShader(&vertexShaderId,   vertexShaderPath.c_str(),   GL_VERTEX_SHADER);
    GLuint fragmentShaderId = 0;
    string fragmentShaderPath = ((string)GLSL_PATH) + "model_light.frag";
    Shader::processShader(&fragmentShaderId, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    GL_CHECK(glAttachShader(programId, vertexShaderId));
    GL_CHECK(glAttachShader(programId, fragmentShaderId));
    GL_CHECK(glLinkProgram(programId));
    GL_CHECK(glUseProgram (programId));
}

bool setupCubesAndPlaneProgram(void)
{
    programId = GL_CHECK(glCreateProgram());
    setUpAndUseProgramObject(programId, "armadillo.frag", "armadillo.vert");

    positionAttributeLocation   = GL_CHECK(glGetAttribLocation  (programId, "attributePosition"));
    normalsAttributeLocation    = GL_CHECK(glGetAttribLocation  (programId, "attributeNormals"));
    lightViewMatrixLocation     = GL_CHECK(glGetUniformLocation (programId, "lightViewMatrix"));
    colorOfGeometryLocation     = GL_CHECK(glGetUniformLocation (programId, "colorOfGeometry"));
    rotationMatrixLocation = GL_CHECK(glGetUniformLocation(programId, "rotationMatrix"));  
    GLuint scaleMatrixLocation        = GL_CHECK(glGetUniformLocation  (programId, "scaleMatrix"));
    cubePosLocation                   = GL_CHECK(glGetUniformLocation  (programId, "cubesPosition"));
    GLuint cameraPositionLocation         = GL_CHECK(glGetUniformLocation  (programId, "cameraPosition"));
    GLuint cameraProjectionMatrixLocation = GL_CHECK(glGetUniformLocation  (programId, "cameraProjectionMatrix"));
    GLuint lightProjectionMatrixLocation  = GL_CHECK(glGetUniformLocation  (programId, "lightProjectionMatrix"));
    glUniform3fv(cameraPositionLocation, 1, (float*)&cameraPosition);
    glUniformMatrix4fv(cameraProjectionMatrixLocation, 1, GL_FALSE, cameraProjectionMatrix.getAsArray());
    glUniformMatrix4fv(lightProjectionMatrixLocation, 1, GL_FALSE, lightProjectionMatrix.getAsArray());
    GLfloat scalingFactorX=10.0f;
    GLfloat scalingFactorY=10.0f;
    GLfloat scalingFactorZ=10.0f;
    Matrix scaleMatrix = Matrix::createScaling(scalingFactorX, scalingFactorY, scalingFactorZ);
    glUniformMatrix4fv(scaleMatrixLocation, 1, GL_FALSE, scaleMatrix.getAsArray());
    if (!getLightAndShadowUniformLocations())
    {
        return false;
    }

    return true;
}

bool setupPrograms()
{
    if (!setupCubesAndPlaneProgram())
    {
        return false;
    }
    return true;
}
void draw(bool hasShadowMapBeenCalculated)
{
    const float cubesColor[] = {0.486f, 0.432f, 0.322f, 0.6f};
    const float planeColor[] = {0.341f, 0.388f, 0.45f, 0.6f};

    GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));

    GL_CHECK(glUseProgram(programId));
    if (!hasShadowMapBeenCalculated)
    {
        GL_CHECK(glUniform3fv(lightDirectionLocation, 1, (float*)&light.direction));
        GL_CHECK(glUniform3fv(lightPositionLocation,  1, (float*)&light.position));
    }

    GL_CHECK(glUniformMatrix4fv(lightViewMatrixLocation, 1, GL_FALSE, viewMatrixForShadowMapPass.getAsArray()));
    glUniformMatrix4fv(rotationMatrixLocation, 1, GL_FALSE, Rotation.getAsArray());

    GL_CHECK(glUniform4f(colorOfGeometryLocation, cubesColor[0], cubesColor[1], cubesColor[2], cubesColor[3]));
    glUniform4fv(cubePosLocation, 1, cube_position);

    GL_CHECK(glEnableVertexAttribArray(positionAttributeLocation));
    GL_CHECK(glVertexAttribPointer    (positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, armadilloVerts));
    GL_CHECK(glEnableVertexAttribArray(normalsAttributeLocation));
    GL_CHECK(glVertexAttribPointer    (normalsAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, armadilloNormals));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, armadilloNumVerts));
}

void renderFrame(void)
{
    light.position.x =  3.0;
    light.position.y =  6.0f;
    light.position.z =  0.0;
    light.direction.x = lookAtPoint.x - light.position.x;
    light.direction.y = lookAtPoint.y - light.position.y;
    light.direction.z = lookAtPoint.z - light.position.z;
    light.direction.normalize();
static float angleX = 0, angleY = 0, angleZ = 0;
    float deltatime;
    Matrix RotationX = Matrix::createRotationX(angleX);
    Matrix RotationY = Matrix::createRotationY(angleY);
    Matrix RotationZ = Matrix::createRotationZ(angleZ);
    Rotation = RotationX * RotationY;
    Rotation = Rotation * RotationZ;
    gettimeofday(&t2, &tz);
    deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
    t1 = t2;
    angleY += 20*deltatime;

    if(angleY >= 360) angleY -= 360;
    if(angleY < 0) angleY += 360;

    glClearColor(0.0, 0.0, 0.0, 0.0);

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    
    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    GL_CHECK(glViewport(0, 0, window.width, window.height));
    calculateLookAtMatrix();
    glEnable(GL_POLYGON_OFFSET_FILL);
    draw(false);
    draw(true);
}

void Sample::test() {
    gettimeofday ( &t1 , &tz );

    initializeStructureData();

    setupPrograms();
    glPolygonOffset(1.0, 0.0);
    timer.reset();
    int LoopCNT = 0;
    while (LoopCNT < 50)
    {
        renderFrame();
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, WINDOW_W_, WINDOW_H_);

    sample.test();

    return 0;
}