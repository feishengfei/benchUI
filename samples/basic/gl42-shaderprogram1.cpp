
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint vao, vbo, vs, fs, pipe;

static GLuint g_getOffsetRedSubIndex;
static GLuint g_getOffsetGreenSubIndex;
static GLuint g_getOffsetBlueSubIndex;

GLfloat points[] = {
        -0.25, 0.0, 0.0, 1.0,
        0.25, 0.0, 0.0, 1.0,
        0.0, 0.25, 0.0, 1.0
};

GLfloat color[] = {
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0
};

bool setupGraphics(int w, int h) {
    const char *strings[1] = { NULL };
    string vertexShaderPath   = ((string)GLSL_PATH) + "shaderprogram1.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "shaderprogram1.frag";

    strings[0] = Shader::loadShader(vertexShaderPath.c_str());
    vs = GL_CHECK(glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings));
    GLint compiled;
    glGetProgramiv(vs, GL_LINK_STATUS, &compiled);
    if (!compiled) {
        GLint length;
        GLchar *log;
        glGetProgramiv(vs, GL_INFO_LOG_LENGTH, &length);

        log = (GLchar *)malloc(length);
        glGetProgramInfoLog(vs, length, &length, log);
        printf("%s", log);
        free(log);
    }
    strings[0] = Shader::loadShader(fragmentShaderPath.c_str());
    fs = GL_CHECK(glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings));
    GLint compiled1;
    glGetProgramiv(fs, GL_LINK_STATUS, &compiled1);
    if (!compiled1) {
        GLint length;
        GLchar *log;
        glGetProgramiv(fs, GL_INFO_LOG_LENGTH, &length);

        log = (GLchar *)malloc(length);
        glGetProgramInfoLog(fs, length, &length, log);
        printf("%s", log);
        free(log);
    }
    GL_CHECK(glGenProgramPipelines(1, &pipe));
    GL_CHECK(glBindProgramPipeline(pipe));

    GL_CHECK(glUseProgramStages(pipe, GL_VERTEX_SHADER_BIT, vs));
    GL_CHECK(glUseProgramStages(pipe, GL_FRAGMENT_SHADER_BIT, fs));

    GL_CHECK(glGenVertexArrays(1, &vao));
    GL_CHECK(glGenBuffers(1, &vbo));

    GL_CHECK(glBindVertexArray(vao));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(color),
                          NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(color), color));
    GL_CHECK(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points))));
    GL_CHECK(glEnableVertexAttribArray(1));

    g_getOffsetRedSubIndex = GL_CHECK(glGetSubroutineIndex(vs, GL_VERTEX_SHADER, "redOffset"));
    LOGI("red offset index is %d\n", g_getOffsetRedSubIndex);
    g_getOffsetGreenSubIndex = GL_CHECK(glGetSubroutineIndex(vs, GL_VERTEX_SHADER, "greenOffset"));
    LOGI("green offset index is %d\n", g_getOffsetGreenSubIndex);
    g_getOffsetBlueSubIndex = GL_CHECK(glGetSubroutineIndex(vs, GL_VERTEX_SHADER, "blueOffset"));
    LOGI("blue offset index is %d\n", g_getOffsetBlueSubIndex);

    GL_CHECK(glViewport(0, 0, w, h));
    GL_CHECK(glClearColor(0.0, 0.0, 0.0, 1.0));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void render(){
    GL_CHECK(glBindVertexArray(vao));

    GLint value;
    GL_CHECK(glGetProgramStageiv(vs, GL_VERTEX_SHADER, GL_ACTIVE_SUBROUTINES, &value));
    LOGI("vertex shader active subroutine is %d\n", value);
    GL_CHECK(glGetProgramStageiv(vs, GL_VERTEX_SHADER, GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &value));
    LOGI("vertex shader active subroutine uniform location is %d\n", value);


    GL_CHECK(glActiveShaderProgram(pipe, vs));
    GL_CHECK(glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &g_getOffsetRedSubIndex));
    GL_CHECK(glActiveShaderProgram(pipe, fs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glActiveShaderProgram(pipe, vs));
    GL_CHECK(glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &g_getOffsetGreenSubIndex));
    GL_CHECK(glActiveShaderProgram(pipe, fs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GL_CHECK(glActiveShaderProgram(pipe, vs));
    GL_CHECK(glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &g_getOffsetBlueSubIndex));
    GL_CHECK(glActiveShaderProgram(pipe, fs));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &vao));
    GL_CHECK(glDeleteBuffers(1, &vbo));
    GL_CHECK(glDeleteProgramPipelines(1, &pipe));
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