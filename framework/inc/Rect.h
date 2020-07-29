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
        Primitive();
	    void drawRect(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	    void drawRectZ(GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLfloat h);
	    void drawRectTex(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	    void drawRectNorm(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
        void drawRectNormTex(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
    };
}

#endif /*__PRIMITIVE_H__*/