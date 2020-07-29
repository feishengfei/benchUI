#include "Sample.h"
#include "Timer.h"
#include <string>

const static int          FRAMES_NUM = 10;
const static unsigned int VERTEX_NUM = 30000;
float                     vertices[VERTEX_NUM * 2];
float                     colors[VERTEX_NUM * 4];
GLuint                    vao, vbo, vs, fs, pipe;

#define BUFFER_OFFSET(x)  ((const void*) (x))


bool
    initProgram() {
    const char *strings[1] = { NULL };
    string vertexShaderPath = ((string)GLSL_PATH) + "basic.vert";
    string fragmentShaderPath = ((string)GLSL_PATH) + "basic.frag";

    strings[0] = Shader::loadShader(vertexShaderPath.c_str());
    vs = GL_CHECK(glCreateShaderProgramv(GL_VERTEX_SHADER, 1, strings));
    strings[0] = Shader::loadShader(fragmentShaderPath.c_str());
    fs = GL_CHECK(glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, strings));

    GL_CHECK(glGenProgramPipelines(1, &pipe));
    GL_CHECK(glBindProgramPipeline(pipe));

    GL_CHECK(glUseProgramStages(pipe, GL_VERTEX_SHADER_BIT, vs));
    GL_CHECK(glUseProgramStages(pipe, GL_FRAGMENT_SHADER_BIT, fs));

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

        GL_CHECK(glGenVertexArrays(1, &vao));
        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glGenBuffers(1, &vbo));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(colors), NULL, GL_STATIC_DRAW));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
        GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors));
        GL_CHECK(glEnableVertexAttribArray(0));
        GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
        GL_CHECK(glEnableVertexAttribArray(1));
        GL_CHECK(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices))));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));

        GL_CHECK(glBindVertexArray(vao));
        GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, VERTEX_NUM));

    }


    void
    cleanUp() {
        glDeleteProgramPipelines(1, &pipe);
        glDeleteBuffers(1, &vbo);
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
    LOGI("pipeline One frame average time:--%f\n", ave_time);
}

int main(int argc, char **argv) {
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);

    sample.test();

    return 0;
}

