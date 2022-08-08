/**
 * @file accum2.c
 * @testpoint glColor glVertex
 *
 */
#include "gl-util.h"
#include "limits.h"

GLenum factors[] = {
	GL_BYTE,
	GL_SHORT,
	GL_INT,
	GL_FLOAT,
	GL_DOUBLE
};
GLfloat ambient[4] = {0.1745, 0.11175, 0.01175, 1.0};	
GLfloat diffuse[4] = {0.61424, 0.04136, 0.04136, 1.0};	
GLfloat specular[4] = {0.727811, 0.626959, 0.626959, 1.0};	

const float vertices[] =
{
	0.5,0.0,0.0,1.0,
	0.0,0.5,0.0,1.0,
	0.5,0.5,0.0,1.0,
};

const float colors[] =
{
	1.0,0.0,0.0,1.0,
	0.0,1.0,0.0,1.0,
	0.0,0.0,1.0,1.0,
};

GLfloat normal_f[] =
{
	1.0,0.0,0.0,
	0.0,1.0,0.0,
	0.0,0.0,1.0
};

GLbyte normal_b[] =
{
	1,0,0,
	0,1,0,
	0,0,1
};

GLshort normal_s[] =
{
	1,0,0,
	0,1,0,
	0,0,1
};
unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0,-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getdata() 
{
GLvoid **param;
GLint parami;
GLboolean paramb;

glGetBooleanv(GL_NORMAL_ARRAY, &paramb); 
LOGIF("get(GL_NORMAL_ARRAY)=%s\n",GET_BOOL(paramb));

glGetIntegerv(GL_NORMAL_ARRAY_BUFFER_BINDING, &parami);
LOGIF("get(GL_NORMAL_ARRAY_BUFFER_BINDING)=%d\n",parami);
glGetIntegerv(GL_NORMAL_ARRAY_STRIDE, &parami);
LOGIF("get(GL_NORMAL_ARRAY_STRIDE)=%d\n",parami);
glGetIntegerv(GL_NORMAL_ARRAY_TYPE, &parami);
LOGIF("get(GL_NORMAL_ARRAY_TYPE)=%d\n",parami);

    GL_CHECK(glGetPointerv(GL_NORMAL_ARRAY, param));
    LOGIF("GetPointerv(GL_NORMAL_ARRAY): %x\n", *param);
}

void render(GLenum factor)
{
 
    switch (factor) {
    case GL_BYTE:
        GL_CHECK(glEnableClientState(GL_NORMAL_ARRAY));
        GL_CHECK(glNormalPointer(GL_BYTE, 0, normal_b));
        break;
    case GL_SHORT:
        GL_CHECK(glEnableClientState(GL_NORMAL_ARRAY));
        GL_CHECK(glNormalPointer(GL_SHORT, 0, normal_s));
        break;
    case GL_FLOAT:
        GL_CHECK(glEnableClientState(GL_NORMAL_ARRAY));
        GL_CHECK(glNormalPointer(GL_FLOAT, 0, normal_f));
        break;
    default:
        break;
    }
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(4, GL_FLOAT, 0, vertices));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void renderFrame(GLenum factor)
{
	GLfloat li_ambient[] = { 0.0f, 0.2f, 1.0f, 1.0f };
	GLfloat li_diffuse[] = { 0.8f, 0.5f, 0.2f, 1.0f };
	GLfloat li_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, li_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, li_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,li_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0);

	GLfloat lmodel_ambient2[] ={1.0,1.0,1.0,1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient2);
	float light_model_ambient[4] = {1.0,1.0,1.0,0.0};
	float light_model_two_side = GL_FALSE;


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light_model_ambient);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,light_model_two_side);

	GLfloat light5_ambient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light5_diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light5_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light5_position[] = { -2.0f, 2.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT5, GL_AMBIENT, light5_ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR,light5_specular);
	glLightfv(GL_LIGHT5, GL_POSITION,light5_position);

   GL_CHECK(glEnable(GL_LIGHTING));
   GL_CHECK(glEnable(GL_LIGHT5));


   GL_CHECK(glClearColor(0.5, 0.5, 0.5, 0.0));

   GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
   render(factor);
   glFlush();
getdata();
   GL_CHECK(glDisable(GL_LIGHTING));
   GL_CHECK(glDisable(GL_LIGHT0));
}

int main(int argc, char** argv)
{
    string file = "gl13-normalpointer";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<3; i++) {
        renderFrame(factors[i]);
        string factor_name = get_enum_name(factors[i]);
    string filename = file + "_" + factor_name + ".bmp";
    LOGIF("filename=%s\n", filename.c_str());
    save2bmp(filename.c_str());
    glutSwapBuffers();
}
    GBtest_deinit();

    return 0;
}
