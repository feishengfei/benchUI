/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef __ENUM_H__
#define __ENUM_H__

#ifdef API_ES
	#if API_VERSION == 11
		#include <GLES/gl.h>
		#include <GLES/glext.h>
	#elif API_VERSION == 20
		#include <GLES2/gl2.h>
		#include <GLES2/gl2ext.h>
	#elif API_VERSION == 30
		#include <GLES3/gl3.h>
		#include <GLES3/gl3ext.h>
	#elif API_VERSION == 31
		#include <GLES3/gl31.h>
		#include <GLES3/gl3ext.h>
	#elif API_VERSION == 32
		#include <GLES3/gl32.h>
		#include <GLES3/gl3ext.h>
	#endif
	#include <EGL/egl.h>
#else
	#define GL_GLEXT_PROTOTYPES
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glcorearb.h>
    #include <GL/glext.h>
#endif

#include "Platform.h"
#include <string>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#define GET_BOOL(x) (x == GL_TRUE ? "GL_TRUE" : "GL_FALSE")

#define CASE_NAME(x) case x: return #x; 

GLboolean needs_blend_color(const GLenum func);
const char* get_primitives_name(GLenum factor);
const char* get_blending_name(GLenum factor);
const char* get_error_name(GLenum factor);
const char* get_bufferbit_name(GLenum factor);
const char* get_enum_name(GLenum factor);

#if GLES_VERSION == 32
const char* get_shader_bits_enum(const GLenum func);
const char* get_barrier_bit_enum(const GLenum func);
const char* get_context_enum(const GLenum func);
#endif

#define GL_CHECK(x) \
	x; \
	{ \
	    GLenum glError = glGetError(); \
	    if(glError != GL_NO_ERROR) { \
	        LOGE("glGetError(%s)\n", get_error_name(glError)); \
	    } \
	}

#define WINDOW_W 256
#define WINDOW_H 256

#define ARRAY_NUM(x) (sizeof(x)/sizeof(x[0])) 

#endif /* __ENUM_H__ */
