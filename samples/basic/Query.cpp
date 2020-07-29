/**
 * @file query.cpp
 * @testpoint glGenQueries glGetQueryObjectuiv glBeginQuery glGetQueryiv
 *
 */

#include "gl-util.h"
#include <cstring>

unsigned int DisplayMode = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;
GLuint query[3];

const float triangleVertices[] =
{
     1.0f, -1.0f, 0.0f,
     2.0f,  1.5f, 0.0f,
     3.0f, -1.0f, 0.0f
};
const float triangleVertices1[] =
{
    -1.0f, -1.0f, 0.0f,
     0.0f,  1.5f, 0.0f,
     1.0f, -1.0f, 0.0f
};
const float triangleVertices2[] =
{
    -1.0f, -1.0f, 0.0f,
    -2.0f,  1.5f, 0.0f,
    -3.0f, -1.0f, 0.0f
};
/* Per corner colors for the triangle (Red, Green, Green). */
const float triangleColors[] =
{
    1.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0
};
const float triangleColors1[] =
{
    0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0
};
const float triangleColors2[] =
{
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0
};

bool setupGraphics(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho (-3.0f, 3.0f, -3.0f*h/w, 3.0f*h/w, -3.0f, 3.0f);
	}
	else {
		glOrtho (-3.0f*w/h, 3.0f*w/h, -3.0f, 3.0f, -3.0f, 3.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGenQueries(3,query);
	LOGIF("is query: %d,%d,%d\n",glIsQuery(query[0]),glIsQuery(query[1]),glIsQuery(query[2]));

    return true;
}

void getQueryObject(GLuint id)
{
    int count=1000;
    GLuint queryReady=GL_FALSE;
    while(!queryReady&&count--)
    {
        glGetQueryObjectuiv(id, GL_QUERY_RESULT_AVAILABLE, &queryReady);
        LOGIF("GL_QUERY_RESULT_AVAILABLE(%d):%d\n",id, queryReady);
    }
    GLuint samples;
    glGetQueryObjectuiv(id, GL_QUERY_RESULT, &samples);
    LOGIF("GL_QUERY_RESULT(%d):%d\n",id, samples);
}

void renderFrame(void)
{
GLint name;
   GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

glBeginQuery(GL_SAMPLES_PASSED, query[0]);
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, triangleVertices));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, triangleColors));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
glGetQueryiv(GL_SAMPLES_PASSED,GL_CURRENT_QUERY,&name);
LOGIF("current query: %d\n",name);
glGetQueryiv(GL_SAMPLES_PASSED,GL_QUERY_COUNTER_BITS,&name);
LOGIF("query counter bits: %d\n",name);
glEndQuery(GL_SAMPLES_PASSED);
getQueryObject(query[0]);

glBeginQuery(GL_SAMPLES_PASSED, query[1]);
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, triangleVertices1));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, triangleColors1));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
glGetQueryiv(GL_SAMPLES_PASSED,GL_CURRENT_QUERY,&name);
LOGIF("current query: %d\n",name);
glGetQueryiv(GL_SAMPLES_PASSED,GL_QUERY_COUNTER_BITS,&name);
LOGIF("query counter bits: %d\n",name);
glEndQuery(GL_SAMPLES_PASSED);
getQueryObject(query[1]);

glBeginQuery(GL_SAMPLES_PASSED, query[2]);
    GL_CHECK(glVertexPointer(3, GL_FLOAT, 0, triangleVertices2));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, triangleColors2));
    GL_CHECK(glEnableClientState(GL_VERTEX_ARRAY));
    GL_CHECK(glEnableClientState(GL_COLOR_ARRAY));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
glGetQueryiv(GL_SAMPLES_PASSED,GL_CURRENT_QUERY,&name);
LOGIF("current query: %d\n",name);
glEndQuery(GL_SAMPLES_PASSED);
getQueryObject(query[2]);
glGetQueryiv(GL_SAMPLES_PASSED,GL_CURRENT_QUERY,&name);
LOGIF("current query: %d\n",name);
glGetQueryiv(GL_SAMPLES_PASSED,GL_QUERY_COUNTER_BITS,&name);
LOGIF("query counter bits: %d\n",name);
glFlush();
}

int main(int argc, char** argv)
{
    string file = "gl15-query";
    GBtest_init(&argc,argv,file,DisplayMode);
    setupGraphics(WINDOW_W, WINDOW_H);
	    string filename = file + ".bmp";
	    LOGIF("[]: filename=%s\n", filename.c_str());
            renderFrame();
	    save2bmp(filename.c_str());
	    glutSwapBuffers();
    GBtest_deinit();

    return 0;
}
