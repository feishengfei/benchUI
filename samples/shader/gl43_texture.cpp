/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_texture.cpp
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
    const int NumPoints = 6; /* number of points */
    GLfloat points[NumPoints*3] = {
         -0.50, 0.75,  0.00, 
          0.50, 0.75,  0.00,
         -0.50, 0.00+0.1,  0.25,

          0.50, 0.75,  0.00,
         -0.50, 0.00+0.1,  0.25,
          0.50, 0.00+0.1,  0.25
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
    GLfloat norms[NumPoints*3] = {
        0.0, 0.25, 0.75,
        0.0, 0.25, 0.75,
        0.0, 0.25, 0.75,

        0.0, 0.25, 0.75,
        0.0, 0.25, 0.75,
        0.0, 0.25, 0.75,
    };

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

    GLfloat lightsource_pos[3] = {0.4, 0.4, 0.0}; /// the position of the light source
    GLfloat lightsource_col[4] = {1.0, 1.0, 1.0, 1.0};

    GLuint program;
    GLuint loc_theta;
    GLuint VAO;
    GLuint texture_ob;
    GLuint norm_ob;
    GLuint buffer_ob;

    GLuint program_lightsource;
    GLuint loc_lightsource;
    GLuint VAO_lightsource;
    GLuint lightsource_buffer_ob;

    GLuint loc_lightColor;
    GLuint loc_lightPosition;
    GLuint loc_choice;

    GLuint VAO_bone;
    GLuint buffer_bone_ob;

    GLfloat Theta = 0.0;
///====================================================================================

void getdata()
{

}

void initVBO()
{
    GL_CHECK(glGenBuffers(1, &buffer_ob));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_ob));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors)+sizeof(textures)+sizeof(norms), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), sizeof(textures), textures));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(textures), sizeof(norms), norms));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));


    GL_CHECK(glGenBuffers(1, &buffer_bone_ob));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_bone_ob));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points_bone) + sizeof(colors_bone) + sizeof(norms_bone), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points_bone), points_bone));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points_bone), sizeof(colors_bone), colors_bone));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points_bone) + sizeof(colors_bone), sizeof(norms_bone), norms_bone));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));


    GL_CHECK(glGenBuffers(1, &lightsource_buffer_ob));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, lightsource_buffer_ob));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(lightsource_pos), lightsource_pos, GL_STATIC_DRAW));
}

void initVAO()
{
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_ob));
    GL_CHECK(glGenVertexArrays(1, &VAO));
    GL_CHECK(glBindVertexArray(VAO));
    GLuint loc1 = GL_CHECK(glGetAttribLocation(program, "vPosition"));
    GL_CHECK(glEnableVertexAttribArray(loc1));
    GL_CHECK(glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0))); 
    GLuint loc2 = GL_CHECK(glGetAttribLocation(program, "vColor"));
    GL_CHECK(glEnableVertexAttribArray(loc2));
    GL_CHECK(glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points))));
    GLuint loc3 = GL_CHECK(glGetAttribLocation(program, "vTexCoord"));
    GL_CHECK(glEnableVertexAttribArray(loc3));
    GL_CHECK(glVertexAttribPointer(loc3, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)+sizeof(colors))));
    GLuint loc4 = GL_CHECK(glGetAttribLocation(program, "vNorm"));
    GL_CHECK(glEnableVertexAttribArray(loc4));
    GL_CHECK(glVertexAttribPointer(loc4, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)+sizeof(colors)+sizeof(textures))));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffer_bone_ob));
    GL_CHECK(glGenVertexArrays(1, &VAO_bone));
    GL_CHECK(glBindVertexArray(VAO_bone));
    loc1 = GL_CHECK(glGetAttribLocation(program, "vPosition"));
    GL_CHECK(glEnableVertexAttribArray(loc1));
    GL_CHECK(glVertexAttribPointer(loc1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0))); 
    loc2 = GL_CHECK(glGetAttribLocation(program, "vColor"));
    GL_CHECK(glEnableVertexAttribArray(loc2));
    GL_CHECK(glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points_bone))));
    loc4 = GL_CHECK(glGetAttribLocation(program, "vNorm"));
    GL_CHECK(glEnableVertexAttribArray(loc4));
    GL_CHECK(glVertexAttribPointer(loc4, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points_bone)+sizeof(colors_bone))));
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, lightsource_buffer_ob));
    GL_CHECK(glGenVertexArrays(1, &VAO_lightsource));
    GL_CHECK(glBindVertexArray(VAO_lightsource));
    GLuint loc_lightsource = GL_CHECK(glGetAttribLocation(program_lightsource, "vPosition"));
    GL_CHECK(glEnableVertexAttribArray(loc_lightsource));
    GL_CHECK(glVertexAttribPointer(loc_lightsource, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
}

void initTexture()
{
    int width, height;
    struct bmp_data bmpdata;
    string picture_name = (string)PICTURE_PATH + "myBMP.bmp";
    printf("picture_name = %s  \n", picture_name.c_str());
    bmpdata.file_name = (char*) picture_name.c_str();
    read_bmp(&bmpdata);
    width = bmpdata.width;
    height = bmpdata.height;
    printf("%d %d\n", width, height);
    unsigned char image[width * height * 4];
    for(int i = 0,j = 0; i < width * height * 4; i += 4, j += 3)
    {
        unsigned char t;
        image[i] = (bmpdata.image_data)[j+2];
        image[i+1] = (bmpdata.image_data)[j+1];
        image[i+2] = (bmpdata.image_data)[j];
        image[i+3] = 255;
    }

    GL_CHECK(glGenTextures(1, &texture_ob));    
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image)); 
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_texture";
#else
    string path = "gl43_texture";
    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
