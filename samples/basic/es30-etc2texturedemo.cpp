/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file etc2texturedemo.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for etc2texturedemo related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"
#include "ETCHeader.h"

using namespace BotsonSDK;
using std::string;

string compressedTextureDirectory = (string)PICTURE_PATH + "textures/compressed/";

struct Image {
    GLenum       internalformat;
    std::string  fileName;
    const char*  nameOfImageIneternalformat;
    GLuint       textureId; 
};

Image image0 = {GL_COMPRESSED_RG11_EAC,                       compressedTextureDirectory + "BumpMap.pkm",         "GL_COMPRESSED_RG11_EAC",                       0};
Image image1 = {GL_COMPRESSED_SIGNED_RG11_EAC,                compressedTextureDirectory + "BumpMapSigned.pkm",   "GL_COMPRESSED_SIGNED_RG11_EAC",                0};
Image image2 = {GL_COMPRESSED_RGBA8_ETC2_EAC,                 compressedTextureDirectory + "SemiAlpha.pkm",       "GL_COMPRESSED_RGBA8_ETC2_EAC",                 0};
Image image3 = {GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,          compressedTextureDirectory + "SemiAlpha.pkm",       "GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC",          0};

Image imageArrays[] = {image0, image1, image2, image3};


GLuint      bufferObjectIds[2]          = {0};           
GLuint      currentAssetIndex           = 0;     
const float displayInterval             = 5.0f;  
GLuint      fragmentShaderId            = 0;     
string      fragmentShaderPath          = (string)GLSL_PATH + "instancing.frag";
GLint       modelViewMatrixLocation     = 0;    
const int   numberOfTextures            = sizeof(imageArrays) / sizeof(imageArrays[0]);
GLint       positionLocation            = 0;     
GLuint      programId                   = 0;     
float       scalingFactor               = 0.75f; 
GLint       textureCoordinateLocation   = 0;     
GLint       textureLocation             = 0;
int         window_Height                = 800;   
int         window_Width                 = 800;   
GLuint      vertexShaderId              = 0;     
string      vertexShaderPath            = (string)GLSL_PATH + "instancing.vert";
GLuint      vertexArrayId               = 0;

float vertexData[] = {-1.0f, -1.0f, 0.0f,
                       1.0f, -1.0f, 0.0f,
                      -1.0f,  1.0f, 0.0f,
                      -1.0f,  1.0f, 0.0f,
                       1.0f, -1.0f, 0.0f,
                       1.0f,  1.0f, 0.0f};

float textureCoordinatesData[] = {0.0f, 1.0f,
                                  1.0f, 1.0f,
                                  0.0f, 0.0f,
                                  0.0f, 0.0f,
                                  1.0f, 1.0f,
                                  1.0f, 0.0f};

bool initializeTexture(int textureIndex) {
    if (textureIndex >= 0 && textureIndex < numberOfTextures) {
        std::string fileName = imageArrays[textureIndex].fileName;
        ETCHeader etcHeader;
        unsigned char *imageData = NULL;
        Texture::loadPKMData(fileName.c_str(), &etcHeader, &imageData);

        if (imageData != NULL) {
            int imageHeight = etcHeader.getHeight();
            int imageWidth  = etcHeader.getWidth();

            GLenum  internalformat = imageArrays[textureIndex].internalformat;
            GLsizei imageSize      = etcHeader.getSize(internalformat);

            GLenum target = GL_TEXTURE_2D;
            GL_CHECK(glGenTextures(1, &imageArrays[textureIndex].textureId));
            GL_CHECK(glBindTexture(target, imageArrays[textureIndex].textureId));
            GL_CHECK(glCompressedTexImage2D(target, 0, internalformat, imageWidth, imageHeight,
                                            0, imageSize, imageData));
            GL_CHECK(glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            GL_CHECK(glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
            GL_CHECK(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            GL_CHECK(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        } else {
            LOGE("Could not load image data.");
            return false;
        }
    } else {
        LOGE("Incorrect value of index of imageArrays.");
        return false;
    }

    return true;
}

bool setupTextures() {
    GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    for (int allTextures = 0; allTextures < numberOfTextures; allTextures++) {
        if (!initializeTexture(allTextures)) {
            return false;
        }
    }

    GL_CHECK(glGenVertexArrays(1, &vertexArrayId));
    GL_CHECK(glBindVertexArray(vertexArrayId));
    GL_CHECK(glGenBuffers(2, bufferObjectIds));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, bufferObjectIds[0]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
                          GL_STATIC_DRAW));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, bufferObjectIds[1]));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinatesData),
                          textureCoordinatesData, GL_STATIC_DRAW));

    return true;
}

bool draw() {

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, imageArrays[currentAssetIndex].textureId));
    GL_CHECK(glUseProgram(programId));

    if (textureLocation != -1) {
        GL_CHECK(glUniform1i(textureLocation, 0));
    }
    
    if (positionLocation != -1) {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, bufferObjectIds[0]));
        GL_CHECK(glEnableVertexAttribArray(positionLocation));
        GL_CHECK(glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0));

        if (textureCoordinateLocation != -1) {
            GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, bufferObjectIds[1]));
            GL_CHECK(glVertexAttribPointer(textureCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 0, 0));
            GL_CHECK(glEnableVertexAttribArray(textureCoordinateLocation));
        } else {
            return false;
        }
    } else {
        return false;
    }
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));

    return true;
}

bool setupGraphics() {
    if (!setupTextures()) {
        return false;
    }

   glClearColor(0.1f, 0.3f, 0.2f, 1.0f);
    Matrix scaleMatrix       = Matrix::createScaling     (scalingFactor * window_Width, scalingFactor * window_Height, 1.0f);
    Matrix ortographicMatrix = Matrix::matrixOrthographic(float(-window_Width), float(window_Width), float(-window_Height), 
                                                          float(window_Height), -1.0f,              1.0f);
    
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Shader::processShader(&vertexShaderId,   vertexShaderPath.c_str(),   GL_VERTEX_SHADER);
    Shader::processShader(&fragmentShaderId, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);

    programId = GL_CHECK(glCreateProgram());

    GL_CHECK(glAttachShader(programId, vertexShaderId));
    GL_CHECK(glAttachShader(programId, fragmentShaderId));
    GL_CHECK(glLinkProgram(programId));
    GL_CHECK(glUseProgram(programId));

    modelViewMatrixLocation   = GL_CHECK(glGetUniformLocation(programId, "modelViewMatrix"));
    positionLocation          = GL_CHECK(glGetAttribLocation (programId, "attributePosition"));
    textureCoordinateLocation = GL_CHECK(glGetAttribLocation (programId, "attributeTextureCoordinate"));
    textureLocation           = GL_CHECK(glGetUniformLocation(programId, "uniformTexture"));

    if (modelViewMatrixLocation != -1) {
        Matrix resultMatrix = ortographicMatrix * scaleMatrix;
        GL_CHECK(glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, resultMatrix.getAsArray()));
    } else {
        LOGE("Could not retrieve attribute location: modelViewMatrix.");
        return false;
    }
    return true;
}

bool renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (!draw()) {
        return false;
    }
    
    return true;
}

void Sample::test() {
    setupGraphics();
    for (int i = 0; i < ARRAY_NUM(imageArrays); i++) {
        renderFrame();
        char ss[2];
        sprintf(ss, "%d", i);
        string bmp_file = filename + ss + ".bmp";
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }

}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}