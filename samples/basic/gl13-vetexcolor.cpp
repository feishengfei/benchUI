/**
 * @file accum2.c
 * @testpoint glColor glVertex
 *
 */
#include "gl-util.h"
#include "limits.h"

#define NUM 16
GLfloat colors_f[NUM*3],vertex_f[NUM*2];//

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
    return true;
}

void renderFrame()
{
    int nv=0,nc=0;
    GL_CHECK(glClearColor(1.0,1.0,1.0,0.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glLineWidth(3.0));
    glBegin(GL_LINE_LOOP);
        glColor3b((GLbyte)(colors_f[nc] * CHAR_MAX), (GLbyte)(colors_f[nc+1] * CHAR_MAX), (GLbyte)(colors_f[nc+2] * CHAR_MAX));
        glVertex2s((GLshort)(vertex_f[nv]), (GLshort)(vertex_f[nv+1]));
	nc = nc + 3; nv = nv + 2;
        glColor3s((GLshort)(colors_f[nc] *SHRT_MAX), (GLshort)(colors_f[nc+1] *SHRT_MAX), (GLshort)(colors_f[nc+2] *SHRT_MAX));
        glVertex2i((GLint)(vertex_f[nv]), (GLint)(vertex_f[nv+1]));
	nc = nc + 3; nv = nv + 2;
        glColor3i((GLint)(colors_f[nc] *INT_MAX), (GLint)(colors_f[nc+1] *INT_MAX), (GLint)(colors_f[nc+2] *INT_MAX));
        glVertex2f(vertex_f[nv], vertex_f[nv]);
	nc = nc + 3; nv = nv + 2;
        glColor3f(colors_f[nc], colors_f[nc+1], colors_f[nc+2]);
        glVertex2d((GLdouble)(vertex_f[nv]), (GLdouble)(vertex_f[nv+1]));
	nc = nc + 3; nv = nv + 2;
        glColor3d((GLdouble)(colors_f[nc]), (GLdouble)(colors_f[nc+1]), (GLdouble)(colors_f[nc+2]));
        glVertex3s((GLshort)(vertex_f[nv]), (GLshort)(vertex_f[nv+1]), 0);
	nc = nc + 3; nv = nv + 2;
        glColor3ub((GLubyte)(colors_f[nc] * UCHAR_MAX), (GLubyte)(colors_f[nc+1] * UCHAR_MAX), (GLubyte)(colors_f[nc+2] * UCHAR_MAX));
        glVertex3i((GLint)(vertex_f[nv]), (GLint)(vertex_f[nv+1]), 0);
	nc = nc + 3; nv = nv + 2;
        glColor3us((GLushort)(colors_f[nc] * USHRT_MAX), (GLushort)(colors_f[nc+1] * USHRT_MAX), (GLushort)(colors_f[nc+2] * USHRT_MAX));
        glVertex3f(vertex_f[nv], vertex_f[nv+1], 0.0);
	nc = nc + 3; nv = nv + 2;
        glColor3ui((GLuint)(colors_f[nc] * UINT_MAX), (GLuint)(colors_f[nc+1] * UINT_MAX), (GLuint)(colors_f[nc+2] * UINT_MAX));
        glVertex3d((GLdouble)(vertex_f[nv]), (GLdouble)(vertex_f[nv+1]), 0.0);
	nc = nc + 3; nv = nv + 2;
        glColor4b((GLbyte)(colors_f[nc] * CHAR_MAX), (GLbyte)(colors_f[nc+1] * CHAR_MAX), (GLbyte)(colors_f[nc+2] * CHAR_MAX), 0);
        glVertex4s((GLshort)(vertex_f[nv]), (GLshort)(vertex_f[nv+1]), 0, 1);
	nc = nc + 3; nv = nv + 2;
        glColor4s((GLshort)(colors_f[nc] *SHRT_MAX), (GLshort)(colors_f[nc+1] *SHRT_MAX), (GLshort)(colors_f[nc+2] *SHRT_MAX), 0);
        glVertex4i((GLint)(vertex_f[nv]), (GLint)(vertex_f[nv+1]), 0, 1);
	nc = nc + 3; nv = nv + 2;
        glColor4i((GLint)(colors_f[nc] *INT_MAX), (GLint)(colors_f[nc+1] *INT_MAX), (GLint)(colors_f[nc+2] *INT_MAX), 0);
        glVertex4f(vertex_f[nv], vertex_f[nv+1], 0.0, 1.0);
	nc = nc + 3; nv = nv + 2;
        glColor4f(colors_f[nc], colors_f[nc+1], colors_f[nc+2], 0.0);
        glVertex4d((GLdouble)(vertex_f[nv]), (GLdouble)(vertex_f[nv+1]), 0.0, 1.0);
	nc = nc + 3; nv = nv + 2;
        glColor4ub((GLubyte)(colors_f[nc] * UCHAR_MAX), (GLubyte)(colors_f[nc+1] * UCHAR_MAX), (GLubyte)(colors_f[nc+2] * UCHAR_MAX), 0);
        glVertex2f(vertex_f[nv], vertex_f[nv+1]);
	nc = nc + 3; nv = nv + 2;
        glColor4us((GLushort)(colors_f[nc] * USHRT_MAX), (GLushort)(colors_f[nc+1] * USHRT_MAX), (GLushort)(colors_f[nc+2] * USHRT_MAX), 0);
        glVertex2f(vertex_f[nv], vertex_f[nv+1]);
	nc = nc + 3; nv = nv + 2;
        glColor4ui((GLuint)(colors_f[nc] * UINT_MAX), (GLuint)(colors_f[nc+1] * UINT_MAX), (GLuint)(colors_f[nc+2] * UINT_MAX), 0);
        glVertex2f(vertex_f[nv], vertex_f[nv+1]);
	nc = nc + 3; nv = nv + 2;
        glColor4d((GLdouble)(colors_f[nc]), (GLdouble)(colors_f[nc+1]), (GLdouble)(colors_f[nc+2]), 0);
        glVertex2f(vertex_f[nv], vertex_f[nv+1]);
    glEnd();
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-vetexcolor";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    string filename = file + ".bmp";
    LOGIF("filename=%s\n", filename.c_str());
    renderFrame();
    save2bmp(filename.c_str());
    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
