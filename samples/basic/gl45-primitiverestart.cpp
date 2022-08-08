
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint programID, VAOs, Buffers, ebo;

static const GLfloat cube_positions[] =
                             {
                                     -0.7f,  0.3f, 0.0f, 1.0f,
                                     -0.5f, -0.3f, 0.0f, 1.0f,
                                     -0.3f,  0.3f, 0.0f, 1.0f,
                                     -0.1f, -0.3f, 0.0f, 1.0f,
                                     0.1f, 0.3f, 0.0f, 1.0f,
                                     0.3f,  -0.3f, 0.0f, 1.0f,
                                     0.5f,  0.3f, 0.0f, 1.0f,
                                     0.7f, -0.3f, 0.0f, 1.0f
                             };

static const GLfloat cube_colors[] =
                             {
                                     1.0f, 1.0f, 1.0f, 1.0f,
                                     1.0f, 1.0f, 0.0f, 1.0f,
                                     1.0f, 0.0f, 1.0f, 1.0f,
                                     1.0f, 0.0f, 0.0f, 1.0f,
                                     0.0f, 1.0f, 1.0f, 1.0f,
                                     0.0f, 1.0f, 0.0f, 1.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f,
                                     0.5f, 0.5f, 0.5f, 1.0f
                             };

static const GLushort cube_indices[] =
                              {
                                      0, 1, 2, 3,
                                      0xFFFF,
                                      4, 5, 6, 7
                              };

bool setupGraphics(int w, int h) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "primitiverestart.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "primitiverestart.frag";

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

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(cube_positions) + sizeof(cube_colors),
                 NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_positions), cube_positions));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_positions), sizeof(cube_colors), cube_colors));

    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cube_positions))));
    GL_CHECK(glEnableVertexAttribArray(1));

    GL_CHECK(glGenBuffers(1, &ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), &cube_indices, GL_STATIC_DRAW));

    GL_CHECK(glViewport(0, 0, w, h));

}

void render(){
    GL_CHECK(glClearColor(0.5, 0.0, 0.2, 1.0));
    GL_CHECK(glEnable(GL_PRIMITIVE_RESTART));
    GL_CHECK(glPrimitiveRestartIndex(0xFFFF));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawElements(GL_TRIANGLE_FAN, 17, GL_UNSIGNED_SHORT, NULL));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
    GL_CHECK(glDeleteBuffers(1, &ebo));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    render();
    string bmp_file1 = filename + ".bmp";
    save2bmp(bmp_file1.c_str());
    SwapBuffers();
    de_init();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}