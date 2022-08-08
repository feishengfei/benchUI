/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file multitexcoord.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for multitexcoord related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLfloat vertices[] = {
	0.0, 0.0,
	50.0, 100.0,
	100.0, 0.0
};

GLfloat colors[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0
};

static GLubyte texels0[32][32][4];
static GLubyte texels1[16][16][4];

void makeCheckImages(void)
{
   int i, j;
    
   for (i = 0; i < 32; i++) {
      for (j = 0; j < 32; j++) {
         texels0[i][j][0] = (GLubyte) i;
         texels0[i][j][1] = (GLubyte) 255;
         texels0[i][j][2] = (GLubyte) (i*j)/255;
         texels0[i][j][3] = (GLubyte) 255;
      }
   }

   for (i = 0; i < 16; i++) {
      for (j = 0; j < 16; j++) {
         texels1[i][j][0] = (GLubyte) 255;
         texels1[i][j][1] = (GLubyte) i;
         texels1[i][j][2] = (GLubyte) j;
         texels1[i][j][3] = (GLubyte) 255;
      }
   }
}

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof (-3.0f, 130.0f, -3.0f, 130.0f, -3.0f, 3.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void renderFrame()
{
   GLuint texNames[2];

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeCheckImages();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(2, texNames);
   glBindTexture(GL_TEXTURE_2D, texNames[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, texels0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glBindTexture(GL_TEXTURE_2D, texNames[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, texels1);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texNames[0]);
   glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glMatrixMode (GL_TEXTURE);
      glLoadIdentity();
      glTranslatef(0.5f, 0.5f, 0.0f);
      glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
      glTranslatef(-0.5f, -0.5f, 0.0f);
   glMatrixMode (GL_MODELVIEW);
   glActiveTexture(GL_TEXTURE1);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texNames[1]);
   glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glMultiTexCoord4f(GL_TEXTURE0, 0.0, 0.0, 0.0, 1.0);
   glMultiTexCoord4f(GL_TEXTURE1, 1.0, 0.0, 0.0, 1.0);
   glMultiTexCoord4f(GL_TEXTURE0, 0.5, 1.0, 0.0, 1.0);
   glMultiTexCoord4f(GL_TEXTURE1, 0.5, 0.0, 0.0, 1.0);
   glMultiTexCoord4f(GL_TEXTURE0, 1.0, 0.0, 0.0, 1.0);
   glMultiTexCoord4f(GL_TEXTURE1, 1.0, 1.0, 0.0, 1.0);
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

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
