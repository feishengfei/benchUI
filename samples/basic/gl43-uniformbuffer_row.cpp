
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vertices[] = {
        -0.8, -0.8, 0.0, 1.0,
         0.0,  0.8, 0.0, 1.0,
         0.8, -0.8, 0.0, 1.0
};

GLfloat color[] = {
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0
};

GLuint programID_row, VAOs, Buffers, buf, block_index;


bool setupGraphics(int w, int h) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "ubo_row.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "ubo.frag";

    programID_row = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(),
            fragmentShaderPath.c_str()));
    GL_CHECK(glUseProgram(programID_row));
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

    Matrix rotation  = Matrix::createRotationX(-45.0);
    Matrix scale     = Matrix::createScaling(0.3f, 1.0f, 1.0f);
    Matrix translate_row = Matrix::createTranslation(0.3, 0.0, 0.0);
    Matrix translate = Matrix::matrixTranspose(&translate_row);

    GLint blockSize;
    GL_CHECK(glGetActiveUniformBlockiv(programID_row, 0, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize));
    GLubyte *blockBuffer=(GLubyte *)malloc(blockSize);
    memcpy(blockBuffer+0, rotation.getAsArray(), 16*sizeof(float));
    memcpy(blockBuffer+16*sizeof(float), scale.getAsArray(), 16*sizeof(float));
    memcpy(blockBuffer+32*sizeof(float), translate.getAsArray(), 16*sizeof(float));

    block_index = GL_CHECK(glGetUniformBlockIndex(programID_row, "MVP"));
    LOGI("UNIFORM BLOCK INDEX IS %d\n", block_index);
    GL_CHECK(glUniformBlockBinding(programID_row, block_index, 0));
    GL_CHECK(glGenBuffers(1, &buf));
    GL_CHECK(glBindBuffer(GL_UNIFORM_BUFFER, buf));
    GL_CHECK(glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_COPY));
    GL_CHECK(glBindBufferBase(GL_UNIFORM_BUFFER, 0, buf));

    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glViewport(0, 0, w, h));

}

void render(){
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
    GL_CHECK(glDeleteBuffers(1, &buf));
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