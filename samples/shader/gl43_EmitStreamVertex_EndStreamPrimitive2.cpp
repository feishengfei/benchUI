/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_EmitStreamVertex_EndStreamPrimitive
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
    const int NumPoints_bone = 18;
    GLuint tb[2]; 
    GLuint tb1; 
    GLuint tb2;
    GLuint TransBack;
    GLfloat points_bone[NumPoints_bone*3] = {
         0.5, 0.5, 0.0,
         0.5, -0.5, 0.0,
         -0.5, -0.5, 0.0,
         -0.5, 0.5, 0.0
    };

    GLuint programID;
    GLuint loc_theta;
    GLuint VAO;
    GLuint norm_ob;
    
    GLuint VAO_bone;
    GLuint buffer_bone_ob;

    GLfloat Theta = 60.0;
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

    const char* feedbackVaryings[] = {"rf_position", "gl_NextBuffer", "lf_position"};
    GL_CHECK(glTransformFeedbackVaryings(program , 3, feedbackVaryings, GL_INTERLEAVED_ATTRIBS));
        
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
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points_bone), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points_bone), points_bone));

    GL_CHECK(glEnableVertexAttribArray(loc1));
    GL_CHECK(glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0))); 
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_EmitStreamVertex_EndStreamPrimitive";
#else
    string path = "gl43_EmitStreamVertex_EndStreamPrimitive";
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

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(loc_theta = glGetUniformLocation(programID, "theta"));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glViewport(0, 0, width, height));
    return true;
}
///===========================================================================================

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
/*********************************************************************************************/
    init();
    GL_CHECK(glGenBuffers(1, &tb1));
    GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tb1));
    GL_CHECK(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float)*4*4, NULL, GL_DYNAMIC_COPY));
    GL_CHECK(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tb1));

    init();
    GL_CHECK(glGenBuffers(1, &tb2));
    GL_CHECK(glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tb2));
    GL_CHECK(glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(float)*4*4, NULL, GL_DYNAMIC_COPY));
    GL_CHECK(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, tb2));

        
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, TransBack);
        GL_CHECK(glBeginTransformFeedback(GL_POINTS));
        GL_CHECK(glDrawArrays(GL_POINTS, 0, 4));
        GL_CHECK(glEndTransformFeedback());


        float tbv[4][4] = {0.0f};
        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tb1);
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

        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tb2);
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
