/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_EmitVertex_EndPrimitive.cpp
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

///====================================================================================
    const int NumPoints_bone = 18;
    GLfloat points_bone[NumPoints_bone*3] = {

         -0.50, 0.00,  0.25,
          0.50, 0.00,  0.25,
         -0.50, -0.05, -0.25,

          0.50, 0.00,  0.25,
         -0.50, -0.05, -0.25,
          0.50, -0.05, -0.25, 

         -0.50, -0.05, -0.25,
          0.50, -0.05, -0.25, 
         -0.50, 0.75,  0.00, 

          0.50, -0.05, -0.25, 
         -0.50, 0.75,  0.00, 
          0.50, 0.75,  0.00,

         -0.50, 0.75,  0.00, 
          0.50, 0.75,  0.00,
         -0.50, 0.00,  0.25,

          0.50, 0.75,  0.00,
         -0.50, 0.00,  0.25,
          0.50, 0.00,  0.25

    };
    GLfloat colors_bone[NumPoints_bone*4] = {
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
        1.0, 0.5, 0.0, 1.0,
    };
    GLfloat norms_bone[NumPoints_bone*3] = {
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,

        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,

        0.0, 0.25, -0.75,
        0.0, 0.25, -0.75,
        0.0, 0.25, -0.75,

        0.0, 0.25, -0.75,
        0.0, 0.25, -0.75,
        0.0, 0.25, -0.75,

        0.0, 0.25, 0.75,
        0.0, 0.25, 0.75,
        0.0, 0.25, 0.75,

        0.0, 0.25, 0.75,
        0.0, 0.25, 0.75,
        0.0, 0.25, 0.75,
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

void initVBO()
{
    GL_CHECK(glGenBuffers(1, &buffer_bone_ob));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_bone_ob));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points_bone) + sizeof(colors_bone) + sizeof(norms_bone), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points_bone), points_bone));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points_bone), sizeof(colors_bone), colors_bone));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points_bone) + sizeof(colors_bone), sizeof(norms_bone), norms_bone));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


void initVAO()
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_bone_ob));
    GL_CHECK(glGenVertexArrays(1, &VAO_bone));
    GL_CHECK(glBindVertexArray(VAO_bone));
    GLuint loc1 = GL_CHECK(glGetAttribLocation(programID, "vPosition"));
    GL_CHECK(glEnableVertexAttribArray(loc1));
    GL_CHECK(glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0))); 
    GLuint loc2 = GL_CHECK(glGetAttribLocation(programID, "vColor"));
    GL_CHECK(glEnableVertexAttribArray(loc2));
    GL_CHECK(glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points_bone))));
    GLuint loc4 = GL_CHECK(glGetAttribLocation(programID, "vNorm"));
    GL_CHECK(glEnableVertexAttribArray(loc4));
    GL_CHECK(glVertexAttribPointer(loc4, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points_bone)+sizeof(colors_bone))));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_EmitVertex_EndPrimitive";
#else
    string path = "gl43_EmitVertex_EndPrimitive";
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

    programID = Shader::LoadShaders( shaders );

    initVBO();
    initVAO();
    
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
    GL_CHECK(glUniform1f(loc_theta, Theta));
    GL_CHECK(glBindVertexArray(VAO_bone));
    GL_CHECK(glDrawArrays(GL_TRIANGLES,0,NumPoints_bone));

    Theta = Theta + 0.02;
    if(Theta > 360){
        Theta = Theta - 360;
    }
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
