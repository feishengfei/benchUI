/**
 * @file gl13-interleavedarrays.cpp
 * @testpoint glInterleavedArrays
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

typedef struct
{
    GLubyte  r,g,b,a;
    GLfloat x, y, z;
} Vertex_C4UB_V3F;

typedef struct
{
    GLubyte  r,g,b,a;
    GLfloat x, y;
} Vertex_C4UB_V2F;

typedef struct
{
    GLfloat s, t;
    GLubyte r,g,b,a;
    GLfloat x, y, z;
} Vertex_T2F_C4UB_V3F;

static const GLfloat vertices_C3F_V3F [] = {1.0, 0.0, 0.0,  2.0, 0.0, 0.0,
				0.0, 0.0, 1.0,  -2.0, 0.0, 0.0};
static const GLfloat vertices_V3F [] = {-2.0, -2.0, 0.0,  2.0, -2.0, 0.0};
static const GLfloat vertices_V2F [] = {-2.0, -3.0,  2.0, -3.0};
Vertex_C4UB_V2F vertices_C4UB_V2F[] = {255,0,0,0, -2.0,-1.0, 255,255,0,0, 2.0,-1.0};
Vertex_C4UB_V3F vertices_C4UB_V3F[] = {0,0,255,0, -2.0,1.0,0.0, 255,0,255,0, 2.0,1.0,0.0};
static const GLfloat vertices_N3F_V3F[] = {0.0,0.0,1.0, -2.0,0.0,0.0,
					0.0,0.0,1.0, 2.0,0.0,0.0,
					0.0,0.0,1.0, 0.0,2.0,0.0,};
static const GLfloat vertices_C4F_N3F_V3F[] = {0.0,0.0,1.0,0.0, 0.0,0.0,1.0, -2.0,0.0,0.0,
					0.0,1.0,0.0,0.0, 0.0,0.0,1.0, 2.0,0.0,0.0,
					1.0,0.0,0.0,0.0, 0.0,0.0,1.0, 0.0,2.0,0.0,};
static const GLfloat vertices_T2F_V3F[] = {0.0,1.0, -2.0,2.0,0.0,
					0.0,0.0,  -2.0,-2.0,0.0,
					1.0,0.0,  2.0,-2.0,0.0,
					1.0,1.0,  2.0,2.0,0.0,};
static const GLfloat vertices_T4F_V4F[] = {0.0,1.0,0.0,0.0, -2.0,2.0,0.0,0.0,
					0.0,0.0,0.0,0.0, -2.0,-2.0,0.0,0.0,
					1.0,0.0,0.0,0.0, 2.0,-2.0,0.0,0.0,
					1.0,1.0,0.0,0.0, 2.0,2.0,0.0,0.0,};
Vertex_T2F_C4UB_V3F vertices_T2F_C4UB_V3F[] = {0.0,1.0, 0,0,255,0, -2.0,2.0,0.0,
					0.0,0.0, 0,255,0,0, -2.0,-2.0,0.0,
					1.0,0.0, 255,0,0,0, 2.0,-2.0,0.0,
					1.0,1.0, 255,0,255,0, 2.0,2.0,0.0,};
static const GLfloat vertices_T2F_C3F_V3F[] = {0.0,1.0, 0.0,0.0,1.0, -2.0,2.0,0.0,
					0.0,0.0, 0.0,1.0,0.0, -2.0,-2.0,0.0,
					1.0,0.0, 1.0,0.0,0.0, 2.0,-2.0,0.0,
					1.0,1.0, 1.0,0.0,1.0, 2.0,2.0,0.0,};
static const GLfloat vertices_T2F_N3F_V3F[] = {0.0,1.0, 0.0,0.0,1.0, -2.0,2.0,0.0,
					0.0,0.0, 0.0,0.0,1.0, -2.0,-2.0,0.0,
					1.0,0.0, 0.0,0.0,1.0, 2.0,-2.0,0.0,
					1.0,1.0, 0.0,0.0,1.0, 2.0,2.0,0.0,};
static const GLfloat vertices_T2F_C4F_N3F_V3F[] = {0.0,1.0, 0.0,0.0,1.0,0.0, 0.0,0.0,1.0, -2.0,2.0,0.0,
					0.0,0.0, 0.0,1.0,1.0,0.0, 0.0,0.0,1.0, -2.0,-2.0,0.0,
					1.0,0.0, 1.0,0.0,1.0,0.0, 0.0,0.0,1.0, 2.0,-2.0,0.0,
					1.0,1.0, 0.0,1.0,0.0,0.0, 0.0,0.0,1.0, 2.0,2.0,0.0,};
static const GLfloat vertices_T4F_C4F_N3F_V4F[] = {0.0,1.0,0.0,0.0, 0.0,0.0,1.0,0.0, 0.0,0.0,1.0, -2.0,2.0,0.0,0.0,
					0.0,0.0,0.0,0.0, 0.0,1.0,1.0,0.0, 0.0,0.0,1.0, -2.0,-2.0,0.0,0.0,
					1.0,0.0,0.0,0.0, 1.0,0.0,1.0,0.0, 0.0,0.0,1.0, 2.0,-2.0,0.0,0.0,
					1.0,1.0,0.0,0.0, 0.0,1.0,0.0,0.0, 0.0,0.0,1.0, 2.0,2.0,0.0,0.0,};

typedef struct
{
    GLenum type;
    GLenum mode;
    GLint num;
    GLboolean color;
    GLboolean normal;
    GLboolean texture;
    void *data;
} interleave_type_t;

interleave_type_t factors[] = {
	{GL_V2F, GL_LINES, 2, GL_FALSE, GL_FALSE, GL_FALSE, (void *)vertices_V2F},
	{GL_V3F, GL_LINES, 2, GL_FALSE, GL_FALSE, GL_FALSE, (void *)vertices_V3F},
	{GL_C4UB_V2F, GL_LINES, 2, GL_TRUE, GL_FALSE, GL_FALSE, (void *)vertices_C4UB_V2F},
	{GL_C4UB_V3F, GL_LINES, 2, GL_TRUE, GL_FALSE, GL_FALSE, (void *)vertices_C4UB_V3F},
	{GL_C3F_V3F, GL_LINES, 2, GL_TRUE, GL_FALSE, GL_FALSE, (void *)vertices_C3F_V3F},
	{GL_N3F_V3F, GL_TRIANGLES, 3, GL_FALSE, GL_TRUE, GL_FALSE, (void *)vertices_N3F_V3F},
	{GL_C4F_N3F_V3F, GL_TRIANGLES, 3, GL_TRUE, GL_TRUE, GL_FALSE, (void *)vertices_C4F_N3F_V3F},
	{GL_T2F_V3F, GL_QUADS, 4, GL_FALSE, GL_FALSE, GL_TRUE, (void *)vertices_T2F_V3F},
	{GL_T4F_V4F, GL_QUADS, 4, GL_FALSE, GL_FALSE, GL_TRUE, (void *)vertices_T4F_V4F},
	{GL_T2F_C4UB_V3F, GL_QUADS, 4, GL_TRUE, GL_FALSE, GL_TRUE, (void *)vertices_T2F_C4UB_V3F},
	{GL_T2F_C3F_V3F, GL_QUADS, 4, GL_TRUE, GL_FALSE, GL_TRUE, (void *)vertices_T2F_C3F_V3F},
	{GL_T2F_N3F_V3F, GL_QUADS, 4, GL_FALSE, GL_TRUE, GL_TRUE, (void *)vertices_T2F_N3F_V3F},
	{GL_T2F_C4F_N3F_V3F, GL_QUADS, 4, GL_TRUE, GL_TRUE, GL_TRUE, (void *)vertices_T2F_C4F_N3F_V3F},
	{GL_T4F_C4F_N3F_V4F, GL_QUADS, 4, GL_TRUE, GL_TRUE, GL_TRUE, (void *)vertices_T4F_C4F_N3F_V4F},
};

#define checkImageWidth 64
#define checkImageHeight 64
GLubyte image_ub4[checkImageHeight][checkImageWidth][4];

static GLuint texName;

void makeCheckImages(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
            c = (((i&0x8)==0)^((j&0x8)==0))*255;
            image_ub4[i][j][0] = (GLubyte) c;
            image_ub4[i][j][1] = (GLubyte) 0;
            image_ub4[i][j][2] = (GLubyte) 255;
            image_ub4[i][j][3] = (GLubyte) 255;
      }
   }
}
/*
void gendata(GLint n) {
	int i=0;

	switch(factor[n].type)
	case GL_V2F:
		vertices_V2F = (GLfloat *)malloc(2*NUM*sizeof(GLfloat));
		for(i=0; i<NUM; i++)
			vertices_V2F[i*
}*/

