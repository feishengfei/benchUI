/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file interlogics.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for interlogics related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"

using           std::string;
using namespace BotsonSDK;

static const float lineVertices[] = {
    -0.5f, 1.0f, 0.0f, 0.5f,
     0.5f, 1.0f, 0.0f, 0.5f,
};

static const float quadVertices[] = {
    -0.5f,  1.0f, 0.0f, 0.5f,
     0.5f,  1.0f, 0.0f, 0.5f,
    -0.5f, -1.0f, 0.0f, 0.5f,
     0.5f, -1.0f, 0.0f, 0.5f,
};

static const float lineTextureCoordinates[] = {
    0.0f, 1.0f,
    1.0f, 1.0f
};

static const float quadTextureCoordinates[] = {
    0.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
};

string vertexRule30ShaderFilename   = "IntegerLogic_Rule30_shader.vert";
string vertexMergeShaderFilename    = "IntegerLogic_Merge_shader.vert";
string fragmentRule30ShaderFilename = "IntegerLogic_Rule30_shader.frag";
string fragmentMergeShaderFilename  = "IntegerLogic_Merge_shader.frag";
GLuint rule30ProgramID = 0;
GLuint mergeProgramID  = 0;
const GLuint pingTextureUnit = 0;
const GLuint pongTextureUnit = 1;
GLvoid* pingTextureData = NULL;
GLuint  pingTextureID   = -1;
GLuint  pongTextureID   = -1;
GLuint framebufferID = -1;
GLuint linePositionBOID = -1;
GLuint lineUVBOID = -1;
GLuint quadPositionBOID = 0;
GLuint quadUVBOID = 0;
GLuint lineVAOID = -1;
GLuint quadVAOID = 0;

Matrix modelViewProjectionMatrix;

const float resetTimeInterval = 5.0f;

void generateRule30Input(unsigned int xoffset, unsigned int width, unsigned int height,
                         unsigned int nComponents, GLvoid** textureData) {
    if(textureData == NULL) {
        LOGE("Null data passed");
        return;
    }

    for(unsigned int channelIndex = 0; channelIndex < nComponents; ++channelIndex) {
        (*(unsigned char**)textureData)[(height - 1) * width * nComponents +
                                        xoffset * nComponents + channelIndex] = 255;
    }
}

void generateRule30Input(unsigned int width, unsigned int height,
                         unsigned int nComponents, GLvoid** textureData) {
    if(textureData == NULL) {
        LOGE("Null data passed");
        return;
    }

    for (unsigned int texelIndex = 0; texelIndex < width; ++texelIndex) {
        bool setWhite = (rand() % 2 == 0) ? true : false;
        if (setWhite) {
            for (unsigned int channelIndex = 0; channelIndex < nComponents;
                    ++channelIndex) {
                (*(unsigned char**)textureData)[(height - 1) * width * nComponents +
                                     texelIndex * nComponents + channelIndex] = 255;
            }
        }
    }
}

