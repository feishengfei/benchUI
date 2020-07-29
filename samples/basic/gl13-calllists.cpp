/**
 * @file accum2.c
 * @testpoint glColorMask
 *
 */
#include "gl-util.h"

GLboolean flag[] = {GL_TRUE,GL_FALSE,GL_TRUE};
GLfloat vertex[] = {-10.0f, 0.0f,  -15.0f,-10.0f,  10.0f, 0.0f};
GLuint offset=0;
GLenum types[] = {
	GL_BYTE,
	GL_UNSIGNED_BYTE,
	GL_SHORT,
	GL_UNSIGNED_SHORT,
	GL_INT,
	GL_UNSIGNED_INT,
	GL_FLOAT,
	GL_2_BYTES,
	GL_3_BYTES,
	GL_4_BYTES
};

GLbyte offset_b[2] = {0,1};
GLubyte offset_ub[2] = {0,1};
GLshort offset_s[2] = {0,1};
GLushort offset_us[2] = {0,1};
GLint offset_i[2] = {0,1};
GLfloat offset_f[2] = {0.0,1.0};
GLuint offset_ui[2] = {0,1};

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

void init(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2,2,-2,2,-2,2);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

	offset = glGenLists (2);
	glNewList(offset,GL_COMPILE);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(0.0,0.0);
	glVertex2f(1.0,0.0);
	glVertex2f(1.0,1.0);
	glEndList(); 

	glNewList(offset+1,GL_COMPILE);
	glColor3f(0.0,1.0,0.0);
	glVertex2f(0.0,0.0);
	glVertex2f(-1.0,0.0);
	glVertex2f(-1.0,1.0);
	glEndList();
}

void renderFrame(GLenum type)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear (GL_COLOR_BUFFER_BIT);
/*
	switch (type) {
	case GL_BYTE:
		offset_b=(GLbyte)offset;
		break;
	case GL_UNSIGNED_BYTE:
		offset_ub=(GLubyte)offset;
		break;
	case GL_SHORT:
		offset_s=(GLshort)offset;
		break;
	case GL_UNSIGNED_SHORT:
	case GL_2_BYTES:
		offset_us=(GLushort)offset;
		break;
	case GL_INT:
		offset_i=(GLint)offset;
		break;
	case GL_FLOAT:
		offset_f=(GLfloat)offset;
		break;
	case GL_2_BYTES:
		offset_2b=(GLushort)offset;
		break;
	case GL_3_BYTES:
		offset_3b=(GLuint)offset;
		break;
	case GL_4_BYTES:
		offset_4b=(GLuint)offset;
		break;
	default:
		break;
	} 
*/
	glShadeModel (GL_SMOOTH);
glListBase(offset);
	glBegin(GL_TRIANGLES);
	switch (type) {
	case GL_BYTE:
		glCallLists(2, type, offset_b);
		break;
	case GL_UNSIGNED_BYTE:
		glCallLists(2, type, offset_ub);
		break;
	case GL_SHORT:
		glCallLists(2, type, offset_s);
		break;
	case GL_UNSIGNED_SHORT:
		glCallLists(2, type, offset_us);
		break;
	case GL_INT:
		glCallLists(2, type, offset_i);
		break;
	case GL_UNSIGNED_INT:
		glCallLists(2, type, offset_ui);
		break;
	case GL_FLOAT:
		glCallLists(2, type, offset_f);
		break;
	case GL_2_BYTES:
		glCallLists(2, type, offset_us);
		break;
	case GL_3_BYTES:
		glCallLists(2, type, offset_ui);
		break;
	case GL_4_BYTES:
		glCallLists(2, type, offset_ui);
		break;
	default:
		break;
	}
	glEnd();
	GLboolean islist = glIsList(offset);
	LOGIF("islist=%s\n", GET_BOOL(islist));
	glDeleteLists(offset,2);
	glFlush();
}

int main(int argc, char** argv)
{
    string file = "gl13-calllists";
    GBtest_init(&argc,argv,file,DisplayMode);
    init(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(types); i++) {
	string type_name = get_enum_name(types[i]);
    string filename = file + "-" + type_name + ".bmp";
    LOGIF("filename=%s\n", filename.c_str());
    renderFrame(types[i]);
    save2bmp(filename.c_str());
    glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
