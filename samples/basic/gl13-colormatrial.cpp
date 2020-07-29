/*
 *  colormatix.c
 *  This program uses the color matrix to exchange the color channels of
 *  an image.
 *
 *    Red   -> Green
 *    Green -> Blue
 *    Blue  -> Red
 *
 */

#include "gl-util.h"
#include <cstring>

unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

GLenum faces[] = {
        GL_FRONT,
	GL_BACK,
	GL_FRONT_AND_BACK
};

GLenum modes[] = {
        GL_EMISSION,
        GL_AMBIENT,
        GL_DIFFUSE,
        GL_SPECULAR,
	GL_AMBIENT_AND_DIFFUSE
};

void draw_triangle(void)
{
	glBegin(GL_TRIANGLES);
	glColor4f(1.0,0.0,0.0,1.0);
	glNormal3f(1.0,0.0,0.0);
	glVertex4f(0.5,0.0,0.0,1.0);
	glColor4f(0.0,1.0,0.0,1.0);
	glNormal3f(0.0,1.0,0.0);
	glVertex4f(0.0,0.5,0.0,1.0);
	glColor4f(0.0,0.0,1.0,1.0);
	glNormal3f(0.0,0.0,1.0);
	glVertex4f(0.5,0.5,0.0,1.0);
	glEnd();
}

void glmaterial(GLenum face)
{
	GLfloat li_ambient[] = { 0.0f, 0.2f, 1.0f, 1.0f };
	GLfloat li_diffuse[] = { 0.8f, 0.5f, 0.2f, 1.0f };
	GLfloat li_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat li_emission[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glMaterialfv(face, GL_AMBIENT_AND_DIFFUSE, li_diffuse);
	glMaterialfv(face, GL_AMBIENT, li_ambient);
	glMaterialfv(face, GL_DIFFUSE, li_diffuse);
	glMaterialfv(face, GL_SPECULAR,li_specular);
	glMaterialf(face, GL_SHININESS, 20.0);
}

void gllightmodel(void)
{   
	GLfloat lmodel_ambient2[] ={1.0,1.0,1.0,1.0};
	float light_model_ambient[4] = {1.0,1.0,1.0,0.0};
	float light_model_local_viewer = 1.0;
	float light_model_two_side = GL_FALSE;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light_model_ambient);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,light_model_local_viewer);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,light_model_two_side);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient2);
}

void gllight(void)
{
	GLfloat light1_ambient[]= { 0.0f, 1.0f, 0.0f, 1.0f };
	GLfloat light1_diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light1_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light1_position[] = { 0.2f, 1.0f, 0.2f, 1.0f };
	GLfloat spot_direction[] ={-1.0, -1.0, 0.0};

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR,light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION,light1_position);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

	glEnable(GL_LIGHTING);
}

void init(void)
{   
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,480,320);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0,-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
}

void getdata()
{
	GLfloat paramf[4];

	glGetMaterialfv(GL_FRONT, GL_AMBIENT, paramf);
	LOGIF("GetMaterialfv(GL_AMBIENT)=%f %f %f %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetMaterialfv(GL_FRONT, GL_DIFFUSE, paramf);
	LOGIF("GetMaterialfv(GL_DIFFUSE)=%f %f %f %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetMaterialfv(GL_FRONT, GL_SPECULAR, paramf);
	LOGIF("GetMaterialfv(GL_SPECULAR)=%f %f %f %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetMaterialfv(GL_FRONT, GL_EMISSION, paramf);
	LOGIF("GetMaterialfv(GL_EMISSION)=%f %f %f %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetMaterialfv(GL_FRONT, GL_SHININESS, paramf);
	LOGIF("GetMaterialfv(GL_SHININESS)=%f\n", paramf[0]);
	glGetMaterialfv(GL_FRONT, GL_COLOR_INDEXES, paramf);
	LOGIF("GetMaterialfv(GL_COLOR_INDEXES)=%f\n", paramf[0]);

	glGetLightfv(GL_LIGHT1, GL_AMBIENT, paramf);
	LOGIF("glGetLightfv(GL_AMBIENT)=%f %f %f %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetLightfv(GL_LIGHT1, GL_DIFFUSE, paramf);
	LOGIF("glGetLightfv(GL_DIFFUSE)=%f %f %f %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetLightfv(GL_LIGHT1, GL_SPECULAR, paramf);
	LOGIF("glGetLightfv(GL_SPECULAR)=%f %f %f %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetLightfv(GL_LIGHT1, GL_POSITION, paramf);
	LOGIF("glGetLightfv(GL_POSITION)=%f %f %f %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
	glGetLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, paramf);
	LOGIF("glGetLightfv(GL_SPOT_DIRECTION)=%f %f %f\n", paramf[0], paramf[1], paramf[2]);
	glGetLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, paramf);
	LOGIF("glGetLightfv(GL_SPOT_EXPONENT)=%f\n", paramf[0]);
	glGetLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, paramf);
	LOGIF("glGetLightfv(GL_SPOT_CUTOFF)=%f\n", paramf[0]);
	glGetLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, paramf);
	LOGIF("glGetLightfv(GL_CONSTANT_ATTENUATION)=%f\n", paramf[0]);
	glGetLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, paramf);
	LOGIF("glGetLightfv(GL_LINEAR_ATTENUATION)=%f\n", paramf[0]);
	glGetLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, paramf);
	LOGIF("glGetLightfv(GL_QUADRATIC_ATTENUATION)=%f\n", paramf[0]);
}

void display(GLenum face)
{  
	glEnable(GL_LIGHT5);
	gllight();
	gllightmodel();
	glmaterial(face);
	glEnable(GL_COLOR_MATERIAL); 
	glColorMaterial(face, GL_AMBIENT_AND_DIFFUSE);
	glColorMaterial(face, GL_AMBIENT);
	glColorMaterial(face, GL_DIFFUSE);
	glColorMaterial(face, GL_SPECULAR);
	glColorMaterial(face, GL_EMISSION); 

	draw_triangle();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT5);
	glDisable(GL_COLOR_MATERIAL); 
	glFlush(); 
	getdata();
}

void reshape (int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0,-1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);  
}


int main(int argc, char** argv)
{
    string file = "gl13-colormatrial";
    GBtest_init(&argc,argv,file,DisplayMode);
    init();
    reshape(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(faces); i++) {
	string filename = file + ".bmp";
	LOGIF("filename=%s\n", filename.c_str());
        display(faces[i]);
        save2bmp(filename.c_str());
	glutSwapBuffers();
    }
    GBtest_deinit();

    return 0;
}
