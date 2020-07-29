/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file gl43_texQueryLevels
 * @author Martin.li
 * @par History:
 *    A001: Martin.li, 20XX-XX-XX, Add commit
 * @
 * @par TestPoints:
 *
 */
///===================================================================================
#include "Sample.h"
#include <iostream>
using std::string;
using namespace BotsonSDK;
using namespace std;

#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))
#define W_Width 400
#define W_Height 400

///====================================================================================
    const int NumPoints = 32; // number of points 
//    GLfloat points[NumPoints*3];
    GLfloat points[4] = {0.1, 0.2, 0.3, 0.4};
    GLuint tb1;
    GLuint TransBack;
    GLuint programID;
    GLuint VAO_bone;
    GLuint buffer_bone_ob;
    GLuint texture_ob;
    GLuint texture_ob_I;
    GLuint texture_ob_U;
    GLuint texture_ob_3D;
    GLuint texture_ob_I_3D;
    GLuint texture_ob_U_3D;
    GLuint texture_ob_2DArray;
    GLuint texture_ob_I_2DArray;
    GLuint texture_ob_U_2DArray;
    GLuint texture_ob_Cube;
    GLuint texture_ob_I_Cube;
    GLuint texture_ob_U_Cube;
    GLuint exeure_ob_CubeArray;
///====================================================================================

void getdata()
{
}

GLuint LoadShaders( ShaderInfo shaders[] )
{
    ShaderInfo* entry = shaders;
    if ( shaders == NULL ) { return 0; }
    else {
        entry = shaders;
        int num_vs=0, num_fs=0, num_gs=0, num_tcs=0, num_tes=0;
        while ( entry->type != GL_NONE ) {
            switch(entry->type) {
                case GL_VERTEX_SHADER:
                    num_vs += 1;
                    break;
                case GL_FRAGMENT_SHADER:
                    num_fs += 1;
                    break;
#if (GLES_VERSION >= 32) || (GL_VER >= 43)
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
        Shader::processShader(&(entry->shader), srcPath.c_str(), entry->type);
        glAttachShader( program, entry->shader );
        ++entry;
    }

    const char* feedbackVaryings = {"rf_position"};
    GL_CHECK(glTransformFeedbackVaryings(program , 1, &feedbackVaryings, GL_INTERLEAVED_ATTRIBS/*GL_SEPARATE_ATTRIBS*/));

    GL_CHECK(glLinkProgram( program ));

    glGenTransformFeedbacks(1 , &TransBack);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, TransBack);

    GLint linked;
    glGetProgramiv( program, GL_LINK_STATUS, &linked );
    if ( !linked ) {
        GLsizei len;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

        GLchar* log = new GLchar[len+1];
        glGetProgramInfoLog( program, len, &len, log );
        printf("Shader linking failed: %s\n", log);
        delete [] log;

        for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
            glDeleteShader( entry->shader );
            entry->shader = 0;
        }
        return 0;
    }
    return program;
}

void init()
{
    GL_CHECK(glGenVertexArrays(1, &VAO_bone));
    GL_CHECK(glBindVertexArray(VAO_bone));
    GLuint loc1 = GL_CHECK(glGetAttribLocation(programID, "vPosition"));

    GL_CHECK(glGenBuffers(1, &buffer_bone_ob));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_bone_ob));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points));

    GL_CHECK(glEnableVertexAttribArray(loc1));
    GL_CHECK(glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void initTexture()
{
    const int width = 32;
    const int height = 32;
    const int depth = 32;
//*************************************Texture0*****************************************
    GLfloat image[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image[4*i] = i * 1.0 + 0.0;
        image[4*i + 1] = i * 1.0 + 0.1;
        image[4*i + 2] = i * 1.0 + 0.2;
        image[4*i + 3] = i * 1.0 + 0.3;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob));

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, image)); 
    GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));

//*************************************Texture1*****************************************
    GLint image_I[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_I[4*i] = i * 100 + 0;
        image_I[4*i + 1] = i * 100 + 10;
        image_I[4*i + 2] = i * 100 + 20;
        image_I[4*i + 3] = i * 100 + 30;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_I));

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32I, width, height, 0, GL_RGBA_INTEGER, GL_INT, image_I)); 
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0));

