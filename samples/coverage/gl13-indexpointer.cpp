/**
 * @file accum2.c
 * @testpoint glArrayElement glVertexPointer
 *
 */
#include "gl-util.h"
#include "limits.h"

static const GLenum factors[] = {
	GL_UNSIGNED_BYTE,
        GL_SHORT,
        GL_INT,
        GL_FLOAT,
	GL_DOUBLE
};
#define NUM 4
GLbyte colors_b[NUM*3];
GLubyte colors_ub[NUM*3];
GLshort colors_s[NUM*3],vertex_s[NUM*2];//
GLushort colors_us[NUM*3];
GLint colors_i[NUM*3],vertex_i[NUM*2];//
GLuint colors_ui[NUM*3];
GLfloat colors_f[NUM*3],vertex_f[NUM*2];//
GLdouble colors_d[NUM*3],vertex_d[NUM*2];//

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-3.0f, 3.0f, -3.0f*h/w, 3.0f*h/w, -3.0f, 3.0f);
	}
	else {
		glOrtho(-3.0f*w/h, 3.0f*w/h, -3.0f, 3.0f, -3.0f, 3.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	genvertex2(NUM, vertex_f, colors_f, 2);
	for(int i=0; i<NUM; i++)  //use max
	{
		for(int c=0; c<3; c++) {
		colors_d[i*3+c] = (GLdouble)colors_f[i*3+c];
		colors_ui[i*3+c] = (GLuint)(colors_f[i*3+c]*UINT_MAX);
		colors_i[i*3+c] = (GLint)(colors_f[i*3+c]*INT_MAX);
		colors_us[i*3+c] = (GLushort)(colors_f[i*3+c]*USHRT_MAX);
		colors_s[i*3+c] = (GLshort)(colors_f[i*3+c]*SHRT_MAX);
		colors_ub[i*3+c] = (GLubyte)(colors_f[i*3+c]*UCHAR_MAX);
		colors_b[i*3+c] = (GLbyte)(colors_f[i*3+c]*CHAR_MAX);
		}
	}
    return true;
}

void getdata() 
{
GLvoid **param;

    GL_CHECK(glGetPointerv(GL_INDEX_ARRAY_POINTER, param));
    LOGIF("GetPointerv(GL_INDEX_ARRAY_POINTER): %x\n", *param);
}

void renderFrame(GLenum type)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_INDEX_ARRAY_POINTER));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertex_f));
    if(type == GL_UNSIGNED_BYTE) { //
    GL_CHECK(glIndexPointer(GL_UNSIGNED_BYTE, 0, colors_ub));
    }
    if(type == GL_SHORT) { //
    GL_CHECK(glIndexPointer(GL_SHORT, 0, colors_s));
    }
    if(type == GL_INT) { //
    GL_CHECK(glIndexPointer(GL_INT, 0, colors_i));
    }
    if(type == GL_FLOAT) { //
    GL_CHECK(glIndexPointer(GL_FLOAT, 0, colors_f));
    }
    if(type == GL_DOUBLE) { //
    GL_CHECK(glIndexPointer(GL_DOUBLE, 0, colors_d));
    }
    glBegin(GL_QUADS);  // do not check
        glArrayElement(0);
        glArrayElement(1);
        glArrayElement(2);
        glArrayElement(3);
    glEnd();
getdata();
    GL_CHECK(glFlush());
    GL_CHECK(glDisableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glDisableClientState(GL_INDEX_ARRAY_POINTER));
}

int main(int argc, char** argv)
{
    string file = "arrayelement";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
            string src_name = get_enum_name(factors[i]);
	    string filename = file + "-" + src_name + ".bmp";
	    printf("[%d]: filename=%s\n", i, filename.c_str());
	    LOGIF("[%d]: filename=%s\n", i, filename.c_str());
            renderFrame(factors[i]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
