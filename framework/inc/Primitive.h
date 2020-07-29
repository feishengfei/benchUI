/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include "Shader.h"
#include "Enum.h"

namespace BotsonSDK
{
    class Primitive
    {
    private:
	    void drawRectCustom(GLfloat x, GLfloat y, GLfloat z, 
	    	GLfloat w, GLfloat h, bool isNorm, bool isTex);
    public:
        float *getNormal(float *vertice, int n);
        void genvertex2(int num, GLfloat *vertex, GLfloat *color, float Radius);
        Primitive();
	    void drawRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	    void drawRectZ(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h);
	    void drawRectTex(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	    void drawRectNorm(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
        void drawRectNormTex(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
        //void GBtest_draw_triangle(GBtest_Vertex3 vetex[]);
        //void GBtest_draw_quad(GBtest_Vertex3 vetex[]);
    };
}

#endif /*__PRIMITIVE_H__*/