/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"
#include <cstring>

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

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA | GLUT_ACCUM;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho (-5.0f, 5.0f, -5.0f*h/w, 5.0f*h/w, -5.0f, 5.0f);
	}
	else {
		glOrtho (-5.0f*w/h, 5.0f*w/h, -5.0f, 5.0f, -5.0f, 5.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getdata()
{
GLint parami;
GLboolean paramb;
GLfloat paramf4[4];
GLfloat paramf3[3];
GLfloat paramf;

glGetBooleanv(GL_FOG, &paramb); 
LOGIF("get(GL_FOG)=%s\n",GET_BOOL(paramb));
glGetBooleanv(GL_NORMALIZE, &paramb); 
LOGIF("get(GL_NORMALIZE)=%s\n",GET_BOOL(paramb));
glGetBooleanv(GL_RESCALE_NORMAL, &paramb); 
LOGIF("get(GL_RESCALE_NORMAL)=%s\n",GET_BOOL(paramb));

glGetFloatv(GL_FOG_COLOR, paramf4); 
LOGIF("get(GL_FOG_COLOR):%f,%f,%f,%f\n", paramf4[0], paramf4[1], paramf4[2], paramf4[3]);
glGetFloatv(GL_FOG_DENSITY, &paramf); 
LOGIF("get(GL_FOG_DENSITY):%f\n", paramf);
glGetFloatv(GL_FOG_END, &paramf); 
LOGIF("get(GL_FOG_END):%f\n", paramf);
glGetFloatv(GL_FOG_START, &paramf); 
LOGIF("get(GL_FOG_START):%f\n", paramf);
glGetFloatv(GL_CURRENT_NORMAL, paramf4); 
LOGIF("get(GL_CURRENT_NORMAL):%f,%f,%f\n", paramf3[0], paramf3[1], paramf3[2]);

glGetIntegerv(GL_FOG_MODE, &parami);
LOGIF("get(GL_FOG_MODE)=%d\n",parami);
glGetIntegerv(GL_FOG_HINT, &parami);
LOGIF("get(GL_FOG_HINT)=%d\n",parami);
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
  //  GL_CHECK(glDisableClientState(GL_COLOR_ARRAY));
//    GL_CHECK(glDisableClientState(GL_NORMAL_ARRAY));
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
   glFlush();
getdata();
}

int main(int argc, char** argv)
{
    string file = "gl13-fog";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<3; i++) {
        renderFrame(factors[i]);
	string factor_name = get_enum_name(factors[i]);
        string filename = file + "-" + factor_name + ".bmp";
        LOGIF("filename=%s\n", filename.c_str());
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
