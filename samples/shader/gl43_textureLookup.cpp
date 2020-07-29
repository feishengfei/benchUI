/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_textureLookup.cpp
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
    GLfloat points[NumPoints*3] = {
         -1.0, 1.0,  0.0, 
          1.0, 1.0,  0.0,
         -1.0, -1.0,  0.0,

          1.0, 1.0,  0.0,
         -1.0, -1.0,  0.0,
          1.0, -1.0,  0.0
    };
    GLfloat colors[NumPoints*4] = {
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,

        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0
    };
    GLfloat textures[NumPoints*2] = {
        0.0, 1.0,
        1.0, 1.0,
        0.0, 0.0,

        1.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
    };

    GLuint VAO;
    GLuint loc_theta;
    GLuint programID;
    GLuint VBO;
    GLuint texture_ob;
    GLfloat Theta = 135.0;
///====================================================================================

void getdata()
{

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
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(textures), sizeof(textures), textures));
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
    GLuint loc3 = GL_CHECK(glGetAttribLocation(programID, "vTexCoord"));
    GL_CHECK(glEnableVertexAttribArray(loc3));
    GL_CHECK(glVertexAttribPointer(loc3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)+sizeof(colors))));

    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void initTexture()
{

    struct bmp_data bmpdata;
    string picture_name = (string)PICTURE_PATH + "myBMP.bmp";
    bmpdata.file_name = (char*) picture_name.c_str();
    read_bmp(&bmpdata);  // in bmp.h
    int width, height;
    width = bmpdata.width;
    height = bmpdata.height;
    printf("%d %d\n", width, height);
    unsigned char* image = new unsigned char[width * height * 4];
    for(int i = 0,j = 0; i < width * height * 4; i += 4, j += 3)
    {
        unsigned char t;
        image[i] = (bmpdata.image_data)[j+2];
        image[i+1] = (bmpdata.image_data)[j+1];
        image[i+2] = (bmpdata.image_data)[j];
        image[i+3] = 255;
    }

    ///create the texture object
    GL_CHECK(glGenTextures(1, &texture_ob));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob));

    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image)); 
    delete []image;
    ///setting the texture wrapping method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    ///setting the texture filtering method
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    ///setting the texture Mipmaps
    GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
    ///bind GL_TEXTURE_2D to 0-object
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_textureLookup";
#else
    string path = "gl43_textureLookup";
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
    GL_CHECK(loc_theta = glGetUniformLocation(programID, "theta"));
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
    GL_CHECK(glUniform1f(loc_theta, Theta)); /// update the uniform variable with location loc_theta

    GLuint tex0_uniform_loc = glGetUniformLocation(programID, "texUnit0");
    GL_CHECK(glUniform1i(tex0_uniform_loc, 0));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob));
//    GL_CHECK(glDrawArrays(GL_POINTS,0,NumPoints)); 
    GL_CHECK(glDrawArrays(GL_TRIANGLES,0,NumPoints));
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


