/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file sampler-shadowmap.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for sampler-shadowmap related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Matrix.h"

using std::string;
using namespace BotsonSDK;

#define POSITION_LOC    0
#define COLOR_LOC       1

GLuint sceneProgramObject;
GLuint shadowMapProgramObject;
GLint  sceneMvpLoc;
GLint  shadowMapMvpLoc;
GLint  sceneMvpLightLoc;
GLint  shadowMapMvpLightLoc;
GLint shadowMapSamplerLoc;
GLuint shadowMapTextureId;
GLuint shadowMapBufferId;
GLuint groundPositionVBO;
GLuint groundIndicesIBO;
GLuint cubePositionVBO;
GLuint cubeIndicesIBO;
int groundNumIndices;
int cubeNumIndices;
int groundGridSize;
Matrix  groundMvpMatrix;
Matrix  groundMvpLightMatrix;
Matrix  cubeMvpMatrix;
Matrix  cubeMvpLightMatrix;
float eyePosition[3];
float lightPosition[3];
GLint texUnit = 0;
GLuint sampler = 0;
GLuint shadowMapTextureWidth;
GLuint shadowMapTextureHeight;
struct {
	GLenum mode;
	GLenum func;
} factors[] = {
	{GL_COMPARE_REF_TO_TEXTURE, GL_LEQUAL},
	{GL_COMPARE_REF_TO_TEXTURE, GL_GEQUAL},
	{GL_COMPARE_REF_TO_TEXTURE, GL_LESS},
	{GL_COMPARE_REF_TO_TEXTURE, GL_GREATER},
	{GL_COMPARE_REF_TO_TEXTURE, GL_EQUAL},
	{GL_COMPARE_REF_TO_TEXTURE, GL_NOTEQUAL},
	{GL_COMPARE_REF_TO_TEXTURE, GL_ALWAYS},
	{GL_COMPARE_REF_TO_TEXTURE, GL_NEVER},
	{GL_NONE, GL_NONE}
};

int width=500, height=500;

