/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texenv.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for texenv related API
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

struct envmode_t {
	GLenum pname;
	GLenum param;
};

GLenum modes[] = {
	GL_ADD,
	GL_MODULATE,
	GL_DECAL,
	GL_BLEND,
	GL_REPLACE,
	GL_COMBINE
};
GLenum combine_a[] = {
	GL_REPLACE,
	GL_MODULATE,
	GL_ADD,
	GL_ADD_SIGNED,
	GL_INTERPOLATE,
	GL_SUBTRACT
};
GLenum combine_rgb[] = {
	GL_REPLACE,
	GL_MODULATE,
	GL_ADD,
	GL_ADD_SIGNED,
	GL_INTERPOLATE,
	GL_SUBTRACT,
	GL_DOT3_RGB,
	GL_DOT3_RGBA
};
struct envmode_t always[] = {
	{GL_SRC0_RGB,GL_PREVIOUS},
	{GL_SRC1_RGB,GL_CONSTANT},
	{GL_SRC2_RGB,GL_PRIMARY_COLOR},
	{GL_SRC0_ALPHA,GL_PREVIOUS},
	{GL_SRC1_ALPHA,GL_CONSTANT},
	{GL_SRC2_ALPHA,GL_PRIMARY_COLOR},

	{GL_OPERAND0_RGB,GL_SRC_COLOR},
	{GL_OPERAND1_RGB,GL_SRC_COLOR},
	{GL_OPERAND2_RGB,GL_ONE_MINUS_SRC_COLOR},
	{GL_OPERAND0_ALPHA,GL_SRC_ALPHA},
	{GL_OPERAND1_ALPHA,GL_SRC_ALPHA},
	{GL_OPERAND2_ALPHA,GL_ONE_MINUS_SRC_ALPHA}
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
         checkImage[i][j][2] = (GLubyte) 0;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) 255;
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
    GLenum getname[16] = {
	GL_TEXTURE_ENV_MODE,
	GL_TEXTURE_ENV_COLOR,
	GL_COMBINE_RGB,
	GL_COMBINE_ALPHA,
	GL_SRC0_RGB,
	GL_SRC1_RGB,
	GL_SRC2_RGB,
	GL_SRC0_ALPHA,
	GL_SRC1_ALPHA,
	GL_SRC2_ALPHA,
	GL_OPERAND0_RGB,
	GL_OPERAND1_RGB,
	GL_OPERAND2_RGB,
	GL_OPERAND0_ALPHA,
	GL_OPERAND1_ALPHA,
	GL_OPERAND2_ALPHA
    };
    GLint parami;
    GLfloat paramf;

    glGetTexEnviv(GL_TEXTURE_ENV, getname[0], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[0]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[1], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[1]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[2], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[2]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[3], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[3]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[4], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[4]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[5], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[5]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[6], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[6]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[7], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[7]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[8], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[8]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[9], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[9]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[10], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[10]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[11], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[11]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[12], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[12]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[13], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[13]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[14], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[14]), parami);
    glGetTexEnviv(GL_TEXTURE_ENV, getname[15], &parami);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, %s): %d\n",get_enum_name(getname[15]), parami);
    glGetTexEnvfv(GL_TEXTURE_ENV, GL_RGB_SCALE, &paramf);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, GL_RGB_SCALE): %f\n", paramf);
    glGetTexEnvfv(GL_TEXTURE_ENV, GL_ALPHA_SCALE, &paramf);
    LOGI("GetTexEnv(GL_TEXTURE_ENV, GL_ALPHA_SCALE): %f\n", paramf);
}

void renderFrame(int n, GLenum mode)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeCheckImages();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glActiveTexture(GL_TEXTURE0);
    GL_CHECK(glEnable(GL_TEXTURE_2D));

    GL_CHECK(glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode));
    GL_CHECK(glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, mode));
    GL_CHECK(glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, combine_a[n%6]));
    GL_CHECK(glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, combine_rgb[n%8]));
    for(int i=0; i<sizeof(always)/sizeof(always[0]); i++) {
       GL_CHECK(glTexEnvi(GL_TEXTURE_ENV, always[i].pname, always[i].param));

    }
    GL_CHECK(glTexEnvf(GL_TEXTURE_ENV, GL_ALPHA_SCALE, 1.0)); //
    GL_CHECK(glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE, 1.0)); //
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

    for(int i=0; i<8; i++) {
        for (int j = 0; j < 6; j++) {
            string mode_name = get_enum_name(modes[j]);
            char ss[2];
            sprintf(ss, "-%d", i);
            LOGI("%d_%d:", i,j);
            string bmp_file = filename + ss + "-" + mode_name + ".bmp";
            LOGI("filename=%s",bmp_file.c_str());
            renderFrame(i, modes[j]);
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

