#include "Sample.h"
#include "Timer.h"
#include <string>

const static int          FRAMES_NUM = 10;
const static unsigned int VERTEX_NUM = 30000;
float                     vertices[VERTEX_NUM * 2];
float                     colors[VERTEX_NUM * 4];
GLuint                    vao, vbo, svbo, programID;

#define BUFFER_OFFSET(x)  ((const void*) (x))

bool
    initProgram() {
    GLint success;
    GLchar infoLog[512];

    string vertexShaderPath = ((string)GLSL_PATH) + "ssbo.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "ssbo.frag";
    programID = GL_CHECK(Shader::CreateProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str()));

    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        LOGI("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
    }
        glClearColor(0.0, 0.0, 0.0, 1.0);
        return true;
    }

    void
    initData() {
        for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); i++) {
            vertices[i] = ((float)(rand() % 100)) / 50 - 1;
        }


        for (int j = 0; j < sizeof(colors) / sizeof(colors[0]); j++) {
            colors[j] = ((float)(rand() % 50)) / 50;
        }
    }

    void
    renderFrame() {
        glUseProgram(programID);

        GL_CHECK(glGenVertexArrays(1, &vao));
        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glGenBuffers(1, &vbo));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
        GL_CHECK(glEnableVertexAttribArray(0));
        GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

        GL_CHECK(glGenBuffers(1, &svbo));
        GL_CHECK(glBindBuffer(GL_SHADER_STORAGE_BUFFER, svbo));
        GL_CHECK(glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(colors), colors, GL_DYNAMIC_COPY));
        GL_CHECK(GLuint storageblockindex = glGetProgramResourceIndex(programID,
                         GL_SHADER_STORAGE_BLOCK, "my_vertices"));
        GL_CHECK(glShaderStorageBlockBinding(programID, storageblockindex, 0));
        GL_CHECK(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, svbo));

        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, VERTEX_NUM));

    }


    void
    cleanUp() {
        glDeleteProgram(programID);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &svbo);
        glDeleteVertexArrays(1, &vao);

    }

void Sample::test() {
    Timer    *time     = new Timer();
    double   flopstime = 0.0;
    for (int j         = 0; j < FRAMES_NUM; j++) {
        time->reset();
        initProgram();
        initData();
        renderFrame();
        glFlush();
        flopstime = flopstime + time->getTime();
        string bmp_file = filename + ".bmp";
        save2bmp(bmp_file.c_str());
        SwapBuffers();
        cleanUp();
    }
    double   ave_time  = flopstime / FRAMES_NUM;
    LOGI("shadersotrage One frame average time:-%f\n", ave_time);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