bool setupGraphics(int w, int h)
{
    glViewport(0, 0, w, h);
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5,5,-5,5,5,15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0,0,10,0,0,0,0,1,0);
    return true;
}

void setupLight(void)
{
	GLfloat li_ambient[] = { 0.0f, 0.2f, 1.0f, 1.0f };
	GLfloat li_diffuse[] = { 0.8f, 0.5f, 0.2f, 1.0f };
	GLfloat li_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_ambient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_position[] = { -2.0f, 2.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, li_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, li_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,li_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION,light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void setupTexture(void)
{
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
   makeCheckImages();

   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, image_ub4);
   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texName);
}

void deleteLight(void)
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

void deleteTexture(void)
{
    glDeleteTextures(1, &texName);
    GL_CHECK(glDisable(GL_TEXTURE_2D));
}

void renderFrame(GLint n)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0,0.5,0.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	if(factors[n].color)
		glEnableClientState(GL_COLOR_ARRAY);
	if(factors[n].normal) {
		setupLight();
		glEnableClientState(GL_NORMAL_ARRAY);
	}
	if(factors[n].texture) {
		setupTexture();
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	glInterleavedArrays(factors[n].type, 0, factors[n].data);
	glDrawArrays(factors[n].mode, 0, factors[n].num);

	GL_CHECK(glFlush());
	if(factors[n].color)
		glDisableClientState(GL_COLOR_ARRAY);
	if(factors[n].normal) {
		deleteLight();
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	if(factors[n].texture) {
		deleteTexture();
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

int main(int argc, char** argv)
{
    string file = "gl13-interleavedarrays";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
            string src_name = get_enum_name(factors[i].type);
	    string filename = file + "-" + src_name + ".bmp";
	    LOGIF("[%d]: filename=%s\n", i, filename.c_str());
            renderFrame(i);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
