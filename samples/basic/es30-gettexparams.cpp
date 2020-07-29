/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file gettexparams.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for gettexparams related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Texture.h"

using std::string;
using namespace BotsonSDK;

string textureFilename = "RotoZoom.raw";
string vertexShaderFilename = "GetTexParams.vert";
string fragmentShaderFilename = "GetTexParams.frag";

static const GLubyte indices[] = {0,  1,  2,  3};

static const GLfloat vertices[] = {
    -0.800000f,  0.8000f, 0.0f,
    -0.800000f, -0.8000f, 0.0f,
     0.800000f,  0.8000f, 0.0f,
     0.800000f, -0.8000f, 0.0f,
};

static const GLfloat textureCoordinates[] = {
    0.0f, 0.0f, 
    0.0f, 1.0f, 
    1.0f, 0.0f, 
    1.0f, 1.0f, 
};

GLuint textureID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocTexCoord = -1;
GLint iLocSampler = -1;

GLenum factors[] = {
	GL_TEXTURE_BASE_LEVEL,
	GL_TEXTURE_COMPARE_FUNC,
	GL_TEXTURE_COMPARE_MODE,
	GL_TEXTURE_IMMUTABLE_FORMAT,
	GL_TEXTURE_MAX_LEVEL,
	GL_TEXTURE_MAX_LOD,
	GL_TEXTURE_MIN_LOD,
	GL_TEXTURE_SWIZZLE_R,
	GL_TEXTURE_SWIZZLE_G,
	GL_TEXTURE_SWIZZLE_B,
	GL_TEXTURE_SWIZZLE_A,
	GL_TEXTURE_WRAP_R
};

int num_factors = (int)ARRAY_NUM(factors);
string filename="demo.bmp";
string src_name;

bool setupGraphics(int w, int h) {
    string texturePath = (string)PICTURE_PATH + textureFilename;
    string vertexShaderPath = (string)GLSL_PATH + vertexShaderFilename; 
    string fragmentShaderPath = (string)GLSL_PATH + fragmentShaderFilename;
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    GL_CHECK(glActiveTexture(GL_TEXTURE0))
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    unsigned char* textureData = NULL;

    Texture::loadData(texturePath.c_str(), &textureData);
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA,
                          GL_UNSIGNED_BYTE, textureData)); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_ZERO);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 4.0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, -4.0);
    for(int i=0; i<num_factors; i++) {
	if(factors[i] == GL_TEXTURE_MAX_LOD || factors[i] == GL_TEXTURE_MIN_LOD) {
	float paramf;
	glGetTexParameterfv(GL_TEXTURE_2D, factors[i], &paramf);
	LOGI("%s: %d\n",get_enum_name(factors[i]),paramf);} else {
	int parami;
	glGetTexParameteriv(GL_TEXTURE_2D, factors[i], &parami);
	LOGI("%s: 0x%x\n",get_enum_name(factors[i]),parami);}
    }

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGD("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGD("fragmentShaderID = %d", fragmentShaderID);
    programID = GL_CHECK(glCreateProgram());
    if (!programID) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    GL_CHECK(glUseProgram(programID));

    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    if(iLocPosition == -1) {
        LOGE("Attribute not found: \"a_v4Position\"");
        exit(1);
    }
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    iLocTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_v2TexCoord"));
    if(iLocTexCoord == -1) {
        LOGW("Warning: Attribute not found: \"a_v2TexCoord\"");
    } else {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }
    iLocSampler = GL_CHECK(glGetUniformLocation(programID, "u_s2dTexture"));
    if(iLocSampler == -1) {
        LOGW("Warning: Uniform not found: \"u_s2dTexture\"");
    } else {
        GL_CHECK(glUniform1i(iLocSampler, 0));
    }

    glViewport(0,0,256,256);
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0));
    free(textureData);
    return true;
}

void renderFrame(void) {
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));

    if(iLocTexCoord != -1) {
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates));
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices);
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
