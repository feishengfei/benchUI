/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texcompress.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for texcompress related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#define DISABLE_MIPMAPS

using namespace BotsonSDK;
using std::string;

GLfloat texcoord[]={
	0.0, 1.0, 
	0.0, 0.0,
	1.0, 1.0, 
	1.0, 0.0
};

GLfloat vertice[]={
	-3.0, 3.0, 0.0,
	-3.0, -3.0, 0.0,
	3.0, 3.0, 0.0,
	3.0, -3.0, 0.0
};

GLfloat vertices1[] = {
	-2.0, 2.0,
	0.0, -2.0,
	2.0, 2.0
};

GLfloat colors[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0
};

#define checkImageWidth 64
#define checkImageHeight 64
GLubyte image_ub1[checkImageHeight][checkImageWidth];
GLubyte image_ub2[checkImageHeight][checkImageWidth][2];
GLubyte image_ub3[checkImageHeight][checkImageWidth][3];
GLubyte image_ub4[checkImageHeight][checkImageWidth][4];
GLushort image_us[checkImageHeight][checkImageWidth];
#define subcheckImageWidth 16
#define subcheckImageHeight 16
GLubyte subimage_ub1[subcheckImageHeight][subcheckImageWidth];
GLubyte subimage_ub2[subcheckImageHeight][subcheckImageWidth][2];
GLubyte subimage_ub3[subcheckImageHeight][subcheckImageWidth][3];
GLubyte subimage_ub4[subcheckImageHeight][subcheckImageWidth][4];
GLushort subimage_us[subcheckImageHeight][subcheckImageWidth];

struct image_t {
	GLenum format;
	GLfloat r,g,b,a;
};

struct image_t image[] = {
	{GL_RGB, 1.0, 0.0, 0.0, 0.0},
	{GL_RGBA, 1.0, 1.0, 0.0, 0.0},
	{GL_ALPHA, 0.0, 1.0, 0.0, 1.0},
	{GL_LUMINANCE, 0.0, 1.0, 1.0, 1.0},
	{GL_LUMINANCE_ALPHA, 0.0, 0.0, 1.0, 1.0},
};

GLenum formats[] = {
	GL_RGB,
	GL_RGBA,
	GL_ALPHA,
	GL_LUMINANCE,
	GL_LUMINANCE_ALPHA
};

#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLuint texName;

void makeCheckImages(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) (255-c);
         checkImage[i][j][1] = (GLubyte) 255;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

string textureFilename = "res/picture/good_mip_0.pkm";

unsigned char *textureData;
unsigned short Width, Height, PaddedWidth, PaddedHeight;

bool setupGraphics(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrthof(-3.0, 3.0,-3.0, 3.0, -3.0, 3.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
    return true;
}

void loadPKMData(const char *filename)
{
        unsigned char paddedWidthMSB;
        unsigned char paddedWidthLSB;
        unsigned char paddedHeightMSB;
        unsigned char paddedHeightLSB;
        unsigned char widthMSB;
        unsigned char widthLSB;
        unsigned char heightMSB;
        unsigned char heightLSB;

        printf("Texture loadData started for %s...\n", filename);

        FILE *file = fopen(filename, "rb");
        if(file == NULL)
        {
            LOGE("Failed to open '%s'\n", filename);
            exit(1);
        }
        fseek(file, 0, SEEK_END);
        unsigned int length = ftell(file);
        textureData = (unsigned char *)calloc(length,sizeof(unsigned char));
        if(textureData == NULL)
        {
            LOGE("Out of memory at %s:%i\n", "es11-texcompress", __LINE__);
            exit(1);
        }
        fseek(file, 0, SEEK_SET);
        size_t read = fread(textureData, sizeof(unsigned char), length, file);
        if(read != length)
        {
            LOGE("Failed to read in '%s'\n", filename);
            exit(1);
        }
        fclose(file);

        printf("Texture loadData for %s done.\n", filename);

        paddedWidthMSB = textureData[8];
        paddedWidthLSB = textureData[9];
        paddedHeightMSB = textureData[10];
        paddedHeightLSB = textureData[11];
        widthMSB = textureData[12];
        widthLSB = textureData[13];
        heightMSB = textureData[14];
        heightLSB = textureData[15];

        Width = (widthMSB << 8) | widthLSB;
        Height = (heightMSB << 8) | heightLSB;
        PaddedWidth = (paddedWidthMSB << 8) | paddedWidthLSB;
        PaddedHeight = (paddedHeightMSB << 8) | paddedHeightLSB;

        printf("Width=%d Height=%d PaddedWidth=%d PaddedHeight=%d\n", Width, Height, PaddedWidth, PaddedHeight);
}

void renderFrame()
{

    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glGenTextures(1, &texName));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texName));

    string mainTexturePath = (string)PROJECT_PATH + textureFilename;
    loadPKMData(mainTexturePath.c_str());

   glEnable(GL_TEXTURE_2D);
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_ETC1_RGB8_OES, (GLsizei)Width,(GLsizei)Height, 0, (GLsizei)(PaddedWidth * PaddedHeight >> 1), textureData + 16));
    free(textureData);

    unsigned char textureDataSub[64*64];
    memset(textureDataSub,255,sizeof(textureDataSub));
    GL_CHECK(glCompressedTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 64, 64, GL_ETC1_RGB8_OES, 64*32, textureDataSub));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

   glActiveTexture(GL_TEXTURE0);
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texName));

    GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, texcoord));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, vertice));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));

    glDeleteTextures(1, &texName);
    GL_CHECK(glDisable(GL_TEXTURE_2D));
    GL_CHECK(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    string bmp_file = filename + ".bmp";
    LOGI("filename=%s",bmp_file.c_str());
    renderFrame();
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
