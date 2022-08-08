/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file sampler-wrap2d.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for sampler-wrap2d related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;
GLuint query;
GLuint programID, VAOs, Buffers;
GLuint sampler=0;
GLuint texBufferObject;

float vertices[] = {
    -1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
};

float texcoords[] = {
    -2.0f, 3.0f,
    -2.0f, -2.0f,
    3.0f, 3.0f,
    3.0f, -2.0f,
};

GLenum factors[] = {
	GL_CLAMP_TO_EDGE, 
	GL_MIRRORED_REPEAT,
	GL_REPEAT,
};

bool setupGraphics(int width, int height) {
    string vertexShaderPath = (string)GLSL_PATH + "Sampler.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "Sampler.frag";
    string textureShaderPath = (string)PICTURE_PATH + "cat.jpg";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
                                      fragmentShaderPath.c_str());
    GL_CHECK(glUseProgram(programID));

    TexData image_jpg;
    image_jpg.file_name = (char *)textureShaderPath.c_str();
    read_jpeg(&image_jpg);
    GL_CHECK(glGenTextures(1, &texBufferObject));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texBufferObject));
    LOGI("TEXTURE IS %d\n", glIsTexture(texBufferObject));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, image_jpg.width, image_jpg.height,
                 0, GL_RGB,GL_UNSIGNED_BYTE, image_jpg.data));
    GLfloat res[image_jpg.width*image_jpg.height];

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0));
    free(image_jpg.data);

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

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CHECK(glClearDepthf(1.0f));

    return true;
}

void renderFrame(GLenum factor) {
    GL_CHECK(glGenQueries(1,&query));
    GL_CHECK(glBeginQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, query));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    const GLint color[4]={1, 0, 1, 1};
    GL_CHECK(glGenSamplers(1,&sampler));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER,GL_LINEAR));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER,GL_LINEAR));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S,factor));
    GL_CHECK(glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T,factor));
    GL_CHECK(glSamplerParameteriv(sampler,GL_TEXTURE_BORDER_COLOR, color));

    GLint param;
    GLint iparams;
    GLfloat fparams;
    GL_CHECK(glGetSamplerParameteriv(sampler, GL_TEXTURE_WRAP_S,&param));
    LOGI("glGetSamplerParameteriv(GL_TEXTURE_WRAP_S)=%x\n",get_enum_name(param));
    GL_CHECK(glGetSamplerParameteriv(sampler, GL_TEXTURE_WRAP_T,&param));
    LOGI("glGetSamplerParameteriv(GL_TEXTURE_WRAP_T)=%x\n",get_enum_name(param));
    GL_CHECK(glGetTexLevelParameterfv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&fparams));
    GL_CHECK(glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&iparams));
    LOGI("glGetTexLevelParameterfv GL_TEXTURE_WIDTH = %f\n",fparams);
    LOGI("glGetTexLevelParameteriv GL_TEXTURE_WIDTH = %d\n",iparams);

    GLfloat par;
    GL_CHECK(glGetSamplerParameterfv(sampler, GL_TEXTURE_MIN_LOD,&par));
    LOGI("glGetSamplerParameterfv(GL_TEXTURE_MIN_LOD)=%f",par);
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glEnable(GL_SCISSOR_TEST));
    GL_CHECK(glScissor(0,0,160,320));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D,texBufferObject));
    GL_CHECK(glBindSampler(0,sampler));

    GLboolean isSampler=glIsSampler(sampler);
    LOGI("glIsSampler:sampler=%d\n",sampler);

    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
    GL_CHECK(glEndQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE));

    GL_CHECK(glDeleteQueries(1, &query));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(factors); i++) {
        renderFrame(factors[i]);
        string mode_name = get_enum_name(factors[i]);
        string bmp_file  = filename + "-" + mode_name + ".bmp";
        LOGI("bmp_file=%s\n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
    glDeleteSamplers(1,&sampler);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