//*************************************Texture2*****************************************
    GLuint image_U[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_U[4*i] = i * 100 + 0;
        image_U[4*i + 1] = i * 100 + 10;
        image_U[4*i + 2] = i * 100 + 20;
        image_U[4*i + 3] = i * 100 + 30;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_U));

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32UI, width, height, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U)); 
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA32UI, width/2, height/2, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U)); 
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1));

//*************************************Texture3*****************************************
    GLfloat image_3D[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_3D[4*i] = i * 1.0 + 0.0;
        image_3D[4*i + 1] = i * 1.0 + 0.1;
        image_3D[4*i + 2] = i * 1.0 + 0.2;
        image_3D[4*i + 3] = i * 1.0 + 0.3;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_3D));    
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_3D));

    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32F, width, height, depth, 0, GL_RGBA, GL_FLOAT, image_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 1, GL_RGBA32F, width/2, height/2, depth/2, 0, GL_RGBA, GL_FLOAT, image_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 2, GL_RGBA32F, width/4, height/4, depth/4, 0, GL_RGBA, GL_FLOAT, image_3D)); 

    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAX_LEVEL, 2));


//*************************************Texture4*****************************************
//    const int width_1 = 32;
//    const int height_1 = 32;
//    const int depth_1 = 32;

    GLint image_I_3D[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_I_3D[4*i] = i * 100 + 0;
        image_I_3D[4*i + 1] = i * 100 + 10;
        image_I_3D[4*i + 2] = i * 100 + 20;
        image_I_3D[4*i + 3] = i * 100 + 30;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I_3D));    
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_I_3D));

    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32I, width, height, depth , 0, GL_RGBA_INTEGER, GL_INT, image_I_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 1, GL_RGBA32I, width/2, height/2, depth/2 , 0, GL_RGBA_INTEGER, GL_INT, image_I_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 2, GL_RGBA32I, width/4, height/4, depth/4 , 0, GL_RGBA_INTEGER, GL_INT, image_I_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 3, GL_RGBA32I, width/8, height/8, depth/8 , 0, GL_RGBA_INTEGER, GL_INT, image_I_3D)); 

    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAX_LEVEL, 3));

//*************************************Texture5*****************************************
    GLuint image_U_3D[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_U_3D[4*i] = i * 100 + 0;
        image_U_3D[4*i + 1] = i * 100 + 10;
        image_U_3D[4*i + 2] = i * 100 + 20;
        image_U_3D[4*i + 3] = i * 100 + 30;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U_3D));    
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_U_3D));

    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32UI, width, height, depth , 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_I_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 1, GL_RGBA32UI, width/2, height/2, depth/2 , 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_I_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 2, GL_RGBA32UI, width/4, height/4, depth/4 , 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_I_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 3, GL_RGBA32UI, width/8, height/8, depth/8 , 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_I_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 4, GL_RGBA32UI, width/16, height/16, depth/16 , 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_I_3D)); 

    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAX_LEVEL, 4));

//*************************************Texture6*****************************************
    GLfloat image_2DArray[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_2DArray[4*i] = i * 1.0 + 0.0;
        image_2DArray[4*i + 1] = i * 1.0 + 0.1;
        image_2DArray[4*i + 2] = i * 1.0 + 0.2;
        image_2DArray[4*i + 3] = i * 1.0 + 0.3;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_2DArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_2DArray));

    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA32F, width, height, depth, 0, GL_RGBA, GL_FLOAT, image_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32F, width/2, height/2, depth/2, 0, GL_RGBA, GL_FLOAT, image_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 2, GL_RGBA32F, width/4, height/4, depth/4, 0, GL_RGBA, GL_FLOAT, image_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 3, GL_RGBA32F, width/8, height/8, depth/8, 0, GL_RGBA, GL_FLOAT, image_2DArray)); 
//    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 4, GL_RGBA32F, width/16, height/16, depth/16, 0, GL_RGBA, GL_FLOAT, image_2DArray)); 
//    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 5, GL_RGBA32F, width/32, height/32, depth/32, 0, GL_RGBA, GL_FLOAT, image_2DArray)); 

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 3));

