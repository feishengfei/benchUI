/**
 * @file accum2.c
 * @testpoint glArrayElement glVertexPointer
 *
 */
#include "gl-util.h"
#include "limits.h"
#include "string.h"

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

#define NUM_LIST_TYPES 3
typedef enum {CUBE=0, SQUARE, PUSHPOP} listType;

listType currentList = SQUARE;

GLuint lists[NUM_LIST_TYPES];

GLenum doubleBuffer;

GLboolean multTex = GL_TRUE;
GLboolean immed = GL_FALSE;
GLboolean queryTexobj = GL_TRUE;

#define NUM_TEXTURES 3

GLuint texNames[NUM_TEXTURES];
GLfloat texPriorities[NUM_TEXTURES] = {0.1, 0.2, 0.3};
RGBImageRec *images[NUM_TEXTURES];
char *texFiles[NUM_TEXTURES] = {
	"1.rgb",
	"2.rgb",
	"3.rgb",
};

float *minFilter, *magFilter, *sWrapMode, *tWrapMode;
float decal[] = {GL_DECAL};
float modulate[] = {GL_MODULATE};
float repeat[] = {GL_REPEAT};
float clamp[] = {GL_CLAMP};
float nr[] = {GL_NEAREST};
float ln[] = {GL_LINEAR};
float nr_mipmap_nr[] = {GL_NEAREST_MIPMAP_NEAREST};
float nr_mipmap_ln[] = {GL_NEAREST_MIPMAP_LINEAR};
float ln_mipmap_nr[] = {GL_LINEAR_MIPMAP_NEAREST};
float ln_mipmap_ln[] = {GL_LINEAR_MIPMAP_LINEAR};
GLint sphereMap[] = {GL_SPHERE_MAP};

GLenum doSphere = GL_FALSE;
float xRotation = 0.0, yRotation = 0.0, zTranslate = -3.125;

float c[6][4][3] = {
    {
	{ 1.0, 1.0, -1.0 },
	{ -1.0, 1.0, -1.0 },
	{ -1.0, -1.0, -1.0 },
	{ 1.0, -1.0, -1.0 }
    },
    {
	{ 1.0, 1.0, 1.0 },
	{ 1.0, 1.0, -1.0 },
	{ 1.0, -1.0, -1.0 },
	{ 1.0, -1.0, 1.0 }
    },
    {
	{ -1.0, 1.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 1.0, -1.0, 1.0 },
	{ -1.0, -1.0, 1.0 }
    },
    {
	{ -1.0, 1.0, -1.0 },
	{ -1.0, 1.0, 1.0 },
	{ -1.0, -1.0, 1.0 },
	{ -1.0, -1.0, -1.0 }
    },
    {
	{ -1.0, 1.0, 1.0 },
	{ -1.0, 1.0, -1.0 },
	{ 1.0, 1.0, -1.0 },
	{ 1.0, 1.0, 1.0 }
    },
    {
	{ -1.0, -1.0, -1.0 },
	{ -1.0, -1.0, 1.0 },
	{ 1.0, -1.0, 1.0 },
	{ 1.0, -1.0, -1.0 }
    }
};
static float n[6][3] = {
    { 0.0, 0.0, -1.0 },
    { 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    { -1.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 0.0, -1.0, 0.0 }
};
static float t[6][4][2] = {
    {
	{ 1.1,  1.1 },
	{ -0.1, 1.1 },
	{ -0.1, -0.1 },
	{ 1.1,  -0.1 }
    },
    {
	{ 1.1,  1.1 },
	{ -0.1, 1.1 },
	{ -0.1, -0.1 },
	{ 1.1,  -0.1 }
    },
    {
	{ -0.1,  1.1 },
	{ 1.1, 1.1 },
	{ 1.1, -0.1 },
	{ -0.1,  -0.1 }
    },
    {
	{ 1.1,  1.1 },
	{ -0.1, 1.1 },
	{ -0.1, -0.1 },
	{ 1.1,  -0.1 }
    },
    {
	{ 1.1,  1.1 },
	{ -0.1, 1.1 },
	{ -0.1, -0.1 },
	{ 1.1,  -0.1 }
    },
    {
	{ 1.1,  1.1 },
	{ -0.1, 1.1 },
	{ -0.1, -0.1 },
	{ 1.1,  -0.1 }
    },
};


static void SelectTexture(GLint i)
{
    RGBImageRec *texImage;

	if (i<NUM_TEXTURES) {
	    glBindTexture(GL_TEXTURE_2D, texNames[i]);
	} else {
	    glBindTexture(GL_TEXTURE_2D, 0);
	}
	return;

    if (i >= NUM_TEXTURES) {
	i = NUM_TEXTURES - 1;
    }

    texImage = images[i];

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texImage->sizeX, texImage->sizeY,
		      GL_RGB, GL_UNSIGNED_BYTE, texImage->data);
}

