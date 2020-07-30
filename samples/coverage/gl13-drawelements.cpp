/**
 * @file accum2.c
 * @testpoint glDrawElements
 *
 */
#include "gl-util.h"

static const GLenum factors[] = {
	GL_POINTS,
	GL_LINE_STRIP,
	GL_LINE_LOOP,
	GL_LINES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN,
	GL_TRIANGLES,
	GL_QUAD_STRIP,
	GL_QUADS,
	GL_POLYGON 
};
static const GLenum types[] = {
GL_UNSIGNED_BYTE,
GL_UNSIGNED_SHORT,
GL_UNSIGNED_INT
};
#define NUM 12
GLfloat colors[NUM*3],vertex[NUM*2];
GLubyte indices_ub[NUM];
unsigned short indices_us[NUM];
unsigned int indices_ui[NUM];
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
	genvertex2(NUM, vertex, colors, 2);
	for(int i=0; i<NUM; i++)
	{
		indices_ub[i] = (GLubyte)i;
		indices_us[i] = (GLushort)i;
		indices_ui[i] = (GLuint)i;
	}
    return true;
}

void renderFrame(GLenum mode, GLenum type)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glPointSize(5.0));
    GL_CHECK(glLineWidth(3.0));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glVertexPointer(2, GL_FLOAT, 0, vertex));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    if(type == GL_UNSIGNED_BYTE)
        GL_CHECK(glDrawElements(mode, NUM, type, indices_ub));
    if(type == GL_UNSIGNED_SHORT)
        GL_CHECK(glDrawElements(mode, NUM, type, indices_us));
    if(type == GL_UNSIGNED_INT)
        GL_CHECK(glDrawElements(mode, NUM, type, indices_ui));
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-drawelements";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
    for(int j=0; j<ARRAY_NUM(types); j++) {
            string src_name = get_primitives_name(factors[i]);
            string type_name = get_enum_name(types[j]);
	    string filename = file + "-" + src_name + "-" + type_name + ".bmp";
	    LOGIF("[%d_%d]: filename=%s\n", i, j, filename.c_str());
            renderFrame(factors[i],types[j]);
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    }}
    GBtest_deinit();

    return 0;
}