bool setupGraphics() {
    string vertexRule30ShaderPath   = (string)GLSL_PATH + vertexRule30ShaderFilename;
    string vertexMergeShaderPath    = (string)GLSL_PATH + vertexMergeShaderFilename;
    string fragmentRule30ShaderPath = (string)GLSL_PATH + fragmentRule30ShaderFilename;
    string fragmentMergeShaderPath  = (string)GLSL_PATH + fragmentMergeShaderFilename;

    Matrix scale = Matrix::createScaling ((float) WINDOW_W, (float) WINDOW_H, 1.0f);
    Matrix orthographic = Matrix::matrixOrthographic(-(float) WINDOW_W,
            (float) WINDOW_W, -(float) WINDOW_H*2, (float) WINDOW_H*2, -1.0f, 1.0f);
    modelViewProjectionMatrix = orthographic * scale;
    Texture::createTexture(WINDOW_W,WINDOW_H, 0,&pingTextureData);
    generateRule30Input(WINDOW_W / 2, WINDOW_W, WINDOW_H, 1, &pingTextureData);
    GLuint textureIDs[] = {0, 0};
    GL_CHECK(glGenTextures(2, textureIDs));
    pingTextureID = textureIDs[0];
    pongTextureID = textureIDs[1];

    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture  (GL_TEXTURE_2D, pingTextureID));
    GL_CHECK(glTexImage2D   (GL_TEXTURE_2D, 0, GL_R8UI, WINDOW_W, WINDOW_H, 0,
                             GL_RED_INTEGER, GL_UNSIGNED_BYTE, pingTextureData));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    GL_CHECK(glActiveTexture(GL_TEXTURE1));
    GL_CHECK(glBindTexture  (GL_TEXTURE_2D, pongTextureID));
    GL_CHECK(glTexImage2D   (GL_TEXTURE_2D, 0, GL_R8UI, WINDOW_W, WINDOW_H, 0,
                             GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

    GLuint fragmentMergeShaderID  = 0;
    GLuint fragmentRule30ShaderID = 0;
    GLuint vertexRule30ShaderID   = 0;
    GLuint vertexMergeShaderID    = 0;

    Shader::processShader(&vertexRule30ShaderID, vertexRule30ShaderPath.c_str(),
                          GL_VERTEX_SHADER);
    Shader::processShader(&vertexMergeShaderID, vertexMergeShaderPath.c_str(),
                          GL_VERTEX_SHADER);
    Shader::processShader(&fragmentRule30ShaderID, fragmentRule30ShaderPath.c_str(),
                          GL_FRAGMENT_SHADER);
    Shader::processShader(&fragmentMergeShaderID, fragmentMergeShaderPath.c_str(),
                          GL_FRAGMENT_SHADER);

    rule30ProgramID = GL_CHECK(glCreateProgram());
    mergeProgramID  = GL_CHECK(glCreateProgram());

    GL_CHECK(glAttachShader(rule30ProgramID, vertexRule30ShaderID));
    GL_CHECK(glAttachShader(rule30ProgramID, fragmentRule30ShaderID));
    GL_CHECK(glAttachShader(mergeProgramID,  vertexMergeShaderID));
    GL_CHECK(glAttachShader(mergeProgramID,  fragmentMergeShaderID));

    GL_CHECK(glLinkProgram(rule30ProgramID));
    GL_CHECK(glLinkProgram(mergeProgramID) );

    GLuint boIDs[] = {0, 0, 0, 0};

    GL_CHECK(glGenBuffers(4, boIDs));

    linePositionBOID = boIDs[0];
    lineUVBOID       = boIDs[1];
    quadPositionBOID = boIDs[2];
    quadUVBOID       = boIDs[3];

    GL_CHECK(glGenFramebuffers(1, &framebufferID));
    GL_CHECK(glGenVertexArrays(1, &lineVAOID));
    GL_CHECK(glBindVertexArray(lineVAOID));

    GLint positionLocation = GL_CHECK(glGetAttribLocation(rule30ProgramID, "position"));
    GLint texCoordLocation = GL_CHECK(glGetAttribLocation(rule30ProgramID, "vertexTexCoord"));

    if (positionLocation == -1) {
        LOGE("Could not find position attribute in program [%d]", rule30ProgramID);
    } else {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, linePositionBOID));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices),
                              lineVertices, GL_STATIC_DRAW));
        GL_CHECK(glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(positionLocation));
    }

    if (texCoordLocation == -1) {
        LOGE("Could not find model_tex_coord attribute in program [%d]", rule30ProgramID);
    } else {
        GL_CHECK(glBindBuffer (GL_ARRAY_BUFFER, lineUVBOID));
        GL_CHECK(glBufferData (GL_ARRAY_BUFFER, sizeof(lineTextureCoordinates),
                               lineTextureCoordinates, GL_STATIC_DRAW));
        GL_CHECK(glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(texCoordLocation));
    }

    GL_CHECK(glGenVertexArrays(1, &quadVAOID));
    GL_CHECK(glBindVertexArray(quadVAOID));

    positionLocation  = GL_CHECK(glGetAttribLocation(mergeProgramID, "position"));
    texCoordLocation  = GL_CHECK(glGetAttribLocation(mergeProgramID, "vertexTexCoord"));

    if (positionLocation == -1) {
        LOGE("Could not find position attribute in program [%d]", mergeProgramID);
    } else {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER,quadPositionBOID));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),
                              quadVertices, GL_STATIC_DRAW));
        GL_CHECK(glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(positionLocation));
    }

    if (texCoordLocation == -1) {
        LOGE("Could not find model_tex_coord attribute in program [%d]", mergeProgramID);
    } else {
        GL_CHECK(glBindBuffer (GL_ARRAY_BUFFER, quadUVBOID));
        GL_CHECK(glBufferData (GL_ARRAY_BUFFER, sizeof(quadTextureCoordinates),
                               quadTextureCoordinates, GL_STATIC_DRAW));
        GL_CHECK(glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(texCoordLocation));
    }
    GL_CHECK(glLineWidth(1.5));

    return true;
}

