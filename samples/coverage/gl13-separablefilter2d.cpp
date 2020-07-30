/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"
#include <cstring>
#include "limits.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLfloat horizontal[3] = { -0.5, 1.0, -0.5 };

GLfloat vertical[3] = { -0.5, 1.0, -0.5 };

struct type {
	GLenum type;
	GLenum format;
	GLenum internalfmt;
} factors[] = {
	{ GL_UNSIGNED_BYTE, 	GL_RGBA, 	GL_RGBA2 },//0
	{ GL_UNSIGNED_SHORT, 	GL_RGB, 	GL_RGB10 },//1
	{ GL_UNSIGNED_SHORT, 	GL_RGB, 	GL_RGB12 },//2
	{ GL_UNSIGNED_SHORT, 	GL_RGBA, 	GL_RGBA12 },//3
	{ GL_UNSIGNED_SHORT, 	GL_RGB, 	GL_RGB16 },//4
	{ GL_UNSIGNED_SHORT, 	GL_RGBA, 	GL_RGBA16 },//5
	{ GL_UNSIGNED_INT, 	GL_GREEN, 	GL_INTENSITY16 },//6
	{ GL_BYTE, 		GL_ALPHA, 	GL_ALPHA },//
	{ GL_SHORT, 		GL_RED, 	GL_INTENSITY },//
	{ GL_FLOAT, 		GL_LUMINANCE, 	GL_LUMINANCE },  //
	{ GL_UNSIGNED_BYTE_3_3_2, 	GL_RGB, 	GL_R3_G3_B2 },//
	{ GL_UNSIGNED_BYTE_2_3_3_REV, 	GL_BGR, 	GL_RGB },//
	{ GL_UNSIGNED_SHORT_5_6_5, GL_RGB, GL_RGB5 },//
	{ GL_UNSIGNED_SHORT_5_6_5_REV, GL_BGR, GL_RGB },//
	{ GL_UNSIGNED_SHORT_4_4_4_4, GL_RGBA, GL_RGBA4 },//
	{ GL_UNSIGNED_SHORT_4_4_4_4, GL_RGB, GL_RGB4 },//
	{ GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_BGRA, GL_RGBA },//
	{ GL_UNSIGNED_SHORT_5_5_5_1, GL_RGBA, GL_RGB5_A1 },//
	{ GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_BGRA, GL_RGBA },//
	{ GL_UNSIGNED_INT_8_8_8_8, GL_RGBA, GL_RGBA8 },//
	{ GL_UNSIGNED_INT_8_8_8_8, GL_RGB, GL_RGB8 },//
	{ GL_UNSIGNED_INT_8_8_8_8_REV, GL_BGRA, GL_RGBA },//
	{ GL_UNSIGNED_INT_10_10_10_2, GL_RGBA, GL_RGB10_A2 },//
	{ GL_UNSIGNED_INT_2_10_10_10_REV, GL_BGRA, GL_RGBA },//
//	GL_BITMAP
};
/*	Create checkerboard image	*/
#define	checkImageWidth 128
#define	checkImageHeight 128
GLubyte checkImage[checkImageHeight][checkImageWidth][4];

static GLdouble zoomFactor = 1.0;
static GLint height;
void *image;

