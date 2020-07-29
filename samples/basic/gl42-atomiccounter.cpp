
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */

#include "Sample.h"

GLuint Program;
GLuint VertexArrayName;
GLuint BufferName[2];

struct {
    GLenum interfmt;
    GLenum format;
    GLenum type;
} factors[] = {
        {GL_R8, GL_RED , GL_UNSIGNED_BYTE},
        {GL_R16, GL_RED , GL_UNSIGNED_SHORT},
        {GL_R32F, GL_RED , GL_FLOAT},
        {GL_R8I, GL_RED_INTEGER , GL_BYTE},
        {GL_R16I, GL_RED_INTEGER , GL_SHORT},
        {GL_R32I, GL_RED_INTEGER , GL_INT},
        {GL_R8UI, GL_RED_INTEGER , GL_UNSIGNED_BYTE},
        {GL_R16UI, GL_RED_INTEGER , GL_UNSIGNED_SHORT},
        {GL_R32UI, GL_RED_INTEGER , GL_UNSIGNED_INT},
        {GL_RG8, GL_RG , GL_UNSIGNED_BYTE},
        {GL_RG16, GL_RG , GL_UNSIGNED_SHORT},
        {GL_RG8I, GL_RG_INTEGER , GL_BYTE},
        {GL_RG16I, GL_RG_INTEGER , GL_SHORT},
        {GL_RG8UI, GL_RG_INTEGER , GL_UNSIGNED_BYTE},
        {GL_RG16UI, GL_RG_INTEGER , GL_UNSIGNED_SHORT},
        {GL_RGBA8, GL_RGBA , GL_UNSIGNED_BYTE},
        {GL_RGBA8I, GL_RGBA_INTEGER , GL_BYTE},
        {GL_RGBA8UI, GL_RGBA_INTEGER , GL_UNSIGNED_BYTE}
};

bool setupGraphics(int i) {
    string vertexShaderPath   = ((string)GLSL_PATH) + "atomiccounter.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "atomiccounter.frag";

    Program = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));
    if (!Program) {
        LOGE("Could not create program.");
        return false;
    }
    GL_CHECK(glUseProgram(Program));
    GLint64 valData64_v;
    GL_CHECK(glGenVertexArrays(1, &VertexArrayName));
    GL_CHECK(glBindVertexArray(VertexArrayName));
    GL_CHECK(glGenBuffers(2, &BufferName[0]));
    GL_CHECK(glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, BufferName[0]));
    GL_CHECK(glGetInteger64i_v(GL_ATOMIC_COUNTER_BUFFER_SIZE, 0, &valData64_v));
    LOGI("atomic counter buffer size is %lld\n", valData64_v);


    GL_CHECK(glBufferStorage(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_MAP_WRITE_BIT));
    GLuint Data = 0;
    GL_CHECK(glClearBufferSubData(GL_ATOMIC_COUNTER_BUFFER, factors[i].interfmt, 0, sizeof(GLuint),
                                  factors[i].format, factors[i].type, &Data));
    GL_CHECK(glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0));
}

void render(int w, int h){
    
    GL_CHECK(glBindVertexArray(VertexArrayName));
    GL_CHECK(glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, BufferName[0]));
    GL_CHECK(glViewportIndexedf(0, 0, 0, (float)w/2.0, (float)h/2.0));
    GL_CHECK(glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 3, 1, 0));

    const GLfloat viewport[4] = {(float)w/2.0, (float)h/2.0, (float)w/2.0, (float)h/2.0};
    GL_CHECK(glViewportIndexedfv(0, &viewport[0]));
    GL_CHECK(glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 3, 1, 0));

    const GLfloat viewport1[4] = {0, (float)h/2.0, (float)w/2.0, (float)h/2.0};
    GL_CHECK(glViewportArrayv(0, 1, &viewport1[0]));
    GL_CHECK(glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 3, 1, 0));

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
    GL_CHECK(glDeleteVertexArrays(1, &VertexArrayName));
    GL_CHECK(glDeleteBuffers(2, &BufferName[0]));
}

void Sample::test() {
    for (int i = 0; i < ARRAY_NUM(factors); i++) {
        setupGraphics(i);
        char ss[2];
        sprintf(ss, "%d", i);
        render(WINDOW_W, WINDOW_H);
        string bmp_file = filename + "-" + ss + ".bmp";
        save2bmp(bmp_file.c_str());
        LOGI("bmp_file=%s\n", bmp_file.c_str());
        SwapBuffers();
        de_init();
    }
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}
