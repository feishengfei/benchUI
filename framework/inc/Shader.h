/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#ifndef SHADER_H
#define SHADER_H

#include "Util.h"
//#include <GL/glcorearb.h>

namespace BotsonSDK
{
    typedef struct {
        GLenum       type;
        const char*  filename;
        GLuint       shader;
    } ShaderInfo;

    /**
     * \brief Functions for working with OpenGL ES shaders.
     */
    class Shader
    {
//    private:
        /**
         * \brief Load shader source from a file into memory.
         * \param[in] filename File name of the shader to load.
         * \return A character array containing the contents of the shader source file. 
         */
//        static char *loadShader(const char *filename);
    public:

        static char *loadShader(const char *filename);
        /**
         * \brief Create shader, load in source, compile, and dump debug as necessary.
         *
         * Loads the OpenGL ES Shading Language code into memory.
         * Creates a shader using with the required shaderType using glCreateShader(shaderType) and then compiles it using glCompileShader.
         * The output from the compilation is checked for success and a log of the compilation errors is printed in the case of failure.
         * \param[out] shader The shader ID of the newly compiled shader.
         * \param[in] filename Filename of a file containing OpenGL ES SL source code.
         * \param[in] shaderType Passed to glCreateShader to define the type of shader being processed. Must be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
         */
        static void processShader(GLuint *shader, const char *filename, GLint shaderType);

        static GLint CreateProgram(const char *vertex, const char *frag);
        
        static GLuint LoadShaders( ShaderInfo shaders[] );
        static GLuint loadShaderFromString (GLenum type, const char *shaderSrc);
        static GLuint createProgramFromString ( const char *vertShaderSrc, const char *fragShaderSrc );
        static GLuint createProgramFromString ( const char *vertShaderSrc, const char *geomShaderSrc, const char *fragShaderSrc );
        static GLuint createProgramFromString ( const char *vertShaderSrc, const char *tcShaderSrc, const char *teShaderSrc, const char *fragShaderSrc );
        static GLuint createProgramFromString ( const char *vertShaderSrc, const char *tcShaderSrc, const char *fragShaderSrc, int i);
    };
}

#endif /* SHADER_H */
