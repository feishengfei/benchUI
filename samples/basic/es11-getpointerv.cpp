/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file getpointerv.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-08-21, Add commit
 * @brief basic test for getpointerv related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using namespace BotsonSDK;
using std::string;

GLenum getfactors[] = {
	GL_COLOR_ARRAY_POINTER,
	GL_NORMAL_ARRAY_POINTER,
	GL_POINT_SIZE_ARRAY_POINTER_OES,
	GL_TEXTURE_COORD_ARRAY_POINTER,
	GL_VERTEX_ARRAY_POINTER
};
GLenum factors[] = {
	GL_COLOR_ARRAY,
	GL_NORMAL_ARRAY,
	GL_POINT_SIZE_ARRAY_OES,
	GL_TEXTURE_COORD_ARRAY,
	GL_VERTEX_ARRAY
};

bool renderFrame()
{
    int i=0;
    int num=ARRAY_NUM(factors);
    GLfloat param[4];
    GLvoid *params;
    bool pass=true;
    GLfloat vertices[4] = {0.1,0.2,0.3,0.4};
    GLfloat colors[4] = {0.5,0.6,0.7,0.8};
    GLfloat normals[4] = {0.9,1.0,1.1,1.2};
    GLfloat textures[4] = {1.3,1.4,1.5,1.6};
    GLfloat points[4] = {1.7,1.8,1.9,2.0};

    GL_CHECK(glVertexPointer(4, GL_FLOAT, 0, vertices));
    GL_CHECK(glColorPointer(4, GL_FLOAT, 0, colors));
    GL_CHECK(glNormalPointer(GL_FLOAT, 0, normals));
    GL_CHECK(glTexCoordPointer(4, GL_FLOAT, 0, textures));
    GL_CHECK(glPointSizePointerOES(GL_FLOAT, 0, points));

    for(i=0; i<num; i++)
	GL_CHECK(glEnableClientState(factors[i]));

    for(i=0; i<num; i++) {
	pass=true;
	glGetPointerv(getfactors[i], &params);
        memcpy(param,params,4*sizeof(GLfloat));
	for(int j=0; j<4; j++) {
            if(param[i]!=(i*0.4+0.1))
		pass == false;	
	}	
	LOGI("glGetPointerv(%s):\n\t%f %f %f %f\ntest result:%s\n",
	get_enum_name(getfactors[i]),param[0],param[1],param[2],param[3],pass==true?"PASS":"FAIL");
    }

    for(i=0; i<num; i++)
	GL_CHECK(glDisableClientState(factors[i]));

    return pass;
}

void Sample::test()
{
    SwapBuffers();
}

int main(int argc, char **argv)
{
    Sample sample(__FILE__);

    sample.test();

    return 0;
}
