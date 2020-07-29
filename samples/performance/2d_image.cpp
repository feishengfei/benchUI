/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texstorage2d.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texstorage2d related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include "Timer.h"

using std::string;
using namespace BotsonSDK;
GLuint programID, VAOs, Buffers;
const static int          FRAMES_NUM = 10;
GLuint tex, sampler;

#define BUFFER_OFFSET(x)  ((const void*) (x))
#define	iWidth 4
#define	iHeight 4

float vertices[] = {
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
};

float texcoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
};


bool setupGraphics() {
    string vertexShaderPath = (string)GLSL_PATH + "Sampler.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "Sampler.frag";
    string textureShaderPath = (string)PICTURE_PATH + "cat.jpg";
    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());

    glUseProgram(programID);

    TexData image_jpg;
    image_jpg.file_name = (char *)textureShaderPath.c_str();
    read_jpeg(&image_jpg);
    GL_CHECK(glGenTextures(1, &tex));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, tex));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image_jpg.width, image_jpg.height,
                          0, GL_RGB,GL_UNSIGNED_BYTE, image_jpg.data));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(texcoords), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(texcoords), texcoords));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));

    GL_CHECK(glViewport(0, 0, WINDOW_W, WINDOW_H));
    GL_CHECK(glClearColor (0.5, 0.2, 1.0, 1.0));
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    return true;
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    const GLint color[4]={1, 0, 1, 1};
    GL_CHECK(glGenSamplers(1,&sampler));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER,GL_LINEAR));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER,GL_LINEAR));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT));
    GL_CHECK(glSamplerParameteriv(sampler,GL_TEXTURE_BORDER_COLOR, color));
    GL_CHECK(glBindSampler(0,sampler));

    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D,tex));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_FAN, 0, 4));
}

void clean_up(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteTextures(1, &tex));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
    GL_CHECK(glDeleteProgram(programID));
}
void Sample::test() {
    Timer    *time     = new Timer();
    double   flopstime = 0.0;
    for (int j         = 0; j < FRAMES_NUM; j++) {
        time->reset();
        setupGraphics();
        renderFrame();
        glFlush();
        flopstime = flopstime + time->getTime();
        string bmp_file = filename + ".bmp";
        save2bmp(bmp_file.c_str());
        SwapBuffers();
        clean_up();
    }
    double   ave_time  = flopstime / FRAMES_NUM;
    LOGI("image2d One frame average time:--%f\n", ave_time);
}


int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
