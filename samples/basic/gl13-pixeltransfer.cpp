/**
 * @file gl13-pixeltransfer.cpp
 * @testpoint glPixeltransfer
 *
 */
#include "gl-util.h"
unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGB;
int n;
int m;
float s;

GLuint *image;
typedef struct _SplatInfo {
  int x, y;
  GLboolean alphaTest;
  GLfloat xScale, yScale;
  GLfloat scale[4];
  GLfloat bias[4];
} SplatInfo;

SplatInfo splat = {
  0, 0,
  GL_TRUE,
  1.0, 1.0,
  1.0, 1.0, 1.0,
  1.0, 1.0, 1.0,
};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);
		glVertex2i(0,0);
		glTexCoord2f(0.0,1.0);
		glVertex2i(0,m-1);
		glTexCoord2f(1.0,1.0);
		glVertex2i(n-1,m-1);
		glTexCoord2f(1.0,0.0);
		glVertex2i(n-1,0);
	glEnd();
	glFlush();
}

void readppm()
{
	FILE *fd;
	int  k, nm;
	char c;
	int i;
	char b[100];
	int red, green, blue;

	string file = (string)PICTURE_PATH + "robot2.ppm";
	fd = fopen(file.c_str(), "r");
	fscanf(fd,"%[^\n] ",b);
	if(b[0]!='P'|| b[1] != '3')
	{
		printf("%s is not a PPM file!\n", b); 
		exit(0);
	}
	printf("%s is a PPM file\n",b);
	fscanf(fd, "%c",&c);
	while(c == '#') 
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n",b);
		fscanf(fd, "%c",&c);
	}
	ungetc(c,fd); 
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n",n,m,k);

	nm = n*m;

	image=(GLuint *)malloc(3*sizeof(GLuint)*nm);
	s=255./k;
	for(i=0;i<nm;i++) 
	{
		fscanf(fd,"%d %d %d",&red, &green, &blue );
		image[3*nm-3*i-3]=red;
		image[3*nm-3*i-2]=green;
		image[3*nm-3*i-1]=blue;
	}
	printf("read image\n");
}

void setupGraphics(int h, int w)
{
	readppm();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat) n, 0.0, (GLfloat) m);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,h,w);
}


void renderFrame(GLboolean boolfactor)
{
    glPixelTransferf(GL_MAP_COLOR, boolfactor);
    glPixelTransferf(GL_MAP_STENCIL, boolfactor);
    glPixelTransferf(GL_INDEX_SHIFT, 0);
    glPixelTransferf(GL_INDEX_OFFSET, 0);
	glPixelTransferf(GL_RED_SCALE, s);
	glPixelTransferf(GL_GREEN_SCALE, s);
	glPixelTransferf(GL_BLUE_SCALE, s);
    glPixelTransferf(GL_ALPHA_SCALE, s);
	glPixelTransferf(GL_DEPTH_SCALE, 0.5);
	glPixelTransferf(GL_RED_BIAS, splat.bias[0]);
	glPixelTransferf(GL_GREEN_BIAS, splat.bias[1]);
	glPixelTransferf(GL_BLUE_BIAS, splat.bias[2]);
	glPixelTransferf(GL_ALPHA_BIAS, splat.bias[3]);
	glPixelTransferf(GL_DEPTH_BIAS, 0.5);
	glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D,0,3,n,m,0,GL_RGB,GL_UNSIGNED_INT, image);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0,1.0,1.0);
	display();
	free(image);
}

int main(int argc, char** argv)
{
    string file = "gl13-pixeltransfer";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(bool_factors); i++) {
            string src_name = GET_BOOL(bool_factors[i]);
	    string filename = file + "-" + src_name + ".bmp";
	    LOGIF("[%d]: filename=%s\n", i, filename.c_str());
            renderFrame(bool_factors[i]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
