/**
 * @file gl20-drawbuffers.cpp
 * @testpoint glDrawBuffers
 *
 */

#include "Sample.h"
#include <cstring>

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;

GLuint bufferID;
GLuint textureID;
GLuint vao;

GLfloat texcoord[]={
	0.0, 1.0, 
	0.0, 0.0,
	1.0, 1.0, 
	1.0, 0.0
};

GLfloat vertice[]={
	-0.5, 0.5, 0.0,
	 0.5, 0.5, 0.0,
	-0.5,-0.5, 0.0,
	 0.5,-0.5, 0.0
};

GLenum factors[] = {
	GL_NONE,
	GL_FRONT_LEFT,
	GL_FRONT_RIGHT,
	GL_BACK_LEFT,
	GL_BACK_RIGHT,
	GL_AUX0
};

bool setupGraphics(GLenum buffer, int width, int height)
{
    GLubyte image[width*height*3];
    GLubyte *mapArray;
    GLenum buffers[] = {buffer};

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glDrawBuffers(1, buffers));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glColor4f(0.0, 1.0, 0.0, 0.0));
    GL_CHECK(glReadBuffer(buffer));
    GL_CHECK(glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, image));
    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, width, height, 0));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glClearColor(1.0f, 1.0f, 1.0f, 0.0f));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glEnable(GL_TEXTURE_2D));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
    GL_CHECK(glTexCoordPointer(2, GL_FLOAT, 0, texcoord));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, vertice));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    GL_CHECK(glFlush());
    GL_CHECK(glDeleteBuffers(1, &bufferID));
    GL_CHECK(glDisable(GL_TEXTURE_2D));
}

void Sample::test() {
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        setupGraphics(factors[i], WINDOW_W, WINDOW_H);
        string factor_name = get_enum_name(factors[i]);
        string bmp_file    = filename + "-" + factor_name + ".bmp";
        LOGI("[]: filename=%s\n", bmp_file.c_str());
        renderFrame();
        save2bmp(bmp_file.c_str());
        SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}

//int main(int argc, char** argv)
//{
//    string file = "gl20-drawbuffers";
//    GBtest_init(&argc,argv,file,DisplayMode);
//    for(int i=0; i<ARRAY_NUM(factors); i++) {
//        setupGraphics(factors[i], WINDOW_W, WINDOW_H);
//	string factor_name = get_enum_name(factors[i]);
//	    string filename = file + "-" + factor_name + ".bmp";
//	    LOGIF("[]: filename=%s\n", filename.c_str());
//            renderFrame();
//	    save2bmp(filename.c_str());
//	    glutSwapBuffers();
//    }
//    GBtest_deinit();
//
//    return 0;
//}
