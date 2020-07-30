
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#include "Texture.h"
#include "Timer.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

string cubemap[]={
        "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"
};

string texpath[6];

Timer this_one;

GLfloat vertices[] = {

        1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f,  1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

          -1.0f, -1.0f,  1.0f,  0.0f, 1.0f,
          -1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
          -1.0f,  1.0f, -1.0f,  1.0f, 0.0f,
          -1.0f,  1.0f, -1.0f,  1.0f, 0.0f,
          -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
          -1.0f, -1.0f,  1.0f,  0.0f, 1.0f,

          -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
           1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
           1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
           1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
          -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
          -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,

          -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
          -1.0f, -1.0f,  1.0f,  0.0f, 1.0f,
           1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
           1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
          -1.0f, -1.0f,  1.0f,  0.0f, 1.0f,
           1.0f, -1.0f,  1.0f,  1.0f, 1.0f,

          -1.0f,  1.0f, -1.0f,  0.0f, 0.0f,
          -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
          1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
          1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
          1.0f,  1.0f, -1.0f,  1.0f, 0.0f,
          -1.0f,  1.0f, -1.0f,  0.0f, 0.0f,


          -1.0f, -1.0f,  1.0f,  1.0f, 1.0f,
          -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
          1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
          1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
          1.0f, -1.0f,  1.0f,  0.0f, 1.0f,
          -1.0f, -1.0f,  1.0f,  1.0f, 1.0f
};

GLuint programID, VAOs, Buffers, texture1;

bool setupGraphics(int w, int h) {
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "cullface.vert"},
            {GL_FRAGMENT_SHADER, "cullface.frag"},
            {GL_NONE, NULL}
    };

    programID = Shader::LoadShaders(shaders);

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), BUFFER_OFFSET(3 * sizeof(float))));


    GL_CHECK(glClearColor(0.2, 0.2, 0.6, 1.0));
    GL_CHECK(glViewport(0, 0, w, h));
}

void render(){
    GL_CHECK(glUseProgram(programID));
    static float angleX = 0, angleY = 0, angleZ = 0;
    Matrix translate = Matrix::createTranslation(0.0, 0.0, 0.0);
    Matrix rotationX = Matrix::createRotationX(angleX);
    Matrix rotationY = Matrix::createRotationY(angleY);
    Matrix perspective = Matrix::matrixPerspective(45.0f,
                                                   WINDOW_W / (float)WINDOW_H, 0.01f, 100.0f);
    Matrix modelView = perspective  * translate * rotationY * rotationX;

    GL_CHECK(glUniformMatrix4fv(0, 1, GL_FALSE, modelView.getAsArray()));

    angleX += 0.0;
    angleY += 10;
    angleZ += 0.0;

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

    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glEnable(GL_DEPTH_TEST));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenTextures(1, &texture1));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));
    TexData image_jpg;
    for(int i = 0; i < 6; i++) {
        texpath[i] = ((string)PICTURE_PATH) + cubemap[i];
        image_jpg.file_name = (char *)texpath[i].c_str();
        read_jpeg(&image_jpg);
        GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_jpg.width, image_jpg.height,
                              0, GL_RGB,GL_UNSIGNED_BYTE, image_jpg.data));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


        GL_CHECK(glActiveTexture(GL_TEXTURE0));
        GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture1));
        GL_CHECK(glDrawArrays(GL_TRIANGLES, 6*i, 6));
    }
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
    GL_CHECK(glDeleteTextures(1, &texture1));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    this_one.reset();
    //bool end = false;
    //while(!end)
    for(int i=0; i<20; i++)
    {
        float fFPS = this_one.getFPS();
        if(this_one.isTimePassed(1.0f))
        {
            printf("FPS:\t%.1f\n", fFPS);
        }
        render();
        Sample::SwapBuffers();
    }
    de_init();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}