/* =================================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file aishe.cpp
 * @author Cary.Zhang
 * @par History:
 *    A001: Cary.Zhang, 2020-01-11, create file
 * @par TestPoints:
 *      
 *
 */

#include "tuzi.h"
#include "Sample.h"
#include "Text.h"
#include "Shader.h"
#include "Texture.h"
#include "Matrix.h"
#include "Timer.h"

#define WINDOW_W_ 512
#define WINDOW_H_ 512

using std::string;
using namespace BotsonSDK;

/* Asset directories and filenames. */
//string resourceDirectory = "assets/";
//string vertexShaderFilename = "Cube_cube.vert";
//string fragmentShaderFilename = "Cube_cube.frag";

/* Shader variables. */
GLuint programID;
GLint iLocPosition;
GLint iLocColor;
GLint iLocNormal;
GLint iLocMVP;

int windowWidth = -1;
int windowHeight = -1;
GLuint fragmentShaderID, vertexShaderID;

/* A text object to draw text on the screen. */
Text *text;

bool setupGraphics()
{
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    string vertexShaderPath = ((string)GLSL_PATH) + "tuzi.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "tuzi.frag";

    printf("vertexShaderPath = %s  \n", vertexShaderPath.c_str());
    printf("fragmentShaderPath = %s  \n", fragmentShaderPath.c_str());

    Shader::processShader(&vertexShaderID, vertexShaderPath.c_str(), GL_VERTEX_SHADER);
    LOGI("vertexShaderID = %d \n", vertexShaderID);
    Shader::processShader(&fragmentShaderID, fragmentShaderPath.c_str(), GL_FRAGMENT_SHADER);
    LOGI("fragmentShaderID = %d \n", fragmentShaderID);

    programID = GL_CHECK(glCreateProgram());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }


    printf("programID = %d  \n", programID);

    /* Initialize the Text object and add some text. */
 //   text = new Text(resourceDirectory.c_str(), windowWidth, windowHeight);
    text = new Text( WINDOW_W_, WINDOW_H_);
    text->addString(0, 0, "Cow", 255, 255, 0, 255);



    /* Attach shaders and link programID */
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    printf("programID = %d  \n", programID);
    GL_CHECK(glUseProgram(programID));

    printf("programID = %d  \n", programID);
    /* Get attribute locations of non-fixed attributes like colour and texture coordinates. */
    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "av4position"));
    iLocColor = GL_CHECK(glGetAttribLocation(programID, "av3colour"));
    iLocNormal = GL_CHECK(glGetAttribLocation(programID, "av3normal"));

    LOGD("iLocPosition = %i\n", iLocPosition);
    LOGD("iLocColor   = %i\n", iLocColor);
    LOGD("iLocNormal   = %i\n", iLocNormal);

    /* Get uniform locations */
    iLocMVP = GL_CHECK(glGetUniformLocation(programID, "mvp"));
    LOGD("iLocMVP      = %i\n", iLocMVP);

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    /* Set clear screen color. */
    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));
    GL_CHECK(glEnableVertexAttribArray(iLocColor));
    //GL_CHECK(glEnableVertexAttribArray(iLocNormal));

    /* Populate attributes for position, color and texture coordinates etc. */
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));
    GL_CHECK(glVertexAttribPointer(iLocColor, 3, GL_FLOAT, GL_FALSE, 0, vertices));
    //GL_CHECK(glVertexAttribPointer(iLocNormal, 3, GL_FLOAT, GL_FALSE, 0, normals));

    static float angleX = 0, angleY = 0, angleZ = 0;
    /*
     * Do some rotation with Euler angles. It is not a fixed axis as
     * quaternions would be, but the effect is nice.
     */

    Matrix scale = Matrix::createScaling(0.03f, 0.03f, 0.03f);  //###add scale by cgj###//
    //Matrix scale = Matrix::createScaling(1.0f, 1.0f, 1.0f);
    Matrix modelView = Matrix::createRotationX(angleX);
    Matrix rotation = Matrix::createRotationY(angleY);

    modelView=modelView * scale;//add scale by cgj

    modelView = rotation * modelView;

    rotation = Matrix::createRotationZ(angleZ);
    modelView = rotation * modelView;

    /* Pull the camera back from the cube */
    modelView[14] -= 1.8;

    Matrix perspective = Matrix::matrixPerspective(45.0f, WINDOW_W_/(float)WINDOW_H_, 0.5f, 100.0f);
    Matrix modelViewPerspective = perspective * modelView;

    GL_CHECK(glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, modelViewPerspective.getAsArray()));

    /* Update cube's rotation angles for animating. */
    angleX += 0;
    angleY += 2;
    angleZ += 0;

    if(angleX >= 360) angleX -= 360;
    if(angleX < 0) angleX += 360;
    if(angleY >= 360) angleY -= 360;
    if(angleY < 0) angleY += 360;
    if(angleZ >= 360) angleZ -= 360;
    if(angleZ < 0) angleZ += 360;

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
   GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 37764));
    /* Draw any text. */
    text->draw();
}

void Sample::test() {
    setupGraphics();

    Timer fpsTimer;
    fpsTimer.reset();
    bool end = false;
    while(!end)
    {
        float fFPS = fpsTimer.getFPS();
        if(fpsTimer.isTimePassed(1.0f))
        {
            printf("FPS:\t%.1f\n", fFPS);
        }
        renderFrame();
        eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
    }


    renderFrame();
    string bmp_file = filename + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, WINDOW_W_, WINDOW_H_);

    sample.test();

    return 0;
}

