/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file light.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for light related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "vertex_ball.h"

using namespace BotsonSDK;
using std::string;

GLenum factors[] = {
	GL_FASTEST,
	GL_NICEST,
	GL_DONT_CARE
};
GLfloat ambient[4] = {0.1745, 0.11175, 0.01175, 1.0};	
GLfloat diffuse[4] = {0.61424, 0.04136, 0.04136, 1.0};	
GLfloat specular[4] = {0.727811, 0.626959, 0.626959, 1.0};	

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrthof (-88.0f, 88.0f, -88.0f*h/w, 88.0f*h/w, -88.0f, 88.0f);
	}
	else {
		glOrthof (-88.0f*w/h, 88.0f*w/h, -88.0f, 88.0f, -88.0f, 88.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getdata() 
{
    GLenum factor1[]={
	GL_SPOT_DIRECTION,
	GL_SPOT_EXPONENT,
	GL_CONSTANT_ATTENUATION,
	GL_LINEAR_ATTENUATION,
	GL_QUADRATIC_ATTENUATION
    };
    GLenum factor4[]={
	GL_AMBIENT,
	GL_DIFFUSE,
	GL_SPECULAR,
	GL_POSITION
    };

    GLfloat param3[3];
    GLfloat param4[4];
    GLfloat param1;

    for(int j=0; j<4; j++) {
        glGetLightfv(GL_LIGHT0, factor4[j],param4);
        LOGI("GetLight(%s)=%f,%f,%f,%f\n",get_enum_name(factor4[j]), param4[0],param4[1],param4[2],param4[3]);
    }
    for(int j=0; j<5; j++) {
        glGetLightfv(GL_LIGHT0, factor1[j],&param1);
        LOGI("GetLight(%s)=%f\n",get_enum_name(factor1[j]),param1);
    }
    glGetLightfv(GL_LIGHT0, GL_SPOT_CUTOFF,param3);
    LOGI("GetLight(GL_SPOT_CUTOFF)=%f,%f,%f\n",param3[0], param3[1], param3[2]);
}

static void render()
{
    GL_CHECK(glEnableClientState(GL_NORMAL_ARRAY));
    GL_CHECK(glNormalPointer(GL_FLOAT, 0, normals_ball));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));

    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, vertices_ball));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, numofball));
}

void renderFrame()
{
   GLfloat position[] = { 50.0, 50.0, -80.0, 0.0 };
   GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, ambient));
   GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse));
   GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, specular));
   GL_CHECK(glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 0.6*128.0));
   GL_CHECK(glLightfv(GL_LIGHT0, GL_POSITION, position));
	float light_model_ambient[4] = {1.0,1.0,1.0,0.0};
	float light_model_two_side = GL_FALSE;
	GL_CHECK(glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light_model_ambient));
	GL_CHECK(glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,light_model_two_side));

	GLfloat light1_ambient[]= { 0.0f, 1.0f, 0.0f, 1.0f };
	GLfloat light1_diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GL_CHECK(glLightfv(GL_LIGHT0, GL_AMBIENT, light1_ambient));
	GL_CHECK(glLightfv(GL_LIGHT0, GL_DIFFUSE, light1_diffuse));
	GL_CHECK(glLightfv(GL_LIGHT0, GL_SPECULAR, light1_specular));

	GL_CHECK(glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5));//
	GL_CHECK(glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5));//
	GL_CHECK(glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2));//
	GL_CHECK(glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0));//
	GL_CHECK(glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0));//

   GL_CHECK(glEnable(GL_LIGHTING));
   GL_CHECK(glEnable(GL_LIGHT0));


   GL_CHECK(glClearColor(0.5, 0.5, 0.5, 0.0));

   GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

   render();

   GL_CHECK(glDisable(GL_LIGHTING));
   GL_CHECK(glDisable(GL_LIGHT0));
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