void makeCheckImage(GLenum internalformat, GLenum format, GLenum type)
{
   int i, j, c, k, cnt=0;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) (255 - c);
         checkImage[i][j][2] = (GLubyte) 0;
         checkImage[i][j][3] = (GLubyte) (i*255/checkImageHeight);
      }
   }

   switch (type) {
      case GL_UNSIGNED_BYTE: 
         image = (GLubyte *)malloc(checkImageWidth*checkImageHeight*4*sizeof(GLubyte));
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
                     for (k = 0; k < 4; k++) {
                        *((GLubyte *)image+cnt) = ((checkImage[i][j][k]>>6) & 0x03);
                        cnt++;
                     }
/*               *((GLubyte *)image+cnt) = (checkImage[i][j][0] & 0xc0) | 
					 ((checkImage[i][j][1]>>2) & 0x30) | 
					 ((checkImage[i][j][2]>>4) & 0x0c) | 
					 ((checkImage[i][j][3]>>6) & 0x03);
               cnt++;*/
            }
         }
         break;
      case GL_UNSIGNED_SHORT:
         switch(internalformat) {
            case GL_RGB10:
            case GL_RGB12:
            case GL_RGB16:
               image = (GLushort *)malloc(sizeof(GLushort)*checkImageWidth*checkImageHeight*3);
               cnt = 0;
               for (i = 0; i < checkImageHeight; i++) {
                  for (j = 0; j < checkImageWidth; j++) {
                     for (k = 0; k < 3; k++) {
                        *((GLushort *)image+cnt) = (GLushort)(USHRT_MAX*checkImage[i][j][k]/255);
                        cnt++;
                     }
                  }
               }
            break;
            case GL_RGBA12:
            case GL_RGBA16:
               image = (GLushort *)malloc(sizeof(GLushort)*checkImageWidth*checkImageHeight*4);
               cnt = 0;
               for (i = 0; i < checkImageHeight; i++) {
                  for (j = 0; j < checkImageWidth; j++) {
                     for (k = 0; k < 4; k++) {
                        *((GLushort *)image+cnt) = (GLushort)(USHRT_MAX*checkImage[i][j][k]/255);
                        cnt++;
                     }
                  }
               }
            break;
            default:
            break;
         }
      case GL_UNSIGNED_INT:
         image = (GLuint *)malloc(sizeof(GLuint)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
                  *((GLuint *)image+cnt) = (((GLuint)(checkImage[i][j][1]))*UINT_MAX/256);
                  cnt++;
            }
         }
         break;
      case GL_BYTE:
         image = (GLbyte *)malloc(sizeof(GLbyte)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLbyte *)image+cnt) = (GLbyte)(checkImage[i][j][3] - 128);
               cnt++;
            }
         }
         break;
      case GL_SHORT:
         image = (GLshort *)malloc(sizeof(GLshort)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLshort *)image+cnt) = (GLshort) SHRT_MAX*(checkImage[i][j][0] - 128)/128;
               cnt++;
            }
         }
         break;
      case GL_INT:
         image = (GLint *)malloc(sizeof(GLint)*checkImageWidth*checkImageHeight*3);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               for (k = 0; k < 3; k++) {
                  *((GLint *)image+cnt) = (GLint) INT_MAX*(checkImage[i][j][k] - 128)/128;
                  cnt++;
               }
            }
         }
         break;
      case GL_FLOAT:
         image = (GLfloat *)malloc(sizeof(GLfloat)*checkImageWidth*checkImageHeight*3);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               for (k = 0; k < 3; k++) {
                  *((GLfloat *)image+cnt) = (GLfloat) (checkImage[i][j][k] - 128)/128;
                  cnt++;
               }
            }
         }
         break;
