/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texparameter.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for texparameter related API
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

static const GLenum fliter[] = {
            GL_NEAREST,
            GL_LINEAR
};

static const GLenum wrap[] = {
          GL_CLAMP_TO_EDGE,
          GL_REPEAT
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
         checkImage[i][j][0] = (GLubyte) 255;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) 0;
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

void getdata()
{
	GLenum pname[]={
		GL_TEXTURE_MIN_FILTER,
		GL_TEXTURE_MAG_FILTER,
		GL_TEXTURE_WRAP_S,
		GL_TEXTURE_WRAP_T
	};
	GLint param;

	for(int i=0; i<4; i++) {
		glGetTexParameteriv(GL_TEXTURE_2D, pname[i], &param);
		LOGI("GetTexParameter(%s): %d\n",get_enum_name(pname[i]), param);
	}
}

void renderFrame(GLenum fliter, GLenum wrap)
{
    GLboolean isTex;
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeCheckImages();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    isTex = glIsTexture(texName);
    LOGI("before: isTex:%s\n",isTex==GL_TRUE?"YES":"NO");
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, fliter);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, fliter);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, texName);

    GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, texcoord));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, vertice));
    GL_CHECK(glColor4f(0.0, 0.0, 1.0, 0.8));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    isTex = glIsTexture(texName);
    LOGI("after: isTex:%s\n",isTex==GL_TRUE?"YES":"NO");
    getdata();
    glDeleteTextures(1, &texName);
    GL_CHECK(glDisable(GL_TEXTURE_2D));
    GL_CHECK(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<2; i++) {
        for (int j = 0; j < 2; j++) {
            string fliter_name = get_enum_name(fliter[i]);
            string wrap_name = get_enum_name(wrap[j]);
            string bmp_file = filename + "-" + fliter_name + "-" + wrap_name + ".bmp";
            LOGI("filename=%s",bmp_file.c_str());
            renderFrame(fliter[i], wrap[j]);
            save2bmp(bmp_file.c_str());
            SwapBuffers();
        }
    }
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
