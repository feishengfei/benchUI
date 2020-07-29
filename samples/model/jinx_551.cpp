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

#include "jinx_512.h"
#include "Sample.h"
#include "Text.h"
#include "Texture.h"
#include "Timer.h"

#define WINDOW_W_ 512
#define WINDOW_H_ 515

//-------add----------
GLint iLocMVP;
int windowWidth = -1;
int windowHeight = -1;
//-------add----------

using std::string;
using namespace BotsonSDK;


/* Texture variables. */
GLuint textureID = 0;
/* Shader variables. */
GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;
GLuint programID = 0;
GLint iLocPosition = -1;
GLint iLocTexCoord = -1;
GLint iLocSampler = -1;


/* A text object to draw text on the screen. */
Text *text;

bool setupGraphics()
{
    /* Initialize OpenGL ES. */
   GL_CHECK(glEnable(GL_CULL_FACE));
   GL_CHECK(glCullFace(GL_BACK));
   GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glEnable(GL_BLEND));
    /* Should do src * (src alpha) + dest * (1-src alpha). */
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    string vertexShaderPath = ((string)GLSL_PATH) + "jinx_551.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "jinx_551.frag";

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
//    text = new Text(resourceDirectory.c_str(), w, h);
    text = new Text( WINDOW_W_, WINDOW_H_);
    text->addString(0, 0, "Jinx", 255, 255, 0, 255);

    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    //string mainTexturePath = texturePath;
    //unsigned char *textureData;
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData));
   // GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); /* Default anyway. */
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    /* Process shaders. */

    /* Attach shaders and link programID */
    GL_CHECK(glAttachShader(programID, vertexShaderID));
    GL_CHECK(glAttachShader(programID, fragmentShaderID));
    GL_CHECK(glLinkProgram(programID));
    printf("programID = %d  \n", programID);
    GL_CHECK(glUseProgram(programID));

    printf("programID = %d  \n", programID);
    /* Vertex positions. */
    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "a_v4Position"));
    if(iLocPosition == -1)
    {
        LOGE("Attribute not found: \"a_v4Position\"");
        exit(1);
    }
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    /* Texture coordinates. */
    iLocTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_v2TexCoord"));
    if(iLocTexCoord == -1)
    {
        LOGD("Warning: Attribute not found: \"a_v2TexCoord\"");
    }
    else
    {
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }

    /* Set the sampler to point at the 0th texture unit. */
    iLocSampler = GL_CHECK(glGetUniformLocation(programID, "u_s2dTexture"));
    if(iLocSampler == -1)
    {
        LOGD("Warning: Uniform not found: \"u_s2dTexture\"");
    }
    else
    {
        GL_CHECK(glUniform1i(iLocSampler, 0));
    }

    //-------add----------
    /* Get uniform locations */
    iLocMVP = GL_CHECK(glGetUniformLocation(programID, "mvp"));

    LOGD("iLocMVP      = %i\n", iLocMVP);
    //-------add----------

    /* Set clear screen color. */
    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));

    /* Pass the plane vertices to the shader. */
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));
    if(iLocTexCoord != -1)
    {
        /* Pass the texture coordinates to the shader. */
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates));
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }

    /* Ensure the correct texture is bound to texture unit 0. */
    GL_CHECK(glActiveTexture(GL_TEXTURE0));//当前纹理单位
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));

    //----------------add--------------------
        static float angleX = 0, angleY = 0, angleZ = 0;
    /*
     * Do some rotation with Euler angles. It is not a fixed axis as
     * quaternions would be, but the effect is nice.
     */

    Matrix scale = Matrix::createScaling(0.008f, 0.008f, 0.008f);  //###add scale by cgj###//
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
    angleY += 1;
    angleZ += 0;

    if(angleX >= 360) angleX -= 360;
    if(angleX < 0) angleX += 360;
    if(angleY >= 360) angleY -= 360;
    if(angleY < 0) angleY += 360;
    if(angleZ >= 360) angleZ -= 360;
    if(angleZ < 0) angleZ += 360;

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 46395));

    /* Draw fonts. */
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

