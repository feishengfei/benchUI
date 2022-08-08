/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file texparameterI.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for texparameterI related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;
GLuint programID;
GLuint tex;
GLuint vao;
GLuint vbo;
#define VertexCount 6

typedef struct {
    float x;
    float b;
} vec2;

typedef struct {
    vec2 vertex;
    vec2 texcoord;
} vertex_v2fv2f;

vertex_v2fv2f VertexData[VertexCount] =
                      {
                              {{-0.4f,-0.4f}, {0.0f, 1.0f}},
                              {{ 0.4f,-0.4f}, {1.0f, 1.0f}},
                              {{ 0.4f, 0.4f}, {1.0f, 0.0f}},
                              {{ 0.4f, 0.4f}, {1.0f, 0.0f}},
                              {{-0.4f, 0.4f}, {0.0f, 0.0f}},
                              {{-0.4f,-0.4f}, {0.0f, 1.0f}}
                      };

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#define	iWidth 16
#define	iHeight 16
#define iDepth 16
static GLubyte image[iDepth][iHeight][iWidth][4];

void makeImage(void)
{
    int s, t, r;

    for (s = 0; s < iWidth; s++)
        for (t = 0; t < iHeight; t++)
            for (r = 0; r < iDepth; r++) {
                image[r][t][s][0] = (GLubyte) (s * 17);
                image[r][t][s][1] = (GLubyte) (t * 8);
                image[r][t][s][2] = (GLubyte) (r * 17);
                image[r][t][s][3] = (GLubyte) (r * 17);
            }
}

bool initTexture()
{
    GLint MaxTextureArrayLayers = 0;
    GL_CHECK(glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &MaxTextureArrayLayers));
    LOGI("GetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS): %d\n", MaxTextureArrayLayers);
    GL_CHECK(glGenTextures(1, &tex));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, tex));
    makeImage();
    GL_CHECK(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, iWidth, iHeight, iDepth));
    GL_CHECK(glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, iWidth, iHeight, iDepth,
                             GL_RGBA, GL_UNSIGNED_BYTE, image));

    GL_CHECK(glPixelStorei(GL_UNPACK_ALIGNMENT, 4));

}

void initVertexArray()
{
    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(vertex_v2fv2f),
                          VertexData, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_v2fv2f),
                                   BUFFER_OFFSET(0)));
    GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_v2fv2f),
                                   BUFFER_OFFSET(sizeof(vec2))));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glEnableVertexAttribArray(1));
}

bool initSampler() {
    GLfloat get[4];
    const GLint baselevel = 0;
    const GLuint max_level = 1000;
    GLuint maxlevel;
    const GLint base = 0;
    GLint max_lod, min_lod;

    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    GL_CHECK(glTexParameterIiv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, &baselevel));
    GL_CHECK(glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_LOD, -1000.f));
    GL_CHECK(glTexParameterIuiv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, &max_level));
    GL_CHECK(glGetTexParameterIuiv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, &maxlevel))
    LOGI("MAX LEVEL IS %d\n", maxlevel);
    GL_CHECK(glTexParameteriv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, &base));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_MODE, GL_NONE));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
    GL_CHECK(glGetTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, get));
    LOGI("border color:%f, %f, %f, %f\n", get[0], get[1], get[2], get[3]);
    GL_CHECK(glGetTexParameterIiv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LOD, &max_lod));
    LOGI("max lod = %d\n", max_lod);
    GL_CHECK(glGetTexParameteriv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_LOD, &min_lod));
    LOGI("min lod = %d\n", min_lod);
}


void initProgram()
{
    string vertexShaderPath = (string)GLSL_PATH + "texstorage3d.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "texstorage3d.frag";

    programID = Shader::CreateProgram(vertexShaderPath.c_str(),
            fragmentShaderPath.c_str());
}

bool setupGraphics(int w, int h) {
    makeImage();
    glViewport(0, 0, w, h);
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.0));
    initProgram();
    initVertexArray();
    initTexture();
    initSampler();
}

void renderFrame() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D_ARRAY, tex));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, VertexCount));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    renderFrame();
    string bmp_file  = filename + ".bmp";
    LOGI("bmp_file=%s", bmp_file.c_str());
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

