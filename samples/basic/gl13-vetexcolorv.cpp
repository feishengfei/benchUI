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
	GLbyte color_3b[3] = {(GLbyte)(colors_f[nc] * CHAR_MAX), (GLbyte)(colors_f[nc+1] * CHAR_MAX), (GLbyte)(colors_f[nc+2] * CHAR_MAX)};
	GLshort vertex_2s[2] = {(GLshort)(vertex_f[nv]), (GLshort)(vertex_f[nv+1])};
        glColor3bv(color_3b);
        glVertex2sv(vertex_2s);
	nc = nc + 3; nv = nv + 2;

	GLshort color_3s[3] = {(GLshort)(colors_f[nc] *SHRT_MAX), (GLshort)(colors_f[nc+1] *SHRT_MAX), (GLshort)(colors_f[nc+2] *SHRT_MAX)};
	GLint vertex_2i[2] = {(GLint)(vertex_f[nv]), (GLint)(vertex_f[nv+1])};
        glColor3sv(color_3s);
        glVertex2iv(vertex_2i);
	nc = nc + 3; nv = nv + 2;

	GLint color_3i[3] = {(GLint)(colors_f[nc] *INT_MAX), (GLint)(colors_f[nc+1] *INT_MAX), (GLint)(colors_f[nc+2] *INT_MAX)};
	GLfloat vertex_2f[2] = {vertex_f[nv], vertex_f[nv]};
        glColor3iv(color_3i);
        glVertex2fv(vertex_2f);
	nc = nc + 3; nv = nv + 2;

	GLfloat color_3f[3] = {colors_f[nc], colors_f[nc+1], colors_f[nc+2]};
	GLdouble vertex_2d[2] = {(GLdouble)(vertex_f[nv]), (GLdouble)(vertex_f[nv+1])};
        glColor3fv(color_3f);
        glVertex2dv(vertex_2d);
	nc = nc + 3; nv = nv + 2;

	GLdouble color_3d[3] = {(GLdouble)(colors_f[nc]), (GLdouble)(colors_f[nc+1]), (GLdouble)(colors_f[nc+2])};
	GLshort vertex_3s[3] = {(GLshort)(vertex_f[nv]), (GLshort)(vertex_f[nv+1]), 0};
        glColor3dv(color_3d);
        glVertex3sv(vertex_3s);
	nc = nc + 3; nv = nv + 2;

	GLubyte color_3ub[3] = {(GLubyte)(colors_f[nc] * UCHAR_MAX), (GLubyte)(colors_f[nc+1] * UCHAR_MAX), (GLubyte)(colors_f[nc+2] * UCHAR_MAX)};
	GLint vertex_3i[3] = {(GLint)(vertex_f[nv]), (GLint)(vertex_f[nv+1]), 0};
        glColor3ubv(color_3ub);
        glVertex3iv(vertex_3i);
	nc = nc + 3; nv = nv + 2;

	GLushort color_3us[3] = {(GLushort)(colors_f[nc] * USHRT_MAX), (GLushort)(colors_f[nc+1] * USHRT_MAX), (GLushort)(colors_f[nc+2] * USHRT_MAX)};
	GLfloat vertex_3f[3] = {vertex_f[nv], vertex_f[nv+1], 0.0};
        glColor3usv(color_3us);
        glVertex3fv(vertex_3f);
	nc = nc + 3; nv = nv + 2;

	GLuint color_3ui[3] = {(GLuint)(colors_f[nc] * UINT_MAX), (GLuint)(colors_f[nc+1] * UINT_MAX), (GLuint)(colors_f[nc+2] * UINT_MAX)};
	GLdouble vertex_3d[3] = {(GLdouble)(vertex_f[nv]), (GLdouble)(vertex_f[nv+1]), 0.0};
        glColor3uiv(color_3ui);
        glVertex3dv(vertex_3d);
	nc = nc + 3; nv = nv + 2;

	GLbyte color_4b[4] = {(GLbyte)(colors_f[nc] * CHAR_MAX), (GLbyte)(colors_f[nc+1] * CHAR_MAX), (GLbyte)(colors_f[nc+2] * CHAR_MAX), 0};
	GLshort vertex_4s[4] = {(GLshort)(vertex_f[nv]), (GLshort)(vertex_f[nv+1]), 0, 1};
        glColor4bv(color_4b);
        glVertex4sv(vertex_4s);
	nc = nc + 3; nv = nv + 2;

	GLshort color_4s[4] = {(GLshort)(colors_f[nc] *SHRT_MAX), (GLshort)(colors_f[nc+1] *SHRT_MAX), (GLshort)(colors_f[nc+2] *SHRT_MAX), 0};
	GLint vertex_4i[4] = {(GLint)(vertex_f[nv]), (GLint)(vertex_f[nv+1]), 0, 1};
        glColor4sv(color_4s);
        glVertex4iv(vertex_4i);
	nc = nc + 3; nv = nv + 2;

	GLint color_4i[4] = {(GLint)(colors_f[nc] *INT_MAX), (GLint)(colors_f[nc+1] *INT_MAX), (GLint)(colors_f[nc+2] *INT_MAX), 0};
	GLfloat vertex_4f[4] = {vertex_f[nv], vertex_f[nv+1], 0.0, 1.0};
        glColor4iv(color_4i);
        glVertex4fv(vertex_4f);
	nc = nc + 3; nv = nv + 2;

	GLfloat color_4f[4] = {colors_f[nc], colors_f[nc+1], colors_f[nc+2], 0.0};
	GLdouble vertex_4d[4] = {(GLdouble)(vertex_f[nv]), (GLdouble)(vertex_f[nv+1]), 0.0, 1.0};
        glColor4fv(color_4f);
        glVertex4dv(vertex_4d);
	nc = nc + 3; nv = nv + 2;

	GLubyte color_4ub[4] = {(GLubyte)(colors_f[nc] * UCHAR_MAX), (GLubyte)(colors_f[nc+1] * UCHAR_MAX), (GLubyte)(colors_f[nc+2] * UCHAR_MAX), 0};
        glColor4ubv(color_4ub);
        glVertex2fv(&vertex_2f[nv]);
	nc = nc + 3; nv = nv + 2;

	GLushort color_4us[4] = {(GLushort)(colors_f[nc] * USHRT_MAX), (GLushort)(colors_f[nc+1] * USHRT_MAX), (GLushort)(colors_f[nc+2] * USHRT_MAX), 0};
        glColor4usv(color_4us);
        glVertex2fv(&vertex_2f[nv]);
	nc = nc + 3; nv = nv + 2;

	GLuint color_4ui[4] = {(GLuint)(colors_f[nc] * UINT_MAX), (GLuint)(colors_f[nc+1] * UINT_MAX), (GLuint)(colors_f[nc+2] * UINT_MAX), 0};
        glColor4uiv(color_4ui);
        glVertex2fv(&vertex_2f[nv]);
	nc = nc + 3; nv = nv + 2;

	GLdouble color_4d[4] = {(GLdouble)(colors_f[nc]), (GLdouble)(colors_f[nc+1]), (GLdouble)(colors_f[nc+2]), 0};
        glColor4dv(color_4d);
        glVertex2fv(&vertex_2f[nv]);
    glEnd();
    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl13-vetexcolorv";
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
