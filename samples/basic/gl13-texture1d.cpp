/**
 * @file gl13-texture1d.cpp
 * @testpoint glTexImage1D glTexSubImage1D
 *
 */

#include "gl-util.h"
#include <cstring>

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

#define	iWidth 64

GLubyte image_ub1[iWidth];
GLubyte image_ub2[iWidth][2];
GLubyte image_ub3[iWidth][3];
GLubyte image_ub4[iWidth][4];
GLushort image_us[iWidth];

static GLuint texName;

#define	iSubWidth 16

GLubyte iSubmage_ub1[iSubWidth];
GLubyte iSubmage_ub2[iSubWidth][2];
GLubyte iSubmage_ub3[iSubWidth][3];
GLubyte iSubmage_ub4[iSubWidth][4];
GLushort iSubmage_us[iSubWidth];

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

static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;

void makeCheckImages(struct image_t imgdata)
{
   int i, c;
    
   for (i = 0; i < iWidth; i++) {
         if(imgdata.redTexel == 0) {
            c = (((i&0x8)==0))*255;
            switch (imgdata.num) {
            case 1:
               image_ub1[i] = (GLubyte) c;
               break;
            case 2:
               image_ub2[i][0] = (GLubyte) c;
               image_ub2[i][1] = (GLubyte) c;
               break;
            case 3:
               image_ub3[i][0] = (GLubyte) c;
               image_ub3[i][1] = (GLubyte) 255;
               image_ub3[i][2] = (GLubyte) 0;
               break;
            case 4:
               image_ub4[i][0] = (GLubyte) c;
               image_ub4[i][1] = (GLubyte) 0;
               image_ub4[i][2] = (GLubyte) 255;
               image_ub4[i][3] = (GLubyte) 255;
               break;
            default:
               break;
            }
         } else {
            image_us[i] = (((i&0x8)==0)) ? imgdata.redTexel : imgdata.greenTexel;
      }
   }

   for (i = 0; i < iSubWidth; i++) {
         if(imgdata.redTexel == 0) {
            c = (((i&0x4)==0))*255;
            switch (imgdata.num) {
            case 1:
               iSubmage_ub1[i] = (GLubyte) c;
               break;
            case 2:
               iSubmage_ub2[i][0] = (GLubyte) c;
               iSubmage_ub2[i][1] = (GLubyte) c;
               break;
            case 3:
               iSubmage_ub3[i][0] = (GLubyte) c;
               iSubmage_ub3[i][1] = (GLubyte) 255;
               iSubmage_ub3[i][2] = (GLubyte) 0;
               break;
            case 4:
               iSubmage_ub4[i][0] = (GLubyte) c;
               iSubmage_ub4[i][1] = (GLubyte) 0;
               iSubmage_ub4[i][2] = (GLubyte) 255;
               iSubmage_ub4[i][3] = (GLubyte) 255;
               break;
            default:
               break;
            }
         } else {
            iSubmage_us[i] = (((i&0x8)==0)) ? imgdata.redTexel : imgdata.greenTexel;
      }
   }
}

void renderFrame(struct image_t imgdata)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   makeCheckImages(imgdata);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_1D, texName);
   glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   if(imgdata.redTexel == 0) {
     switch (imgdata.num) {
     case 1:
        glTexImage1D(GL_TEXTURE_1D, 0, imgdata.format, iWidth,
                0, imgdata.format, imgdata.type, image_ub1);
        glTexSubImage1D(GL_TEXTURE_1D, 0, 10,iSubWidth, imgdata.format, imgdata.type, iSubmage_ub1);
        break;
     case 2:
        glTexImage1D(GL_TEXTURE_1D, 0, imgdata.format, iWidth,
                0, imgdata.format, imgdata.type, image_ub2);
        glTexSubImage1D(GL_TEXTURE_1D, 0, 10,iSubWidth, imgdata.format, imgdata.type, iSubmage_ub2);
        break;
     case 3:
        glTexImage1D(GL_TEXTURE_1D, 0, imgdata.format, iWidth,
                0, imgdata.format, imgdata.type, image_ub3);
        glTexSubImage1D(GL_TEXTURE_1D, 0, 10,iSubWidth, imgdata.format, imgdata.type, iSubmage_ub3);
               break;
     case 4:
        glTexImage1D(GL_TEXTURE_1D, 0, imgdata.format, iWidth,
                0, imgdata.format, imgdata.type, image_ub4);
        glTexSubImage1D(GL_TEXTURE_1D, 0, 10,iSubWidth, imgdata.format, imgdata.type, iSubmage_ub4);
        break;
     default:
        break;
     }
   } else {
     glTexImage1D(GL_TEXTURE_1D, 0, imgdata.format, iWidth,
                0, imgdata.format, imgdata.type, image_us);
        glTexSubImage1D(GL_TEXTURE_1D, 0, 10,iSubWidth, imgdata.format, imgdata.type, iSubmage_us);
   }

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   currentCoeff = xequalzero;
   currentGenMode = GL_OBJECT_LINEAR;
   currentPlane = GL_OBJECT_PLANE;
   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
   glTexGenfv(GL_S, currentPlane, currentCoeff);

   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_1D);
   glEnable(GL_TEXTURE_1D);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glBegin(GL_QUADS);
   glVertex3f(-2.25, -1.0, 0.0);
   glVertex3f(-2.25, 1.0, 0.0);
   glVertex3f(-0.25, 1.0, 0.0);
   glVertex3f(-0.25, -1.0, 0.0);
/*
   glTexCoord1f(0.0, 0.0, 1.0); glVertex3f(0.25, -1.0, 0.0);
   glTexCoord1f(0.0, 1.0, 1.0); glVertex3f(0.25, 1.0, 0.0);
   glTexCoord1f(1.0, 1.0, 0.0); glVertex3f(2.25, 1.0, 0.0);
   glTexCoord1f(1.0, 0.0, 0.0); glVertex3f(2.25, -1.0, 0.0);*/
   glEnd();
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -4.0);
}

int main(int argc, char** argv)
{
    string file = "texture3d";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(image); i++) {
            string src_name = get_enum_name(image[i].format);
	    string filename = file + "-" + src_name + ".bmp";
	    LOGIF("[%d]: filename=%s\n", i, filename.c_str());
            renderFrame(image[i]);
        save2bmp(filename.c_str());
	glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
