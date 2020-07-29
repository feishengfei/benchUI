/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file fog.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for fog related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

float vertices[]={
	-4.0,-1.0,  
	-4.0,1.0,
	-3.0,-1.0,
	-3.0,1.0
};

GLenum factors[] = {
	GL_FASTEST,
	GL_NICEST,
	GL_DONT_CARE
};
static GLint fogMode;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrthof (-5.0f, 5.0f, -5.0f*h/w, 5.0f*h/w, -5.0f, 5.0f);
	}
	else {
		glOrthof (-5.0f*w/h, 5.0f*w/h, -5.0f, 5.0f, -5.0f, 5.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

static void renderSphere (GLfloat x, GLfloat y, GLfloat z)
{
   glPushMatrix();
   glTranslatef (x, y, z);
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertices));
    GL_CHECK(glNormal3f(0.0, 0.0, 1.0));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.0));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
   glPopMatrix();
}

void renderFrame(GLenum factor)
{
   GLfloat position[] = { 3.0, 2.0, 3.0, 0.0 };

   GL_CHECK(glEnable(GL_DEPTH_TEST));

   GL_CHECK(glLightfv(GL_LIGHT0, GL_POSITION, position));
   GL_CHECK(glEnable(GL_LIGHTING));
   GL_CHECK(glEnable(GL_LIGHT0));
   {
      GLfloat mat[3] = {0.1745, 0.01175, 0.01175};	
      GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mat));
      mat[0] = 0.61424; mat[1] = 0.04136; mat[2] = 0.04136;	
      GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat));
      mat[0] = 0.727811; mat[1] = 0.626959; mat[2] = 0.626959;
      GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat));
      GL_CHECK(glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 0.6*128.0));
   }

   GL_CHECK(glEnable(GL_FOG));
   {
      GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0};

      fogMode = GL_EXP;
      GL_CHECK(glFogf (GL_FOG_MODE, fogMode));
      GL_CHECK(glFogfv (GL_FOG_COLOR, fogColor));
      GL_CHECK(glFogf (GL_FOG_DENSITY, 0.35));
      GL_CHECK(glHint (GL_FOG_HINT, factor));// 
      GL_CHECK(glFogf (GL_FOG_START, 1.0));
      GL_CHECK(glFogf (GL_FOG_END, 5.0));
   }
    GL_CHECK(glClearColor(0.5, 0.5, 0.5, 1.0));

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
   renderSphere (0.0, 0.0, 0.0);
   renderSphere (2.0, 0.0, 0.0);
   renderSphere (5.0, 0.0, 0.0);
   renderSphere (7.0, 0.0, 0.0);
//   glFlush();
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    for(int i=0; i<ARRAY_NUM(factors); i++) {
        renderFrame(factors[i]);
        string factor_name = get_enum_name(factors[i]);
        string bmp_file = filename + "-" + factor_name + ".bmp";
        LOGI("filename=%s",bmp_file.c_str());
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
