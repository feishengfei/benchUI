/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file mt_FragCoord.cpp
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
    const int NumPoints = 3; // number of points 
    GLfloat points[NumPoints*3] = {
                                            0.0, 0.0, 0.0,
                                            0.3, 1.0, 0.0,
                                            1.0, 0.0, 0.0
                                        };
    GLfloat colors[NumPoints*4] = {
                                            1.0, 0.0, 0.0, 1.0,
                                            1.0, 0.0, 0.0, 1.0,
                                            1.0, 0.0, 0.0, 1.0
                                        };
    GLfloat func[NumPoints*4] = {
                                            0.0, 0.0, 0.0, 1.0,
                                            100.0, 0.0, 0.0, 1.0,
                                            200.0, 0.0, 0.0, 1.0
    };
    GLuint VAO;
    GLuint programID;
    GLuint VBO;
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
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(func), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), sizeof(func), func));
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
    GLuint loc3 = GL_CHECK(glGetAttribLocation(programID, "vFunc"));
    if(loc3 < 0) {
        LOGE("loc3 = %d, loc3 is illegel! \n", loc3);
    }
    GL_CHECK(glEnableVertexAttribArray(loc3));
    GL_CHECK(glVertexAttribPointer(loc3, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points) + sizeof(colors))));
    
    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

bool setupGraphics(int width, int height)
{
#ifdef API_ES
    string path = "es32_FragCoord";
#else
    string path = "gl43_FragCoord";
    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
#endif
    string vertexShaderPath = (string)GLSL_PATH + path + "/vertex_shader.glsl";
    string fragmentShaderPath = (string)GLSL_PATH + path + "/fragment_shader.glsl";

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

    int SAMPLES = -1;
    glGetIntegerv(GL_SAMPLES, &SAMPLES);
    printf("GL_SAMPLES = %d \n", SAMPLES);
    GL_CHECK(glUniform1i(0, SAMPLES)); 
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