static void DrawCube(void)
{
    GLint i;

    for (i = 0; i < 6; i++) {
	    SelectTexture(i);
	glBegin(GL_POLYGON);
	    glNormal3fv(n[i]); glTexCoord2fv(t[i][0]); glVertex3fv(c[i][0]);
	    glNormal3fv(n[i]); glTexCoord2fv(t[i][1]); glVertex3fv(c[i][1]);
	    glNormal3fv(n[i]); glTexCoord2fv(t[i][2]); glVertex3fv(c[i][2]);
	    glNormal3fv(n[i]); glTexCoord2fv(t[i][3]); glVertex3fv(c[i][3]);
	glEnd();
    }
}

static void BuildCube(void)
{
    GLint i;

    glNewList(lists[CUBE], GL_COMPILE);
    DrawCube();
    glEndList();
}

static void DrawSquare(void)
{

    glBegin(GL_POLYGON);
	glNormal3fv(n[2]); glTexCoord2fv(t[2][0]); glVertex3fv(c[2][0]);
	glNormal3fv(n[2]); glTexCoord2fv(t[2][1]); glVertex3fv(c[2][1]);
	glNormal3fv(n[2]); glTexCoord2fv(t[2][2]); glVertex3fv(c[2][2]);
	glNormal3fv(n[2]); glTexCoord2fv(t[2][3]); glVertex3fv(c[2][3]);
    glEnd();
}

static void DrawSquares(void)
{
    GLint i;
    GLfloat xTranslate = 0.0;

    glTranslatef(-2.0, 0.0, 0.0);
    for (i = 0; i < 3; i++) {
	    SelectTexture(i);
	DrawSquare();
	glTranslatef(2.0, 0.0, 0.0);
    }
}

static void BuildSquare(void)
{
    GLint i;
    GLfloat xTranslate = 0.0;

    glNewList(lists[SQUARE], GL_COMPILE);
    DrawSquares();
    glEndList();
}

static void DoPushPopTest(void)
{
    GLfloat xTranslate = 0.0;

	SelectTexture(1);
    glTranslatef(-4.0, 0.0, 0.0);
    DrawSquare();

    glPushAttrib(GL_TEXTURE_BIT);
	SelectTexture(2);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp);
    glTranslatef(2.0, 0.0, 0.0);
    DrawSquare();

    glPopAttrib();
    glTranslatef(2.0, 0.0, 0.0);
    DrawSquare();

    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp);
    glTranslatef(2.0, 0.0, 0.0);
    DrawSquare();

}

static void BuildPushPopTest(void)
{
    GLfloat xTranslate = 0.0;

    glNewList(lists[PUSHPOP], GL_COMPILE);
    DoPushPopTest();
    glEndList();
}

static void BuildLists(void)
{

    lists[CUBE] = glGenLists(1);
    BuildCube();
    lists[SQUARE] = glGenLists(1);
    BuildSquare();
    lists[PUSHPOP] = glGenLists(1);
    BuildPushPopTest();
}

static void UnBuildLists(void)
{
    int i;

    for (i = 0; i < NUM_LIST_TYPES; i++) {
	glDeleteLists(lists[i], 1);
    }
}