//      case GL_BITMAP:
//         break;
      case GL_UNSIGNED_BYTE_3_3_2:
         image = (GLubyte *)malloc(sizeof(GLubyte)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLubyte *)image+cnt) = ((checkImage[i][j][0] & 0xe0) |
				((checkImage[i][j][1] >> 3)&0x1c) |
				((checkImage[i][j][2] >> 6)&0x03));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_BYTE_2_3_3_REV:
         image = (GLubyte *)malloc(sizeof(GLubyte)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLubyte *)image+cnt) = ((checkImage[i][j][2] & 0xc0) |
				((checkImage[i][j][1] >> 2)&0x38) |
				((checkImage[i][j][0] >> 5)&0x07));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_SHORT_5_6_5:
         image = (GLushort *)malloc(sizeof(GLushort)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLushort *)image+cnt) = ((((GLushort)checkImage[i][j][0] << 8)&0xf800) |
				(((GLushort)checkImage[i][j][1] << 3)&0x07e0) |
				(((GLushort)checkImage[i][j][2] >> 3)&0x001f));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_SHORT_5_6_5_REV:
         image = (GLushort *)malloc(sizeof(GLushort)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLushort *)image+cnt) = ((((GLushort)checkImage[i][j][2] << 8)&0xf800) |
				(((GLushort)checkImage[i][j][1] << 3)&0x07e0) |
				(((GLushort)checkImage[i][j][0] >> 3)&0x001f));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_SHORT_4_4_4_4:
         image = (GLushort *)malloc(sizeof(GLushort)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLushort *)image+cnt) = ((((GLushort)checkImage[i][j][0] << 8)&0xF000) |
				(((GLushort)checkImage[i][j][1] << 4)&0x0F00) |
				((GLushort)checkImage[i][j][2] & 0x00F0) |
				(((GLushort)checkImage[i][j][3] >> 4)&0x000F));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_SHORT_4_4_4_4_REV:
         image = (GLushort *)malloc(sizeof(GLushort)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLushort *)image+cnt) = ((((GLushort)checkImage[i][j][3] << 8)&0xF000) |
				(((GLushort)checkImage[i][j][2] << 4)&0x0F00) |
				((GLushort)checkImage[i][j][1]&0x00F0) |
				(((GLushort)checkImage[i][j][0] >> 4)&0x000F));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_SHORT_5_5_5_1:
         image = (GLushort *)malloc(sizeof(GLushort)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLushort *)image+cnt) = ((((GLushort)checkImage[i][j][0] << 8)&0xf100) |
				(((GLushort)checkImage[i][j][1] << 3)&0x07c0) |
				(((GLushort)checkImage[i][j][2] >> 2)&0x003e) |
				(((GLushort)checkImage[i][j][3] >> 7)&0x0001));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_SHORT_1_5_5_5_REV:
         image = (GLushort *)malloc(sizeof(GLushort)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLushort *)image+cnt) = ((((GLushort)checkImage[i][j][3] << 8)&0x8000) |
				(((GLushort)checkImage[i][j][2] << 7)&0x7c00) |
				(((GLushort)checkImage[i][j][1] << 2)&0x03e0) |
				(((GLushort)checkImage[i][j][0] >> 3)&0x001F));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_INT_8_8_8_8:
         image = (GLuint *)malloc(sizeof(GLuint)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLuint *)image+cnt) = ((((GLuint)checkImage[i][j][0] << 24)&0xff000000) |
				(((GLuint)checkImage[i][j][1] << 16)&0x00ff0000) |
				(((GLuint)checkImage[i][j][2] << 8)&0x0000ff00) |
				(((GLuint)checkImage[i][j][3])&0x000000ff) );
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_INT_8_8_8_8_REV:
         image = (GLuint *)malloc(sizeof(GLuint)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLuint *)image+cnt) = ((((GLuint)checkImage[i][j][3] << 24)&0xff000000) |
				(((GLuint)checkImage[i][j][2] << 16)&0x00ff0000) |
				(((GLuint)checkImage[i][j][1] << 8)&0x0000ff00) |
				(((GLuint)checkImage[i][j][0]) & 0x000000ff));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_INT_10_10_10_2:
         image = (GLuint *)malloc(sizeof(GLuint)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLuint *)image+cnt) =  (((((GLuint)(1024*checkImage[i][j][0]/255)) << 22)&0xffc00000) |
				((((GLuint)(1024*checkImage[i][j][1]/255)) << 22)&0x03ff000) |
				((((GLuint)(1024*checkImage[i][j][2]/255)) << 22)&0x0000ffc) |
				(((GLuint)checkImage[i][j][3] >> 6)&0x00000003));
               cnt++;
            }
         }
         break;
      case GL_UNSIGNED_INT_2_10_10_10_REV:
         image = (GLuint *)malloc(sizeof(GLuint)*checkImageWidth*checkImageHeight);
         cnt = 0;
         for (i = 0; i < checkImageHeight; i++) {
            for (j = 0; j < checkImageWidth; j++) {
               *((GLuint *)image+cnt) =  (((GLuint)checkImage[i][j][3] << 30) & 0xC0000000) |
				((((GLuint)(1024*checkImage[i][j][2]/255)) << 22) & 0x3ff00000) |
				((((GLuint)(1024*checkImage[i][j][1]/255)) << 22) & 0x000ffc00) |
				((((GLuint)(1024*checkImage[i][j][0]/255)) << 22) & 0x000003ff);
               cnt++;
            }
         }
         break;
      default:
	 break;
    }
}

