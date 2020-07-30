/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file teximage.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for teximage related API
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

#define checkImageWidth 64
#define checkImageHeight 64
GLubyte image_ub1[checkImageHeight][checkImageWidth];
GLubyte image_ub2[checkImageHeight][checkImageWidth][2];
GLubyte image_ub3[checkImageHeight][checkImageWidth][3];
GLubyte image_ub4[checkImageHeight][checkImageWidth][4];
GLushort image_us[checkImageHeight][checkImageWidth];

struct image_t {
	GLenum format;
	GLenum type;
	GLint num;
	GLuint redTexel, greenTexel;
};

struct image_t image[] = {
	{GL_RGB, GL_UNSIGNED_BYTE, 3, 0,0},
	{GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 1, 0xf800, 0x7e0},
	{GL_RGBA, GL_UNSIGNED_BYTE, 4, 0,0},
	{GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, 1, 0xf008, 0x0f08},
	{GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 1, 0xf801, 0x7c1},
	{GL_ALPHA, GL_UNSIGNED_BYTE, 1, 0,0},
	{GL_LUMINANCE, GL_UNSIGNED_BYTE, 2, 0,0},
	{GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, 2, 0,0},
};

static GLuint texName;

void makeCheckImages(struct image_t imgdata)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         if(imgdata.redTexel == 0) {
            c = (((i&0x8)==0)^((j&0x8)==0))*255;
            switch (imgdata.num) {
            case 1:
               image_ub1[i][j] = (GLubyte) c;
               break;
            case 2:
               image_ub2[i][j][0] = (GLubyte) c;
               image_ub2[i][j][1] = (GLubyte) c;
               break;
            case 3:
               image_ub3[i][j][0] = (GLubyte) c;
               image_ub3[i][j][1] = (GLubyte) 255;
               image_ub3[i][j][2] = (GLubyte) 0;
               break;
            case 4:
               image_ub4[i][j][0] = (GLubyte) c;
               image_ub4[i][j][1] = (GLubyte) 0;
               image_ub4[i][j][2] = (GLubyte) 255;
               image_ub4[i][j][3] = (GLubyte) 255;
               break;
            default:
               break;
            }
         } else {
            image_us[i][j] = (((i&0x8)==0)^((j&0x8)==0)) ? imgdata.redTexel : imgdata.greenTexel;
            
         }
      }
   }
}

bool setupGraphics(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrthof(-3.0, 3.0,-3.0, 3.0, -3.0, 3.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
    return true;
}

void renderFrame(struct image_t imgdata)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   makeCheckImages(imgdata);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   if(imgdata.redTexel == 0) {
     switch (imgdata.num) {
     case 1:
        glTexImage2D(GL_TEXTURE_2D, 0, imgdata.format, checkImageWidth, checkImageHeight, 
                0, imgdata.format, imgdata.type, image_ub1);
        break;
     case 2:
        glTexImage2D(GL_TEXTURE_2D, 0, imgdata.format, checkImageWidth, checkImageHeight, 
                0, imgdata.format, imgdata.type, image_ub2);
        break;
     case 3:
        glTexImage2D(GL_TEXTURE_2D, 0, imgdata.format, checkImageWidth, checkImageHeight, 
                0, imgdata.format, imgdata.type, image_ub3);
               break;
     case 4:
        glTexImage2D(GL_TEXTURE_2D, 0, imgdata.format, checkImageWidth, checkImageHeight, 
                0, imgdata.format, imgdata.type, image_ub4);
        break;
     default:
        break;
     }
   } else {
     glTexImage2D(GL_TEXTURE_2D, 0, imgdata.format, checkImageWidth, checkImageHeight, 
                0, imgdata.format, imgdata.type, image_us);
   }
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
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

    for(int i=0; i<8; i++) {
        string type_name = get_enum_name(image[i].type);
        string format_name = get_enum_name(image[i].format);
        string bmp_file = filename + "-" + format_name + "-" + type_name + ".bmp";
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
