/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file drawarrayinstance.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for drawarrayinstance related API
 * @par TestPoints:
 *
 */

#include "Sample.h"
#include <GL/glcorearb.h>
#include "Timer.h"

using std::string;
using namespace BotsonSDK;

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vert[]={ -0.9f, -0.9f,    0.9f, -0.9f,     0.9f, 0.9f,    -0.9f, 0.9f,
                 1.0, 0.0, 0.0,    0.0, 1.0, 0.0,  0.0, 0.0, 1.0, 0.0, 1.0, 1.0
};

GLuint programID[12];
GLuint vao;
GLuint vbo;

bool init_shader(){
    ShaderInfo  shaders[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax0.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[0] = Shader::LoadShaders(shaders);

    ShaderInfo  shaders1[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax1.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[1] = Shader::LoadShaders(shaders1);

    ShaderInfo  shaders2[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax2.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[2] = Shader::LoadShaders(shaders2);

    ShaderInfo  shaders3[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax3.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[3] = Shader::LoadShaders(shaders3);

    ShaderInfo  shaders4[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax4.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[4] = Shader::LoadShaders(shaders4);

    ShaderInfo  shaders5[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax5.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[5] = Shader::LoadShaders(shaders5);

    ShaderInfo  shaders6[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax6.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[6] = Shader::LoadShaders(shaders6);

    ShaderInfo  shaders7[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax7.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[7] = Shader::LoadShaders(shaders7);

    ShaderInfo  shaders8[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax8.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[8] = Shader::LoadShaders(shaders8);

    ShaderInfo  shaders9[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax9.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[9] = Shader::LoadShaders(shaders9);

    ShaderInfo  shaders10[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax10.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[10] = Shader::LoadShaders(shaders10);

    ShaderInfo  shaders11[] = {
            {GL_VERTEX_SHADER, "equalspace.vert", },
            {GL_TESS_CONTROL_SHADER, "glmax11.tcs", },
            {GL_TESS_EVALUATION_SHADER, "glmax.tes", },
            {GL_FRAGMENT_SHADER, "equalspace.frag", },
            {GL_NONE,NULL},
    };
    programID[11] = Shader::LoadShaders(shaders11);
}
bool setupGraphics(int width, int height) {
    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(float)*2*4)));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glClearColor(0.1, 0.1, 0.1, 1.0));
    GL_CHECK(glViewport(0, 0, width, height));

    return true;
}

void renderFrame(int i) {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glUseProgram(programID[i]));
    GL_CHECK(glPatchParameteri(GL_PATCH_VERTICES, 4));
    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    GL_CHECK(glDrawArrays(GL_PATCHES, 0, 4));

}

void Sample::test() {
    init_shader();
    setupGraphics(WINDOW_W, WINDOW_H);
    for (int i = 0; i < 12; i++) {
        renderFrame(i);
        char ss[3];
        sprintf(ss, "%d", i);
        string bmp_file = filename + "-" + ss + ".bmp";
        LOGI("bmp_file=%s\n", bmp_file.c_str());
        save2bmp(bmp_file.c_str());
        Sample::SwapBuffers();
    }
}


int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}
