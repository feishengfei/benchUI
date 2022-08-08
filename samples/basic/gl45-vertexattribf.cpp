#include "Sample.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat vertex[] = {
        -0.8, -0.8, 0.0, 1.0,
        -0.4, -0.8, 0.0, 1.0,
        -0.6, -0.2, 0.0, 1.0,

        -0.4, -0.8, 0.0, 1.0,
        -0.2, -0.2, 0.0, 1.0,
         0.0, -0.8, 0.0, 1.0,/*4f*/

         0.8, -0.8, 0.0, 1.0,
         0.4, -0.8, 0.0, 1.0,
         0.6, -0.2, 0.0, 1.0,/*4fv*/

         0.4, -0.8, 0.0, 1.0,
         0.2, -0.2, 0.0, 1.0,
         0.0, -0.8, 0.0, 1.0,/*3f*/

        -0.8,  0.8, 0.0, 1.0,
        -0.4,  0.8, 0.0, 1.0,
        -0.6,  0.2, 0.0, 1.0,/*3fv*/

        -0.4,  0.8, 0.0, 1.0,
        -0.2,  0.2, 0.0, 1.0,
         0.0,  0.8, 0.0, 1.0,/*2f*/

         0.8,  0.8, 0.0, 1.0,
         0.4,  0.8, 0.0, 1.0,
         0.6,  0.2, 0.0, 1.0,/*2fv*/

         0.4,  0.8, 0.0, 1.0,
         0.2,  0.2, 0.0, 1.0,
         0.0,  0.8, 0.0, 1.0,/*1f*/

        -0.2, -0.2, 0.0, 1.0,
         0.2, -0.2, 0.0, 1.0,
         0.0,  0.2, 0.0, 1.0,/*1fv*/
};

GLfloat color[] = {
        1.0 , 0.0, 0.0 ,1.0,
        0.0 , 1.0, 0.0 ,1.0,
        0.0 , 0.0, 1.0 ,1.0
};

GLuint Program = 0;

GLuint vert;
GLuint vbo;

bool setupGraphics(int w, int h) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "vertexattribf.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "vertexattribf.frag";

    Program = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (!Program) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(Program));

    GL_CHECK(glGenVertexArrays(1, &vert));
    GL_CHECK(glBindVertexArray(vert));

    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) + sizeof(color), NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color), color));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(color), sizeof(vertex), vertex));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,0,
                                   BUFFER_OFFSET(sizeof(color))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glUseProgram(Program));
    GL_CHECK(glViewport(0, 0, w, h));
}

void render() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(vert));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 24, 3));

    GL_CHECK(glVertexAttrib4f(0, 0.0, 0.0, 1.0, 1.0));
    GL_CHECK(glDisableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    const GLfloat col[4] = {0.0, 0.0, 1.0, 1.0};
    GL_CHECK(glVertexAttrib4fv(0, &col[0]));
    GL_CHECK(glDisableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 3, 3));

    GL_CHECK(glVertexAttrib3f(0, 1.0, 0.0, 1.0));
    GL_CHECK(glDisableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 6, 3));

    const GLfloat col1[3] = {1.0, 0.0, 1.0};
    GL_CHECK(glVertexAttrib3fv(0, &col1[0]));
    GL_CHECK(glDisableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 9, 3));

    GL_CHECK(glVertexAttrib2f(0, 1.0, 1.0));
    GL_CHECK(glDisableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 12, 3));

    const GLfloat col2[2] = {1.0, 1.0};
    GL_CHECK(glVertexAttrib2fv(0, &col2[0]));
    GL_CHECK(glDisableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 15, 3));

    GL_CHECK(glVertexAttrib1f(0, 1.0));
    GL_CHECK(glDisableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 18, 3));

    const GLfloat col3[1] = {1.0};
    GL_CHECK(glVertexAttrib1fv(0, &col3[0]));
    GL_CHECK(glDisableVertexAttribArray(0));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 21, 3));

}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &vert));
    GL_CHECK(glDeleteBuffers(1, &vbo));
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
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}