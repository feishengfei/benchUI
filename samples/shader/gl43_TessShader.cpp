/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file TessShader.cpp
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
                                            0.2, 1.0, 0.0,
                                            1.0, 0.0, 0.0
                                        };
    GLfloat colors[NumPoints*4] = {
                                            1.0, 0.0, 0.0, 1.0,
                                            0.0, 1.0, 0.0, 1.0,
                                            0.0, 0.0, 1.0, 1.0
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
#ifdef API_ES
    string path = "es32_TessShader";
#else
    string path = "gl43_TessShader";
    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
#endif
    string vertexShaderPath = path + "/vertex_shader.glsl";
    string essellation_Control_Shader_Path = path + "/Tessellation_Control_Shader.glsl";
    string Tessellation_Evaluation_Shader_Path = path + "/Tessellation_Evaluation_Shader.glsl";
    string fragmentShaderPath = path + "/fragment_shader.glsl";

    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER,   vertexShaderPath.c_str() },
        { GL_TESS_CONTROL_SHADER, essellation_Control_Shader_Path.c_str() },
        { GL_TESS_EVALUATION_SHADER, Tessellation_Evaluation_Shader_Path.c_str() },
        { GL_FRAGMENT_SHADER, fragmentShaderPath.c_str() },
        { GL_NONE, NULL }
    };

    programID = Shader::LoadShaders( shaders );
/*
    program = initProgram("vertex_shader.glsl","fragment_shader.glsl","Tessellation_Control_Shader.glsl","Tessellation_Evaluation_Shader.glsl");
    if(program <= 0){
        LOGIF("program = %d, initProgram() is not successfull! \n", program);
    }
    GL_CHECK(glUseProgram(program));
*/
    initVBO();
    initVAO();
/// GL_CHECK(loc_choice = glGetUniformLocation(program, "choice"));
/// GL_CHECK(glEnable(GL_DEPTH_TEST)); //P97, you can use glDisable(GL_DEPTH_TEST) to close GL_DEPTH_TEST
/// GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE)); /// when you use gl_PointSize, you must enable GL_PROGRAM_POINT_SIZE
    GL_CHECK(glClearColor(1.0, 1.0, 1.0, 1.0));  /// white background
    GL_CHECK(glViewport(0, 0, width, height));
    return true;
}
///===========================================================================================

void renderFrame(void)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(VAO));
    GL_CHECK(glPatchParameteri(GL_PATCH_VERTICES, 3));
    glEnable(GL_SCISSOR_TEST);
//glPrimitiveBoundingBox(-0.5, -0.5, -1.0, -1.0, 0.5, 0.5, 1.0, 1.0);
    GL_CHECK(glDrawArrays(GL_PATCHES,0,NumPoints)); 
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
