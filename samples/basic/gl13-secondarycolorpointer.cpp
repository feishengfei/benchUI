/**
 * @file accum2.c
 * @testpoint glArrayElement glVertexPointer
 *
 */
#include "gl-util.h"
#include "limits.h"

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

GLenum factors[] = {
	GL_BYTE,
	GL_UNSIGNED_BYTE,
	GL_SHORT,
	GL_UNSIGNED_SHORT,
	GL_INT,
	GL_UNSIGNED_INT,
	GL_FLOAT,
	GL_DOUBLE
};

/*  Create checkerboard textures  */
#define checkImageWidth 64
#define checkImageHeight 64
#define subImageWidth 16
#define subImageHeight 16
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLubyte subImage[subImageHeight][subImageWidth][4];

static GLuint texName;

void makeCheckImages(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
   for (i = 0; i < subImageHeight; i++) {
      for (j = 0; j < subImageWidth; j++) {
         c = ((((i&0x4)==0)^((j&0x4))==0))*255;
         subImage[i][j][0] = (GLubyte) c;
         subImage[i][j][1] = (GLubyte) 0;
         subImage[i][j][2] = (GLubyte) 0;
         subImage[i][j][3] = (GLubyte) 255;
      }
   }
}

void init(void)
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
}

void getdata() 
{
GLvoid **param;

    GL_CHECK(glGetPointerv(GL_SECONDARY_COLOR_ARRAY, param));
    LOGIF("GetPointerv(GL_SECONDARY_COLOR_ARRAY): %x\n", *param);
}

void display(void)
{
   GLfloat secondcolor[] = {
	0.5, 0.0, 0.0, 0.0,
	0.0, 0.5, 0.0, 0.0,
	0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.0, 0.0,
	0.5, 0.0, 0.5, 0.0,
	0.0, 0.5, 0.5, 0.0,
	0.5, 0.5, 0.5, 0.0,
	0.0, 0.0, 0.0, 0.0
   };
   GLfloat texcoord[] = {
	0.0, 0.0,
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0,
	0.0, 0.0,
	0.0, 1.0,
	1.0, 1.0,
	1.0, 0.0
   };
   GLfloat vertex[] = {
	-2.0, -1.0, 0.0,
	-2.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, -1.0, 0.0,
	1.0, -1.0, 0.0,
	1.0, 1.0, 0.0,
	2.41421, 1.0, -1.41421,
	2.41421, -1.0, -1.41421
   };
   int num  = ARRAY_NUM(secondcolor);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, texName);
   
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glEnableClientState(GL_SECONDARY_COLOR_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, vertex));
    GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, texcoord));
switch(type) {
    case GL_DOUBLE:
    {
    GLdouble temp[num];
    for(int i=0; i<num; i++) {
	temp[i] = (GLdouble)secondcolor[i];
    }
    GL_CHECK(glSecondaryColorPointer(4, GL_DOUBLE, 0, temp));
    break;
    }
    case GL_UNSIGNED_INT:
    {
    GLuint temp[num];
    for(int i=0; i<num; i++) {
	temp[i] = (GLuint)(secondcolor[i]*UINT_MAX);
    }
    GL_CHECK(glSecondaryColorPointer(4, GL_UNSIGNED_INT, 0, temp));
    break;
    }
    case GL_UNSIGNED_INT:
    {
    GLuint temp[num];
    for(int i=0; i<num; i++) {
	temp[i] = (GLuint)(secondcolor[i]*UINT_MAX);
    }
    GL_CHECK(glSecondaryColorPointer(4, GL_UNSIGNED_INT, 0, temp));
    break;
    }
    case GL_INT:
    {
    GLint temp[num];
    for(int i=0; i<num; i++) {
	temp[i] = (GLuint)(secondcolor[i]*INT_MAX);
    }
    GL_CHECK(glSecondaryColorPointer(4, GL_INT, 0, temp));
    break;
    }
    case GL_UNSIGNED_SHORT:
    {
    GLushort temp[num];
    for(int i=0; i<num; i++) {
	temp[i] = (GLuint)(secondcolor[i]*USHRT_MAX);
    }
    GL_CHECK(glSecondaryColorPointer(4, GL_UNSIGNED_SHORT, 0, temp));
    break;
    }
    case GL_SHORT:
    {
    GLshort temp[num];
    for(int i=0; i<num; i++) {
	temp[i] = (GLuint)(secondcolor[i]*SHRT_MAX);
    }
    GL_CHECK(glSecondaryColorPointer(4, GL_SHORT, 0, temp));
    break;
    }
    case GL_UNSIGNED_BYTE:
    {
    GLubyte temp[num];
    for(int i=0; i<num; i++) {
	temp[i] = (GLuint)(secondcolor[i]*256);
    }
    GL_CHECK(glSecondaryColorPointer(4, GL_UNSIGNED_BYTE, 0, temp));
    break;
    }
    case GL_BYTE:
    {
    GLbyte temp[num];
    for(int i=0; i<num; i++) {
	temp[i] = (GLuint)(secondcolor[i]*128);
    }
    GL_CHECK(glSecondaryColorPointer(4, GL_BYTE, 0, temp));
    break;
    }
    default:
    GL_CHECK(glSecondaryColorPointer(4, GL_FLOAT, 0, secondcolor));
    break;
}
   glBegin(GL_QUADS);
        glArrayElement(0);
        glArrayElement(1);
        glArrayElement(2);
        glArrayElement(3);
        glArrayElement(4);
        glArrayElement(5);
        glArrayElement(6);
        glArrayElement(7);
   glEnd();
   glFlush();
getdata();
   glDisable(GL_TEXTURE_2D);
    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glDisableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glDisableClientState(GL_SECONDARY_COLOR_ARRAY));
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -3.6);
}

int main(int argc, char** argv)
{
    string file = "secondarycolor";
    GBtest_init(&argc,argv,file,DisplayMode);
    init ();
    reshape(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
            string factor_name = get_enum_name(factors[i]);
	    string filename = file + "-" + factor_name + ".bmp";
	    LOGIF(" filename=%s\n", filename.c_str());
            renderFrame(factors[i]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
