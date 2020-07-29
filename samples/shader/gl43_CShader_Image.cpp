/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_CShader_Image.cpp
 * @author Martin.li
 * @par History:
 *    A001: Martin.li, 20XX-XX-XX, Add commit
 * @
 * @par TestPoints:
 *
 */
///===================================================================================
#include "Shader.h"
#include "Platform.h"
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
    GLuint program_cs;
    GLuint VBO;
    GLuint texture_ob;
    GLuint texture_ob_I;
    GLuint texture_ob_U;
    GLuint texture_ob_3D;
    GLuint texture_ob_I_3D;
    GLuint texture_ob_U_3D;
    string path;
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


    GLfloat image[width * height];
    for(int i = 0; i < width * height; i++){
        image[i] = i * 1.0 + 0.0;
    }


    GL_CHECK(glGenTextures(1, &texture_ob));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob));

    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, width, height));
    GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED, GL_FLOAT, image));
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
//    GL_CHECK(glBindImageTexture(0, texture_ob, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32F));
    GL_CHECK(glBindImageTexture(0, texture_ob, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32F));



    GLint image_I[width * height];
    for(int i = 0; i < width * height; i++){
        image_I[i] = i * 100 + 0;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob_I));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_I));

    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32I, width, height));
    GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_INT, image_I));

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    GL_CHECK(glBindImageTexture(1, texture_ob_I, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32I));



    GLuint image_U[width * height];
    for(int i = 0; i < width * height; i++){
        image_U[i] = i * 100 + 0;    
    }

    GL_CHECK(glGenTextures(1, &texture_ob_U));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob_U));

    GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32UI, width, height));
    GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RED_INTEGER, GL_UNSIGNED_INT, image_U));

    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    GL_CHECK(glBindImageTexture(2, texture_ob_U, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI));


    GLfloat image_3D[width * height * depth];
    for(int i = 0; i < width * height * depth; i++){
        image_3D[i] = i * 1.0 + 0.0;
    }

    GL_CHECK(glGenTextures(1, &texture_ob_3D));    
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_3D));

    GL_CHECK(glTexStorage3D(GL_TEXTURE_3D, 1, GL_R32F, width, height, depth));
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, width, height, depth, GL_RED, GL_FLOAT, image_3D));
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_3D, 0));
    GL_CHECK(glBindImageTexture(3, texture_ob_3D, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32F));


    GLint image_I_3D[width * height * depth];
    for(int i = 0; i < width * height * depth; i++){
        image_I_3D[i] = i * 100 + 0;
    }

    GL_CHECK(glGenTextures(1, &texture_ob_I_3D));    
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_I_3D));

    GL_CHECK(glTexStorage3D(GL_TEXTURE_3D, 1, GL_R32I, width, height, depth));
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, width, height, depth, GL_RED_INTEGER, GL_INT, image_I_3D));
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_3D, 0));
    GL_CHECK(glBindImageTexture(4, texture_ob_I_3D, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32I));



    GLuint image_U_3D[width * height * depth];
    for(int i = 0; i < width * height * depth; i++){
        image_U_3D[i] = i * 100 + 0;
    }

    GL_CHECK(glGenTextures(1, &texture_ob_U_3D));    
    GL_CHECK(glBindTexture(GL_TEXTURE_3D, texture_ob_U_3D));

    GL_CHECK(glTexStorage3D(GL_TEXTURE_3D, 1, GL_R32UI, width, height, depth));
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, width, height, depth, GL_RED_INTEGER, GL_UNSIGNED_INT, image_U_3D));
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CHECK(glBindTexture(GL_TEXTURE_3D, 0));
    GL_CHECK(glBindImageTexture(5, texture_ob_U_3D, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI));



}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    path = "es32_CShader_Image";
#else
    path = "gl43_CShader_Image";
    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
#endif
    string vertexShaderPath = (string)GLSL_PATH + path + "/vertex_shader.glsl";
    string fragmentShaderPath = (string)GLSL_PATH + path + "/fragment_shader.glsl";
    string computerShaderPath = (string)GLSL_PATH + path + "/compute_shader.glsl";

    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    GLuint computerID=-1;
    Shader::processShader(&computerID, computerShaderPath.c_str(), GL_COMPUTE_SHADER);
    program_cs = GL_CHECK(glCreateProgram());
    if (!program_cs)
    {
        printf("Could not create program.");
        return false;
    }
        GL_CHECK(glAttachShader(program_cs, computerID));
        GL_CHECK(glLinkProgram(program_cs));

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
    GL_CHECK(glUseProgram(program_cs));

    GL_CHECK(glDispatchCompute(1, 2, 4));

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
