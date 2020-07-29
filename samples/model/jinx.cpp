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

#include "jinx.h"
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


GLuint textureID = 0;
/* Shader variables. */
GLuint programID;
GLint iLocPosition;
GLint iLocNormal;
GLint iLocMVP;
GLint iLocTexCoord = -1;
GLint iLocSampler = -1;
//light
GLint iLocLightPosition;
GLint iLocEyeVector;
GLint iLocLight_ambient_color;
GLint iLocLight_diffuse_color;
GLint iLocLight_specular_color;

//material
GLint iLocLMaterial_ambient_color;
GLint iLocLMaterial_diffuse_color;
GLint iLocLMaterial_specular_color;
GLint iLocLMaterial_specular_exponent;

GLuint vertexShaderID = 0;
GLuint fragmentShaderID = 0;


/* A text object to draw text on the screen. */
Text *text;

bool setupGraphics()
{

    /* Initialize OpenGL ES. */
    GL_CHECK(glEnable(GL_BLEND));
    /* Should do: src * (src alpha) + dest * (1-src alpha). */
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    string vertexShaderPath = ((string)GLSL_PATH) + "jinx.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "jinx.frag";

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
    text->addString(0, 0, "Lighe Torus", 255, 255, 0, 255);

    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    //string mainTexturePath = texturePath;
    //unsigned char *textureData;
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData));
    //GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
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

    /* Get attribute locations of non-fixed attributes like colour and texture coordinates. */
    iLocPosition = GL_CHECK(glGetAttribLocation(programID, "av4position"));
    /* Texture coordinates. */
    iLocTexCoord = GL_CHECK(glGetAttribLocation(programID, "a_v2TexCoord"));
    iLocNormal = GL_CHECK(glGetAttribLocation(programID, "normal"));

    LOGD("iLocPosition = %i\n", iLocPosition);
	LOGD("iLocTexCoord = %i\n", iLocTexCoord);
    LOGD("iLocNormal   = %i\n", iLocNormal);
    iLocSampler = GL_CHECK(glGetUniformLocation(programID, "u_s2dTexture"));
	LOGD("iLocSampler = %i\n", iLocSampler);
    /* Get uniform locations */
    iLocMVP = GL_CHECK(glGetUniformLocation(programID, "mvp"));
    LOGD("iLocMVP      = %i\n", iLocMVP);

    //light
    iLocLightPosition = GL_CHECK(glGetUniformLocation(programID, "position"));
    LOGD("iLocLightPosition      = %i\n", iLocLightPosition);

    iLocEyeVector = GL_CHECK(glGetUniformLocation(programID, "eye_vector"));
    LOGD("iLocEyeVector      = %i\n", iLocEyeVector);

    iLocLight_ambient_color = GL_CHECK(glGetUniformLocation(programID, "light_ambient_color"));
    LOGD("iLocLight_ambient_color      = %i\n", iLocLight_ambient_color);

    iLocLight_diffuse_color = GL_CHECK(glGetUniformLocation(programID, "light_diffuse_color"));
    LOGD("iLocLight_diffuse_color      = %i\n", iLocLight_diffuse_color);

    iLocLight_specular_color = GL_CHECK(glGetUniformLocation(programID, "light_specular_color"));
    LOGD("iLocLight_specular_color      = %i\n", iLocLight_specular_color);

    //material
    iLocLMaterial_ambient_color = GL_CHECK(glGetUniformLocation(programID, "material_ambient_color"));
    LOGD("iLocLMaterial_ambient_color      = %i\n", iLocLMaterial_ambient_color);

    iLocLMaterial_diffuse_color = GL_CHECK(glGetUniformLocation(programID, "material_diffuse_color"));
    LOGD("iLocLMaterial_diffuse_color      = %i\n", iLocLMaterial_diffuse_color);

    iLocLMaterial_specular_color = GL_CHECK(glGetUniformLocation(programID, "material_specular_color"));
    LOGD("iLocLMaterial_specular_color      = %i\n", iLocLMaterial_specular_color);

    iLocLMaterial_specular_exponent = GL_CHECK(glGetUniformLocation(programID, "material_specular_exponent"));
    LOGD("iLocLMaterial_specular_exponent      = %i\n", iLocLMaterial_specular_exponent);

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    /* Set clear screen color. */
    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

    return true;
}