void getdata(int num)
{
	void *row;
	void *column;
	void *span;
	GLint parami;
	GLfloat paramf[4];

	glGetConvolutionParameteriv(GL_SEPARABLE_2, GL_CONVOLUTION_BORDER_MODE, &parami);
	LOGIF("GetConvolutionParameteriv(GL_CONVOLUTION_BORDER_MODE)=%d\n",parami);
	glGetConvolutionParameterfv(GL_SEPARABLE_2, GL_CONVOLUTION_BORDER_COLOR, paramf);
	LOGIF("GetConvolutionParameterfv(GL_CONVOLUTION_BORDER_COLOR)=%f %f %f %f\n",paramf[0],paramf[1],paramf[2],paramf[3]);
	glGetConvolutionParameterfv(GL_SEPARABLE_2, GL_CONVOLUTION_FILTER_SCALE, paramf);
	LOGIF("GetConvolutionParameterfv(GL_CONVOLUTION_FILTER_SCALE)=%f %f %f %f\n",paramf[0],paramf[1],paramf[2],paramf[3]);
	glGetConvolutionParameterfv(GL_SEPARABLE_2, GL_CONVOLUTION_FILTER_BIAS, parami);
	LOGIF("GetConvolutionParameterfv(GL_CONVOLUTION_FILTER_BIAS)=%f %f %f %f\n",paramf[0],paramf[1],paramf[2],paramf[3]);
	glGetConvolutionParameteriv(GL_SEPARABLE_2, GL_CONVOLUTION_FORMAT, &parami);
	LOGIF("GetConvolutionParameteriv(GL_CONVOLUTION_FORMAT)=%d\n",parami);
	glGetConvolutionParameterfv(GL_SEPARABLE_2, GL_CONVOLUTION_WIDTH, paramf);
	LOGIF("GetConvolutionParameterfv(GL_CONVOLUTION_WIDTH)=%f\n",paramf[0]);
	glGetConvolutionParameterfv(GL_SEPARABLE_2, GL_CONVOLUTION_HEIGHT, paramf);
	LOGIF("GetConvolutionParameterfv(GL_CONVOLUTION_HEIGHT)=%f\n",paramf[0]);
	glGetConvolutionParameterfv(GL_SEPARABLE_2, GL_MAX_CONVOLUTION_WIDTH, paramf);
	LOGIF("GetConvolutionParameterfv(GL_MAX_CONVOLUTION_WIDTH)=%f\n",paramf[0]);
	glGetConvolutionParameterfv(GL_SEPARABLE_2, GL_MAX_CONVOLUTION_HEIGHT, paramf);
	LOGIF("GetConvolutionParameterfv(GL_MAX_CONVOLUTION_HEIGHT)=%f\n",paramf[0]);
	glGetSeparableFilter(GL_SEPARABLE_2D, factors[num].format, factors[num].type, row, column, span);
}

void display(int num)
{    
   GLfloat color[4] = {0.1, 0.8, 0.1, 0.3};
   GLfloat scale[4] = {0.5, 0.5, 0.5, 0.5};
   GLfloat bias[4] = {0.5, 0.5, 0.5, 0.5};

   glClearColor (0.0, 0.0, 0.0, 0.0);
   makeCheckImage(factors[num].internalfmt, factors[num].format, factors[num].type);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   printf("Using the horizontal filter\n");
   glSeparableFilter2D(GL_SEPARABLE_2D, factors[num].internalfmt, 3, 3, factors[num].format, factors[num].type, horizontal, vertical);
   glEnable(GL_SEPARABLE_2D);
   glConvolutionParameteri(GL_SEPARABLE_2, GL_CONVOLUTION_BORDER_MODE, GL_REDUCE);
   glConvolutionParameteri(GL_SEPARABLE_2, GL_CONVOLUTION_BORDER_MODE, GL_CONSTANT_BORDER);
   glConvolutionParameteri(GL_SEPARABLE_2, GL_CONVOLUTION_BORDER_MODE, GL_REPLICATE_BORDER);
   glConvolutionParameterfv(GL_SEPARABLE_2, GL_CONVOLUTION_BORDER_COLOR, color);
   glConvolutionParameterfv(GL_SEPARABLE_2, GL_CONVOLUTION_FILTER_SCALE, scale);
   glConvolutionParameterfv(GL_SEPARABLE_2, GL_CONVOLUTION_FILTER_BIAS, bias);
   glClear(GL_COLOR_BUFFER_BIT);
   glRasterPos2i(20, 20);
   glDrawPixels(checkImageWidth, checkImageHeight, factors[num].format, factors[num].type, image);
   glFlush();
   getdata(num);
   if(image != NULL)
      free(image);
   glDisable(GL_CONVOLUTION_2D);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   height = (GLint) h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
    string file = "convolution2d";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
	char ss[2];
	sprintf(ss, "%d", i);
        string filename = file + "-" + ss + ".bmp";
        printf("[%d] filename=%s\n", i, filename.c_str());
        display(i);
        save2bmp(filename.c_str());
	glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