#endif
    string vertexShaderPath = (string)GLSL_PATH + path + "/vertex_shader.glsl";
    string fragmentShaderPath = (string)GLSL_PATH + path + "/fragment_shader.glsl";
    string light_source_vshader_Path = (string)GLSL_PATH + path + "/light_source_vshader.glsl";
    string light_source_fshader_Path = (string)GLSL_PATH + path + "/light_source_fshader.glsl";

    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());
    printf("light_source_vshader_Path = %s  \n", light_source_vshader_Path.c_str());
    printf("light_source_fshader_Path = %s  \n", light_source_fshader_Path.c_str());

    program = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    program_lightsource = Shader::CreateProgram(light_source_vshader_Path.c_str(), light_source_fshader_Path.c_str());

    initVBO();
    initVAO();
    initTexture();

    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(loc_theta = glGetUniformLocation(program, "theta"));
    GL_CHECK(loc_lightColor = glGetUniformLocation(program, "light_color"));
    GL_CHECK(loc_lightPosition = glGetUniformLocation(program, "light_position"));
    GL_CHECK(loc_choice = glGetUniformLocation(program, "choice"));
    GL_CHECK(glViewport(0, 0, width, height));
    return true;
}
///===========================================================================================

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CHECK(glUseProgram(program));   
    GL_CHECK(glUniform1f(loc_theta, Theta));
    GL_CHECK(glUniform4f(loc_lightColor, lightsource_col[0], lightsource_col[1], lightsource_col[2], lightsource_col[3]));
    GL_CHECK(glUniform3f(loc_lightPosition, lightsource_pos[0], lightsource_pos[1], lightsource_pos[2]));
    GL_CHECK(glUniform1i(loc_choice, 0));

    GL_CHECK(glBindVertexArray(VAO));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_ob));
    GL_CHECK(glDrawArrays(GL_TRIANGLES,0,NumPoints)); 



    GL_CHECK(glUniform1i(loc_choice, 1));
    GL_CHECK(glBindVertexArray(VAO_bone));
    GL_CHECK(glDrawArrays(GL_TRIANGLES,0,NumPoints_bone));

    GL_CHECK(glUseProgram(program_lightsource));
    GL_CHECK(glBindVertexArray(VAO_lightsource));
    GL_CHECK(glDrawArrays(GL_POINTS,0,1));

    Theta = Theta + 0.02;
    if(Theta > 360){
        Theta = Theta - 360;
    }
/*
    static int flag = 0;
    if(Theta >= 135 && flag == 0){
        EGLRuntime::pixelsToPicture("es32_texture.bmp"); 
        flag++;
    }  
    EGL_CHECK(eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface));
*/
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
