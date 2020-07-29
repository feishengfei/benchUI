/* =================================================================
 * Copyright (c) 2019 Botson Cor
 * Botson Confidential and Proprietary
 * =================================================================
 */

/**
 * @file double-write.cpp
 * @author Otto.Liu
 * @par History:
 *    A001: Otto.Liu, 2019-09-02, Add commit
 * @brief basic test for double-write related API
 * @par TestPoints:
 *
 */

#include "Sample.h"

using std::string;
using namespace BotsonSDK;

#define FRUSTUM_DEPTH 2000.0f

// Member variables
float aspect;

// Program to construct the linked list (renders the transparent objects)
GLuint  list_build_program;

// Color palette buffer texture
GLuint  image_palette_buffer;
GLuint  image_palette_texture;

// Output image and PBO for clearing it
GLuint  output_texture;
GLuint  output_texture_clear_buffer;

// Program to render the scene
GLuint render_scene_prog;
struct
{
        GLint aspect;
        GLint time;
        GLint model_matrix;
        GLint view_matrix;
        GLint projection_matrix;
} render_scene_uniforms;

// Program to resolve 
GLuint resolve_program;

// Full Screen Quad
GLuint  quad_vbo;
GLuint  quad_vao;
GLuint render_vao, render_vbo;
GLint current_width;
GLint current_height;
GLuint output_image;
GLuint program, gComputeProgram;
GLuint gVBO;
float radius=0.5;
#define LOG_MAX 255

bool setupGraphics(int width, int height)
{
    int length;
    char log[LOG_MAX];

    string computeShaderPath = (string)GLSL_PATH + "imageStore.comp";
    gComputeProgram = glCreateProgram();
    GLuint mComputeShader;

    Shader::processShader(&mComputeShader, computeShaderPath.c_str(), GL_COMPUTE_SHADER);
    glAttachShader(gComputeProgram, mComputeShader);
    glLinkProgram(mComputeShader);
    int rvalue;
    glGetProgramiv(gComputeProgram, GL_LINK_STATUS, &rvalue);
    if(rvalue) {
        glGetProgramInfoLog(gComputeProgram, LOG_MAX, &length, log);
        printf("Error: Linker log:\n%s", log);
        return false;
    }

    glGenTextures(1, &output_image);
    glBindTexture(GL_TEXTURE_2D, output_image);
    glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, 256, 256);

    string vertexShaderPath = (string)GLSL_PATH + "imageStore.vert";
    string fragmentShaderPath = (string)GLSL_PATH + "imageStore.frag";
    program = Shader::CreateProgram (vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    glViewport(0, 0, width, height);
    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );

    glGenVertexArrays(1, &render_vao);
    glBindVertexArray(render_vao);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &render_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, render_vbo);
    static const float verts[] =
    {
        -1.0f, -1.0f, 0.5f, 1.0f,
         1.0f, -1.0f, 0.5f, 1.0f,
         1.0f,  1.0f, 0.5f, 1.0f,
        -1.0f,  1.0f, 0.5f, 1.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    return true;
}

void renderFrame()
{
    glUseProgram(gComputeProgram);
    glBindImageTexture(0, output_image, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glDispatchCompute(8, 16, 1);

    // Now bind the texture for rendering _from_
    glBindTexture(GL_TEXTURE_2D, output_image);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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
    Sample sample(__FILE__);

    sample.test();

    return 0;
}

//int main(int argc, char **argv)
//{
//    string file = "es30-double-write";
//
//    GBtest_init(&argc,argv,file);
//    Platform * platform = Platform::getInstance();
//    platform->createWindow(WINDOW_W, WINDOW_H);
//    EGLRuntime::initializeEGL(EGLRuntime::OPENGLES31);
//    EGL_CHECK(eglMakeCurrent(EGLRuntime::display, EGLRuntime::surface, EGLRuntime::surface, EGLRuntime::context));
//    setupGraphics(WINDOW_W, WINDOW_H);
//#ifndef DUMP
//    while(1) {
//#endif
//        renderFrame();
//        string filename = file + ".bmp";
//        EGLRuntime::pixelsToPicture(filename.c_str());
//        eglSwapBuffers(EGLRuntime::display, EGLRuntime::surface);
//#ifndef DUMP
//    }
//#endif
//    EGLRuntime::terminateEGL();
//    platform->destroyWindow();
//    delete platform;
//    GBtest_deinit();
//
//    return 0;
//}
//