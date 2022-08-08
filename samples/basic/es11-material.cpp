/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file material.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for material related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "vertex_roll.h"

using namespace BotsonSDK;
using std::string;

GLenum factors[] = {
	GL_FASTEST,
	GL_NICEST,
	GL_DONT_CARE
};
GLfloat ambient[4] = {0.1745, 0.01175, 0.01175, 1.0};	
GLfloat diffuse[4] = {0.61424, 0.04136, 0.04136, 1.0};	

GLfloat specular[4] = {0.727811, 0.626959, 0.626959, 1.0};
GLfloat emission[4] = {0.456811, 0.321759, 0.268159, 1.0};


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

static void renderSphere (GLfloat x, GLfloat y, GLfloat z)
{
   glTranslatef (x, y, z);
    GL_CHECK(glEnableClientState(GL_NORMAL_ARRAY));
    GL_CHECK(glNormalPointer(GL_FLOAT, 0, normals_roll));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, vertex_roll));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, numofroll));
}

void getdata() 
{
    GLenum face[]={
	GL_FRONT,
	GL_BACK
    };

    GLenum factor[]= {
            GL_AMBIENT,
            GL_DIFFUSE,
            GL_SPECULAR,
            GL_EMISSION
    };
    GLfloat param4[4];
    GLfloat param1;
    GLfloat param2;

    for(int i=0; i<2; i++) {
        for(int j=0; j<3; j++) {
            glGetMaterialfv(face[i], factor[j],param4);
            LOGI("GetMaterial(%s,%s)=%f,%f,%f,%f\n",get_enum_name(face[i]), get_enum_name(factor[j]), param4[0],param4[1],param4[2],param4[3]);
        }
        glGetMaterialfv(face[i], GL_SHININESS,&param1);
        LOGI("GetMaterial(%s,GL_SHININESS)=%f\n",get_enum_name(face[i]), param1);
    }
}

void renderFrame1()
{
   GLfloat position[] = { 50.0, 50.0, 80.0, 0.0 };

   GL_CHECK(glLightfv(GL_LIGHT0, GL_POSITION, position));
   GL_CHECK(glEnable(GL_LIGHTING));
   GL_CHECK(glEnable(GL_LIGHT0));
   GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, ambient));
   GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse));
   GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, specular));
   GL_CHECK(glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 0.6*128.0));
    GL_CHECK(glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, emission));


   GL_CHECK(glClearColor(0.5, 0.5, 0.5, 0.0));

   GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
   renderSphere (0.0, 0.0, 0.0);
   getdata();
   GL_CHECK(glDisable(GL_LIGHTING));
   GL_CHECK(glDisable(GL_LIGHT0));
}

void Sample::test()
{
    setupGraphics(WINDOW_W, WINDOW_H);

    renderFrame1();
    string bmp_file = filename + ".bmp";
    LOGI("filename=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
