/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_texLookupFuncs_CubeArray.cpp
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

    GLuint texture_ob_CubeArray;
    GLuint texture_ob_I_CubeArray;
    GLuint texture_ob_U_CubeArray;
    GLuint texture_ob_CubeArrayShadow;
    GLuint texture_ob_Buffer;
    GLuint texture_ob_I_Buffer;
    GLuint texture_ob_U_Buffer;

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

    GLfloat image_CubeArray[width * height * 12 * 4];
    for(int i = 0; i < width * height * 12; i++){
        image_CubeArray[4*i] = i * 1.0 + 0.0;
        image_CubeArray[4*i + 1] = i * 1.0 + 0.1;
        image_CubeArray[4*i + 2] = i * 1.0 + 0.2;
        image_CubeArray[4*i + 3] = i * 1.0 + 0.3;
    }

    GLfloat image_CubeArray1[width_1 * height_1 * 12 *4];
    for(int i = 0; i < width_1 * height_1 * 12; i++){
        image_CubeArray1[4*i] = i * 1.0 + 0.0 +0.01;
        image_CubeArray1[4*i + 1] = i * 1.0 + 0.1 + 0.01;
        image_CubeArray1[4*i + 2] = i * 1.0 + 0.2 + 0.01;
        image_CubeArray1[4*i + 3] = i * 1.0 + 0.3 + 0.01;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_CubeArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, texture_ob_CubeArray));

    GL_CHECK(glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_RGBA32F, width, height, 12, 0, GL_RGBA, GL_FLOAT, image_CubeArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 1, GL_RGBA32F, width_1, height_1, 12, 0, GL_RGBA, GL_FLOAT, image_CubeArray1)); 

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0));

    GLint image_I_CubeArray[width * height * 12 * 4];
    for(int i = 0; i < width * height * 12; i++){
        image_I_CubeArray[4*i] = i * 100 + 0;
        image_I_CubeArray[4*i + 1] = i * 100 + 10;
        image_I_CubeArray[4*i + 2] = i * 100 + 20;
        image_I_CubeArray[4*i + 3] = i * 100 + 30;
    }

    GLint image_I_CubeArray1[width_1 * height_1 * 12 * 4];
    for(int i = 0; i < width_1 * height_1 * 12; i++){
        image_I_CubeArray1[4*i] = i * 100 + 0 +1;
        image_I_CubeArray1[4*i + 1] = i * 100 + 10 + 1;
        image_I_CubeArray1[4*i + 2] = i * 100 + 20 + 1;
        image_I_CubeArray1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I_CubeArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, texture_ob_I_CubeArray));

    GL_CHECK(glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_RGBA32I, width, height, 12, 0, GL_RGBA_INTEGER, GL_INT, image_I_CubeArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 1, GL_RGBA32I, width_1, height_1, 12, 0, GL_RGBA_INTEGER, GL_INT, image_I_CubeArray1)); 

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0));

    GLuint image_U_CubeArray[width * height * 12 * 4];
    for(int i = 0; i < width * height * 12; i++){
        image_U_CubeArray[4*i] = i * 100 + 0;
        image_U_CubeArray[4*i + 1] = i * 100 + 10;
        image_U_CubeArray[4*i + 2] = i * 100 + 20;
        image_U_CubeArray[4*i + 3] = i * 100 + 30;
    }

    GLuint image_U_CubeArray1[width_1 * height_1 * 12 * 4];
    for(int i = 0; i < width_1 * height_1 * 12; i++){
        image_U_CubeArray1[4*i] = i * 100 + 0 +1;
        image_U_CubeArray1[4*i + 1] = i * 100 + 10 + 1;
        image_U_CubeArray1[4*i + 2] = i * 100 + 20 + 1;
        image_U_CubeArray1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U_CubeArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, texture_ob_U_CubeArray));

    GL_CHECK(glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_RGBA32UI, width, height, 12, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_CubeArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 1, GL_RGBA32UI, width_1, height_1, 12, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_CubeArray1)); 

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0));

    GLfloat image_CubeArrayShadow[width * height * 12];
    for(int i = 0; i < width * height * 12; i++){
        image_CubeArrayShadow[i] = i * 0.01 + 0.00;
    }

    GLfloat image_CubeArrayShadow1[width_1 * height_1 * 12];
    for(int i = 0; i < width_1 * height_1 * 12; i++){
        image_CubeArrayShadow1[i] = i * 0.01 + 0.001;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_CubeArrayShadow));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, texture_ob_CubeArrayShadow));

    GL_CHECK(glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, GL_DEPTH_COMPONENT32F, width, height, 12, 0, GL_DEPTH_COMPONENT, GL_FLOAT, image_CubeArrayShadow)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 1, GL_DEPTH_COMPONENT32F, width_1, height_1, 12, 0, GL_DEPTH_COMPONENT, GL_FLOAT, image_CubeArrayShadow1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAX_LEVEL, 1));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0));

    GLfloat image_Buffer[width * height];
    for(int i = 0; i < width * height; i++){
        image_Buffer[i] = i * 1.0 + 0.0;
    }
    GLuint buffer_ob_Texture;
    GL_CHECK(glGenBuffers(1, &buffer_ob_Texture));
    GL_CHECK(glBindBuffer(GL_TEXTURE_BUFFER, buffer_ob_Texture));
    GL_CHECK(glBufferData(GL_TEXTURE_BUFFER, width * height * sizeof(int), image_Buffer, GL_STATIC_DRAW));

    GL_CHECK(glGenTextures(1, &texture_ob_Buffer));
    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, texture_ob_Buffer));
    GL_CHECK(glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, buffer_ob_Texture));

    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_TEXTURE_BUFFER, 0));

    GLint image_I_Buffer[width * height];
    for(int i = 0; i < width * height; i++){
        image_I_Buffer[i] = i * 100 + 0;
    }
    GLuint buffer_ob_I_Texture;
    GL_CHECK(glGenBuffers(1, &buffer_ob_I_Texture));
    GL_CHECK(glBindBuffer(GL_TEXTURE_BUFFER, buffer_ob_I_Texture));
    GL_CHECK(glBufferData(GL_TEXTURE_BUFFER, width * height * sizeof(int), image_I_Buffer, GL_STATIC_DRAW));

    GL_CHECK(glGenTextures(1, &texture_ob_I_Buffer));
    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, texture_ob_I_Buffer));
    GL_CHECK(glTexBuffer(GL_TEXTURE_BUFFER, GL_R32I, buffer_ob_I_Texture));

    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_TEXTURE_BUFFER, 0));

    GLuint image_U_Buffer[width * height];
    for(int i = 0; i < width * height; i++){
        image_U_Buffer[i] = i * 100 + 0;
    }
    GLuint buffer_ob_U_Texture;
    GL_CHECK(glGenBuffers(1, &buffer_ob_U_Texture));
    GL_CHECK(glBindBuffer(GL_TEXTURE_BUFFER, buffer_ob_U_Texture));
    GL_CHECK(glBufferData(GL_TEXTURE_BUFFER, width * height * sizeof(int), image_U_Buffer, GL_STATIC_DRAW));

    GL_CHECK(glGenTextures(1, &texture_ob_U_Buffer));
    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, texture_ob_U_Buffer));
    GL_CHECK(glTexBuffer(GL_TEXTURE_BUFFER, GL_R32UI, buffer_ob_U_Texture));

    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_TEXTURE_BUFFER, 0));
}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_texLookupFuncs_CubeArray";
#else
    string path = "gl43_texLookupFuncs_CubeArray";
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

    GLuint tex0_uniform_loc = glGetUniformLocation(programID, "texUnit0");
    GL_CHECK(glUniform1i(tex0_uniform_loc, 0));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, texture_ob_CubeArray));

    GLuint tex1_uniform_loc = glGetUniformLocation(programID, "texUnit1");
    GL_CHECK(glUniform1i(tex1_uniform_loc, 1));
    GL_CHECK(glActiveTexture(GL_TEXTURE1));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, texture_ob_I_CubeArray));

    GLuint tex2_uniform_loc = glGetUniformLocation(programID, "texUnit2");
    GL_CHECK(glUniform1i(tex2_uniform_loc, 2));
    GL_CHECK(glActiveTexture(GL_TEXTURE2));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, texture_ob_U_CubeArray));

    GLuint tex3_uniform_loc = glGetUniformLocation(programID, "texUnit3");
    GL_CHECK(glUniform1i(tex3_uniform_loc, 3));
    GL_CHECK(glActiveTexture(GL_TEXTURE3));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, texture_ob_CubeArrayShadow));

    GLuint tex4_uniform_loc = glGetUniformLocation(programID, "texUnit4");
    GL_CHECK(glUniform1i(tex4_uniform_loc, 4));
    GL_CHECK(glActiveTexture(GL_TEXTURE4));
    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, texture_ob_Buffer));

    GLuint tex5_uniform_loc = glGetUniformLocation(programID, "texUnit5");
    GL_CHECK(glUniform1i(tex5_uniform_loc, 5));
    GL_CHECK(glActiveTexture(GL_TEXTURE5));
    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, texture_ob_I_Buffer));

    GLuint tex6_uniform_loc = glGetUniformLocation(programID, "texUnit6");
    GL_CHECK(glUniform1i(tex6_uniform_loc, 6));
    GL_CHECK(glActiveTexture(GL_TEXTURE6));
    GL_CHECK(glBindTexture(GL_TEXTURE_BUFFER, texture_ob_U_Buffer));

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

