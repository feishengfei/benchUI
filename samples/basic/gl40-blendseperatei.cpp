/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file uniformmatrix2x3fv.cpp
 * @author Eric.Ma
 * @par History:
 *    A001: Eric.Ma, 2019-11-20, Add commit
 * @brief basic test for related API
 * @par TestPoints:
        glBlendEquationi
        glBlendEquationSeparatei
        glBlendFunci
        glBlendFuncSeparatei
 *
 */

#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;

GLuint programID, VAOs, Buffers;

float Vertices[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f,

    -0.5f,  0.5f,
     0.5f,  0.5f,
     0.0f, -0.5f
};

float Colors[] = {
    0.0, 1.0, 0.0, 0.3,
    0.0, 1.0, 0.0, 0.3,
    0.0, 1.0, 0.0, 0.3,

    0.0, 0.0, 1.0, 0.6,
    0.0, 0.0, 1.0, 0.6,
    0.0, 0.0, 1.0, 0.6
};

GLfloat constant_color[4] = {0.25, 0.0, 1.0, 0.75};

GLenum factors[] = {
//    GL_ZERO,
    GL_ONE,
    GL_SRC_COLOR,
/*    GL_ONE_MINUS_SRC_COLOR,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_CONSTANT_COLOR,
    GL_ONE_MINUS_CONSTANT_COLOR,
    GL_CONSTANT_ALPHA,
    GL_ONE_MINUS_CONSTANT_ALPHA,
    GL_SRC_ALPHA_SATURATE,*/
};

GLenum modes[] = {
    GL_FUNC_ADD,
    GL_FUNC_SUBTRACT,
//    GL_FUNC_REVERSE_SUBTRACT,
//    GL_MIN,
//    GL_MAX
};

bool setupGraphics(GLuint buf, int width, int height, GLenum modeRGB, GLenum modeA,
		GLenum srcRGB, GLenum dstRGB, GLenum srcA, GLenum dstA) {
    string vertexShaderPath = ((string)GLSL_PATH) + "vert2color4_passby.vert"; 
    string fragmentShaderPath = ((string)GLSL_PATH) + "color_passby.frag";

    GL_CHECK(glEnablei(GL_BLEND, buf));
    GL_CHECK(glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcA, dstA));
    GL_CHECK(glBlendEquationSeparatei(buf, modeRGB, modeA));

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    if (programID == 0) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) + sizeof(Colors), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Colors), Colors));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(Vertices))));

    GL_CHECK(glViewport(0, 0, width, height));
    GL_CHECK(glClearColor(0.3f, 0.3f, 0.3f, 0.7f));
    return true;
}


void renderFrame(void) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
}

void Sample::test() {
    GLint bufferNum = 0;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &bufferNum);
    LOGI("get(GL_MAX_DRAW_BUFFERS): %d\n", bufferNum);

    //for (int srcRGB = 0; srcRGB < ARRAY_NUM(factors); srcRGB++) {
    //    for (int dstRGB = 0; dstRGB < ARRAY_NUM(factors); dstRGB++) {
    //        for (int srcA = 0; srcA < ARRAY_NUM(factors); srcA++) {
    //            for (int dstA = 0; dstA < ARRAY_NUM(factors); dstA++) {
    //                for (int modeRGB = 0; modeRGB < ARRAY_NUM(modes); modeRGB++) {
    //                    for (int modeA = 0; modeA < ARRAY_NUM(modes); modeA++) {
    //                        for (GLuint buf = 0; buf < bufferNum; buf++) {
    //                            // if (factors[j] != GL_SRC_ALPHA_SATURATE) {
    //                            setupGraphics(buf, WINDOW_W, WINDOW_H, modes[modeRGB], modes[modeA],
    //                                          factors[srcRGB], factors[dstRGB], factors[srcA], factors[dstA]);
    //                            renderFrame();
    //                            char ss[10];
    //                            sprintf(ss, "_%d%d%d%d%d%d%d", srcRGB, dstRGB, srcA, dstA, modeRGB, modeA, buf);
    //                            string bmp_file = filename + ss + ".bmp";
    //                            LOGI("%s: buf=%d, src(%s,%s) dst(%s,%s) mode(%s,%s)\n", bmp_file.c_str(), buf,
    //                                 get_blending_name(factors[srcRGB]), get_blending_name(factors[srcA]),
    //                                 get_blending_name(factors[dstRGB]), get_blending_name(factors[dstA]),
    //                                 get_blending_name(modes[modeRGB]), get_blending_name(modes[modeA]));
    //                            save2bmp(bmp_file.c_str());
    //                            Sample::SwapBuffers();
//  //              }
    //                        }
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}
    setupGraphics(0, WINDOW_W, WINDOW_H, modes[0], modes[0],
                  factors[0], factors[0], factors[0], factors[0]);
    renderFrame();
    string bmp_file = filename + ".bmp";
    save2bmp(bmp_file.c_str());
    Sample::SwapBuffers();
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, argc, argv);
    sample.test();
    return 0;
}

