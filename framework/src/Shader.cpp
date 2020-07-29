
/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

#include "Shader.h"
#include "Platform.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace BotsonSDK
{
#if (GLES_VERSION > 11)|| (GL_VER >= 20)
    void Shader::processShader(GLuint *shader, const char *filename, GLint shaderType)
    {  
        const char *strings[1] = { NULL };

        /* Create shader and load into GL. */
        *shader = GL_CHECK(glCreateShader(shaderType));
        strings[0] = loadShader(filename);
        GL_CHECK(glShaderSource(*shader, 1, strings, NULL));

        /* Clean up shader source. */
        free((void *)(strings[0]));
        strings[0] = NULL;

        /* Try compiling the shader. */
        GL_CHECK(glCompileShader(*shader));
        GLint status;
        GL_CHECK(glGetShaderiv(*shader, GL_COMPILE_STATUS, &status));

        /* Dump debug info (source and log) if compilation failed. */
        if(status != GL_TRUE) 
        {
            GLint length;
            char *debugSource = NULL;
            char *errorLog = NULL;

            /* Get shader source. */
            GL_CHECK(glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length));
            debugSource = (char *)malloc(length);
            GL_CHECK(glGetShaderSource(*shader, length, NULL, debugSource));
            LOGE("Debug source START:\n%s\nDebug source END\n\n", debugSource);
            free(debugSource);

            /* Now get the info log. */
            GL_CHECK(glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &length));
            errorLog = (char *)malloc(length);
            GL_CHECK(glGetShaderInfoLog(*shader, length, NULL, errorLog));
            LOGE("Log START:\n%s\nLog END\n\n", errorLog);
            free(errorLog);

            LOGE("Compilation FAILED!\n\n");
            exit(1);
        }
    }

    char* Shader::loadShader(const char *filename)
    {
        int versionMap[] = {
        //OpenGL version, shader version;
            //10, 110,
            //21, 120,
            //30, 130,
            //31, 140,
            //32, 150,
            //33, 330,
            //40, 400,
            //41, 410,
            //42, 420,
            //43, 430
                10, 430,
                21, 430,
                30, 430,
                31, 430,
                32, 430,
                33, 430,
                40, 430,
                41, 430,
                42, 430,
                43, 430
            };

        FILE *file = fopen(filename, "rb");
        if(file == NULL)
        {
            LOGE("Cannot read file '%s'\n", filename);
            exit(1);
        }
        /* Seek end of file. */
        fseek(file, 0, SEEK_END);
        /* Record the size of the file for memory allocation. */
        long length = ftell(file);
        /* Seek start of file again. */
        fseek(file, 0, SEEK_SET); 
        char *shader = (char *)calloc(length + 1, sizeof(char));
        if(shader == NULL)
        {
            LOGE("Out of memory at %s:%i\n", __FILE__, __LINE__);
            exit(1);
        }
        /* Read in the file */
        size_t numberOfBytesRead = fread(shader, sizeof(char), length, file);
        if (numberOfBytesRead != length) 
        {
            LOGE("Error reading %s (read %d of %d)", filename, numberOfBytesRead, length);
            exit(1);
        }
        shader[length] = '\0';
        string typecfg = (string)TYPE;
        if(0 == typecfg.compare("shader")) {
            string shaderStr = shader;
//        #if (GL_VER > 33)
            #ifdef API_ES
                stringstream replaceSt;
                int api_version = API_VERSION * 10;
                replaceSt << api_version;
                string replaceStr1 = replaceSt.str();
                string replaceStr2 = " es";
                string replaceStr3 = " ";
                string replaceStr = replaceStr3 + replaceStr1 + replaceStr2;
            #else 

  //              stringstream replaceSt;
  //              int api_version = API_VERSION * 10;
  //              replaceSt << api_version;
  //              string replaceStr2 = replaceSt.str();
  //              string replaceStr1 = " ";
  //              string replaceStr = replaceStr1 + replaceStr2;

                int shader_version;
                string replaceStr;
                for(int i = 0;  i < sizeof(versionMap); i = i+2)
                {
                    if(API_VERSION == versionMap[i])
                        shader_version = versionMap[i+1];
                    else
                        continue;
                    stringstream replaceSt;
                    replaceSt << shader_version;
                    string replaceStr2 = replaceSt.str();
                    string replaceStr1 = " ";
                    replaceStr = replaceStr1 + replaceStr2 + replaceStr1 + "core";
                }
            #endif
                string findStr = "version";
                int pos = shaderStr.find(findStr);
                if(pos != -1)
                {
                    shaderStr.replace(pos + 7, 0, replaceStr);
                }
                char* shaderC = new char[strlen(shaderStr.c_str()) + 1];
                strcpy(shaderC, shaderStr.c_str());
                fclose(file);
                return shaderC;
        } else {
            fclose(file);
            return shader;
        }
    }


    GLuint Shader::loadShaderFromString(GLenum type, const char *shaderSrc) {
        GLuint shader;
        GLint  compiled;

        shader = glCreateShader(type);
        if (shader == 0) {
            return 0;
        }

        glShaderSource(shader, 1, &shaderSrc, NULL);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 1) {
                char *infoLog = (char *)malloc(sizeof(char) * infoLen);
                glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
                LOGE("Error compiling shader:\n%s\n", infoLog);

                free(infoLog);
            }
            glDeleteShader(shader);

            return 0;
        }
        return shader;
    }

    GLuint Shader::createProgramFromString ( const char *vertShaderSrc, const char *fragShaderSrc ) {
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint programObject;
        GLint  linked;

        vertexShader = loadShaderFromString(GL_VERTEX_SHADER, vertShaderSrc);
        if (vertexShader == 0) {
            return 0;
        }

        fragmentShader = loadShaderFromString(GL_FRAGMENT_SHADER, fragShaderSrc);
        if (fragmentShader == 0) {
            glDeleteShader(vertexShader);
            return 0;
        }

        programObject = glCreateProgram();
        if (programObject == 0) {
            return 0;
        }

        glAttachShader(programObject, vertexShader);
        glAttachShader(programObject, fragmentShader);
        glLinkProgram(programObject);
        glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

        if (!linked) {
            GLint infoLen = 0;
            glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 1) {
                char *infoLog = (char *)malloc(sizeof(char) * infoLen);
                glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
                LOGI("Error linking program:\n%s\n", infoLog);

                free(infoLog);
            }
            glDeleteProgram(programObject);
            return 0;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return programObject;
    }

    GLuint Shader::createProgramFromString ( const char *vertShaderSrc, const char *geomShaderSrc, const char *fragShaderSrc ) {
        GLuint vertexShader;
        GLuint geometryShader;
        GLuint fragmentShader;
        GLuint programObject;
        GLint  linked;

        vertexShader = loadShaderFromString(GL_VERTEX_SHADER, vertShaderSrc);
        if (vertexShader == 0) {
            return 0;
        }

        geometryShader = loadShaderFromString(GL_GEOMETRY_SHADER, geomShaderSrc);
        if (geometryShader == 0) {
            return 0;
        }

        fragmentShader = loadShaderFromString(GL_FRAGMENT_SHADER, fragShaderSrc);
        if (fragmentShader == 0) {
            glDeleteShader(vertexShader);
            return 0;
        }

        programObject = glCreateProgram();
        if (programObject == 0) {
            return 0;
        }

        glAttachShader(programObject, vertexShader);
        glAttachShader(programObject, geometryShader);
        glAttachShader(programObject, fragmentShader);
        glLinkProgram(programObject);
        glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

        if (!linked) {
            GLint infoLen = 0;
            glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 1) {
                char *infoLog = (char *)malloc(sizeof(char) * infoLen);
                glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
                LOGI("Error linking program:\n%s\n", infoLog);

                free(infoLog);
            }
            glDeleteProgram(programObject);
            return 0;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);

        return programObject;
    }

    GLuint Shader::createProgramFromString ( const char *vertShaderSrc, const char *tcShaderSrc, const char *teShaderSrc, const char *fragShaderSrc ) {
        GLuint vertexShader;
        GLuint tcShader;
        GLuint teShader;
        GLuint fragmentShader;
        GLuint programObject;
        GLint  linked;

        vertexShader = loadShaderFromString(GL_VERTEX_SHADER, vertShaderSrc);
        if (vertexShader == 0) {
            return 0;
        }

        tcShader = loadShaderFromString(GL_TESS_CONTROL_SHADER, tcShaderSrc);
        if (tcShader == 0) {
            return 0;
        }

        teShader = loadShaderFromString(GL_TESS_EVALUATION_SHADER, teShaderSrc);
        if (tcShader == 0) {
            return 0;
        }

        fragmentShader = loadShaderFromString(GL_FRAGMENT_SHADER, fragShaderSrc);
        if (fragmentShader == 0) {
            glDeleteShader(vertexShader);
            return 0;
        }

        programObject = glCreateProgram();
        if (programObject == 0) {
            return 0;
        }

        glAttachShader(programObject, vertexShader);
        glAttachShader(programObject, tcShader);
        glAttachShader(programObject, teShader);
        glAttachShader(programObject, fragmentShader);
        glLinkProgram(programObject);
        glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

        if (!linked) {
            GLint infoLen = 0;
            glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 1) {
                char *infoLog = (char *)malloc(sizeof(char) * infoLen);
                glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
                LOGI("Error linking program:\n%s\n", infoLog);

                free(infoLog);
            }
            glDeleteProgram(programObject);
            return 0;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(tcShader);
        glDeleteShader(teShader);
        glDeleteShader(fragmentShader);

        return programObject;
    }

    GLuint Shader::createProgramFromString ( const char *vertShaderSrc, const char *tcShaderSrc, const char *fragShaderSrc, int i ) {
        GLuint vertexShader;
        GLuint tcShader;
        GLuint fragmentShader;
        GLuint programObject;
        GLint  linked;

        vertexShader = loadShaderFromString(GL_VERTEX_SHADER, vertShaderSrc);
        if (vertexShader == 0) {
            return 0;
        }

        tcShader = loadShaderFromString(GL_TESS_CONTROL_SHADER, tcShaderSrc);
        if (tcShader == 0) {
            return 0;
        }

        fragmentShader = loadShaderFromString(GL_FRAGMENT_SHADER, fragShaderSrc);
        if (fragmentShader == 0) {
            glDeleteShader(vertexShader);
            return 0;
        }

        programObject = glCreateProgram();
        if (programObject == 0) {
            return 0;
        }

        glAttachShader(programObject, vertexShader);
        glAttachShader(programObject, tcShader);
        glAttachShader(programObject, fragmentShader);
        glLinkProgram(programObject);
        glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

        if (!linked) {
            GLint infoLen = 0;
            glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 1) {
                char *infoLog = (char *)malloc(sizeof(char) * infoLen);
                glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
                LOGI("Error linking program:\n%s\n", infoLog);

                free(infoLog);
            }
            glDeleteProgram(programObject);
            return 0;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(tcShader);
        glDeleteShader(fragmentShader);

        return programObject;
    }

    GLint Shader::CreateProgram(const char *vertex, const char *frag)
    {
        GLuint vertexID=-1, fragmentID=-1;
        GLint ID;

        processShader(&vertexID, vertex, GL_VERTEX_SHADER);
        processShader(&fragmentID, frag, GL_FRAGMENT_SHADER);
        ID = GL_CHECK(glCreateProgram());
        if (!ID) 
        {
            printf("Could not create program.");
            return -1;
        }
        GL_CHECK(glAttachShader(ID, vertexID));
        GL_CHECK(glAttachShader(ID, fragmentID));
        GL_CHECK(glLinkProgram(ID));

        GLint linked;
        glGetProgramiv(ID, GL_LINK_STATUS, &linked );
        if ( !linked ) {
            GLsizei len;
            glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &len );

            GLchar* linklog = new GLchar[len+1];
            glGetProgramInfoLog(ID, len, &len, linklog );
            printf("Shader linking failed: %s\n", linklog);
            delete [] linklog;

            glDeleteShader(fragmentID);
            glDeleteShader(vertexID);
            
            return -1;

        }
        return ID;
    }


    GLuint Shader::LoadShaders( ShaderInfo shaders[] )
    {
        ShaderInfo* entry = shaders;
        if ( shaders == NULL ) { return 0; }
        else {
            entry = shaders;
            int num_vs=0, num_fs=0, num_gs=0, num_tcs=0, num_tes=0, num_cs=0;
            while ( entry->type != GL_NONE ) {
                switch(entry->type) {
                case GL_VERTEX_SHADER:
                    num_vs += 1;
                    break;
                case GL_FRAGMENT_SHADER:
                    num_fs += 1;
                    break;
#if (GLES_VERSION >= 31) || (GL_VER >= 43)
                    case GL_COMPUTE_SHADER:
                        num_cs += 1;
                        break;
#elif (GLES_VERSION >= 32) || (GL_VER >= 43)
                    case GL_GEOMETRY_SHADER:
                        num_gs += 1;
                        break;
                    case GL_TESS_CONTROL_SHADER:
                        num_tcs += 1;
                        break;
                    case GL_TESS_EVALUATION_SHADER:
                        num_tes += 1;
                        break;
#endif
                    default:
                        break;
                }
                entry++;
            }
            if(num_vs != 1 && num_fs != 1) { 
                printf("Number of vertex and fragment shader should be 1, num_vs = %d, num_fs = %d.\n", num_vs, num_fs);
                return 0;
            }
            if(num_gs > 1) { 
                printf("Use geometry shader.\n");
                printf("Number of geometry shader should be 1, num_gs = %d.\n", num_gs);
                return 0;
            }
            if(num_tcs + num_tes != 0) {
                printf("Use tesslation shader.\n");
                if(num_vs != 1 && num_fs != 1) {
                    printf("Number of vertex and fragment shader should be 1, num_tcs = %d, num_tes = %d.\n", num_tcs, num_tes); 
                    return 0;
                }
            }
        }
    
        GLuint program = glCreateProgram();

        entry = shaders;
        while ( entry->type != GL_NONE ) {
            string srcPath = (string)GLSL_PATH + entry->filename;
            processShader(&(entry->shader), srcPath.c_str(), entry->type);
            glAttachShader( program, entry->shader );
            ++entry;
        }
       
        glLinkProgram( program );

        GLint linked;
        glGetProgramiv( program, GL_LINK_STATUS, &linked );
        if ( !linked ) {
            GLsizei len;
            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

            GLchar* linklog = new GLchar[len+1];
            glGetProgramInfoLog( program, len, &len, linklog );
            printf("Shader linking failed: %s\n", linklog);
            delete [] linklog;

            for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
                glDeleteShader( entry->shader );
                entry->shader = 0;
            }
            
            return 0;
        }

        return program;
    }
#endif
}