void performOffscreenRendering() {
    static bool isRenderedForTheFirstTime = true;
    const GLuint offscreenFBODrawBuffers[] = {GL_COLOR_ATTACHMENT0};
    GLint inputTextureLocation = GL_CHECK(glGetUniformLocation(rule30ProgramID, "inputTexture"));
    GLint verticalOffsetLocation = GL_CHECK(glGetUniformLocation(rule30ProgramID, "verticalOffset"));
    GLint mvpMatrixLocation = GL_CHECK(glGetUniformLocation(rule30ProgramID, "mvpMatrix"));
    GLint inputVerticalOffsetLocation = GL_CHECK(glGetUniformLocation(rule30ProgramID, "inputVerticalOffset"));
    GLint inputNeighbourLocation = GL_CHECK(glGetUniformLocation(rule30ProgramID, "inputNeighbour"));

    float inputVerticalOffset = 0.0f;

    GL_CHECK(glUseProgram(rule30ProgramID));
    GL_CHECK(glBindVertexArray(lineVAOID));
    GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebufferID));

    if(isRenderedForTheFirstTime) {
        GL_CHECK(glDrawBuffers    (1, offscreenFBODrawBuffers));
        GL_CHECK(glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE,
                                    modelViewProjectionMatrix.getAsArray()));
        GL_CHECK(glUniform1f(inputNeighbourLocation, 1.0f / WINDOW_W)                                    );

        isRenderedForTheFirstTime = false;
    }

    for (unsigned int y = 1; y <= WINDOW_H; ++y) {
        bool isEvenLineBeingRendered = (y % 2 == 0) ? (true) : (false);
        float verticalOffset = (float) y / (float) WINDOW_H;
        GL_CHECK(glUniform1f(verticalOffsetLocation, verticalOffset));
        GL_CHECK(glUniform1f(inputVerticalOffsetLocation, inputVerticalOffset));
        if (isEvenLineBeingRendered) {
            GL_CHECK(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                            GL_TEXTURE_2D, pingTextureID, 0));
            GL_CHECK(glUniform1i(inputTextureLocation, pongTextureUnit)                                        );
        } else {
            GL_CHECK(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                            GL_TEXTURE_2D, pongTextureID, 0));
            GL_CHECK(glUniform1i(inputTextureLocation, pingTextureUnit)                                        );
        }
        GL_CHECK(glDrawArrays(GL_LINES, 0, 2));
        inputVerticalOffset = verticalOffset;
    }
    GL_CHECK(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
}

void renderToBackBuffer() {
    static bool isRenderedForTheFirstTime = true;
    GLint mvpMatrixLocation = GL_CHECK(glGetUniformLocation(mergeProgramID, "mvpMatrix")     );
    GLint pingTextureLocation = GL_CHECK(glGetUniformLocation(mergeProgramID, "pingTexture")   );
    GLint pongTextureLocation = GL_CHECK(glGetUniformLocation(mergeProgramID, "pongTexture")   );

    GL_CHECK(glUseProgram(mergeProgramID));
    GL_CHECK(glBindVertexArray(quadVAOID));
    if(isRenderedForTheFirstTime) {
        GL_CHECK(glUniformMatrix4fv(mvpMatrixLocation,1, GL_FALSE,
                                    modelViewProjectionMatrix.getAsArray()));
        GL_CHECK(glUniform1i(pingTextureLocation, 0)                                                  );
        GL_CHECK(glUniform1i(pongTextureLocation, 1)                                                  );

        isRenderedForTheFirstTime = false;
    }
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
}

void renderFrame() {
    performOffscreenRendering();
    renderToBackBuffer();
}

void resetTextures() {
    Texture::deleteTextureData(&pingTextureData);
    Texture::createTexture(WINDOW_W, WINDOW_H, 0, &pingTextureData);
    generateRule30Input   (WINDOW_W, WINDOW_H, 1, &pingTextureData);
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WINDOW_W, WINDOW_H, GL_RED_INTEGER, GL_UNSIGNED_BYTE, pingTextureData));
}

void Sample::test() {
    setupGraphics();
    renderFrame();
    string bmp_file = filename + "1.bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();

    resetTextures();
    renderFrame();
    string bmp_file1 = filename + "2.bmp";
    LOGI("bmp_file1=%s", bmp_file.c_str());
    save2bmp(bmp_file1.c_str());
    Sample::SwapBuffers();

    Texture::deleteTextureData(&pingTextureData);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
