/**
 * @file gl14-points.c
 * @testpoint glPointParameter
 *
 */
#include "gl-util.h"
unsigned int DisplayMode = GLUT_SINGLE | GLUT_RGBA;

#define NUM 8//68
float vertices[NUM*3], colors[NUM*4];
float constant[3] = {2.0, 0.0, 0.0};
float linear[3] = {0.0, 0.12, 0.0};
float quadratic[3] = {0.0, 0.0, 0.01};

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-2.0f, 2.0f, -2.0f*h/w, 2.0f*h/w, -2.0f, 2.0f);
	}
	else {
		glOrtho(-2.0f*w/h, 2.0f*w/h, -2.0f, 2.0f, -2.0f, 2.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    return true;
}

void getRandv3(float *data) {
        LOGIF("float vertices[] = {\n");
    for(int i=0; i<NUM; i++) {
        *(data+(i*2)) = (rand()/(float)RAND_MAX) * 3.8 - 1.9;
        LOGIF("\t %f,", *(data+(i*2)));
        *(data+(i*2)+1) = (rand()/(float)RAND_MAX) * 3.8 - 1.9;
        LOGIF(" %f,", *(data+(i*2)+1));
        *(data+(i*2)+2) = (rand()/(float)RAND_MAX) * 3.8 - 1.9;
        LOGIF(" %f,\n", *(data+(i*2)+1));
    }
        LOGIF("\t}\n");
}

void getRandc4(float *data) {
        LOGIF("float colors[] = {\n");
    for(int i=0; i<NUM; i++) {
        *(data+(i*4)) = (rand()/(float)RAND_MAX) * 0.9 + 0.1;
        LOGIF("\t %f,", *(data+(i*4)));
        *(data+(i*4)+1) = (rand()/(float)RAND_MAX) * 0.9 + 0.1;
        LOGIF(" %f,", *(data+(i*4)+1));
        *(data+(i*4)+2) = (rand()/(float)RAND_MAX) * 0.9 + 0.1;
        LOGIF(" %f,", *(data+(i*4)+2));
        *(data+(i*4)+3) = (rand()/(float)RAND_MAX) * 1.0;
        LOGIF(" %f,\n", *(data+(i*4)+3));
    }
        LOGIF("\t}\n");
}

void renderFrame()
{
    getRandv3(vertices);
    getRandc4(colors);
glClearColor (0.0, 0.0, 0.0, 0.0);
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
//    GL_CHECK(glSampleCoverage(1.0,GL_TRUE));
//    GL_CHECK(glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE));
    GL_CHECK(glEnable(GL_POINT_SMOOTH));
//    GL_CHECK(glEnable(GL_MULTISAMPLE));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

    GL_CHECK(glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, constant));
    GL_CHECK(glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, linear));
    GL_CHECK(glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, quadratic));
    GL_CHECK(glPointParameterf(GL_POINT_SIZE_MIN, 2.0));
    GL_CHECK(glPointParameteri(GL_POINT_SIZE_MAX, 20));
    GL_CHECK(glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, 2.0));

    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, vertices));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, NUM));

    GL_CHECK(glFlush());
}

int main(int argc, char** argv)
{
    string file = "gl14-points";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
    //while(1)
    
        string filename = file + ".bmp";
        LOGIF("filename=%s\n", filename.c_str());
        renderFrame();
	save2bmp(filename.c_str());
	glutSwapBuffers();
    
    GBtest_deinit();

    return 0;
}
