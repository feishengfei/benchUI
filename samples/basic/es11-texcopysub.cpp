/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texcopysub.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for texcopysub related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat texcoord[]={
	0.0, 1.0, 
	0.0, 0.0,
	1.0, 1.0, 
	1.0, 0.0
};

GLfloat vertice[]={
	-2.0, 1.0, 0.0,
	-2.0, -1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, -1.0, 0.0
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

bool setupGraphics(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrthof(-3.0, 3.0,-3.0, 3.0, -3.0, 3.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
    return true;
}

void renderFrame()
{
   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
   makeCheckImages();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);


    GL_CHECK(glCopyTexSubImage2D(GL_TEXTURE_2D, 0, checkImageWidth/4, checkImageHeight/4, checkImageWidth/4, checkImageHeight/4, checkImageWidth/4, checkImageHeight/4));
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


   glBindTexture(GL_TEXTURE_2D, texName);

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
