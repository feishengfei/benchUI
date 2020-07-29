/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texcopy.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for texcopy related API
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

static GLuint texName;

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

void renderFrame(struct image_t imgformat)
{

   glPixelStorei(GL_PACK_ALIGNMENT, 4);
   glViewport(0, 0, WINDOW_W, WINDOW_H);

    GL_CHECK(glClearColor(imgformat.r, imgformat.g, imgformat.b, imgformat.a));
    printf("clear data: %f,%f,%f,%f\n",imgformat.r, imgformat.g, imgformat.b, imgformat.a);
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, imgformat.format, 0, 0, WINDOW_W, WINDOW_H, 0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glViewport(0,0,WINDOW_W,WINDOW_H);
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

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

    for(int i=0; i<ARRAY_NUM(image); i++) {
        string format_name = get_enum_name(image[i].format);
        string bmp_file = filename + "-" + format_name + ".bmp";
        LOGI("filename=%s",bmp_file.c_str());
        renderFrame(image[i]);
        save2bmp(bmp_file.c_str());
        SwapBuffers();
    }
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
