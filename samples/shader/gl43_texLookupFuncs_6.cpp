/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_texLookupFuncs_6.cpp
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
    GLuint texture_ob_CubeArray;

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
    GL_CHECK(glGenBuffers(1, &VBO));
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


    GLfloat image[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image[4*i] = i * 1.0 + 0.0;
        image[4*i + 1] = i * 1.0 + 0.1;
        image[4*i + 2] = i * 1.0 + 0.2;
        image[4*i + 3] = i * 1.0 + 0.3;
    }

    GLfloat image1[width_1 * height_1 * 4];
    for(int i = 0; i < width_1 * height_1; i++){
        image1[4*i] = i * 1.0 + 0.0 +0.01;
        image1[4*i + 1] = i * 1.0 + 0.1 + 0.01;
        image1[4*i + 2] = i * 1.0 + 0.2 + 0.01;
        image1[4*i + 3] = i * 1.0 + 0.3 + 0.01;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob));

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, image)); 
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, width_1, height_1, 0, GL_RGBA, GL_FLOAT, image1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

    GLint image_I[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_I[4*i] = i * 100 + 0;
        image_I[4*i + 1] = i * 100 + 10;
        image_I[4*i + 2] = i * 100 + 20;
        image_I[4*i + 3] = i * 100 + 30;
    }

    GLint image_I1[width_1 * height_1 * 4];
    for(int i = 0; i < width_1 * height_1; i++){
        image_I1[4*i] = i * 100 + 0 + 1;
        image_I1[4*i + 1] = i * 100 + 10 + 1;
        image_I1[4*i + 2] = i * 100 + 20 + 1;
        image_I1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_I));

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32I, width, height, 0, GL_RGBA_INTEGER, GL_INT, image_I)); 
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA32I, width_1, height_1, 0, GL_RGBA_INTEGER, GL_INT, image_I1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

    GLuint image_U[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_U[4*i] = i * 100 + 0;
        image_U[4*i + 1] = i * 100 + 10;
        image_U[4*i + 2] = i * 100 + 20;
        image_U[4*i + 3] = i * 100 + 30;
    }

    GLuint image_U1[width_1 * height_1 * 4];
    for(int i = 0; i < width_1 * height_1; i++){
        image_U1[4*i] = i * 100 + 0 + 1;
        image_U1[4*i + 1] = i * 100 + 10 + 1;
        image_U1[4*i + 2] = i * 100 + 20 + 1;
        image_U1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_U));

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32UI, width, height, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U)); 
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA32UI, width_1, height_1, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

    GLfloat image_3D[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_3D[4*i] = i * 1.0 + 0.0;
        image_3D[4*i + 1] = i * 1.0 + 0.1;
        image_3D[4*i + 2] = i * 1.0 + 0.2;
        image_3D[4*i + 3] = i * 1.0 + 0.3;
    }

    GLfloat image_3D1[width_1 * height_1 * depth_1 * 4];
    for(int i = 0; i < width_1 * height_1 * depth_1; i++){
        image_3D1[4*i] = i * 1.0 + 0.0 +0.01;
        image_3D1[4*i + 1] = i * 1.0 + 0.1 + 0.01;
        image_3D1[4*i + 2] = i * 1.0 + 0.2 + 0.01;
        image_3D1[4*i + 3] = i * 1.0 + 0.3 + 0.01;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_3D));    
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_3D));

    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32F, width, height, depth, 0, GL_RGBA, GL_FLOAT, image_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 1, GL_RGBA32F, width_1, height_1, depth_1, 0, GL_RGBA, GL_FLOAT, image_3D1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, 0));

    GLint image_I_3D[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_I_3D[4*i] = i * 100 + 0;
        image_I_3D[4*i + 1] = i * 100 + 10;
        image_I_3D[4*i + 2] = i * 100 + 20;
        image_I_3D[4*i + 3] = i * 100 + 30;
    }

    GLint image_I_3D1[width_1 * height_1 * depth_1 * 4];
    for(int i = 0; i < width_1 * height_1 * depth_1; i++){
        image_I_3D1[4*i] = i * 100 + 0 + 1;
        image_I_3D1[4*i + 1] = i * 100 + 10 + 1;
        image_I_3D1[4*i + 2] = i * 100 + 20 + 1;
        image_I_3D1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I_3D));    
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_I_3D));

    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32I, width, height, depth , 0, GL_RGBA_INTEGER, GL_INT, image_I_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 1, GL_RGBA32I, width_1, height_1, depth_1, 0, GL_RGBA_INTEGER, GL_INT, image_I_3D1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, 0));

    GLuint image_U_3D[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_U_3D[4*i] = i * 100 + 0;
        image_U_3D[4*i + 1] = i * 100 + 10;
        image_U_3D[4*i + 2] = i * 100 + 20;
        image_U_3D[4*i + 3] = i * 100 + 30;
    }

    GLuint image_U_3D1[width_1 * height_1 * depth_1 * 4];
    for(int i = 0; i < width_1 * height_1 * depth_1; i++){
        image_U_3D1[4*i] = i * 100 + 0 + 1;
        image_U_3D1[4*i + 1] = i * 100 + 10 + 1;
        image_U_3D1[4*i + 2] = i * 100 + 20 + 1;
        image_U_3D1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U_3D));    
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_U_3D));

    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32UI, width, height, depth , 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_I_3D)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_3D, 1, GL_RGBA32UI, width_1, height_1, depth_1, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_I_3D1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, 0));

    GLfloat image_2DArray[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_2DArray[4*i] = i * 1.0 + 0.0;
        image_2DArray[4*i + 1] = i * 1.0 + 0.1;
        image_2DArray[4*i + 2] = i * 1.0 + 0.2;
        image_2DArray[4*i + 3] = i * 1.0 + 0.3;
    }

    GLfloat image_2DArray1[width_1 * height_1 * depth * 4];
    for(int i = 0; i < width_1 * height_1 * depth; i++){
        image_2DArray1[4*i] = i * 1.0 + 0.0 +0.01;
        image_2DArray1[4*i + 1] = i * 1.0 + 0.1 + 0.01;
        image_2DArray1[4*i + 2] = i * 1.0 + 0.2 + 0.01;
        image_2DArray1[4*i + 3] = i * 1.0 + 0.3 + 0.01;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_2DArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_2DArray));

    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA32F, width, height, depth, 0, GL_RGBA, GL_FLOAT, image_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32F, width_1, height_1, depth, 0, GL_RGBA, GL_FLOAT, image_2DArray1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

    GLint image_I_2DArray[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_I_2DArray[4*i] = i * 100 + 0;
        image_I_2DArray[4*i + 1] = i * 100 + 10;
        image_I_2DArray[4*i + 2] = i * 100 + 20;
        image_I_2DArray[4*i + 3] = i * 100 + 30;
    }

    GLint image_I_2DArray1[width_1 * height_1 * depth * 4];
    for(int i = 0; i < width_1 * height_1 * depth; i++){
        image_I_2DArray1[4*i] = i * 100 + 0 + 1;
        image_I_2DArray1[4*i + 1] = i * 100 + 10 + 1;
        image_I_2DArray1[4*i + 2] = i * 100 + 20 + 1;
        image_I_2DArray1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I_2DArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_I_2DArray));

    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA32I, width, height, depth, 0, GL_RGBA_INTEGER, GL_INT, image_I_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32I, width_1, height_1, depth, 0, GL_RGBA_INTEGER, GL_INT, image_I_2DArray1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

    GLuint image_U_2DArray[width * height * depth * 4];
    for(int i = 0; i < width * height * depth; i++){
        image_U_2DArray[4*i] = i * 100 + 0;
        image_U_2DArray[4*i + 1] = i * 100 + 10;
        image_U_2DArray[4*i + 2] = i * 100 + 20;
        image_U_2DArray[4*i + 3] = i * 100 + 30;
    }

    GLuint image_U_2DArray1[width_1 * height_1 * depth * 4];
    for(int i = 0; i < width_1 * height_1 * depth; i++){
        image_U_2DArray1[4*i] = i * 100 + 0 + 1;
        image_U_2DArray1[4*i + 1] = i * 100 + 10 + 1;
        image_U_2DArray1[4*i + 2] = i * 100 + 20 + 1;
        image_U_2DArray1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U_2DArray));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_U_2DArray));

    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA32UI, width, height, depth, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_2DArray)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32UI, width_1, height_1, depth, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_2DArray1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

    GLfloat image_Cube[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_Cube[4*i] = i * 1.0 + 0.0;
        image_Cube[4*i + 1] = i * 1.0 + 0.1;
        image_Cube[4*i + 2] = i * 1.0 + 0.2;
        image_Cube[4*i + 3] = i * 1.0 + 0.3;
    }

    GLfloat image_Cube1[width_1 * height_1 * 4];
    for(int i = 0; i < width_1 * height_1; i++){
        image_Cube1[4*i] = i * 1.0 + 0.0 +0.01;
        image_Cube1[4*i + 1] = i * 1.0 + 0.1 + 0.01;
        image_Cube1[4*i + 2] = i * 1.0 + 0.2 + 0.01;
        image_Cube1[4*i + 3] = i * 1.0 + 0.3 + 0.01;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_Cube));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_Cube));

    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
        GL_CHECK(glTexImage2D(target, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, image_Cube)); 
        GL_CHECK(glTexImage2D(target, 1, GL_RGBA32F, width_1, height_1, 0, GL_RGBA, GL_FLOAT, image_Cube1)); 
    }

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

    GLint image_I_Cube[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_I_Cube[4*i] = i * 100 + 0;
        image_I_Cube[4*i + 1] = i * 100 + 10;
        image_I_Cube[4*i + 2] = i * 100 + 20;
        image_I_Cube[4*i + 3] = i * 100 + 30;
    }

    GLint image_I_Cube1[width_1 * height_1 * 4];
    for(int i = 0; i < width_1 * height_1; i++){
        image_I_Cube1[4*i] = i * 100 + 0 + 1;
        image_I_Cube1[4*i + 1] = i * 100 + 10 + 1;
        image_I_Cube1[4*i + 2] = i * 100 + 20 + 1;
        image_I_Cube1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I_Cube));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_I_Cube));

    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
        GL_CHECK(glTexImage2D(target, 0, GL_RGBA32I, width, height, 0, GL_RGBA_INTEGER, GL_INT, image_I_Cube)); 
        GL_CHECK(glTexImage2D(target, 1, GL_RGBA32I, width_1, height_1, 0, GL_RGBA_INTEGER, GL_INT, image_I_Cube1)); 
    }

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

    GLuint image_U_Cube[width * height * 4];
    for(int i = 0; i < width * height; i++){
        image_U_Cube[4*i] = i * 100 + 0;
        image_U_Cube[4*i + 1] = i * 100 + 10;
        image_U_Cube[4*i + 2] = i * 100 + 20;
        image_U_Cube[4*i + 3] = i * 100 + 30;
    }

    GLuint image_U_Cube1[width_1 * height_1 * 4];
    for(int i = 0; i < width_1 * height_1; i++){
        image_U_Cube1[4*i] = i * 100 + 0 + 1;
        image_U_Cube1[4*i + 1] = i * 100 + 10 + 1;
        image_U_Cube1[4*i + 2] = i * 100 + 20 + 1;
        image_U_Cube1[4*i + 3] = i * 100 + 30 + 1;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_U_Cube));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_U_Cube));

    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
        GL_CHECK(glTexImage2D(target, 0, GL_RGBA32UI, width, height, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_Cube)); 
        GL_CHECK(glTexImage2D(target, 1, GL_RGBA32UI, width_1, height_1, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, image_U_Cube1)); 
    }

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 1));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_texLookupFuncs_6";
#else
    string path = "gl43_texLookupFuncs_6";
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

