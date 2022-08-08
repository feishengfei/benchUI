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
#define BUFFER_OFFSET(x)  ((const void*) (x))
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
GLuint programID, VAOs, Buffers;


static GLint TexWidth = 128, TexHeight = 128;

GLenum factors[] = {
	//GL_ALPHA,
	//GL_LUMINANCE,
	//GL_LUMINANCE_ALPHA,
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
    GL_CHECK(glPixelStoref(GL_UNPACK_ALIGNMENT, 1.2));
    if (format == GL_RGBA) {
        makeCheckImages();
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, format, checkImageWidth, checkImageHeight,
                     0, format, GL_UNSIGNED_BYTE, checkImage));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 12, 44, subImageWidth,
                        subImageHeight, format, GL_UNSIGNED_BYTE, subImage));
    } else if (format == GL_RGB) {
        makeCheckImages1();
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, format, checkImageWidth, checkImageHeight,
                     0, format, GL_UNSIGNED_BYTE, checkImage1));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 12, 44, subImageWidth,
                        subImageHeight, format, GL_UNSIGNED_BYTE, subImage1));
    } /*else {
        GLubyte *image;
        image = (GLubyte *)malloc(TexWidth * TexHeight * 2 * sizeof(GLubyte));
        GLubyte *image1;
        image1 = (GLubyte *)malloc(TexWidth / 4 * TexHeight / 4 * 2 * sizeof(GLubyte));
        GLuint comps = (format == GL_ALPHA) ? 1 : 2;
        fill_texture_image(TexWidth, TexHeight, comps, image, image1);
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, format, TexWidth, TexHeight, 0,
                              format, GL_UNSIGNED_BYTE, image));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 12, 44, TexWidth / 4, TexHeight / 4, format,
                        GL_UNSIGNED_BYTE, image1));
        free(image);
        free(image1);
    }*/
}

bool setupGraphics(int w, int h) {
    string texturePath = ((string)PICTURE_PATH) + textureFilename;
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    ShaderInfo  shaders[] = {
            { GL_VERTEX_SHADER,  "pixelstoref.vert" },
            { GL_FRAGMENT_SHADER, "pixelstoref.frag" },
            { GL_NONE, NULL }
    };

    programID = Shader::LoadShaders(shaders);

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(textureCoordinates), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(textureCoordinates), textureCoordinates));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glUseProgram(programID));
    glViewport(0,0,WINDOW_W,WINDOW_H);
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 1.0));

    return true;
}

void renderFrame(void) {
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices));
    GL_CHECK(glDeleteTextures(1, &textureID));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(factors); i++) {
        setTexImage(factors[i]);
        renderFrame();
        string src_name=get_enum_name(factors[i]);
        string bmp_file = filename + src_name + ".bmp";
        LOGI("bmp_file=%s\n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

