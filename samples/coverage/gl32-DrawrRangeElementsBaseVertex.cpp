/**
 * @file accum2.c
 * @testpoint glDrawRangeElementsBaseVertex
 *
 */
#include "Sample.h"
#include "Primitive.h"

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
unsigned int start = 0;
unsigned int end = 12;

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
    Primitive::genvertex2(NUM, vertex, colors, 2);
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
        GL_CHECK(glDrawRangeElementsBaseVertex(mode, start, end, NUM, type, indices_ub, 3));
    if(type == GL_UNSIGNED_SHORT)
        GL_CHECK(glDrawRangeElementsBaseVertex(mode, start, end, NUM, type, indices_us, 3));
    if(type == GL_UNSIGNED_INT)
        GL_CHECK(glDrawRangeElementsBaseVertex(mode, start, end, NUM, type, indices_ui, 3));
    GL_CHECK(glFlush());
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
    for(int j=0; j<ARRAY_NUM(types); j++) {
            string src_name = get_primitives_name(factors[i]);
            string type_name = get_enum_name(types[j]);
	    string bmp_file = filename + "-" + src_name + "-" + type_name + ".bmp";
	    LOGI("[%d_%d]: filename=%s\n", i, j, bmp_file.c_str());
            renderFrame(factors[i],types[j]);
	    save2bmp(bmp_file.c_str());
	    SwapBuffers();
    }}
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}