int InitMVP ( ) {
   Matrix perspective;
   Matrix ortho;
   Matrix modelview;
   Matrix model;
   Matrix view;
   float    aspect;
   aspect = (GLfloat) width / (GLfloat) height;
   perspective = Matrix::identityMatrix;
    Matrix Perspective = Matrix::matrixPerspective( 45.0f, aspect, 0.1f, 100.0f);
    perspective = Perspective * perspective;


    ortho = Matrix::identityMatrix;
    Matrix Ortho = Matrix::matrixOrthographic(-10, 10, -10, 10, -30, 30);
    ortho = Ortho * ortho;

    model = Matrix::identityMatrix;
   Matrix translate = Matrix::createTranslation(-2.0f, -2.0f, 0.0f);
    model = model * translate;
   Matrix scale = Matrix::createScaling(10.0f, 10.0f, 10.0f);
   model = model * scale;

    Matrix rotate = Matrix::createRotationX(45.0f);
    model = model * rotate;
    Matrix matrixlookat = Matrix::matrixCameraLookAt(eyePosition[0], eyePosition[1], eyePosition[2],
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    view = model * matrixlookat;
    Matrix multiply = Matrix::multiply(&model, &view );
    modelview = model * multiply;

    Matrix multiply1 = Matrix::multiply(&modelview, &perspective );
    groundMvpMatrix = model * multiply1;

    Matrix matrixlookat1 = Matrix::matrixCameraLookAt(lightPosition[0], lightPosition[1],
            lightPosition[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    view = model * matrixlookat1;

    Matrix multiply2 = Matrix::multiply(&model, &view );
    modelview = model * multiply2;

    Matrix multiply3 = Matrix::multiply(&modelview, &ortho );
    groundMvpLightMatrix = model * multiply3;

    model = Matrix::identityMatrix;

    Matrix translate1 = Matrix::createTranslation( 5.0f, -0.4f, -3.0f );
    model = model * translate1;

    Matrix scale1 = Matrix::createScaling(1.0f, 2.5f, 1.0f);
    model = model * scale1;

    Matrix rotate1 = Matrix::createRotationX(45.0f);
    model = model * rotate1;

    Matrix matrixlookat2 = Matrix::matrixCameraLookAt(eyePosition[0], eyePosition[1], eyePosition[2],
                                                     0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    view = model * matrixlookat2;

    Matrix multiply4 = Matrix::multiply(&model, &view );
    modelview = model * multiply4;

    Matrix multiply5 = Matrix::multiply(&modelview, &perspective);
    cubeMvpMatrix = model * multiply5;

    Matrix matrixlookat3 = Matrix::matrixCameraLookAt(lightPosition[0], lightPosition[1], lightPosition[2],
                                                     0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    view = model * matrixlookat3;

    Matrix multiply6 = Matrix::multiply(&model, &view );
    modelview = model * multiply6;

    Matrix multiply7 = Matrix::multiply(&modelview, &ortho  );
    cubeMvpLightMatrix = model * multiply7;

   return TRUE;
}

int InitShadowMap (int i) {
    GLenum none               = GL_NONE;
    GLint  defaultFramebuffer = 0;
    shadowMapTextureWidth = shadowMapTextureHeight = 1024;
    glGenTextures(1, &shadowMapTextureId);
    glBindTexture(GL_TEXTURE_2D, shadowMapTextureId);

    glGenSamplers(1, &sampler);
    glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_MODE, factors[i].mode);
    if (factors[i].mode != GL_NONE)
        glSamplerParameteri(sampler, GL_TEXTURE_COMPARE_FUNC, factors[i].func);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindSampler(texUnit, sampler);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, shadowMapTextureWidth,
                 shadowMapTextureHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFramebuffer);
    glGenFramebuffers(1, &shadowMapBufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapBufferId);
    glDrawBuffers(1, &none);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                           shadowMapTextureId, 0);
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMapTextureId);
    if (GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
        return GL_FALSE;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);

    GLint param;
    glGetSamplerParameteriv(sampler, GL_TEXTURE_COMPARE_MODE, &param);
    LOGI("glGetSamplerParameteriv(GL_TEXTURE_COMPARE_FUNC)=%s", get_enum_name(param));
    glGetSamplerParameteriv(sampler, GL_TEXTURE_COMPARE_FUNC, &param);
    LOGI("glGetSamplerParameteriv(GL_TEXTURE_COMPARE_FUNC)=%s", get_enum_name(param));
    return GL_TRUE;
}

bool setupGraphics(int num) {
    GLfloat *positions;
    GLuint  *indices;

    string vertexShaderFilename   = "Scene.vert";
    string fragmentShaderFilename = "Scene.frag";
    string vertexShaderPath       = (string)GLSL_PATH + vertexShaderFilename;
    string fragmentShaderPath     = (string)GLSL_PATH + fragmentShaderFilename;
    sceneProgramObject     = Shader::CreateProgram(vertexShaderPath.c_str(),
                                                   fragmentShaderPath.c_str());
    vertexShaderFilename   = "ShadowMap.vert";
    fragmentShaderFilename = "ShadowMap.frag";
    vertexShaderPath       = (string)GLSL_PATH + vertexShaderFilename;
    fragmentShaderPath     = (string)GLSL_PATH + fragmentShaderFilename;
    shadowMapProgramObject = Shader::CreateProgram(vertexShaderPath.c_str(),
                                                   fragmentShaderPath.c_str());

    sceneMvpLoc          = glGetUniformLocation(sceneProgramObject, "u_mvpMatrix");
    shadowMapMvpLoc      = glGetUniformLocation(shadowMapProgramObject, "u_mvpMatrix");
    sceneMvpLightLoc     = glGetUniformLocation(sceneProgramObject, "u_mvpLightMatrix");
    shadowMapMvpLightLoc = glGetUniformLocation(shadowMapProgramObject, "u_mvpLightMatrix");
    shadowMapSamplerLoc  = glGetUniformLocation(sceneProgramObject, "s_shadowMap");
    groundGridSize       = 3;
    groundNumIndices     = genSquareGrid(groundGridSize, &positions, &indices);
    glGenBuffers(1, &groundIndicesIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndicesIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, groundNumIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    free(indices);

    glGenBuffers(1, &groundPositionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, groundPositionVBO);
    glBufferData(GL_ARRAY_BUFFER, groundGridSize * groundGridSize * sizeof(GLfloat) * 3, positions, GL_STATIC_DRAW);
    free(positions);

    cubeNumIndices = genCube(1.0f, &positions, NULL, NULL, &indices);
    glGenBuffers(1, &cubeIndicesIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndicesIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * cubeNumIndices,
                 indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    free(indices);
    glGenBuffers(1, &cubePositionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubePositionVBO);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat) * 3, positions,
                 GL_STATIC_DRAW);
    free(positions);

    eyePosition[0]   = -5.0f;
    eyePosition[1]   = 3.0f;
    eyePosition[2]   = 5.0f;
    lightPosition[0] = 10.0f;
    lightPosition[1] = 5.0f;
    lightPosition[2] = 2.0f;

    if (!InitShadowMap(num)) {
        return GL_FALSE;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void DrawScene ( GLint mvpLoc, GLint mvpLightLoc ) {

   glBindBuffer ( GL_ARRAY_BUFFER, groundPositionVBO );
   glVertexAttribPointer ( POSITION_LOC, 3, GL_FLOAT, 
                           GL_FALSE, 3 * sizeof(GLfloat), (const void*)NULL );
   glEnableVertexAttribArray ( POSITION_LOC );   

   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, groundIndicesIBO );
   glUniformMatrix4fv ( mvpLoc, 1, GL_FALSE, groundMvpMatrix.getAsArray() );
   glUniformMatrix4fv ( mvpLightLoc, 1, GL_FALSE, groundMvpLightMatrix.getAsArray() );
   glVertexAttrib4f ( COLOR_LOC, 0.9f, 0.9f, 0.9f, 1.0f );
   glDrawElements ( GL_TRIANGLES, groundNumIndices, GL_UNSIGNED_INT,
                    (const void*)NULL );
   glBindBuffer( GL_ARRAY_BUFFER, cubePositionVBO );
   glVertexAttribPointer ( POSITION_LOC, 3, GL_FLOAT, 
                           GL_FALSE, 3 * sizeof(GLfloat), (const void*)NULL );
   glEnableVertexAttribArray ( POSITION_LOC );
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, cubeIndicesIBO );
   glUniformMatrix4fv ( mvpLoc, 1, GL_FALSE,cubeMvpMatrix.getAsArray());
   glUniformMatrix4fv(mvpLightLoc, 1, GL_FALSE, cubeMvpLightMatrix.getAsArray());
   glVertexAttrib4f ( COLOR_LOC, 1.0f, 0.0f, 0.0f, 1.0f );
   glDrawElements ( GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_INT, (const void*)NULL );
}

void renderFrame() {
   GLint defaultFramebuffer = 0;

   InitMVP ();
   glGetIntegerv ( GL_FRAMEBUFFER_BINDING, &defaultFramebuffer );
   glBindFramebuffer ( GL_FRAMEBUFFER, shadowMapBufferId );
   glViewport ( 0, 0, shadowMapTextureWidth, shadowMapTextureHeight );
   glClear( GL_DEPTH_BUFFER_BIT );
   glColorMask ( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
   glEnable ( GL_POLYGON_OFFSET_FILL );
   glPolygonOffset( 5.0f, 100.0f );

   glUseProgram ( shadowMapProgramObject );
   DrawScene ( shadowMapMvpLoc, shadowMapMvpLightLoc );

   glDisable( GL_POLYGON_OFFSET_FILL );

   glBindFramebuffer ( GL_FRAMEBUFFER, defaultFramebuffer );
   glColorMask ( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );

   glViewport ( 0, 0, width, height );
   
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glClearColor ( 0.3f, 0.7f, 0.6f, 0.3f );

   glUseProgram ( sceneProgramObject );
    glActiveTexture(GL_TEXTURE0+texUnit);
   glBindTexture ( GL_TEXTURE_2D, shadowMapTextureId );
   glUniform1i ( shadowMapSamplerLoc, texUnit );

   DrawScene ( sceneMvpLoc, sceneMvpLightLoc );

}

void Cleanup() {
   glDeleteBuffers( 1, &groundPositionVBO );
   glDeleteBuffers( 1, &groundIndicesIBO );
   glDeleteBuffers( 1, &cubePositionVBO );
   glDeleteBuffers( 1, &cubeIndicesIBO );
   
   glBindFramebuffer ( GL_FRAMEBUFFER, shadowMapBufferId );
   glFramebufferTexture2D ( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0 );
   glBindFramebuffer ( GL_FRAMEBUFFER, 0 );
   glDeleteFramebuffers ( 1, &shadowMapBufferId );
   glDeleteTextures ( 1, &shadowMapTextureId );

   glDeleteProgram ( sceneProgramObject );
   glDeleteProgram ( shadowMapProgramObject );
}

void Sample::test() {
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        setupGraphics(i);
        renderFrame();
        string mode_name = get_enum_name(factors[i].func);
        string bmp_file  = filename + "-" + mode_name + ".bmp";
        LOGI("bmp_file=%s", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
        Cleanup();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
