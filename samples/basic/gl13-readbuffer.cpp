/**
 * @file accum2.c
 * @testpoint glAccum
 *
 */
#include "gl-util.h"

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

int n=300;
int m=300;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(255, 255, 127);
    glRecti(0,0,n,m);
    glFlush(); 
}

void reshape(int w, int h)
{
	int i,j;
	GLubyte pixels[3];

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLfloat) w, 0.0, (GLfloat) h);
    glMatrixMode(GL_MODELVIEW);

    glClearColor (0.0, 0.5, 1.0, 1.0);
    gluOrtho2D(0.0, 0.0, (GLfloat) n, (GLfloat) m);
    glReadBuffer(GL_BACK); 

    glPixelStorei(GL_PACK_SWAP_BYTES, GL_TRUE);
    glPixelStorei(GL_PACK_LSB_FIRST, GL_TRUE);
    glPixelStorei(GL_PACK_ROW_LENGTH, 1);
    glPixelStorei(GL_PACK_IMAGE_HEIGHT, 1);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 1);
    glPixelStorei(GL_PACK_SKIP_ROWS, 1);
    glPixelStorei(GL_PACK_SKIP_IMAGES, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    /* glDisable(GL_DITHER); */

	glutPostRedisplay();
	glReadPixels(0,0,1,1,GL_RGB,GL_UNSIGNED_BYTE, pixels);
	for(i=0;i<2;i++) for(j=0;j<2;j++)
	{
		printf("%d %d %d\n", pixels[0], pixels[1], pixels[2]);
	}
}

int main(int argc, char** argv)
{
    string file = "gl13-readbuffer";
    GBtest_init(&argc,argv,file,DisplayMode);
    reshape(WINDOW_W, WINDOW_H);
/*    for(int i=0; i<ARRAY_NUM(funcs); i++) {
        for(int j=0; j<ARRAY_NUM(factors); j++) {
            string func_name = get_enum_name(funcs[i]);
            string sfail_name = get_enum_name(factors[j]);*/
	    string filename = file + ".bmp";
	    LOGIF("filename=%s\n", filename.c_str());
            display();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
//    }}
    GBtest_deinit();

    return 0;
}
