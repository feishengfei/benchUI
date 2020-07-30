/**
 * @file accum2.c
 * @testpoint glArrayElement glVertexPointer
 *
 */
#include "gl-util.h"

static const GLenum factors[] = {
/*	GL_BYTE,
	GL_UNSIGNED_BYTE,
	GL_SHORT,
	GL_UNSIGNED_SHORT,
	GL_INT,
	GL_UNSIGNED_INT,*/
	GL_FLOAT,
//	GL_DOUBLE
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
	    printf("genvertex2\n");
	for(int i=0; i<NUM; i++)
	{
printf("V: %f, %f\t\t C: %f, %f, %f\n",vertex_f[i*2],vertex_f[i*2+1],colors_f[i*3],colors_f[i*3+1],colors_f[i*3+2]);
		colors_d[i] = (GLdouble)colors_f[i];		vertex_d[i] = (GLdouble)vertex_f[i];
		colors_ui[i] = (GLuint)colors_f[i];
		colors_i[i] = (GLint)colors_f[i];		vertex_i[i] = (GLint)vertex_f[i];
		colors_us[i] = (GLushort)colors_f[i];
		colors_s[i] = (GLshort)colors_f[i];		vertex_d[i] = (GLshort)vertex_f[i];
		colors_ub[i] = (GLubyte)(colors_f[i]*256);
		colors_b[i] = (GLbyte)(colors_f[i]*128);
	}
    return true;
}

void renderFrame(GLenum type)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
	    printf("glEnableClientState\n");
    if(type == GL_BYTE) {
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertex_f));
    GL_CHECK(glColorPointer(4, GL_BYTE, 0, colors_b));
    }
    if(type == GL_UNSIGNED_BYTE) {
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertex_f));
    GL_CHECK(glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors_ub));
    }
    if(type == GL_UNSIGNED_BYTE) {
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertex_f));
    GL_CHECK(glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors_ub));
    }
    if(type == GL_SHORT) {
    GL_CHECK(glVertexPointer(2, GL_SHORT, 0, vertex_s));
    GL_CHECK(glColorPointer(4, GL_SHORT, 0, colors_s));
    }
    if(type == GL_UNSIGNED_SHORT) {
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertex_f));
    GL_CHECK(glColorPointer(4, GL_UNSIGNED_SHORT, 0, colors_us));
    }
    if(type == GL_INT) {
    GL_CHECK(glVertexPointer(2, GL_INT, 0, vertex_i));
    GL_CHECK(glColorPointer(4, GL_INT, 0, colors_i));
    }
    if(type == GL_UNSIGNED_INT) {
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertex_f));
    GL_CHECK(glColorPointer(4, GL_UNSIGNED_INT, 0, colors_ui));
    }
    if(type == GL_FLOAT) {
	    printf("GL_FLOAT\n");
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertex_f));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors_f));
    }
    if(type == GL_DOUBLE) {
    GL_CHECK(glVertexPointer(2, GL_DOUBLE, 0, vertex_d));
    GL_CHECK(glColorPointer(4, GL_DOUBLE, 0, colors_d));
    }
	    printf("glBegin\n");
    GL_CHECK(glBegin(GL_QUADS));
	    printf("glArrayElement\n");
        GL_CHECK(glArrayElement(0));
        GL_CHECK(glArrayElement(1));
        GL_CHECK(glArrayElement(2));
        GL_CHECK(glArrayElement(3));
	    printf("glEnd\n");
        GL_CHECK(glEnd());
	    printf("glFlush\n");
        GL_CHECK(glFlush());
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
	    //glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
