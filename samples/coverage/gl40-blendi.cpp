#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
using std::string;
using namespace BotsonSDK;

GLuint programID, VAOs, Buffers;

float Vertices[] = {
    -0.8f, -0.8f,
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
    GL_FUNC_REVERSE_SUBTRACT,
    GL_MIN,
    GL_MAX
};

void getdata() {
    GLboolean param;
    GLfloat paramf[4];
    GLint parami;

    GL_CHECK(glGetBooleanv(GL_BLEND, &param));
    LOGI("get(GL_BLEND): %d\n", param);
    GL_CHECK(glGetFloatv(GL_BLEND_COLOR, paramf));
    LOGI("get(GL_BLEND_COLOR): %f %f %f %f\n", paramf[0], paramf[1], paramf[2], paramf[3]);
    GL_CHECK(glGetIntegerv(GL_BLEND_DST_ALPHA, &parami));
    LOGI("get(GL_BLEND_DST_ALPHA): %d\n", parami);
    GL_CHECK(glGetIntegerv(GL_BLEND_DST_RGB, &parami));
    LOGI("get(GL_BLEND_DST_RGB): %d\n", parami);
    GL_CHECK(glGetIntegerv(GL_BLEND_SRC_ALPHA, &parami));
    LOGI("get(GL_BLEND_SRC_ALPHA): %d\n", parami);
    GL_CHECK(glGetIntegerv(GL_BLEND_SRC_RGB, &parami));
    LOGI("get(GL_BLEND_SRC_RGB): %d\n", parami);

    GL_CHECK(glGetIntegerv(GL_DRAW_BUFFER, &parami));
    LOGI("get(GL_DRAW_BUFFER): %x\n", parami);
    GL_CHECK(glGetIntegerv(GL_READ_BUFFER, &parami));
    LOGI("get(GL_READ_BUFFER): %x\n", parami);
    GL_CHECK(glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &parami));
    LOGI("get(GL_MAX_COLOR_ATTACHMENTS): %d\n", parami);
    GL_CHECK(glGetIntegerv(GL_MAX_DRAW_BUFFERS, &parami));
    LOGI("get(GL_MAX_DRAW_BUFFERS): %d\n", parami);
}

bool setupGraphics(GLuint buf, int width, int height, GLenum mode, GLenum src_factor_rgb, GLenum dst_factor_rgb) {
    string vertexShaderPath = ((string)GLSL_PATH) + "vert2color4_passby.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "color_passby.frag";

    GL_CHECK(glEnablei(GL_BLEND, buf));
    GL_CHECK(glBlendFunci(buf, src_factor_rgb, dst_factor_rgb));
    GL_CHECK(glBlendEquationi(buf, mode));
    if(needs_blend_color(src_factor_rgb) || needs_blend_color(dst_factor_rgb)) {
        GL_CHECK(glBlendColor(constant_color[0], constant_color[1], constant_color[2], constant_color[3]));
    }
    getdata();

    programID = Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    if (programID == 0) {
        LOGE("Could not create program.\n");
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

    //for (int i = 0; i < ARRAY_NUM(factors); i++) {
    //    for (int j = 0; j < ARRAY_NUM(factors); j++) {
    //        for (int mode = 0; mode < ARRAY_NUM(modes); mode++) {
    //            for (GLuint buf = 0; buf < bufferNum; buf++) {
    //                if (factors[j] != GL_SRC_ALPHA_SATURATE) {
    //                    setupGraphics(buf, WINDOW_W, WINDOW_H, modes[mode], factors[i], factors[j]);
    //                    renderFrame();
    //                    char ss[10];
    //                    sprintf(ss, "%d%d%d%d", i, j, mode, buf);
    //                    string bmp_file = filename + ss + ".bmp";
    //                    LOGI("%s: buf=%d, src=%s, dst=%s, mode=%s\n", bmp_file.c_str(), buf,
    //                         get_blending_name(factors[i]), get_blending_name(factors[j]),
    //                         get_blending_name(modes[mode]));
    //                    save2bmp(bmp_file.c_str());
    //                    Sample::SwapBuffers();
    //                }
    //            }
    //        }
    //    }
    //}
    setupGraphics(0, WINDOW_W, WINDOW_H, modes[1], factors[0], factors[0]);
    //setupGraphics(WINDOW_W, WINDOW_H);
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

