/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_texLookupFuncs_2.cpp
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
    GLuint texture_ob_2DShadow;
    GLuint texture_ob_2DArrayShadow;
    GLuint texture_ob_CubeShadow;

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

    GLfloat image_2DShadow[width * height];
    for(int i = 0; i < width * height; i++){
        image_2DShadow[i] = i * 0.01 + 0.00;
    }

    GLfloat image_2DShadow1[width_1 * height_1];
    for(int i = 0; i < width_1 * height_1; i++){
        image_2DShadow1[i] = i * 0.01 + 0.001;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_2DShadow));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_2DShadow));

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, image_2DShadow));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, width_1, height_1, 0, GL_DEPTH_COMPONENT, GL_FLOAT, image_2DShadow1));
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

    GLfloat image_2DArrayShadow[width * height * depth];
    for(int i = 0; i < width * height * depth; i++){
        image_2DArrayShadow[i] = i * 0.01 + 0.00;
    }

    GLfloat image_2DArrayShadow1[width_1 * height_1 * depth];
    for(int i = 0; i < width_1 * height_1 * depth; i++){
        image_2DArrayShadow1[i] = i * 0.01 + 0.001;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_2DArrayShadow));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_2DArrayShadow));

    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT32F, width, height, depth, 0, GL_DEPTH_COMPONENT, GL_FLOAT, image_2DArrayShadow)); 
    GL_CHECK(glTexImage3D(GL_TEXTURE_2D_ARRAY, 1, GL_DEPTH_COMPONENT32F, width_1, height_1, depth, 0, GL_DEPTH_COMPONENT, GL_FLOAT, image_2DArrayShadow1)); 
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 1));

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

    GLfloat image_CubeShadow[width * height];
    for(int i = 0; i < width * height; i++){
        image_CubeShadow[i] = i * 0.01 + 0.00;
    }

    GLfloat image_CubeShadow1[width_1 * height_1];
    for(int i = 0; i < width_1 * height_1; i++){
        image_CubeShadow1[i] = i * 0.01 + 0.001;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_CubeShadow));    
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_CubeShadow));

    for(int face = 0; face < 6; face++){
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
        GL_CHECK(glTexImage2D(target, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, image_CubeShadow)); 
        GL_CHECK(glTexImage2D(target, 1, GL_DEPTH_COMPONENT32F, width_1, height_1, 0, GL_DEPTH_COMPONENT, GL_FLOAT, image_CubeShadow1)); 
    }

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 1));

    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
    ///setting the texture Mipmaps
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_texLookupFuncs_2";
#else
    string path = "gl43_texLookupFuncs_2";
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
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_2DShadow));

    GLuint tex1_uniform_loc = glGetUniformLocation(programID, "texUnit1");
    GL_CHECK(glUniform1i(tex1_uniform_loc, 1));
    GL_CHECK(glActiveTexture(GL_TEXTURE1));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_ob_2DArrayShadow));

    GLuint tex2_uniform_loc = glGetUniformLocation(programID, "texUnit2");
    GL_CHECK(glUniform1i(tex2_uniform_loc, 2));
    GL_CHECK(glActiveTexture(GL_TEXTURE2));
    GL_CHECK(glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ob_CubeShadow));

    GL_CHECK(glDrawArrays(GL_POINTS,0,NumPoints)); 
}
///==========================================================================================

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
