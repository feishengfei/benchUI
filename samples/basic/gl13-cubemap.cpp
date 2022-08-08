/**
 * @file accum2.c
 * @testpoint glArrayElement glVertexPointer
 *
 */
#include "gl-util.h"
#include "limits.h"

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

#define	imageSize 4
static GLubyte image1[imageSize][imageSize][4];
static GLubyte image2[imageSize][imageSize][4];
static GLubyte image3[imageSize][imageSize][4];
static GLubyte image4[imageSize][imageSize][4];
static GLubyte image5[imageSize][imageSize][4];
static GLubyte image6[imageSize][imageSize][4];

static GLdouble ztrans = 0.0;

void makeImages(void)
{
   int i, j, c;
    
   for (i = 0; i < imageSize; i++) {
      for (j = 0; j < imageSize; j++) {
         c = ((((i&0x1)==0)^((j&0x1))==0))*255;
         image1[i][j][0] = (GLubyte) c;
         image1[i][j][1] = (GLubyte) c;
         image1[i][j][2] = (GLubyte) c;
         image1[i][j][3] = (GLubyte) 255;

         image2[i][j][0] = (GLubyte) c;
         image2[i][j][1] = (GLubyte) c;
         image2[i][j][2] = (GLubyte) 0;
         image2[i][j][3] = (GLubyte) 255;

         image3[i][j][0] = (GLubyte) c;
         image3[i][j][1] = (GLubyte) 0;
         image3[i][j][2] = (GLubyte) c;
         image3[i][j][3] = (GLubyte) 255;

         image4[i][j][0] = (GLubyte) 0;
         image4[i][j][1] = (GLubyte) c;
         image4[i][j][2] = (GLubyte) c;
         image4[i][j][3] = (GLubyte) 255;

         image5[i][j][0] = (GLubyte) 255;
         image5[i][j][1] = (GLubyte) c;
         image5[i][j][2] = (GLubyte) c;
         image5[i][j][3] = (GLubyte) 255;

         image6[i][j][0] = (GLubyte) c;
         image6[i][j][1] = (GLubyte) c;
         image6[i][j][2] = (GLubyte) 255;
         image6[i][j][3] = (GLubyte) 255;
      }
   }
}

void init(void)
{
   GLfloat diffuse[4] = {1.0, 1.0, 1.0, 1.0};

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);

   makeImages();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_R, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT, 0, GL_RGBA, imageSize, 
                imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT, 0, GL_RGBA, imageSize, 
                imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image4);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT, 0, GL_RGBA, imageSize,
                imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT, 0, GL_RGBA, imageSize,
                imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image5);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT, 0, GL_RGBA, imageSize,
                imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image3);
   glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT, 0, GL_RGBA, imageSize,
                imageSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, image6);
   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT);
   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT);
   glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP_EXT); 
   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);
   glEnable(GL_TEXTURE_GEN_R);

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

   glEnable(GL_TEXTURE_CUBE_MAP_EXT);   
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE);
   glMaterialfv (GL_FRONT, GL_DIFFUSE, diffuse);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glPushMatrix ();
   glTranslatef (0.0, 0.0, ztrans);
   glutSolidSphere (5.0, 20, 10);
   glPopMatrix ();
   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 300.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -20.0);
}

int main(int argc, char** argv)
{
    string file = "gl13-cubemap";
    GBtest_init(&argc,argv,file,DisplayMode);
    init ();
    reshape(WINDOW_W, WINDOW_H);
	    string filename = file + ".bmp";
	    LOGIF(" filename=%s\n", filename.c_str());
            display();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
