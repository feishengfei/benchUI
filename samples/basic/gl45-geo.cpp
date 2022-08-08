#include "Sample.h"

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLfloat points[] = {
        -0.5, 0.5, 1.0, 0.0, 0.0,
        0.5, 0.5, 0.0, 1.0, 0.0,
        0.5, -0.5, 0.0, 0.0, 1.0,
        -0.5, -0.5, 1.0, 1.0, 0.0
};

GLuint Program = 0;

GLuint vert;
GLuint vbo;

bool setupGraphics(int w, int h) {
    string vertexShaderPath = "geo.vert";
    string geometryShaderPath = "geo.geom";
    string fragmentShaderPath = "geo.frag";

    ShaderInfo  shaders[] = {
            { GL_VERTEX_SHADER,   vertexShaderPath.c_str() },
            { GL_GEOMETRY_SHADER, geometryShaderPath.c_str() },
            { GL_FRAGMENT_SHADER, fragmentShaderPath.c_str() },
            { GL_NONE, NULL }
    };

    Program = Shader::LoadShaders(shaders);
    GL_CHECK(glUseProgram(Program));

    GL_CHECK(glGenVertexArrays(1, &vert));
    GL_CHECK(glBindVertexArray(vert));

    GL_CHECK(glGenBuffers(1, &vbo));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW));
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), BUFFER_OFFSET(2*sizeof(float))));
    GL_CHECK(glEnableVertexAttribArray(1));

    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glUseProgram(Program));
    GL_CHECK(glViewport(0, 0, w, h));
}

void render() {
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glUseProgram(Program));
    GL_CHECK(glBindVertexArray(vert));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, 4));
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