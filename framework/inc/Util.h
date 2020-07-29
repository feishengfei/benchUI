/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef UTIL_H
#define UTIL_H

#ifdef API_ES
    #define GLES_VERSION API_VERSION
    #define GL_VER 0
#endif

#ifdef API_GL
    #define GLES_VERSION 0
    #define GL_VER API_VERSION
#endif


#ifndef API_VERSION
    #error "ERROR: API_VERSION not define"
#endif

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

#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cmath>
#include <string>
#include <string.h>
#include "bmp.h"
#include "rgb.h"
#include <time.h>
#include <sys/timeb.h>
//#include "Mathematics.h"

#define WINDOW_W 256
#define WINDOW_H 256

#ifndef PI
#define PI 3.1415926535897932384
#endif /* M_PI */

using std::string;

#ifndef PROJECT_PATH
#error "PROJECT_PATH must be defined, default defined in CMakeLists.txt"
#endif

#define ARRAY_NUM(x) (sizeof(x)/sizeof(x[0]))
#define GET_BOOL(x) (x == GL_TRUE ? "GL_TRUE" : "GL_FALSE")

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

static GLboolean bool_factors[2] = {
    GL_FALSE,
    GL_TRUE
};

namespace BotsonSDK
{
    static FILE * fp_log=NULL;

    static int windowWidth;
    static int windowHeight;
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
    void save2bmp(string filename);

    void btx_init(string file);
    void btx_deinit(void);
    void log(const char* format, ...);
    char * getTime();
	int  genSphere ( int numSlices, float radius, GLfloat **vertices, GLfloat **normals,
					 GLfloat **texCoords, GLuint **indices );
    string getFileName(string file);

    #define LOG_FILE fp_log

    string getFileName(string file);

//    #define LOGE log("%s %s:%d<%s> [ERROR]:",getTime(), getFileName(__FILE__).c_str(), __LINE__, __FUNCTION__);log
//    #define LOGW log("%s %s:%d<%s> [WARN]:",getTime(), getFileName(__FILE__).c_str(), __LINE__, __FUNCTION__);log
//    #define LOGI log("%s %s:%d<%s> [INFO]:",getTime(), getFileName(__FILE__).c_str(), __LINE__, __FUNCTION__);log
//    #define LOGD log("%s %s:%d<%s> [DEBUG]:",getTime(), getFileName(__FILE__).c_str(), __LINE__, __FUNCTION__);log
//for golden data
    #define LOGE log("[ERROR] %s:%d<%s> ",getFileName(__FILE__).c_str(), __LINE__, __FUNCTION__);log
    #define LOGW log("[WARN ] %s:%d<%s> ",getFileName(__FILE__).c_str(), __LINE__, __FUNCTION__);log
    #define LOGI log("[INFO ] %s:%d<%s> ",getFileName(__FILE__).c_str(), __LINE__, __FUNCTION__);log
    #define LOGD log("[DEBUG] %s:%d<%s> ",getFileName(__FILE__).c_str(), __LINE__, __FUNCTION__);log


    GLboolean check_gl_error_(GLenum expected_error, const char *file, unsigned line);
    #define check_gl_error(expected) check_gl_error_((expected), __FILE__, __LINE__)

    #define GL_CHECK(x) \
    	x; \
    	{ \
    	    GLenum glError = glGetError(); \
    	    if(glError != GL_NO_ERROR) { \
    	        LOGE("glGetError(%s)\n", get_error_name(glError)); \
				} \
    }
}

#endif