//*************************************Texture7*****************************************
    GLint image_I_2DArray[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_I_2DArray[4*i] = i * 100 + 0;
        image_I_2DArray[4*i + 1] = i * 100 + 10;
        image_I_2DArray[4*i + 2] = i * 100 + 20;
        image_I_2DArray[4*i + 3] = i * 100 + 30;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I_2DArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_I_2DArray));

    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA32I, width, height, depth, 0, GL_RGBA_INTEGER, GL_INT, image_I_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32I, width/2, height/2, depth/2, 0, GL_RGBA_INTEGER, GL_INT, image_I_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 2, GL_RGBA32I, width/4, height/4, depth/4, 0, GL_RGBA_INTEGER, GL_INT, image_I_2DArray)); 
//    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 3, GL_RGBA32I, width/8, height/8, depth/8, 0, GL_RGBA_INTEGER, GL_INT, image_I_2DArray)); 
//    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 4, GL_RGBA32I, width/16, height/16, depth/16, 0, GL_RGBA_INTEGER, GL_INT, image_I_2DArray)); 

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 2));

//*************************************Texture8*****************************************
    GLuint image_U_2DArray[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_U_2DArray[4*i] = i * 100 + 0;
        image_U_2DArray[4*i + 1] = i * 100 + 10;
        image_U_2DArray[4*i + 2] = i * 100 + 20;
        image_U_2DArray[4*i + 3] = i * 100 + 30;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U_2DArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_U_2DArray));

    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA32UI, width, height, depth, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32UI, width/2, height/2, depth/2, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 2, GL_RGBA32UI, width/4, height/4, depth/4, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 3, GL_RGBA32UI, width/8, height/8, depth/8, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_2DArray)); 

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 3));

//*************************************Texture9*****************************************
    GLfloat image_Cube[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_Cube[4*i] = i * 1.0 + 0.0;
        image_Cube[4*i + 1] = i * 1.0 + 0.1;
        image_Cube[4*i + 2] = i * 1.0 + 0.2;
        image_Cube[4*i + 3] = i * 1.0 + 0.3;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_Cube));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_Cube));

    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
        GL_CHECK(glTexImage2D(target, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, image_Cube)); 
        GL_CHECK(glTexImage2D(target, 1, GL_RGBA32F, width/2, height/2, 0, GL_RGBA, GL_FLOAT, image_Cube)); 
        GL_CHECK(glTexImage2D(target, 2, GL_RGBA32F, width/4, height/4, 0, GL_RGBA, GL_FLOAT, image_Cube)); 
    }

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 2));

//*************************************Texture10*****************************************
    GLint image_I_Cube[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_I_Cube[4*i] = i * 100 + 0;
        image_I_Cube[4*i + 1] = i * 100 + 10;
        image_I_Cube[4*i + 2] = i * 100 + 20;
        image_I_Cube[4*i + 3] = i * 100 + 30;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I_Cube));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_I_Cube));

    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
        GL_CHECK(glTexImage2D(target, 0, GL_RGBA32I, width, height, 0, GL_RGBA_INTEGER, GL_INT, image_I_Cube)); 
        GL_CHECK(glTexImage2D(target, 1, GL_RGBA32I, width/2, height/2, 0, GL_RGBA_INTEGER, GL_INT, image_I_Cube)); 
    }

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 1));

//*************************************Texture11****************************************
    GLuint image_U_Cube[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_U_Cube[4*i] = i * 100 + 0;
        image_U_Cube[4*i + 1] = i * 100 + 10;
        image_U_Cube[4*i + 2] = i * 100 + 20;
        image_U_Cube[4*i + 3] = i * 100 + 30;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U_Cube));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_U_Cube));

    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
        GL_CHECK(glTexImage2D(target, 0, GL_RGBA32UI, width, height, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_Cube)); 
    }

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0));


}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_texQueryLevels";
#else
    string path = "gl43_texQueryLevels";
    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
#endif
    string vertexShaderPath = path + "/vertex_shader.glsl";
    string geometryShaderPath = path + "/geometry_shader.glsl";
    string fragmentShaderPath = path + "/fragment_shader.glsl";

    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER,   vertexShaderPath.c_str() },
        { GL_GEOMETRY_SHADER, geometryShaderPath.c_str() },
        { GL_FRAGMENT_SHADER, fragmentShaderPath.c_str() },
        { GL_NONE, NULL }
    };

    programID = LoadShaders( shaders );

    init();
    initTexture();

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glViewport(0, 0, width, height));
    return true;
}

