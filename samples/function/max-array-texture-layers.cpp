/**
 ** @file max-array-texture-layers.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2019-05-25, create file
 ** @par TestPoints:
 **    GL_MAX_ARRAY_TEXTURE_LAYERS
 **/

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

        0.0, 0.5, 0.2, 1.0,
        0.0, 0.5, 0.2, 1.0,
        0.0, 0.5, 0.2, 1.0,

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
    GLuint norm_ob;

    GLuint VAOs; 
    GLuint VAO_bone;
    GLuint buffer_bone_ob;

    GLfloat Theta = 100.0;

    GLuint tex;
    GLuint fbo;
    GLuint fbo_slice;
///====================================================================================

void initVAO()
{
    GL_CHECK(glGenVertexArrays(1, &VAOs)); 
    GL_CHECK(glBindVertexArray(VAOs))   

    GL_CHECK(glGenBuffers(1, &buffer_bone_ob));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_bone_ob));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points_bone) + sizeof(colors_bone) + sizeof(norms_bone), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points_bone), points_bone));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points_bone), sizeof(colors_bone), colors_bone));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points_bone) + sizeof(colors_bone), sizeof(norms_bone), norms_bone));
 
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));

    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points_bone))));

    GL_CHECK(glEnableVertexAttribArray(2));
    GL_CHECK(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points_bone)+sizeof(colors_bone))));
}

void initTexture()
{
    GLint my_array_texture_layers;
    GL_CHECK(glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS , &my_array_texture_layers));
    LOGI("GL_MAX_ARRAY_TEXTURE_LAYERS = %d\n", my_array_texture_layers);

    GL_CHECK(glGenTextures(1, &tex));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, tex));
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, /*GL_RGBA32F,*/ GL_RGBA, 400, 400, my_array_texture_layers, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
}

bool setupGraphics(int width, int height)
{
    string vertexShaderPath = (string)GLSL_PATH + "max-array-texture-layers.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "max-array-texture-layers.frag";

    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    initVAO();
    initTexture();
    return true;
}
///===========================================================================================

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();

    return 0;
}

