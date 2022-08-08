/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texcoordpointer.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for texcoordpointer related API
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
GLbyte texcoord_b[]={
	0, 1, 
	0, 0,
	1, 1, 
	1, 0
};
GLshort texcoord_s[]={
	0, 1, 
	0, 0,
	1, 1, 
	1, 0
};
GLfloat vertice[]={
	-2.0, 1.0, 0.0,
	-2.0, -1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, -1.0, 0.0
};

static const GLenum texcoord_format[] = {
	GL_BYTE,
	GL_SHORT,
	GL_FLOAT
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
         checkImage[i][j][0] = (GLubyte) 0;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) 255;
         checkImage[i][j][3] = (GLubyte) 255;
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

void renderFrame(GLenum coord_type)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeCheckImages();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, texName);

    GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    switch(coord_type) {
    case GL_BYTE:
        GL_CHECK(glTexCoordPointer(2, GL_BYTE, 0, texcoord_b));
        break;
    case GL_SHORT:
        GL_CHECK(glTexCoordPointer(2, GL_SHORT, 0, texcoord_s));
        break;
    default:
        GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, texcoord));
    }
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, vertice));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.8));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));

    glDeleteTextures(1, &texName);
    GL_CHECK(glDisable(GL_TEXTURE_2D));
    GL_CHECK(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<3; i++) {
        string type_name = get_enum_name(texcoord_format[i]);
        string bmp_file = filename + "-" + type_name + ".bmp";
        LOGI("filename=%s",bmp_file.c_str());
        renderFrame(texcoord_format[i]);
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
