/* ============================================================
 * Copyright (c) 2019 Botson Corp 
 * Botson Confidential and Proprietary 
 *
 * @file getShaderPrecisionFormat
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

float vertices_data[] = {
		-0.8, 0.0,
		-0.6, 0.6,
		0.0, 0.8,
		0.6, 0.6,
		0.8, 0.0,
        	0.6, -0.6,
		0.0, -0.8,
		-0.6, -0.6
};

GLuint programID;
GLint iLocPosition = -1;
GLuint vao;
GLuint vertices_bo;
GLint vrange = 0;
GLint vprecision = 0;
GLint frange = 0;
GLint fprecision = 0;
GLboolean compilerResult = false;

///====================================================================================

void getdata()
{
    GL_CHECK(glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_LOW_FLOAT, &vrange, &vprecision));
    printf("GL_VERTEX_SHADER GL_LOW_FLOAT      :  myrange = %d , myprecision = %d \n", vrange, vprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_MEDIUM_FLOAT, &vrange, &vprecision));
    printf("GL_VERTEX_SHADER GL_MEDIUM_FLOAT   :  myrange = %d , myprecision = %d \n", vrange, vprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_HIGH_FLOAT, &vrange, &vprecision));
    printf("GL_VERTEX_SHADER GL_HIGH_FLOAT     :  myrange = %d , myprecision = %d \n", vrange, vprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_LOW_INT, &vrange, &vprecision));
    printf("GL_VERTEX_SHADER GL_LOW_INT        :  myrange = %d , myprecision = %d \n", vrange, vprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_MEDIUM_INT, &vrange, &vprecision));
    printf("GL_VERTEX_SHADER GL_MEDIUM_INT     :  myrange = %d , myprecision = %d \n", vrange, vprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_VERTEX_SHADER, GL_HIGH_INT, &vrange, &vprecision));
    printf("GL_VERTEX_SHADER GL_HIGH_INT       :  myrange = %d , myprecision = %d \n", vrange, vprecision);


    GL_CHECK(glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_LOW_FLOAT, &frange, &fprecision));
    printf("GL_FRAGMENT_SHADER GL_LOW_FLOAT    :  myrange = %d , myprecision = %d \n", frange, fprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_MEDIUM_FLOAT, &frange, &fprecision));
    printf("GL_FRAGMENT_SHADER GL_MEDIUM_FLOAT :  myrange = %d , myprecision = %d \n", frange, fprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_HIGH_FLOAT, &frange, &fprecision));
    printf("GL_FRAGMENT_SHADER GL_HIGH_FLOAT   :  myrange = %d , myprecision = %d \n", frange, fprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_LOW_INT, &frange, &fprecision));
    printf("GL_FRAGMENT_SHADER GL_LOW_INT      :  myrange = %d , myprecision = %d \n", frange, fprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_MEDIUM_INT, &frange, &fprecision));
    printf("GL_FRAGMENT_SHADER GL_MEDIUM_INT   :  myrange = %d , myprecision = %d \n", frange, fprecision);

    GL_CHECK(glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, GL_HIGH_INT, &frange, &fprecision));
    printf("GL_FRAGMENT_SHADER GL_HIGH_INT     :  myrange = %d , myprecision = %d \n", frange, fprecision);
}

void initVAO()
{
    GL_CHECK(iLocPosition = glGetAttribLocation(programID, "a_v4Position"));
    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &vertices_bo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertices_bo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_data), vertices_data, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glVertexAttribPointer(iLocPosition, 2, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glBindVertexArray(0));
}

bool setupGraphics(int width, int height)
{
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //glTranslatef(0.3, 0.3, 0.0);

    GL_CHECK(glEnable(GL_PROGRAM_POINT_SIZE));
    string vertexShaderPath = (string)GLSL_PATH + "base-green.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "base-green.frag";

    printf(" After  the release:%d \n", compilerResult);
    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    GL_CHECK(glReleaseShaderCompiler());

    getdata();

    initVAO();

    GL_CHECK(glBindVertexArray(0));
    GL_CHECK(glClearColor(1.0, 1.0, 1.0, 1.0));
    GL_CHECK(glViewport(0, 0, width, height));
    return true;
}
///===========================================================================================

void renderFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN,0,8));
}
///===========================================================================================

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    string bmp_file = filename + ".bmp";
    renderFrame();
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();

    return 0;
}
