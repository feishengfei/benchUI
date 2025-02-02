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


#include "yasuo.h"
#include "Sample.h"
#include "Timer.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;

GLuint textureID;
GLuint programID, VAOs, Buffers;
GLuint normalprogramID;

bool setupGraphics()
{
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    ShaderInfo  normalshaders[] = {
            { GL_VERTEX_SHADER,  "yasuo_normal.vert" },
            { GL_GEOMETRY_SHADER, "yasuo_normal.gemo" },
            { GL_FRAGMENT_SHADER, "yasuo_normal.frag" },
            { GL_NONE, NULL }
    };

    normalprogramID = Shader::LoadShaders( normalshaders );


    ShaderInfo  shaders[] = {
            { GL_VERTEX_SHADER,  "yasuo_ob.vert" },
            { GL_FRAGMENT_SHADER, "yasuo_ob.frag" },
            { GL_NONE, NULL }
    };

    programID = Shader::LoadShaders( shaders );

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals) + sizeof(textureCoordinates), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals), sizeof(textureCoordinates), textureCoordinates));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
    GL_CHECK(glEnableVertexAttribArray(2));
    GL_CHECK(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)+sizeof(normals))));

    GL_CHECK(glGenTextures(1, &textureID));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData));
    GL_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); /* Default anyway. */
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GL_CHECK(glEnable(GL_CULL_FACE));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glClearColor(0.5f, 0.5f, 0.5f, 1.0f));

    return true;
}

void renderFrame(void) {

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));//当前纹理单位
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureID));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    static float angleX = 0, angleY = 0, angleZ = 0;
    /*
     * Do some rotation with Euler angles. It is not a fixed axis as
     * quaternions would be, but the effect is nice.
     */

    Matrix scale     = Matrix::createScaling(0.008f, 0.008f, 0.008f);
    Matrix modelView = Matrix::createRotationX(angleX);
    Matrix rotation  = Matrix::createRotationY(angleY);
    Matrix model = Matrix::identityMatrix;
    Matrix perspective = Matrix::matrixPerspective(45.0f, WINDOW_W / (float)WINDOW_H, 0.0001f, 100.0f);

    modelView = modelView * scale;//add scale by cgj
    modelView = rotation * modelView;
    rotation  = Matrix::createRotationZ(angleZ);
    modelView = rotation * modelView;
    modelView[14] -= 2.5;

    Matrix modelViewPerspective = perspective * modelView;

    angleX += 0;
    angleY += 1.5;
    angleZ += 0;

    if (angleX >= 360)
        angleX -= 360;
    if (angleX < 0)
        angleX += 360;
    if (angleY >= 360)
        angleY -= 360;
    if (angleY < 0)
        angleY += 360;
    if (angleZ >= 360)
        angleZ -= 360;
    if (angleZ < 0)
        angleZ += 360;
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glUseProgram(normalprogramID));
    GL_CHECK(glUniformMatrix4fv(0, 1, GL_FALSE, perspective.getAsArray()));
    GL_CHECK(glUniformMatrix4fv(1, 1, GL_FALSE, modelView.getAsArray()));
    GL_CHECK(glUniformMatrix4fv(2, 1, GL_FALSE, model.getAsArray()));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 22374));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glUniform4f(0, 2.0f, 2.0f, 2.0f, 1.0f));
    GL_CHECK(glUniform4f(1, 0.0f, 0.0f, 1.0f, 1.0f));
    GL_CHECK(glUniform4f(2, 1.0f, 1.0f, 1.0f, 1.0f));
    GL_CHECK(glUniform4f(3, 1.0f, 1.0f, 1.0f, 1.0f));
    GL_CHECK(glUniform4f(4, 1.0f, 1.0f, 1.0f, 1.0f));
    GL_CHECK(glUniform4f(5, 1.0f, 1.0f, 1.0f, 1.0f));
    GL_CHECK(glUniform4f(6, 1.0f, 1.0f, 1.0f, 1.0f));
    GL_CHECK(glUniform4f(7, 3.0f, 3.0f, 3.0f, 1.0f));
    GL_CHECK(glUniform1f(8, 32.0f));
    GL_CHECK(glUniformMatrix4fv(9, 1, GL_FALSE, modelViewPerspective.getAsArray()));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 22374));
}

void Sample::test() {
    setupGraphics();

    Timer fpsTimer;
    fpsTimer.reset();
   //bool end = false;
   //while(!end)
    for(int i=0; i<20; i++)
    {
        float fFPS = fpsTimer.getFPS();
        if(fpsTimer.isTimePassed(1.0f))
        {
            printf("FPS:\t%.1f\n", fFPS);
        }
        renderFrame();
              char ss[3];
        sprintf(ss, "%d", i);
        string bmp_file = filename + "-" + ss + ".bmp";
    LOGI("bmp_file=%s",bmp_file.c_str());
    save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

