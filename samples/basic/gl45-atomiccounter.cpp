
/* ============================================================
 * Copyright (c) 2019 Botson Corp
 * Botson Confidential and Proprietary
 * =============================================================
 */

#include "Sample.h"

GLuint PipelineName;
GLuint ProgramName;
GLuint VertexArrayName;
GLuint BufferName[2];
GLuint fs;
GLuint vs;
bool setupGraphics() {
    const char *strings[1]        = {NULL};
    string     vertexShaderPath   = ((string)GLSL_PATH) + "atomiccounter.vert";
    string     fragmentShaderPath = ((string)GLSL_PATH) + "atomiccounter.frag";

    strings[0] = Shader::loadShader(vertexShaderPath.c_str());
    vs = GL_CHECK(glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings));
    strings[0] = Shader::loadShader(fragmentShaderPath.c_str());
    fs = GL_CHECK(glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings));

    GL_CHECK(glGenProgramPipelines(1, &PipelineName));
    GL_CHECK(glBindProgramPipeline(PipelineName));

    GLuint k = GL_CHECK(glIsProgramPipeline(PipelineName));
    LOGI("PIPELINE IS %d\n", k);
    GL_CHECK(glUseProgramStages(PipelineName, GL_VERTEX_SHADER_BIT, vs));
    GL_CHECK(glUseProgramStages(PipelineName, GL_FRAGMENT_SHADER_BIT, fs));

    GL_CHECK(glGenVertexArrays(1, &VertexArrayName));
    GL_CHECK(glBindVertexArray(VertexArrayName));

    GL_CHECK(glGenBuffers(2, &BufferName[0]));
    GL_CHECK(glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, BufferName[0]));
    GL_CHECK(glBufferStorage(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_MAP_WRITE_BIT));
    GLuint Data = 0;
    GL_CHECK(glClearBufferSubData(GL_ATOMIC_COUNTER_BUFFER, GL_R8UI, 0, sizeof(GLuint),
                         GL_RGBA, GL_UNSIGNED_INT, &Data));
    GL_CHECK(glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0));
}

void render(int w, int h){

    GL_CHECK(glBindProgramPipeline(PipelineName));
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
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_BINDING, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_BINDING = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER = %d\n", params);
    GL_CHECK(glGetActiveAtomicCounterBufferiv(fs, 0, GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER, &params));
    LOGI("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER = %d\n", params);
}

void de_init(){
    GL_CHECK(glDeleteVertexArrays(1, &VertexArrayName));
    GL_CHECK(glDeleteBuffers(2, &BufferName[0]));
    GL_CHECK(glDeleteProgramPipelines(1, &PipelineName));
}

void Sample::test() {
    setupGraphics();
    render(WINDOW_W, WINDOW_H);
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