///===========================================================================================

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));

    GLuint tex0_uniform_loc = glGetUniformLocation(programID, "texUnit0");
    GL_CHECK(glUniform1i(tex0_uniform_loc, 0));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob));

    GLuint tex1_uniform_loc = glGetUniformLocation(programID, "texUnit1");
    GL_CHECK(glUniform1i(tex1_uniform_loc, 1));
    GL_CHECK(glActiveTexture(GL_TEXTURE1));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_I));

    GLuint tex2_uniform_loc = glGetUniformLocation(programID, "texUnit2");
    GL_CHECK(glUniform1i(tex2_uniform_loc, 2));
    GL_CHECK(glActiveTexture(GL_TEXTURE2));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_U));

    GLuint tex3_uniform_loc = glGetUniformLocation(programID, "texUnit3");
    GL_CHECK(glUniform1i(tex3_uniform_loc, 3));
    GL_CHECK(glActiveTexture(GL_TEXTURE3));
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_3D));

    GLuint tex4_uniform_loc = glGetUniformLocation(programID, "texUnit4");
    GL_CHECK(glUniform1i(tex4_uniform_loc, 4));
    GL_CHECK(glActiveTexture(GL_TEXTURE4));
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_I_3D));

    GLuint tex5_uniform_loc = glGetUniformLocation(programID, "texUnit5");
    GL_CHECK(glUniform1i(tex5_uniform_loc, 5));
    GL_CHECK(glActiveTexture(GL_TEXTURE5));
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_U_3D));

    GLuint tex6_uniform_loc = glGetUniformLocation(programID, "texUnit6");
    GL_CHECK(glUniform1i(tex6_uniform_loc, 6));
    GL_CHECK(glActiveTexture(GL_TEXTURE6));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_2DArray));

    GLuint tex7_uniform_loc = glGetUniformLocation(programID, "texUnit7");
    GL_CHECK(glUniform1i(tex7_uniform_loc, 7));
    GL_CHECK(glActiveTexture(GL_TEXTURE7));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_I_2DArray));

    GLuint tex8_uniform_loc = glGetUniformLocation(programID, "texUnit8");
    GL_CHECK(glUniform1i(tex8_uniform_loc, 8));
    GL_CHECK(glActiveTexture(GL_TEXTURE8));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_U_2DArray));

    GLuint tex9_uniform_loc = glGetUniformLocation(programID, "texUnit9");
    GL_CHECK(glUniform1i(tex9_uniform_loc, 9));
    GL_CHECK(glActiveTexture(GL_TEXTURE9));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_Cube));

    GLuint tex10_uniform_loc = glGetUniformLocation(programID, "texUnit10");
    GL_CHECK(glUniform1i(tex10_uniform_loc, 10));
    GL_CHECK(glActiveTexture(GL_TEXTURE10));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_I_Cube));

    GLuint tex11_uniform_loc = glGetUniformLocation(programID, "texUnit11");
    GL_CHECK(glUniform1i(tex11_uniform_loc, 11));
    GL_CHECK(glActiveTexture(GL_TEXTURE11));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_U_Cube));

    GL_CHECK(glDrawArrays(GL_POINTS,0,NumPoints)); 

/**********************************************************************************************/
    GL_CHECK(glGenBuffers(1, &tb1));
    GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tb1));
    GL_CHECK(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float)*4*4, NULL, GL_DYNAMIC_COPY));
    GL_CHECK(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tb1));

    GL_CHECK(glBeginTransformFeedback(GL_POINTS));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 4));
    GL_CHECK(glEndTransformFeedback());

    float tbv[4][4] = {0.0f};
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(tbv), tbv);
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
           cout << tbv[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}
///===========================================================================================

void Sample::test() {
    getdata();
    setupGraphics(WINDOW_W, WINDOW_H);
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    Sample::SwapBuffers();
    renderFrame();
    save2bmp(bmp_file.c_str());
}

int main(int argc, char **argv) {
#ifdef API_ES
    Sample sample(__FILE__);
#else
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
#endif
    sample.test();

    return 0;
}
