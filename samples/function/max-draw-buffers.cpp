/**
 ** @file max-draw-buffers.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2020-05-15, create file
 ** @par TestPoints:
 **    GL_MAX_DRAW_BUFFERS
 */


#include "Sample.h"

using std::string;
using namespace std;

void getInfo()
{
    GLint my_draw_buffers;
    GL_CHECK(glGetIntegerv(GL_MAX_DRAW_BUFFERS , &my_draw_buffers));
    LOGI("GL_MAX_DRAW_BUFFERS = %d\n", my_draw_buffers);

    for(int i = 0 ; i < my_draw_buffers ; i++)
    {
        int temp;
        GL_CHECK( glGetIntegerv(GL_DRAW_BUFFER0 +i, &temp));
        LOGI("GL_DRAW_BUFFER0: %d \n", temp);    
    }
}

void Sample::test() {
    getInfo();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}
