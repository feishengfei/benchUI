/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * * =================================================================
*/

/**
 * @file rotozoom.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for rotozoom related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"


using std::string;
using namespace BotsonSDK;

string textureFilename = "RotoZoom.raw";

static const GLubyte quadIndices[] = {
    0, 1, 2, 3,
};

static const float quadVertices[] = {
    -1.0f, -1.0f,  0.0f,
     1.0f, -1.0f,  0.0f,
    -1.0f,  1.0f,  0.0f,
     1.0f,  1.0f,  0.0f,
};

static const float quadTextureCoordinates[] = {
    0.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
};

GLuint textureID = 0;
GLuint programID = 0;
GLint iLocTextureMatrix = -1;
GLint iLocPosition = -1;
GLint iLocTextureMix = -1;
GLint iLocTexture = -1;
GLint iLocTexCoord = -1;

Matrix translation;
Matrix scale;
Matrix negativeTranslation;

int window_Width = -1;
int window_Height = -1;

static float angleZTexture = 0.0f;
static float angleZOffset = 0.0f;
static float angleZoom = 0.0f;

bool setupGraphics(int width, int height) {
    int textureWidth = 256;
    int textureHeight = 256;
    
    window_Width = width;
    window_Height = height;

    string texturePath = ((string)PICTURE_PATH) + textureFilename;   
    string vertexShaderPath = ((string)GLSL_PATH) + "rotozoom.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "rotozoom.frag";

    translation = Matrix::createTranslation(0.5f, 0.5f, 0.0f);
    scale = Matrix::createScaling(width / (float)textureWidth, height / (float)textureHeight, 1.0f); /* 2.0 makes it smaller, 0.5 makes it bigger. */
    negativeTranslation = Matrix::createTranslation(-0.5f, -0.5f, 0.0f);

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glCullFace(GL_BACK));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    unsigned char *textureData = NULL;
    Texture::loadData(texturePath.c_str(), &textureData);
        
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 256, 256, 0, GL_RGBA,
                          GL_UNSIGNED_BYTE, textureData));
    GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                             GL_LINEAR_MIPMAP_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GLuint vertexShaderID = 0;
    GLuint fragmentShaderID = 0;
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

    iLocTexture = GL_CHECK(glGetUniformLocation(programID, "u_s2dTexture"));
    if(iLocTexture == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniform1i(iLocTexture, 0));
    }

    iLocTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_v2TexCoord"));
    if(iLocTexCoord == -1) {
        LOGW("Warning: Attribute not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }

    iLocTextureMatrix = GL_CHECK(glGetUniformLocation(programID, "u_m4Texture"));
    if(iLocTextureMatrix == -1) {
        LOGW("Warning: Uniform not found at %s:%i\n", __FILE__, __LINE__);
    } else {
        GL_CHECK(glUniformMatrix4fv(iLocTextureMatrix, 1, GL_FALSE, scale.getAsArray()));
    }
    
    return true;
}

void renderFrame(void) {
    static Vec4f radius = {0.0f, 1.0f, 0.0f, 1.0f};

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, quadVertices));

    if(iLocTexCoord != -1) {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, quadTextureCoordinates));
    }

    GL_CHECK(glViewport(0, 0, window_Width, window_Height));
    GL_CHECK(glClearColor(1.0f, 1.0f, 0.0f, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    Matrix rotateTextureZ = Matrix::createRotationZ(angleZTexture);
    Matrix rotateOffsetZ = Matrix::createRotationZ(angleZOffset);
    Vec4f offset = Matrix::vertexTransform(&radius, &rotateOffsetZ);

    Matrix translateTexture = Matrix::createTranslation(offset.x, offset.y, offset.z);
    Matrix zoom = Matrix::createScaling(sinf(degreesToRadians(angleZoom)) * 0.75f + 1.25f,
            sinf(degreesToRadians(angleZoom)) * 0.75f + 1.25f, 1.0f);
    Matrix textureMovement = Matrix::identityMatrix * translation;
    textureMovement = textureMovement * rotateTextureZ;
    textureMovement = textureMovement * translateTexture;
    textureMovement = textureMovement * zoom;
    textureMovement = textureMovement * scale;
    textureMovement = textureMovement * negativeTranslation;

    GL_CHECK(glUniformMatrix4fv(iLocTextureMatrix, 1, GL_FALSE,
                                textureMovement.getAsArray()));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, sizeof(quadIndices) / sizeof(GLubyte),
                            GL_UNSIGNED_BYTE, quadIndices));

    angleZTexture += 10;
    angleZOffset += 10;
    angleZoom += 10;
    if(angleZoom >= 360) angleZoom -= 360;
    if(angleZoom < 0) angleZoom += 360;
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);

    while(angleZOffset <= 360 && angleZTexture <= 360) {
        renderFrame();
        char ss[3];
        sprintf(ss, "_%d", (int)angleZOffset);
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
