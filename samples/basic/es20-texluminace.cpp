/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texluminace.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-26, Add commit
 * @brief basic test for texluminace related API
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
	GL_LUMINANCE_ALPHA,
	GL_RGB,
	GL_RGBA
};

#define checkImageWidth 64
#define checkImageHeight 64
#define subImageWidth 16
#define subImageHeight 16
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLubyte subImage[subImageHeight][subImageWidth][4];
static GLubyte checkImage1[checkImageHeight][checkImageWidth][3];
static GLubyte subImage1[subImageHeight][subImageWidth][3];

void fill_texture_image(GLint w, GLint h, GLint comps, GLubyte *buf, GLubyte *buf1)
{
   GLint i, j, k;
   for (i = 0; i < h; i++) {
      for (j = 0; j < w; j++) {
         for (k = 0; k < comps; k++) {
            GLfloat val;
            if (k == 0) {
               val = (int) (255 * j / (float) (w - 1));
            } else {
               val = (int) (255 * i / (float) (h - 1));
            }
            *buf++ = val;
         }
      }
   }

   for (i = 0; i < h/4; i++) {
      for (j = 0; j < w/4; j++) {
         for (k = 0; k < comps; k++) {
            GLfloat val;
            if (k == 0) {
               val = (int) (127 * j / (float) (w - 1));
            } else {
               val = (int) (127 * i / (float) (h - 1));
            }
            *buf1++ = val;
         }
      }
   }
}

void makeCheckImages(void) {
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
   for (i = 0; i < subImageHeight; i++) {
      for (j = 0; j < subImageWidth; j++) {
         c = ((((i&0x4)==0)^((j&0x4))==0))*255;
         subImage[i][j][0] = (GLubyte) c;
         subImage[i][j][1] = (GLubyte) 0;
         subImage[i][j][2] = (GLubyte) 0;
         subImage[i][j][3] = (GLubyte) 255;
      }
   }
}

void makeCheckImages1(void) {
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage1[i][j][0] = (GLubyte) c;
         checkImage1[i][j][1] = (GLubyte) 0;
         checkImage1[i][j][2] = (GLubyte) c;
      }
   }
   for (i = 0; i < subImageHeight; i++) {
      for (j = 0; j < subImageWidth; j++) {
         c = ((((i&0x4)==0)^((j&0x4))==0))*255;
         subImage1[i][j][0] = (GLubyte) 0;
         subImage1[i][j][1] = (GLubyte) c;
         subImage1[i][j][2] = (GLubyte) 0;
      }
   }
}

void setTexImage(GLenum format) {
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0))
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (format == GL_RGBA) {
        makeCheckImages();
        glTexImage2D(GL_TEXTURE_2D, 0, format, checkImageWidth, checkImageHeight,
                     0, format, GL_UNSIGNED_BYTE, checkImage);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 12, 44, subImageWidth,
                        subImageHeight, format, GL_UNSIGNED_BYTE, subImage);
    } else if (format == GL_RGB) {
        makeCheckImages1();
        glTexImage2D(GL_TEXTURE_2D, 0, format, checkImageWidth, checkImageHeight,
                     0, format, GL_UNSIGNED_BYTE, checkImage1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 12, 44, subImageWidth,
                        subImageHeight, format, GL_UNSIGNED_BYTE, subImage1);
    } else {
        GLubyte *image;
        image = (GLubyte *)malloc(TexWidth * TexHeight * 2 * sizeof(GLubyte));
        GLubyte *image1;
        image1 = (GLubyte *)malloc(TexWidth / 4 * TexHeight / 4 * 2 * sizeof(GLubyte));
        GLuint comps = (format == GL_ALPHA) ? 1 : 2;
        fill_texture_image(TexWidth, TexHeight, comps, image, image1);
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, format, TexWidth, TexHeight, 0,
                              format, GL_UNSIGNED_BYTE, image));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 12, 44, TexWidth / 4, TexHeight / 4, format,
                        GL_UNSIGNED_BYTE, image1);
        free(image);
        free(image1);
    }
}

bool setupGraphics(int w, int h) {
    string texturePath = ((string)PICTURE_PATH) + textureFilename;
    string vertexShaderPath = ((string)GLSL_PATH) + "texture2d.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "texture2d.frag";
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d", fragmentShaderID);

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

    for(int i=0; i<ARRAY_NUM(factors); i++) {
        setTexImage(factors[i]);
        renderFrame();
        string src_name=get_enum_name(factors[i]);
        string bmp_file = filename + src_name + ".bmp";
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