static void Init(void)
{

    doSphere = GL_FALSE;
    xRotation = 0.0;
    yRotation = 0.0;
    zTranslate = -3.125;

    images[0] = rgbImageLoad(texFiles[0]);
    if (images[0] == NULL) {
	printf("Bad texture file.\n");
	exit(1);
    }
	int i;
	for (i = 1; i < NUM_TEXTURES; i++) {
	    images[i] = rgbImageLoad(texFiles[i]);
	    if (images[i] == NULL) {
		printf("Bad texture file.\n");
		exit(1);
	    }
	}

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(NUM_TEXTURES, texNames);
	for (i = 1; i < NUM_TEXTURES; i++) {
	    glBindTexture(GL_TEXTURE_2D, texNames[i]);
	    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, images[i]->sizeX,
			      images[i]->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
			      images[i]->data);
	}
	glBindTexture(GL_TEXTURE_2D, texNames[0]);
	glPrioritizeTextures(NUM_TEXTURES, texNames, texPriorities);
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, images[0]->sizeX, images[0]->sizeY,
		      GL_RGB, GL_UNSIGNED_BYTE, images[0]->data);

    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, decal);
    glEnable(GL_TEXTURE_2D);

    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    BuildLists();

    glClearColor(0.0, 0.0, 0.0, 0.0);

    magFilter = nr;
    minFilter = nr;
    sWrapMode = repeat;
    tWrapMode = repeat;
}

static void UnInit(void)
{
	glDeleteTextures(NUM_TEXTURES, texNames);
    UnBuildLists();
}

static void Reshape(int width, int height)
{

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(145.0, 1.0, 0.01, 1000);
    glMatrixMode(GL_MODELVIEW);
}

static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrapMode);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrapMode);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

    glPushMatrix();

    glTranslatef(0.0, 0.0, zTranslate);
    glRotatef(xRotation, 1, 0, 0);
    glRotatef(yRotation, 0, 1, 0);

    if (immed) { 		
	switch(currentList) {
	    case SQUARE:
		DrawSquares();
		break;
	    case PUSHPOP:
		DoPushPopTest();
		break;
	    case CUBE:
		DrawCube();
		break;
	}
    } else {
	glCallList(lists[currentList]);
    }

    glPopMatrix();

	    GLint name;
	    GLfloat priority;
	    GLboolean isTex, resident, residences[NUM_TEXTURES];

	    glGetIntegerv(GL_TEXTURE_2D_BINDING_EXT, &name);
	    glGetTexParameterfv(GL_TEXTURE_2D, 
				GL_TEXTURE_PRIORITY_EXT, &priority);
	    isTex = glIsTexture(name);
	    resident = glAreTexturesResident(NUM_TEXTURES, 
						texNames, residences);
	    fprintf(stdout, "\tname=%d priority=%f allResident=%d isTex=%d\n",
		    name, priority, resident, isTex);

	glFlush();
}

static char *argList[][2] = {
    {"-sb", "single buffered"},
    {"-db", "double buffered"},
    {"-dr", "direct rendering"},
    {"-ir", "indirect rendering"},
    {"-f filename", "filename for texture"},
    {"-gl13-texobj", "use texture objects"},
    {"-nogl13-texobj", "don't use texture objects"},
    {"-immed", "immediate mode"},
    {"-square", "draw squares"},
    {"-cube", "draw cube"},
    {"-pushpop", "push pop test"},
    {"-nq", "skip query gl13-texobj extension"},
    {"-h", "display this list"},
    {"Press H in app window to get key interpretations", ""},
    {NULL, NULL}
};

static void Args(int argc, char **argv)
{
    GLint i;

    for (i = 1; i < argc; i++) {
	if (strcmp(argv[i], "-flat") == 0) {
	    currentList = SQUARE;
	} else if (strcmp(argv[i], "-immed") == 0) {
	    immed = GL_TRUE;
	} else if (strcmp(argv[i], "-pushpop") == 0) {
	    currentList = PUSHPOP;
	} else if (strcmp(argv[i], "-cube") == 0) {
	    currentList = CUBE;
	}
    }
}

int main(int argc, char** argv)
{
    Args(argc, argv);
    string file = "gl13-texobj";
    GBtest_init(&argc,argv,file,DisplayMode);
    Init ();
    Reshape(WINDOW_W, WINDOW_H);
	    string filename = file + ".bmp";
	    LOGIF(" filename=%s\n", filename.c_str());
            Draw();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
