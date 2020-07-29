/* ============================================================
 * Copyright (c) 2020 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file point_sprite
 * @author Cary.Zhang
 * @par History:
 *    A001: Cary.Zhang, 20XX-XX-XX, Add commit
 * @
 * @par TestPoints:
 *
 */
///===================================================================================
#include "Sample.h"
#include "Timer.h"

using std::string;
using namespace BotsonSDK;
using namespace std;

#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))
#define W_Width 400
#define W_Height 400

const static int FRAMES_NUM = 10;
double flopstime=0.0;
Timer flopsTimer;

///====================================================================================
    const int NumPoints = 100; // number of points 
    GLfloat points[NumPoints*3];
    GLfloat colors[NumPoints*4];
    GLuint VAO;
    GLuint programID;
    GLuint VBO;
///====================================================================================

void getdata()
{
    for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++) {
        points[i] = ((float)(rand() % 100)) / 50 - 1;
    }
    for (int j = 0; j < sizeof(colors) / sizeof(colors[0]); j++) {
        colors[j] = ((float)(rand() % 50)) / 50; 
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

bool setupGraphics(int width, int height)
{
    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
    string vertexShaderPath = (string)GLSL_PATH + "point_sprite.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "point_sprite.frag";

    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    initVBO();
    initVAO();
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

    for(int i = 0; i < FRAMES_NUM; i++)
    {
        flopsTimer.reset();
        renderFrame();
        flopstime = flopsTimer.getTime();
        double ave_time = flopstime / FRAMES_NUM;
        LOGI("FLOPS : One frame average time:---%f\n", ave_time);
    }
    save2bmp(bmp_file.c_str());
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();

    return 0;
}

