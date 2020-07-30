
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */


#include "Sample.h"
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint Program, VAOs, Buffers, aco1, aco2;

GLfloat vertices[] = {0.9, -0.9,
                      0.7, -0.5,
                      0.5, -0.9};

GLfloat vertColor[] = {0.3, 0, 0,
                       0, 0.3, 0,
                       0, 0, 0.3};


bool setupGraphics(int w, int h) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "atomiccounter2.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "atomiccounter2.frag";

    Program = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (!Program) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(Program));

    GL_CHECK(glGenVertexArrays(1, &VAOs));
    GL_CHECK(glBindVertexArray(VAOs));

    GL_CHECK(glGenBuffers(1, &Buffers));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Buffers));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertColor) + sizeof(vertices),
                 NULL, GL_STATIC_DRAW));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
    GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertColor), vertColor));

    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0)));
    GL_CHECK(glEnableVertexAttribArray(0));
    GL_CHECK(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
    GL_CHECK(glEnableVertexAttribArray(1));
    GL_CHECK(glViewport(0, 0, w, h));


    GL_CHECK(glGenBuffers(1, &aco1));
    GL_CHECK(glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, aco1));
    GL_CHECK(glBufferData(GL_ATOMIC_COUNTER_BUFFER, 5*sizeof(GLuint), NULL, GL_DYNAMIC_COPY));
    GLuint data[5] = {0, 0, 0, 0, 0};
    GL_CHECK(glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, 5*sizeof(GLuint), &data));
    GL_CHECK(glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, aco1));
}

void render(int k){
    GL_CHECK(glUseProgram(Program));
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
    GL_CHECK(glBindVertexArray(VAOs));
    GL_CHECK(glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, aco1));
    GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));

    GLint params;
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_BINDING, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_BINDING = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(Program, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER = %d\n", params);
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VAOs));
    GL_CHECK(glDeleteBuffers(1, &Buffers));
    GL_CHECK(glDeleteBuffers(1, &aco1));
    GL_CHECK(glDeleteBuffers(1, &aco2));
}

void Sample::test() {
    setupGraphics(WINDOW_W, WINDOW_H);
    for(int i=0; i<6; i++){
        char ss[5];
        sprintf(ss, "%d", i);
        render(i);
        string bmp_file1 = filename + "-" + ss + ".bmp";
        save2bmp(bmp_file1.c_str());
        SwapBuffers();
    }
    de_init();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_MULTISAMPLE | GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}