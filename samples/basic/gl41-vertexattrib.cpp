#include "Sample.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLdouble vertex[] = {
        -0.2, -0.2, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
         0.2, -0.2, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
         0.0,  0.2, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,

        0.8,  0.8, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
        0.4,  0.8, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
        0.6,  0.2, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,

        0.4,  0.8, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
        0.2,  0.2, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
        0.0,  0.8, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,

        -0.8,  0.8, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
        -0.4,  0.8, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
        -0.6,  0.2, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,

        -0.4,  0.8, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
        -0.2,  0.2, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
        0.0,  0.8, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,

        -0.8, -0.8, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
        -0.4, -0.8, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
        -0.6, -0.2, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
        
        -0.4, -0.8, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
        -0.2, -0.2, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
         0.0, -0.8, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
        
         0.8, -0.8, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
         0.4, -0.8, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
         0.6, -0.2, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
        
         0.4, -0.8, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0,
         0.2, -0.2, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
         0.0, -0.8, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
};


GLuint Program = 0;

GLuint vert;
GLuint vbo;

bool setupGraphics(int w, int h) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "vertexattrib.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "vertexattrib.frag";

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
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribLPointer(0, 4, GL_DOUBLE, 8*sizeof(double), BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribLPointer(1, 4, GL_DOUBLE, 8*sizeof(double), BUFFER_OFFSET(4*sizeof(double))));
    GL_CHECK(glEnableVertexAttribArray(1));


    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glUseProgram(Program));
    GL_CHECK(glViewport(0, 0, w, h));
}

void render() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(vert));

    GL_CHECK(glVertexAttribL4d(1, 1.0, 1.0, 0.0, 1.0));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 3, 3));

    const GLdouble col[4] = {1.0, 1.0, 0.0, 1.0};
    GL_CHECK(glVertexAttribL4dv(1, &col[0]));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 6, 3));

    GL_CHECK(glVertexAttribL3d(1, 0.0, 0.0, 1.0));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 9, 3));

    const GLdouble col1[3] = {0.0, 0.0, 1.0};
    GL_CHECK(glVertexAttribL3dv(1, &col1[0]));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 12, 3));

    GL_CHECK(glVertexAttribL2d(1, 1.0, 0.0));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 15, 3));

    const GLdouble col2[2] = {1.0, 0.0};
    GL_CHECK(glVertexAttribL2dv(1, &col2[0]));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 18, 3));

    GL_CHECK(glVertexAttribL1d(1, 1.0));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 21, 3));

    const GLdouble col3[1] = {1.0};
    GL_CHECK(glVertexAttribL1dv(1, &col3[0]));
    GL_CHECK(glDisableVertexAttribArray(1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 24, 3));

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