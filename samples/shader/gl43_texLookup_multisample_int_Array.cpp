/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 *
 * @file mt_texLookup_multisample_int_Array.cpp
 * @author Martin.li
 * @par History:
 *    A001: Martin.li, 20XX-XX-XX, Add commit
 * @
 * @par TestPoints:
 *
 */
///===================================================================================
#include "Sample.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))
#define W_Width 400
#define W_Height 400

///===================================================================================
    const int NumPoints_bone = 6;
    GLfloat points_bone[NumPoints_bone*3] = {

         -1.0, 1.0, 0.0,
         1.0, 1.0, 0.0,
         -1.0, -1.0, 0.0,

         1.0, 1.0, 0.0,
         -1.0, -1.0, 0.0,
         1.0, -1.0, 0.0
    };


    GLint colors_bone[NumPoints_bone*4] = {
        9, 5, 1, 10,
        9, 5, 1, 10,
        9, 5, 1, 10,

        9, 5, 1, 10,
        9, 5, 1, 10,
        9, 5, 1, 10,
    };

    GLuint program_tex;
    GLuint VAO_bone;
    GLuint buffer_bone_ob;


    GLuint texture_ob_2DMSArray;
    GLuint fbo;
    


    const int NumPoints = 32; // number of points 
    GLfloat points[NumPoints*3];
    GLfloat colors[NumPoints*4];

    GLuint program;
    GLuint VAO;
    GLuint VBO;

///====================================================================================

void getdata()
{
    GLfloat theta = -16.0;
    for(int i = 0, j = 0; i < NumPoints * 3; i += 3, j += 4){
        points[i] = theta;
        points[i+1] = 0.0;
        points[i+2] = 0.0;
        theta += 1.0;

        colors[j] = 1.0;
        colors[j+1] = 0.0;
        colors[j+2] = 0.0;
        colors[j+3] = 1.0;
    }
}        

void initVBO()
{
    GL_CHECK(glGenBuffers(1, &buffer_bone_ob));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_bone_ob));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points_bone) + sizeof(colors_bone), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points_bone), points_bone));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points_bone), sizeof(colors_bone), colors_bone));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glGenBuffers(1, &VBO));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void initVAO()
{
    GL_CHECK(glUseProgram(program_tex));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_bone_ob));
    GL_CHECK(glGenVertexArrays(1, &VAO_bone));
    GL_CHECK(glBindVertexArray(VAO_bone));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribIPointer(1, 4, GL_INT, 0, BUFFER_OFFSET(sizeof(points_bone))));

    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glEnable(GL_DEPTH_TEST)); //P97, you can use glDisable(GL_DEPTH_TEST) to close GL_DEPTH_TEST

    GL_CHECK(glUseProgram(program));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glGenVertexArrays(1, &VAO));
    GL_CHECK(glBindVertexArray(VAO));

    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points))));

    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glEnable(GL_DEPTH_TEST)); //P97, you can use glDisable(GL_DEPTH_TEST) to close GL_DEPTH_TEST
}

void initTexture()
{

    GL_CHECK(glGenTextures(1, &texture_ob_2DMSArray));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, texture_ob_2DMSArray));
    GL_CHECK(glTexStorage3DMultisample(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 4, GL_RGBA32I, 4, 4, 2, GL_TRUE));

    GL_CHECK(glGenFramebuffers(1, &fbo));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
    GL_CHECK(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_ob_2DMSArray, 0));

//    GL_CHECK(glClearColor(0.1, 0.0, 0.0, 1.0));
//    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(program_tex));
    GL_CHECK(glBindVertexArray(VAO_bone));

    static const GLenum draw_buffers[] = 
    {
        GL_COLOR_ATTACHMENT0
    };
    GL_CHECK(glDrawBuffers(1, draw_buffers));

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("\nframe buffer is not complete \n");
    else
        printf("\nframe buffer is complete \n");

    int SAMPLE_BUFFERS = -100;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &SAMPLE_BUFFERS);
    printf("\nGL_SAMPLE_BUFFERS = %d \n", SAMPLE_BUFFERS);

    GL_CHECK(glDrawArrays(GL_TRIANGLES,0,NumPoints_bone));
    GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));  
}





///===========================================================================================
bool setupGraphics(int width, int height)
{
    initVBO();

#ifdef API_ES
    string path = "es32_texLookup_multisample_int_Array";
#else
    string path = "gl43_texLookup_multisample_int_Array";
    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
#endif
    string vShader_tex_Path = path + "/vShader_tex.glsl";
    string gShader_tex_Path = path + "/gShader_tex.glsl";
    string fShader_tex_Path = path + "/fShader_tex.glsl";
    string vertexShaderPath = (string)GLSL_PATH + path + "/vertex_shader.glsl";
    string fragmentShaderPath = (string)GLSL_PATH + path + "/fragment_shader.glsl";

    printf("vShader_tex_Path = %s  \n", vShader_tex_Path.c_str());
    printf("gShader_tex_Path = %s  \n", gShader_tex_Path.c_str());
    printf("fShader_tex_Path = %s  \n", fShader_tex_Path.c_str());
    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    program = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER,   vShader_tex_Path.c_str() },
        { GL_GEOMETRY_SHADER, gShader_tex_Path.c_str() },
        { GL_FRAGMENT_SHADER, fShader_tex_Path.c_str() },
        { GL_NONE, NULL }
    };

    program_tex = Shader::LoadShaders( shaders );

    initVAO();
    initTexture();

    GL_CHECK(glEnable(GL_DEPTH_TEST)); //P97, you can use glDisable(GL_DEPTH_TEST) to close GL_DEPTH_TEST
/// GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE)); /// when you use gl_PointSize, you must enable GL_PROGRAM_POINT_SIZE
    GL_CHECK(glClearColor(1.0, 1.0, 1.0, 1.0));  /// white background
    GL_CHECK(glViewport(0, 0, width, height));
    return true;
}
///===========================================================================================

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(program));
    GL_CHECK(glBindVertexArray(VAO));


    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, texture_ob_2DMSArray)); 
    
    GL_CHECK(glDrawArrays(GL_POINTS,0,NumPoints));

    int SAMPLE_BUFFERS = -100;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &SAMPLE_BUFFERS);
    printf("\nGL_SAMPLE_BUFFERS = %d \n", SAMPLE_BUFFERS);

    int SAMPLES = -1;
    glGetIntegerv(GL_SAMPLES, &SAMPLES);
    printf("\nGL_SAMPLES = %d \n", SAMPLES);
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
