/**
 * \file ShadowMapping.cpp
 * draw a
 */
#include "f16.h"
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

#define NUM 4

/* Texture variables. */
GLuint textureID[NUM];
/* Shader variables. */
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocTexCoord = -1;
GLint iLocSampler = -1;
GLuint iLocTrans;

GLint iLocMVP;
struct timeval t1, t2;
struct timezone tz;
static float angleX = 0, angleY = 0, angleZ = 0, angle=0;

#define LOGIF printf

bool setupGraphics(int w, int h)
{
    string texturePath = ((string)PICTURE_PATH) + "F16s.bmp";
    string vertexShaderPath = ((string)GLSL_PATH) + "model_texture.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "model_texture.frag";
    /* Initialize OpenGL ES. */
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glGenTextures(NUM, textureID));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID[0]));
    string mainTexturePath1 = texturePath;
    tBMP image_bmp;
    //image_bmp.file_name = (char *)texturePath.c_str();
    //read_bmp(&image_bmp);
    //rgba_to_stream(&image_bmp);
    GLsizei        imageHeight = 0;
    GLsizei        imageWidth  = 0;
    unsigned char* textureData1 = NULL;
    Texture::loadBmpImageData(texturePath, &imageWidth, &imageHeight, &textureData1);
    //GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_bmp.width, image_bmp.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_bmp.image_data));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData1));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    free(image_bmp.image_data);
    /* Process shaders. */
    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGIF("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGIF("fragmentShaderID = %d", fragmentShaderID);
    programID = GL_CHECK(glCreateProgram());
    if (!programID) 
    {
        LOGIF("Could not create program.");
        return false;
    }
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    /* Vertex positions. */
    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    if(iLocPosition == -1)
    {
        LOGIF("Attribute not found: \"a_v4Position\"");
        exit(1);
    }
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    iLocTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_v2TexCoord"));
    if(iLocTexCoord == -1)
    {
        LOGIF("Warning: Attribute not found: \"a_v2TexCoord\"");
    }
    else
    {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }
    iLocSampler = GL_CHECK(glGetUniformLocation(programID, "u_s2dTexture"));
    if(iLocSampler == -1)
    {
        LOGIF("Warning: Uniform not found: \"u_s2dTexture\"");
    }
    else
    {
        GL_CHECK(glUniform1i(iLocSampler, 0));
    }
    iLocMVP = GL_CHECK(glGetUniformLocation(programID, "mvp"));
    GL_CHECK(glClearColor(0.1f, 0.01f, 0.01f, 1.0));
    return true;
}

void renderFrame(void)
{
float deltatime;

    GL_CHECK(glActiveTexture(GL_TEXTURE1));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, f16Verts));

    if(iLocTexCoord != -1)
    {
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, f16TexCoords));
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }
    Matrix modelView = Matrix::createRotationX(angleX);
    Matrix rotation = Matrix::createRotationY(angleY);
    modelView = rotation * modelView;
    rotation = Matrix::createRotationZ(angleZ);
    modelView = rotation * modelView;
    modelView[14] -= 2.5;

    Matrix Scaling = Matrix::createScaling(1.8, 1.8, 1.8);
    Matrix Translation = Matrix::createTranslation(0.0, 0.0, 0.0);
    
    Matrix perspective = Matrix::matrixPerspective(45.0f, WINDOW_W_/WINDOW_H_, 0.01f, 100.0f);
    Matrix modelViewPerspective = perspective * modelView * Scaling * Translation;

    GL_CHECK(glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, modelViewPerspective.getAsArray()));
    gettimeofday(&t2, &tz);
    deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
    t1 = t2;

    angleY += 40*deltatime;

    if(angleX >= 360) angleX -= 360;
    if(angleX < 0) angleX += 360;
    if(angleZ >= 360) angleZ -= 360;
    if(angleZ < 0) angleZ += 360;

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID[0]));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    glDrawArrays(GL_TRIANGLES, 0, f16NumVerts);
}
void Sample::test() {
    gettimeofday ( &t1 , &tz );
    setupGraphics(WINDOW_W_, WINDOW_H_);
    int LoopCNT = 0;
    while (LoopCNT < 50)
    {
        renderFrame();
        Sample::SwapBuffers();
    }
    GL_CHECK(glDeleteTextures(2, textureID));
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, WINDOW_W_, WINDOW_H_);

    sample.test();

    return 0;
}