void renderFrame(void)
{
    GL_CHECK(glUseProgram(programID));

    /* Enable attributes for position, color and texture coordinates etc. */
    GL_CHECK(glEnableVertexAttribArray(iLocPosition));


    /* Populate attributes for position, color and texture coordinates etc. */
    GL_CHECK(glVertexAttribPointer(iLocPosition, 3, GL_FLOAT, GL_FALSE, 0, vertices));
    if(iLocTexCoord != -1)
    {
        /* Pass the texture coordinates to the shader. */
        GL_CHECK(glVertexAttribPointer(iLocTexCoord, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates));
        GL_CHECK(glEnableVertexAttribArray(iLocTexCoord));
    }
    GL_CHECK(glActiveTexture(GL_TEXTURE0));//当前纹理单位
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glEnableVertexAttribArray(iLocNormal));

    GL_CHECK(glVertexAttribPointer(iLocNormal, 3, GL_FLOAT, GL_FALSE, 0, normals));

    //light
    GL_CHECK(glUniform4f(iLocLightPosition,2.0f,2.0f,2.0f,1.0f));
    GL_CHECK(glUniform4f(iLocEyeVector,0.0f,0.0f,1.0f,1.0f));
    GL_CHECK(glUniform4f(iLocLight_ambient_color,1.0f,1.0f,1.0f,1.0f));
    GL_CHECK(glUniform4f(iLocLight_diffuse_color,1.0f,1.0f,1.0f,1.0f));
    GL_CHECK(glUniform4f(iLocLight_specular_color, 1.0f,1.0f,1.0f,1.0f));

    //material
    GL_CHECK(glUniform4f(iLocLMaterial_ambient_color, 1.0f, 1.0f,1.0f, 1.0f));
   // GL_CHECK(glUniform4f(iLocLMaterial_ambient_color, 0.3333f, 0.1098f, 0.6941f, 1.0f));
    GL_CHECK(glUniform4f(iLocLMaterial_diffuse_color, 1.0f, 1.0f,1.0f, 1.0f));
   // GL_CHECK(glUniform4f(iLocLMaterial_diffuse_color, 0.3333f, 0.1098f, 0.6941f, 1.0f));
    GL_CHECK(glUniform4f(iLocLMaterial_specular_color,3.0f, 3.0f,3.0f, 1.0f));
    //GL_CHECK(glUniform4f(iLocLMaterial_specular_color, 0.3500f, 0.3500f, 0.3500f, 1.0f));
    GL_CHECK(glUniform1f(iLocLMaterial_specular_exponent, 32.0f));

    static float angleX = 0, angleY = 0, angleZ = 0;
    /*
     * Do some rotation with Euler angles. It is not a fixed axis as
     * quaternions would be, but the effect is nice.
     */

    //Matrix scale = Matrix::createScaling(0.5f, 0.5f, 0.5f);  //###add scale by cgj###//
    Matrix scale = Matrix::createScaling(0.012f, 0.012f, 0.012f);
    Matrix modelView = Matrix::createRotationX(angleX);
    Matrix rotation = Matrix::createRotationY(angleY);

    modelView=modelView * scale;//add scale by cgj

    modelView = rotation * modelView;

    rotation = Matrix::createRotationZ(angleZ);
    modelView = rotation * modelView;

    /* Pull the camera back from the cube */
    modelView[14] -= 2.5;

    Matrix perspective = Matrix::matrixPerspective(45.0f, WINDOW_W_/(float)WINDOW_H_, 0.01f, 100.0f);
    Matrix modelViewPerspective = perspective * modelView;

    GL_CHECK(glUniformMatrix4fv(iLocMVP, 1, GL_FALSE, modelViewPerspective.getAsArray()));


    //Matrix NormalInvert=Matrix::matrixInvert(&modelViewPerspective);
    //NormalInvert.matrixTranspose(&NormalInvert);



    /* Update cube's rotation angles for animating. */
    angleX += 0;
    angleY += 1.5;
    angleZ += 0;

    if(angleX >= 360) angleX -= 360;
    if(angleX < 0) angleX += 360;
    if(angleY >= 360) angleY -= 360;
    if(angleY < 0) angleY += 360;
    if(angleZ >= 360) angleZ -= 360;
    if(angleZ < 0) angleZ += 360;

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 46395));

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

