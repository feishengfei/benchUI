/**
 * @file gl13-depth.c
 * @testpoint glDepthFunc glClearDepthf glDepthRangef glDepthMask
 *
 */
#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, VAOs, Buffers;
GLfloat vertices[] = {
        -0.5, 0.5, 1.0, 1.0,
        0.0, -0.5, 1.0, 1.0,
        0.5, 0.5, 1.0, 1.0,
        -0.5, -0.5, 0.2, 1.0,
        0.0, 0.5, 0.2, 1.0,
        0.5, -0.5, 0.2, 1.0
};

GLfloat color[] = {
       1.0, 0.0, 0.0, 0.2,
       0.0, 1.0, 0.0, 0.2,
       1.0, 0.0, 1.0, 0.2,
       1.0, 1.0, 0.0, 0.8,
       1.0, 0.0, 1.0, 0.8,
       0.0, 1.0, 1.0, 0.8
};

static const GLenum masks[] = {
        GL_TRUE,
        GL_FALSE
};

static const GLenum funcs[] = {
        GL_NEVER,
        GL_LESS,
        GL_EQUAL,
        GL_LEQUAL,
        GL_GREATER,
        GL_NOTEQUAL,
        GL_GEQUAL,
        GL_ALWAYS
};

bool setupGraphics(int w, int h)
{
    string vertexShaderPath   = ((string)GLSL_PATH) + "shader.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "shader.frag";

    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (!programID) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(programID));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(color), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(color), color));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
    GL_CHECK(glClearDepthf(0.5f));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 0.5));
    GL_CHECK(glViewport(0, 0, w, h));
    return true;
}


void renderFrame(GLenum func, GLboolean mask)
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glDepthMask(mask));
    GL_CHECK(glDepthFunc(func));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 6));
}


void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<ARRAY_NUM(funcs); i++) {
        for (int j = 0; j < 2; j++) {
            string func_name = get_enum_name(funcs[i]);
            string mask_name = get_enum_name(masks[j]);
            string bmp_file1  = filename + "-func-" + func_name + "_mask_" + mask_name + ".bmp";
            LOGI("[%d_%d]: %s  %s,  filename=%s\n", i, j, func_name.c_str(), mask_name.c_str(), filename.c_str());
            renderFrame(funcs[i], masks[j]);
            save2bmp(bmp_file1.c_str());
        }
    }
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}
