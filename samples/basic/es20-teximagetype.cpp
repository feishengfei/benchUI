/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file teximagetype.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for teximagetype related API
 * @par TestPoints:
 *
 */

#include "Sample.h"


using std::string;
using namespace BotsonSDK;

static const GLubyte indices[] = {
     0,  1,  2,  3
};

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

string textureFilename = "RotoZoom.raw";

GLuint textureID;
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocTexCoord = -1;
GLint iLocSampler = -1;

static GLint TexWidth = 128, TexHeight = 128;

GLenum factors[] = {
	GL_ALPHA,
	GL_LUMINANCE,
	GL_LUMINANCE_ALPHA
};
struct pixel_format {
	GLenum format;
	GLenum type;
	GLint bytes;
	GLuint redTexel, greenTexel, blueTexel; /* with approx 51% alpha, when applicable */
};

struct pixel_format Formats[] = {
	{ GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 2, 0xf800, 0x7e0 },
	{ GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 2, 0xf008, 0x0f08 },
	{ GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 2, 0xf801, 0x7c1 }
};

static void
fill_texture_image(GLint w, GLint h, struct pixel_format *format, GLushort *buf,
        GLushort *buf1) {
   GLint i, j;
   for (i = 0; i < h; i++) {
       for (j = 0; j < w; j++) {
           GLushort us;
           if ((i + j) % 2 == 0) {
               us = format->redTexel;
           } else {
               us = format->greenTexel;
           }
           *buf++ = us;
       }
   }

   for (i = 0; i < h/4; i++) {
       for (j = 0; j < w / 4; j++) {
           GLushort us;
           if ((i + j) % 4 == 0) {
               us = format->greenTexel;
           } else {
               us = format->redTexel;
           }
           *buf1++ = us;
       }
   }
}

void setTexImage(struct pixel_format *format) {
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0))
    GLushort *image;
    image = (GLushort *)malloc(TexWidth * TexHeight * sizeof(GLushort));
    GLushort *image1;
    image1 = (GLushort *)malloc(TexWidth / 4 * TexHeight / 4 * sizeof(GLushort));
    fill_texture_image(TexWidth, TexHeight, format, image, image1);

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, format->format, TexWidth, TexHeight,
                          0, format->format, format->type, image));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 12, 44, TexWidth / 4, TexHeight / 4,
                    format->format, format->type, image1);
    free(image);
    free(image1);
}

bool setupGraphics(int w, int h) {
    string texturePath = ((string)GLSL_PATH) + textureFilename;
    string vertexShaderPath = ((string)GLSL_PATH) + "texture2d.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "texture2d.frag";
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d\n", fragmentShaderID);

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

    glViewport(0,0,WINDOW_W,WINDOW_H);
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0));

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
    GL_CHECK(glDeleteTextures(1, &textureID));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(Formats); i++) {
        setTexImage(&(Formats[i]));
        renderFrame();
        string src_name=get_enum_name(Formats[i].type);
        string bmp_file = filename + src_name + ".bmp";
        LOGI("bmp_file=%s", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv){
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
