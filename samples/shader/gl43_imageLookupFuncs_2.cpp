/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_imageLookupFuncs_2.cpp
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
    const int NumPoints = 32; // number of points 
    GLfloat points[NumPoints*3];
    GLfloat colors[NumPoints*4];
    GLuint VAO;
    GLuint programID;
    GLuint VBO;
    GLuint texture_ob_Cube;
    GLuint texture_ob_I_Cube;
    GLuint texture_ob_U_Cube;
    GLuint texture_ob_2DArray;
    GLuint texture_ob_I_2DArray;
    GLuint texture_ob_U_2DArray;


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
    GL_CHECK(glGenBuffers(1, &VBO));
    if(VBO <= 0) {
        LOGE("VBO = %d, VBO is illegel! \n", VBO);
    }
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void initVAO()
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_CHECK(glGenVertexArrays(1, &VAO));
    if(VAO <= 0) {
        LOGE("VAO = %d, VAO is illegel! \n", VAO);
    }
    GL_CHECK(glBindVertexArray(VAO));
    GLuint loc1 = GL_CHECK(glGetAttribLocation(programID, "vPosition"));
    if(loc1 < 0) {
        LOGE("loc1 = %d, loc1 is illegel! \n", loc1);
    }
    GL_CHECK(glEnableVertexAttribArray(loc1));
    GL_CHECK(glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GLuint loc2 = GL_CHECK(glGetAttribLocation(programID, "vColor"));
    if(loc2 < 0) {
        LOGE("loc2 = %d, loc2 is illegel! \n", loc2);
    }
    GL_CHECK(glEnableVertexAttribArray(loc2));
    GL_CHECK(glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points))));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void initTexture()
{
    const int width = 4;
    const int height = 4;
    const int depth = 4;
    const int width_1 = 2;
    const int height_1 = 2;
    const int depth_1 = 2;



    GLfloat image_Cube[width * height];
    for(int i = 0; i < width * height; i++){
        image_Cube[i] = i * 1.0 + 0.0;
    }

    GL_CHECK(glGenTextures(1, &texture_ob_Cube));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_Cube));

    GL_CHECK(glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_R32F, width, height));
    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;

          GL_CHECK(glTexSubImage2D(target, 0, 0, 0, width, height, GL_RED, GL_FLOAT, image_Cube));
    }

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
    GL_CHECK(glBindImageTexture(0, texture_ob_Cube, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32F));




    GLint image_I_Cube[width * height];
    for(int i = 0; i < width * height; i++){
        image_I_Cube[i] = i * 100 + 0;
    }

    GL_CHECK(glGenTextures(1, &texture_ob_I_Cube));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_I_Cube));

    GL_CHECK(glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_R32I, width, height));
    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;

          GL_CHECK(glTexSubImage2D(target, 0, 0, 0, width, height, GL_RED_INTEGER, GL_INT, image_I_Cube));
    }

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

    GL_CHECK(glBindImageTexture(1, texture_ob_I_Cube, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32I));



    GLuint image_U_Cube[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_U_Cube[i] = i * 100 + 0;
    }

    GL_CHECK(glGenTextures(1, &texture_ob_U_Cube));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_U_Cube));

    GL_CHECK(glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_R32UI, width, height));
    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;

          GL_CHECK(glTexSubImage2D(target, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, image_U_Cube));
    }

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

    GL_CHECK(glBindImageTexture(2, texture_ob_U_Cube, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI));




    GLfloat image_2DArray[width * height * depth];
    for(int i = 0; i < width * height * depth; i++){
        image_2DArray[i] = i * 1.0 + 0.0;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_2DArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_2DArray));

    GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_R32F, width, height, depth));
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, depth, GL_RED, GL_FLOAT, image_2DArray));
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

    GL_CHECK(glBindImageTexture(3, texture_ob_2DArray, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32F));



    GLint image_I_2DArray[width * height * depth];
    for(int i = 0; i < width * height * depth; i++){
        image_I_2DArray[i] = i * 100 + 0;
    }


    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I_2DArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_I_2DArray));

    GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_R32I, width, height, depth));
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, depth, GL_RED_INTEGER, GL_INT, image_I_2DArray));
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

    GL_CHECK(glBindImageTexture(4, texture_ob_I_2DArray, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32I));




    GLuint image_U_2DArray[width * height * depth];
    for(int i = 0; i < width * height * depth; i++){
        image_U_2DArray[i] = i * 100 + 0;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U_2DArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_U_2DArray));

    GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_R32UI, width, height, depth));
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, depth, GL_RED_INTEGER, GL_UNSIGNED_INT, image_U_2DArray));

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

    GL_CHECK(glBindImageTexture(5, texture_ob_U_2DArray, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI));
}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_imageLookupFuncs_2";
#else
    string path = "gl43_imageLookupFuncs_2";
    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
#endif
    string vertexShaderPath = (string)GLSL_PATH + path + "/vertex_shader.glsl";
    string fragmentShaderPath = (string)GLSL_PATH + path + "/fragment_shader.glsl";

    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    initVBO();
    initVAO();
    initTexture();
    GL_CHECK(glEnable(GL_DEPTH_TEST)); //P97, you can use glDisable(GL_DEPTH_TEST) to close GL_DEPTH_TEST
/// GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE)); /// when you use gl_PointSize, you must enable GL_PROGRAM_POINT_SIZE
    GL_CHECK(glClearColor(1.0, 1.0, 1.0, 1.0));
    GL_CHECK(glViewport(0, 0, width, height));
    return true;
}
///===========================================================================================

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAO));
    GL_CHECK(glDrawArrays(GL_POINTS,0,NumPoints));
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
